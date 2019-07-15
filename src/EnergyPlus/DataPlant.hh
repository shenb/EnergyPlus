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

    EP_GLOBAL int const OptimalLoading(1);              // Optimal Load Distribution Scheme
    EP_GLOBAL int const SequentialLoading(2);           // Sequential Load Distribution Scheme
    EP_GLOBAL int const UniformLoading(3);              // Uniform Load Distribution Scheme
    EP_GLOBAL int const UniformPLRLoading(4);           // Uniform PLR Load Distribution Scheme
    EP_GLOBAL int const SequentialUniformPLRLoading(5); // Sequential Uniform PLR Load Distribution Scheme

    EP_GLOBAL extern int const LoadRangeBasedMin;
    EP_GLOBAL extern int const LoadRangeBasedMax;

    // SimFlagCriteriaTypes for use in performing interconnect re-sim checks
    EP_GLOBAL extern int const CriteriaType_MassFlowRate;
    EP_GLOBAL extern int const CriteriaType_Temperature;
    EP_GLOBAL extern int const CriteriaType_HeatTransferRate;

    // Criteria percentage limits for determining re-simulation of connected loop sides
    EP_GLOBAL extern Real64 const CriteriaDelta_MassFlowRate;
    EP_GLOBAL extern Real64 const CriteriaDelta_Temperature;
    EP_GLOBAL extern Real64 const CriteriaDelta_HeatTransferRate;

    EP_GLOBAL extern int const FreeCoolControlMode_WetBulb; // HeatExchanger:Hydronic model control type mode, outdoor wetbulb sensor
    EP_GLOBAL extern int const FreeCoolControlMode_DryBulb; // HeatExchanger:Hydronic model control type mode, outdoor drybulb sensor
    EP_GLOBAL extern int const FreeCoolControlMode_Loop;    // HeatExchanger:Hydronic model control type mode, loop setpoint sensor

    // Parameters for use in Loop Demand Calculation Schemes
    EP_GLOBAL extern int const SingleSetPoint;       // Uses a single temp setpoint to calculate loop demand
    EP_GLOBAL extern int const DualSetPointDeadBand; // Uses a dual temp setpoint with a deadband between the high
    //  and the low to calculate loop demand
    // Parameters for loop setpoint reference
    EP_GLOBAL extern int const Air;
    EP_GLOBAL extern int const Ground;

    // Parameters for common pipe
    EP_GLOBAL extern int const CommonPipe_No;
    EP_GLOBAL extern int const CommonPipe_Single;
    EP_GLOBAL extern int const CommonPipe_TwoWay;

    // Parameters for loop side location
    EP_GLOBAL extern int const DemandSupply_No;
    EP_GLOBAL extern int const DemandSide;
    EP_GLOBAL extern int const SupplySide;

    // Parameters for economizer
    EP_GLOBAL extern int const Integrated;
    EP_GLOBAL extern int const NonIntegrated;
    EP_GLOBAL extern int const None;

    // Parameters for tolerance
    EP_GLOBAL extern Real64 const LoopDemandTol; // minimum significant loop cooling or heating demand
    EP_GLOBAL extern Real64 const DeltaTempTol;  // minimum significant loop temperature difference

    // Parameters for Component/Equipment Types  (ref: TypeOf in CompData)
    EP_GLOBAL extern int const LoopType_Plant;
    EP_GLOBAL extern int const LoopType_Condenser;
    EP_GLOBAL extern int const LoopType_Both;

    // Parameters for FlowLock standardization
    EP_GLOBAL extern int const FlowPumpQuery; // Used to ask the pumps for their min/max avail based on no constraints
    EP_GLOBAL extern int const FlowUnlocked;  // components request flow
    EP_GLOBAL extern int const FlowLocked;    // components take their inlet flow

    // Pressure Routine Call Enumeration
    EP_GLOBAL extern int const PressureCall_Init;
    EP_GLOBAL extern int const PressureCall_Calc;
    EP_GLOBAL extern int const PressureCall_Update;

    // Pressure Simulation Types
    EP_GLOBAL extern int const Press_NoPressure;          // Nothing for that particular loop
    EP_GLOBAL extern int const Press_PumpPowerCorrection; // Only updating the pump power
    EP_GLOBAL extern int const Press_FlowCorrection;      // Update pump flow rate based on pump curve
    EP_GLOBAL extern int const Press_FlowSimulation;      // Full pressure network simulation
    EP_GLOBAL extern Array1D_string const PressureSimType;
    // Parameters for Component/Equipment Types  (ref: TypeOf in CompData)
    EP_GLOBAL extern int const NumSimPlantEquipTypes;
    EP_GLOBAL extern Array1D_string const SimPlantEquipTypes;

    EP_GLOBAL extern Array1D_string const ccSimPlantEquipTypes;

    EP_GLOBAL extern Array1D_int const ValidLoopEquipTypes;

    EP_GLOBAL extern int const TypeOf_Other;
    EP_GLOBAL extern int const TypeOf_Boiler_Simple;
    EP_GLOBAL extern int const TypeOf_Boiler_Steam;
    EP_GLOBAL extern int const TypeOf_Chiller_Absorption;          // older BLAST absorption chiller
    EP_GLOBAL extern int const TypeOf_Chiller_Indirect_Absorption; // revised absorption chiller
    EP_GLOBAL extern int const TypeOf_Chiller_CombTurbine;
    EP_GLOBAL extern int const TypeOf_Chiller_ConstCOP;
    EP_GLOBAL extern int const TypeOf_Chiller_DFAbsorption;
    EP_GLOBAL extern int const TypeOf_Chiller_Electric; // basic BLAST Chiller
    EP_GLOBAL extern int const TypeOf_Chiller_ElectricEIR;
    EP_GLOBAL extern int const TypeOf_Chiller_ElectricReformEIR;
    EP_GLOBAL extern int const TypeOf_Chiller_EngineDriven;
    EP_GLOBAL extern int const TypeOf_CoolingTower_SingleSpd;
    EP_GLOBAL extern int const TypeOf_CoolingTower_TwoSpd;
    EP_GLOBAL extern int const TypeOf_CoolingTower_VarSpd;
    EP_GLOBAL extern int const TypeOf_Generator_FCExhaust;
    EP_GLOBAL extern int const TypeOf_HeatPumpWtrHeaterPumped;
    EP_GLOBAL extern int const TypeOf_HeatPumpWtrHeaterWrapped;
    EP_GLOBAL extern int const TypeOf_HPWaterEFCooling;
    EP_GLOBAL extern int const TypeOf_HPWaterEFHeating;
    EP_GLOBAL extern int const TypeOf_HPWaterPECooling;
    EP_GLOBAL extern int const TypeOf_HPWaterPEHeating;
    EP_GLOBAL extern int const TypeOf_Pipe;
    EP_GLOBAL extern int const TypeOf_PipeSteam;
    EP_GLOBAL extern int const TypeOf_PipeExterior;
    EP_GLOBAL extern int const TypeOf_PipeInterior;
    EP_GLOBAL extern int const TypeOf_PipeUnderground;
    EP_GLOBAL extern int const TypeOf_PurchChilledWater;
    EP_GLOBAL extern int const TypeOf_PurchHotWater;
    EP_GLOBAL extern int const TypeOf_TS_IceDetailed;
    EP_GLOBAL extern int const TypeOf_TS_IceSimple;
    EP_GLOBAL extern int const TypeOf_ValveTempering;
    EP_GLOBAL extern int const TypeOf_WtrHeaterMixed;
    EP_GLOBAL extern int const TypeOf_WtrHeaterStratified;
    EP_GLOBAL extern int const TypeOf_PumpVariableSpeed;
    EP_GLOBAL extern int const TypeOf_PumpConstantSpeed;
    EP_GLOBAL extern int const TypeOf_PumpCondensate;
    EP_GLOBAL extern int const TypeOf_PumpBankVariableSpeed;
    EP_GLOBAL extern int const TypeOf_PumpBankConstantSpeed;
    EP_GLOBAL extern int const TypeOf_WaterUseConnection;
    EP_GLOBAL extern int const TypeOf_CoilWaterCooling;             // demand side component
    EP_GLOBAL extern int const TypeOf_CoilWaterDetailedFlatCooling; // demand side component
    EP_GLOBAL extern int const TypeOf_CoilWaterSimpleHeating;       // demand side component
    EP_GLOBAL extern int const TypeOf_CoilSteamAirHeating;          // demand side component
    EP_GLOBAL extern int const TypeOf_SolarCollectorFlatPlate;      // demand side component
    EP_GLOBAL extern int const TypeOf_PlantLoadProfile;             // demand side component
    EP_GLOBAL extern int const TypeOf_GrndHtExchgSystem;
    EP_GLOBAL extern int const TypeOf_GrndHtExchgSurface;
    EP_GLOBAL extern int const TypeOf_GrndHtExchgPond;
    EP_GLOBAL extern int const TypeOf_Generator_MicroTurbine; // newer FSEC turbine
    EP_GLOBAL extern int const TypeOf_Generator_ICEngine;
    EP_GLOBAL extern int const TypeOf_Generator_CTurbine; // older BLAST turbine
    EP_GLOBAL extern int const TypeOf_Generator_MicroCHP;
    EP_GLOBAL extern int const TypeOf_Generator_FCStackCooler;
    EP_GLOBAL extern int const TypeOf_FluidCooler_SingleSpd;
    EP_GLOBAL extern int const TypeOf_FluidCooler_TwoSpd;
    EP_GLOBAL extern int const TypeOf_EvapFluidCooler_SingleSpd;
    EP_GLOBAL extern int const TypeOf_EvapFluidCooler_TwoSpd;
    EP_GLOBAL extern int const TypeOf_ChilledWaterTankMixed;
    EP_GLOBAL extern int const TypeOf_ChilledWaterTankStratified;
    EP_GLOBAL extern int const TypeOf_PVTSolarCollectorFlatPlate;
    EP_GLOBAL extern int const TypeOf_Baseboard_Conv_Water;
    EP_GLOBAL extern int const TypeOf_Baseboard_Rad_Conv_Steam;
    EP_GLOBAL extern int const TypeOf_Baseboard_Rad_Conv_Water;
    EP_GLOBAL extern int const TypeOf_CoolingPanel_Simple;
    EP_GLOBAL extern int const TypeOf_LowTempRadiant_VarFlow;
    EP_GLOBAL extern int const TypeOf_LowTempRadiant_ConstFlow;
    EP_GLOBAL extern int const TypeOf_CooledBeamAirTerminal;
    EP_GLOBAL extern int const TypeOf_CoilWAHPHeatingEquationFit;
    EP_GLOBAL extern int const TypeOf_CoilWAHPCoolingEquationFit;
    EP_GLOBAL extern int const TypeOf_CoilWAHPHeatingParamEst;
    EP_GLOBAL extern int const TypeOf_CoilWAHPCoolingParamEst;
    EP_GLOBAL extern int const TypeOf_RefrigSystemWaterCondenser;
    EP_GLOBAL extern int const TypeOf_RefrigerationWaterCoolRack;
    EP_GLOBAL extern int const TypeOf_MultiSpeedHeatPumpRecovery;
    EP_GLOBAL extern int const TypeOf_Chiller_ExhFiredAbsorption;
    EP_GLOBAL extern int const TypeOf_PipingSystemPipeCircuit;
    EP_GLOBAL extern int const TypeOf_SolarCollectorICS;
    EP_GLOBAL extern int const TypeOf_CoilVSWAHPHeatingEquationFit;
    EP_GLOBAL extern int const TypeOf_CoilVSWAHPCoolingEquationFit;
    EP_GLOBAL extern int const TypeOf_PlantComponentUserDefined;
    EP_GLOBAL extern int const TypeOf_CoilUserDefined;
    EP_GLOBAL extern int const TypeOf_ZoneHVACAirUserDefined;
    EP_GLOBAL extern int const TypeOf_AirTerminalUserDefined;
    EP_GLOBAL extern int const TypeOf_HeatPumpVRF;
    EP_GLOBAL extern int const TypeOf_GrndHtExchgHorizTrench;
    EP_GLOBAL extern int const TypeOf_FluidToFluidPlantHtExchg;
    EP_GLOBAL extern int const TypeOf_WaterSource;
    EP_GLOBAL extern int const TypeOf_CentralGroundSourceHeatPump;
    EP_GLOBAL extern int const TypeOf_UnitarySysRecovery;
    EP_GLOBAL extern int const TypeOf_PackagedTESCoolingCoil;
    EP_GLOBAL extern int const TypeOf_CoolingTower_VarSpdMerkel;
    EP_GLOBAL extern int const TypeOf_SwimmingPool_Indoor;
    EP_GLOBAL extern int const TypeOf_GrndHtExchgSlinky;
    EP_GLOBAL extern int const TypeOf_FourPipeBeamAirTerminal;
    EP_GLOBAL extern int const TypeOf_HeatPumpEIRCooling;
    EP_GLOBAL extern int const TypeOf_HeatPumpEIRHeating;

    // Parameters for General Equipment Types
    EP_GLOBAL extern int const NumGeneralEquipTypes;
    EP_GLOBAL extern Array1D_string const GeneralEquipTypes;

    EP_GLOBAL extern int const GenEquipTypes_Boiler;
    EP_GLOBAL extern int const GenEquipTypes_Chiller;
    EP_GLOBAL extern int const GenEquipTypes_CoolingTower;
    EP_GLOBAL extern int const GenEquipTypes_Generator;
    EP_GLOBAL extern int const GenEquipTypes_HeatExchanger;
    EP_GLOBAL extern int const GenEquipTypes_HeatPump;
    EP_GLOBAL extern int const GenEquipTypes_Pipe;
    EP_GLOBAL extern int const GenEquipTypes_Pump;
    EP_GLOBAL extern int const GenEquipTypes_Purchased;
    EP_GLOBAL extern int const GenEquipTypes_ThermalStorage;
    EP_GLOBAL extern int const GenEquipTypes_Valve;
    EP_GLOBAL extern int const GenEquipTypes_WaterThermalTank;
    EP_GLOBAL extern int const GenEquipTypes_WaterUse;
    EP_GLOBAL extern int const GenEquipTypes_DemandCoil;
    EP_GLOBAL extern int const GenEquipTypes_SolarCollector;
    EP_GLOBAL extern int const GenEquipTypes_LoadProfile;
    EP_GLOBAL extern int const GenEquipTypes_FluidCooler;
    EP_GLOBAL extern int const GenEquipTypes_EvapFluidCooler;
    EP_GLOBAL extern int const GenEquipTypes_GroundHeatExchanger;
    EP_GLOBAL extern int const GenEquipTypes_ZoneHVACDemand;
    EP_GLOBAL extern int const GenEquipTypes_Refrigeration;
    EP_GLOBAL extern int const GenEquipTypes_PlantComponent;
    EP_GLOBAL extern int const GenEquipTypes_CentralHeatPumpSystem;

    EP_GLOBAL extern Array1D<Real64> const ConvergenceHistoryARR;
    EP_GLOBAL extern Real64 const sum_ConvergenceHistoryARR;
    EP_GLOBAL extern Real64 const square_sum_ConvergenceHistoryARR;
    EP_GLOBAL extern Real64 const sum_square_ConvergenceHistoryARR;

    EP_GLOBAL extern int NumPipes;                       // Total number of pipes
    EP_GLOBAL extern int NumPlantPipes;                  // Total number of plant pipes
    EP_GLOBAL extern int NumCondPipes;                   // Total number of condenser pipes
    EP_GLOBAL extern int TotNumLoops;                    // number of plant and condenser loops
    EP_GLOBAL extern int TotNumHalfLoops;                // number of half loops (2 * TotNumLoops)
    EP_GLOBAL extern bool PlantFirstSizeCompleted;       // true if first-pass sizing is still going on and not finished
    EP_GLOBAL extern bool PlantFirstSizesOkayToFinalize; // true if first-pass plant sizing is finish and can save results for simulation
    EP_GLOBAL extern bool PlantFirstSizesOkayToReport;   // true if initial first pass size can be reported
    EP_GLOBAL extern bool PlantFinalSizesOkayToReport;   // true if plant sizing is really all done and final results reported
    EP_GLOBAL extern bool PlantReSizingCompleted;

    EP_GLOBAL extern bool AnyEMSPlantOpSchemesInModel;

    EP_GLOBAL extern Array1D_int EconBranchNum; // Branch num on which economizer is placed
    EP_GLOBAL extern Array1D_int EconCompNum;   // Component num of economizer in the economizer branch

    EP_GLOBAL extern Array1D_bool LoadChangeDownStream; // sim control flag.

    EP_GLOBAL extern int PlantManageSubIterations; // tracks plant iterations to characterize solver
    EP_GLOBAL extern int PlantManageHalfLoopCalls; // tracks number of half loop calls

    // Object Data
    EP_GLOBAL extern Array1D<PlantLoopData> PlantLoop;
    EP_GLOBAL extern Array1D<PlantAvailMgrData> PlantAvailMgr;
    EP_GLOBAL extern Array1D<ReportVars> PlantReport;
    EP_GLOBAL extern Array1D<ReportLoopData> VentRepPlantSupplySide;
    EP_GLOBAL extern Array1D<ReportLoopData> VentRepPlantDemandSide;
    EP_GLOBAL extern Array1D<ReportLoopData> VentRepCondSupplySide;
    EP_GLOBAL extern Array1D<ReportLoopData> VentRepCondDemandSide;
    EP_GLOBAL extern Array1D<PlantCallingOrderInfoStruct> PlantCallingOrderInfo;

    // Clears the global data in DataPlant.
    // Needed for unit tests, should not be normally called.
    void clear_state();

} // namespace DataPlant

} // namespace EnergyPlus

#endif
