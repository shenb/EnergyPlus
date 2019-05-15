// EnergyPlus, Copyright (c) 1996-2018, The Board of Trustees of the University of Illinois,
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy), Oak Ridge
// National Laboratory, managed by UT-Battelle, Alliance for Sustainable Energy, LLC, and other
// contributors. All rights reserved.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without the U.S. Department of Energy's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// EnergyPlus Headers
#include <DataHVACGlobals.hh>
#include <DataPrecisionGlobals.hh>

namespace EnergyPlus {

namespace DataHVACGlobals {

    // MODULE INFORMATION:
    //       MODIFIED       Craig Wray 22Aug2010 Added Fan Component Model

    // PURPOSE OF THIS MODULE:
    // This data-only module is a repository for HVAC variables which are considered
    // to be "global" in nature in EnergyPlus.

    // METHODOLOGY EMPLOYED:

    // REFERENCES:

    // OTHER NOTES:

    // Using/Aliasing
    using namespace DataPrecisionGlobals;

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    // MODULE PARAMETER DEFINITIONS:

    // EModelica EMO;

    thread_local Real64 const SmallTempDiff(1.0E-5);
    thread_local Real64 const SmallMassFlow(0.001);
    thread_local Real64 const VerySmallMassFlow(1.0E-30);
    thread_local Real64 const SmallLoad(1.0);
    thread_local Real64 const TempControlTol(0.1); // temperature control tolerance for packaged equip. [deg C]
    thread_local Real64 const SmallAirVolFlow(0.001);
    thread_local Real64 const SmallWaterVolFlow(1.0E-9);
    thread_local Real64 const BlankNumeric(-99999.0);      // indicates numeric input field was blank
    thread_local Real64 const RetTempMax(60.0);            // maximum return air temperature [deg C]
    thread_local Real64 const RetTempMin(-30.0);           // minimum return air temperature [deg C]
    thread_local Real64 const DesCoilHWInletTempMin(46.0); // minimum heating water coil water inlet temp for UA sizing only. [deg C]

    // Number of Sizing types from list below
    thread_local int const NumOfSizingTypes(33); // number of sizing types

    // Sizing types
    thread_local int const CoolingAirflowSizing(1);                               // request sizing for cooling air flow rate
    thread_local int const CoolingWaterflowSizing(2);                             // request sizing for cooling water flow rate
    thread_local int const HeatingWaterflowSizing(3);                             // request sizing for heating coil water flow rate
    thread_local int const CoolingWaterDesAirInletTempSizing(4);                  // request sizing for cooling water coil inlet air temp
    thread_local int const CoolingWaterDesAirInletHumRatSizing(5);                // request sizing for cooling water coil inlet air humidity ratio
    thread_local int const CoolingWaterDesWaterInletTempSizing(6);                // request sizing for cooling water coil inlet water temp
    thread_local int const CoolingWaterDesAirOutletTempSizing(7);                 // request sizing for cooling water coil outlet air temp
    thread_local int const CoolingWaterDesAirOutletHumRatSizing(8);               // request sizing for cooling water coil outlet air humidity ratio
    thread_local int const CoolingWaterNumofTubesPerRowSizing(9);                 // request sizing for cooling water coil number of tubes per row
    thread_local int const HeatingWaterDesAirInletTempSizing(10);                 // request sizing for heating water coil inlet air temp
    thread_local int const HeatingWaterDesAirInletHumRatSizing(11);               // request sizing for heating water coil inlet air humidity ratio
    thread_local int const HeatingWaterDesCoilLoadUsedForUASizing(12);            // request sizing for heating water coil capacity used for UA sizing
    thread_local int const HeatingWaterDesCoilWaterVolFlowUsedForUASizing(13);    // request sizing for heating water coil volume flow rate used for UA sizing
    thread_local int const HeatingAirflowSizing(14);                              // request sizing for heating air flow rate
    thread_local int const HeatingAirflowUASizing(15);                            // request sizing for heating air flow rate
    thread_local int const SystemAirflowSizing(16);                               // request sizing for system air flow rate
    thread_local int const CoolingCapacitySizing(17);                             // request sizing for cooling capacity
    thread_local int const HeatingCapacitySizing(18);                             // request sizing for heating capacity
    thread_local int const WaterHeatingCapacitySizing(19);                        // request sizing for water-side heating capacity
    thread_local int const WaterHeatingCoilUASizing(20);                          // request sizing for heating coil UA
    thread_local int const SystemCapacitySizing(21);                              // request sizing for system capacity
    thread_local int const CoolingSHRSizing(22);                                  // request sizing for cooling SHR
    thread_local int const HeatingDefrostSizing(23);                              // request sizing for heating defrost capacity
    thread_local int const MaxHeaterOutletTempSizing(24);                         // request sizing for heating coil maximum outlet temperature
    thread_local int const AutoCalculateSizing(25);                               // identifies an autocalulate input
    thread_local int const ZoneCoolingLoadSizing(26);                             // zone cooling sensible load (zsz file)
    thread_local int const ZoneHeatingLoadSizing(27);                             // zome heating sensible load (zsz file)
    thread_local int const MinSATempCoolingSizing(28);                            // minimum SA temperature in cooling
    thread_local int const MaxSATempHeatingSizing(29);                            // maximum SA temperature in heating
    thread_local int const ASHRAEMinSATCoolingSizing(30);                         // minimum SA temperature in cooling model when using ASHRAE 90.1 SZVAV method
    thread_local int const ASHRAEMaxSATHeatingSizing(31);                         // maximum SA temperature in heating model when using ASHRAE 90.1 SZVAV method
    thread_local int const HeatingCoilDesAirInletTempSizing(32);                  // design inlet air temperature for heating coil
    thread_local int const HeatingCoilDesAirOutletTempSizing(33);                 // design outlet air temperature for heating coil
    thread_local int const HeatingCoilDesAirInletHumRatSizing(34);                // design inlet air humidity ratio for heating coil
    thread_local int const DesiccantDehumidifierBFPerfDataFaceVelocitySizing(35); // identifies desiccant performance data face velocity autosisizing input

    // Condenser Type (using same numbering scheme as for chillers)
    thread_local int const AirCooled(1);   // Air-cooled condenser
    thread_local int const WaterCooled(2); // Water-cooled condenser
    thread_local int const EvapCooled(3);  // Evaporatively-cooled condenser
    thread_local int const WaterHeater(4); // Condenser heats water (e.g., in water heater tank)

    // The following parameters are used for system availability status
    thread_local int const NoAction(0);
    thread_local int const ForceOff(1);
    thread_local int const CycleOn(2);
    thread_local int const CycleOnZoneFansOnly(3);
    // The following parameters describe the setpoint types in TempControlType(ActualZoneNum)
    thread_local int const SingleHeatingSetPoint(1);
    thread_local int const SingleCoolingSetPoint(2);
    thread_local int const SingleHeatCoolSetPoint(3);
    thread_local int const DualSetPointWithDeadBand(4);
    // parameters describing air duct type
    thread_local int const Main(1);
    thread_local int const Cooling(2);
    thread_local int const Heating(3);
    thread_local int const Other(4);
    thread_local int const RAB(5);
    // parameters describing fan types
    thread_local int const NumAllFanTypes(6); // cpw22Aug2010 (was 4)

    // fan types
    thread_local int const FanType_SimpleConstVolume(1);
    thread_local int const FanType_SimpleVAV(2);
    thread_local int const FanType_SimpleOnOff(3);
    thread_local int const FanType_ZoneExhaust(4);
    thread_local int const FanType_ComponentModel(5);    // cpw22Aug2010
    thread_local int const FanType_SystemModelObject(6); // new for V8.7, simple versatile fan object

    // Fan Minimum Flow Fraction Input Method
    thread_local int const MinFrac(1);
    thread_local int const FixedMin(2);
    // Fan mode
    thread_local int const CycFanCycCoil(1);  // Cycling fan, cycling coil = 1
    thread_local int const ContFanCycCoil(2); // Continuous fan, cycling coil = 2
    // Fan placement
    thread_local int const BlowThru(1); // fan before coil
    thread_local int const DrawThru(2); // fan after coil
    // OA Controller Heat Recovery Bypass Control Types
    thread_local int const BypassWhenWithinEconomizerLimits(0);   // heat recovery controlled by economizer limits
    thread_local int const BypassWhenOAFlowGreaterThanMinimum(1); // heat recovery ON at minimum OA in economizer mode

    thread_local Array1D_string const
        cFanTypes(NumAllFanTypes,
                  {"Fan:ConstantVolume", "Fan:VariableVolume", "Fan:OnOff", "Fan:ZoneExhaust", "Fan:ComponentModel", "Fan:SystemModel"});

    // parameters describing unitary systems
    thread_local int const NumUnitarySystemTypes(7);
    // Furnace/Unitary System Types
    thread_local int const Furnace_HeatOnly(1);
    thread_local int const Furnace_HeatCool(2);
    thread_local int const UnitarySys_HeatOnly(3);
    thread_local int const UnitarySys_HeatCool(4);
    thread_local int const UnitarySys_HeatPump_AirToAir(5);
    thread_local int const UnitarySys_HeatPump_WaterToAir(6);
    thread_local int const UnitarySys_AnyCoilType(7);
    thread_local Array1D_string const cFurnaceTypes(NumUnitarySystemTypes,
                                       {"AirLoopHVAC:Unitary:Furnace:HeatOnly",
                                        "AirLoopHVAC:Unitary:Furnace:HeatCool",
                                        "AirLoopHVAC:UnitaryHeatOnly",
                                        "AirLoopHVAC:UnitaryHeatCool",
                                        "AirLoopHVAC:UnitaryHeatPump:AirToAir",
                                        "AirLoopHVAC:UnitaryHeatPump:WaterToAir",
                                        "AirLoopHVAC:UnitarySystem"});

    // parameters describing coil types
    thread_local int const NumAllCoilTypes(34);

    thread_local int const CoilDX_CoolingSingleSpeed(1);
    thread_local int const CoilDX_HeatingEmpirical(2);
    thread_local int const CoilDX_CoolingTwoSpeed(3);
    thread_local int const CoilDX_CoolingHXAssisted(4);
    thread_local int const CoilDX_CoolingTwoStageWHumControl(5);
    thread_local int const CoilDX_HeatPumpWaterHeaterPumped(6);
    thread_local int const CoilDX_HeatPumpWaterHeaterWrapped(7);
    thread_local int const CoilDX_MultiSpeedCooling(8);
    thread_local int const CoilDX_MultiSpeedHeating(9);

    thread_local int const Coil_HeatingGasOrOtherFuel(10);
    thread_local int const Coil_HeatingGas_MultiStage(11);
    thread_local int const Coil_HeatingElectric(12);
    thread_local int const Coil_HeatingElectric_MultiStage(13);
    thread_local int const Coil_HeatingDesuperheater(14);

    thread_local int const Coil_CoolingWater(15);
    thread_local int const Coil_CoolingWaterDetailed(16);
    thread_local int const Coil_HeatingWater(17);
    thread_local int const Coil_HeatingSteam(18);
    thread_local int const CoilWater_CoolingHXAssisted(19);

    thread_local int const Coil_CoolingWaterToAirHP(20);
    thread_local int const Coil_HeatingWaterToAirHP(21);
    thread_local int const Coil_CoolingWaterToAirHPSimple(22);
    thread_local int const Coil_HeatingWaterToAirHPSimple(23);
    thread_local int const CoilVRF_Cooling(24);
    thread_local int const CoilVRF_Heating(25);

    thread_local int const Coil_UserDefined(26);
    thread_local int const CoilDX_PackagedThermalStorageCooling(27);

    thread_local int const Coil_CoolingWaterToAirHPVSEquationFit(28);
    thread_local int const Coil_HeatingWaterToAirHPVSEquationFit(29);
    thread_local int const Coil_CoolingAirToAirVariableSpeed(30);
    thread_local int const Coil_HeatingAirToAirVariableSpeed(31);
    thread_local int const CoilDX_HeatPumpWaterHeaterVariableSpeed(32);

    thread_local int const CoilVRF_FluidTCtrl_Cooling(33);
    thread_local int const CoilVRF_FluidTCtrl_Heating(34);

    thread_local Array1D_string const cAllCoilTypes(NumAllCoilTypes,
                                       {"Coil:Cooling:DX:SingleSpeed",
                                        "Coil:Heating:DX:SingleSpeed",
                                        "Coil:Cooling:DX:TwoSpeed",
                                        "CoilSystem:Cooling:DX:HeatExchangerAssisted",
                                        "Coil:Cooling:DX:TwoStageWithHumidityControlMode",
                                        "Coil:WaterHeating:AirToWaterHeatPump:Pumped",
                                        "Coil:WaterHeating:AirToWaterHeatPump:Wrapped",
                                        "Coil:Cooling:DX:MultiSpeed",
                                        "Coil:Heating:DX:MultiSpeed",
                                        "Coil:Heating:Fuel",
                                        "Coil:Heating:Gas:MultiStage",
                                        "Coil:Heating:Electric",
                                        "Coil:Heating:Electric:MultiStage",
                                        "Coil:Heating:Desuperheater",
                                        "Coil:Cooling:Water",
                                        "Coil:Cooling:Water:DetailedGeometry",
                                        "Coil:Heating:Water",
                                        "Coil:Heating:Steam",
                                        "CoilSystem:Cooling:Water:HeatExchangerAssisted",
                                        "Coil:Cooling:WaterToAirHeatPump:ParameterEstimation",
                                        "Coil:Heating:WaterToAirHeatPump:ParameterEstimation",
                                        "Coil:Cooling:WaterToAirHeatPump:EquationFit",
                                        "Coil:Heating:WaterToAirHeatPump:EquationFit",
                                        "Coil:Cooling:DX:VariableRefrigerantFlow",
                                        "Coil:Heating:DX:VariableRefrigerantFlow",
                                        "Coil:UserDefined",
                                        "Coil:Cooling:DX:SingleSpeed:ThermalStorage",
                                        "Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit",
                                        "Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit",
                                        "Coil:Cooling:DX:VariableSpeed",
                                        "Coil:Heating:DX:VariableSpeed",
                                        "Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed",
                                        "Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl",
                                        "Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl"});

    thread_local Array1D_string const cCoolingCoilTypes(NumAllCoilTypes,
                                           {"Coil:Cooling:DX:SingleSpeed",
                                            "",
                                            "Coil:Cooling:DX:TwoSpeed",
                                            "CoilSystem:Cooling:DX:HeatExchangerAssisted",
                                            "Coil:Cooling:DX:TwoStageWithHumidityControlMode",
                                            "",
                                            "",
                                            "Coil:Cooling:DX:MultiSpeed",
                                            "",
                                            "",
                                            "",
                                            "",
                                            "",
                                            "",
                                            "Coil:Cooling:Water",
                                            "Coil:Cooling:Water:DetailedGeometry",
                                            "",
                                            "",
                                            "CoilSystem:Cooling:Water:HeatExchangerAssisted",
                                            "Coil:Cooling:WaterToAirHeatPump:ParameterEstimation",
                                            "",
                                            "Coil:Cooling:WaterToAirHeatPump:EquationFit",
                                            "",
                                            "Coil:Cooling:DX:VariableRefrigerantFlow",
                                            "",
                                            "",
                                            "Coil:Cooling:DX:SingleSpeed:ThermalStorage",
                                            "Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit",
                                            "",
                                            "Coil:Cooling:DX:VariableSpeed",
                                            "",
                                            "",
                                            "Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl",
                                            ""});

    thread_local Array1D_string const cHeatingCoilTypes(NumAllCoilTypes,
                                           {"",
                                            "Coil:Heating:DX:SingleSpeed",
                                            "",
                                            "",
                                            "",
                                            "Coil:WaterHeating:AirToWaterHeatPump:Pumped",
                                            "Coil:WaterHeating:AirToWaterHeatPump:Wrapped",
                                            "",
                                            "Coil:Heating:DX:MultiSpeed",
                                            "Coil:Heating:Fuel",
                                            "Coil:Heating:Gas:MultiStage",
                                            "Coil:Heating:Electric",
                                            "Coil:Heating:Electric:MultiStage",
                                            "Coil:Heating:Desuperheater",
                                            "",
                                            "",
                                            "Coil:Heating:Water",
                                            "Coil:Heating:Steam",
                                            "",
                                            "",
                                            "Coil:Heating:WaterToAirHeatPump:ParameterEstimation",
                                            "",
                                            "Coil:Heating:WaterToAirHeatPump:EquationFit",
                                            "",
                                            "Coil:Heating:DX:VariableRefrigerantFlow",
                                            "",
                                            "",
                                            "",
                                            "Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit",
                                            "",
                                            "Coil:Heating:DX:VariableSpeed",
                                            "Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed",
                                            "",
                                            "Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl"});

    // Water to air HP coil types
    thread_local int const WatertoAir_Simple(1);
    thread_local int const WatertoAir_ParEst(2);
    thread_local int const WatertoAir_VarSpeedEquationFit(3);
    thread_local int const WatertoAir_VarSpeedLooUpTable(4);

    // Water to Air HP Water Flow Mode
    thread_local int const WaterCycling(1);  // water flow cycles with compressor
    thread_local int const WaterConstant(2); // water flow is constant
    thread_local int const
        WaterConstantOnDemand(3); // water flow is constant whenever the coil is operational - this is the only method used in EP V7.2 and earlier

    // parameters describing coil performance types
    thread_local int const CoilPerfDX_CoolBypassEmpirical(100);

    // Airflow per total capacity range (Regular DX coils)
    thread_local Real64 const MaxRatedVolFlowPerRatedTotCap1(0.00006041); // m3/s per watt = 450 cfm/ton
    thread_local Real64 const MinRatedVolFlowPerRatedTotCap1(0.00004027); // m3/s per watt = 300 cfm/ton
    thread_local Real64 const MaxHeatVolFlowPerRatedTotCap1(0.00008056);  // m3/s per watt = 600 cfm/ton
    thread_local Real64 const MaxCoolVolFlowPerRatedTotCap1(0.00006713);  // m3/s per watt = 500 cfm/ton
    thread_local Real64 const MinOperVolFlowPerRatedTotCap1(0.00002684);  // m3/s per watt = 200 cfm/ton

    // 100% DOAS DX coils Airflow per total capacity ratio
    thread_local Real64 const MaxRatedVolFlowPerRatedTotCap2(0.00003355); // m3/s per watt = 250 cfm/ton
    thread_local Real64 const MinRatedVolFlowPerRatedTotCap2(0.00001677); // m3/s per watt = 125 cfm/ton
    thread_local Real64 const MaxHeatVolFlowPerRatedTotCap2(0.00004026);  // m3/s per watt = 300 cfm/ton
    thread_local Real64 const MaxCoolVolFlowPerRatedTotCap2(0.00004026);  // m3/s per watt = 300 cfm/ton
    thread_local Real64 const MinOperVolFlowPerRatedTotCap2(0.00001342);  // m3/s per watt = 100 cfm/ton

    thread_local Array1D<Real64> MaxRatedVolFlowPerRatedTotCap(2, {MaxRatedVolFlowPerRatedTotCap1, MaxRatedVolFlowPerRatedTotCap2});
    thread_local Array1D<Real64> MinRatedVolFlowPerRatedTotCap(2, {MinRatedVolFlowPerRatedTotCap1, MinRatedVolFlowPerRatedTotCap2});
    thread_local Array1D<Real64> MaxHeatVolFlowPerRatedTotCap(2, {MaxHeatVolFlowPerRatedTotCap1, MaxHeatVolFlowPerRatedTotCap2});
    thread_local Array1D<Real64> MaxCoolVolFlowPerRatedTotCap(2, {MaxCoolVolFlowPerRatedTotCap1, MaxCoolVolFlowPerRatedTotCap2});
    thread_local Array1D<Real64> MinOperVolFlowPerRatedTotCap(2, {MinOperVolFlowPerRatedTotCap1, MinOperVolFlowPerRatedTotCap2});

    // dx coil type (DXCT)
    thread_local int const RegularDXCoil(1); // Regular DX coils or mixed air dx coils
    thread_local int const DOASDXCoil(2);    // 100% DOAS DX coils
    thread_local int DXCT(1);                // dx coil type: regular DX coil ==1, 100% DOAS DX coil = 2

    // Parameters describing Heat Exchanger types
    thread_local int const NumHXTypes(3);

    thread_local int const HX_AIRTOAIR_FLATPLATE(1);
    thread_local int const HX_AIRTOAIR_GENERIC(2);
    thread_local int const HX_DESICCANT_BALANCED(3);

    thread_local Array1D_string const
        cHXTypes(NumHXTypes,
                 {"HeatExchanger:AirToAir:FlatPlate", "HeatExchanger:AirToAir:SensibleAndLatent", "HeatExchanger:Desiccant:BalancedFlow"});

    // Parameters describing air terminal mixers
    thread_local int const NumATMixerTypes(2);

    thread_local int const No_ATMixer(0);
    thread_local int const ATMixer_InletSide(1);
    thread_local int const ATMixer_SupplySide(2);

    thread_local Array1D_string const cATMixerTypes(NumATMixerTypes, {"AirTerminal:SingleDuct:InletSideMixer", "AirTerminal:SingleDuct:SupplySideMixer"});
    thread_local bool const ATMixerExists(true);

    // Parameters describing variable refrigerant flow terminal unit types
    thread_local int const NumVRFTUTypes(1);

    thread_local int const VRFTUType_ConstVolume(1);

    thread_local Array1D_string const cVRFTUTypes(NumVRFTUTypes, std::string("ZoneHVAC:TerminalUnit:VariableRefrigerantFlow"));

    // VRF Heating Performance Curve Temperature Type
    thread_local int const NumVRFHeatingPerformanceOATTypes(2);
    thread_local int const WetBulbIndicator(1);
    thread_local int const DryBulbIndicator(2);

    thread_local Array1D_string const cVRFHeatingPerformanceOATTypes(NumVRFHeatingPerformanceOATTypes, {"WetBulbTemperature", "DryBulbTemperature"});

    // parameter concerning the amount of change in zone temperature is needed
    // for oscillation of zone temperature to be detected.
    thread_local Real64 const OscillateMagnitude(0.15);

    // Parameters for HVACSystemRootFindingAlgorithm
    thread_local int const Bisection(2);

    // DERIVED TYPE DEFINITIONS

    // INTERFACE BLOCK SPECIFICATIONS

    // MODULE VARIABLE DECLARATIONS:

    thread_local bool FirstTimeStepSysFlag(false); // Set to true at the start of each sub-time step

    thread_local Real64 TimeStepSys(0.0);                  // System Time Increment - the adaptive time step used by the HVAC simulation (hours)
    thread_local Real64 SysTimeElapsed(0.0);               // elapsed system time in zone timestep (hours)
    thread_local Real64 FracTimeStepZone(0.0);             // System time step divided by the zone time step
    thread_local bool ShortenTimeStepSys(false);           // Logical flag that triggers shortening of system time step
    thread_local int NumOfSysTimeSteps(1);                 // for current zone time step, number of system timesteps inside  it
    thread_local int NumOfSysTimeStepsLastZoneTimeStep(1); // previous zone time step, num of system timesteps inside
    thread_local int LimitNumSysSteps(0);

    thread_local bool UseZoneTimeStepHistory(true);    // triggers use of zone time step history, else system time step history, for ZTM1, ZTMx
    thread_local int NumPlantLoops(0);                 // Number of plant loops specified in simulation
    thread_local int NumCondLoops(0);                  // Number of condenser plant loops specified in simulation
    thread_local int NumElecCircuits(0);               // Number of electric circuits specified in simulation
    thread_local int NumGasMeters(0);                  // Number of gas meters specified in simulation
    thread_local int NumPrimaryAirSys(0);              // Number of primary HVAC air systems
    thread_local Real64 OnOffFanPartLoadFraction(1.0); // fan part-load fraction (Fan:OnOff)
    thread_local Real64 DXCoilTotalCapacity(0.0);      // DX coil total cooling capacity (eio report var for HPWHs)
    thread_local Real64 DXElecCoolingPower(0.0);       // Electric power consumed by DX cooling coil last DX simulation
    thread_local Real64 DXElecHeatingPower(0.0);       // Electric power consumed by DX heating coil last DX simulation
    thread_local Real64 ElecHeatingCoilPower(0.0);     // Electric power consumed by electric heating coil
    thread_local Real64 AirToAirHXElecPower(0.0);      // Electric power consumed by Heat Exchanger:Air To Air (Generic or Flat Plate)
    // from last simulation in HeatRecovery.cc
    thread_local Real64 UnbalExhMassFlow(0.0);      // unbalanced zone exhaust from a zone equip component [kg/s]
    thread_local Real64 BalancedExhMassFlow(0.0);   // balanced zone exhaust (declared as so by user)  [kg/s]
    thread_local Real64 PlenumInducedMassFlow(0.0); // secondary air mass flow rate induced from a return plenum [kg/s]
    thread_local bool TurnFansOn(false);            // If true overrides fan schedule and cycles fans on
    thread_local bool TurnZoneFansOnlyOn(false); // If true overrides zone fan schedule and cycles fans on (currently used only by parallel powered induction unit)
    thread_local bool TurnFansOff(false);        // If True overides fan schedule and TurnFansOn and forces fans off
    thread_local bool ZoneCompTurnFansOn(false); // If true overrides fan schedule and cycles fans on
    thread_local bool ZoneCompTurnFansOff(false); // If True overides fan schedule and TurnFansOn and forces fans off
    thread_local bool SetPointErrorFlag(false);   // True if any needed setpoints not set; if true, program terminates
    thread_local bool DoSetPointTest(false);      // True one time only for sensed node setpoint test
    thread_local bool NightVentOn(false);         // set TRUE in SimAirServingZone if night ventilation is happening

    thread_local int NumTempContComps(0);
    thread_local Real64 HPWHInletDBTemp(0.0);     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    thread_local Real64 HPWHInletWBTemp(0.0);     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    thread_local Real64 HPWHCrankcaseDBTemp(0.0); // Used for HEAT PUMP:WATER HEATER crankcase heater ambient temperature calculations
    thread_local bool AirLoopInit(false);         // flag for whether InitAirLoops has been called
    thread_local bool AirLoopsSimOnce(false);     // True means that the air loops have been simulated once in this environment
    thread_local bool GetAirPathDataDone(false);  // True means that air loops inputs have been processed

    // Hybrid ventilation control part
    thread_local int NumHybridVentSysAvailMgrs(0);               // Number of hybrid ventilation control
    thread_local Array1D_int HybridVentSysAvailAirLoopNum;       // Airloop number in hybrid vent availability manager
    thread_local Array1D_int HybridVentSysAvailVentCtrl;         // Ventilation control action in hybrid vent availability manager
    thread_local Array1D_int HybridVentSysAvailActualZoneNum;    // Actual zone num in hybrid vent availability manager
    thread_local Array1D_int HybridVentSysAvailANCtrlStatus;     // AN control status in hybrid vent availability manager
    thread_local Array1D_int HybridVentSysAvailMaster;           // Master object name: Ventilation for simple; Zone name for AN
    thread_local Array1D<Real64> HybridVentSysAvailWindModifier; // Wind modifier for AirflowNetwork
    // For multispeed heat pump only
    thread_local Real64 MSHPMassFlowRateLow(0.0);       // Mass flow rate at low speed
    thread_local Real64 MSHPMassFlowRateHigh(0.0);      // Mass flow rate at high speed
    thread_local Real64 MSHPWasteHeat(0.0);             // Waste heat
    thread_local Real64 PreviousTimeStep(0.0);          // The time step length at the previous time step
    thread_local bool ShortenTimeStepSysRoomAir(false); // Logical flag that triggers shortening of system time step

    thread_local Real64 deviationFromSetPtThresholdHtg(-0.2); // heating threshold for reporting setpoint deviation
    thread_local Real64 deviationFromSetPtThresholdClg(0.2);  // cooling threshold for reporting setpoint deviation

    thread_local bool SimAirLoopsFlag;          // True when the air loops need to be (re)simulated
    thread_local bool SimElecCircuitsFlag;      // True when electic circuits need to be (re)simulated
    thread_local bool SimPlantLoopsFlag;        // True when the main plant loops need to be (re)simulated
    thread_local bool SimZoneEquipmentFlag;     // True when zone equipment components need to be (re)simulated
    thread_local bool SimNonZoneEquipmentFlag;  // True when non-zone equipment components need to be (re)simulated
    thread_local bool ZoneMassBalanceHVACReSim; // True when zone air mass flow balance and air loop needs (re)simulated
    thread_local int MinAirLoopIterationsAfterFirst(
        1); // minimum number of HVAC iterations after FirstHVACIteration (must be at least 2 for sequenced loads to operate on air loops)

    thread_local int const NumZoneHVACTerminalTypes(38);

    thread_local Array1D_string const ZoneHVACTerminalTypes(NumZoneHVACTerminalTypes,
                                               {"ZONEHVAC:TERMINALUNIT:VARIABLEREFRIGERANTFLOW",
                                                "ZONEHVAC:ENERGYRECOVERYVENTILATOR",
                                                "ZONEHVAC:FOURPIPEFANCOIL",
                                                "ZONEHVAC:OUTDOORAIRUNIT",
                                                "ZONEHVAC:PACKAGEDTERMINALAIRCONDITIONER",
                                                "ZONEHVAC:PACKAGEDTERMINALHEATPUMP",
                                                "ZONEHVAC:UNITHEATER",
                                                "ZONEHVAC:UNITVENTILATOR",
                                                "ZONEHVAC:VENTILATEDSLAB",
                                                "ZONEHVAC:WATERTOAIRHEATPUMP",
                                                "ZONEHVAC:WINDOWAIRCONDITIONER",
                                                "ZONEHVAC:BASEBOARD:RADIANTCONVECTIVE:ELECTRIC",
                                                "ZONEHVAC:BASEBOARD:RADIANTCONVECTIVE:WATER",
                                                "ZONEHVAC:BASEBOARD:RADIANTCONVECTIVE:STEAM",
                                                "ZONEHVAC:BASEBOARD:CONVECTIVE:ELECTRIC",
                                                "ZONEHVAC:BASEBOARD:CONVECTIVE:WATER",
                                                "ZONEHVAC:HIGHTEMPERATURERADIANT",
                                                "ZONEHVAC:DEHUMIDIFIER:DX",
                                                "ZONEHVAC:IDEALLOADSAIRSYSTEM",
                                                "ZONEHVAC:REFRIGERATIONCHILLERSET",
                                                "FAN:ZONEEXHAUST",
                                                "WATERHEATER:HEATPUMP",
                                                "AIRTERMINAL:SINGLEDUCT:UNCONTROLLED",
                                                "AIRTERMINAL:DUALDUCT:CONSTANTVOLUME",
                                                "AIRTERMINAL:DUALDUCT:VAV",
                                                "AIRTERMINAL:SINGLEDUCT:CONSTANTVOLUME:REHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:CONSTANTVOLUME:NOREHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:VAV:REHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:VAV:NOREHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:SERIESPIU:REHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:PARALLELPIU:REHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:CONSTANTVOLUME:FOURPIPEINDUCTION",
                                                "AIRTERMINAL:SINGLEDUCT:VAV:REHEAT:VARIABLESPEEDFAN",
                                                "AIRTERMINAL:SINGLEDUCT:VAV:HEATANDCOOL:REHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:VAV:HEATANDCOOL:NOREHEAT",
                                                "AIRTERMINAL:SINGLEDUCT:CONSTANTVOLUME:COOLEDBEAM",
                                                "AIRTERMINAL:DUALDUCT:VAV:OUTDOORAIR",
                                                "AIRLOOPHVACRETURNAIR"});

    thread_local Array1D_string const ccZoneHVACTerminalTypes(NumZoneHVACTerminalTypes,
                                                 {"ZoneHVAC:TerminalUnit:VariableRefrigerantFlow",
                                                  "ZoneHVAC:EnergyRecoveryVentilator",
                                                  "ZoneHVAC:FourPipeFanCoil",
                                                  "ZoneHVAC:OutdoorAirUnit",
                                                  "ZoneHVAC:PackagedTerminalAirConditioner",
                                                  "ZoneHVAC:PackagedTerminalHeatPump",
                                                  "ZoneHVAC:UnitHeater",
                                                  "ZoneHVAC:UnitVentilator",
                                                  "ZoneHVAC:VentilatedSlab",
                                                  "ZoneHVAC:WaterToAirHeatPump",
                                                  "ZoneHVAC:WindowAirConditioner",
                                                  "ZoneHVAC:Baseboard:RadiantConvective:Electric",
                                                  "ZoneHVAC:Baseboard:RadiantConvective:Water",
                                                  "ZoneHVAC:Baseboard:RadiantConvective:Steam",
                                                  "ZoneHVAC:Baseboard:Convective:Electric",
                                                  "ZoneHVAC:Baseboard:Convective:Water",
                                                  "ZoneHVAC:HighTemperatureRadiant",
                                                  "ZoneHVAC:Dehumidifier:DX",
                                                  "ZoneHVAC:IdealLoadsAirSystem",
                                                  "ZoneHVAC:RefrigerationChillerSet",
                                                  "Fan:ZoneExhaust",
                                                  "WaterHeater:HeatPump",
                                                  "AirTerminal:SingleDuct:Uncontrolled",
                                                  "AirTerminal:DualDuct:ConstantVolume",
                                                  "AirTerminal:DualDuct:VAV",
                                                  "AirTerminal:SingleDuct:ConstantVolume:Reheat",
                                                  "AirTerminal:SingleDuct:ConstantVolume:NoReheat",
                                                  "AirTerminal:SingleDuct:VAV:Reheat",
                                                  "AirTerminal:SingleDuct:VAV:NoReheat",
                                                  "AirTerminal:SingleDuct:SeriesPIU:Reheat",
                                                  "AirTerminal:SingleDuct:ParallelPIU:Reheat",
                                                  "AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction",
                                                  "AirTerminal:SingleDuct:VAV:Reheat:VariableSpeedFan",
                                                  "AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat",
                                                  "AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat",
                                                  "AirTerminal:SingleDuct:ConstantVolume:CooledBeam",
                                                  "AirTerminal:DualDuct:VAV:OutdoorAir",
                                                  "AirLoopHVACReturnAir"});

    thread_local int const ZoneEquipTypeOf_VariableRefrigerantFlow(1);
    thread_local int const ZoneEquipTypeOf_EnergyRecoveryVentilator(2);
    thread_local int const ZoneEquipTypeOf_FourPipeFanCoil(3);
    thread_local int const ZoneEquipTypeOf_OutdoorAirUnit(4);
    thread_local int const ZoneEquipTypeOf_PackagedTerminalAirConditioner(5);
    thread_local int const ZoneEquipTypeOf_PackagedTerminalHeatPump(6);
    thread_local int const ZoneEquipTypeOf_UnitHeater(7);
    thread_local int const ZoneEquipTypeOf_UnitVentilator(8);
    thread_local int const ZoneEquipTypeOf_VentilatedSlab(9);
    thread_local int const ZoneEquipTypeOf_WaterToAirHeatPump(10);
    thread_local int const ZoneEquipTypeOf_WindowAirConditioner(11);
    thread_local int const ZoneEquipTypeOf_BaseboardRadiantConvectiveElectric(12);
    thread_local int const ZoneEquipTypeOf_BaseboardRadiantConvectiveWater(13);
    thread_local int const ZoneEquipTypeOf_BaseboardRadiantConvectiveSteam(14);
    thread_local int const ZoneEquipTypeOf_BaseboardConvectiveElectric(15);
    thread_local int const ZoneEquipTypeOf_BaseboardConvectiveWater(16);
    thread_local int const ZoneEquipTypeOf_HighTemperatureRadiant(17);
    thread_local int const ZoneEquipTypeOf_DehumidifierDX(18);
    thread_local int const ZoneEquipTypeOf_IdealLoadsAirSystem(19);
    thread_local int const ZoneEquipTypeOf_RefrigerationChillerSet(20);
    thread_local int const ZoneEquipTypeOf_FanZoneExhaust(21);
    thread_local int const ZoneEquipTypeOf_WaterHeaterHeatPump(22);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctUncontrolled(23);
    thread_local int const ZoneEquipTypeOf_AirTerminalDualDuctConstantVolume(24);
    thread_local int const ZoneEquipTypeOf_AirTerminalDualDuctVAV(25);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeReheat(26);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeNoReheat(27);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheat(28);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVNoReheat(29);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctSeriesPIUReheat(30);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctParallelPIUReheat(31);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctCAVFourPipeInduction(32);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheatVariableSpeedFan(33);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolReheat(34);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolNoReheat(35);
    thread_local int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeCooledBeam(36);
    thread_local int const ZoneEquipTypeOf_AirTerminalDualDuctVAVOutdoorAir(37);
    thread_local int const ZoneEquipTypeOf_AirLoopHVACReturnAir(38);

    // Object Data
    thread_local Array1D<ZoneCompTypeData> ZoneComp;
    thread_local OptStartDataType OptStartData; // For optimum start
    thread_local Array1D<ComponentSetPtData> CompSetPtEquip;
    thread_local HVACSystemRootFindingAlgorithm HVACSystemRootFinding;

    // Clears the global data in DataHVACGlobals.
    // Needed for unit tests, should not be normally called.
    void clear_state()
    {
        DXCT = 1;
        FirstTimeStepSysFlag = false;
        TimeStepSys = 0.0;
        SysTimeElapsed = 0.0;
        FracTimeStepZone = 0.0;
        ShortenTimeStepSys = false;
        NumOfSysTimeSteps = 1;
        NumOfSysTimeStepsLastZoneTimeStep = 1;
        LimitNumSysSteps = 0;
        UseZoneTimeStepHistory = true;
        NumPlantLoops = 0;
        NumCondLoops = 0;
        NumElecCircuits = 0;
        NumGasMeters = 0;
        NumPrimaryAirSys = 0;
        OnOffFanPartLoadFraction = 1.0;
        DXCoilTotalCapacity = 0.0;
        DXElecCoolingPower = 0.0;
        DXElecHeatingPower = 0.0;
        ElecHeatingCoilPower = 0.0;
        AirToAirHXElecPower = 0.0;
        UnbalExhMassFlow = 0.0;
        BalancedExhMassFlow = 0.0;
        PlenumInducedMassFlow = 0.0;
        TurnFansOn = false;
        TurnZoneFansOnlyOn = false;
        TurnFansOff = false;
        ZoneCompTurnFansOn = false;
        ZoneCompTurnFansOff = false;
        SetPointErrorFlag = false;
        DoSetPointTest = false;
        NightVentOn = false;
        NumTempContComps = 0;
        HPWHInletDBTemp = 0.0;
        HPWHInletWBTemp = 0.0;
        HPWHCrankcaseDBTemp = 0.0;
        AirLoopInit = false;
        AirLoopsSimOnce = false;
        GetAirPathDataDone = false;
        NumHybridVentSysAvailMgrs = 0;
        HybridVentSysAvailAirLoopNum.deallocate();
        HybridVentSysAvailVentCtrl.deallocate();
        HybridVentSysAvailActualZoneNum.deallocate();
        HybridVentSysAvailANCtrlStatus.deallocate();
        HybridVentSysAvailMaster.deallocate();
        HybridVentSysAvailWindModifier.deallocate();
        MSHPMassFlowRateLow = 0.0;
        MSHPMassFlowRateHigh = 0.0;
        MSHPWasteHeat = 0.0;
        PreviousTimeStep = 0.0;
        ShortenTimeStepSysRoomAir = false;
        deviationFromSetPtThresholdHtg = -0.2;
        deviationFromSetPtThresholdClg = 0.2;
        SimAirLoopsFlag = true;
        SimElecCircuitsFlag = true;
        SimPlantLoopsFlag = true;
        SimZoneEquipmentFlag = true;
        SimNonZoneEquipmentFlag = true;
        ZoneMassBalanceHVACReSim = true;
        MinAirLoopIterationsAfterFirst = 1;
        ZoneComp.deallocate();
        CompSetPtEquip.deallocate();
        OptStartData = OptStartDataType();
        // unit test ZoneTempPredictorCorrector_ReportingTest fails without this next line. Next 2 lines are just to be thorough.
        OptStartData.OptStartFlag.deallocate();
        OptStartData.ActualZoneNum.deallocate();
        OptStartData.OccStartTime.deallocate();
    }

} // namespace DataHVACGlobals

} // namespace EnergyPlus
