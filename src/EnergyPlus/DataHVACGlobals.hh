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
    // extern EModelica EMO;

    thread_local extern Real64 const SmallTempDiff;
    thread_local extern Real64 const SmallMassFlow;
    thread_local extern Real64 const VerySmallMassFlow;
    thread_local extern Real64 const SmallLoad;
    thread_local extern Real64 const TempControlTol; // temperature control tolerance for packaged equip. [deg C]
    thread_local extern Real64 const SmallAirVolFlow;
    thread_local extern Real64 const SmallWaterVolFlow;
    thread_local extern Real64 const BlankNumeric;          // indicates numeric input field was blank
    thread_local extern Real64 const RetTempMax;            // maximum return air temperature [deg C]
    thread_local extern Real64 const RetTempMin;            // minimum return air temperature [deg C]
    thread_local extern Real64 const DesCoilHWInletTempMin; // minimum heating water coil water inlet temp for UA sizing only. [deg C]

    thread_local extern int const NumOfSizingTypes; // request sizing for cooling air flow rate

    thread_local extern int const CoolingAirflowSizing;                              // request sizing for cooling air flow rate
    thread_local extern int const CoolingWaterflowSizing;                            // request sizing for cooling coil water flow rate
    thread_local extern int const HeatingWaterflowSizing;                            // request sizing for heating coil water flow rate
    thread_local extern int const CoolingWaterDesAirInletTempSizing;                 // request sizing for cooling water coil inlet air temp
    thread_local extern int const CoolingWaterDesAirInletHumRatSizing;               // request sizing for cooling water coil inlet air humidity ratio
    thread_local extern int const CoolingWaterDesWaterInletTempSizing;               // request sizing for cooling water coil inlet water temp
    thread_local extern int const CoolingWaterDesAirOutletTempSizing;                // request sizing for cooling water coil outlet air temp
    thread_local extern int const CoolingWaterDesAirOutletHumRatSizing;              // request sizing for cooling water coil outlet air humidity ratio
    thread_local extern int const CoolingWaterNumofTubesPerRowSizing;                // request sizing for cooling water coil number of tubes per row
    thread_local extern int const HeatingWaterDesAirInletTempSizing;                 // request sizing for heating water coil inlet air temp
    thread_local extern int const HeatingWaterDesAirInletHumRatSizing;               // request sizing for heating water coil inlet air humidity ratio
    thread_local extern int const HeatingWaterDesCoilLoadUsedForUASizing;            // request sizing for heating water coil capacity used for UA sizing
    thread_local extern int const HeatingWaterDesCoilWaterVolFlowUsedForUASizing;    // request sizing for heating water coil volume flow rate used for UA sizing
    thread_local extern int const HeatingAirflowSizing;                              // request sizing for heating air flow rate
    thread_local extern int const HeatingAirflowUASizing;                            // request sizing for heating air flow rate
    thread_local extern int const SystemAirflowSizing;                               // request sizing for system air flow rate
    thread_local extern int const CoolingCapacitySizing;                             // request sizing for cooling capacity
    thread_local extern int const HeatingCapacitySizing;                             // request sizing for heating capacity
    thread_local extern int const WaterHeatingCapacitySizing;                        // request sizing for heating capacity
    thread_local extern int const WaterHeatingCoilUASizing;                          // request sizing for heating coil UA
    thread_local extern int const SystemCapacitySizing;                              // request sizing for system capacity
    thread_local extern int const CoolingSHRSizing;                                  // request sizing for cooling SHR
    thread_local extern int const HeatingDefrostSizing;                              // request sizing for heating defrost capacity
    thread_local extern int const MaxHeaterOutletTempSizing;                         // request sizing for heating coil maximum outlet temperature
    thread_local extern int const AutoCalculateSizing;                               // identifies an autocalulate input
    thread_local extern int const ZoneCoolingLoadSizing;                             // zone cooling sensible load (zsz file)
    thread_local extern int const ZoneHeatingLoadSizing;                             // zome heating sensible load (zsz file)
    thread_local extern int const MinSATempCoolingSizing;                            // minimum SA temperature in cooling
    thread_local extern int const MaxSATempHeatingSizing;                            // maximum SA temperature in heating
    thread_local extern int const ASHRAEMinSATCoolingSizing;                         // minimum SA temperature in cooling model when using ASHRAE 90.1 SZVAV method
    thread_local extern int const ASHRAEMaxSATHeatingSizing;                         // maximum SA temperature in heating model when using ASHRAE 90.1 SZVAV method
    thread_local extern int const HeatingCoilDesAirInletTempSizing;                  // design inlet air temperature for heating coil
    thread_local extern int const HeatingCoilDesAirOutletTempSizing;                 // design outlet air temperature for heating coil
    thread_local extern int const HeatingCoilDesAirInletHumRatSizing;                // design inlet air humidity ratio for heating coil
    thread_local extern int const DesiccantDehumidifierBFPerfDataFaceVelocitySizing; // identifies desiccant performance data face velocity autosisizing input

    // Condenser Type (using same numbering scheme as for chillers)
    thread_local extern int const AirCooled;   // Air-cooled condenser
    thread_local extern int const WaterCooled; // Water-cooled condenser
    thread_local extern int const EvapCooled;  // Evaporatively-cooled condenser
    thread_local extern int const WaterHeater; // Condenser heats water (e.g., in water heater tank)

    // The following parameters are used for system availability status
    thread_local extern int const NoAction;
    thread_local extern int const ForceOff;
    thread_local extern int const CycleOn;
    thread_local extern int const CycleOnZoneFansOnly;
    // The following parameters describe the setpoint types in TempControlType(ActualZoneNum)
    thread_local extern int const SingleHeatingSetPoint;
    thread_local extern int const SingleCoolingSetPoint;
    thread_local extern int const SingleHeatCoolSetPoint;
    thread_local extern int const DualSetPointWithDeadBand;
    // parameters describing air duct type
    thread_local extern int const Main;
    thread_local extern int const Cooling;
    thread_local extern int const Heating;
    thread_local extern int const Other;
    thread_local extern int const RAB;
    // parameters describing fan types
    thread_local extern int const NumAllFanTypes; // cpw22Aug2010 (was 4)

    // fan types
    thread_local extern int const FanType_SimpleConstVolume;
    thread_local extern int const FanType_SimpleVAV;
    thread_local extern int const FanType_SimpleOnOff;
    thread_local extern int const FanType_ZoneExhaust;
    thread_local extern int const FanType_ComponentModel;    // cpw22Aug2010 (new)
    thread_local extern int const FanType_SystemModelObject; //

    // Fan Minimum Flow Fraction Input Method
    thread_local extern int const MinFrac;
    thread_local extern int const FixedMin;
    // Fan mode
    thread_local extern int const CycFanCycCoil;  // Cycling fan, cycling coil = 1
    thread_local extern int const ContFanCycCoil; // Continuous fan, cycling coil = 2
    // Fan placement
    thread_local extern int const BlowThru; // fan before coil
    thread_local extern int const DrawThru; // fan after coil
    // OA Controller Heat Recovery Bypass Control Types
    thread_local extern int const BypassWhenWithinEconomizerLimits;   // heat recovery controlled by economizer limits
    thread_local extern int const BypassWhenOAFlowGreaterThanMinimum; // heat recovery ON at minimum OA in economizer mode

    thread_local extern Array1D_string const cFanTypes; // cpw22Aug2010 | cpw22Aug2010 (new)

    // parameters describing unitary systems
    thread_local extern int const NumUnitarySystemTypes;
    // Furnace/Unitary System Types
    thread_local extern int const Furnace_HeatOnly;
    thread_local extern int const Furnace_HeatCool;
    thread_local extern int const UnitarySys_HeatOnly;
    thread_local extern int const UnitarySys_HeatCool;
    thread_local extern int const UnitarySys_HeatPump_AirToAir;
    thread_local extern int const UnitarySys_HeatPump_WaterToAir;
    thread_local extern int const UnitarySys_AnyCoilType;
    thread_local extern Array1D_string const cFurnaceTypes;

    // parameters describing coil types
    thread_local extern int const NumAllCoilTypes;

    thread_local extern int const CoilDX_CoolingSingleSpeed;
    thread_local extern int const CoilDX_HeatingEmpirical;
    thread_local extern int const CoilDX_CoolingTwoSpeed;
    thread_local extern int const CoilDX_CoolingHXAssisted;
    thread_local extern int const CoilDX_CoolingTwoStageWHumControl;
    thread_local extern int const CoilDX_HeatPumpWaterHeaterPumped;
    thread_local extern int const CoilDX_HeatPumpWaterHeaterWrapped;
    thread_local extern int const CoilDX_MultiSpeedCooling;
    thread_local extern int const CoilDX_MultiSpeedHeating;

    thread_local extern int const Coil_HeatingGasOrOtherFuel;
    thread_local extern int const Coil_HeatingGas_MultiStage;
    thread_local extern int const Coil_HeatingElectric;
    thread_local extern int const Coil_HeatingElectric_MultiStage;
    thread_local extern int const Coil_HeatingDesuperheater;

    thread_local extern int const Coil_CoolingWater;
    thread_local extern int const Coil_CoolingWaterDetailed;
    thread_local extern int const Coil_HeatingWater;
    thread_local extern int const Coil_HeatingSteam;
    thread_local extern int const CoilWater_CoolingHXAssisted;

    thread_local extern int const Coil_CoolingWaterToAirHP;
    thread_local extern int const Coil_HeatingWaterToAirHP;
    thread_local extern int const Coil_CoolingWaterToAirHPSimple;
    thread_local extern int const Coil_HeatingWaterToAirHPSimple;
    thread_local extern int const CoilVRF_Cooling;
    thread_local extern int const CoilVRF_Heating;

    thread_local extern int const Coil_UserDefined;
    thread_local extern int const CoilDX_PackagedThermalStorageCooling;

    thread_local extern int const Coil_CoolingWaterToAirHPVSEquationFit;
    thread_local extern int const Coil_HeatingWaterToAirHPVSEquationFit;
    thread_local extern int const Coil_CoolingAirToAirVariableSpeed;
    thread_local extern int const Coil_HeatingAirToAirVariableSpeed;
    thread_local extern int const CoilDX_HeatPumpWaterHeaterVariableSpeed;

    thread_local extern int const CoilVRF_FluidTCtrl_Cooling;
    thread_local extern int const CoilVRF_FluidTCtrl_Heating;

    thread_local extern Array1D_string const cAllCoilTypes;
    thread_local extern Array1D_string const cCoolingCoilTypes;
    thread_local extern Array1D_string const cHeatingCoilTypes;

    // Water to air HP coil types
    thread_local extern int const WatertoAir_Simple;
    thread_local extern int const WatertoAir_ParEst;
    thread_local extern int const WatertoAir_VarSpeedEquationFit;
    thread_local extern int const WatertoAir_VarSpeedLooUpTable;

    // Water to Air HP Water Flow Mode
    thread_local extern int const WaterCycling;  // water flow cycles with compressor
    thread_local extern int const WaterConstant; // water flow is constant
    thread_local extern int const
        WaterConstantOnDemand; // water flow is constant whenever the coil is operational - this is the only method used in EP V7.2 and earlier

    // parameters describing coil performance types
    thread_local extern int const CoilPerfDX_CoolBypassEmpirical;

    // Airflow per total capacity range (Regular DX coils)
    thread_local extern Real64 const MaxRatedVolFlowPerRatedTotCap1; // m3/s per watt = 450 cfm/ton
    thread_local extern Real64 const MinRatedVolFlowPerRatedTotCap1; // m3/s per watt = 300 cfm/ton
    thread_local extern Real64 const MaxHeatVolFlowPerRatedTotCap1;  // m3/s per watt = 600 cfm/ton
    thread_local extern Real64 const MaxCoolVolFlowPerRatedTotCap1;  // m3/s per watt = 500 cfm/ton
    thread_local extern Real64 const MinOperVolFlowPerRatedTotCap1;  // m3/s per watt = 200 cfm/ton

    // 100% DOAS DX coils Airflow per total capacity ratio
    thread_local extern Real64 const MaxRatedVolFlowPerRatedTotCap2; // m3/s per watt = 250 cfm/ton
    thread_local extern Real64 const MinRatedVolFlowPerRatedTotCap2; // m3/s per watt = 125 cfm/ton
    thread_local extern Real64 const MaxHeatVolFlowPerRatedTotCap2;  // m3/s per watt = 300 cfm/ton
    thread_local extern Real64 const MaxCoolVolFlowPerRatedTotCap2;  // m3/s per watt = 300 cfm/ton
    thread_local extern Real64 const MinOperVolFlowPerRatedTotCap2;  // m3/s per watt = 100 cfm/ton

    thread_local extern Array1D<Real64> MaxRatedVolFlowPerRatedTotCap;
    thread_local extern Array1D<Real64> MinRatedVolFlowPerRatedTotCap;
    thread_local extern Array1D<Real64> MaxHeatVolFlowPerRatedTotCap;
    thread_local extern Array1D<Real64> MaxCoolVolFlowPerRatedTotCap;
    thread_local extern Array1D<Real64> MinOperVolFlowPerRatedTotCap;

    // dx coil type (DXCT)
    thread_local extern int const RegularDXCoil; // Regular DX coils or mixed air dx coils
    thread_local extern int const DOASDXCoil;    // 100% DOAS DX coils
    thread_local extern int DXCT;                // dx coil type: regular DX coil ==1, 100% DOAS DX coil = 2

    // Parameters describing Heat Exchanger types
    thread_local extern int const NumHXTypes;

    thread_local extern int const HX_AIRTOAIR_FLATPLATE;
    thread_local extern int const HX_AIRTOAIR_GENERIC;
    thread_local extern int const HX_DESICCANT_BALANCED;

    thread_local extern Array1D_string const cHXTypes;

    // Parameters describing air terminal mixers
    thread_local extern int const NumATMixerTypes;

    thread_local extern int const No_ATMixer;
    thread_local extern int const ATMixer_InletSide;
    thread_local extern int const ATMixer_SupplySide;

    thread_local extern Array1D_string const cATMixerTypes;
    thread_local extern bool const ATMixerExists;

    // Parameters describing variable refrigerant flow terminal unit types
    thread_local extern int const NumVRFTUTypes;

    thread_local extern int const VRFTUType_ConstVolume;

    thread_local extern Array1D_string const cVRFTUTypes;

    // VRF Heating Performance Curve Temperature Type
    thread_local extern int const NumVRFHeatingPerformanceOATTypes;
    thread_local extern int const WetBulbIndicator;
    thread_local extern int const DryBulbIndicator;

    thread_local extern Array1D_string const cVRFHeatingPerformanceOATTypes;

    // parameter concerning the amount of change in zone temperature is needed
    // for oscillation of zone temperature to be detected.
    thread_local extern Real64 const OscillateMagnitude;

    // Parameters for HVACSystemRootFindingAlgorithm
    thread_local extern int const Bisection;
    // DERIVED TYPE DEFINITIONS

    // INTERFACE BLOCK SPECIFICATIONS

    // MODULE VARIABLE DECLARATIONS:

    thread_local extern bool FirstTimeStepSysFlag; // Set to true at the start of each sub-time step

    thread_local extern Real64 TimeStepSys;                    // System Time Increment - the adaptive time step used by the HVAC simulation (hours)
    thread_local extern Real64 SysTimeElapsed;                 // elapsed system time in zone timestep (hours)
    thread_local extern Real64 FracTimeStepZone;               // System time step divided by the zone time step
    thread_local extern bool ShortenTimeStepSys;               // Logical flag that triggers shortening of system time step
    thread_local extern int NumOfSysTimeSteps;                 // for current zone time step, number of system timesteps inside  it
    thread_local extern int NumOfSysTimeStepsLastZoneTimeStep; // previous zone time step, num of system timesteps inside
    thread_local extern int LimitNumSysSteps;

    thread_local extern bool UseZoneTimeStepHistory;     // triggers use of zone time step history, else system time step history, for ZTM1, ZTMx
    thread_local extern int NumPlantLoops;               // Number of plant loops specified in simulation
    thread_local extern int NumCondLoops;                // Number of condenser plant loops specified in simulation
    thread_local extern int NumElecCircuits;             // Number of electric circuits specified in simulation
    thread_local extern int NumGasMeters;                // Number of gas meters specified in simulation
    thread_local extern int NumPrimaryAirSys;            // Number of primary HVAC air systems
    thread_local extern Real64 OnOffFanPartLoadFraction; // fan part-load fraction (Fan:OnOff)
    thread_local extern Real64 DXCoilTotalCapacity;      // DX coil total cooling capacity (eio report var for HPWHs)
    thread_local extern Real64 DXElecCoolingPower;       // Electric power consumed by DX cooling coil last DX simulation
    thread_local extern Real64 DXElecHeatingPower;       // Electric power consumed by DX heating coil last DX simulation
    thread_local extern Real64 ElecHeatingCoilPower;     // Electric power consumed by electric heating coil
    thread_local extern Real64 AirToAirHXElecPower;      // Electric power consumed by Heat Exchanger:Air To Air (Generic or Flat Plate)
    // from last simulation in HeatRecovery.cc
    thread_local extern Real64 UnbalExhMassFlow;      // unbalanced zone exhaust from a zone equip component [kg/s]
    thread_local extern Real64 BalancedExhMassFlow;   // balanced zone exhaust (declared as so by user)  [kg/s]
    thread_local extern Real64 PlenumInducedMassFlow; // secondary air mass flow rate induced from a return plenum [kg/s]
    thread_local extern bool TurnFansOn;              // If true overrides fan schedule and cycles fans on
    thread_local extern bool TurnZoneFansOnlyOn; // If true overrides zone fan schedule and cycles fans on (currently used only by parallel powered induction unit)
    thread_local extern bool TurnFansOff;        // If True overides fan schedule and TurnFansOn and forces fans off
    thread_local extern bool ZoneCompTurnFansOn; // If true overrides fan schedule and cycles fans on
    thread_local extern bool ZoneCompTurnFansOff; // If True overides fan schedule and TurnFansOn and forces fans off
    thread_local extern bool SetPointErrorFlag;   // True if any needed setpoints not set; if true, program terminates
    thread_local extern bool DoSetPointTest;      // True one time only for sensed node setpoint test
    thread_local extern bool NightVentOn;         // set TRUE in SimAirServingZone if night ventilation is happening

    thread_local extern int NumTempContComps;
    thread_local extern Real64 HPWHInletDBTemp;     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    thread_local extern Real64 HPWHInletWBTemp;     // Used by curve objects when calculating DX coil performance for HEAT PUMP:WATER HEATER
    thread_local extern Real64 HPWHCrankcaseDBTemp; // Used for HEAT PUMP:WATER HEATER crankcase heater ambient temperature calculations
    thread_local extern bool AirLoopInit;           // flag for whether InitAirLoops has been called
    thread_local extern bool AirLoopsSimOnce;       // True means that the air loops have been simulated once in this environment
    thread_local extern bool GetAirPathDataDone;    // True means that air loops inputs have been processed

    // Hybrid ventilation control part
    thread_local extern int NumHybridVentSysAvailMgrs;                  // Number of hybrid ventilation control
    thread_local extern Array1D_int HybridVentSysAvailAirLoopNum;       // Airloop number in hybrid vent availability manager
    thread_local extern Array1D_int HybridVentSysAvailVentCtrl;         // Ventilation control action in hybrid vent availability manager
    thread_local extern Array1D_int HybridVentSysAvailActualZoneNum;    // Actual zone num in hybrid vent availability manager
    thread_local extern Array1D_int HybridVentSysAvailANCtrlStatus;     // AN control status in hybrid vent availability manager
    thread_local extern Array1D_int HybridVentSysAvailMaster;           // Master object name: Ventilation for simple; Zone name for AN
    thread_local extern Array1D<Real64> HybridVentSysAvailWindModifier; // Wind modifier for AirflowNetwork
    // For multispeed heat pump only
    thread_local extern Real64 MSHPMassFlowRateLow;     // Mass flow rate at low speed
    thread_local extern Real64 MSHPMassFlowRateHigh;    // Mass flow rate at high speed
    thread_local extern Real64 MSHPWasteHeat;           // Waste heat
    thread_local extern Real64 PreviousTimeStep;        // The time step length at the previous time step
    thread_local extern bool ShortenTimeStepSysRoomAir; // Logical flag that triggers shortening of system time step

    thread_local extern Real64 deviationFromSetPtThresholdHtg; // heating threshold for reporting setpoint deviation
    thread_local extern Real64 deviationFromSetPtThresholdClg; // cooling threshold for reporting setpoint deviation

    thread_local extern bool SimAirLoopsFlag;               // True when the air loops need to be (re)simulated
    thread_local extern bool SimElecCircuitsFlag;           // True when electic circuits need to be (re)simulated
    thread_local extern bool SimPlantLoopsFlag;             // True when the main plant loops need to be (re)simulated
    thread_local extern bool SimZoneEquipmentFlag;          // True when zone equipment components need to be (re)simulated
    thread_local extern bool SimNonZoneEquipmentFlag;       // True when non-zone equipment components need to be (re)simulated
    thread_local extern bool ZoneMassBalanceHVACReSim;      // True when zone air mass flow balance and air loop needs (re)simulated
    thread_local extern int MinAirLoopIterationsAfterFirst; // minimum number of HVAC iterations after FirstHVACIteration (must be at least 2 for sequenced loads
                                               // to operate on air loops)

    thread_local extern int const NumZoneHVACTerminalTypes;
    thread_local extern Array1D_string const ccZoneHVACTerminalTypes;
    thread_local extern Array1D_string const ZoneHVACTerminalTypes;
    thread_local extern int const ZoneEquipTypeOf_VariableRefrigerantFlow;
    thread_local extern int const ZoneEquipTypeOf_EnergyRecoveryVentilator;
    thread_local extern int const ZoneEquipTypeOf_FourPipeFanCoil;
    thread_local extern int const ZoneEquipTypeOf_OutdoorAirUnit;
    thread_local extern int const ZoneEquipTypeOf_PackagedTerminalAirConditioner;
    thread_local extern int const ZoneEquipTypeOf_PackagedTerminalHeatPump;
    thread_local extern int const ZoneEquipTypeOf_UnitHeater;
    thread_local extern int const ZoneEquipTypeOf_UnitVentilator;
    thread_local extern int const ZoneEquipTypeOf_VentilatedSlab;
    thread_local extern int const ZoneEquipTypeOf_WaterToAirHeatPump;
    thread_local extern int const ZoneEquipTypeOf_WindowAirConditioner;
    thread_local extern int const ZoneEquipTypeOf_BaseboardRadiantConvectiveElectric;
    thread_local extern int const ZoneEquipTypeOf_BaseboardRadiantConvectiveWater;
    thread_local extern int const ZoneEquipTypeOf_BaseboardRadiantConvectiveSteam;
    thread_local extern int const ZoneEquipTypeOf_BaseboardConvectiveElectric;
    thread_local extern int const ZoneEquipTypeOf_BaseboardConvectiveWater;
    thread_local extern int const ZoneEquipTypeOf_HighTemperatureRadiant;
    thread_local extern int const ZoneEquipTypeOf_DehumidifierDX;
    thread_local extern int const ZoneEquipTypeOf_IdealLoadsAirSystem;
    thread_local extern int const ZoneEquipTypeOf_RefrigerationChillerSet;
    thread_local extern int const ZoneEquipTypeOf_FanZoneExhaust;
    thread_local extern int const ZoneEquipTypeOf_WaterHeaterHeatPump;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctUncontrolled;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalDualDuctConstantVolume;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalDualDuctVAV;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeNoReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVNoReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctSeriesPIUReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctParallelPIUReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctCAVFourPipeInduction;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVReheatVariableSpeedFan;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctVAVHeatAndCoolNoReheat;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalSingleDuctConstantVolumeCooledBeam;
    thread_local extern int const ZoneEquipTypeOf_AirTerminalDualDuctVAVOutdoorAir;
    thread_local extern int const ZoneEquipTypeOf_AirLoopHVACReturnAir;

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
    thread_local extern Array1D<ZoneCompTypeData> ZoneComp;
    thread_local extern OptStartDataType OptStartData; // For optimum start
    thread_local extern Array1D<ComponentSetPtData> CompSetPtEquip;
    thread_local extern HVACSystemRootFindingAlgorithm HVACSystemRootFinding;

    // Clears the global data in DataHVACGlobals.
    // Needed for unit tests, should not be normally called.
    void clear_state();

} // namespace DataHVACGlobals

} // namespace EnergyPlus

#endif
