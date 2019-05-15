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

#ifndef DataPlant_hh_INCLUDED
#define DataPlant_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>
#include <ObjexxFCL/Fmath.hh>
#include <ObjexxFCL/Optional.hh>

// EnergyPlus Headers
#include <DataGlobals.hh>
#include <DataLoopNode.hh>
#include <EnergyPlus.hh>
#include <OutputProcessor.hh>
#include <Plant/CallingOrder.hh>
#include <Plant/Enums.hh>
#include <Plant/Loop.hh>
#include <Plant/PlantAvailManager.hh>
#include <Plant/PlantLoopSolver.hh>
#include <Plant/ReportLoopData.hh>
#include <Plant/ReportVars.hh>

namespace EnergyPlus {

namespace DataPlant {

    // Using/Aliasing
    using DataLoopNode::SensedNodeFlagValue;

    thread_local int const OptimalLoading(1);              // Optimal Load Distribution Scheme
    thread_local int const SequentialLoading(2);           // Sequential Load Distribution Scheme
    thread_local int const UniformLoading(3);              // Uniform Load Distribution Scheme
    thread_local int const UniformPLRLoading(4);           // Uniform PLR Load Distribution Scheme
    thread_local int const SequentialUniformPLRLoading(5); // Sequential Uniform PLR Load Distribution Scheme

    thread_local extern int const LoadRangeBasedMin;
    thread_local extern int const LoadRangeBasedMax;

    // SimFlagCriteriaTypes for use in performing interconnect re-sim checks
    thread_local extern int const CriteriaType_MassFlowRate;
    thread_local extern int const CriteriaType_Temperature;
    thread_local extern int const CriteriaType_HeatTransferRate;

    // Criteria percentage limits for determining re-simulation of connected loop sides
    thread_local extern Real64 const CriteriaDelta_MassFlowRate;
    thread_local extern Real64 const CriteriaDelta_Temperature;
    thread_local extern Real64 const CriteriaDelta_HeatTransferRate;

    thread_local extern int const FreeCoolControlMode_WetBulb; // HeatExchanger:Hydronic model control type mode, outdoor wetbulb sensor
    thread_local extern int const FreeCoolControlMode_DryBulb; // HeatExchanger:Hydronic model control type mode, outdoor drybulb sensor
    thread_local extern int const FreeCoolControlMode_Loop;    // HeatExchanger:Hydronic model control type mode, loop setpoint sensor

    // Parameters for use in Loop Demand Calculation Schemes
    thread_local extern int const SingleSetPoint;       // Uses a single temp setpoint to calculate loop demand
    thread_local extern int const DualSetPointDeadBand; // Uses a dual temp setpoint with a deadband between the high
    //  and the low to calculate loop demand
    // Parameters for loop setpoint reference
    thread_local extern int const Air;
    thread_local extern int const Ground;

    // Parameters for common pipe
    thread_local extern int const CommonPipe_No;
    thread_local extern int const CommonPipe_Single;
    thread_local extern int const CommonPipe_TwoWay;

    // Parameters for loop side location
    thread_local extern int const DemandSupply_No;
    thread_local extern int const DemandSide;
    thread_local extern int const SupplySide;

    // Parameters for economizer
    thread_local extern int const Integrated;
    thread_local extern int const NonIntegrated;
    thread_local extern int const None;

    // Parameters for tolerance
    thread_local extern Real64 const LoopDemandTol; // minimum significant loop cooling or heating demand
    thread_local extern Real64 const DeltaTempTol;  // minimum significant loop temperature difference

    // Parameters for Component/Equipment Types  (ref: TypeOf in CompData)
    thread_local extern int const LoopType_Plant;
    thread_local extern int const LoopType_Condenser;
    thread_local extern int const LoopType_Both;

    // Parameters for FlowLock standardization
    thread_local extern int const FlowPumpQuery; // Used to ask the pumps for their min/max avail based on no constraints
    thread_local extern int const FlowUnlocked;  // components request flow
    thread_local extern int const FlowLocked;    // components take their inlet flow

    // Pressure Routine Call Enumeration
    thread_local extern int const PressureCall_Init;
    thread_local extern int const PressureCall_Calc;
    thread_local extern int const PressureCall_Update;

    // Pressure Simulation Types
    thread_local extern int const Press_NoPressure;          // Nothing for that particular loop
    thread_local extern int const Press_PumpPowerCorrection; // Only updating the pump power
    thread_local extern int const Press_FlowCorrection;      // Update pump flow rate based on pump curve
    thread_local extern int const Press_FlowSimulation;      // Full pressure network simulation
    thread_local extern Array1D_string const PressureSimType;
    // Parameters for Component/Equipment Types  (ref: TypeOf in CompData)
    thread_local extern int const NumSimPlantEquipTypes;
    thread_local extern Array1D_string const SimPlantEquipTypes;

    thread_local extern Array1D_string const ccSimPlantEquipTypes;

    thread_local extern Array1D_int const ValidLoopEquipTypes;

    thread_local extern int const TypeOf_Other;
    thread_local extern int const TypeOf_Boiler_Simple;
    thread_local extern int const TypeOf_Boiler_Steam;
    thread_local extern int const TypeOf_Chiller_Absorption;          // older BLAST absorption chiller
    thread_local extern int const TypeOf_Chiller_Indirect_Absorption; // revised absorption chiller
    thread_local extern int const TypeOf_Chiller_CombTurbine;
    thread_local extern int const TypeOf_Chiller_ConstCOP;
    thread_local extern int const TypeOf_Chiller_DFAbsorption;
    thread_local extern int const TypeOf_Chiller_Electric; // basic BLAST Chiller
    thread_local extern int const TypeOf_Chiller_ElectricEIR;
    thread_local extern int const TypeOf_Chiller_ElectricReformEIR;
    thread_local extern int const TypeOf_Chiller_EngineDriven;
    thread_local extern int const TypeOf_CoolingTower_SingleSpd;
    thread_local extern int const TypeOf_CoolingTower_TwoSpd;
    thread_local extern int const TypeOf_CoolingTower_VarSpd;
    thread_local extern int const TypeOf_Generator_FCExhaust;
    thread_local extern int const TypeOf_HeatPumpWtrHeaterPumped;
    thread_local extern int const TypeOf_HeatPumpWtrHeaterWrapped;
    thread_local extern int const TypeOf_HPWaterEFCooling;
    thread_local extern int const TypeOf_HPWaterEFHeating;
    thread_local extern int const TypeOf_HPWaterPECooling;
    thread_local extern int const TypeOf_HPWaterPEHeating;
    thread_local extern int const TypeOf_Pipe;
    thread_local extern int const TypeOf_PipeSteam;
    thread_local extern int const TypeOf_PipeExterior;
    thread_local extern int const TypeOf_PipeInterior;
    thread_local extern int const TypeOf_PipeUnderground;
    thread_local extern int const TypeOf_PurchChilledWater;
    thread_local extern int const TypeOf_PurchHotWater;
    thread_local extern int const TypeOf_TS_IceDetailed;
    thread_local extern int const TypeOf_TS_IceSimple;
    thread_local extern int const TypeOf_ValveTempering;
    thread_local extern int const TypeOf_WtrHeaterMixed;
    thread_local extern int const TypeOf_WtrHeaterStratified;
    thread_local extern int const TypeOf_PumpVariableSpeed;
    thread_local extern int const TypeOf_PumpConstantSpeed;
    thread_local extern int const TypeOf_PumpCondensate;
    thread_local extern int const TypeOf_PumpBankVariableSpeed;
    thread_local extern int const TypeOf_PumpBankConstantSpeed;
    thread_local extern int const TypeOf_WaterUseConnection;
    thread_local extern int const TypeOf_CoilWaterCooling;             // demand side component
    thread_local extern int const TypeOf_CoilWaterDetailedFlatCooling; // demand side component
    thread_local extern int const TypeOf_CoilWaterSimpleHeating;       // demand side component
    thread_local extern int const TypeOf_CoilSteamAirHeating;          // demand side component
    thread_local extern int const TypeOf_SolarCollectorFlatPlate;      // demand side component
    thread_local extern int const TypeOf_PlantLoadProfile;             // demand side component
    thread_local extern int const TypeOf_GrndHtExchgSystem;
    thread_local extern int const TypeOf_GrndHtExchgSurface;
    thread_local extern int const TypeOf_GrndHtExchgPond;
    thread_local extern int const TypeOf_Generator_MicroTurbine; // newer FSEC turbine
    thread_local extern int const TypeOf_Generator_ICEngine;
    thread_local extern int const TypeOf_Generator_CTurbine; // older BLAST turbine
    thread_local extern int const TypeOf_Generator_MicroCHP;
    thread_local extern int const TypeOf_Generator_FCStackCooler;
    thread_local extern int const TypeOf_FluidCooler_SingleSpd;
    thread_local extern int const TypeOf_FluidCooler_TwoSpd;
    thread_local extern int const TypeOf_EvapFluidCooler_SingleSpd;
    thread_local extern int const TypeOf_EvapFluidCooler_TwoSpd;
    thread_local extern int const TypeOf_ChilledWaterTankMixed;
    thread_local extern int const TypeOf_ChilledWaterTankStratified;
    thread_local extern int const TypeOf_PVTSolarCollectorFlatPlate;
    thread_local extern int const TypeOf_Baseboard_Conv_Water;
    thread_local extern int const TypeOf_Baseboard_Rad_Conv_Steam;
    thread_local extern int const TypeOf_Baseboard_Rad_Conv_Water;
    thread_local extern int const TypeOf_CoolingPanel_Simple;
    thread_local extern int const TypeOf_LowTempRadiant_VarFlow;
    thread_local extern int const TypeOf_LowTempRadiant_ConstFlow;
    thread_local extern int const TypeOf_CooledBeamAirTerminal;
    thread_local extern int const TypeOf_CoilWAHPHeatingEquationFit;
    thread_local extern int const TypeOf_CoilWAHPCoolingEquationFit;
    thread_local extern int const TypeOf_CoilWAHPHeatingParamEst;
    thread_local extern int const TypeOf_CoilWAHPCoolingParamEst;
    thread_local extern int const TypeOf_RefrigSystemWaterCondenser;
    thread_local extern int const TypeOf_RefrigerationWaterCoolRack;
    thread_local extern int const TypeOf_MultiSpeedHeatPumpRecovery;
    thread_local extern int const TypeOf_Chiller_ExhFiredAbsorption;
    thread_local extern int const TypeOf_PipingSystemPipeCircuit;
    thread_local extern int const TypeOf_SolarCollectorICS;
    thread_local extern int const TypeOf_CoilVSWAHPHeatingEquationFit;
    thread_local extern int const TypeOf_CoilVSWAHPCoolingEquationFit;
    thread_local extern int const TypeOf_PlantComponentUserDefined;
    thread_local extern int const TypeOf_CoilUserDefined;
    thread_local extern int const TypeOf_ZoneHVACAirUserDefined;
    thread_local extern int const TypeOf_AirTerminalUserDefined;
    thread_local extern int const TypeOf_HeatPumpVRF;
    thread_local extern int const TypeOf_GrndHtExchgHorizTrench;
    thread_local extern int const TypeOf_FluidToFluidPlantHtExchg;
    thread_local extern int const TypeOf_WaterSource;
    thread_local extern int const TypeOf_CentralGroundSourceHeatPump;
    thread_local extern int const TypeOf_UnitarySysRecovery;
    thread_local extern int const TypeOf_PackagedTESCoolingCoil;
    thread_local extern int const TypeOf_CoolingTower_VarSpdMerkel;
    thread_local extern int const TypeOf_SwimmingPool_Indoor;
    thread_local extern int const TypeOf_GrndHtExchgSlinky;
    thread_local extern int const TypeOf_FourPipeBeamAirTerminal;

    // Parameters for General Equipment Types
    thread_local extern int const NumGeneralEquipTypes;
    thread_local extern Array1D_string const GeneralEquipTypes;

    thread_local extern int const GenEquipTypes_Boiler;
    thread_local extern int const GenEquipTypes_Chiller;
    thread_local extern int const GenEquipTypes_CoolingTower;
    thread_local extern int const GenEquipTypes_Generator;
    thread_local extern int const GenEquipTypes_HeatExchanger;
    thread_local extern int const GenEquipTypes_HeatPump;
    thread_local extern int const GenEquipTypes_Pipe;
    thread_local extern int const GenEquipTypes_Pump;
    thread_local extern int const GenEquipTypes_Purchased;
    thread_local extern int const GenEquipTypes_ThermalStorage;
    thread_local extern int const GenEquipTypes_Valve;
    thread_local extern int const GenEquipTypes_WaterThermalTank;
    thread_local extern int const GenEquipTypes_WaterUse;
    thread_local extern int const GenEquipTypes_DemandCoil;
    thread_local extern int const GenEquipTypes_SolarCollector;
    thread_local extern int const GenEquipTypes_LoadProfile;
    thread_local extern int const GenEquipTypes_FluidCooler;
    thread_local extern int const GenEquipTypes_EvapFluidCooler;
    thread_local extern int const GenEquipTypes_GroundHeatExchanger;
    thread_local extern int const GenEquipTypes_ZoneHVACDemand;
    thread_local extern int const GenEquipTypes_Refrigeration;
    thread_local extern int const GenEquipTypes_PlantComponent;
    thread_local extern int const GenEquipTypes_CentralHeatPumpSystem;

    thread_local extern Array1D<Real64> const ConvergenceHistoryARR;
    thread_local extern Real64 const sum_ConvergenceHistoryARR;
    thread_local extern Real64 const square_sum_ConvergenceHistoryARR;
    thread_local extern Real64 const sum_square_ConvergenceHistoryARR;

    thread_local extern int NumPipes;                       // Total number of pipes
    thread_local extern int NumPlantPipes;                  // Total number of plant pipes
    thread_local extern int NumCondPipes;                   // Total number of condenser pipes
    thread_local extern int TotNumLoops;                    // number of plant and condenser loops
    thread_local extern int TotNumHalfLoops;                // number of half loops (2 * TotNumLoops)
    thread_local extern bool PlantFirstSizeCompleted;       // true if first-pass sizing is still going on and not finished
    thread_local extern bool PlantFirstSizesOkayToFinalize; // true if first-pass plant sizing is finish and can save results for simulation
    thread_local extern bool PlantFirstSizesOkayToReport;   // true if initial first pass size can be reported
    thread_local extern bool PlantFinalSizesOkayToReport;   // true if plant sizing is really all done and final results reported
    thread_local extern bool PlantReSizingCompleted;

    thread_local extern bool AnyEMSPlantOpSchemesInModel;

    thread_local extern Array1D_int EconBranchNum; // Branch num on which economizer is placed
    thread_local extern Array1D_int EconCompNum;   // Component num of economizer in the economizer branch

    thread_local extern Array1D_bool LoadChangeDownStream; // sim control flag.

    thread_local extern int PlantManageSubIterations; // tracks plant iterations to characterize solver
    thread_local extern int PlantManageHalfLoopCalls; // tracks number of half loop calls

    // Object Data
    thread_local extern Array1D<PlantLoopData> PlantLoop;
    thread_local extern Array1D<PlantAvailMgrData> PlantAvailMgr;
    thread_local extern Array1D<ReportVars> PlantReport;
    thread_local extern Array1D<ReportLoopData> VentRepPlantSupplySide;
    thread_local extern Array1D<ReportLoopData> VentRepPlantDemandSide;
    thread_local extern Array1D<ReportLoopData> VentRepCondSupplySide;
    thread_local extern Array1D<ReportLoopData> VentRepCondDemandSide;
    thread_local extern Array1D<PlantCallingOrderInfoStruct> PlantCallingOrderInfo;

    // Clears the global data in DataPlant.
    // Needed for unit tests, should not be normally called.
    void clear_state();

} // namespace DataPlant

} // namespace EnergyPlus

#endif
