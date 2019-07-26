#include "EPFMI.hpp"
#include "EPComponent.hpp"
#include <fmi2Functions.h>
#include "../EnergyPlus/public/EnergyPlusPgm.hh"
#include "../EnergyPlus/CommandLineInterface.hh"
#include "../EnergyPlus/ZoneTempPredictorCorrector.hh"
#include "../EnergyPlus/DataGlobals.hh"
#include "../EnergyPlus/DataHeatBalFanSys.hh"
#include "../EnergyPlus/DataHeatBalance.hh"
#include "../EnergyPlus/DataEnvironment.hh"
#include "../EnergyPlus/FMIDataGlobals.hh"
#include "../EnergyPlus/InputProcessing/IdfParser.hh"
#include "../EnergyPlus/InputProcessing/EmbeddedEpJSONSchema.hh"
#include <boost/filesystem.hpp>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
#include <regex>

using namespace std::placeholders;

#define UNUSED(expr) do { (void)(expr); } while (0);

std::list<EPComponent> epComponents;

using json = nlohmann::json;

EPFMI_API fmi2Component fmi2Instantiate(fmi2String instanceName,
  fmi2Type fmuType,
  fmi2String fmuGUID,
  fmi2String fmuResourceURI,
  const fmi2CallbackFunctions* functions,
  fmi2Boolean visible,
  fmi2Boolean loggingOn)
{
  UNUSED(fmuType);
  UNUSED(fmuGUID);
  UNUSED(functions);
  UNUSED(visible);
  UNUSED(loggingOn);

  std::cout << "fmi2Instantiate called" << std::endl;

  epComponents.emplace_back();
  auto & comp = epComponents.back();
  comp.instanceName = instanceName;

	const auto resourcePathString = std::regex_replace(fmuResourceURI, std::regex("^file://"), "");
  const auto resourcePath = boost::filesystem::path(resourcePathString);

  boost::system::error_code ec;
  for ( const auto & entry : boost::filesystem::directory_iterator(resourcePath, ec) ) {
    const auto path = entry.path();
    const auto extension = path.extension();
    if ( extension == ".idf" ) {
      comp.idfInputPath = path.string();
    } else if ( extension == ".epw" ) {
      comp.weatherFilePath = path.string();
    } else if ( extension == ".idd" ) {
      comp.iddPath = path.string();
    }
  }

  comp.variables = EnergyPlus::FMI::parseVariables(comp.idfInputPath);

  return &comp;
}

EPFMI_API fmi2Status fmi2SetupExperiment(fmi2Component c,
  fmi2Boolean toleranceDefined,
  fmi2Real tolerance,
  fmi2Real startTime,
  fmi2Boolean stopTimeDefined,
  fmi2Real stopTime)
{
  std::cout << "fmi2SetupExperiment called" << std::endl;
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  epcomp->toleranceDefined = toleranceDefined;
  epcomp->tolerance = tolerance;
  epcomp->startTime = startTime;
  epcomp->stopTimeDefined = stopTimeDefined;
  epcomp->stopTime = stopTime;

  auto simulation = [&epcomp](){
    auto workingPath = boost::filesystem::path(epcomp->instanceName).filename();

    const int argc = 8;
    const char * argv[argc];
    argv[0] = "energyplus";
    argv[1] = "-d";
    argv[2] = workingPath.string().c_str();
    argv[3] = "-w";
    argv[4] = epcomp->weatherFilePath.c_str();
    argv[5] = "-i";
    argv[6] = epcomp->iddPath.c_str();
    argv[7] = epcomp->idfInputPath.c_str();

    EnergyPlus::epcomp = epcomp;
    EnergyPlus::CommandLineInterface::ProcessArgs( argc, argv );
    RunEnergyPlus();
  };

  {
    std::unique_lock<std::mutex> lk(epcomp->time_mutex);
    epcomp->currentTime = 0.0;
    epcomp->epstatus = EPStatus::WORKING;
  }

  epcomp->simthread = std::thread(simulation);

  {
    // Wait for E+ to go back to IDLE
    std::unique_lock<std::mutex> lk( epcomp->time_mutex );
    epcomp->time_cv.wait( lk, [&epcomp](){ return epcomp->epstatus == EPStatus::IDLE; } );
  }

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2SetTime(fmi2Component c, fmi2Real time)
{
  std::cout << "fmi2SetTime called" << std::endl;
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  {
    std::unique_lock<std::mutex> lk(epcomp->time_mutex);
    epcomp->currentTime = time;
    epcomp->epstatus = EPStatus::WORKING;
  }
  // Notify E+ to advance
  epcomp->time_cv.notify_one();
  {
    // Wait for E+ to advance and go back to IDLE before returning
    std::unique_lock<std::mutex> lk( epcomp->time_mutex );
    epcomp->time_cv.wait( lk, [&epcomp](){ return epcomp->epstatus == EPStatus::IDLE; } );
  }
  
  return fmi2OK;
}

EPFMI_API fmi2Status fmi2SetReal(fmi2Component c,
  const fmi2ValueReference vr[],
  size_t nvr,
  const fmi2Real values[])
{
  std::cout << "fmi2SetReal called" << std::endl;
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  for ( size_t i = 0; i < nvr; ++i ) {
    auto valueRef = vr[i];
    auto value = values[i];
    auto varit = epcomp->variables.find(valueRef);
    if ( varit != epcomp->variables.end() ) {
      varit->second.value = value;
    }
  }

  epcomp->time_cv.notify_one();
  {
    // Wait for E+ to advance and go back to IDLE before returning
    std::unique_lock<std::mutex> lk( epcomp->time_mutex );
    epcomp->time_cv.wait( lk, [&epcomp](){ return epcomp->epstatus == EPStatus::IDLE; } );
  }

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetReal(fmi2Component c,
  const fmi2ValueReference vr[],
  size_t nvr,
  fmi2Real values[])
{
  std::cout << "fmi2GetReal called" << std::endl;
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  for ( size_t i = 0; i < nvr; ++i ) {
    auto valueRef = vr[i];
    auto varit = epcomp->variables.find(valueRef);
    if ( varit != epcomp->variables.end() ) {
      values[i] = varit->second.value;
    }
  }

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2NewDiscreteStates(fmi2Component  c, fmi2EventInfo* eventInfo)
{
  std::cout << "fmi2NewDiscreteStates called" << std::endl;

  EPComponent * epcomp = static_cast<EPComponent*>(c);

  eventInfo->newDiscreteStatesNeeded = fmi2False;
  eventInfo->nextEventTime = epcomp->nextSimTime;
  eventInfo->nextEventTimeDefined = fmi2True;
  eventInfo->terminateSimulation = fmi2False;

  return fmi2OK;
}

void stopEnergyPlus(fmi2Component c) {
  std::cout << "stopEnergyPlus called" << std::endl;

  EPComponent * epcomp = static_cast<EPComponent*>(c);

  {
    std::unique_lock<std::mutex> lk(epcomp->time_mutex);
    epcomp->epstatus = EPStatus::TERMINATING;
  }
  // Notify E+ to advance
  epcomp->time_cv.notify_one();
  epcomp->simthread.join();
}

EPFMI_API fmi2Status fmi2Terminate(fmi2Component c)
{
  std::cout << "fmi2Terminate called" << std::endl;
  stopEnergyPlus(c);

  return fmi2OK;
}

EPFMI_API const char* fmi2GetTypesPlatform(void)
{
  std::cout << "fmi2GetTypesPlatform called" << std::endl;
  return fmi2TypesPlatform;
}

EPFMI_API const char* fmi2GetVersion(void)
{
  std::cout << "fmi2GetVersion called" << std::endl;
  return fmi2Version;
}

EPFMI_API fmi2Status fmi2SetDebugLogging(fmi2Component, fmi2Boolean, size_t, const fmi2String[])
{
  std::cout << "Logging not enabled yet" << std::endl;
  return fmi2OK;
}

EPFMI_API fmi2Status fmi2Reset(fmi2Component c)
{
  std::cout << "fmi2Reset called" << std::endl;
  EPComponent * epcomp = static_cast<EPComponent*>(c);
  stopEnergyPlus(c);
  epcomp->variables = EnergyPlus::FMI::parseVariables(epcomp->idfInputPath);

  return fmi2OK;
}

EPFMI_API void fmi2FreeInstance(fmi2Component c)
{
  std::cout << "fmi2FreeInstance called" << std::endl;
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  auto it = std::find(epComponents.begin(), epComponents.end(), *epcomp);
  epComponents.erase(it);

  c = nullptr;
}

EPFMI_API fmi2Status fmi2EnterInitializationMode(fmi2Component)
{
  std::cout << "fmi2EnterInitializationMode called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2ExitInitializationMode(fmi2Component)
{
  std::cout << "fmi2ExitInitializationMode called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetInteger(fmi2Component, const fmi2ValueReference[], size_t, fmi2Integer[])
{
  std::cout << "fmi2GetInteger called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetBoolean(fmi2Component, const fmi2ValueReference[], size_t, fmi2Boolean[])
{
  std::cout << "fmi2GetBoolean called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetString(fmi2Component, const fmi2ValueReference[], size_t, fmi2String [])
{
  std::cout << "fmi2GetString called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2SetInteger(fmi2Component, const fmi2ValueReference[], size_t, const fmi2Integer[])
{
  std::cout << "fmi2SetInteger called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2SetBoolean(fmi2Component, const fmi2ValueReference[], size_t, const fmi2Boolean[])
{
  std::cout << "fmi2SetInteger called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2SetString(fmi2Component, const fmi2ValueReference[], size_t, const fmi2String [])
{
  std::cout << "fmi2SetString called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2EnterEventMode(fmi2Component)
{
  std::cout << "fmi2EnterEventMode called" << std::endl;

  return fmi2OK;
}


EPFMI_API fmi2Status fmi2EnterContinuousTimeMode(fmi2Component)
{
  std::cout << "fmi2EnterContinuousTimeMode called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2CompletedIntegratorStep(fmi2Component, fmi2Boolean, fmi2Boolean*, fmi2Boolean*)
{
  std::cout << "fmi2CompletedIntegratorStep called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2SetContinuousStates(fmi2Component, const fmi2Real[], size_t)
{
  std::cout << "fmi2SetContinuousStates called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetDerivatives(fmi2Component, fmi2Real[], size_t)
{
  std::cout << "fmi2GetDerivatives called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetEventIndicators(fmi2Component, fmi2Real[], size_t)
{
  std::cout << "fmi2GetEventIndicators called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetContinuousStates(fmi2Component, fmi2Real[], size_t)
{
  std::cout << "fmi2GetContinuousStates called" << std::endl;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2GetNominalsOfContinuousStates(fmi2Component, fmi2Real[], size_t)
{
  std::cout << "fmi2GetNominalsOfContinuousStates called" << std::endl;

  return fmi2OK;
}


