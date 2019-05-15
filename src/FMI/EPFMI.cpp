#include "EPFMI.hpp"
#include "EPComponent.hpp"
#include "../EnergyPlus/public/EnergyPlusPgm.hh"
#include "../EnergyPlus/CommandLineInterface.hh"
#include "../EnergyPlus/ZoneTempPredictorCorrector.hh"
#include "../EnergyPlus/DataGlobals.hh"
#include "../EnergyPlus/DataHeatBalFanSys.hh"
#include "../EnergyPlus/DataHeatBalance.hh"
#include "../EnergyPlus/DataEnvironment.hh"
#include "../EnergyPlus/FMIDataGlobals.hh"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>

using namespace std::placeholders;

#define UNUSED(expr) do { (void)(expr); } while (0);

std::list<EPComponent> epComponents;

EPFMI_API fmi2Component fmi2Instantiate(fmi2String instanceName,
  fmi2Type fmuType,
  fmi2String fmuGUID,
  fmi2String fmuResourceLocation,
  const fmi2CallbackFunctions* functions,
  fmi2Boolean visible,
  fmi2Boolean loggingOn)
{
  UNUSED(fmuType);
  UNUSED(fmuGUID);
  UNUSED(fmuResourceLocation);
  UNUSED(functions);
  UNUSED(visible);
  UNUSED(loggingOn);

  epComponents.emplace_back();
  auto & comp = epComponents.back();
  comp.instanceName = instanceName;

  return &comp;
}


EPFMI_API fmi2Status fmi2SetupExperiment(fmi2Component c,
  fmi2Boolean toleranceDefined,
  fmi2Real tolerance,
  fmi2Real startTime,
  fmi2Boolean stopTimeDefined,
  fmi2Real stopTime)
{
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  epcomp->toleranceDefined = toleranceDefined;
  epcomp->tolerance = tolerance;
  epcomp->startTime = startTime;
  epcomp->stopTimeDefined = stopTimeDefined;
  epcomp->stopTime = stopTime;

  auto simulation = [&epcomp](){
    const int argc = 8;
    const char * argv[argc];
    argv[0] = "energyplus";
    argv[1] = "-d";
    argv[2] = epcomp->instanceName;
    argv[3] = "-w";
    argv[4] = epcomp->weatherFilePath;
    argv[5] = "-i";
    argv[6] = epcomp->iddPath;
    argv[7] = epcomp->idfInputPath;
    
    EnergyPlus::epcomp = epcomp;
    EnergyPlus::CommandLineInterface::ProcessArgs( argc, argv );
    RunEnergyPlus();
  };

  {
    std::unique_lock<std::mutex> lk(epcomp->time_mutex);
    epcomp->currentTime = 0.0;
    epcomp->epstatus = EPStatus::WORKING;
  }

  std::cout << "start thread" << std::endl;

  epcomp->simthread = std::thread(simulation);

  {
    // Wait for E+ to go back to IDLE
    std::unique_lock<std::mutex> lk( epcomp->time_mutex );
    epcomp->time_cv.wait( lk, [&epcomp](){ return epcomp->epstatus == EPStatus::IDLE; } );
  }

  std::cout << "done wait after start thread" << std::endl;

  return fmi2OK;
}

//  //for ( const auto & param : parameters ) {
//  //  if ( param.varName == "V" ) {
//  //    valueGetters[param.valueRef] = std::bind(getZoneVolume, _1, param.zoneNum());
//  //  } else if ( param.varName == "AFlo" ) {
//  //    valueGetters[param.valueRef] = std::bind(getZoneFloorArea, _1, param.zoneNum());
//  //  } else if ( param.varName == "mSenFac" ) {
//  //    valueGetters[param.valueRef] = std::bind(getZoneCapacityMult, _1, param.zoneNum());
//  //  } else {
//  //    std::cout << "parameter named " << param.varName << " is not valid" << std::endl;
//  //  }
//  //}
//
//  //for ( const auto & input : inputs ) {
//  //  if ( input.varName == "T" ) {
//  //    valueSetters[input.valueRef] = std::bind(setZoneTemperature, _1, input.zoneNum());
//  //  } else {
//  //    std::cout << "input named " << input.varName << " is not valid" << std::endl;
//  //  }
//  //}
//
//  //for ( const auto & output : outputs ) {
//  //  if ( output.varName == "QConSen_flow" ) {
//  //    valueGetters[output.valueRef] = std::bind(getZoneH, _1, output.zoneNum());
//  //  } else {
//  //    std::cout << "output named " << output.varName << " is not valid" << std::endl;
//  //  }
//  //}

EPFMI_API fmi2Status fmi2SetTime(fmi2Component c, fmi2Real time)
{
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
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  eventInfo->nextEventTime = epcomp->nextSimTime;
  eventInfo->nextEventTimeDefined = fmi2True;
  eventInfo->terminateSimulation = fmi2False;

  return fmi2OK;
}

EPFMI_API fmi2Status fmi2Terminate(fmi2Component c)
{
  EPComponent * epcomp = static_cast<EPComponent*>(c);

  {
    std::unique_lock<std::mutex> lk(epcomp->time_mutex);
    epcomp->epstatus = EPStatus::TERMINATING;
  }
  // Notify E+ to advance
  epcomp->time_cv.notify_one();
  epcomp->simthread.join();

  // TODO: Something like this
  //auto it = std::find(epComponents.begin(), epComponents.end(), *epcomp);
  //if ( it != epComponents.end() ) {
  //  epComponents.erase(it);
  //}

  return fmi2OK;
}

