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

#ifndef DataHVACGlobals_hh_INCLUDED
#define DataHVACGlobals_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>

// EnergyPlus Headers
#include <DataGlobals.hh>
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace DataHVACGlobals {

    // Using/Aliasing

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.
    enum class HVACSystemRootSolverAlgorithm : int
    {
        RegulaFalsi = 0,
        Bisection,
        RegulaFalsiThenBisection,
        BisectionThenRegulaFalsi,
        Alternation
    };

    // MODULE PARAMETER DEFINITIONS:

    EP_GLOBAL extern Real64 const SmallTempDiff;
    EP_GLOBAL extern Real64 const SmallMassFlow;
    EP_GLOBAL extern Real64 const VerySmallMassFlow;
    EP_GLOBAL extern Real64 const SmallLoad;
    EP_GLOBAL extern Real64 const TempControlTol; // temperature control tolerance for packaged equip. [deg C]
    EP_GLOBAL extern Real64 const SmallAirVolFlow;
    EP_GLOBAL extern Real64 const SmallWaterVolFlow;
    EP_GLOBAL extern Real64 const BlankNumeric;          // indicates numeric input field was blank
    EP_GLOBAL extern Real64 const RetTempMax;            // maximum return air temperature [deg C]
    EP_GLOBAL extern Real64 const RetTempMin;            // minimum return air temperature [deg C]
    EP_GLOBAL extern Real64 const DesCoilHWInletTempMin; // minimum heating water coil water inlet temp for UA sizing only. [deg C]

    EP_GLOBAL extern int const NumOfSizingTypes; // request sizing for cooling air flow rate

    EP_GLOBAL extern int const CoolingAirflowSizing;                              // request sizing for cooling air flow rate
    EP_GLOBAL extern int const CoolingWaterflowSizing;                            // request sizing for cooling coil water flow rate
    EP_GLOBAL extern int const HeatingWaterflowSizing;                            // request sizing for heating coil water flow rate
    EP_GLOBAL extern int const CoolingWaterDesAirInletTempSizing;                 // request sizing for cooling water coil inlet air temp
    EP_GLOBAL extern int const CoolingWaterDesAirInletHumRatSizing;               // request sizing for cooling water coil inlet air humidity ratio
    EP_GLOBAL extern int const CoolingWaterDesWaterInletTempSizing;               // request sizing for cooling water coil inlet water temp
    EP_GLOBAL extern int const CoolingWaterDesAirOutletTempSizing;                // request sizing for cooling water coil outlet air temp
    EP_GLOBAL extern int const CoolingWaterDesAirOutletHumRatSizing;              // request sizing for cooling water coil outlet air humidity ratio
    EP_GLOBAL extern int const CoolingWaterNumofTubesPerRowSizing;                // request sizing for cooling water coil number of tubes per row
    EP_GLOBAL extern int const HeatingWaterDesAirInletTempSizing;                 // request sizing for heating water coil inlet air temp
    EP_GLOBAL extern int const HeatingWaterDesAirInletHumRatSizing;               // request sizing for heating water coil inlet air humidity ratio
    EP_GLOBAL extern int const HeatingWaterDesCoilLoadUsedForUASizing;            // request sizing for heating water coil capacity used for UA sizing
    EP_GLOBAL extern int const HeatingWaterDesCoilWaterVolFlowUsedForUASizing;    // request sizing for heating water coil volume flow rate used for UA sizing
    EP_GLOBAL extern int const HeatingAirflowSizing;                              // request sizing for heating air flow rate
    EP_GLOBAL extern int const HeatingAirflowUASizing;                            // request sizing for heating air flow rate
    EP_GLOBAL extern int const SystemAirflowSizing;                               // request sizing for system air flow rate
    EP_GLOBAL extern int const CoolingCapacitySizing;                             // request sizing for cooling capacity
    EP_GLOBAL extern int const HeatingCapacitySizing;                             // request sizing for heating capacity
    EP_GLOBAL extern int const WaterHeatingCapacitySizing;                        // request sizing for heating capacity
    EP_GLOBAL extern int const WaterHeatingCoilUASizing;                          // request sizing for heating coil UA
    EP_GLOBAL extern int const SystemCapacitySizing;                              // request sizing for system capacity
    EP_GLOBAL extern int const CoolingSHRSizing;                                  // request sizing for cooling SHR
    EP_GLOBAL extern int const HeatingDefrostSizing;                              // request sizing for heating defrost capacity
    EP_GLOBAL extern int const MaxHeaterOutletTempSizing;                         // request sizing for heating coil maximum outlet temperature
    EP_GLOBAL extern int const AutoCalculateSizing;                               // identifies an autocalulate input
    EP_GLOBAL extern int const ZoneCoolingLoadSizing;                             // zone cooling sensible load (zsz file)
    EP_GLOBAL extern int const ZoneHeatingLoadSizing;                             // zome heating sensible load (zsz file)
    EP_GLOBAL extern int const MinSATempCoolingSizing;                            // minimum SA temperature in cooling
    EP_GLOBAL extern int const MaxSATempHeatingSizing;                            // maximum SA temperature in heating
    EP_GLOBAL extern int const ASHRAEMinSATCoolingSizing;                         // minimum SA temperature in cooling model when using ASHRAE 90.1 SZVAV method
    EP_GLOBAL extern int const ASHRAEMaxSATHeatingSizing;                         // maximum SA temperature in heating model when using ASHRAE 90.1 SZVAV method
    EP_GLOBAL extern int const HeatingCoilDesAirInletTempSizing;                  // design inlet air temperature for heating coil
    EP_GLOBAL extern int const HeatingCoilDesAirOutletTempSizing;                 // design outlet air temperature for heating coil
    EP_GLOBAL extern int const HeatingCoilDesAirInletHumRatSizing;                // design inlet air humidity ratio for heating coil
    EP_GLOBAL extern int const DesiccantDehumidifierBFPerfDataFaceVelocitySizing; // identifies desiccant performance data face velocity autosisizing input

    // Condenser Type (using same numbering scheme as for chillers)
    EP_GLOBAL extern int const AirCooled;   // Air-cooled condenser
    EP_GLOBAL extern int const WaterCooled; // Water-cooled condenser
    EP_GLOBAL extern int const EvapCooled;  // Evaporatively-cooled condenser
    EP_GLOBAL extern int const WaterHeater; // Condenser heats water (e.g., in water heater tank)

    // The following parameters are used for system availability status
    EP_GLOBAL extern int const NoAction;
    EP_GLOBAL extern int const ForceOff;
    EP_GLOBAL extern int const CycleOn;
    EP_GLOBAL extern int const CycleOnZoneFansOnly;
    // The following parameters describe the setpoint types in TempControlType(ActualZoneNum)
    EP_GLOBAL extern int const SingleHeatingSetPoint;
    EP_GLOBAL extern int const SingleCoolingSetPoint;
    EP_GLOBAL extern int const SingleHeatCoolSetPoint;
    EP_GLOBAL extern int const DualSetPointWithDeadBand;
    // parameters describing air duct type
    EP_GLOBAL extern int const Main;
    EP_GLOBAL extern int const Cooling;
    EP_GLOBAL extern int const Heating;
    EP_GLOBAL extern int const Other;
    EP_GLOBAL extern int const RAB;
    // parameters describing fan types
    EP_GLOBAL extern int const NumAllFanTypes; // cpw22Aug2010 (was 4)

    // fan types
    EP_GLOBAL extern int const FanType_SimpleConstVolume;
    EP_GLOBAL extern int const FanType_SimpleVAV;
    EP_GLOBAL extern int const FanType_SimpleOnOff;
    EP_GLOBAL extern int const FanType_ZoneExhaust;
    EP_GLOBAL extern int const FanType_ComponentModel;    // cpw22Aug2010 (new)
    EP_GLOBAL extern int const FanType_SystemModelObject; //

    // Fan Minimum Flow Fraction Input Method
    EP_GLOBAL extern int const MinFrac;
    EP_GLOBAL extern int const FixedMin;
    // Fan mode
    EP_GLOBAL extern int const CycFanCycCoil;  // Cycling fan, cycling coil = 1
    EP_GLOBAL extern int const ContFanCycCoil; // Continuous fan, cycling coil = 2
    // Fan placement
    EP_GLOBAL extern int const BlowThru; // fan before coil
    EP_GLOBAL extern int const DrawThru; // fan after coil
    // OA Controller Heat Recovery Bypass Control Types
    EP_GLOBAL extern int const BypassWhenWithinEconomizerLimits;   // heat recovery controlled by economizer limits
    EP_GLOBAL extern int const BypassWhenOAFlowGreaterThanMinimum; // heat recovery ON at minimum OA in economizer mode

    EP_GLOBAL extern Array1D_string const cFanTypes; // cpw22Aug2010 | cpw22Aug2010 (new)

    // parameters describing unitary systems
    EP_GLOBAL extern int const NumUnitarySystemTypes;
    // Furnace/Unitary System Types
    EP_GLOBAL extern int const Furnace_HeatOnly;
    EP_GLOBAL extern int const Furnace_HeatCool;
    EP_GLOBAL extern int const UnitarySys_HeatOnly;
    EP_GLOBAL extern int const UnitarySys_HeatCool;
    EP_GLOBAL extern int const UnitarySys_HeatPump_AirToAir;
    EP_GLOBAL extern int const UnitarySys_HeatPump_WaterToAir;
    EP_GLOBAL extern int const UnitarySys_AnyCoilType;
    EP_GLOBAL extern Array1D_string const cFurnaceTypes;

    // parameters describing coil types
    EP_GLOBAL extern int const NumAllCoilTypes;

    EP_GLOBAL extern int const CoilDX_CoolingSingleSpeed;
    EP_GLOBAL extern int const CoilDX_HeatingEmpirical;
    EP_GLOBAL extern int const CoilDX_CoolingTwoSpeed;
    EP_GLOBAL extern int const CoilDX_CoolingHXAssisted;
    EP_GLOBAL extern int const CoilDX_CoolingTwoStageWHumControl;
    EP_GLOBAL extern int const CoilDX_HeatPumpWaterHeaterPumped;
    EP_GLOBAL extern int const CoilDX_HeatPumpWaterHeaterWrapped;
    EP_GLOBAL extern int const CoilDX_MultiSpeedCooling;
    EP_GLOBAL extern int const CoilDX_MultiSpeedHeating;

    EP_GLOBAL extern int const Coil_HeatingGasOrOtherFuel;
    EP_GLOBAL extern int const Coil_HeatingGas_MultiStage;
    EP_GLOBAL extern int const Coil_HeatingElectric;
    EP_GLOBAL extern int const Coil_HeatingElectric_MultiStage;
    EP_GLOBAL extern int const Coil_HeatingDesuperheater;

    EP_GLOBAL extern int const Coil_CoolingWater;
    EP_GLOBAL extern int const Coil_CoolingWaterDetailed;
    EP_GLOBAL extern int const Coil_HeatingWater;
    EP_GLOBAL extern int const Coil_HeatingSteam;
    EP_GLOBAL extern int const CoilWater_CoolingHXAssisted;

    EP_GLOBAL extern int const Coil_CoolingWaterToAirHP;
    EP_GLOBAL extern int const Coil_HeatingWaterToAirHP;
    EP_GLOBAL extern int const Coil_CoolingWaterToAirHPSimple;
    EP_GLOBAL extern int const Coil_HeatingWaterToAirHPSimple;
    EP_GLOBAL extern int const CoilVRF_Cooling;
    EP_GLOBAL extern int const CoilVRF_Heating;

    EP_GLOBAL extern int const Coil_UserDefined;
    EP_GLOBAL extern int const CoilDX_PackagedThermalStorageCooling;

    EP_GLOBAL extern int const Coil_CoolingWaterToAirHPVSEquationFit;
    EP_GLOBAL extern int const Coil_HeatingWaterToAirHPVSEquationFit;
    EP_GLOBAL extern int const Coil_CoolingAirToAirVariableSpeed;
    EP_GLOBAL extern int const Coil_HeatingAirToAirVariableSpeed;
    EP_GLOBAL extern int const CoilDX_HeatPumpWaterHeaterVariableSpeed;

    EP_GLOBAL extern int const CoilVRF_FluidTCtrl_Cooling;
    EP_GLOBAL extern int const CoilVRF_FluidTCtrl_Heating;

    EP_GLOBAL extern Array1D_string const cAllCoilTypes;
    EP_GLOBAL extern Array1D_string const cCoolingCoilTypes;
    EP_GLOBAL extern Array1D_string const cHeatingCoilTypes;

    // Water to air HP coil types
    EP_GLOBAL extern int const WatertoAir_Simple;
    EP_GLOBAL extern int const WatertoAir_ParEst;
    EP_GLOBAL extern int const WatertoAir_VarSpeedEquationFit;
    EP_GLOBAL extern int const WatertoAir_VarSpeedLooUpTable;

    // Water to Air HP Water Flow Mode
    EP_GLOBAL extern int const WaterCycling;  // water flow cycles with compressor
    EP_GLOBAL extern int const WaterConstant; // water flow is constant
    EP_GLOBAL extern int const
        WaterConstantOnDemand; // water flow is constant whenever the coil is operational - this is the only method used in EP V7.2 and earlier

    // parameters describing coil performance types
    EP_GLOBAL extern int const CoilPerfDX_CoolBypassEmpirical;

    // Airflow per total capacity range (Regular DX coils)
    EP_GLOBAL extern Real64 const MaxRatedVolFlowPerRatedTotCap1; // m3/s per watt = 450 cfm/ton
    EP_GLOBAL extern Real64 const MinRatedVolFlowPerRatedTotCap1; // m3/s per watt = 300 cfm/ton
    EP_GLOBAL extern Real64 const MaxHeatVolFlowPerRatedTotCap1;  // m3/s per watt = 600 cfm/ton
    EP_GLOBAL extern Real64 const MaxCoolVolFlowPerRatedTotCap1;  // m3/s per watt = 500 cfm/ton
    EP_GLOBAL extern Real64 const MinOperVolFlowPerRatedTotCap1;  // m3/s per watt = 200 cfm/ton

    // 100% DOAS DX coils Airflow per total capacity ratio
    EP_GLOBAL extern Real64 const MaxRatedVolFlowPerRatedTotCap2; // m3/s per watt = 250 cfm/ton
    EP_GLOBAL extern Real64 const MinRatedVolFlowPerRatedTotCap2; // m3/s per watt = 125 cfm/ton
    EP_GLOBAL extern Real64 const MaxHeatVolFlowPerRatedTotCap2;  // m3/s per watt = 300 cfm/ton
    EP_GLOBAL extern Real64 const MaxCoolVolFlowPerRatedTotCap2;  // m3/s per watt = 300 cfm/ton
    EP_GLOBAL extern Real64 const MinOperVolFlowPerRatedTotCap2;  // m3/s per watt = 100 cfm/ton

    EP_GLOBAL extern Array1D<Real64> MaxRatedVolFlowPerRatedTotCap;
    EP_GLOBAL extern Array1D<Real64> MinRatedVolFlowPerRatedTotCap;
    EP_GLOBAL extern Array1D<Real64> MaxHeatVolFlowPerRatedTotCap;
    EP_GLOBAL extern Array1D<Real64> MaxCoolVolFlowPerRatedTotCap;
    EP_GLOBAL extern Array1D<Real64> MinOperVolFlowPerRatedTotCap;

    // dx coil type (DXCT)
    EP_GLOBAL extern int const RegularDXCoil; // Regular DX coils or mixed air dx coils
    EP_GLOBAL extern int const DOASDXCoil;    // 100% DOAS DX coils
    EP_GLOBAL extern int DXCT;                // dx coil type: regular DX coil ==1, 100% DOAS DX coil = 2

    // Parameters describing Heat Exchanger types
    EP_GLOBAL extern int const NumHXTypes;

    EP_GLOBAL extern int const HX_AIRTOAIR_FLATPLATE;
    EP_GLOBAL extern int const HX_AIRTOAIR_GENERIC;
    EP_GLOBAL extern int const HX_DESICCANT_BALANCED;

    EP_GLOBAL extern Array1D_string const cHXTypes;

    // Parameters describing air terminal mixers
    EP_GLOBAL extern int const NumATMixerTypes;

    EP_GLOBAL extern int const No_ATMixer;
    EP_GLOBAL extern int const ATMixer_InletSide;
    EP_GLOBAL extern int const ATMixer_SupplySide;

    EP_GLOBAL extern Array1D_string const cATMixerTypes;
    EP_GLOBAL extern bool const ATMixerExists;

    // Parameters describing variable refrigerant flow terminal unit types
    EP_GLOBAL extern int const NumVRFTUTypes;

    EP_GLOBAL extern int const VRFTUType_ConstVolume;

    EP_GLOBAL extern Array1D_string const cVRFTUTypes;

    // VRF Heating Performance Curve Temperature Type
    EP_GLOBAL extern int const NumVRFHeatingPerformanceOATTypes;
    EP_GLOBAL extern int const WetBulbIndicator;
    EP_GLOBAL extern int const DryBulbIndicator;

    EP_GLOBAL extern Array1D_string const cVRFHeatingPerformanceOATTypes;

    // parameter concerning the amount of change in zone temperature is needed
    // for oscillation of zone temperature to be detected.
    EP_GLOBAL extern Real64 const OscillateMagnitude;

    // Parameters for HVACSystemRootFindingAlgorithm
    EP_GLOBAL extern int const Bisection;
    // DERIVED TYPE DEFINITIONS

    // INTERFACE BLOCK SPECIFICATIONS

    // MODULE VARIABLE DECLARATIONS:

    EP_GLOBAL extern bool FirstTimeStepSysFlag; // Set to true at the start of each sub-time step

    EP_GLOBAL extern Real64 TimeStepSys;                    // System Time Increment - the adaptive time step used by the HVAC simulation (hours)
    EP_GLOBAL extern Real64 SysTimeElapsed;                 // elapsed system time in zone timestep (hours)
    EP_GLOBAL extern Real64 FracTimeStepZone;               // System time step divided by the zone time step
    EP_GLOBAL extern bool ShortenTimeStepSys;               // Logical flag that triggers shortening of system time step
    EP_GLOBAL extern int NumOfSysTimeSteps;                 // for current zone time step, number of system timesteps inside  it
    EP_GLOBAL extern int NumOfSysTimeStepsLastZoneTimeStep; // previous zone time step, num of system timesteps inside
    EP_GLOBAL extern int LimitNumSysSteps;

    EP_GLOBAL extern bool UseZoneTimeStepHistory;     // triggers use of zone time step history, else system time step history, for ZTM1, ZTMx
    EP_GLOBAL extern int NumPlantLoops;               // Number of plant loops specified in simulation
    EP_GLOBAL extern int NumCondLoops;                // Number of condenser plant loops specified in simulation
    EP_GLOBAL extern int NumElecCircuits;             // Number of electric circuits specified in simulation
    EP_GLOBAL extern int NumGasMeters;                // Number of gas meters specified in simulation
    EP_GLOBAL extern int NumPrimaryAirSys;            // Number of primary HVAC air systems
    EP_GLOBAL extern Real64 OnOffFanPartLoadFraction; // fan part-load fraction (Fan:OnOff)
    EP_GLOBAL extern Real64 DXCoilTotalCapacity;      // DX coil total cooling capacity (eio report var for HPWHs)
    EP_GLOBAL extern Real64 DXElecCoolingPower;       // Electric power consumed by DX cooling coil last DX simulation
    EP_GLOBAL extern Real64 DXElecHeatingPower;       // Electric power consumed by DX heating coil last DX simulation
    EP_GLOBAL extern Real64 ElecHeatingCoilPower;     // Electric power consumed by electric heating coil
    EP_GLOBAL extern Real64 AirToAirHXElecPower;      // Electric power consumed by Heat Exchanger:Air To Air (Generic or Flat Plate)
    // from last simulation in HeatRecovery.cc
    EP_GLOBAL extern Real64 UnbalExhMassFlow;      // unbalanced zone exhaust from a zone equip component [kg/s]
    EP_GLOBAL extern Real64 BalancedExhMassFlow;   // balanced zone exhaust (declared as so by user)  [kg/s]
    EP_GLOBAL extern Real64 PlenumInducedMassFlow; // secondary air mass flow rate induced from a return plenum [kg/s]
    EP_GLOBAL extern bool TurnFansOn;              // If true overrides fan schedule and cycles fans on
    EP_GLOBAL extern bool TurnZoneFansOnlyOn; // If true overrides zone fan schedule and cycles fans on (currently used only by parallel powered induction unit)
    EP_GLOBAL extern bool TurnFansOff;        // If True overides fan schedule and TurnFansOn and forces fans off
    EP_GLOBAL extern bool ZoneCompTurnFansOn; // If true overrides fan schedule and cycles fans on
    EP_GLOBAL extern bool ZoneCompTurnFansOff; // If True overides fan schedule and TurnFansOn and forces fans off
    EP_GLOBAL extern bool SetPointErrorFlag;   // True if any needed setpoints not set; if true, program terminates
    EP_GLOBAL extern bool DoSetPointTest;      // True one time only for sensed node setpoint test
    EP_GLOBAL extern bool NightVentOn;         // set TRUE in SimAirServingZone if night ventilation is happening

    EP_GLOBAL extern int NumTempContComps;
    EP_GLOBAL extern Real64 HPWHInletDBTemp;     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    EP_GLOBAL extern Real64 HPWHInletWBTemp;     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    EP_GLOBAL extern Real64 HPWHCrankcaseDBTemp; // Used for HEAT PUMP:WATER HEATER crankcase heater ambient temperature calculations
    EP_GLOBAL extern bool AirLoopInit;           // flag for whether InitAirLoops has been called
    EP_GLOBAL extern bool AirLoopsSimOnce;       // True means that the air loops have been simulated once in this environment
    EP_GLOBAL extern bool GetAirPathDataDone;    // True means that air loops inputs have been processed

    // Hybrid ventilation control part
    EP_GLOBAL extern int NumHybridVentSysAvailMgrs;                  // Number of hybrid ventilation control
    EP_GLOBAL extern Array1D_int HybridVentSysAvailAirLoopNum;       // Airloop number in hybrid vent availability manager
    EP_GLOBAL extern Array1D_int HybridVentSysAvailVentCtrl;         // Ventilation control action in hybrid vent availability manager
    EP_GLOBAL extern Array1D_int HybridVentSysAvailActualZoneNum;    // Actual zone num in hybrid vent availability manager
    EP_GLOBAL extern Array1D_int HybridVentSysAvailANCtrlStatus;     // AN control status in hybrid vent availability manager
    EP_GLOBAL extern Array1D_int HybridVentSysAvailMaster;           // Master object name: Ventilation for simple; Zone name for AN
    EP_GLOBAL extern Array1D<Real64> HybridVentSysAvailWindModifier; // Wind modifier for AirflowNetwork
    // For multispeed heat pump only
    EP_GLOBAL extern Real64 MSHPMassFlowRateLow;     // Mass flow rate at low speed
    EP_GLOBAL extern Real64 MSHPMassFlowRateHigh;    // Mass flow rate at high speed
    EP_GLOBAL extern Real64 MSHPWasteHeat;           // Waste heat
    EP_GLOBAL extern Real64 PreviousTimeStep;        // The time step length at the previous time step
    EP_GLOBAL extern bool ShortenTimeStepSysRoomAir; // Logical flag that triggers shortening of system time step

    EP_GLOBAL extern Real64 deviationFromSetPtThresholdHtg; // heating threshold for reporting setpoint deviation
    EP_GLOBAL extern Real64 deviationFromSetPtThresholdClg; // cooling threshold for reporting setpoint deviation

    EP_GLOBAL extern bool SimAirLoopsFlag;               // True when the air loops need to be (re)simulated
    EP_GLOBAL extern bool SimElecCircuitsFlag;           // True when electic circuits need to be (re)simulated
    EP_GLOBAL extern bool SimPlantLoopsFlag;             // True when the main plant loops need to be (re)simulated
    EP_GLOBAL extern bool SimZoneEquipmentFlag;          // True when zone equipment components need to be (re)simulated
    EP_GLOBAL extern bool SimNonZoneEquipmentFlag;       // True when non-zone equipment components need to be (re)simulated
    EP_GLOBAL extern bool ZoneMassBalanceHVACReSim;      // True when zone air mass flow balance and air loop needs (re)simulated
    EP_GLOBAL extern int MinAirLoopIterationsAfterFirst; // minimum number of HVAC iterations after FirstHVACIteration (must be at least 2 for sequenced loads
                                               // to operate on air loops)

    EP_GLOBAL extern int const NumZoneHVACTerminalTypes;
    EP_GLOBAL extern Array1D_string const ccZoneHVACTerminalTypes;
    EP_GLOBAL extern Array1D_string const ZoneHVACTerminalTypes;
    EP_GLOBAL extern int const ZoneEquipTypeOf_VariableRefrigerantFlow;
    EP_GLOBAL extern int const ZoneEquipTypeOf_EnergyRecoveryVentilator;
    EP_GLOBAL extern int const ZoneEquipTypeOf_FourPipeFanCoil;
    EP_GLOBAL extern int const ZoneEquipTypeOf_OutdoorAirUnit;
    EP_GLOBAL extern int const ZoneEquipTypeOf_PackagedTerminalAirConditioner;
    EP_GLOBAL extern int const ZoneEquipTypeOf_PackagedTerminalHeatPump;
    EP_GLOBAL extern int const ZoneEquipTypeOf_UnitHeater;
    EP_GLOBAL extern int const ZoneEquipTypeOf_UnitVentilator;
    EP_GLOBAL extern int const ZoneEquipTypeOf_VentilatedSlab;
    EP_GLOBAL extern int const ZoneEquipTypeOf_WaterToAirHeatPump;
    EP_GLOBAL extern int const ZoneEquipTypeOf_WindowAirConditioner;
    EP_GLOBAL extern int const ZoneEquipTypeOf_BaseboardRadiantConvectiveElectric;
    EP_GLOBAL extern int const ZoneEquipTypeOf_BaseboardRadiantConvectiveWater;
    EP_GLOBAL extern int const ZoneEquipTypeOf_BaseboardRadiantConvectiveSteam;
    EP_GLOBAL extern int const ZoneEquipTypeOf_BaseboardConvectiveElectric;
    EP_GLOBAL extern int const ZoneEquipTypeOf_BaseboardConvectiveWater;
    EP_GLOBAL extern int const ZoneEquipTypeOf_HighTemperatureRadiant;
    EP_GLOBAL extern int const ZoneEquipTypeOf_DehumidifierDX;
    EP_GLOBAL extern int const ZoneEquipTypeOf_IdealLoadsAirSystem;
    EP_GLOBAL extern int const ZoneEquipTypeOf_RefrigerationChillerSet;
    EP_GLOBAL extern int const ZoneEquipTypeOf_FanZoneExhaust;
    EP_GLOBAL extern int const ZoneEquipTypeOf_WaterHeaterHeatPump;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctUncontrolled;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalDualDuctConstantVolume;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalDualDuctVAV;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeNoReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVNoReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctSeriesPIUReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctParallelPIUReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctCAVFourPipeInduction;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheatVariableSpeedFan;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolNoReheat;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeCooledBeam;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirTerminalDualDuctVAVOutdoorAir;
    EP_GLOBAL extern int const ZoneEquipTypeOf_AirLoopHVACReturnAir;

    // Types

    struct ComponentSetPtData
    {
        // Members
        // CHARACTER(len=MaxNameLength) :: EquipOperListName
        std::string EquipmentType;
        std::string EquipmentName;
        int NodeNumIn;
        int NodeNumOut;
        Real64 EquipDemand;
        Real64 DesignFlowRate;
        std::string HeatOrCool;
        int OpType;

        // Default Constructor
        ComponentSetPtData() : NodeNumIn(0), NodeNumOut(0), EquipDemand(0.0), DesignFlowRate(0.0), OpType(0)
        {
        }
    };

    struct DefineZoneCompAvailMgrs
    {
        // Members
        int NumAvailManagers;             // number of availability managers for this system
        int AvailStatus;                  // system availability status
        int StartTime;                    // cycle on time (in SimTimeSteps)
        int StopTime;                     // cycle off time (in SimTimeSteps)
        std::string AvailManagerListName; // name of each availability manager
        Array1D_string AvailManagerName;  // name of each availability manager
        Array1D_int AvailManagerType;     // type of availability manager
        Array1D_int AvailManagerNum;      // index for availability manager
        int ZoneNum;                      // cycle off time (in SimTimeSteps)
        bool Input;                       // starts off as true to initialize zone equipment availability manager data
        int Count;                        // initialize twice to ensure zone equipment availability manager list name has been read in

        // Default Constructor
        DefineZoneCompAvailMgrs() : NumAvailManagers(0), AvailStatus(0), StartTime(0), StopTime(0), ZoneNum(0), Input(true), Count(0)
        {
        }
    };

    struct ZoneCompTypeData
    {
        // Members
        Array1D<DefineZoneCompAvailMgrs> ZoneCompAvailMgrs;
        int TotalNumComp; // total number of components of a zone equip type

        // Default Constructor
        ZoneCompTypeData() : TotalNumComp(0)
        {
        }
    };

    struct OptStartDataType
    {
        // Members
        Array1D_int ActualZoneNum;
        Array1D<Real64> OccStartTime;
        Array1D_bool OptStartFlag;

        // Default Constructor
        OptStartDataType()
        {
        }
    };

    struct HVACSystemRootFindingAlgorithm
    {
        // Members
        std::string Algorithm;                              // Choice of algorithm
        int NumOfIter;                                      // Number of Iteration Before Algorith Switch
        HVACSystemRootSolverAlgorithm HVACSystemRootSolver; // 1 RegulaFalsi; 2 Bisection; 3 BisectionThenRegulaFalsi; 4 RegulaFalsiThenBisection; 5
                                                            // Alternation Default Constructor
        HVACSystemRootFindingAlgorithm() : NumOfIter(5), HVACSystemRootSolver(HVACSystemRootSolverAlgorithm::RegulaFalsi)
        {
        }
    };

    // Object Data
    EP_GLOBAL extern Array1D<ZoneCompTypeData> ZoneComp;
    EP_GLOBAL extern OptStartDataType OptStartData; // For optimum start
    EP_GLOBAL extern Array1D<ComponentSetPtData> CompSetPtEquip;
    EP_GLOBAL extern HVACSystemRootFindingAlgorithm HVACSystemRootFinding;

    // Clears the global data in DataHVACGlobals.
    // Needed for unit tests, should not be normally called.
    void clear_state();

} // namespace DataHVACGlobals

} // namespace EnergyPlus

#endif
