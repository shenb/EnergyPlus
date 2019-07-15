// EnergyPlus, Copyright (c) 1996-2019, The Board of Trustees of the University of Illinois,
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

    EP_GLOBAL Real64 const SmallTempDiff(1.0E-5);
    EP_GLOBAL Real64 const SmallMassFlow(0.001);
    EP_GLOBAL Real64 const VerySmallMassFlow(1.0E-30);
    EP_GLOBAL Real64 const SmallLoad(1.0);
    EP_GLOBAL Real64 const TempControlTol(0.1); // temperature control tolerance for packaged equip. [deg C]
    EP_GLOBAL Real64 const SmallAirVolFlow(0.001);
    EP_GLOBAL Real64 const SmallWaterVolFlow(1.0E-9);
    EP_GLOBAL Real64 const BlankNumeric(-99999.0);      // indicates numeric input field was blank
    EP_GLOBAL Real64 const RetTempMax(60.0);            // maximum return air temperature [deg C]
    EP_GLOBAL Real64 const RetTempMin(-30.0);           // minimum return air temperature [deg C]
    EP_GLOBAL Real64 const DesCoilHWInletTempMin(46.0); // minimum heating water coil water inlet temp for UA sizing only. [deg C]

    // Number of Sizing types from list below
    EP_GLOBAL int const NumOfSizingTypes(33); // number of sizing types

    // Sizing types
    EP_GLOBAL int const CoolingAirflowSizing(1);                               // request sizing for cooling air flow rate
    EP_GLOBAL int const CoolingWaterflowSizing(2);                             // request sizing for cooling water flow rate
    EP_GLOBAL int const HeatingWaterflowSizing(3);                             // request sizing for heating coil water flow rate
    EP_GLOBAL int const CoolingWaterDesAirInletTempSizing(4);                  // request sizing for cooling water coil inlet air temp
    EP_GLOBAL int const CoolingWaterDesAirInletHumRatSizing(5);                // request sizing for cooling water coil inlet air humidity ratio
    EP_GLOBAL int const CoolingWaterDesWaterInletTempSizing(6);                // request sizing for cooling water coil inlet water temp
    EP_GLOBAL int const CoolingWaterDesAirOutletTempSizing(7);                 // request sizing for cooling water coil outlet air temp
    EP_GLOBAL int const CoolingWaterDesAirOutletHumRatSizing(8);               // request sizing for cooling water coil outlet air humidity ratio
    EP_GLOBAL int const CoolingWaterNumofTubesPerRowSizing(9);                 // request sizing for cooling water coil number of tubes per row
    EP_GLOBAL int const HeatingWaterDesAirInletTempSizing(10);                 // request sizing for heating water coil inlet air temp
    EP_GLOBAL int const HeatingWaterDesAirInletHumRatSizing(11);               // request sizing for heating water coil inlet air humidity ratio
    EP_GLOBAL int const HeatingWaterDesCoilLoadUsedForUASizing(12);            // request sizing for heating water coil capacity used for UA sizing
    EP_GLOBAL int const HeatingWaterDesCoilWaterVolFlowUsedForUASizing(13);    // request sizing for heating water coil volume flow rate used for UA sizing
    EP_GLOBAL int const HeatingAirflowSizing(14);                              // request sizing for heating air flow rate
    EP_GLOBAL int const HeatingAirflowUASizing(15);                            // request sizing for heating air flow rate
    EP_GLOBAL int const SystemAirflowSizing(16);                               // request sizing for system air flow rate
    EP_GLOBAL int const CoolingCapacitySizing(17);                             // request sizing for cooling capacity
    EP_GLOBAL int const HeatingCapacitySizing(18);                             // request sizing for heating capacity
    EP_GLOBAL int const WaterHeatingCapacitySizing(19);                        // request sizing for water-side heating capacity
    EP_GLOBAL int const WaterHeatingCoilUASizing(20);                          // request sizing for heating coil UA
    EP_GLOBAL int const SystemCapacitySizing(21);                              // request sizing for system capacity
    EP_GLOBAL int const CoolingSHRSizing(22);                                  // request sizing for cooling SHR
    EP_GLOBAL int const HeatingDefrostSizing(23);                              // request sizing for heating defrost capacity
    EP_GLOBAL int const MaxHeaterOutletTempSizing(24);                         // request sizing for heating coil maximum outlet temperature
    EP_GLOBAL int const AutoCalculateSizing(25);                               // identifies an autocalulate input
    EP_GLOBAL int const ZoneCoolingLoadSizing(26);                             // zone cooling sensible load (zsz file)
    EP_GLOBAL int const ZoneHeatingLoadSizing(27);                             // zome heating sensible load (zsz file)
    EP_GLOBAL int const MinSATempCoolingSizing(28);                            // minimum SA temperature in cooling
    EP_GLOBAL int const MaxSATempHeatingSizing(29);                            // maximum SA temperature in heating
    EP_GLOBAL int const ASHRAEMinSATCoolingSizing(30);                         // minimum SA temperature in cooling model when using ASHRAE 90.1 SZVAV method
    EP_GLOBAL int const ASHRAEMaxSATHeatingSizing(31);                         // maximum SA temperature in heating model when using ASHRAE 90.1 SZVAV method
    EP_GLOBAL int const HeatingCoilDesAirInletTempSizing(32);                  // design inlet air temperature for heating coil
    EP_GLOBAL int const HeatingCoilDesAirOutletTempSizing(33);                 // design outlet air temperature for heating coil
    EP_GLOBAL int const HeatingCoilDesAirInletHumRatSizing(34);                // design inlet air humidity ratio for heating coil
    EP_GLOBAL int const DesiccantDehumidifierBFPerfDataFaceVelocitySizing(35); // identifies desiccant performance data face velocity autosisizing input

    // Condenser Type (using same numbering scheme as for chillers)
    EP_GLOBAL int const AirCooled(1);   // Air-cooled condenser
    EP_GLOBAL int const WaterCooled(2); // Water-cooled condenser
    EP_GLOBAL int const EvapCooled(3);  // Evaporatively-cooled condenser
    EP_GLOBAL int const WaterHeater(4); // Condenser heats water (e.g., in water heater tank)

    // The following parameters are used for system availability status
    EP_GLOBAL int const NoAction(0);
    EP_GLOBAL int const ForceOff(1);
    EP_GLOBAL int const CycleOn(2);
    EP_GLOBAL int const CycleOnZoneFansOnly(3);
    // The following parameters describe the setpoint types in TempControlType(ActualZoneNum)
    EP_GLOBAL int const SingleHeatingSetPoint(1);
    EP_GLOBAL int const SingleCoolingSetPoint(2);
    EP_GLOBAL int const SingleHeatCoolSetPoint(3);
    EP_GLOBAL int const DualSetPointWithDeadBand(4);
    // parameters describing air duct type
    EP_GLOBAL int const Main(1);
    EP_GLOBAL int const Cooling(2);
    EP_GLOBAL int const Heating(3);
    EP_GLOBAL int const Other(4);
    EP_GLOBAL int const RAB(5);
    // parameters describing fan types
    EP_GLOBAL int const NumAllFanTypes(6); // cpw22Aug2010 (was 4)

    // fan types
    EP_GLOBAL int const FanType_SimpleConstVolume(1);
    EP_GLOBAL int const FanType_SimpleVAV(2);
    EP_GLOBAL int const FanType_SimpleOnOff(3);
    EP_GLOBAL int const FanType_ZoneExhaust(4);
    EP_GLOBAL int const FanType_ComponentModel(5);    // cpw22Aug2010
    EP_GLOBAL int const FanType_SystemModelObject(6); // new for V8.7, simple versatile fan object

    // Fan Minimum Flow Fraction Input Method
    EP_GLOBAL int const MinFrac(1);
    EP_GLOBAL int const FixedMin(2);
    // Fan mode
    EP_GLOBAL int const CycFanCycCoil(1);  // Cycling fan, cycling coil = 1
    EP_GLOBAL int const ContFanCycCoil(2); // Continuous fan, cycling coil = 2
    // Fan placement
    EP_GLOBAL int const BlowThru(1); // fan before coil
    EP_GLOBAL int const DrawThru(2); // fan after coil
    // OA Controller Heat Recovery Bypass Control Types
    EP_GLOBAL int const BypassWhenWithinEconomizerLimits(0);   // heat recovery controlled by economizer limits
    EP_GLOBAL int const BypassWhenOAFlowGreaterThanMinimum(1); // heat recovery ON at minimum OA in economizer mode

    EP_GLOBAL Array1D_string const
        cFanTypes(NumAllFanTypes,
                  {"Fan:ConstantVolume", "Fan:VariableVolume", "Fan:OnOff", "Fan:ZoneExhaust", "Fan:ComponentModel", "Fan:SystemModel"});

    // parameters describing unitary systems
    EP_GLOBAL int const NumUnitarySystemTypes(7);
    // Furnace/Unitary System Types
    EP_GLOBAL int const Furnace_HeatOnly(1);
    EP_GLOBAL int const Furnace_HeatCool(2);
    EP_GLOBAL int const UnitarySys_HeatOnly(3);
    EP_GLOBAL int const UnitarySys_HeatCool(4);
    EP_GLOBAL int const UnitarySys_HeatPump_AirToAir(5);
    EP_GLOBAL int const UnitarySys_HeatPump_WaterToAir(6);
    EP_GLOBAL int const UnitarySys_AnyCoilType(7);
    EP_GLOBAL Array1D_string const cFurnaceTypes(NumUnitarySystemTypes,
                                       {"AirLoopHVAC:Unitary:Furnace:HeatOnly",
                                        "AirLoopHVAC:Unitary:Furnace:HeatCool",
                                        "AirLoopHVAC:UnitaryHeatOnly",
                                        "AirLoopHVAC:UnitaryHeatCool",
                                        "AirLoopHVAC:UnitaryHeatPump:AirToAir",
                                        "AirLoopHVAC:UnitaryHeatPump:WaterToAir",
                                        "AirLoopHVAC:UnitarySystem"});

    // parameters describing coil types
    EP_GLOBAL int const NumAllCoilTypes(34);

    EP_GLOBAL int const CoilDX_CoolingSingleSpeed(1);
    EP_GLOBAL int const CoilDX_HeatingEmpirical(2);
    EP_GLOBAL int const CoilDX_CoolingTwoSpeed(3);
    EP_GLOBAL int const CoilDX_CoolingHXAssisted(4);
    EP_GLOBAL int const CoilDX_CoolingTwoStageWHumControl(5);
    EP_GLOBAL int const CoilDX_HeatPumpWaterHeaterPumped(6);
    EP_GLOBAL int const CoilDX_HeatPumpWaterHeaterWrapped(7);
    EP_GLOBAL int const CoilDX_MultiSpeedCooling(8);
    EP_GLOBAL int const CoilDX_MultiSpeedHeating(9);

    EP_GLOBAL int const Coil_HeatingGasOrOtherFuel(10);
    EP_GLOBAL int const Coil_HeatingGas_MultiStage(11);
    EP_GLOBAL int const Coil_HeatingElectric(12);
    EP_GLOBAL int const Coil_HeatingElectric_MultiStage(13);
    EP_GLOBAL int const Coil_HeatingDesuperheater(14);

    EP_GLOBAL int const Coil_CoolingWater(15);
    EP_GLOBAL int const Coil_CoolingWaterDetailed(16);
    EP_GLOBAL int const Coil_HeatingWater(17);
    EP_GLOBAL int const Coil_HeatingSteam(18);
    EP_GLOBAL int const CoilWater_CoolingHXAssisted(19);

    EP_GLOBAL int const Coil_CoolingWaterToAirHP(20);
    EP_GLOBAL int const Coil_HeatingWaterToAirHP(21);
    EP_GLOBAL int const Coil_CoolingWaterToAirHPSimple(22);
    EP_GLOBAL int const Coil_HeatingWaterToAirHPSimple(23);
    EP_GLOBAL int const CoilVRF_Cooling(24);
    EP_GLOBAL int const CoilVRF_Heating(25);

    EP_GLOBAL int const Coil_UserDefined(26);
    EP_GLOBAL int const CoilDX_PackagedThermalStorageCooling(27);

    EP_GLOBAL int const Coil_CoolingWaterToAirHPVSEquationFit(28);
    EP_GLOBAL int const Coil_HeatingWaterToAirHPVSEquationFit(29);
    EP_GLOBAL int const Coil_CoolingAirToAirVariableSpeed(30);
    EP_GLOBAL int const Coil_HeatingAirToAirVariableSpeed(31);
    EP_GLOBAL int const CoilDX_HeatPumpWaterHeaterVariableSpeed(32);

    EP_GLOBAL int const CoilVRF_FluidTCtrl_Cooling(33);
    EP_GLOBAL int const CoilVRF_FluidTCtrl_Heating(34);

    EP_GLOBAL Array1D_string const cAllCoilTypes(NumAllCoilTypes,
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

    EP_GLOBAL Array1D_string const cCoolingCoilTypes(NumAllCoilTypes,
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

    EP_GLOBAL Array1D_string const cHeatingCoilTypes(NumAllCoilTypes,
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
    EP_GLOBAL int const WatertoAir_Simple(1);
    EP_GLOBAL int const WatertoAir_ParEst(2);
    EP_GLOBAL int const WatertoAir_VarSpeedEquationFit(3);
    EP_GLOBAL int const WatertoAir_VarSpeedLooUpTable(4);

    // Water to Air HP Water Flow Mode
    EP_GLOBAL int const WaterCycling(1);  // water flow cycles with compressor
    EP_GLOBAL int const WaterConstant(2); // water flow is constant
    EP_GLOBAL int const
        WaterConstantOnDemand(3); // water flow is constant whenever the coil is operational - this is the only method used in EP V7.2 and earlier

    // parameters describing coil performance types
    EP_GLOBAL int const CoilPerfDX_CoolBypassEmpirical(100);

    // Airflow per total capacity range (Regular DX coils)
    EP_GLOBAL Real64 const MaxRatedVolFlowPerRatedTotCap1(0.00006041); // m3/s per watt = 450 cfm/ton
    EP_GLOBAL Real64 const MinRatedVolFlowPerRatedTotCap1(0.00004027); // m3/s per watt = 300 cfm/ton
    EP_GLOBAL Real64 const MaxHeatVolFlowPerRatedTotCap1(0.00008056);  // m3/s per watt = 600 cfm/ton
    EP_GLOBAL Real64 const MaxCoolVolFlowPerRatedTotCap1(0.00006713);  // m3/s per watt = 500 cfm/ton
    EP_GLOBAL Real64 const MinOperVolFlowPerRatedTotCap1(0.00002684);  // m3/s per watt = 200 cfm/ton

    // 100% DOAS DX coils Airflow per total capacity ratio
    EP_GLOBAL Real64 const MaxRatedVolFlowPerRatedTotCap2(0.00003355); // m3/s per watt = 250 cfm/ton
    EP_GLOBAL Real64 const MinRatedVolFlowPerRatedTotCap2(0.00001677); // m3/s per watt = 125 cfm/ton
    EP_GLOBAL Real64 const MaxHeatVolFlowPerRatedTotCap2(0.00004026);  // m3/s per watt = 300 cfm/ton
    EP_GLOBAL Real64 const MaxCoolVolFlowPerRatedTotCap2(0.00004026);  // m3/s per watt = 300 cfm/ton
    EP_GLOBAL Real64 const MinOperVolFlowPerRatedTotCap2(0.00001342);  // m3/s per watt = 100 cfm/ton

    EP_GLOBAL Array1D<Real64> MaxRatedVolFlowPerRatedTotCap(2, {MaxRatedVolFlowPerRatedTotCap1, MaxRatedVolFlowPerRatedTotCap2});
    EP_GLOBAL Array1D<Real64> MinRatedVolFlowPerRatedTotCap(2, {MinRatedVolFlowPerRatedTotCap1, MinRatedVolFlowPerRatedTotCap2});
    EP_GLOBAL Array1D<Real64> MaxHeatVolFlowPerRatedTotCap(2, {MaxHeatVolFlowPerRatedTotCap1, MaxHeatVolFlowPerRatedTotCap2});
    EP_GLOBAL Array1D<Real64> MaxCoolVolFlowPerRatedTotCap(2, {MaxCoolVolFlowPerRatedTotCap1, MaxCoolVolFlowPerRatedTotCap2});
    EP_GLOBAL Array1D<Real64> MinOperVolFlowPerRatedTotCap(2, {MinOperVolFlowPerRatedTotCap1, MinOperVolFlowPerRatedTotCap2});

    // dx coil type (DXCT)
    EP_GLOBAL int const RegularDXCoil(1); // Regular DX coils or mixed air dx coils
    EP_GLOBAL int const DOASDXCoil(2);    // 100% DOAS DX coils
    EP_GLOBAL int DXCT(1);                // dx coil type: regular DX coil ==1, 100% DOAS DX coil = 2

    // Parameters describing Heat Exchanger types
    EP_GLOBAL int const NumHXTypes(3);

    EP_GLOBAL int const HX_AIRTOAIR_FLATPLATE(1);
    EP_GLOBAL int const HX_AIRTOAIR_GENERIC(2);
    EP_GLOBAL int const HX_DESICCANT_BALANCED(3);

    EP_GLOBAL Array1D_string const
        cHXTypes(NumHXTypes,
                 {"HeatExchanger:AirToAir:FlatPlate", "HeatExchanger:AirToAir:SensibleAndLatent", "HeatExchanger:Desiccant:BalancedFlow"});

    // Parameters describing air terminal mixers
    EP_GLOBAL int const NumATMixerTypes(2);

    EP_GLOBAL int const No_ATMixer(0);
    EP_GLOBAL int const ATMixer_InletSide(1);
    EP_GLOBAL int const ATMixer_SupplySide(2);

    EP_GLOBAL Array1D_string const cATMixerTypes(NumATMixerTypes, {"AirTerminal:SingleDuct:InletSideMixer", "AirTerminal:SingleDuct:SupplySideMixer"});
    EP_GLOBAL bool const ATMixerExists(true);

    // Parameters describing variable refrigerant flow terminal unit types
    EP_GLOBAL int const NumVRFTUTypes(1);

    EP_GLOBAL int const VRFTUType_ConstVolume(1);

    EP_GLOBAL Array1D_string const cVRFTUTypes(NumVRFTUTypes, std::string("ZoneHVAC:TerminalUnit:VariableRefrigerantFlow"));

    // VRF Heating Performance Curve Temperature Type
    EP_GLOBAL int const NumVRFHeatingPerformanceOATTypes(2);
    EP_GLOBAL int const WetBulbIndicator(1);
    EP_GLOBAL int const DryBulbIndicator(2);

    EP_GLOBAL Array1D_string const cVRFHeatingPerformanceOATTypes(NumVRFHeatingPerformanceOATTypes, {"WetBulbTemperature", "DryBulbTemperature"});

    // parameter concerning the amount of change in zone temperature is needed
    // for oscillation of zone temperature to be detected.
    EP_GLOBAL Real64 const OscillateMagnitude(0.15);

    // Parameters for HVACSystemRootFindingAlgorithm
    EP_GLOBAL int const Bisection(2);

    // DERIVED TYPE DEFINITIONS

    // INTERFACE BLOCK SPECIFICATIONS

    // MODULE VARIABLE DECLARATIONS:

    EP_GLOBAL bool FirstTimeStepSysFlag(false); // Set to true at the start of each sub-time step

    EP_GLOBAL Real64 TimeStepSys(0.0);                  // System Time Increment - the adaptive time step used by the HVAC simulation (hours)
    EP_GLOBAL Real64 SysTimeElapsed(0.0);               // elapsed system time in zone timestep (hours)
    EP_GLOBAL Real64 FracTimeStepZone(0.0);             // System time step divided by the zone time step
    EP_GLOBAL bool ShortenTimeStepSys(false);           // Logical flag that triggers shortening of system time step
    EP_GLOBAL int NumOfSysTimeSteps(1);                 // for current zone time step, number of system timesteps inside  it
    EP_GLOBAL int NumOfSysTimeStepsLastZoneTimeStep(1); // previous zone time step, num of system timesteps inside
    EP_GLOBAL int LimitNumSysSteps(0);

    EP_GLOBAL bool UseZoneTimeStepHistory(true);    // triggers use of zone time step history, else system time step history, for ZTM1, ZTMx
    EP_GLOBAL int NumPlantLoops(0);                 // Number of plant loops specified in simulation
    EP_GLOBAL int NumCondLoops(0);                  // Number of condenser plant loops specified in simulation
    EP_GLOBAL int NumElecCircuits(0);               // Number of electric circuits specified in simulation
    EP_GLOBAL int NumGasMeters(0);                  // Number of gas meters specified in simulation
    EP_GLOBAL int NumPrimaryAirSys(0);              // Number of primary HVAC air systems
    EP_GLOBAL Real64 OnOffFanPartLoadFraction(1.0); // fan part-load fraction (Fan:OnOff)
    EP_GLOBAL Real64 DXCoilTotalCapacity(0.0);      // DX coil total cooling capacity (eio report var for HPWHs)
    EP_GLOBAL Real64 DXElecCoolingPower(0.0);       // Electric power consumed by DX cooling coil last DX simulation
    EP_GLOBAL Real64 DXElecHeatingPower(0.0);       // Electric power consumed by DX heating coil last DX simulation
    EP_GLOBAL Real64 ElecHeatingCoilPower(0.0);     // Electric power consumed by electric heating coil
    EP_GLOBAL Real64 AirToAirHXElecPower(0.0);      // Electric power consumed by Heat Exchanger:Air To Air (Generic or Flat Plate)
    // from last simulation in HeatRecovery.cc
    EP_GLOBAL Real64 UnbalExhMassFlow(0.0);      // unbalanced zone exhaust from a zone equip component [kg/s]
    EP_GLOBAL Real64 BalancedExhMassFlow(0.0);   // balanced zone exhaust (declared as so by user)  [kg/s]
    EP_GLOBAL Real64 PlenumInducedMassFlow(0.0); // secondary air mass flow rate induced from a return plenum [kg/s]
    EP_GLOBAL bool TurnFansOn(false);            // If true overrides fan schedule and cycles fans on
    EP_GLOBAL bool TurnZoneFansOnlyOn(false); // If true overrides zone fan schedule and cycles fans on (currently used only by parallel powered induction unit)
    EP_GLOBAL bool TurnFansOff(false);        // If True overides fan schedule and TurnFansOn and forces fans off
    EP_GLOBAL bool ZoneCompTurnFansOn(false); // If true overrides fan schedule and cycles fans on
    EP_GLOBAL bool ZoneCompTurnFansOff(false); // If True overides fan schedule and TurnFansOn and forces fans off
    EP_GLOBAL bool SetPointErrorFlag(false);   // True if any needed setpoints not set; if true, program terminates
    EP_GLOBAL bool DoSetPointTest(false);      // True one time only for sensed node setpoint test
    EP_GLOBAL bool NightVentOn(false);         // set TRUE in SimAirServingZone if night ventilation is happening

    EP_GLOBAL int NumTempContComps(0);
    EP_GLOBAL Real64 HPWHInletDBTemp(0.0);     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    EP_GLOBAL Real64 HPWHInletWBTemp(0.0);     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    EP_GLOBAL Real64 HPWHCrankcaseDBTemp(0.0); // Used for HEAT PUMP:WATER HEATER crankcase heater ambient temperature calculations
    EP_GLOBAL bool AirLoopInit(false);         // flag for whether InitAirLoops has been called
    EP_GLOBAL bool AirLoopsSimOnce(false);     // True means that the air loops have been simulated once in this environment
    EP_GLOBAL bool GetAirPathDataDone(false);  // True means that air loops inputs have been processed

    // Hybrid ventilation control part
    EP_GLOBAL int NumHybridVentSysAvailMgrs(0);               // Number of hybrid ventilation control
    EP_GLOBAL Array1D_int HybridVentSysAvailAirLoopNum;       // Airloop number in hybrid vent availability manager
    EP_GLOBAL Array1D_int HybridVentSysAvailVentCtrl;         // Ventilation control action in hybrid vent availability manager
    EP_GLOBAL Array1D_int HybridVentSysAvailActualZoneNum;    // Actual zone num in hybrid vent availability manager
    EP_GLOBAL Array1D_int HybridVentSysAvailANCtrlStatus;     // AN control status in hybrid vent availability manager
    EP_GLOBAL Array1D_int HybridVentSysAvailMaster;           // Master object name: Ventilation for simple; Zone name for AN
    EP_GLOBAL Array1D<Real64> HybridVentSysAvailWindModifier; // Wind modifier for AirflowNetwork
    // For multispeed heat pump only
    EP_GLOBAL Real64 MSHPMassFlowRateLow(0.0);       // Mass flow rate at low speed
    EP_GLOBAL Real64 MSHPMassFlowRateHigh(0.0);      // Mass flow rate at high speed
    EP_GLOBAL Real64 MSHPWasteHeat(0.0);             // Waste heat
    EP_GLOBAL Real64 PreviousTimeStep(0.0);          // The time step length at the previous time step
    EP_GLOBAL bool ShortenTimeStepSysRoomAir(false); // Logical flag that triggers shortening of system time step

    EP_GLOBAL Real64 deviationFromSetPtThresholdHtg(-0.2); // heating threshold for reporting setpoint deviation
    EP_GLOBAL Real64 deviationFromSetPtThresholdClg(0.2);  // cooling threshold for reporting setpoint deviation

    EP_GLOBAL bool SimAirLoopsFlag;          // True when the air loops need to be (re)simulated
    EP_GLOBAL bool SimElecCircuitsFlag;      // True when electic circuits need to be (re)simulated
    EP_GLOBAL bool SimPlantLoopsFlag;        // True when the main plant loops need to be (re)simulated
    EP_GLOBAL bool SimZoneEquipmentFlag;     // True when zone equipment components need to be (re)simulated
    EP_GLOBAL bool SimNonZoneEquipmentFlag;  // True when non-zone equipment components need to be (re)simulated
    EP_GLOBAL bool ZoneMassBalanceHVACReSim; // True when zone air mass flow balance and air loop needs (re)simulated
    EP_GLOBAL int MinAirLoopIterationsAfterFirst(1); // minimum number of HVAC iterations after FirstHVACIteration

    EP_GLOBAL int const NumZoneHVACTerminalTypes(38);

    EP_GLOBAL Array1D_string const ZoneHVACTerminalTypes(NumZoneHVACTerminalTypes,
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

    EP_GLOBAL Array1D_string const ccZoneHVACTerminalTypes(NumZoneHVACTerminalTypes,
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

    EP_GLOBAL int const ZoneEquipTypeOf_VariableRefrigerantFlow(1);
    EP_GLOBAL int const ZoneEquipTypeOf_EnergyRecoveryVentilator(2);
    EP_GLOBAL int const ZoneEquipTypeOf_FourPipeFanCoil(3);
    EP_GLOBAL int const ZoneEquipTypeOf_OutdoorAirUnit(4);
    EP_GLOBAL int const ZoneEquipTypeOf_PackagedTerminalAirConditioner(5);
    EP_GLOBAL int const ZoneEquipTypeOf_PackagedTerminalHeatPump(6);
    EP_GLOBAL int const ZoneEquipTypeOf_UnitHeater(7);
    EP_GLOBAL int const ZoneEquipTypeOf_UnitVentilator(8);
    EP_GLOBAL int const ZoneEquipTypeOf_VentilatedSlab(9);
    EP_GLOBAL int const ZoneEquipTypeOf_WaterToAirHeatPump(10);
    EP_GLOBAL int const ZoneEquipTypeOf_WindowAirConditioner(11);
    EP_GLOBAL int const ZoneEquipTypeOf_BaseboardRadiantConvectiveElectric(12);
    EP_GLOBAL int const ZoneEquipTypeOf_BaseboardRadiantConvectiveWater(13);
    EP_GLOBAL int const ZoneEquipTypeOf_BaseboardRadiantConvectiveSteam(14);
    EP_GLOBAL int const ZoneEquipTypeOf_BaseboardConvectiveElectric(15);
    EP_GLOBAL int const ZoneEquipTypeOf_BaseboardConvectiveWater(16);
    EP_GLOBAL int const ZoneEquipTypeOf_HighTemperatureRadiant(17);
    EP_GLOBAL int const ZoneEquipTypeOf_DehumidifierDX(18);
    EP_GLOBAL int const ZoneEquipTypeOf_IdealLoadsAirSystem(19);
    EP_GLOBAL int const ZoneEquipTypeOf_RefrigerationChillerSet(20);
    EP_GLOBAL int const ZoneEquipTypeOf_FanZoneExhaust(21);
    EP_GLOBAL int const ZoneEquipTypeOf_WaterHeaterHeatPump(22);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctUncontrolled(23);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalDualDuctConstantVolume(24);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalDualDuctVAV(25);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeReheat(26);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeNoReheat(27);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheat(28);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVNoReheat(29);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctSeriesPIUReheat(30);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctParallelPIUReheat(31);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctCAVFourPipeInduction(32);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheatVariableSpeedFan(33);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolReheat(34);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolNoReheat(35);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeCooledBeam(36);
    EP_GLOBAL int const ZoneEquipTypeOf_AirTerminalDualDuctVAVOutdoorAir(37);
    EP_GLOBAL int const ZoneEquipTypeOf_AirLoopHVACReturnAir(38);

    // Object Data
    EP_GLOBAL Array1D<ZoneCompTypeData> ZoneComp;
    EP_GLOBAL OptStartDataType OptStartData; // For optimum start
    EP_GLOBAL Array1D<ComponentSetPtData> CompSetPtEquip;
    EP_GLOBAL HVACSystemRootFindingAlgorithm HVACSystemRootFinding;

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
