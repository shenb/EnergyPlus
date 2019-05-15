#include <gtest/gtest.h>
#include "../EPFMI.hpp"
#include "../EPComponent.hpp"
#include "test-config.h"
#include "../EnergyPlus/DataEnvironment.hh"

EPComponent * createComponent() {
};

TEST( EPFMI, static_lib ) {

  auto comp = fmi2Instantiate("Building_1", // instanceName
    fmi2ModelExchange, // fmuType
    "", // fmuGUID
    "", // fmuResourceLocation
    NULL, // functions
    true, // visible
    false); // loggingOn

  EPComponent * epcomp = static_cast<EPComponent*>(comp);

  epcomp->weatherFilePath = weather;
  epcomp->iddPath = idd;
  epcomp->idfInputPath = input; // This is path to small office idf

  epcomp->variables.emplace(0,Variable("Attic,T", VariableType::INPUT));
  epcomp->variables.emplace(1,Variable("Attic,QConSen_flow", VariableType::OUTPUT));
  epcomp->variables.emplace(2,Variable("Attic,V", VariableType::PARAMETER));
  epcomp->variables.emplace(3,Variable("Attic,AFlo", VariableType::PARAMETER));
  epcomp->variables.emplace(4,Variable("Attic,mSenFac", VariableType::PARAMETER));

  auto comp2 = fmi2Instantiate("Building_2", // instanceName
    fmi2ModelExchange, // fmuType
    "", // fmuGUID
    "", // fmuResourceLocation
    NULL, // functions
    true, // visible
    false); // loggingOn

  EPComponent * epcomp2 = static_cast<EPComponent*>(comp2);

  epcomp2->weatherFilePath = weather;
  epcomp2->iddPath = idd;
  epcomp2->idfInputPath = input2; // This is path to hotel idf

  epcomp2->variables.emplace(0,Variable("GuestRoom101,T", VariableType::INPUT));
  epcomp2->variables.emplace(1,Variable("GuestRoom101,QConSen_flow", VariableType::OUTPUT));
  epcomp2->variables.emplace(2,Variable("GuestRoom101,V", VariableType::PARAMETER));
  epcomp2->variables.emplace(3,Variable("GuestRoom101,AFlo", VariableType::PARAMETER));
  epcomp2->variables.emplace(4,Variable("GuestRoom101,mSenFac", VariableType::PARAMETER));

  double tStart = 0.0;
  double tEnd = 86400;

  double outputs[] = {0.0};
  const unsigned int outputRefs[] = {1}; // Attic,QConSen_flow
  double inputs[] = {21.0};
  const unsigned int inputRefs[] = {0}; // Attic,T...
  const unsigned int paramRefs[] = {2}; // Attic,V
  double params[1];

  double outputs2[] = {0.0};
  const unsigned int outputRefs2[] = {1}; // Attic,QConSen_flow
  double inputs2[] = {21.0};
  const unsigned int inputRefs2[] = {0}; // Attic,T...
  const unsigned int paramRefs2[] = {2}; // Attic,V
  double params2[1];

  fmi2SetupExperiment(epcomp, // component
    false, // toleranceDefined
    0, // tolerance
    tStart, // startTime
    true, // stopTimeDefined
    tEnd); // stopTime

  fmi2SetupExperiment(epcomp2, // component
    false, // toleranceDefined
    0, // tolerance
    tStart, // startTime
    true, // stopTimeDefined
    tEnd); // stopTime

  fmi2EventInfo eventInfo;

  fmi2GetReal(epcomp, paramRefs, 1, params);
  double atticVolume = params[0]; // m^3

  double atticTemp = 21.0;
  inputs[0] = atticTemp;
  fmi2SetReal(epcomp, inputRefs, 6, inputs);

  double time = tStart;
  fmi2SetTime(epcomp, time);

  while ( time < tEnd ) {
    // Advance time of both simulations based on 
    // events from the small office. they should have the same timestep / time events anyway
    fmi2NewDiscreteStates(epcomp, &eventInfo);
    double lastTime = time;
    time = eventInfo.nextEventTime;
    fmi2SetTime(epcomp, time);
    fmi2SetTime(epcomp2, time);
    double dt = time - lastTime;

    // Do something interesting with the small office attic.
    inputs[0] = atticTemp;
    fmi2SetReal(epcomp, inputRefs, 6, inputs);

    // update atticTemp
    fmi2GetReal(epcomp, outputRefs, 1, outputs);

    double atticQFlow = outputs[0]; // J/s 
    std::cout << "atticQFlow: " << atticQFlow << std::endl;
    double densityAir = 1.276; // kg/m^3
    double heatCapacity = 1000.6; // J/kgK
    double tempDot = atticQFlow / ( atticVolume * densityAir * heatCapacity );

    atticTemp = atticTemp + (dt * tempDot);

    std::cout << "Current time: " << time << std::endl;
    std::cout << "Attic Temp is: " << atticTemp << std::endl;
  }

  fmi2Terminate(epcomp);
  fmi2Terminate(epcomp2);

  std::cout << "epfmi test is now complete" << std::endl;
}

