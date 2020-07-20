// EnergyPlus, Copyright (c) 1996-2020, The Board of Trustees of the University of Illinois,
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

#include <iostream> 

// C++ Headers
#include <cmath>

// ObjexxFCL Headers
#include <ObjexxFCL/Array.functions.hh>
#include <ObjexxFCL/Fmath.hh>

// EnergyPlus Headers
#include <EnergyPlus/BranchNodeConnections.hh>
#include <EnergyPlus/DataAirSystems.hh>
#include <EnergyPlus/DataBranchAirLoopPlant.hh>
#include <EnergyPlus/DataContaminantBalance.hh>
#include <EnergyPlus/DataEnvironment.hh>
#include <EnergyPlus/DataHVACGlobals.hh>
#include <EnergyPlus/DataIPShortCuts.hh>
#include <EnergyPlus/DataLoopNode.hh>
#include <EnergyPlus/Plant/DataPlant.hh>
#include <EnergyPlus/DataPrecisionGlobals.hh>
#include <EnergyPlus/DataSizing.hh>
#include <EnergyPlus/DataWater.hh>
#include <EnergyPlus/EMSManager.hh>
#include <EnergyPlus/FaultsManager.hh>
#include <EnergyPlus/FluidProperties.hh>
#include <EnergyPlus/General.hh>
#include <EnergyPlus/GeneralRoutines.hh>
#include <EnergyPlus/GlobalNames.hh>
#include <EnergyPlus/Data/EnergyPlusData.hh>
#include <EnergyPlus/HVACControllers.hh>
#include <EnergyPlus/HVACHXAssistedCoolingCoil.hh>
#include <EnergyPlus/InputProcessing/InputProcessor.hh>
#include <EnergyPlus/NodeInputManager.hh>
#include <EnergyPlus/OutputFiles.hh>
#include <EnergyPlus/OutputProcessor.hh>
#include <EnergyPlus/OutputReportPredefined.hh>
#include <EnergyPlus/PlantUtilities.hh>
#include <EnergyPlus/Psychrometrics.hh>
#include <EnergyPlus/ReportCoilSelection.hh>
#include <EnergyPlus/ReportSizingManager.hh>
#include <EnergyPlus/ScheduleManager.hh>
#include <EnergyPlus/SetPointManager.hh>
#include <EnergyPlus/SimAirServingZones.hh>
#include <EnergyPlus/UtilityRoutines.hh>
#include <EnergyPlus/LiquidDesiccantCoil.hh>
#include <EnergyPlus/WaterManager.hh>

namespace EnergyPlus {

namespace LiquidDesiccantCoil{
    // Module containing the WaterCoil simulation routines

    // MODULE INFORMATION:
    //       AUTHOR         Richard J. Liesen
    //       DATE WRITTEN   April 1998
    //       MODIFIED       April 2004: Rahul Chillar
    //                      Feb. 2010, Brent Griffith, Plant Demand Side Update, general fluid properties
    //       RE-ENGINEERED  na

    // PURPOSE OF THIS MODULE:
    // To encapsulate the data and algorithms required to
    // manage the WaterCoil System Component

    // METHODOLOGY EMPLOYED:

    // REFERENCES:

    // OTHER NOTES:

    // USE STATEMENTS:
    // Use statements for data only modules
    // Using/Aliasing
    using namespace DataPrecisionGlobals;
    using namespace DataLoopNode;
    using namespace DataGlobals;
    using DataEnvironment::OutBaroPress;
    using DataEnvironment::StdBaroPress;
    using DataEnvironment::StdRhoAir;
    using namespace DataHVACGlobals;
    using DataPlant::PlantLoop;
    using DataPlant::TypeOf_CoilLiquidDesiccantCooling;
    //using DataPlant::TypeOf_CoilWaterDetailedFlatCooling;
    using DataPlant::TypeOf_CoilWaterSimpleHeating;
    using FluidProperties::GetDensityGlycol;
    using FluidProperties::GetSpecificHeatGlycol;
    using Psychrometrics::PsyCpAirFnW;
    using Psychrometrics::PsyHFnTdbRhPb;
    using Psychrometrics::PsyHFnTdbW;
    using Psychrometrics::PsyRhoAirFnPbTdbW;
    using Psychrometrics::PsyTdbFnHW;
    using Psychrometrics::PsyTdpFnWPb;
    using Psychrometrics::PsyTsatFnHPb;
    using Psychrometrics::PsyWFnTdbH;
    using Psychrometrics::PsyWFnTdbRhPb;
    using Psychrometrics::PsyWFnTdbTwbPb;
    using Psychrometrics::PsyWFnTdpPb;
    using Psychrometrics::PsyRhFnTdbWPb;
  


    using namespace ScheduleManager;

    // Data
    // PRIVATE ! Everything private unless explicitly made public

    // MODULE PARAMETER DEFINITIONS
    static std::string const BlankString;

    int const MaxPolynomOrder(4);
    int const MaxOrderedPairs(60);

    Real64 const PolyConvgTol(1.E-05);
    Real64 const MinWaterMassFlowFrac(0.000001);
    Real64 const MinAirMassFlow(0.001);

    // coil types in this module
    //int const WaterCoil_SimpleHeating(TypeOf_CoilWaterSimpleHeating);
    int const LiquidDesiccantCoil_Cooling(TypeOf_CoilLiquidDesiccantCooling);

    int const CoilType_Cooling(1);
    int const CoilType_Heating(2);

    int const CoilModel_Simple(1);
    int const CoilModel_Cooling(2);

    // Parameters for Heat Exchanger Configuration
    int const CounterFlow(1);
    int const CrossFlow(2);
    int const SimpleAnalysis(1);
    int const DetailedAnalysis(2);

    // Water Systems
    int const CondensateDiscarded(1001); // default mode where water is "lost"
    int const CondensateToTank(1002);    // collect coil condensate from air and store in water storage tank

    // Parameters for COIL:Water:SimpleHeating Coil Performance Input Method
    int const UAandFlow(1); // for Coil Performance Input Method = UA and Design Water Flow Rate
    int const NomCap(2);    // for Coil Performance Input Method = Nominal Capacity

    // Parameters Subroutine CoolingCoil: design calc or simulation calc.
    int const DesignCalc(1); // ignore on/off check in CoolingCoil
    int const SimCalc(2);    // pay attention to on/off check in CoolingCoil

    // DERIVED TYPE DEFINITIONS

    // MODULE VARIABLE DECLARATIONS:
    int NumWaterCoils(0); // The Number of WaterCoils found in the Input
    Array1D_bool MySizeFlag;
    Array1D_bool MyUAAndFlowCalcFlag;
    Array1D_bool MyCoilDesignFlag;
    Array1D_bool CoilWarningOnceFlag;
    Array1D_int WaterTempCoolCoilErrs;              // error counting for detailed coils
    Array1D_int PartWetCoolCoilErrs;                // error counting for detailed coils
    bool GetWaterCoilsInputFlag(true);              // Flag set to make sure you get input once
    bool WaterCoilControllerCheckOneTimeFlag(true); // flg used to check water coil controller
    Array1D_bool CheckEquipName;
    namespace {
        // These were static variables within different functions. They were pulled out into the namespace
        // to facilitate easier unit testing of those functions.
        // These are purposefully not in the header file as an extern variable. No one outside of this should
        // use these. They are cleared by clear_state() for use by unit tests, but normal simulations should be unaffected.
        // This is purposefully in an anonymous namespace so nothing outside this implementation file can use it.
        bool InitWaterCoilOneTimeFlag(true);
    } // namespace
    // Subroutine Specifications for the Module
    // Driver/Manager Routines

    // Get Input routines for module

    // Initialization routines for module

    // Algorithms for the module

    // Update routine to check convergence and update nodes

    // Reporting routines for module

    // Other routines

    // Object Data
    Array1D<CoilEquipConditions> LiquidDesiccantCoil;
    Array1D<CoilNumericFieldData> LiquidDesiccantCoilNumericFields;

    // MODULE SUBROUTINES:
    //*************************************************************************

    // Functions
    void clear_state()
    {
        NumWaterCoils = 0;
        InitWaterCoilOneTimeFlag = true;
        MySizeFlag.deallocate();
        MyUAAndFlowCalcFlag.deallocate();
        MyCoilDesignFlag.deallocate();
        CoilWarningOnceFlag.deallocate();
        WaterTempCoolCoilErrs.deallocate();
        PartWetCoolCoilErrs.deallocate();
        GetWaterCoilsInputFlag = true;
        CheckEquipName.deallocate();
        LiquidDesiccantCoil.deallocate();
        LiquidDesiccantCoilNumericFields.deallocate();
        WaterCoilControllerCheckOneTimeFlag = true;
    }

    void SimulateLiquideDesiccantCoilComponents(EnergyPlusData &state, std::string const &CompName,
                                     bool const FirstHVACIteration,
                                     int &CompIndex,
                                     Optional<Real64> QActual,
                                     Optional_int_const FanOpMode,
                                     Optional<Real64 const> PartLoadRatio)
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Richard Liesen
        //       DATE WRITTEN   February 1998
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This subroutine manages WaterCoil component simulation.

        // Using/Aliasing
        using General::TrimSigDigits;

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int CoilNum;         // The WaterCoil that you are currently loading input into
        int OpMode;          // fan operating mode
        Real64 PartLoadFrac; // part-load fraction of heating coil

        // FLOW:

        // Obtains and Allocates WaterCoil related parameters from input file
  
        if (GetWaterCoilsInputFlag) { // First time subroutine has been entered
            GetLiquideDesiccantCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        // Find the correct WaterCoilNumber with the Coil Name
        if (CompIndex == 0) {
            CoilNum = 1; // UtilityRoutines::FindItemInList(CompName, WaterCoil);
            if (CoilNum == 0) {
                ShowFatalError("SimulateWaterCoilComponents: Coil not found=" + CompName);
            }
            CompIndex = CoilNum;
        } else {
            CoilNum = CompIndex;
            if (CoilNum > NumWaterCoils || CoilNum < 1) {
                ShowFatalError("SimulateWaterCoilComponents: Invalid CompIndex passed=" + TrimSigDigits(CoilNum) +
                               ", Number of Water Coils=" + TrimSigDigits(NumWaterCoils) + ", Coil name=" + CompName);
            }
            if (CheckEquipName(CoilNum)) {
                if (CompName != LiquidDesiccantCoil(CoilNum).Name) {
                    ShowFatalError("SimulateWaterCoilComponents: Invalid CompIndex passed=" + TrimSigDigits(CoilNum) + ", Coil name=" + CompName +
                                   ", stored Coil Name for that index=" + LiquidDesiccantCoil(CoilNum).Name);
                }
                CheckEquipName(CoilNum) = false;
            }
        }

        // With the correct CoilNum Initialize
        InitLiquideDesiccantCoil(state, CoilNum, FirstHVACIteration); // Initialize all WaterCoil related parameters

        //if (present(FanOpMode)) {
        //    OpMode = FanOpMode;
        //} else {
        OpMode = ContFanCycCoil;
        PartLoadFrac = 1.0;

        SimuLiquideDesiccantCoil(CoilNum, FirstHVACIteration, SimCalc, OpMode, PartLoadFrac);

        // Update the current WaterCoil to the outlet nodes
        UpdateLiquideDesiccantCoil(CoilNum);

        // Report the current WaterCoil
        ReportLiquideDesiccantCoil(CoilNum);
    }

    // Get Input Section of the Module
    //******************************************************************************

    void GetLiquideDesiccantCoilInput()
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Richard Liesen
        //       DATE WRITTEN   April 1998
        //       MODIFIED       April 2004: Rahul Chillar
        //                      November 2013: Tianzhen Hong for fouling coils
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // Obtains input data for coils and stores it in coil data structures

        // METHODOLOGY EMPLOYED:
        // Uses "Get" routines to read in data.
        using namespace std;

        // Using/Aliasing
        using BranchNodeConnections::TestCompSet;
        using DataSizing::AutoSize;
        using NodeInputManager::GetOnlySingleNode;
        using WaterManager::SetupTankSupplyComponent;
        using namespace DataIPShortCuts;
        using GlobalNames::VerifyUniqueCoilName;
        using SetPointManager::NodeHasSPMCtrlVarType;
        using namespace FaultsManager;

        // SUBROUTINE PARAMETER DEFINITIONS:
        static std::string const RoutineName("GetWaterCoilInput: "); // include trailing blank space

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int CoilNum; // The WaterCoil that you are currently loading input into
        static int NumSimpHeat(0);
        static int NumFlatFin(0);
        static int NumCooling(0);
        int SimpHeatNum;
        int FlatFinNum;
        int CoolingNum;
        int NumAlphas;
        int NumNums;
        int IOStat;
        std::string CurrentModuleObject; // for ease in getting objects
        Array1D_string AlphArray;        // Alpha input items for object
        Array1D_string cAlphaFields;     // Alpha field names
        Array1D_string cNumericFields;   // Numeric field names
        Array1D<Real64> NumArray;        // Numeric input items for object
        Array1D_bool lAlphaBlanks;       // Logical array, alpha field input BLANK = .TRUE.
        Array1D_bool lNumericBlanks;     // Logical array, numeric field input BLANK = .TRUE.
        static int MaxNums(0);           // Maximum number of numeric input fields
        static int MaxAlphas(0);         // Maximum number of alpha input fields
        static int TotalArgs(0);         // Total number of alpha and numeric arguments (max) for a
        //  certain object in the input file
        static bool ErrorsFound(false); // If errors detected in input

        // Flow
        NumSimpHeat = 0;        //inputProcessor->getNumObjectsFound("Coil:Heating:Water");
        NumFlatFin = 0;   // inputProcessor->getNumObjectsFound("Coil:Cooling:Water:DetailedGeometry");
        NumCooling = inputProcessor->getNumObjectsFound("Coil:Cooling:LiquidDesiccant");
        NumWaterCoils = NumSimpHeat + NumFlatFin + NumCooling;

        if (NumWaterCoils > 0) {
            LiquidDesiccantCoilNumericFields.allocate(NumWaterCoils);
            LiquidDesiccantCoil.allocate(NumWaterCoils);
            LiquidDesiccantCoilNumericFields.allocate(NumWaterCoils);
            WaterTempCoolCoilErrs.dimension(NumWaterCoils, 0);
            PartWetCoolCoilErrs.dimension(NumWaterCoils, 0);
            CheckEquipName.dimension(NumWaterCoils, true);
        }

        //inputProcessor->getObjectDefMaxArgs("Coil:Heating:Water", TotalArgs, NumAlphas, NumNums);
        //MaxNums = max(MaxNums, NumNums);
        //MaxAlphas = max(MaxAlphas, NumAlphas);

        inputProcessor->getObjectDefMaxArgs("Coil:Cooling:LiquidDesiccant", TotalArgs, NumAlphas, NumNums);
        MaxNums = max(MaxNums, NumNums);
        MaxAlphas = max(MaxAlphas, NumAlphas);

        AlphArray.allocate(MaxAlphas);
        cAlphaFields.allocate(MaxAlphas);
        cNumericFields.allocate(MaxNums);
        NumArray.dimension(MaxNums, 0.0);
        lAlphaBlanks.dimension(MaxAlphas, true);
        lNumericBlanks.dimension(MaxNums, true);

        // Get the data for simple heating coils
        /*
        CurrentModuleObject = "Coil:Heating:Water";
        // Get the data for simple heating coils
        for (SimpHeatNum = 1; SimpHeatNum <= NumSimpHeat; ++SimpHeatNum) {

            CoilNum = SimpHeatNum;

            inputProcessor->getObjectItem(CurrentModuleObject,
                                          SimpHeatNum,
                                          AlphArray,
                                          NumAlphas,
                                          NumArray,
                                          NumNums,
                                          IOStat,
                                          lNumericBlanks,
                                          lAlphaBlanks,
                                          cAlphaFields,
                                          cNumericFields);

            LiquidDesiccantCoilNumericFields(CoilNum).FieldNames.allocate(MaxNums);
            LiquidDesiccantCoilNumericFields(CoilNum).FieldNames = "";
            LiquidDesiccantCoilNumericFields(CoilNum).FieldNames = cNumericFields;
            UtilityRoutines::IsNameEmpty(AlphArray(1), cCurrentModuleObject, ErrorsFound);

            // ErrorsFound will be set to True if problem was found, left untouched otherwise
            VerifyUniqueCoilName(CurrentModuleObject, AlphArray(1), ErrorsFound, CurrentModuleObject + " Name");

            LiquidDesiccantCoil(CoilNum).Name = AlphArray(1);
            LiquidDesiccantCoil(CoilNum).Schedule = AlphArray(2);
            if (lAlphaBlanks(2)) {
                LiquidDesiccantCoil(CoilNum).SchedPtr = ScheduleAlwaysOn;
            } else {
                LiquidDesiccantCoil(CoilNum).SchedPtr = GetScheduleIndex(AlphArray(2));
                if (LiquidDesiccantCoil(CoilNum).SchedPtr == 0) {
                    ShowSevereError(CurrentModuleObject + ": invalid " + cAlphaFields(2) + " entered =" + AlphArray(2) + " for " + cAlphaFields(1) +
                                    '=' + AlphArray(1));
                    ErrorsFound = true;
                }
            }

            LiquidDesiccantCoil(CoilNum).WaterCoilTypeA = "Heating";
            LiquidDesiccantCoil(CoilNum).WaterCoilType = CoilType_Heating; // 'Heating'
            LiquidDesiccantCoil(CoilNum).WaterCoilModelA = "SIMPLE";
            LiquidDesiccantCoil(CoilNum).WaterCoilModel = CoilModel_Simple; // 'SIMPLE'
            LiquidDesiccantCoil(CoilNum).WaterCoilType_Num = WaterCoil_SimpleHeating;

            LiquidDesiccantCoil(CoilNum).UACoil = NumArray(1);
            LiquidDesiccantCoil(CoilNum).UACoilVariable = LiquidDesiccantCoil(CoilNum).UACoil;
            LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate = NumArray(2);
            LiquidDesiccantCoil(CoilNum).WaterInletNodeNum = GetOnlySingleNode(
                AlphArray(3), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Inlet, 2, ObjectIsNotParent);
            LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum = GetOnlySingleNode(
                AlphArray(4), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);
            LiquidDesiccantCoil(CoilNum).AirInletNodeNum = GetOnlySingleNode(
                AlphArray(5), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Inlet, 1, ObjectIsNotParent);
            LiquidDesiccantCoil(CoilNum).AirOutletNodeNum = GetOnlySingleNode(
                AlphArray(6), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Outlet, 1, ObjectIsNotParent);

            {
                auto const SELECT_CASE_var(AlphArray(7));
                if (SELECT_CASE_var == "UFACTORTIMESAREAANDDESIGNWATERFLOWRATE") {
                    LiquidDesiccantCoil(CoilNum).CoilPerfInpMeth = UAandFlow;

                } else if (SELECT_CASE_var == "NOMINALCAPACITY") {
                    LiquidDesiccantCoil(CoilNum).CoilPerfInpMeth = NomCap;

                } else {
                    // will be caught by input processor
                    LiquidDesiccantCoil(CoilNum).CoilPerfInpMeth = UAandFlow;
                }
            }

            LiquidDesiccantCoil(CoilNum).DesTotWaterCoilLoad = NumArray(3);

            if (LiquidDesiccantCoil(CoilNum).UACoil == AutoSize && LiquidDesiccantCoil(CoilNum).CoilPerfInpMeth == UAandFlow)
                LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            if (LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            if (LiquidDesiccantCoil(CoilNum).DesTotWaterCoilLoad == AutoSize && LiquidDesiccantCoil(CoilNum).CoilPerfInpMeth == NomCap)
                LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;

            LiquidDesiccantCoil(CoilNum).DesInletWaterTemp = NumArray(4);
            LiquidDesiccantCoil(CoilNum).DesInletAirTemp = NumArray(5);
            LiquidDesiccantCoil(CoilNum).DesOutletWaterTemp = NumArray(6);
            LiquidDesiccantCoil(CoilNum).DesOutletAirTemp = NumArray(7);
            LiquidDesiccantCoil(CoilNum).RatioAirSideToWaterSideConvect = NumArray(8);
            if (!lNumericBlanks(9)) {
                LiquidDesiccantCoil(CoilNum).DesignWaterDeltaTemp = NumArray(9);
                LiquidDesiccantCoil(CoilNum).UseDesignWaterDeltaTemp = true;
            } else {
                LiquidDesiccantCoil(CoilNum).UseDesignWaterDeltaTemp = false;
            }
            if (LiquidDesiccantCoil(CoilNum).DesInletWaterTemp <= LiquidDesiccantCoil(CoilNum).DesOutletWaterTemp) {
                ShowSevereError("For " + CurrentModuleObject + ", " + AlphArray(1));
                ShowContinueError("  the " + cNumericFields(4) + " must be greater than the " + cNumericFields(6) + '.');
                ErrorsFound = true;
            }
            if (LiquidDesiccantCoil(CoilNum).DesInletAirTemp >= LiquidDesiccantCoil(CoilNum).DesOutletAirTemp) {
                ShowSevereError("For " + CurrentModuleObject + ", " + AlphArray(1));
                ShowContinueError("  the " + cNumericFields(5) + " must be less than the " + cNumericFields(7) + '.');
                ErrorsFound = true;
            }
            if (LiquidDesiccantCoil(CoilNum).DesInletAirTemp >= LiquidDesiccantCoil(CoilNum).DesInletWaterTemp) {
                ShowSevereError("For " + CurrentModuleObject + ", " + AlphArray(1));
                ShowContinueError("  the " + cNumericFields(5) + " must be less than the " + cNumericFields(4) + '.');
                ErrorsFound = true;
            }

            TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(3), AlphArray(4), "Water Nodes");
            TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(5), AlphArray(6), "Air Nodes");

            // Setup the Simple Heating Coil reporting variables
            // CurrentModuleObject = "Coil:Heating:Water"
            SetupOutputVariable("Heating Coil Heating Energy",
                                OutputProcessor::Unit::J,
                                LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilEnergy,
                                "System",
                                "Sum",
                                LiquidDesiccantCoil(CoilNum).Name,
                                _,
                                "ENERGYTRANSFER",
                                "HEATINGCOILS",
                                _,
                                "System");
            SetupOutputVariable("Heating Coil Source Side Heat Transfer Energy",
                                OutputProcessor::Unit::J,
                                LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilEnergy,
                                "System",
                                "Sum",
                                LiquidDesiccantCoil(CoilNum).Name,
                                _,
                                "PLANTLOOPHEATINGDEMAND",
                                "HEATINGCOILS",
                                _,
                                "System");
            SetupOutputVariable("Heating Coil Heating Rate",
                                OutputProcessor::Unit::W,
                                LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate,
                                "System",
                                "Average",
                                LiquidDesiccantCoil(CoilNum).Name);
            SetupOutputVariable("Heating Coil U Factor Times Area Value",
                                OutputProcessor::Unit::W_K,
                                LiquidDesiccantCoil(CoilNum).UACoilVariable,
                                "System",
                                "Average",
                                LiquidDesiccantCoil(CoilNum).Name);
        }
        */
        

        CurrentModuleObject = "Coil:Cooling:LiquidDesiccant";
        // Get the data for Cooling coils.
        for (CoolingNum = 1; CoolingNum <= NumCooling; ++CoolingNum) {

            CoilNum = NumSimpHeat + NumFlatFin + CoolingNum;

            inputProcessor->getObjectItem(CurrentModuleObject,
                                          CoolingNum,
                                          AlphArray,
                                          NumAlphas,
                                          NumArray,
                                          NumNums,
                                          IOStat,
                                          lNumericBlanks,
                                          lAlphaBlanks,
                                          cAlphaFields,
                                          cNumericFields);

            LiquidDesiccantCoilNumericFields(CoilNum).FieldNames.allocate(MaxNums);
            LiquidDesiccantCoilNumericFields(CoilNum).FieldNames = "";
            LiquidDesiccantCoilNumericFields(CoilNum).FieldNames = cNumericFields;
            UtilityRoutines::IsNameEmpty(AlphArray(1), cCurrentModuleObject, ErrorsFound);

            // ErrorsFound will be set to True if problem was found, left untouched otherwise
            VerifyUniqueCoilName(CurrentModuleObject, AlphArray(1), ErrorsFound, CurrentModuleObject + " Name");

            LiquidDesiccantCoil(CoilNum).Name = AlphArray(1);
            LiquidDesiccantCoil(CoilNum).Schedule = AlphArray(2);
            if (lAlphaBlanks(2)) {
                LiquidDesiccantCoil(CoilNum).SchedPtr = ScheduleAlwaysOn;
            } else {
                LiquidDesiccantCoil(CoilNum).SchedPtr = GetScheduleIndex(AlphArray(2));
                if (LiquidDesiccantCoil(CoilNum).SchedPtr == 0) {
                    ShowSevereError(CurrentModuleObject + ": invalid " + cAlphaFields(2) + " entered =" + AlphArray(2) + " for " + cAlphaFields(1) +
                                    '=' + AlphArray(1));
                    ErrorsFound = true;
                }
            }

            LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilTypeA = "Cooling";
            LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType = CoilType_Cooling; // 'Cooling'
            LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilModelA = "Cooling";
            LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilModel = CoilModel_Cooling; // 'Cooling'
            LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType_Num = LiquidDesiccantCoil_Cooling;

            LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate = NumArray(1); // Liquid mass flow rate at Design  kg/s
            if (LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate = NumArray(2); // Dry air mass flow rate at Design (kg/s)
            if (LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            LiquidDesiccantCoil(CoilNum).DesInletWaterTemp = NumArray(3); // Entering water temperature at Design C
            if (LiquidDesiccantCoil(CoilNum).DesInletWaterTemp == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            LiquidDesiccantCoil(CoilNum).DesInletAirTemp = NumArray(4); // Entering air dry bulb temperature at Design(C)
            if (LiquidDesiccantCoil(CoilNum).DesInletAirTemp == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            LiquidDesiccantCoil(CoilNum).DesOutletAirTemp = NumArray(5); // Leaving air dry bulb temperature at Design(C)
            if (LiquidDesiccantCoil(CoilNum).DesOutletAirTemp == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            LiquidDesiccantCoil(CoilNum).DesInletAirHumRat = NumArray(6); // Entering air humidity ratio  at Design
            if (LiquidDesiccantCoil(CoilNum).DesInletAirHumRat == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            LiquidDesiccantCoil(CoilNum).DesOutletAirHumRat = NumArray(7); // Leaving air humidity ratio  at Design
            if (LiquidDesiccantCoil(CoilNum).DesOutletAirHumRat == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
            LiquidDesiccantCoil(CoilNum).DesInletSolnConcentration = NumArray(8); // leaving soultion concentration  at Design
            if (LiquidDesiccantCoil(CoilNum).DesInletSolnConcentration == AutoSize) LiquidDesiccantCoil(CoilNum).RequestingAutoSize = true;
 
            //std::cout << "AlphArray(1) = " << AlphArray(1) << endl;
            //std::cout << "AlphArray(2) = " << AlphArray(2) << endl;

            //std::cout << "NumArray(1) = " << NumArray(1) << endl;
            //std::cout << "NumArray(2) = " << NumArray(2) << endl;
            //std::cout << "NumArray(3) = " << NumArray(3) << endl;
            //std::cout << "NumArray(4) = " << NumArray(4) << endl;
            //std::cout << "NumArray(5) = " << NumArray(5) << endl;
            //std::cout << "NumArray(6) = " << NumArray(6) << endl;
            //std::cout << "NumArray(7) = " << NumArray(7) << endl;
            //std::cout << "NumArray(8) = " << NumArray(8) << endl;
            //std::cout << "NumArray(9) = " << NumArray(9) << endl;


            if (!lNumericBlanks(8)) {
                LiquidDesiccantCoil(CoilNum).DesignWaterDeltaTemp = NumArray(8);
                LiquidDesiccantCoil(CoilNum).UseDesignWaterDeltaTemp = true;
            } else {
                LiquidDesiccantCoil(CoilNum).UseDesignWaterDeltaTemp = false;
            }

            LiquidDesiccantCoil(CoilNum).WaterInletNodeNum = GetOnlySingleNode(
                AlphArray(3), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Inlet, 2, ObjectIsNotParent);
            LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum = GetOnlySingleNode(
                AlphArray(4), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);
            LiquidDesiccantCoil(CoilNum).AirInletNodeNum = GetOnlySingleNode(
                AlphArray(5), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Inlet, 1, ObjectIsNotParent);
            LiquidDesiccantCoil(CoilNum).AirOutletNodeNum = GetOnlySingleNode(
                AlphArray(6), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Outlet, 1, ObjectIsNotParent);

            {
                auto const SELECT_CASE_var(AlphArray(7));
                // The default is SimpleAnalysis = 2.  and DetailedAnalysis   =1
                if (SELECT_CASE_var == "SIMPLEANALYSIS") {
                    LiquidDesiccantCoil(CoilNum).CoolingCoilAnalysisMode = SimpleAnalysis;

                } else if (SELECT_CASE_var == "DETAILEDANALYSIS") {
                    LiquidDesiccantCoil(CoilNum).CoolingCoilAnalysisMode = DetailedAnalysis;

                } else {
                    LiquidDesiccantCoil(CoilNum).CoolingCoilAnalysisMode = SimpleAnalysis;
                }
            }

            {
                auto const SELECT_CASE_var(AlphArray(8));
                // The default is CrossFlow = 2.  and CounterFlow=1
                if (SELECT_CASE_var == "CROSSFLOW") {
                    LiquidDesiccantCoil(CoilNum).HeatExchType = CrossFlow;

                } else if (SELECT_CASE_var == "COUNTERFLOW") {
                    LiquidDesiccantCoil(CoilNum).HeatExchType = CounterFlow;

                } else {
                    LiquidDesiccantCoil(CoilNum).HeatExchType = CrossFlow;
                }
            }

            // A9; \field Name of Water Storage Tank for Condensate Collection
            LiquidDesiccantCoil(CoilNum).CondensateCollectName = AlphArray(9);
            if (lAlphaBlanks(9)) {
                LiquidDesiccantCoil(CoilNum).CondensateCollectMode = CondensateDiscarded;
            } else {
                LiquidDesiccantCoil(CoilNum).CondensateCollectMode = CondensateToTank;
                SetupTankSupplyComponent(LiquidDesiccantCoil(CoilNum).Name,
                                         CurrentModuleObject,
                                         LiquidDesiccantCoil(CoilNum).CondensateCollectName,
                                         ErrorsFound,
                                         LiquidDesiccantCoil(CoilNum).CondensateTankID,
                                         LiquidDesiccantCoil(CoilNum).CondensateTankSupplyARRID);
            }

            TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(3), AlphArray(4), "Water Nodes");
            TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(5), AlphArray(6), "Air Nodes");

            // Setup Report variables for the Design input Cooling Coils
            // CurrentModuleObject = "Coil:Cooling:Water"
            SetupOutputVariable("Cooling Coil Total Cooling Energy",
                                OutputProcessor::Unit::J,
                                LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilEnergy,
                                "System",
                                "Sum",
                                LiquidDesiccantCoil(CoilNum).Name,
                                _,
                                "ENERGYTRANSFER",
                                "COOLINGCOILS",
                                _,
                                "System");
            SetupOutputVariable("Cooling Coil Source Side Heat Transfer Energy",
                                OutputProcessor::Unit::J,
                                LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilEnergy,
                                "System",
                                "Sum",
                                LiquidDesiccantCoil(CoilNum).Name,
                                _,
                                "PLANTLOOPCOOLINGDEMAND",
                                "COOLINGCOILS",
                                _,
                                "System");
            SetupOutputVariable("Cooling Coil Sensible Cooling Energy",
                                OutputProcessor::Unit::J,
                                LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilEnergy,
                                "System",
                                "Sum",
                                LiquidDesiccantCoil(CoilNum).Name);
            SetupOutputVariable("Cooling Coil Total Cooling Rate",
                                OutputProcessor::Unit::W,
                                LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate,
                                "System",
                                "Average",
                                LiquidDesiccantCoil(CoilNum).Name);
            SetupOutputVariable("Cooling Coil Sensible Cooling Rate",
                                OutputProcessor::Unit::W,
                                LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate,
                                "System",
                                "Average",
                                LiquidDesiccantCoil(CoilNum).Name);
            SetupOutputVariable("Cooling Coil Wetted Area Fraction",
                                OutputProcessor::Unit::None,
                                LiquidDesiccantCoil(CoilNum).SurfAreaWetFraction,
                                "System",
                                "Average",
                                LiquidDesiccantCoil(CoilNum).Name);

            if (LiquidDesiccantCoil(CoilNum).CondensateCollectMode == CondensateToTank) {

                SetupOutputVariable("Cooling Coil Condensate Volume Flow Rate",
                                    OutputProcessor::Unit::m3_s,
                                    LiquidDesiccantCoil(CoilNum).CondensateVdot,
                                    "System",
                                    "Average",
                                    LiquidDesiccantCoil(CoilNum).Name);
                SetupOutputVariable("Cooling Coil Condensate Volume",
                                    OutputProcessor::Unit::m3,
                                    LiquidDesiccantCoil(CoilNum).CondensateVol,
                                    "System",
                                    "Sum",
                                    LiquidDesiccantCoil(CoilNum).Name,
                                    _,
                                    "OnSiteWater",
                                    "Condensate",
                                    _,
                                    "System");
            }
        }

        if (ErrorsFound) {
            ShowFatalError(RoutineName + "Errors found in getting input.");
        }

        AlphArray.deallocate();
        cAlphaFields.deallocate();
        cNumericFields.deallocate();
        NumArray.deallocate();
        lAlphaBlanks.deallocate();
        lNumericBlanks.deallocate();
    }
    // End of Get Input subroutines for the HB Module
    //******************************************************************************

    // Beginning Initialization Section of the Module
    //******************************************************************************
    void InitLiquideDesiccantCoil(EnergyPlusData &state, int const CoilNum, bool const FirstHVACIteration)
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Richard J. Liesen
        //       DATE WRITTEN   February 1998
        //       MODIFIED       April 2004: Rahul Chillar
        //                      November 2013: XP, Tianzhen Hong to handle fouling coils
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This subroutine is for initializations of the WaterCoil Components.

        // METHODOLOGY EMPLOYED:
        // Uses the status flags to trigger initializations.

        // REFERENCES:

        using namespace std;

        // Using/Aliasing
        using General::Iterate;
        using General::RoundSigDigits;
        using General::SafeDivide;
        using General::SolveRoot;
        using namespace OutputReportPredefined;
        using PlantUtilities::InitComponentNodes;
        using PlantUtilities::RegisterPlantCompDesignFlow;
        using PlantUtilities::ScanPlantLoopsForObject;
        using namespace FaultsManager;
        using HVACControllers::GetControllerNameAndIndex;
        using SimAirServingZones::CheckWaterCoilIsOnAirLoop;

        // SUBROUTINE PARAMETER DEFINITIONS:
        Real64 const SmallNo(1.e-9); // SmallNo number in place of zero
        int const itmax(10);
        int const MaxIte(500); // Maximum number of iterations
        static std::string const RoutineName("InitWaterCoil");

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int tempCoilNum;                   // loop variable
        Real64 DesInletAirEnth;            // Entering air enthalpy at rating (J/kg)
        Real64 DesOutletAirEnth;           // Leaving air enthalpy at rating(J/kg)
        Real64 CapacitanceAir;             // Air-side capacity rate(W/C)

        int AirInletNode;
        int WaterInletNode;
        int WaterOutletNode;

        //static Array1D<Real64> DesCpAir;        // CpAir at Design Inlet Air Temp
        //static Array1D<Real64> DesUARangeCheck; // Value for range check based on Design Inlet Air Humidity Ratio
        /////////// hoisted into namespace InitWaterCoilOneTimeFlag
        //static bool MyOneTimeFlag( true );
        /////////////////////////
        static Array1D_bool MyEnvrnFlag;
        static Array1D_bool MyCoilReportFlag;
        static Array1D_bool PlantLoopScanFlag;

        //static Array1D<Real64> CoefSeries(5); // Tuned Changed to static: High call count: Set before use
        //Real64 FinDiamVar;
        //Real64 TubeToFinDiamRatio;

        Real64 CpAirStd; // specific heat of air at std conditions
        //int SolFla;      // Flag of solver
        //Real64 UA0;      // lower bound for UA
        //Real64 UA1;      // upper bound for UA
        //Real64 UA;
        //static Array1D<Real64> Par(4); // Tuned Changed to static: High call count: Set before use

        //static bool NoSatCurveIntersect(false); // TRUE if failed to find appatatus dew-point
        //static bool BelowInletWaterTemp(false); // TRUE if apparatus dew-point below design inlet water temperature
        //static bool CBFTooLarge(false);         // TRUE if the coil bypass factor is unrealistically large
        //static bool NoExitCondReset(false);     // TRUE if exit condition reset is not to be done

        static Real64 RatedLatentCapacity(0.0); // latent cooling capacity at the rating point [W]
        static Real64 RatedSHR(0.0);            // sensible heat ratio at the rating point
        static Real64 CapacitanceWater(0.0);    // capacitance of the water stream [W/K]
        static Real64 CMin(0.0);                // minimum capacitance of 2 streams [W/K]
        static Real64 CoilEffectiveness(0.0);   // effectiveness of the coil (rated)
        static Real64 SurfaceArea(0.0);         // heat exchanger surface area, [m2]
        static Real64 UATotal(0.0);             // heat exchanger UA total, [W/C]
        static Array1D_bool RptCoilHeaderFlag(2, true);

        Real64 CpAirDes; // specific heat of air at design conditions
        Real64 DesSenCoilLoad;
        Real64 DesLatCoilLoad;

        Real64 Cp;  // local fluid specific heat
        Real64 rho; // local fluid density
        bool errFlag;
 

        // added variables for desiccant coil
        Real64 DesHdAvVt;
        Real64 Qlat;           // Coil latent load
        Real64 msi;            // Solution mass flow rate IN to this function(kg/s)
        Real64 Tsi;            // Solution temperature IN to this function (C)
        Real64 Xsi;            // Solution concentration IN to this function (weight fraction)
        Real64 Tso;            // Solution temperature IN to this function (C)
        Real64 ma;             // Air mass flow rate IN to this function(kg/s)
        Real64 Tai;            // Air dry bulb temperature IN to this function(C)
        Real64 Wai;            // Air Humidity Ratio IN to this funcation (C)
        Real64 Tao;            // Air dry bulb temperature OUT to this function(C)
        Real64 Wao;            // Air Humidity Ratio OUT to this funcation (C)
        

        // FLOW:
        if (InitWaterCoilOneTimeFlag) {
            // initialize the environment and sizing flags
            MyEnvrnFlag.allocate(NumWaterCoils);
            MySizeFlag.allocate(NumWaterCoils);
            CoilWarningOnceFlag.allocate(NumWaterCoils);
            //DesCpAir.allocate(NumWaterCoils);
            MyUAAndFlowCalcFlag.allocate(NumWaterCoils);
            MyCoilDesignFlag.allocate(NumWaterCoils);
            MyCoilReportFlag.allocate(NumWaterCoils);
            //DesUARangeCheck.allocate(NumWaterCoils);
            PlantLoopScanFlag.allocate(NumWaterCoils);

            //DesCpAir = 0.0;
            //DesUARangeCheck = 0.0;
            MyEnvrnFlag = true;
            MySizeFlag = true;
            CoilWarningOnceFlag = true;
            MyUAAndFlowCalcFlag = true;
            MyCoilDesignFlag = true;
            MyCoilReportFlag = true;
            InitWaterCoilOneTimeFlag = false;
            PlantLoopScanFlag = true;

            for (tempCoilNum = 1; tempCoilNum <= NumWaterCoils; ++tempCoilNum) {
                GetControllerNameAndIndex(state,
                    LiquidDesiccantCoil(tempCoilNum).WaterInletNodeNum, LiquidDesiccantCoil(tempCoilNum).ControllerName, LiquidDesiccantCoil(tempCoilNum).ControllerIndex, errFlag);
            }
        }

        if (WaterCoilControllerCheckOneTimeFlag && (DataHVACGlobals::GetAirPathDataDone)) {
            bool ErrorsFound = false;
            bool WaterCoilOnAirLoop = true;
            for (tempCoilNum = 1; tempCoilNum <= NumWaterCoils; ++tempCoilNum) {
                if (LiquidDesiccantCoil(tempCoilNum).ControllerIndex > 0) {
                    int CoilTypeNum(0);
                    std::string CompType;
                    std::string CompName = LiquidDesiccantCoil(tempCoilNum).Name;
                    if (LiquidDesiccantCoil(tempCoilNum).LiquidDesiccantCoilType_Num == LiquidDesiccantCoil::LiquidDesiccantCoil_Cooling) {
                        CoilTypeNum = SimAirServingZones::LiquidDesiccantCoil_Cooling;
                        CompType = cAllCoilTypes(DataHVACGlobals::Coil_CoolingLiquidDesiccant);
                    //} else if (LiquidDesiccantCoil(tempCoilNum).WaterCoilType_Num == LiquidDesiccantCoil::WaterCoil_SimpleHeating) {
                    //    CoilTypeNum = SimAirServingZones::WaterCoil_SimpleHeat;
                    //    CompType = cAllCoilTypes(DataHVACGlobals::Coil_HeatingWater);
                    }
                    WaterCoilOnAirLoop = true;
                    CheckWaterCoilIsOnAirLoop(state, CoilTypeNum, CompType, CompName, WaterCoilOnAirLoop);
                    if (!WaterCoilOnAirLoop) {
                        ShowContinueError("Controller:WaterCoil = " + LiquidDesiccantCoil(tempCoilNum).ControllerName + ". Invalid water controller entry.");
                        ErrorsFound = true;
                    }
                }
            }
            WaterCoilControllerCheckOneTimeFlag = false;
            if (ErrorsFound) {
                ShowFatalError("Program terminated for previous condition.");
            }
        }

        if (PlantLoopScanFlag(CoilNum) && allocated(PlantLoop)) {
            errFlag = false;
            ScanPlantLoopsForObject(state.dataBranchInputManager,
                                    LiquidDesiccantCoil(CoilNum).Name,
                                    LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType_Num,
                                    LiquidDesiccantCoil(CoilNum).WaterLoopNum,
                                    LiquidDesiccantCoil(CoilNum).WaterLoopSide,
                                    LiquidDesiccantCoil(CoilNum).WaterLoopBranchNum,
                                    LiquidDesiccantCoil(CoilNum).WaterLoopCompNum,
                                    errFlag,
                                    _,
                                    _,
                                    _,
                                    _,
                                    _);
            if (errFlag) {
                ShowFatalError("InitWaterCoil: Program terminated for previous conditions.");
            }
            PlantLoopScanFlag(CoilNum) = false;
        }
        if (!SysSizingCalc && MySizeFlag(CoilNum)) {
            // for each coil, do the sizing once.
            SizeLiquideDesiccantCoil(state, CoilNum);

            MySizeFlag(CoilNum) = false;
        }

        // Do the Begin Environment initializations
        if (BeginEnvrnFlag && MyEnvrnFlag(CoilNum)) {
            rho = GetDensityGlycol(PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidName,
                                   InitConvTemp,
                                   PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidIndex,
                                   RoutineName);
            // Initialize all report variables to a known state at beginning of simulation
           // LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilEnergy = 0.0;
            LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilEnergy = 0.0;
            LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilEnergy = 0.0;
            LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate = 0.0;
            LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate = 0.0;
            LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate = 0.0;

            // The rest of the one time initializations
            AirInletNode = LiquidDesiccantCoil(CoilNum).AirInletNodeNum;
            WaterInletNode = LiquidDesiccantCoil(CoilNum).WaterInletNodeNum;
            WaterOutletNode = LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum;

            //DesCpAir(CoilNum) = PsyCpAirFnW(0.0);
            //DesUARangeCheck(CoilNum) = (-1568.6 * LiquidDesiccantCoil(CoilNum).DesInletAirHumRat + 20.157);

            if (LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType == CoilType_Cooling) { // 'Cooling'
                Node(WaterInletNode).Temp = 5.0;

                Cp = GetSpecificHeatGlycol(PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidName,
                                           Node(WaterInletNode).Temp,
                                           PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidIndex,
                                           RoutineName);

                Node(WaterInletNode).Enthalpy = Cp * Node(WaterInletNode).Temp;
                Node(WaterInletNode).Quality = 0.0;
                Node(WaterInletNode).Press = 0.0;
                Node(WaterInletNode).HumRat = 0.0;
            }

            
            if (LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType == CoilType_Heating) { // 'Heating'
                Node(WaterInletNode).Temp = 60.0;

                Cp = GetSpecificHeatGlycol(PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidName,
                                           Node(WaterInletNode).Temp,
                                           PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidIndex,
                                           RoutineName);

                Node(WaterInletNode).Enthalpy = Cp * Node(WaterInletNode).Temp;
                Node(WaterInletNode).Quality = 0.0;
                Node(WaterInletNode).Press = 0.0;
                Node(WaterInletNode).HumRat = 0.0;
                MyUAAndFlowCalcFlag(CoilNum) = false;
                // fill values for variable UA
                CpAirStd = PsyCpAirFnW(0.0);
                LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate = StdRhoAir * LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate;
                LiquidDesiccantCoil(CoilNum).LiquidSideNominalConvect = LiquidDesiccantCoil(CoilNum).UACoil * (LiquidDesiccantCoil(CoilNum).RatioAirSideToWaterSideConvect + 1) /
                                                              LiquidDesiccantCoil(CoilNum).RatioAirSideToWaterSideConvect;
                LiquidDesiccantCoil(CoilNum).AirSideNominalConvect =
                    LiquidDesiccantCoil(CoilNum).RatioAirSideToWaterSideConvect * LiquidDesiccantCoil(CoilNum).LiquidSideNominalConvect;
            } else {
                MyUAAndFlowCalcFlag(CoilNum) = false;
            }
            

            LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate = rho * LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate;

            InitComponentNodes(0.0,
                               LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate,
                               LiquidDesiccantCoil(CoilNum).WaterInletNodeNum,
                               LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum,
                               LiquidDesiccantCoil(CoilNum).WaterLoopNum,
                               LiquidDesiccantCoil(CoilNum).WaterLoopSide,
                               LiquidDesiccantCoil(CoilNum).WaterLoopBranchNum,
                               LiquidDesiccantCoil(CoilNum).WaterLoopCompNum);


            // Calculation for Cooling Coil, The part between the '@@@' are design condition
            // and are calculated only once to calculate standard values for UAs and other physical parameters of
            // the cooling coil.
            // Basic Idea for UA:  Heat Transfer= UAenthalpybased*(Delta enthalpy), this is a necessity since the
            // coil may be Wet or Dry or Partially Wet-Dry, so latent effects are accounted for in this model while
            // calculating the UA. A fictitious specific heat is also defined to caculate the conventional UA.
            // On the air side, enthalpy capacity rate is the air mass flow rate,while on water side it is
            // enthalpy of saturated air at water temperature.
            
            
            //@@@ DESIGN CONDITION BEGIN HERE @@@

            // Check for zero design cooling capacity as specified by coil design inputs
            /*
            if (MyCoilDesignFlag(CoilNum) && (WaterCoil(CoilNum).WaterCoilModel == CoilModel_Cooling) &&
                (WaterCoil(CoilNum).DesAirVolFlowRate > 0.0) && (WaterCoil(CoilNum).MaxWaterMassFlowRate > 0.0)) {
                
                DesInletAirEnth = PsyHFnTdbW(WaterCoil(CoilNum).DesInletAirTemp, WaterCoil(CoilNum).DesInletAirHumRat);
                DesOutletAirEnth = PsyHFnTdbW(WaterCoil(CoilNum).DesOutletAirTemp, WaterCoil(CoilNum).DesOutletAirHumRat);
                DesSatEnthAtWaterInTemp =
                    PsyHFnTdbW(WaterCoil(CoilNum).DesInletWaterTemp, PsyWFnTdpPb(WaterCoil(CoilNum).DesInletWaterTemp, StdBaroPress));
                // check for dry coil
                DesHumRatAtWaterInTemp = PsyWFnTdbH(WaterCoil(CoilNum).DesInletWaterTemp, DesSatEnthAtWaterInTemp, RoutineName);
                if (DesHumRatAtWaterInTemp > WaterCoil(CoilNum).DesOutletAirHumRat &&
                    WaterCoil(CoilNum).DesOutletAirTemp > WaterCoil(CoilNum).DesInletWaterTemp) {
                    // if the design outlet air humrat is lower than the saturated air humrat at the design inlet water temp
                    // and the design outlet air temperature is higher than the design inlet water temp (i.e, cooling possible),
                    // move the design outlet air saturated enthalpy down (i.e., to Twaterin, Wair,out) to allow the coil to size.
                    DesSatEnthAtWaterInTemp = PsyHFnTdbW(WaterCoil(CoilNum).DesInletWaterTemp, WaterCoil(CoilNum).DesOutletAirHumRat) - 0.0001;
                }
                if (DesOutletAirEnth >= DesInletAirEnth || WaterCoil(CoilNum).DesInletWaterTemp >= WaterCoil(CoilNum).DesInletAirTemp) {
                    ShowWarningError("The design cooling capacity is zero for Coil:Cooling:Water " + WaterCoil(CoilNum).Name);
                    ShowContinueError("  The maximum water flow rate for this coil will be set to zero and the coil will do no cooling.");
                    ShowContinueError("  Check the following coil design inputs for problems: Tair,in = " +
                                      RoundSigDigits(WaterCoil(CoilNum).DesInletAirTemp, 4));
                    ShowContinueError("                                                       Wair,in = " +
                                      RoundSigDigits(WaterCoil(CoilNum).DesInletAirHumRat, 6));
                    ShowContinueError("                                                       Twater,in = " +
                                      RoundSigDigits(WaterCoil(CoilNum).DesInletWaterTemp, 4));
                    ShowContinueError("                                                       Tair,out = " +
                                      RoundSigDigits(WaterCoil(CoilNum).DesOutletAirTemp, 4));
                    ShowContinueError("                                                       Wair,out = " +
                                      RoundSigDigits(WaterCoil(CoilNum).DesOutletAirHumRat, 6));
                    WaterCoil(CoilNum).MaxWaterVolFlowRate = 0.0;
                    WaterCoil(CoilNum).MaxWaterMassFlowRate = 0.0;
                }
            }
            */

            
            if (MyCoilDesignFlag(CoilNum) && (LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilModel == CoilModel_Cooling) &&
                (LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate > 0.0) && (LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate > 0.0)) { // 'Cooling'

                MyCoilDesignFlag(CoilNum) = false;
                //NoSatCurveIntersect = false;
                //BelowInletWaterTemp = false;
                //CBFTooLarge = false;
                //NoExitCondReset = false;

                /*
                for (Ipass = 1; Ipass <= 2; ++Ipass) {
                    if (Ipass == 2) {
                        if (!NoSatCurveIntersect && !BelowInletWaterTemp && !CBFTooLarge) {
                            goto Inlet_Conditions_Loop_exit; // coil UA calcs OK
                        } else {
                            ShowWarningError("In calculating the design coil UA for Coil:Cooling:Water " + WaterCoil(CoilNum).Name);
                            if (NoSatCurveIntersect) {
                                ShowContinueError("no apparatus dew-point can be found for the initial entering and leaving conditions;");
                            }
                            if (BelowInletWaterTemp) {
                                ShowContinueError("the apparatus dew-point is below the coil design inlet water temperature;");
                            }
                            if (CBFTooLarge) {
                                ShowContinueError("the coil bypass factor is unrealistically large;");
                            }
                            if (!NoExitCondReset) {
                                ShowContinueError("the coil outlet design conditions will be changed to correct the problem.");
                            }
                            ShowContinueError("The initial design conditions are: Tair,in = " +
                                              RoundSigDigits(WaterCoil(CoilNum).DesInletAirTemp, 4));
                            ShowContinueError("                                   Wair,in = " +
                                              RoundSigDigits(WaterCoil(CoilNum).DesInletAirHumRat, 6));
                            ShowContinueError("                                   Twater,in = " +
                                              RoundSigDigits(WaterCoil(CoilNum).DesInletWaterTemp, 4));
                            ShowContinueError("                                   Tair,out = " +
                                              RoundSigDigits(WaterCoil(CoilNum).DesOutletAirTemp, 4));
                            ShowContinueError("                                   Wair,out = " +
                                              RoundSigDigits(WaterCoil(CoilNum).DesOutletAirHumRat, 6));
                            if (!NoExitCondReset) {
                                ShowContinueError("The revised design conditions are: Tair,out = " + RoundSigDigits(TOutNew, 4));
                                ShowContinueError("                                   Wair,out = " + RoundSigDigits(WOutNew, 6));
                                WaterCoil(CoilNum).DesOutletAirHumRat = WOutNew;
                                WaterCoil(CoilNum).DesOutletAirTemp = TOutNew;
                                // update outlet air conditions used for sizing
                                std::string CompType;

                                    CompType = cAllCoilTypes(Coil_CoolingWater);
       
                                coilSelectionReportObj->setCoilLvgAirTemp(WaterCoil(CoilNum).Name, CompType, TOutNew);
                                coilSelectionReportObj->setCoilLvgAirHumRat(WaterCoil(CoilNum).Name, CompType, WOutNew);
                                // end update outlet air conditions used for sizing
                            }
                        }
                    }

                    // Volume flow rate being converted to mass flow rate for water
                    WaterCoil(CoilNum).DesAirMassFlowRate = StdRhoAir * WaterCoil(CoilNum).DesAirVolFlowRate;

                    // Enthalpy of Air at Inlet design conditions
                    DesInletAirEnth = PsyHFnTdbW(WaterCoil(CoilNum).DesInletAirTemp, WaterCoil(CoilNum).DesInletAirHumRat);

                    // Enthalpy of Air at outlet at design conditions
                    DesOutletAirEnth = PsyHFnTdbW(WaterCoil(CoilNum).DesOutletAirTemp, WaterCoil(CoilNum).DesOutletAirHumRat);

                    // already calculated above and possibly reset if dry coil
                    //        ! Enthalpy of Water at Inlet design conditions
                    //        DesSatEnthAtWaterInTemp =PsyHFnTdbW(WaterCoil(CoilNum)%DesInletWaterTemp, &
                    //                                             PsyWFnTdpPb(WaterCoil(CoilNum)%DesInletWaterTemp,StdBaroPress))

                    // Total Coil Load from Inlet and Outlet Air States (which include fan heat as appropriate).
                    WaterCoil(CoilNum).DesTotWaterCoilLoad = WaterCoil(CoilNum).DesAirMassFlowRate * (DesInletAirEnth - DesOutletAirEnth);

                    // Enthalpy of Water at Intlet design conditions
                    Cp = GetSpecificHeatGlycol(PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidName,
                                               WaterCoil(CoilNum).DesInletWaterTemp,
                                               PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidIndex,
                                               RoutineName);

                    DesOutletWaterTemp = WaterCoil(CoilNum).DesInletWaterTemp +
                                         WaterCoil(CoilNum).DesTotWaterCoilLoad / (WaterCoil(CoilNum).MaxWaterMassFlowRate * Cp);

                    DesSatEnthAtWaterOutTemp = PsyHFnTdbW(DesOutletWaterTemp, PsyWFnTdpPb(DesOutletWaterTemp, StdBaroPress));
                    DesEnthAtWaterOutTempAirInHumRat = PsyHFnTdbW(DesOutletWaterTemp, WaterCoil(CoilNum).DesInletAirHumRat);
                    DesEnthWaterOut = min(DesSatEnthAtWaterOutTemp, DesEnthAtWaterOutTempAirInHumRat);

                    // dry coil test
                    if (WaterCoil(CoilNum).DesOutletAirHumRat < WaterCoil(CoilNum).DesInletAirHumRat &&
                        DesHumRatAtWaterInTemp < WaterCoil(CoilNum).DesInletAirHumRat) { // wet coil

                        // Calculations for BYPASS FACTOR at design conditions
                        // Calculate "slope" of temperature vs. humidity ratio between entering and leaving states
                        SlopeTempVsHumRatio = (WaterCoil(CoilNum).DesInletAirTemp - WaterCoil(CoilNum).DesOutletAirTemp) /
                                              max((WaterCoil(CoilNum).DesInletAirHumRat - WaterCoil(CoilNum).DesOutletAirHumRat), SmallNo);

                        // Initialize iteration parameters
                        DesAirTempApparatusDewPt = PsyTdpFnWPb(WaterCoil(CoilNum).DesOutletAirHumRat, OutBaroPress);

                        // Iterating to calculate Apparatus Dew Point Temperature at Design Conditions
                        for (iter = 1; iter <= itmax; ++iter) {

                            // Calculate apparatus dewpoint and compare with predicted value
                            // using entering conditions and SlopeTempVsHumRatio
                            DesAirHumRatApparatusDewPt = PsyWFnTdpPb(DesAirTempApparatusDewPt, OutBaroPress);

                            // Initial Estimate for apparatus Dew Point Temperature
                            TempApparatusDewPtEstimate = WaterCoil(CoilNum).DesInletAirTemp -
                                                         SlopeTempVsHumRatio * (WaterCoil(CoilNum).DesInletAirHumRat - DesAirHumRatApparatusDewPt);

                            // Iterating to calculate Apparatus Dew Point Temperature at Design Condition
                            error = DesAirTempApparatusDewPt - TempApparatusDewPtEstimate;
                            Iterate(ResultX, 0.01, DesAirTempApparatusDewPt, error, X1, Y1, iter, icvg);
                            DesAirTempApparatusDewPt = ResultX;

                            // If converged, exit loop
                            if (icvg == 1) {
                                goto App_DewPoint_Loop1_exit;
                            }

                            // If not converged due to low Humidity Ratio approximate value at outlet conditions
                            if (iter == itmax) {
                                NoSatCurveIntersect = true;
                                DesAirTempApparatusDewPt = PsyTdpFnWPb(WaterCoil(CoilNum).DesOutletAirHumRat, OutBaroPress);
                                DesAirHumRatApparatusDewPt = PsyWFnTdpPb(DesAirTempApparatusDewPt, OutBaroPress);
                                goto App_DewPoint_Loop1_exit;
                            }

                            // End of Loop for Iteration
                        }
                    App_DewPoint_Loop1_exit:;

                        // Air enthalpy at apparatus dew point at design conditions
                        DesAirApparatusDewPtEnth = PsyHFnTdbW(DesAirTempApparatusDewPt, DesAirHumRatApparatusDewPt);

                        // Calculate bypass factor from enthalpies calculated above.
                        DesBypassFactor = (DesOutletAirEnth - DesAirApparatusDewPtEnth) / (DesInletAirEnth - DesAirApparatusDewPtEnth);

                        // Check for bypass factor for unsuitable value. Note that bypass factor is never used in the coil calculation
                        if ((DesBypassFactor > 0.5) || (DesBypassFactor < 0.0)) {
                            CBFTooLarge = true;
                            DesBypassFactor = 0.37;
                        }

                        if (DesEnthWaterOut > DesInletAirEnth) {
                            ShowWarningError("In calculating the design coil UA for Coil:Cooling:Water " + WaterCoil(CoilNum).Name);
                            ShowContinueError("the outlet chilled water design enthalpy is greater than the inlet air design enthalpy.");
                            ShowContinueError("To correct this condition the design chilled water flow rate will be increased from " +
                                              RoundSigDigits(WaterCoil(CoilNum).MaxWaterVolFlowRate, 5));
                            EnthCorrFrac = (DesEnthWaterOut - DesInletAirEnth) / (DesEnthWaterOut - DesSatEnthAtWaterInTemp);
                            WaterCoil(CoilNum).MaxWaterVolFlowRate *= (1.0 + 2.0 * EnthCorrFrac);
                            ShowContinueError("to " + RoundSigDigits(WaterCoil(CoilNum).MaxWaterVolFlowRate, 5) + " m3/s");
                            WaterCoil(CoilNum).MaxWaterMassFlowRate = rho * WaterCoil(CoilNum).MaxWaterVolFlowRate;
                            DesOutletWaterTemp = WaterCoil(CoilNum).DesInletWaterTemp +
                                                 WaterCoil(CoilNum).DesTotWaterCoilLoad / (WaterCoil(CoilNum).MaxWaterMassFlowRate * Cp);
                            DesSatEnthAtWaterOutTemp = PsyHFnTdbW(DesOutletWaterTemp, PsyWFnTdpPb(DesOutletWaterTemp, StdBaroPress));
                            DesEnthAtWaterOutTempAirInHumRat = PsyHFnTdbW(DesOutletWaterTemp, WaterCoil(CoilNum).DesInletAirHumRat);
                            DesEnthWaterOut = min(DesSatEnthAtWaterOutTemp, DesEnthAtWaterOutTempAirInHumRat);
                        }



                        // Determine air-side coefficient, UACoilExternal, assuming that the
                        // surface temperature is at the apparatus dewpoint temperature
                        if (DesAirApparatusDewPtEnth <= DesSatEnthAtWaterInTemp) BelowInletWaterTemp = true;
                        if ((DesInletAirEnth - DesEnthWaterOut) > SmallNo && (DesOutletAirEnth - DesSatEnthAtWaterInTemp) > SmallNo) {
                            LogMeanEnthDiff = ((DesInletAirEnth - DesEnthWaterOut) - (DesOutletAirEnth - DesSatEnthAtWaterInTemp)) /
                                              std::log((DesInletAirEnth - DesEnthWaterOut) / (DesOutletAirEnth - DesSatEnthAtWaterInTemp));
                        } else {
                            LogMeanEnthDiff = 2000.0; // UA will be 1/2 the design coil load
                        }
                        DesUACoilExternalEnth = WaterCoil(CoilNum).DesTotWaterCoilLoad / LogMeanEnthDiff;

                        WaterCoil(CoilNum).UACoilExternal = DesUACoilExternalEnth * PsyCpAirFnW(WaterCoil(CoilNum).DesInletAirHumRat);

                        if (Ipass == 1 && (NoSatCurveIntersect || CBFTooLarge || BelowInletWaterTemp)) {
                            // reset outlet conditions to 90% relative humidity at the same outlet enthalpy
                            TOutNew = TdbFnHRhPb(DesOutletAirEnth, 0.9, StdBaroPress);
                            WOutNew = PsyWFnTdbH(TOutNew, DesOutletAirEnth);
                            if (WOutNew >= WaterCoil(CoilNum).DesInletAirHumRat || TOutNew > WaterCoil(CoilNum).DesOutletAirTemp) {
                                NoExitCondReset = true;
                            }
                            goto Inlet_Conditions_Loop_loop;
                        }

                        WaterCoil(CoilNum).UACoilInternal = WaterCoil(CoilNum).UACoilExternal * 3.30;
                        // Overall heat transfer coefficient
                        WaterCoil(CoilNum).UACoilTotal = 1.0 / (1.0 / WaterCoil(CoilNum).UACoilExternal + 1.0 / WaterCoil(CoilNum).UACoilInternal);

                    } else { // dry coil

                        if (DesOutletWaterTemp > WaterCoil(CoilNum).DesInletAirTemp) {
                            ShowWarningError("In calculating the design coil UA for Coil:Cooling:Water " + WaterCoil(CoilNum).Name);
                            ShowContinueError("the outlet chilled water design temperature is greater than the inlet air design temperature.");
                            ShowContinueError("To correct this condition the design chilled water flow rate will be increased from " +
                                              RoundSigDigits(WaterCoil(CoilNum).MaxWaterVolFlowRate, 5));
                            TempCorrFrac = (DesOutletWaterTemp - WaterCoil(CoilNum).DesInletAirTemp) /
                                           (DesOutletWaterTemp - WaterCoil(CoilNum).DesInletWaterTemp);
                            WaterCoil(CoilNum).MaxWaterVolFlowRate *= (1.0 + 2.0 * TempCorrFrac);
                            ShowContinueError("to " + RoundSigDigits(WaterCoil(CoilNum).MaxWaterVolFlowRate, 5) + " m3/s");
                            WaterCoil(CoilNum).MaxWaterMassFlowRate = rho * WaterCoil(CoilNum).MaxWaterVolFlowRate;
                            DesOutletWaterTemp = WaterCoil(CoilNum).DesInletWaterTemp +
                                                 WaterCoil(CoilNum).DesTotWaterCoilLoad / (WaterCoil(CoilNum).MaxWaterMassFlowRate * Cp);
                        }

                        if ((WaterCoil(CoilNum).DesInletAirTemp - DesOutletWaterTemp) > SmallNo &&
                            (WaterCoil(CoilNum).DesOutletAirTemp - WaterCoil(CoilNum).DesInletWaterTemp) > SmallNo) {
                            LogMeanTempDiff = ((WaterCoil(CoilNum).DesInletAirTemp - DesOutletWaterTemp) -
                                               (WaterCoil(CoilNum).DesOutletAirTemp - WaterCoil(CoilNum).DesInletWaterTemp)) /
                                              std::log((WaterCoil(CoilNum).DesInletAirTemp - DesOutletWaterTemp) /
                                                       (WaterCoil(CoilNum).DesOutletAirTemp - WaterCoil(CoilNum).DesInletWaterTemp));
                            WaterCoil(CoilNum).UACoilExternal = WaterCoil(CoilNum).DesTotWaterCoilLoad / LogMeanTempDiff;
                        } else {
                            WaterCoil(CoilNum).UACoilExternal = WaterCoil(CoilNum).DesTotWaterCoilLoad / 2.0; // make the UA large
                        }
                        WaterCoil(CoilNum).UACoilInternal = WaterCoil(CoilNum).UACoilExternal * 3.30;
                        // Overall heat transfer coefficient
                        WaterCoil(CoilNum).UACoilTotal = 1.0 / (1.0 / WaterCoil(CoilNum).UACoilExternal + 1.0 / WaterCoil(CoilNum).UACoilInternal);
                        goto Inlet_Conditions_Loop_exit;
                    }

                Inlet_Conditions_Loop_loop:;
                }
            Inlet_Conditions_Loop_exit:;
                */
                

                /*
                // estimate the heat external transfer surface area using typical design over all U value
                WaterCoil(CoilNum).TotCoilOutsideSurfArea = EstimateHEXSurfaceArea(CoilNum);
                // calculate internal and external "UA per external surface area"
                WaterCoil(CoilNum).UACoilInternalPerUnitArea = WaterCoil(CoilNum).UACoilInternal / WaterCoil(CoilNum).TotCoilOutsideSurfArea;
                WaterCoil(CoilNum).UAWetExtPerUnitArea = WaterCoil(CoilNum).UACoilExternal / WaterCoil(CoilNum).TotCoilOutsideSurfArea;
                // approximate the dry UA as 1.0 times wet UA
                WaterCoil(CoilNum).UADryExtPerUnitArea = WaterCoil(CoilNum).UAWetExtPerUnitArea;

                // Now use SolveRoot to "invert" the cooling coil model to obtain the UA given the specified design inlet and outlet conditions
                // Note that the UAs we have obtained so far are rough estimates that are the starting points for the the following iterative
                //   calulation of the actual UAs.
                Par(1) = WaterCoil(CoilNum).DesTotWaterCoilLoad;
                Par(2) = double(CoilNum);
                Par(3) = double(ContFanCycCoil); // fan operating mode
                Par(4) = 1.0;                    // part-load ratio
                WaterCoil(CoilNum).InletAirTemp = WaterCoil(CoilNum).DesInletAirTemp;
                WaterCoil(CoilNum).InletAirHumRat = WaterCoil(CoilNum).DesInletAirHumRat;
                WaterCoil(CoilNum).InletWaterTemp = WaterCoil(CoilNum).DesInletWaterTemp;
                WaterCoil(CoilNum).InletWaterMassFlowRate = rho * WaterCoil(CoilNum).MaxWaterVolFlowRate;
                WaterCoil(CoilNum).InletAirMassFlowRate = WaterCoil(CoilNum).DesAirMassFlowRate;
                // set the lower and upper limits on the UA
                UA0 = 0.1 * WaterCoil(CoilNum).UACoilExternal;
                UA1 = 10.0 * WaterCoil(CoilNum).UACoilExternal;
                // Invert the simple cooling coil model: given the design inlet conditions and the design load, find the design UA
                SolveRoot(0.001, MaxIte, SolFla, UA, SimpleCoolingCoilUAResidual, UA0, UA1, Par);
                // if the numerical inversion failed, issue error messages.
                if (SolFla == -1) {
                    ShowSevereError("Calculation of cooling coil design UA failed for coil " + WaterCoil(CoilNum).Name);
                    ShowContinueError("  Iteration limit exceeded in calculating coil UA");
                    // CALL ShowFatalError('Preceeding error causes program termination')
                    WaterCoil(CoilNum).UACoilExternal = UA0 * 10.0;
                    WaterCoil(CoilNum).UACoilInternal = WaterCoil(CoilNum).UACoilExternal * 3.3;
                    WaterCoil(CoilNum).UACoilTotal = 1.0 / (1.0 / WaterCoil(CoilNum).UACoilExternal + 1.0 / WaterCoil(CoilNum).UACoilInternal);
                    WaterCoil(CoilNum).TotCoilOutsideSurfArea = EstimateHEXSurfaceArea(CoilNum);
                    WaterCoil(CoilNum).UACoilInternalPerUnitArea = WaterCoil(CoilNum).UACoilInternal / WaterCoil(CoilNum).TotCoilOutsideSurfArea;
                    WaterCoil(CoilNum).UAWetExtPerUnitArea = WaterCoil(CoilNum).UACoilExternal / WaterCoil(CoilNum).TotCoilOutsideSurfArea;
                    WaterCoil(CoilNum).UADryExtPerUnitArea = WaterCoil(CoilNum).UAWetExtPerUnitArea;
                    ShowContinueError(" Coil design UA set to " + RoundSigDigits(WaterCoil(CoilNum).UACoilTotal, 6) + " [W/C]");
                } else if (SolFla == -2) {
                    ShowSevereError("Calculation of cooling coil design UA failed for coil " + WaterCoil(CoilNum).Name);
                    ShowContinueError("  Bad starting values for UA");
                    // CALL ShowFatalError('Preceeding error causes program termination')
                    WaterCoil(CoilNum).UACoilExternal = UA0 * 10.0;
                    WaterCoil(CoilNum).UACoilInternal = WaterCoil(CoilNum).UACoilExternal * 3.3;
                    WaterCoil(CoilNum).UACoilTotal = 1.0 / (1.0 / WaterCoil(CoilNum).UACoilExternal + 1.0 / WaterCoil(CoilNum).UACoilInternal);
                    WaterCoil(CoilNum).TotCoilOutsideSurfArea = EstimateHEXSurfaceArea(CoilNum);
                    WaterCoil(CoilNum).UACoilInternalPerUnitArea = WaterCoil(CoilNum).UACoilInternal / WaterCoil(CoilNum).TotCoilOutsideSurfArea;
                    WaterCoil(CoilNum).UAWetExtPerUnitArea = WaterCoil(CoilNum).UACoilExternal / WaterCoil(CoilNum).TotCoilOutsideSurfArea;
                    WaterCoil(CoilNum).UADryExtPerUnitArea = WaterCoil(CoilNum).UAWetExtPerUnitArea;
                    ShowContinueError(" Coil design UA set to " + RoundSigDigits(WaterCoil(CoilNum).UACoilTotal, 6) + " [W/C]");
                }

                // cooling coil surface area
                SurfaceArea = WaterCoil(CoilNum).TotCoilOutsideSurfArea;

                // cooling coil overall UA value
                UATotal = WaterCoil(CoilNum).UACoilTotal;

                // save the design internal and external UAs
                WaterCoil(CoilNum).UACoilExternalDes = WaterCoil(CoilNum).UACoilExternal;
                WaterCoil(CoilNum).UACoilInternalDes = WaterCoil(CoilNum).UACoilInternal;
                */

            
                // Caculate the liquid desiccant coil HdAvVt at design conditions
                
                // Enthalpy of Air at Inlet design conditions
                DesInletAirEnth = PsyHFnTdbW(LiquidDesiccantCoil(CoilNum).DesInletAirTemp, LiquidDesiccantCoil(CoilNum).DesInletAirHumRat);

                // Enthalpy of Air at outlet at design conditions
                DesOutletAirEnth = PsyHFnTdbW(LiquidDesiccantCoil(CoilNum).DesOutletAirTemp, LiquidDesiccantCoil(CoilNum).DesOutletAirHumRat);

                // Total Coil Load from Inlet and Outlet Air States (which include fan heat as appropriate).
                LiquidDesiccantCoil(CoilNum).DesTotWaterCoilLoad = LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate * (DesInletAirEnth - DesOutletAirEnth);

                CpAirDes = PsyCpAirFnW(LiquidDesiccantCoil(CoilNum).DesInletAirHumRat);
                DesSenCoilLoad = LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate * CpAirDes * (LiquidDesiccantCoil(CoilNum).DesInletAirTemp - LiquidDesiccantCoil(CoilNum).DesOutletAirTemp);
                DesLatCoilLoad = LiquidDesiccantCoil(CoilNum).DesTotWaterCoilLoad - DesSenCoilLoad;
                
                Qlat = DesLatCoilLoad;
                msi = LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate;
                Tsi = LiquidDesiccantCoil(CoilNum).DesInletWaterTemp;
                Xsi = LiquidDesiccantCoil(CoilNum).DesInletSolnConcentration;
                ma = LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate;
                Tai = LiquidDesiccantCoil(CoilNum).DesInletAirTemp;
                Wai = LiquidDesiccantCoil(CoilNum).DesInletAirHumRat;
                Tao = LiquidDesiccantCoil(CoilNum).DesOutletAirTemp;
                Wao = LiquidDesiccantCoil(CoilNum).DesOutletAirHumRat;
                DesHdAvVt = CalculateDesHdAvVt(Qlat, // Coil latent load
                                 msi,  // Solution mass flow rate IN to this function(kg/s)
                                 Tsi,  // Solution temperature IN to this function (C)
                                 Xsi,  // Solution concentration IN to this function (weight fraction)
                                 ma,   // Air mass flow rate IN to this function(kg/s)
                                 Tai,  // Air dry bulb temperature IN to this function(C)
                                 Wai,  // Air Humidity Ratio IN to this funcation (C)
                                 Tao,  // Air dry bulb temperature OUT to this function(C)
                                 Wao); // Air Humidity Ratio OUT to this funcation (C)


                LiquidDesiccantCoil(CoilNum).HdAvVt = DesHdAvVt;
                
                
                // %%%%%%%% add code here %%%%%%%%%%%%%%%%%%%%%%%%%%%
                //LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate = 1.50;
                //LiquidDesiccantCoil(CoilNum).DesTotWaterCoilLoad = 36984;
                //LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate = 0.00132;
                //LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate = 1.32;
                LiquidDesiccantCoil(CoilNum).UACoilExternal = 2989; // make the UA large
                LiquidDesiccantCoil(CoilNum).UACoilInternal = 9864;
                LiquidDesiccantCoil(CoilNum).UACoilTotal = 1.0 / (1.0 / LiquidDesiccantCoil(CoilNum).UACoilExternal + 1.0 / LiquidDesiccantCoil(CoilNum).UACoilInternal);
            
                LiquidDesiccantCoil(CoilNum).TotCoilOutsideSurfArea = 23.3;
                // calculate internal and external "UA per external surface area"
                LiquidDesiccantCoil(CoilNum).UACoilInternalPerUnitArea = LiquidDesiccantCoil(CoilNum).UACoilInternal / LiquidDesiccantCoil(CoilNum).TotCoilOutsideSurfArea;
                LiquidDesiccantCoil(CoilNum).UAWetExtPerUnitArea = LiquidDesiccantCoil(CoilNum).UACoilExternal / LiquidDesiccantCoil(CoilNum).TotCoilOutsideSurfArea;
                // approximate the dry UA as 1.0 times wet UA
                LiquidDesiccantCoil(CoilNum).UADryExtPerUnitArea = LiquidDesiccantCoil(CoilNum).UAWetExtPerUnitArea;
            
                LiquidDesiccantCoil(CoilNum).UACoilExternalDes = LiquidDesiccantCoil(CoilNum).UACoilExternal;
                LiquidDesiccantCoil(CoilNum).UACoilInternalDes = LiquidDesiccantCoil(CoilNum).UACoilInternal;
                // %%%%%% add code end %%%%%%%%%%%%%%%%%%%%%%%%%%%
                

            } // end of if (MyCoilDesignFlag(CoilNum) &&
            
            //@@@@ DESIGN CONDITION END HERE @@@@

            // Calculate rated Total, latent, sensible capacity, SHR, effectiveness
            /*
            if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_SimpleHeating) {
                WaterCoil(CoilNum).InletAirTemp = 16.6;
                WaterCoil(CoilNum).InletAirHumRat = PsyWFnTdbRhPb(16.6, 0.5, StdBaroPress, RoutineName);
                WaterCoil(CoilNum).InletWaterTemp = 82.2;
            } else {
                WaterCoil(CoilNum).InletAirTemp = 26.67;
                WaterCoil(CoilNum).InletAirHumRat = PsyWFnTdbTwbPb(26.67, 19.44, StdBaroPress, RoutineName);
                WaterCoil(CoilNum).InletWaterTemp = 6.67;
            }
            WaterCoil(CoilNum).InletAirEnthalpy = PsyHFnTdbW(WaterCoil(CoilNum).InletAirTemp, WaterCoil(CoilNum).InletAirHumRat);
            WaterCoil(CoilNum).InletWaterMassFlowRate = WaterCoil(CoilNum).MaxWaterMassFlowRate;
            WaterCoil(CoilNum).InletAirMassFlowRate = StdRhoAir * WaterCoil(CoilNum).DesAirVolFlowRate;
            CapacitanceAir = WaterCoil(CoilNum).InletAirMassFlowRate * PsyCpAirFnW(WaterCoil(CoilNum).InletAirHumRat);

            Cp = GetSpecificHeatGlycol(PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidName,
                                       WaterCoil(CoilNum).InletWaterTemp,
                                       PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidIndex,
                                       RoutineName);

            CapacitanceWater = WaterCoil(CoilNum).InletWaterMassFlowRate * Cp;
            CMin = min(CapacitanceAir, CapacitanceWater);
            if (CMin > 0.0) {
                if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_Cooling) {
                    CoolingCoil(CoilNum, FirstHVACIteration, DesignCalc, ContFanCycCoil, 1.0);
                    CoilEffectiveness = (WaterCoil(CoilNum).InletAirTemp - WaterCoil(CoilNum).OutletAirTemp) /
                                        (WaterCoil(CoilNum).InletAirTemp - WaterCoil(CoilNum).InletWaterTemp) * (CapacitanceAir / CMin);
                    RatedLatentCapacity = WaterCoil(CoilNum).TotWaterCoolingCoilRate - WaterCoil(CoilNum).SenWaterCoolingCoilRate;
                    RatedSHR = WaterCoil(CoilNum).SenWaterCoolingCoilRate / WaterCoil(CoilNum).TotWaterCoolingCoilRate;
             //   } else if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_DetFlatFinCooling) {
             //       CalcDetailFlatFinCoolingCoil(CoilNum, DesignCalc, ContFanCycCoil, 1.0);
             //       CoilEffectiveness = (WaterCoil(CoilNum).InletAirTemp - WaterCoil(CoilNum).OutletAirTemp) /
             //                           (WaterCoil(CoilNum).InletAirTemp - WaterCoil(CoilNum).InletWaterTemp) * (CapacitanceAir / CMin);
             //       RatedLatentCapacity = WaterCoil(CoilNum).TotWaterCoolingCoilRate - WaterCoil(CoilNum).SenWaterCoolingCoilRate;
             //       RatedSHR = WaterCoil(CoilNum).SenWaterCoolingCoilRate / WaterCoil(CoilNum).TotWaterCoolingCoilRate;
                } else if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_SimpleHeating) {
                    CalcSimpleHeatingCoil(CoilNum, ContFanCycCoil, 1.0, DesignCalc);
                    CoilEffectiveness = (WaterCoil(CoilNum).OutletAirTemp - WaterCoil(CoilNum).InletAirTemp) /
                                        (WaterCoil(CoilNum).InletWaterTemp - WaterCoil(CoilNum).InletAirTemp) * (CapacitanceAir / CMin);
                }
            } else {
                CoilEffectiveness = 0.0;
                WaterCoil(CoilNum).TotWaterHeatingCoilRate = 0.0;
                WaterCoil(CoilNum).TotWaterCoolingCoilRate = 0.0;
                WaterCoil(CoilNum).SenWaterCoolingCoilRate = 0.0;
                RatedLatentCapacity = 0.0;
                RatedSHR = 0.0;
            }
            */

            MyEnvrnFlag(CoilNum) = false;

        } // End If for the Begin Environment initializations

        if (!BeginEnvrnFlag) {
            MyEnvrnFlag(CoilNum) = true;
        }

        if (!DoingSizing) {
            if (MyCoilReportFlag(CoilNum)) {
                // create predefined report entries
                MyCoilReportFlag(CoilNum) = false;
                {
                    auto const SELECT_CASE_var(LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType_Num);
                    /*
                    if (SELECT_CASE_var == WaterCoil_SimpleHeating) {
                        if (RptCoilHeaderFlag(1)) {
                            print(state.outputFiles.eio, "{}", "! <Water Heating Coil Capacity Information>,Component Type,Name,Nominal Total Capacity {W}\n");
                            RptCoilHeaderFlag(1) = false;
                        }
                        PreDefTableEntry(pdchHeatCoilType, LiquidDesiccantCoil(CoilNum).Name, "Coil:Heating:Water");
                        PreDefTableEntry(pdchHeatCoilDesCap, LiquidDesiccantCoil(CoilNum).Name, LiquidDesiccantCoil(CoilNum).DesWaterHeatingCoilRate);
                        PreDefTableEntry(pdchHeatCoilNomCap, LiquidDesiccantCoil(CoilNum).Name, LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate);
                        PreDefTableEntry(pdchHeatCoilNomEff, LiquidDesiccantCoil(CoilNum).Name, "-");
                        addFootNoteSubTable(
                            pdstHeatCoil,
                            "Nominal values are gross at rated conditions, i.e., the supply air fan heat and electric power NOT accounted for.");
                        print(state.outputFiles.eio,
                              "{},{},{:.2R}\n",
                              "Water Heating Coil Capacity Information,Coil:Heating:Water",
                              LiquidDesiccantCoil(CoilNum).Name,
                              LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate);
                        coilSelectionReportObj->setCoilAirFlow(LiquidDesiccantCoil(CoilNum).Name,
                                                               "Coil:Heating:Water",
                                                               LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate,
                                                               LiquidDesiccantCoil(CoilNum).RequestingAutoSize);
                        coilSelectionReportObj->setCoilWaterHeaterCapacityNodeNums(LiquidDesiccantCoil(CoilNum).Name,
                                                                                   "Coil:Heating:Water",
                                                                                   LiquidDesiccantCoil(CoilNum).DesWaterHeatingCoilRate,
                                                                                   LiquidDesiccantCoil(CoilNum).RequestingAutoSize,
                                                                                   LiquidDesiccantCoil(CoilNum).WaterInletNodeNum,
                                                                                   LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum,
                                                                                   LiquidDesiccantCoil(CoilNum).WaterLoopNum); // coil report
                    } else if (SELECT_CASE_var == LiquidDesiccantCoil_Cooling) {
                        */

                        if (RptCoilHeaderFlag(2)) {
                            print(state.outputFiles.eio,
                                  "{}\n",
                                  "! <Water Cooling Coil Capacity Information>,Component Type,Name,Nominal Total "
                                  "Capacity {W},Nominal Sensible Capacity {W},Nominal Latent Capacity {W},Nominal "
                                  "Sensible Heat Ratio, Nominal Coil UA Value {W/C}, Nominal Coil Surface Area {m2}");
                            RptCoilHeaderFlag(2) = false;
                        }
                        RatedLatentCapacity = LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate - LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate;
                        RatedSHR = SafeDivide(LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate, LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate);
                        PreDefTableEntry(pdchCoolCoilType, LiquidDesiccantCoil(CoilNum).Name, "Coil:Cooling:LiquidDesiccant");
                        PreDefTableEntry(pdchCoolCoilDesCap, LiquidDesiccantCoil(CoilNum).Name, LiquidDesiccantCoil(CoilNum).DesWaterCoolingCoilRate);
                        PreDefTableEntry(pdchCoolCoilTotCap, LiquidDesiccantCoil(CoilNum).Name, LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate);
                        PreDefTableEntry(pdchCoolCoilSensCap, LiquidDesiccantCoil(CoilNum).Name, LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate);
                        PreDefTableEntry(pdchCoolCoilLatCap, LiquidDesiccantCoil(CoilNum).Name, RatedLatentCapacity);
                        PreDefTableEntry(pdchCoolCoilSHR, LiquidDesiccantCoil(CoilNum).Name, RatedSHR);
                        PreDefTableEntry(pdchCoolCoilNomEff, LiquidDesiccantCoil(CoilNum).Name, "-");
                        PreDefTableEntry(pdchCoolCoilUATotal, LiquidDesiccantCoil(CoilNum).Name, LiquidDesiccantCoil(CoilNum).UACoilTotal);
                        PreDefTableEntry(pdchCoolCoilArea, LiquidDesiccantCoil(CoilNum).Name, LiquidDesiccantCoil(CoilNum).TotCoilOutsideSurfArea);
                        addFootNoteSubTable(
                            pdstCoolCoil,
                            "Nominal values are gross at rated conditions, i.e., the supply air fan heat and electric power NOT accounted for.");
                        print(state.outputFiles.eio,
                              "{},{},{:.2R},{:.2R},{:.2R},{:.2R},{:.2R},{:.2R}\n",
                              "Water Cooling Coil Capacity Information,Coil:Cooling:LiquidDesiccant",
                              LiquidDesiccantCoil(CoilNum).Name,
                              LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate,
                              LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate,
                              RatedLatentCapacity,
                              RatedSHR,
                              UATotal,
                              SurfaceArea);
                        coilSelectionReportObj->setCoilAirFlow(LiquidDesiccantCoil(CoilNum).Name,
                                                               "Coil:Cooling:LiquidDesiccant",
                                                               LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate,
                                                               LiquidDesiccantCoil(CoilNum).RequestingAutoSize); // Coil Report
                        coilSelectionReportObj->setCoilWaterCoolingCapacity(LiquidDesiccantCoil(CoilNum).Name,
                                                                            "Coil:Cooling:LiquidDesiccant",
                                                                            LiquidDesiccantCoil(CoilNum).DesWaterCoolingCoilRate,
                                                                            LiquidDesiccantCoil(CoilNum).RequestingAutoSize,
                                                                            LiquidDesiccantCoil(CoilNum).WaterInletNodeNum,
                                                                            LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum,
                                                                            LiquidDesiccantCoil(CoilNum).WaterLoopNum); // Coil Report
                 //   }
                }
                if (LiquidDesiccantCoil(CoilNum).DesWaterCoolingCoilRate <= 0.0)
                    LiquidDesiccantCoil(CoilNum).DesWaterCoolingCoilRate = LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate;
                if (LiquidDesiccantCoil(CoilNum).DesWaterHeatingCoilRate <= 0.0)
                    LiquidDesiccantCoil(CoilNum).DesWaterHeatingCoilRate = LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate;

                // call coil model with everthing set at rating point
                LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate = LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate;
                LiquidDesiccantCoil(CoilNum).InletAirTemp = LiquidDesiccantCoil(CoilNum).DesInletAirTemp;
                LiquidDesiccantCoil(CoilNum).InletAirHumRat = LiquidDesiccantCoil(CoilNum).DesInletAirHumRat; // fixed in sizing routine
                LiquidDesiccantCoil(CoilNum).InletAirEnthalpy =
                    Psychrometrics::PsyHFnTdbW(LiquidDesiccantCoil(CoilNum).DesInletAirTemp, LiquidDesiccantCoil(CoilNum).DesInletAirHumRat);
                Real64 DesInletWetBulb = Psychrometrics::PsyTwbFnTdbWPb(
                    LiquidDesiccantCoil(CoilNum).DesInletAirTemp, LiquidDesiccantCoil(CoilNum).DesInletAirHumRat, DataEnvironment::StdPressureSeaLevel, "InitWaterCoils");
                LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate = LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate;
                LiquidDesiccantCoil(CoilNum).InletWaterTemp = LiquidDesiccantCoil(CoilNum).DesInletWaterTemp;
                Real64 cp = GetSpecificHeatGlycol(PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidName,
                                                  LiquidDesiccantCoil(CoilNum).DesInletWaterTemp,
                                                  PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidIndex,
                                                  "InitWaterCoil");
                LiquidDesiccantCoil(CoilNum).InletWaterEnthalpy = cp * LiquidDesiccantCoil(CoilNum).InletWaterTemp;

                LiquidDesiccantCoil(CoilNum).UACoilVariable = LiquidDesiccantCoil(CoilNum).UACoil;
                //LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingFactor = 0.0;
                Real64 holdOutBaroPress = DataEnvironment::OutBaroPress;
                DataEnvironment::OutBaroPress = DataEnvironment::StdPressureSeaLevel; // assume rating is for sea level.
                //CalcAdjustedCoilUA(CoilNum);

                std::string coilTypeName(" ");
                // calculate coil sim model at rating point, full load, continuous fan
               // if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_DetFlatFinCooling) {
               //     CalcDetailFlatFinCoolingCoil(CoilNum, SimCalc, ContFanCycCoil, 1.0);
               //     coilTypeName = "Coil:Cooling:Water:DetailedGeometry";
               // } else 
               if (LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType_Num == LiquidDesiccantCoil_Cooling) {
                SimuLiquideDesiccantCoil(CoilNum, FirstHVACIteration, SimCalc, ContFanCycCoil, 1.0);
                    coilTypeName = "Coil:Cooling:LiquidDesiccant";
               // } else if (LiquidDesiccantCoil(CoilNum).WaterCoilType_Num == WaterCoil_SimpleHeating) {
               //     CalcSimpleHeatingCoil(CoilNum, ContFanCycCoil, 1.0, SimCalc);
               //     coilTypeName = "Coil:Heating:Water";
               }

                // coil outlets
                Real64 RatedOutletWetBulb(0.0);
                RatedOutletWetBulb = Psychrometrics::PsyTwbFnTdbWPb(
                    LiquidDesiccantCoil(CoilNum).OutletAirTemp, LiquidDesiccantCoil(CoilNum).OutletAirHumRat, DataEnvironment::StdPressureSeaLevel, "InitWaterCoil");

                // call set routine in coil report
                if (//WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_DetFlatFinCooling ||
                    LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType_Num == LiquidDesiccantCoil_Cooling) {
                    coilSelectionReportObj->setRatedCoilConditions(LiquidDesiccantCoil(CoilNum).Name,
                                                                   coilTypeName,
                                                                   LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate, // this is the report variable
                                                                   LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate, // this is the report variable
                                                                   LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate,
                                                                   LiquidDesiccantCoil(CoilNum).InletAirTemp,
                                                                   LiquidDesiccantCoil(CoilNum).InletAirHumRat,
                                                                   DesInletWetBulb,
                                                                   LiquidDesiccantCoil(CoilNum).OutletAirTemp,
                                                                   LiquidDesiccantCoil(CoilNum).OutletAirHumRat,
                                                                   RatedOutletWetBulb,
                                                                   -999.0,
                                                                   -999.0,
                                                                   -999.0,
                                                                   -999.0); // coil effectiveness
                } 
                /*
                else if (LiquidDesiccantCoil(CoilNum).WaterCoilType_Num == WaterCoil_SimpleHeating) {
                    coilSelectionReportObj->setRatedCoilConditions(LiquidDesiccantCoil(CoilNum).Name,
                                                                   coilTypeName,
                                                                   LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate, // this is the report variable
                                                                   LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate, // this is the report variable
                                                                   LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate,
                                                                   LiquidDesiccantCoil(CoilNum).InletAirTemp,
                                                                   LiquidDesiccantCoil(CoilNum).InletAirHumRat,
                                                                   DesInletWetBulb,
                                                                   LiquidDesiccantCoil(CoilNum).OutletAirTemp,
                                                                   LiquidDesiccantCoil(CoilNum).OutletAirHumRat,
                                                                   RatedOutletWetBulb,
                                                                   -999.0,
                                                                   -999.0,
                                                                   -999.0,
                                                                   -999.0); // coil effectiveness
                }
                */
                // now replace the outdoor air conditions set above for one time rating point calc
                DataEnvironment::OutBaroPress = holdOutBaroPress;
            }
        }

        // Do the Begin Day initializations
        // NONE

        // Do the begin HVAC time step initializations
        // NONE

        // Do the following initializations (every time step): This should be the info from
        // the previous components outlets or the node data in this section.
        // First set the conditions for the air into the coil model
        AirInletNode = LiquidDesiccantCoil(CoilNum).AirInletNodeNum;
        WaterInletNode = LiquidDesiccantCoil(CoilNum).WaterInletNodeNum;
        LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate = Node(AirInletNode).MassFlowRate;
        LiquidDesiccantCoil(CoilNum).InletAirTemp = Node(AirInletNode).Temp;
        LiquidDesiccantCoil(CoilNum).InletAirHumRat = Node(AirInletNode).HumRat;
        LiquidDesiccantCoil(CoilNum).InletAirEnthalpy = Node(AirInletNode).Enthalpy;

        LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate = Node(WaterInletNode).MassFlowRate;
        LiquidDesiccantCoil(CoilNum).InletWaterTemp = Node(WaterInletNode).Temp;
        LiquidDesiccantCoil(CoilNum).InletWaterEnthalpy = Node(WaterInletNode).Enthalpy;

        LiquidDesiccantCoil(CoilNum).UACoilVariable = LiquidDesiccantCoil(CoilNum).UACoil;

        //CalcAdjustedCoilUA(CoilNum);

        LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate = 0.0;
        LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate = 0.0;
        LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate = 0.0;
    }

    // refactor coilUA adjustment into separate routine, for use with rating calc
    /*
    void CalcAdjustedCoilUA(int const CoilNum)
    {
        // Pull these precalc routines out of big init routine
        // modify the coil UA based on model in Wetter 1999
        Real64 x_a;                  // result of Eq.70 in Wetter 1999
        Real64 x_w;                  // result of Eq.72 in Wetter 1999
        Real64 AirConvectTerm;       // result of Eq.71 in Wetter 1999
        Real64 WaterConvectTerm;     // result of Eq.73 in Wetter 1999
        Real64 WaterConvSensitivity; // "s" in Wetter 1999, temperature sensitivity in water side convection

        // Coil:Heating:Water
        if ((LiquidDesiccantCoil(CoilNum).WaterCoilType_Num == WaterCoil_SimpleHeating) &&
            (!(MyUAAndFlowCalcFlag(CoilNum)))) { // update Coil UA based on inlet mass flows and temps
            x_a = 1.0 + 4.769E-3 * (LiquidDesiccantCoil(CoilNum).InletAirTemp - LiquidDesiccantCoil(CoilNum).DesInletAirTemp);
            if (LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate > 0.0) {
                AirConvectTerm = x_a * std::pow(LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate / LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate, 0.8) *
                                 LiquidDesiccantCoil(CoilNum).AirSideNominalConvect;
            } else {
                AirConvectTerm = 0.0;
            }
            WaterConvSensitivity = 0.014 / (1.0 + 0.014 * LiquidDesiccantCoil(CoilNum).DesInletWaterTemp);
            x_w = 1.0 + WaterConvSensitivity * (LiquidDesiccantCoil(CoilNum).InletWaterTemp - LiquidDesiccantCoil(CoilNum).DesInletWaterTemp);
            if (LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate > 0.0) {
                WaterConvectTerm = x_w * std::pow(LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate / LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate, 0.85) *
                                   LiquidDesiccantCoil(CoilNum).LiquidSideNominalConvect;
            } else {
                WaterConvectTerm = 0.0;
            }
            if ((AirConvectTerm > 0.0) && (WaterConvectTerm > 0.0)) {
                LiquidDesiccantCoil(CoilNum).UACoilVariable = 1.0 / ((1.0 / WaterConvectTerm) + (1.0 / AirConvectTerm));
            } else {
                // use nominal UA since variable UA cannot be calculated
                LiquidDesiccantCoil(CoilNum).UACoilVariable = LiquidDesiccantCoil(CoilNum).UACoil;
            }

            // calculate the Faulty Coil Fouling (thermal insulance) Factor using fault information
            if (LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingFlag &&
                // The fault shouldn't apply during sizing.
                (!DataGlobals::WarmupFlag) && (!DataGlobals::DoingSizing) && (!DataGlobals::KickOffSimulation) &&
                // This was preexisting
                !(MyUAAndFlowCalcFlag(CoilNum)))
            {
                // Store original value
                LiquidDesiccantCoil(CoilNum).OriginalUACoilVariable = LiquidDesiccantCoil(CoilNum).UACoilVariable;

                int FaultIndex = LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingIndex;
                FaultsManager::FaultPropertiesFoulingCoil &fouling = FaultsManager::FouledCoils(FaultIndex);
                Real64 FaultFrac = fouling.FaultFraction();

                if (fouling.FoulingInputMethod == FaultsManager::iFouledCoil_UARated) {
                    // 1/UA' = Frac * (1/UAFouled) + (1-Frac) / UA
                    LiquidDesiccantCoil(CoilNum).UACoilVariable = 1 / (FaultFrac / (fouling.UAFouled) + (1 - FaultFrac) / LiquidDesiccantCoil(CoilNum).UACoilVariable);
                } else {
                    // R' = R + Rfoul
                    // Rfoul = r_air/A_air + r_water/A_water (FoulingFactor = thermal insulance [K/W, A] = Area [m2], r=fouling factor [m2.K/W]
                    Real64 FoulingFactor = FaultFrac * (fouling.Rfw / (fouling.Aratio * fouling.Aout) + fouling.Rfa / fouling.Aout);
                    LiquidDesiccantCoil(CoilNum).UACoilVariable = 1.0 / ( (1.0 / LiquidDesiccantCoil(CoilNum).UACoilVariable) + FoulingFactor);
                }

                // Do not allow improving coil performance
                LiquidDesiccantCoil(CoilNum).UACoilVariable = min(LiquidDesiccantCoil(CoilNum).UACoilVariable, LiquidDesiccantCoil(CoilNum).OriginalUACoilVariable);

                // Only for reporting purposes
                LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingFactor = (1.0 / LiquidDesiccantCoil(CoilNum).UACoilVariable) -
                                                             (1.0 / LiquidDesiccantCoil(CoilNum).OriginalUACoilVariable);
            } else {
                LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingFactor = 0;
            }
        }

        // Coil:Cooling:Water
        // update Coil UA based on inlet mass flows and temps
        if (LiquidDesiccantCoil(CoilNum).WaterCoilType_Num == WaterCoil_Cooling && (!MyCoilDesignFlag(CoilNum))) {
            if (LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate > 0.0) {
                x_a = 1.0 + 4.769E-3 * (LiquidDesiccantCoil(CoilNum).InletAirTemp - LiquidDesiccantCoil(CoilNum).DesInletAirTemp);
                LiquidDesiccantCoil(CoilNum).UACoilExternal = x_a *
                                                    std::pow(LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate / LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate, 0.8) *
                                                    LiquidDesiccantCoil(CoilNum).UACoilExternalDes;
            } else {
                LiquidDesiccantCoil(CoilNum).UACoilExternal = LiquidDesiccantCoil(CoilNum).UACoilExternalDes;
            }

            if (LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate > 0.0) {
                WaterConvSensitivity = 0.014 / (1.0 + 0.014 * LiquidDesiccantCoil(CoilNum).DesInletWaterTemp);
                x_w = 1.0 + WaterConvSensitivity * (LiquidDesiccantCoil(CoilNum).InletWaterTemp - LiquidDesiccantCoil(CoilNum).DesInletWaterTemp);
                LiquidDesiccantCoil(CoilNum).UACoilInternal =
                    x_w * std::pow(LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate / LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate, 0.85) *
                    LiquidDesiccantCoil(CoilNum).UACoilInternalDes;
            } else {
                LiquidDesiccantCoil(CoilNum).UACoilInternal = LiquidDesiccantCoil(CoilNum).UACoilInternalDes;
            }

            if (!(LiquidDesiccantCoil(CoilNum).UACoilInternal > 0.0 && LiquidDesiccantCoil(CoilNum).UACoilExternal > 0.0)) {
                LiquidDesiccantCoil(CoilNum).UACoilInternal = LiquidDesiccantCoil(CoilNum).UACoilInternalDes;
                LiquidDesiccantCoil(CoilNum).UACoilExternal = LiquidDesiccantCoil(CoilNum).UACoilExternalDes;
            }

            // If Fouling
            if (LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingFlag &&
                // The fault shouldn't apply during sizing.
                (!DataGlobals::WarmupFlag) && (!DataGlobals::DoingSizing) && (!DataGlobals::KickOffSimulation) &&
                // This was preexisting
                !(MyUAAndFlowCalcFlag(CoilNum)))
            {
                // Store original value
                // This is really UACoilTotal technically, but I don't see the point of declaring another Real on the struct just for that
                LiquidDesiccantCoil(CoilNum).OriginalUACoilVariable = 1.0 /
                    (1.0 / LiquidDesiccantCoil(CoilNum).UACoilExternal + 1.0 / LiquidDesiccantCoil(CoilNum).UACoilInternal);

                LiquidDesiccantCoil(CoilNum).OriginalUACoilExternal = LiquidDesiccantCoil(CoilNum).UACoilExternal;
                LiquidDesiccantCoil(CoilNum).OriginalUACoilInternal = LiquidDesiccantCoil(CoilNum).UACoilInternal;

                int FaultIndex = LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingIndex;

                FaultsManager::FaultPropertiesFoulingCoil &fouling = FaultsManager::FouledCoils(FaultIndex);
                Real64 FaultFrac = fouling.FaultFraction();

                if (fouling.FoulingInputMethod == FaultsManager::iFouledCoil_FoulingFactor) {
                    // Adjust the External (air) UA and Internal (water) UA accordingly
                    Real64 Rfoul_air = FaultFrac * (fouling.Rfa / fouling.Aout);
                    Real64 Rfoul_water = FaultFrac * (fouling.Rfw / (fouling.Aratio * fouling.Aout));

                    LiquidDesiccantCoil(CoilNum).UACoilInternal = 1.0 / (1.0 / LiquidDesiccantCoil(CoilNum).UACoilInternal + Rfoul_water);
                    LiquidDesiccantCoil(CoilNum).UACoilExternal = 1.0 / (1.0 / LiquidDesiccantCoil(CoilNum).UACoilExternal + Rfoul_air);
                    //
                } else { // iFouledCoil_UARated
                    // FouledUARated is supposed to be the overall UA. So we need to split between Internal and External UAs

                    // How should I split fouling between internal/external?
                    // We can actually use the current ratio before fouling...
                    // splitRatio = UACoilInternal/UACoilExternal
                    // UACoilInternal = UACoilExternal * splitRatio

                    // UACoilTotal = 1 / (1 / UACoilExternal + 1 / UACoilInternal)
                    // UACoilTotal = 1 / (1 / UACoilExternal + 1 / (UACoilExernal * splitRatio))
                    // UACoilTotal = UACoilExternal / (1 + 1 / splitRatio) = UACoilExternal  * splitRatio / (1 + splitRatio)
                    // UACoilExternal = UACoilTotal * (1 + splitRatio) / splitRatio
                    // UACoilInternal = UACoilTotal * (1 + splitRatio)

                    // Adding in FaultFrac:
                    // UACoilExternal = FaultFrac * [UAFouled * (1+splitRatio) / splitRatio] + (1-FaultFrac) * UACoilExternal
                    // UACoilInternal = FaultFrac * [UAFouled * splitRatio] + (1-FaultFrac) * UACoilInternal

                    Real64 splitRatio = LiquidDesiccantCoil(CoilNum).UACoilInternal / LiquidDesiccantCoil(CoilNum).UACoilExternal;

                    LiquidDesiccantCoil(CoilNum).UACoilExternal =   1.0 /
                        ( (FaultFrac * splitRatio) / ((1 + splitRatio) * fouling.UAFouled) +
                          (1-FaultFrac) / LiquidDesiccantCoil(CoilNum).UACoilExternal);

                    //WaterCoil(CoilNum).UACoilInternal =   1.0 /
                        //( FaultFrac / ((1 + splitRatio) * fouling.UAFouled) +
                          //(1-FaultFrac) / WaterCoil(CoilNum).UACoilInternal);

                    LiquidDesiccantCoil(CoilNum).UACoilInternal = splitRatio * LiquidDesiccantCoil(CoilNum).UACoilExternal;

                }

                // Do not allow improving coil performance
                LiquidDesiccantCoil(CoilNum).UACoilExternal = min(LiquidDesiccantCoil(CoilNum).UACoilExternal, LiquidDesiccantCoil(CoilNum).OriginalUACoilExternal);
                LiquidDesiccantCoil(CoilNum).UACoilInternal = min(LiquidDesiccantCoil(CoilNum).UACoilInternal, LiquidDesiccantCoil(CoilNum).OriginalUACoilInternal);

                // Only for reporting purposes
                LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingFactor = (1.0 / LiquidDesiccantCoil(CoilNum).UACoilExternal) -
                                                             (1.0 / LiquidDesiccantCoil(CoilNum).OriginalUACoilExternal) +
                                                             (1.0 / LiquidDesiccantCoil(CoilNum).UACoilInternal) -
                                                             (1.0 / LiquidDesiccantCoil(CoilNum).OriginalUACoilInternal);
            } else {
                LiquidDesiccantCoil(CoilNum).FaultyCoilFoulingFactor = 0;
            }

            LiquidDesiccantCoil(CoilNum).UACoilTotal = 1.0 /
                (1.0 / LiquidDesiccantCoil(CoilNum).UACoilExternal + 1.0 / LiquidDesiccantCoil(CoilNum).UACoilInternal);

            LiquidDesiccantCoil(CoilNum).UACoilInternalPerUnitArea = LiquidDesiccantCoil(CoilNum).UACoilInternal / LiquidDesiccantCoil(CoilNum).TotCoilOutsideSurfArea;
            LiquidDesiccantCoil(CoilNum).UAWetExtPerUnitArea = LiquidDesiccantCoil(CoilNum).UACoilExternal / LiquidDesiccantCoil(CoilNum).TotCoilOutsideSurfArea;
            LiquidDesiccantCoil(CoilNum).UADryExtPerUnitArea = LiquidDesiccantCoil(CoilNum).UAWetExtPerUnitArea;
        }
    }
    */


    void SizeLiquideDesiccantCoil(EnergyPlusData &state, int const CoilNum)
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         
        //       DATE WRITTEN   
        //       MODIFIED       
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This subroutine is for sizing liquid desiccant Coil Components for which flow rates and UAs have not been
        // specified in the input.

        // METHODOLOGY EMPLOYED:
        // Obtains flow rates from the zone or system sizing arrays and plant sizing data. UAs are
        // calculated by numerically inverting the individual coil calculation routines.

        // REFERENCES:
        // na

        // Using/Aliasing
        using namespace DataSizing;
        using DataEnvironment::StdBaroPress;
        using General::RoundSigDigits;
        using General::SolveRoot;
        using General::TrimSigDigits;
        using PlantUtilities::RegisterPlantCompDesignFlow;
        using ReportSizingManager::GetCoilDesFlowT;
        using ReportSizingManager::ReportSizingOutput;
        using ReportSizingManager::RequestSizing;
        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        static std::string const InitWaterCoil("InitWaterCoil");
        static std::string const RoutineName("SizeWaterCoil");

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int PltSizNum;     // do loop index for plant sizing
        int PltSizCoolNum; // index of plant sizing object for 1st cooling loop
        int PltSizHeatNum; // index of plant sizing object for 1st heating loop
        bool ErrorsFound;  // If errors detected in input
        bool LoopErrorsFound;
        Real64 rho;
        int FieldNum = 2;                      // IDD numeric field number where input field description is found
        std::string CompName;                  // component name
        std::string CompType;                  // component type
        int SizingType;                        // type of sizing to perform
        std::string SizingString;              // input field sizing description (e.g., Nominal Capacity)
        bool bPRINT = true;                    // TRUE if sizing is reported to output (eio)
        Real64 TempSize;                       // autosized value
        Real64 CpAirStd;                       // specific heat of air at standard conditions
        Real64 DesCoilAirFlow;                 // design air flow rate for the coil [m3/s]
        Real64 DesCoilExitTemp;                // design coil exit temperature [C]
        Real64 DesCoilWaterInTempSaved;        // coil water inlet temp used for error checking UA sizing
        Real64 DesCoilInletWaterTempUsed(0.0); // coil design inlet water temp for UA sizing only
        Real64 Cp;
        bool NomCapUserInp = false; // flag for whether user has onput a nominal heating capacity
        int SizingMethod;           // Integer representation of sizing method (e.g., CoolingAirflowSizing, HeatingCapacitySizing, etc.)

        // added variables for desiccant coil
        /*
        Real64 DesHdAvVt;
        Real64 Qlat; // Coil latent load
        Real64 msi;  // Solution mass flow rate IN to this function(kg/s)
        Real64 Tsi;  // Solution temperature IN to this function (C)
        Real64 Xsi;  // Solution concentration IN to this function (weight fraction)
        Real64 Tso;  // Solution temperature IN to this function (C)
        Real64 ma;   // Air mass flow rate IN to this function(kg/s)
        Real64 Tai;  // Air dry bulb temperature IN to this function(C)
        Real64 Wai;  // Air Humidity Ratio IN to this funcation (C)
        Real64 Tao;  // Air dry bulb temperature OUT to this function(C)
        Real64 Wao;  // Air Humidity Ratio OUT to this funcation (C)

        Real64 DesInletAirEnth;
        Real64 DesOutletAirEnth;
        Real64 CpAir;
        Real64 DesSenCoilLoad;
        Real64 DesLatCoilLoad;
        */

        ErrorsFound = false;
        PltSizCoolNum = 0;
        PltSizHeatNum = 0;
        PltSizNum = 0;
        DesCoilAirFlow = 0.0;
        DesCoilExitTemp = 0.0;
        LoopErrorsFound = false;
        CpAirStd = PsyCpAirFnW(0.0);

        // cooling coils
        if (LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType == CoilType_Cooling && LiquidDesiccantCoil(CoilNum).RequestingAutoSize) {
            // find the appropriate Plant Sizing object
            PltSizCoolNum = PlantUtilities::MyPlantSizingIndex("chilled water coil",
                                                               LiquidDesiccantCoil(CoilNum).Name,
                                                               LiquidDesiccantCoil(CoilNum).WaterInletNodeNum,
                                                               LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum,
                                                               LoopErrorsFound);
        }

        // Liquid desiccant coil (Cooling Coil): Sizing cooling coil parameter whick is defined as autosize in IDF file 
        if (LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType == CoilType_Cooling) { // 'Cooling'

            if (LiquidDesiccantCoil(CoilNum).UseDesignWaterDeltaTemp) {
                DataWaterCoilSizCoolDeltaT = LiquidDesiccantCoil(CoilNum).DesignWaterDeltaTemp;
            } else {
                if (PltSizCoolNum > 0) {
                    DataWaterCoilSizCoolDeltaT = PlantSizData(PltSizCoolNum).DeltaT;
                }
            }

            if (PltSizCoolNum > 0) {
                DataPltSizCoolNum = PltSizCoolNum;
                DataWaterLoopNum = LiquidDesiccantCoil(CoilNum).WaterLoopNum;
                    CompType = cAllCoilTypes(Coil_CoolingWater); // Coil:Cooling:Water
                bPRINT = false;       // do not print this sizing request since the autosized value is needed and this input may not be autosized (we
                                      // should print this!)
                TempSize = AutoSize;  // get the autosized air volume flow rate for use in other calculations
                SizingString.clear(); // doesn't matter
                CompName = LiquidDesiccantCoil(CoilNum).Name;
                RequestSizing(state, CompType, CompName, CoolingAirflowSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate = StdRhoAir * TempSize; // inlet air mass flow rate is the autosized value
                DataAirFlowUsedForSizing = TempSize; // many autosized inputs use the design (autosized) air volume flow rate, save this value
                DataFlowUsedForSizing = TempSize;

                if (CurSysNum > 0 && CurOASysNum == 0) {
                    Real64 DesCoilExitHumRat(0.0); // fix coil sizing inconsistency
                    GetCoilDesFlowT(CurSysNum, CpAirStd, DesCoilAirFlow, DesCoilExitTemp, DesCoilExitHumRat);
                    DataAirFlowUsedForSizing = DesCoilAirFlow;
                    DataFlowUsedForSizing = DesCoilAirFlow;
                    DataDesOutletAirTemp = DesCoilExitTemp;
                    DataDesOutletAirHumRat = DesCoilExitHumRat; // need to test for dry coil but inlet conditions not yet known
                }

                // calculate pre-sizing data needed for specific functions (e.g., CoolingWaterDesAirInletTempSizing needs HRin and air flow)
                // these will be calculated again after other parameters are known
                //if (WaterCoil(CoilNum).WaterCoilModel == CoilModel_Detailed) { // 'DETAILED FLAT FIN'
                //    TempSize = AutoSize;                                       // coil report
                //} else {
                    TempSize = LiquidDesiccantCoil(CoilNum).DesInletAirHumRat; // preserve input if entered
                //}
                RequestSizing(state, CompType, CompName, CoolingWaterDesAirInletHumRatSizing, SizingString, TempSize, bPRINT, RoutineName);
                DataDesInletAirHumRat = TempSize;
                TempSize = AutoSize;
                RequestSizing(state, CompType, CompName, CoolingCapacitySizing, SizingString, TempSize, bPRINT, RoutineName);
                DataCapacityUsedForSizing = TempSize;
                TempSize = LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate;
                RequestSizing(state, CompType, CompName, CoolingWaterflowSizing, SizingString, TempSize, bPRINT, RoutineName);
                DataWaterFlowUsedForSizing = TempSize;
                // end pre-sizing data calculations

                    FieldNum = 4; //  N4 , \field Design Inlet Air Temperature
                    bPRINT = true;
                    TempSize = LiquidDesiccantCoil(CoilNum).DesInletAirTemp; // preserve input if entered
                    SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [C]";

                RequestSizing(state, CompType, CompName, CoolingWaterDesAirInletTempSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).DesInletAirTemp = TempSize;
                DataDesInletAirTemp = TempSize;

                    FieldNum = 3; //  N3 , \field Design Inlet Water Temperature
                    bPRINT = true;
                    TempSize = LiquidDesiccantCoil(CoilNum).DesInletWaterTemp; // preserve input if entered
                    SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [C]";
           
                RequestSizing(state, CompType, CompName, CoolingWaterDesWaterInletTempSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).DesInletWaterTemp = TempSize;

                if (CurZoneEqNum > 0) { // zone equipment use air inlet humrat to calculate design outlet air temperature

                        FieldNum = 6; //  N6 , \field Design Inlet Air Humidity Ratio
                        bPRINT = true;
                        TempSize = LiquidDesiccantCoil(CoilNum).DesInletAirHumRat;                     // preserve input if entered
                        SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [kgWater/kgDryAir]";
              
                    RequestSizing(state, CompType, CompName, CoolingWaterDesAirInletHumRatSizing, SizingString, TempSize, bPRINT, RoutineName);
                    LiquidDesiccantCoil(CoilNum).DesInletAirHumRat = TempSize;
                }


                    FieldNum = 5; //  N5 , \field Design Outlet Air Temperature
                    bPRINT = true;
                    TempSize = LiquidDesiccantCoil(CoilNum).DesOutletAirTemp; // preserve input if entered
                    SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [C]";
          

                DataDesInletWaterTemp = LiquidDesiccantCoil(CoilNum).DesInletWaterTemp; // used for warning messages
                RequestSizing(state, CompType, CompName, CoolingWaterDesAirOutletTempSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).DesOutletAirTemp = TempSize;
                DataDesOutletAirTemp = TempSize;

                if (CurSysNum > 0) { // This call can be deleted at a future time and remove the if ( CurZoneEqNum > 0 ) check above. This will
                                     // change the order of the eio file.

                        FieldNum = 6; //  N6 , \field Design Inlet Air Humidity Ratio
                        bPRINT = true;
                        TempSize = LiquidDesiccantCoil(CoilNum).DesInletAirHumRat;
                        SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [kgWater/kgDryAir]";
                                 RequestSizing(state, CompType, CompName, CoolingWaterDesAirInletHumRatSizing, SizingString, TempSize, bPRINT, RoutineName);
                    LiquidDesiccantCoil(CoilNum).DesInletAirHumRat = TempSize;
                }


                    FieldNum = 7; //  N7 , \field Design Outlet Air Humidity Ratio
                    bPRINT = true;
                    TempSize = LiquidDesiccantCoil(CoilNum).DesOutletAirHumRat;                    // preserve input if entered
                    SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [kgWater/kgDryAir]";
         
                RequestSizing(state, CompType, CompName, CoolingWaterDesAirOutletHumRatSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).DesOutletAirHumRat = TempSize;
                DataDesOutletAirHumRat = TempSize;

                    FieldNum = 8; //  N8 , \field Design Inlet Soultion Concentration {-}
                bPRINT = true;
                TempSize = LiquidDesiccantCoil(CoilNum).DesInletSolnConcentration; // preserve input if entered
                SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [%]";

                //RequestSizing(state, CompType, CompName, CoolingWaterDesAirOutletHumRatSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).DesInletSolnConcentration = 0.4;
                //DataDesOutletAirHumRat = TempSize;


                TempSize = AutoSize;
                bPRINT = true;
                if (LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate != AutoSize) bPRINT = false;
                if (CurSysNum == 0) bPRINT = false;
                SizingString = "Design Coil Load [W]"; // there is no input field for this value and this is not the rated capacity (we should
                                                       // always print this!)
                // air inlet/outlet conditions should be known. Don't include fan heat in capacity calculation.
                DataDesAccountForFanHeat = false;
                RequestSizing(state, CompType, CompName, CoolingCapacitySizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).DesWaterCoolingCoilRate = TempSize;
                LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate = StdRhoAir * DataFlowUsedForSizing; // inlet air mass flow rate is the autosized value
                DataCapacityUsedForSizing = LiquidDesiccantCoil(CoilNum).DesWaterCoolingCoilRate;

                // Why isn't the water volume flow rate based on the user inputs for inlet/outlet air/water temps? Water volume flow rate is
                // always based on autosized inputs.
                bPRINT = true;
                FieldNum = 1; //  CoilModel_Detailed: N1 , \field Maximum Water Flow Rate, else: N1 , \field Design Water Flow Rate
                SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [m3/s]";
                TempSize = LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate;
                RequestSizing(state, CompType, CompName, CoolingWaterflowSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate = TempSize;
                DataWaterFlowUsedForSizing = TempSize;

    
                    FieldNum = 2; //  N2 , \field Design Air Flow Rate
                    bPRINT = true;
                    SizingString = LiquidDesiccantCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [m3/s]";
             
                TempSize = LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate;
                RequestSizing(state, CompType, CompName, CoolingAirflowSizing, SizingString, TempSize, bPRINT, RoutineName);
                LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate = TempSize;
                LiquidDesiccantCoil(CoilNum).DesAirMassFlowRate = LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate * StdRhoAir;

                if (LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate <= 0.0) {
                    LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate = 0.0;
                    ShowWarningError("The design air flow rate is zero for Coil:Cooling:LiquidDesiccant " + LiquidDesiccantCoil(CoilNum).Name);
                    ShowContinueError("The autosize value for max air volume flow rate is zero");
                }

                DataPltSizCoolNum = 0; // reset all globals to 0 to ensure correct sizing for other child components
                DataWaterLoopNum = 0;
                DataConstantUsedForSizing = 0.0;
                DataFractionUsedForSizing = 0.0;
                DataAirFlowUsedForSizing = 0.0;
                DataFlowUsedForSizing = 0.0;
                DataWaterFlowUsedForSizing = 0.0;
                DataCapacityUsedForSizing = 0.0;
                DataDesInletAirTemp = 0.0;
                DataDesOutletAirTemp = 0.0;
                DataDesOutletAirHumRat = 0.0;
                DataDesInletAirHumRat = 0.0;
                DataDesInletWaterTemp = 0.0;
                DataWaterCoilSizCoolDeltaT = 0.0;
            } else {
                // If there is no cooling Plant Sizing object and autosizing was requested, issue fatal error message
                if (LiquidDesiccantCoil(CoilNum).RequestingAutoSize) {
                    ShowSevereError("Autosizing of water coil requires a cooling loop Sizing:Plant object");
                    ShowContinueError("Occurs in water coil object= " + LiquidDesiccantCoil(CoilNum).Name);
                    ErrorsFound = true;
                }
            }
            //} // end of cooling Plant Sizing existence IF - ELSE
        } // end cooling coil IF



        // Liquid desiccant coil (Cooling Coil): Calcuate the design HdAvVt 
        // doesn't work if the calcuate in set in Size subroutine    
        /*
        // Enthalpy of Air at Inlet design conditions
        DesInletAirEnth = PsyHFnTdbW(WaterCoil(CoilNum).DesInletAirTemp, WaterCoil(CoilNum).DesInletAirHumRat);

        // Enthalpy of Air at outlet at design conditions
        DesOutletAirEnth = PsyHFnTdbW(WaterCoil(CoilNum).DesOutletAirTemp, WaterCoil(CoilNum).DesOutletAirHumRat);

        // Total Coil Load from Inlet and Outlet Air States (which include fan heat as appropriate).
        WaterCoil(CoilNum).DesTotWaterCoilLoad = WaterCoil(CoilNum).DesAirMassFlowRate * (DesInletAirEnth - DesOutletAirEnth);

        CpAir = PsyCpAirFnW(WaterCoil(CoilNum).DesInletAirHumRat);
        DesSenCoilLoad = WaterCoil(CoilNum).DesAirMassFlowRate * CpAir * (WaterCoil(CoilNum).DesInletAirTemp - WaterCoil(CoilNum).DesOutletAirTemp);
        DesLatCoilLoad = WaterCoil(CoilNum).DesTotWaterCoilLoad - DesSenCoilLoad;

        Qlat = DesLatCoilLoad;
        msi = WaterCoil(CoilNum).DesAirMassFlowRate;
        Tsi = WaterCoil(CoilNum).DesInletWaterTemp;
        Xsi = WaterCoil(CoilNum).DesInletSolnConcentration;
        //                Tso = 50; // WaterCoil(CoilNum).DesOutletWaterTemp;
        ma = WaterCoil(CoilNum).MaxWaterMassFlowRate;
        Tai = WaterCoil(CoilNum).DesInletAirTemp;
        Wai = WaterCoil(CoilNum).DesInletAirHumRat;
        Tao = WaterCoil(CoilNum).DesOutletAirTemp;
        Wao = WaterCoil(CoilNum).DesOutletAirHumRat;
        DesHdAvVt = CalculateDesHdAvVt(Qlat, // Coil latent load
                                       msi,  // Solution mass flow rate IN to this function(kg/s)
                                       Tsi,  // Solution temperature IN to this function (C)
                                       Xsi,  // Solution concentration IN to this function (weight fraction)
                                       ma,   // Air mass flow rate IN to this function(kg/s)
                                       Tai,  // Air dry bulb temperature IN to this function(C)
                                       Wai,  // Air Humidity Ratio IN to this funcation (C)
                                       Tao,  // Air dry bulb temperature OUT to this function(C)
                                       Wao); // Air Humidity Ratio OUT to this funcation (C)

        WaterCoil(CoilNum).HdAvVt = DesHdAvVt;
        */
        

        // if this is a heating coil
        /*
        if (LiquidDesiccantCoil(CoilNum).WaterCoilType == CoilType_Heating && LiquidDesiccantCoil(CoilNum).RequestingAutoSize) {
            // find the appropriate heating Plant Sizing object
            PltSizHeatNum = PlantUtilities::MyPlantSizingIndex("hot water coil",
                                                               LiquidDesiccantCoil(CoilNum).Name,
                                                               LiquidDesiccantCoil(CoilNum).WaterInletNodeNum,
                                                               LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum,
                                                               LoopErrorsFound);
        }
        */

        // Size the heat coil
        /*
        if (WaterCoil(CoilNum).WaterCoilType == CoilType_Heating) {

            if (WaterCoil(CoilNum).UseDesignWaterDeltaTemp) {
                // use water design deltaT specified in the heating water coils
                DataWaterCoilSizHeatDeltaT = WaterCoil(CoilNum).DesignWaterDeltaTemp;
            } else {
                if (PltSizHeatNum > 0) {
                    DataWaterCoilSizHeatDeltaT = PlantSizData(PltSizHeatNum).DeltaT;
                }
            }

            if (PltSizHeatNum > 0) {

                DataPltSizHeatNum = PltSizHeatNum;
                DataWaterLoopNum = WaterCoil(CoilNum).WaterLoopNum;
                rho = GetDensityGlycol(PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidName,
                                       DataGlobals::HWInitConvTemp,
                                       PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidIndex,
                                       RoutineName);
                Cp = GetSpecificHeatGlycol(
                    PlantLoop(DataWaterLoopNum).FluidName, DataGlobals::HWInitConvTemp, PlantLoop(DataWaterLoopNum).FluidIndex, RoutineName);
                if (WaterCoil(CoilNum).DesTotWaterCoilLoad > 0.0) {
                    NomCapUserInp = true;
                } else if (CurSysNum > 0 && CurSysNum <= DataHVACGlobals::NumPrimaryAirSys) {
                    if (FinalSysSizing(CurSysNum).HeatingCapMethod == CapacityPerFloorArea) {
                        NomCapUserInp = true;
                    } else if (FinalSysSizing(CurSysNum).HeatingCapMethod == HeatingDesignCapacity &&
                               FinalSysSizing(CurSysNum).HeatingTotalCapacity > 0.0) {
                        NomCapUserInp = true;
                    }
                } else {
                    NomCapUserInp = false;
                }
                bPRINT = false;                              // do not print this sizing request
                TempSize = AutoSize;                         // get the autosized air volume flow rate for use in other calculations
                SizingString.clear();                        // doesn't matter
                CompType = cAllCoilTypes(Coil_HeatingWater); // "Coil:Heating:Water"
                CompName = WaterCoil(CoilNum).Name;
                if (WaterCoil(CoilNum).DesiccantRegenerationCoil) {
                    DataDesicRegCoil = true;
                    DataDesicDehumNum = WaterCoil(CoilNum).DesiccantDehumNum;
                    TempSize = AutoSize;
                    RequestSizing(state, CompType, CompName, HeatingCoilDesAirInletTempSizing, SizingString, TempSize, bPRINT, RoutineName);
                    DataDesInletAirTemp = TempSize;
                    TempSize = AutoSize;
                    RequestSizing(state, CompType, CompName, HeatingCoilDesAirOutletTempSizing, SizingString, TempSize, bPRINT, RoutineName);
                    DataDesOutletAirTemp = TempSize;
                    if (CurOASysNum > 0) {
                        OASysEqSizing(CurOASysNum).AirFlow = true;
                        OASysEqSizing(CurOASysNum).AirVolFlow = FinalSysSizing(CurSysNum).DesOutAirVolFlow;
                    }
                    TempSize = AutoSize; // reset back
                }
                RequestSizing(state, CompType, CompName, HeatingAirflowSizing, SizingString, TempSize, bPRINT, RoutineName);
                // reset the design air volume flow rate for air loop coils only
                if (CurSysNum > 0) WaterCoil(CoilNum).DesAirVolFlowRate = TempSize;
                WaterCoil(CoilNum).InletAirMassFlowRate = StdRhoAir * TempSize; // inlet air mass flow rate is not the autosized value
                DataAirFlowUsedForSizing = TempSize;
                DataFlowUsedForSizing = TempSize; // many autosized inputs use the design (autosized) air flow rate, save this value

                bPRINT = true;
                if (WaterCoil(CoilNum).CoilPerfInpMeth == NomCap && NomCapUserInp) {
                    TempSize = WaterCoil(CoilNum).DesTotWaterCoilLoad;
                    DataNomCapInpMeth = true;
                } else {
                    TempSize = AutoSize;
                }
                if (CurSysNum > 0) {
                    SizingType = HeatingCapacitySizing;
                } else {
                    SizingType = WaterHeatingCapacitySizing;
                }
                FieldNum = 3; //  N3 , \field Rated Capacity
                SizingString = WaterCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [W]";
                RequestSizing(state, CompType, CompName, SizingType, SizingString, TempSize, bPRINT, RoutineName);
                WaterCoil(CoilNum).DesWaterHeatingCoilRate = TempSize;
                WaterCoil(CoilNum).DesTotWaterCoilLoad = TempSize;
                DataCapacityUsedForSizing = WaterCoil(CoilNum).DesWaterHeatingCoilRate;

                // We now have the design load if it was autosized. For the case of CoilPerfInpMeth == NomCap, calculate the air flow rate
                // specified by the NomCap inputs. This overrides all previous values
                if (WaterCoil(CoilNum).CoilPerfInpMeth == NomCap && NomCapUserInp) {
                    WaterCoil(CoilNum).InletAirMassFlowRate = WaterCoil(CoilNum).DesTotWaterCoilLoad /
                                                              (CpAirStd * (WaterCoil(CoilNum).DesOutletAirTemp - WaterCoil(CoilNum).DesInletAirTemp));
                    WaterCoil(CoilNum).DesAirVolFlowRate = WaterCoil(CoilNum).InletAirMassFlowRate / StdRhoAir;
                    DataAirFlowUsedForSizing = WaterCoil(CoilNum).DesAirVolFlowRate;
                    DataFlowUsedForSizing = WaterCoil(CoilNum).DesAirVolFlowRate;
                }

                FieldNum = 2; // N2 , \field Maximum Water Flow Rate
                SizingString = WaterCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [m3/s]";
                TempSize = WaterCoil(CoilNum).MaxWaterVolFlowRate;
                SizingMethod = HeatingWaterflowSizing;

                if (WaterCoil(CoilNum).CoilPerfInpMeth == NomCap && NomCapUserInp) {
                    if (WaterCoil(CoilNum).DesTotWaterCoilLoad > SmallLoad) {
                        WaterCoil(CoilNum).MaxWaterVolFlowRate =
                            DataCapacityUsedForSizing / (Cp * rho * (WaterCoil(CoilNum).DesInletWaterTemp - WaterCoil(CoilNum).DesOutletWaterTemp));
                    } else {
                        WaterCoil(CoilNum).MaxWaterVolFlowRate = 0.0;
                    }
                    SizingMethod = AutoCalculateSizing;
                    DataConstantUsedForSizing = WaterCoil(CoilNum).MaxWaterVolFlowRate;
                    DataFractionUsedForSizing = 1.0;
                }
                RequestSizing(state, CompType, CompName, SizingMethod, SizingString, TempSize, bPRINT, RoutineName);
                WaterCoil(CoilNum).MaxWaterVolFlowRate = TempSize;
                DataWaterFlowUsedForSizing = WaterCoil(CoilNum).MaxWaterVolFlowRate;
                DataConstantUsedForSizing = 0.0; // reset these in case NomCapUserInp was true
                DataFractionUsedForSizing = 0.0;
                if (WaterCoil(CoilNum).MaxWaterVolFlowRate <= 0.0) {
                    //					MaxWaterVolFlowRateDes = 0.0;
                    ShowWarningError("The design coil load is zero for Coil:Heating:Water " + WaterCoil(CoilNum).Name);
                    ShowContinueError("The autosize value for maximum water flow rate is zero");
                    ShowContinueError("To change this, input a value for UA, change the heating design day, or raise the");
                    ShowContinueError("  system heating design supply air temperature. Also check to make sure the Preheat");
                    ShowContinueError("  Design Temperature is not the same as the Central Heating Design Supply Air Temperature. ");
                }

                // initialize the water coil inlet conditions
                bPRINT = false; // no need to print to eio since we only need the values
                DataFlowUsedForSizing = DataAirFlowUsedForSizing;
                if (WaterCoil(CoilNum).CoilPerfInpMeth == NomCap && NomCapUserInp) {
                    WaterCoil(CoilNum).InletAirTemp = WaterCoil(CoilNum).DesInletAirTemp;
                    WaterCoil(CoilNum).InletAirHumRat = PsyWFnTdbRhPb(WaterCoil(CoilNum).DesInletAirTemp, 0.5, StdBaroPress, RoutineName);
                    WaterCoil(CoilNum).InletAirMassFlowRate = DataAirFlowUsedForSizing * StdRhoAir;               // don't need this
                    DataDesOutletAirTemp = WaterCoil(CoilNum).DesOutletAirTemp;                                   // for error messages
                    DataDesOutletAirHumRat = PsyWFnTdbRhPb(DataDesOutletAirTemp, 0.5, StdBaroPress, RoutineName); // for error messages
                    WaterCoil(CoilNum).InletWaterMassFlowRate = rho * DataWaterFlowUsedForSizing;
                    WaterCoil(CoilNum).MaxWaterMassFlowRate = rho * DataWaterFlowUsedForSizing;
                    WaterCoil(CoilNum).InletWaterTemp = WaterCoil(CoilNum).DesInletWaterTemp;
                } else if (WaterCoil(CoilNum).DesiccantRegenerationCoil) {
                    TempSize = AutoSize; // these data are initially 0, set to autosize to receive a result from RequestSizing
                    RequestSizing(state, CompType, CompName, HeatingCoilDesAirInletTempSizing, SizingString, TempSize, bPRINT, RoutineName);
                    WaterCoil(CoilNum).InletAirTemp = TempSize;
                    TempSize = AutoSize; // these data are initially 0, set to autosize to receive a result from RequestSizing
                    RequestSizing(state, CompType, CompName, HeatingCoilDesAirInletHumRatSizing, SizingString, TempSize, bPRINT, RoutineName);
                    WaterCoil(CoilNum).DesInletAirHumRat = TempSize; // coil report
                    WaterCoil(CoilNum).InletAirHumRat = TempSize;
                    TempSize = AutoSize; // these data are initially 0, set to autosize to receive a result from RequestSizing
                    RequestSizing(state, CompType, CompName, HeatingAirflowUASizing, SizingString, TempSize, bPRINT, RoutineName);
                    // WaterCoil( CoilNum ).InletAirMassFlowRate = TempSize;
                    WaterCoil(CoilNum).DesAirVolFlowRate = DataAirFlowUsedForSizing;                // coil report
                    WaterCoil(CoilNum).InletAirMassFlowRate = DataAirFlowUsedForSizing * StdRhoAir; // this is stiil volume flow!
                } else {
                    TempSize = AutoSize; // these data are initially 0, set to autosize to receive a result from RequestSizing
                    RequestSizing(state, CompType, CompName, HeatingWaterDesAirInletTempSizing, SizingString, TempSize, bPRINT, RoutineName);
                    WaterCoil(CoilNum).InletAirTemp = TempSize;
                    TempSize = AutoSize; // these data are initially 0, set to autosize to receive a result from RequestSizing
                    RequestSizing(state, CompType, CompName, HeatingWaterDesAirInletHumRatSizing, SizingString, TempSize, bPRINT, RoutineName);
                    WaterCoil(CoilNum).DesInletAirHumRat = TempSize; // coil report
                    WaterCoil(CoilNum).InletAirHumRat = TempSize;
                    TempSize = AutoSize; // these data are initially 0, set to autosize to receive a result from RequestSizing
                    RequestSizing(state, CompType, CompName, HeatingAirflowUASizing, SizingString, TempSize, bPRINT, RoutineName);
                    WaterCoil(CoilNum).DesAirMassFlowRate = TempSize; // coil report
                    WaterCoil(CoilNum).InletAirMassFlowRate = TempSize;
                }

                // zone and air loop coils use different design coil load calculations, air loop coils use air side capacity,
                // zone coils use water side capacity
                DataDesInletAirTemp = WaterCoil(CoilNum).InletAirTemp;               // used in error mesages
                DataDesInletAirHumRat = WaterCoil(CoilNum).InletAirHumRat;           // used in error mesages
                DataFlowUsedForSizing = DataAirFlowUsedForSizing * StdRhoAir;        // used in error mesages
                WaterCoil(CoilNum).MaxWaterVolFlowRate = DataWaterFlowUsedForSizing; // why is this here?
                if (!(WaterCoil(CoilNum).CoilPerfInpMeth == NomCap && NomCapUserInp)) {
                    TempSize = AutoSize;
                    RequestSizing(state, CompType, CompName, HeatingWaterDesCoilLoadUsedForUASizing, SizingString, TempSize, bPRINT, RoutineName);
                    DataCapacityUsedForSizing = TempSize;
                    TempSize = AutoSize; // get the water volume flow rate used to size UA
                    RequestSizing(state, CompType, CompName, HeatingWaterDesCoilWaterVolFlowUsedForUASizing, SizingString, TempSize, bPRINT, RoutineName);
                    DataWaterFlowUsedForSizing = TempSize;
                    WaterCoil(CoilNum).InletWaterTemp = PlantSizData(PltSizHeatNum).ExitTemp;
                    WaterCoil(CoilNum).InletWaterMassFlowRate = rho * DataWaterFlowUsedForSizing;
                    WaterCoil(CoilNum).MaxWaterMassFlowRate = rho * DataWaterFlowUsedForSizing;
                    WaterCoil(CoilNum).DesWaterHeatingCoilRate = DataCapacityUsedForSizing;
                }
                // calculate UA
                if (CurSysNum > 0) WaterCoil(CoilNum).DesTotWaterCoilLoad = DataCapacityUsedForSizing;
                FieldNum = 1;  // N1 , \field U-Factor Times Area Value
                bPRINT = true; // report to eio the UA value
                SizingString = WaterCoilNumericFields(CoilNum).FieldNames(FieldNum) + " [W/K]";
                DataCoilNum = CoilNum;
                DataFanOpMode = ContFanCycCoil;
                if (WaterCoil(CoilNum).CoilPerfInpMeth == NomCap && NomCapUserInp) {
                    TempSize = AutoSize;
                } else {
                    TempSize = WaterCoil(CoilNum).UACoil;
                }

                DataFlowUsedForSizing = WaterCoil(CoilNum).InletAirMassFlowRate;
                DesCoilWaterInTempSaved = WaterCoil(DataCoilNum).InletWaterTemp;
                if (DesCoilWaterInTempSaved < DesCoilHWInletTempMin) {
                    // at low coil design water inlet temp, sizing has convergence issue hence slightly higher water inlet temperature
                    // is estimated in "EstimateCoilInletWaterTemp" and used for UA autosizing only
                    EstimateCoilInletWaterTemp(DataCoilNum, DataFanOpMode, 1.0, DataCapacityUsedForSizing, DesCoilInletWaterTempUsed);
                    WaterCoil(DataCoilNum).InletWaterTemp = DesCoilInletWaterTempUsed;
                }
                // must set DataCapacityUsedForSizing, DataWaterFlowUsedForSizing and DataFlowUsedForSizing to size UA. Any value of 0 will result
                // in UA = 1.
                RequestSizing(state, CompType, CompName, WaterHeatingCoilUASizing, SizingString, TempSize, bPRINT, RoutineName);
                if (DesCoilWaterInTempSaved < DesCoilHWInletTempMin) {
                    ShowWarningError("Autosizing of heating coil UA for Coil:Heating:Water \"" + CompName + "\"");
                    ShowContinueError(" Plant design loop exit temperature = " + TrimSigDigits(PlantSizData(DataPltSizHeatNum).ExitTemp, 2) + " C");
                    ShowContinueError(" Plant design loop exit temperature is low for design load and leaving air temperature anticipated.");
                    ShowContinueError(
                        " Heating coil UA-value is sized using coil water inlet temperature = " + TrimSigDigits(DesCoilInletWaterTempUsed, 2) + " C");
                    WaterCoil(DataCoilNum).InletWaterTemp = DesCoilWaterInTempSaved; // reset the Design Coil Inlet Water Temperature
                }
                WaterCoil(CoilNum).UACoil = TempSize;
                // if coil UA did not size due to one of these variables being 0, must set UACoilVariable to avoid crash later on
                if (DataCapacityUsedForSizing == 0.0 || DataWaterFlowUsedForSizing == 0.0 || DataFlowUsedForSizing == 0.0) {
                    if (WaterCoil(CoilNum).UACoilVariable == AutoSize) {
                        WaterCoil(CoilNum).UACoilVariable = TempSize;
                    }
                }
                WaterCoil(CoilNum).UACoilVariable = TempSize;
                WaterCoil(CoilNum).DesWaterHeatingCoilRate = DataCapacityUsedForSizing;
                WaterCoil(DataCoilNum).InletWaterTemp = DesCoilWaterInTempSaved; // reset the Design Coil Inlet Water Temperature

                DataWaterLoopNum = 0; // reset all globals to 0 to ensure correct sizing for other child components
                DataPltSizHeatNum = 0;
                DataCoilNum = 0;
                DataFanOpMode = 0;
                DataCapacityUsedForSizing = 0.0;
                DataWaterFlowUsedForSizing = 0.0;
                DataDesInletAirTemp = 0.0;
                DataDesInletAirHumRat = 0.0;
                DataDesOutletAirTemp = 0.0;
                DataDesOutletAirHumRat = 0.0;
                DataAirFlowUsedForSizing = 0.0;
                DataFlowUsedForSizing = 0.0;
                DataDesicDehumNum = 0;
                DataDesicRegCoil = false;
                DataWaterCoilSizHeatDeltaT = 0.0;
                DataNomCapInpMeth = false;

            } else {
                // if there is no heating Plant Sizing object and autosizng was requested, issue an error message
                if (WaterCoil(CoilNum).RequestingAutoSize) {
                    ShowSevereError("Autosizing of water coil requires a heating loop Sizing:Plant object");
                    ShowContinueError("Occurs in water coil object= " + WaterCoil(CoilNum).Name);
                    ErrorsFound = true;
                }
            }
            //} // end of heating Plant Sizing existence IF - ELSE
        } // end heating coil IF
        */
        


        // save the design water volumetric flow rate for use by the water loop sizing algorithms
        if (LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate > 0.0) {
            RegisterPlantCompDesignFlow(LiquidDesiccantCoil(CoilNum).WaterInletNodeNum, LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate);
        }

        if (ErrorsFound || DataErrorsFound) {
            ShowFatalError("Preceding water coil sizing errors cause program termination");
        }
    }

    // End Initialization Section of the Module
    //******************************************************************************

    // Begin Algorithm Section of the Module
    //******************************************************************************
    /*
    void CalcSimpleHeatingCoil(int const CoilNum,          // index to heating coil
                               int const FanOpMode,        // fan operating mode
                               Real64 const PartLoadRatio, // part-load ratio of heating coil
                               int const CalcMode          // 1 = design calc; 2 = simulation calculation
    )
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Rich Liesen
        //       DATE WRITTEN
        //       MODIFIED       Aug. 2007 - R. Raustad, added fan operating mode and part-load ratio to
        //                                  calculate the outlet conditions when fan and coil cycle.
        //                                  Air and water outlet temperature are full output with average
        //                                  air and water mass flow rate when fan and coil cycle.
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // Simulates a simple NTU effectiveness model heating coil

        // METHODOLOGY EMPLOYED:
        // (1) outlet conditions are calculated from the effectiveness and the inlet conditions.
        // (2) Effectiveness is calculated from the NTU formula for a cross flow heat exchanger
        //     with both streams unmixed.
        // Note: UA is input by user and is fixed.

        // REFERENCES:
        // See for instance ASHRAE HVAC 2 Toolkit, page 4-4, formula (4-7)

        // Using/Aliasing
        using DataBranchAirLoopPlant::MassFlowTolerance;

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        static std::string const RoutineName("CalcSimpleHeatingCoil");

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        Real64 WaterMassFlowRate;
        Real64 AirMassFlow; // [kg/sec]
        Real64 TempAirIn;   // [C]
        Real64 TempAirOut;  // [C]
        Real64 Win;
        Real64 TempWaterIn;
        Real64 TempWaterOut;
        Real64 UA;
        Real64 CapacitanceAir;
        Real64 CapacitanceWater;
        Real64 CapacitanceMin;
        Real64 CapacitanceMax;
        Real64 HeatingCoilLoad;
        Real64 NTU;
        Real64 ETA;
        Real64 A;
        Real64 CapRatio;
        Real64 E1;
        Real64 E2;
        Real64 Effec;
        Real64 Cp;
        int Control;

        UA = LiquidDesiccantCoil(CoilNum).UACoilVariable;
        TempAirIn = LiquidDesiccantCoil(CoilNum).InletAirTemp;
        Win = LiquidDesiccantCoil(CoilNum).InletAirHumRat;
        Control = LiquidDesiccantCoil(CoilNum).Control;
        TempWaterIn = LiquidDesiccantCoil(CoilNum).InletWaterTemp;

        // adjust mass flow rates for cycling fan cycling coil operation
        if (FanOpMode == CycFanCycCoil) {
            if (PartLoadRatio > 0.0) {
                AirMassFlow = LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate / PartLoadRatio;
                WaterMassFlowRate = min(LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate / PartLoadRatio, LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate);
            } else {
                AirMassFlow = 0.0;
                WaterMassFlowRate = 0.0;
            }
        } else {
            AirMassFlow = LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate;
            WaterMassFlowRate = LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate;
        }

        if (WaterMassFlowRate > MassFlowTolerance) { // If the coil is operating
            CapacitanceAir = PsyCpAirFnW(Win) * AirMassFlow;
            Cp = GetSpecificHeatGlycol(PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidName,
                                       TempWaterIn,
                                       PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidIndex,
                                       RoutineName);
            CapacitanceWater = Cp * WaterMassFlowRate;
            CapacitanceMin = min(CapacitanceAir, CapacitanceWater);
            CapacitanceMax = max(CapacitanceAir, CapacitanceWater);
        } else {
            CapacitanceAir = 0.0;
            CapacitanceWater = 0.0;
        }

        // If the coil is operating there should be some heating capacitance
        //  across the coil, so do the simulation. If not set outlet to inlet and no load.
        //  Also the coil has to be scheduled to be available
        if (((CapacitanceAir > 0.0) && (CapacitanceWater > 0.0)) && (CalcMode == DesignCalc || MySizeFlag(CoilNum) || MyUAAndFlowCalcFlag(CoilNum) ||
                                                                     GetCurrentScheduleValue(LiquidDesiccantCoil(CoilNum).SchedPtr) > 0.0)) {

            if (UA <= 0.0) {
                ShowFatalError("UA is zero for COIL:Heating:Water " + LiquidDesiccantCoil(CoilNum).Name);
            }
            NTU = UA / CapacitanceMin;
            ETA = std::pow(NTU, 0.22);
            CapRatio = CapacitanceMin / CapacitanceMax;
            A = CapRatio * NTU / ETA;

            if (A > 20.0) {
                A = ETA * 1.0 / CapRatio;
            } else {
                E1 = std::exp(-A);
                A = ETA * (1.0 - E1) / CapRatio;
            }

            if (A > 20.0) {
                Effec = 1.0;
            } else {
                E2 = std::exp(-A);
                Effec = 1.0 - E2;
            }

            TempAirOut = TempAirIn + Effec * CapacitanceMin * (TempWaterIn - TempAirIn) / CapacitanceAir;
            TempWaterOut = TempWaterIn - CapacitanceAir * (TempAirOut - TempAirIn) / CapacitanceWater;
            HeatingCoilLoad = CapacitanceWater * (TempWaterIn - TempWaterOut);
            // The HeatingCoilLoad is the change in the enthalpy of the water
            LiquidDesiccantCoil(CoilNum).OutletWaterEnthalpy =
                LiquidDesiccantCoil(CoilNum).InletWaterEnthalpy - HeatingCoilLoad / LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate;
            LiquidDesiccantCoil(CoilNum).OutletWaterMassFlowRate = LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate;

        } else { // If not running Conditions do not change across coil from inlet to outlet

            TempAirOut = TempAirIn;
            TempWaterOut = TempWaterIn;
            HeatingCoilLoad = 0.0;
            LiquidDesiccantCoil(CoilNum).OutletWaterEnthalpy = LiquidDesiccantCoil(CoilNum).InletWaterEnthalpy;
            LiquidDesiccantCoil(CoilNum).OutletWaterMassFlowRate = 0.0;
        }

        if (FanOpMode == CycFanCycCoil) {
            HeatingCoilLoad *= PartLoadRatio;
        }

        // Set the outlet conditions
        LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate = HeatingCoilLoad;
        LiquidDesiccantCoil(CoilNum).OutletAirTemp = TempAirOut;
        LiquidDesiccantCoil(CoilNum).OutletWaterTemp = TempWaterOut;

        // This WaterCoil does not change the moisture or Mass Flow across the component
        LiquidDesiccantCoil(CoilNum).OutletAirHumRat = LiquidDesiccantCoil(CoilNum).InletAirHumRat;
        LiquidDesiccantCoil(CoilNum).OutletAirMassFlowRate = LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate;
        // Set the outlet enthalpys for air and water
        LiquidDesiccantCoil(CoilNum).OutletAirEnthalpy = PsyHFnTdbW(LiquidDesiccantCoil(CoilNum).OutletAirTemp, LiquidDesiccantCoil(CoilNum).OutletAirHumRat);
    }
    */

    // new code 
    void SimuLiquideDesiccantCoil(int const CoilNum, // LiquidDesiccantCoil
                     bool const FirstHVACIteration,
                     int const CalcMode,
                     int const FanOpMode,       // fan operating mode
                     Real64 const PartLoadRatio // part-load ratio of heating coil
    )
    {

        // FUNCTION INFORMATION:
        // AUTHOR         
        // DATE WRITTEN   
        // MODIFIED       na
        // RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // 
        // METHODOLOGY EMPLOYED:
        // 
        // REFERENCES:
        // 

        // Using/Aliasing
        using General::SafeDivide;
        using namespace std;

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        Real64 SolnMassFlowRateIn = 0.0;    // Solution mass flow rate IN to this function (kg/s) 
        Real64 SolnTempIn = 1.0;            // Solution temperature IN to this function (C)
        Real64 SolnConcIn = 1.0;            // Solution concentration IN to this function (weight fraction)
        Real64 AirMassFlowRateIn = 1.0;     // Air mass flow rate IN to this function (kg/s) 
        Real64 AirTempIn = 1.0;             // Air dry bulb temperature IN to this function(C)
        Real64 AirHumRat = 1.0;             // Air Humidity Ratio IN to this funcation (C)
        Real64 Coeff_HdAvVt = 1.0;          // Mass Tansfer Coefficient Area Product 
        Real64 LewisNum = 1.0;              // External overall heat transfer coefficient(W/m2 C)
        Real64 OutletSolnTemp = 0.0;           // Leaving solution temperature (C)
        Real64 OutletSolnConc = 0.0;          // Leaving solution concentration (weight fraction)
        Real64 OutletSolnMassFlowRate = 0.0;  // Leaving solution mass flow rate (kg/s)
        Real64 OutletAirTemp = 0.0;           // Leaving air dry bulb temperature(C)
        Real64 OutletAirHumRat = 0.0;         // Leaving air humidity ratio
        Real64 TotWaterCoilLoad = 0.0;        // Total heat transfer rate(W)
        Real64 WaterEvaporate = 0.0;          // Total water evaporate (kg)


        // If Coil is Scheduled ON then do the simulation
        if (((GetCurrentScheduleValue(LiquidDesiccantCoil(CoilNum).SchedPtr) > 0.0) && (LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate > 0.0) &&
             (LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate >= MinAirMassFlow) && (LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate > 0.0) &&
             (LiquidDesiccantCoil(CoilNum).MaxWaterMassFlowRate > 0.0)) || (CalcMode == DesignCalc)) {

            std::cout << "******************************CoilNum:"<< CoilNum<< "start * **************************" << endl;
            
            SolnMassFlowRateIn = LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate;
            SolnTempIn = LiquidDesiccantCoil(CoilNum).InletWaterTemp;
            SolnConcIn = 0.4; 
            AirMassFlowRateIn = LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate;
            AirTempIn = LiquidDesiccantCoil(CoilNum).InletAirTemp;
            AirHumRat = LiquidDesiccantCoil(CoilNum).InletAirHumRat;
            Coeff_HdAvVt = LiquidDesiccantCoil(CoilNum).HdAvVt;
            LewisNum = 1.0;
            LiqDesiccantCoil_Ntu_HPDM(CoilNum,                // Number of Coil
                                      SolnMassFlowRateIn,     // Solution mass flow rate IN to this function(kg/s)
                                      SolnTempIn,             // Solution temperature IN to this function (C)
                                      SolnConcIn,             // Solution concentration IN to this function (weight fraction)
                                      AirMassFlowRateIn,      // Air mass flow rate IN to this function(kg/s)
                                      AirTempIn,              // Air dry bulb temperature IN to this function(C)
                                      AirHumRat,              // Air Humidity Ratio IN to this funcation (C)
                                      Coeff_HdAvVt,           // Mass Tansfer Coefficient Area Product (kg/s)
                                      LewisNum,               // External overall heat transfer coefficient(W/m2 C)
                                      OutletSolnTemp,         // Leaving solution temperature (C)
                                      OutletSolnConc,         // Leaving solution concentration (weight fraction)
                                      OutletSolnMassFlowRate, // Leaving solution mass flow rate (kg/s)
                                      OutletAirTemp,          // Leaving air dry bulb temperature(C)
                                      OutletAirHumRat,        // Leaving air humidity ratio
                                      TotWaterCoilLoad,       // Total heat transfer rate(W)
                                      WaterEvaporate);        // Total water evaporate (kg)
            std::cout << "************************************End ***************************" << endl;
            

            // Report outlet variables at nodes
            LiquidDesiccantCoil(CoilNum).OutletAirTemp = OutletAirTemp;
            LiquidDesiccantCoil(CoilNum).OutletAirHumRat = OutletAirHumRat;
            LiquidDesiccantCoil(CoilNum).OutletWaterTemp = OutletSolnTemp;
            // Report output results if the coil was operating

            LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate = TotWaterCoilLoad;
            LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate = TotWaterCoilLoad*0.5;
            //WaterCoil(CoilNum).SurfAreaWetFraction = SurfAreaWetFraction;
            //       WaterCoil(CoilNum)%OutletWaterEnthalpy = WaterCoil(CoilNum)%InletWaterEnthalpy+ &
            //                                WaterCoil(CoilNum)%TotWaterCoolingCoilRate/WaterCoil(CoilNum)%InletWaterMassFlowRate
            LiquidDesiccantCoil(CoilNum).OutletWaterEnthalpy = LiquidDesiccantCoil(CoilNum).InletWaterEnthalpy + SafeDivide(LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate,
                                                                                                        LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate);

        } else {
            // If both mass flow rates are zero, set outputs to inputs and return
            LiquidDesiccantCoil(CoilNum).OutletWaterTemp = LiquidDesiccantCoil(CoilNum).InletWaterTemp;
            LiquidDesiccantCoil(CoilNum).OutletAirTemp = LiquidDesiccantCoil(CoilNum).InletAirTemp;
            LiquidDesiccantCoil(CoilNum).OutletAirHumRat = LiquidDesiccantCoil(CoilNum).InletAirHumRat;
            LiquidDesiccantCoil(CoilNum).OutletWaterEnthalpy = LiquidDesiccantCoil(CoilNum).InletWaterEnthalpy;
            LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilEnergy = 0.0;
            LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilEnergy = 0.0;
            //WaterCoil(CoilNum).SurfAreaWetFraction = 0.0;

        } // End of the Flow or No flow If block
        LiquidDesiccantCoil(CoilNum).OutletWaterMassFlowRate = LiquidDesiccantCoil(CoilNum).InletWaterMassFlowRate;
        LiquidDesiccantCoil(CoilNum).OutletAirMassFlowRate = LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate;
        LiquidDesiccantCoil(CoilNum).OutletAirEnthalpy = PsyHFnTdbW(LiquidDesiccantCoil(CoilNum).OutletAirTemp, LiquidDesiccantCoil(CoilNum).OutletAirHumRat);
    }

   void LiqDesiccantCoil_Ntu_HPDM(int const CoilNum,            // Number of Coil
                              Real64 const SolnMassFlowRateIn,  // Solution mass flow rate IN to this function(kg/s)
                              Real64 const SolnTempIn,          // Solution temperature IN to this function (C)
                              Real64 const SolnConcIn,          // Solution concentration IN to this function (weight fraction)
                              Real64 const AirMassFlowRateIn,   // Air mass flow rate IN to this function(kg/s)
                              Real64 const AirTempIn,           // Air dry bulb temperature IN to this function(C)
                              Real64 const AirHumRat,           // Air Humidity Ratio IN to this funcation (C)
                              Real64 const Coeff_HdAvVt,        // Mass Tansfer Coefficient Area Product (kg/s) 
                              Real64 const LewisNum,            // External overall heat transfer coefficient(W/m2 C)
                              Real64 &OutletSolnTemp,           // Leaving solution temperature (C)
                              Real64 &OutletSolnConc,           // Leaving solution concentration (weight fraction)
                              Real64 &OutletSolnMassFlowRate,   // Leaving solution mass flow rate (kg/s)
                              Real64 &OutletAirTemp,            // Leaving air dry bulb temperature(C)
                              Real64 &OutletAirHumRat,          // Leaving air humidity ratio
                              Real64 &TotWaterCoilLoad,         // Total heat transfer rate(W)
                              Real64 &WaterEvaporate            // Total water evaporate (kg)

    )
    {
        using General::Iterate;
        using namespace std;

        double const BtuLbToJKg = 2326.0;

        // new varibales
        Real64 Patm = OutBaroPress;
        Real64 HdAvVt = Coeff_HdAvVt;

        Real64 ma = 0.3; // AirMassFlowRateIn;
        Real64 Tai = AirTempIn*1.8 + 32 ; // 30 * 1.8 + 32;  
        //Real64 Twbai = 23 * 1.8 + 32; // 
        Real64 Wai = AirHumRat; // PsyWFnTdbTwbPb((Tai - 32) / 1.8, (Twbai - 32) / 1.8, Patm);

        Real64 msi = 0.3; //SolnMassFlowRateIn; // 0.3;
        Real64 Xsi = SolnConcIn;            // 0 .4;
        Real64 Tsi = SolnTempIn * 1.8 + 32; // 25 * 1.8 + 32; // WaterTempIn; // degree C

        // Output Varibles
        Real64 Wao = 1.0, Tao;
        Real64 mso, Xso, Tso;
        Real64 Qtot, Wevaprate;

        // Local Variables
        Real64 Ntu, Effect;
        Real64 cps;
        Real64 wsatl, wsath, hsatl, hsath;
        Real64 csat, m_star;
        Real64 RHai, Hai = 1.0, HSSi, Hsi;
        Real64 RHao, Hao = 1.0, HSSo, Hso, Hso_p;
        Real64 HSSeff, WSSeff = 1.0, TSSeff = 1.0, HSSeff_p;
        Real64 TsoG = 20.0 * 1.8 + 32;
        Real64 TSSeff_G = 20.0 * 1.8 + 32;

        int iter_Tso, itmax_Tso = 10, icvg_Tso = 0;
        Real64 ResultX_Tso = 1.0, X1_Tso = 1.0, Y1_Tso = 1.0, error_Tso;

        int iter_Hsseff, itmax_Hsseff = 10, icvg_Hsseff = 0;
        Real64 ResultX_Hsseff = 1.0, X1_Hsseff = 1.0, Y1_Hsseff = 1.0, error_Hsseff;
        Ntu = HdAvVt / ma;
        Hsi = hftx9(Tsi, Xsi);

        Xso = Xsi;  // Xsi is the initial guess of Xso
        Tso = TsoG; // TsoG is the initial guess of Tso

        // --------------- Iteration starts -------------------------------
        if (Tso == Tsi) Tso = Tsi + 1.0;
        for (iter_Tso = 1; iter_Tso <= itmax_Tso; ++iter_Tso) {

            Hso = hftx9(Tso, Xso);
            cps = cpftx9(Tsi, Xsi); // Cps = (Hso - Hsi )/(Tso - Tsi)

            // #### Step 1: Calculate the saturation specific heat which is the derivative of the saturated air enthaply with respect to
            // temperature
            wsatl = cpftx9(Tsi, Xsi);
            wsath = cpftx9(Tso, Xso); // Tso & Xso unknown, iterative variables
            hsatl = (1.006 * (Tsi - 32) / 1.8 + wsatl * (1.84 * (Tsi - 32) / 1.8 + 2501)) / 2.326;
            hsath = (1.006 * (Tso - 32) / 1.8 + wsath * (1.84 * (Tso - 32) / 1.8 + 2501)) / 2.326;
            // hsatl = (1.006 * Tsi + wsatl * (1.84 * Tsi + 2501)) / 2.326;
            // hsath = (1.006 * Tso + wsath * (1.84 * Tso + 2501)) / 2.326;

            csat = (hsatl - hsath) / (Tsi - Tso); // P30 (3.23)

            // Step 2: Calculate the capacitance ratio
            m_star = (ma * csat) / (msi * cps); // P30 (3.24)
            // double Cr = ma / msi;

            // Step 3: Calculate the effectiveness
            Effect = (1 - exp(-Ntu * (1 - m_star))) / (1 - m_star * (exp(-Ntu * (1 - m_star)))); // p31 (3.26)

            // Step 4: Calculate the air outlet enthalpy
            RHai = PsyRhFnTdbWPb((Tai - 32) / 1.8, Wai, Patm); //  FluidRH(Tai, Wai, Patm, m_iFLD, 2); // place hold Res 8
            Hai = PsyHFnTdbRhPb((Tai - 32) / 1.8, RHai, Patm) / BtuLbToJKg; // per lb dry air  Hai
            HSSi = LDSatEnthalpy(Tsi, Xsi, Patm) / BtuLbToJKg;              // H_Ts.sat.i
            Hao = Hai + Effect * (HSSi - Hai);                 // res 0  ; p31 (3.27)

            // Step 5: Calculate the effective saturation enthalpy
            HSSeff = Hai + (Hao - Hai) / (1.0 - exp(-1.0 * Ntu)); // Res 1 ;  p31 (3.28) H_Ts,sat.eff

            // use the effective sauration enthaply and a saturated condition to find effective saturation humidity ratio
            TSSeff = TSSeff_G; // TSSeff = TEFF  " to see if can find WSSeff = f (HSSeff, Xso, Xsi)"
            for (iter_Hsseff = 1; iter_Hsseff <= itmax_Hsseff; ++iter_Hsseff) {

                WSSeff = wftx9(TSSeff, (Xsi + Xso) / 2.0);          // dRes6 = wftx9(TEFF, (Xsi + Xso) / 2.0) - WSSeff;
                HSSeff_p = PsyHFnTdbW((TSSeff - 32) / 1.8, WSSeff) / BtuLbToJKg; // Res 1 ; HUMEFF - W_Ts.sat.eff
                error_Hsseff = (HSSeff_p - HSSeff) / HSSeff;
                Iterate(ResultX_Hsseff, 0.01, TSSeff, error_Hsseff, X1_Hsseff, Y1_Hsseff, iter_Hsseff, icvg_Hsseff);
               // std::cout << "iter_Hsseff = " << iter_Hsseff << "   "
               //           << "error_Hsseff = " << error_Hsseff << "   "
               //           << "ResultX_Hsseff  = " << ResultX_Hsseff  << "   " 
               //           << "icvg_Hsseff = " << icvg_Hsseff << endl;
                TSSeff = ResultX_Hsseff;
                // If converged, exit loop
                if (icvg_Hsseff == 1) {
                    TSSeff_G = TSSeff;
                    goto TSSeff_Loop_exit;
                }
                // If not converged due to low Humidity Ratio approximate value at outlet conditions
                if (iter_Hsseff == itmax_Hsseff) {
                    // NoSatCurveIntersect = true;
                    // DesAirTempApparatusDewPt = PsyTdpFnWPb(WaterCoil(CoilNum).DesOutletAirHumRat, OutBaroPress);
                    // DesAirHumRatApparatusDewPt = PsyWFnTdpPb(DesAirTempApparatusDewPt, OutBaroPress);
                    TSSeff_G = TSSeff;
                    goto TSSeff_Loop_exit;
                }
            }
        TSSeff_Loop_exit:;

            // Step 6: calculate the air outlet humidity ratio
            Wao = WSSeff + (Wai - WSSeff) * exp(-1.0 * Ntu); // res 2 ; p31 (3.29) ; HUMOUT - Wao

            // Step 7: calculate soultion outlet conditions
            mso = msi + ma * (Wai - Wao); // res 3 ; MASSFLOWLIQOUT = mso , MASSFLOWLIQIN = msi

            // Step 8: Caculate the iterative variable Tso
            // Hsi = hftx9(Tsi, Xsi); // Hsi has been calcuated outside the iterative loop
            Xso = msi * Xsi / mso;                        // res 4
            Hso_p = (ma * (Hai - Hao) + msi * Hsi) / mso; // dRes5 = ma * (Hai - Hao) + msi * Hsi	- mso * hftx(Tso, Xso); // res 5
            error_Tso = (Hso_p - Hso) / Hso;
            Iterate(ResultX_Tso, 0.01, Tso, error_Tso, X1_Tso, Y1_Tso, iter_Tso, icvg_Tso);
           // std::cout << "iter_Tso = " << iter_Tso << "    "
           //           << "itmax_Tso = " << itmax_Tso << "    "
           //           << "error_Tso = " << error_Tso << endl
            //          << "ResultX_Tso = " << ResultX_Tso << endl
            //          << "icvg_Tso = " << icvg_Tso << endl
            //          << endl;
            Tso = ResultX_Tso;

            // Residual = (Hso_p - Hso) / Hso;
            // SolveRoot(0.001, MaxIte, SolFla, Tso, Residual, UA0, UA1, Par)
            // If converged, exit loop
            if (icvg_Tso == 1) {
                goto Tso_Loop_exit;
            }

            // If not converged due to low Humidity Ratio approximate value at outlet conditions
            if (iter_Tso == itmax_Tso) {
                // NoSatCurveIntersect = true;
                // DesAirTempApparatusDewPt = PsyTdpFnWPb(WaterCoil(CoilNum).DesOutletAirHumRat, OutBaroPress);
                // DesAirHumRatApparatusDewPt = PsyWFnTdpPb(DesAirTempApparatusDewPt, OutBaroPress);
                goto Tso_Loop_exit;
            }
        }
    Tso_Loop_exit:;

        // ---------------- Iteration ends ------------------------------------

        // Step 9: Caculate other outlet conditions
        // double Hao = FluidEnthalpy(Tao, RHao, PATM, m_iFLD, 1);  // Hao
        Tao = PsyTdbFnHW(Hao, Wao); // inline Real64 PsyTdbFnHW(Real64 const H, Real64 const dW)  // enthalpy {J/kg} // humidity ratio
        RHao = PsyRhFnTdbWPb((Tao - 32) / 1.8, Wao, Patm); // dRes9 = FluidRH(dTAIROUT, Wao, PATM, m_iFLD, 2) - RHao;

        // Step 10: Caculate other output variables
        Qtot = ma * (Hao - Hai) * BtuLbToJKg; // Res7
        Wevaprate = ma * (Wao - Wai); // dRes10 = ma * (Wao - Wai) - WEVAPRATE;

        //  ********************* new calcuation code: end *************************

        OutletSolnTemp = Tso;
        OutletSolnConc = Xso;
        OutletSolnMassFlowRate = mso;
        OutletAirTemp = Tao;
        OutletAirHumRat = Wao;
        TotWaterCoilLoad = Qtot;
        WaterEvaporate = Wevaprate;
    }
    
    // End Algorithm Section of the Module

    // Subroutine for Liquid Desiccant Coil calculation
    double CalculateDesHdAvVt(Real64 Qlat, // Coil latent load
                       Real64 msi,  // Solution mass flow rate IN to this function(kg/s)
                       Real64 Tsi,  // Solution temperature IN to this function (C)
                       Real64 Xsi,  // Solution concentration IN to this function (weight fraction)
                       //Real64 Tso,  // Solution temperature IN to this function (C)
                       Real64 ma,   // Air mass flow rate IN to this function(kg/s)
                       Real64 Tai,  // Air dry bulb temperature IN to this function(C)
                       Real64 Wai,  // Air Humidity Ratio IN to this funcation (C)
                       Real64 Tao,  // Air dry bulb temperature OUT to this function(C)
                       Real64 Wao   // Air Humidity Ratio OUT to this funcation (C)
    )
    {
        double const BtuLbToJKg = 2326.0;
        // new varibales
        Real64 Patm = OutBaroPress;
        // Output Varibles
        Real64 mso, Xso, Tso;

        Real64 LogMeanEnthDiff;
        Real64 DesUACoilEnth;
        Real64 DesHdAvVt; 

        // Local Variables

        Real64 RHai, Hai = 1.0, HSSi, Hsi;
        Real64 RHao, Hao = 1.0, HSSo, Hso;

        Real64 cps, wsatl, wsath, hsatl, hsath, csat; 
        Real64 mcp_min; 
        Real64 Error_Hso; 


   
        Hsi = hftx9(Tsi * 1.8 + 32, Xsi);
        mso = msi + ma * (Wai - Wao);
        Xso = msi * Xsi / mso;

        //Hso = msi * Hsi + (Qlat / BtuLbToJKg) / mso;
        //Hso = hftx9(Tso * 1.8 + 32, Xso);
        Hso = msi * Hsi + (Qlat / BtuLbToJKg) / mso;
        Tso = tfhx9(Hso, Xso);
        Error_Hso = hftx9(Tso, Xso)/Hso - 1;

        cps = cpftx9(Tsi * 1.8 + 32, Xsi); // Cps = (Hso - Hsi )/(Tso - Tsi)

        // #### Step 1: Calculate the saturation specific heat which is the derivative of the saturated air enthaply with respect to
        // temperature
        wsatl = cpftx9(Tsi * 1.8 + 32, Xsi);
        wsath = cpftx9(Tso * 1.8 + 32, Xso); // Tso & Xso unknown, iterative variables
        hsatl = (1.006 * (Tsi - 32) / 1.8 + wsatl * (1.84 * (Tsi - 32) / 1.8 + 2501)) / 2.326;
        hsath = (1.006 * (Tso - 32) / 1.8 + wsath * (1.84 * (Tso - 32) / 1.8 + 2501)) / 2.326;
        // hsatl = (1.006 * Tsi + wsatl * (1.84 * Tsi + 2501)) / 2.326;
        // hsath = (1.006 * Tso + wsath * (1.84 * Tso + 2501)) / 2.326;

        csat = (hsatl - hsath) / (Tsi - Tso) / 1.8; // P30 (3.23)

        // Step 2: Calculate the capacitance ratio
        mcp_min = min((ma * csat), (msi * cps));

        RHai = PsyRhFnTdbWPb(Tai, Wai, Patm);              //  FluidRH(Tai, Wai, Patm, m_iFLD, 2); // place hold Res 8
        Hai = PsyHFnTdbRhPb(Tai, RHai, Patm) / BtuLbToJKg; // per lb dry air  Hai
        HSSi = LDSatEnthalpy(Tsi, Xsi, Patm) / BtuLbToJKg; // H_Ts.sat.i

        RHao = PsyRhFnTdbWPb(Tao, Wao, Patm);              //  FluidRH(Tai, Wai, Patm, m_iFLD, 2); // place hold Res 8
        Hao = PsyHFnTdbRhPb(Tao, RHao, Patm) / BtuLbToJKg; // per lb dry air  Hai
        HSSo = LDSatEnthalpy(Tso, Xso, Patm) / BtuLbToJKg; // H_Ts.sat.i

        LogMeanEnthDiff = ((Hai - HSSo) - (Hao - HSSi)) / std::log((Hai - HSSo) / (Hao - HSSi));

        DesUACoilEnth = (Qlat / BtuLbToJKg) / LogMeanEnthDiff;
        DesHdAvVt = DesUACoilEnth / mcp_min;
        return (DesHdAvVt);
    };
    
    double TSHSX(double t, double x, double h){
        double resiual = abs(h - hftx9(t, x));
        return resiual;
    };

    double WSSE(double h, double x, double p){
        using namespace std;

        bool LOF = true;
        double relax = 0.0;
        double WTOL = 1.0e-5;
        double WSOL = 1.0;
        double WSSP = 1.0;
        double WAIR = 0.0;
        double SOLSLOPE = 1.0;
        double HUMP = 1.0;
        double AIRSLOPE = 1.0;
        double Wdiff = 1.0;
        double SLOPEdiff = 1.0;
        double TG = 20.0;
        double _WSSE = 1.0;
        if (h > 150) {
            relax = 0.3;
        }
        else {
            relax = 0.8;
        
        };

         while (abs(WSOL-WAIR) >= WTOL) {
             WSSP = wftx9((TG + 1) * 1.8 + 32, x);
             WSOL = wftx9(TG * 1.8 + 32, x);
             SOLSLOPE = WSSP - WSOL;
             HUMP = PsyWFnTdbH(TG + 1, h);
             WAIR = PsyWFnTdbH(TG, h);
             AIRSLOPE = HUMP - WAIR;
             Wdiff = WSOL - WAIR; 
             SLOPEdiff = AIRSLOPE - SOLSLOPE;
             if (SLOPEdiff < 1.0e-6) {
                 if (abs(WSOL - WAIR) < WTOL) {
                     _WSSE = WSOL;
                     return (_WSSE);
                 } else {
                     std::cout << "error in function WSSE " << endl;
                     return (999.0);
                     
                 } // end of if (abs(WSOL - WAIR) < WTOL)
             } // end of if (SLOPEdiff < 1.0e-6) 
             TG = TG + relax * (WSOL - WAIR) / (AIRSLOPE-SOLSLOPE);
        }

         _WSSE = WSOL;
        return (_WSSE);
    };

    double wftx9(double t, double xi)
    {
        // C*********************************************************************
        // C****** SUBROUTINE CALCULATES HUMIDITY RATIO OF MOIST AIR IN *********
        // C****** EQUILIBRIUM WITH LICL /WATER SOLUTION AS A FUNCTION  *********
        // C****** OF TEMP IN F AND CONCENTRATION IN PERCENTS           *********
        // C*********************************************************************
        //    double tc,pKpa;
        //    tc = (t-32)/1.8;
        //    if(isDehum)
        //        pKpa = (4.58208-0.159174*tc+0.0072594*pow(tc,2))
        //                +(-18.3816+0.5661*tc-0.019314*pow(tc,2))*x
        //                +(21.312-0.666*tc+0.01332*pow(tc,2))*pow(x,2);
        //    else
        //        pKpa = (16.294-0.8893*tc+0.01927*pow(tc,2))
        //                +(74.3-1.8035*tc-0.01875*pow(tc,2))*x
        //                +(-226.4+7.49*tc-0.039*pow(tc,2))*pow(x,2);
        //   data from Goswami 2001

        double psat, psatKpa, tk, pv1;
        double A, B, C, a25;
        double x = xi;

        pft3(psat, t);
        tk = (t - 32) / 1.8 + 273.15;
        psatKpa = psat * 6.895;
        A = 2 - pow((1 + pow((x / 0.28), 4.3)), 0.6);
        B = pow(1 + pow((x / 0.21), 5.1), 0.49) - 1;
        a25 = 1 - pow((1 + pow((x / 0.362), -4.75)), -0.4) - 0.03 * exp(-pow((x - 0.1), 2) / 0.005);
        C = tk / 647.1;
        pv1 = psatKpa * a25 * (A + B * C);

        //    double pv;
        //    pftx9(cmn,pv,t,x*100);
        //    pv = pv* 6.8947;

        const double w = 0.622 * (pv1 / (101.3 - pv1));

        return (w);
    };
    
    void pft3(double &p, double const &t)
    {
        // C***********************************************************************
        // C******  SUBROUTINE CALCULATES SATURATION PRESSURE IN PSIA  ************
        // C******  OF WATER AS A FUNCTION OF TEMPERATURE IN DEG F     ************
        // C***********************************************************************
        double tc = (t - 32.e0) / 1.8e0;
        double tk = tc + 273.15e0;
        double tau = 1.0e0 - tk / 647.14e0;
        if (tau < 1e-6) {
            tau = 1e-6;
        }
        double pkpa = 647.14e0 / tk *
                      (-7.85823e0 * tau + 1.83991e0 * pow(tau, 1.5e0) - 11.7811e0 * pow(tau, 3.0) + 22.6705e0 * pow(tau, 3.5e0) -
                       15.9393e0 * pow(tau, 4.0) + 1.77516e0 * pow(tau, 7.5e0));
        pkpa = 22064.e0 * exp(pkpa);
        p = pkpa / 6.895e0;
    };
    
    double cpftx9(double tsi, double xsi)
    {
        double ts = (tsi - 32) / 1.8;
        double T = (273.15 + ts);
        double xi = xsi / 100;
        double B0 = 1.43980, B1 = -1.24317, B2 = -0.12070, B3 = 0.12825, B4 = 0.62934, B5 = 58.5225, B6 = -105.6343, B7 = 47.7948;
        double theta = T / 228 - 1;
        double A0 = 88.7891, A1 = -120.1959, A2 = -16.9264, A3 = 52.4654, A4 = 0.10826, A5 = 0.46988;
        double cp_H2O = A0 + A1 * pow(theta, 0.02) + A2 * pow(theta, 0.04) + A3 * pow(theta, 0.06) + A4 * pow(theta, 1.8) + A5 * pow(theta, 8);
        double f1;
        if (xi < 0.31)
            f1 = B0 * xi + B1 * pow(xi, 2) + B2 * pow(xi, 3);
        else
            f1 = B3 + B4 * xi;
        double f2 = B5 * pow(theta, 0.02) + B6 * pow(theta, 0.04) + B7 * pow(theta, 0.06);
        double cps = cp_H2O * (1 - f1 * f2);
        cps = cps / 4.186798188;

        return (cps);
        //    qDebug()<<"LiCl cp"<<cps;
    };
    
    Real64 hftx9(Real64 t, Real64 x)
    {
        // C*********************************************************************
        // C******  SUBROUTINE  CALCULATES  ENTHALPY  IN  BTU/LB  OF   **********
        // C******  LICL /WATER  SOLUTION  AS  A  FUNCTION  OF  TEMP   **********
        // C******  IN  DEG  F  AND  CONC  IN  PERCENTS                **********
        // C*********************************************************************

        // C      IMPLICIT REAL*8(A-H,O-Z)
        //  double t0 = t;
        //  double x0 = x;
        //  double tsol = (t0 - 32.0f) / 1.8f;
        //  double tdum = (tsol + 25.f) / 2;
        //  double a0 = 1.002f - 0.0125f * x0 + (7.575e-05) * x0 * x0;
        //  double a1 = -0.0005554f - (1.518e-05) * x0 + (6.1828e-07) * x0 * x0;
        //  double a2 = (5.2266e-09) + (3.6623e-08) * x0 - (3.8345e-09) * x0 * x0;
        //  double cpsol = 4.184f * (a0 + a1 * tdum + a2 * tdum * tdum);
        //  double h0 = 560.7f + x0 * (17.63f * fem::dlog(x0) - 82.6f) + cpsol * (
        //    tsol - 25.f);
        //  double hs0 = h0 / 2.326f;

        double ts = (t - 32) / 1.8;
        double xs = x * 100.0;
        double A = -66.2324 + 11.2711 * xs - 0.79853 * pow(xs, 2) + (2.1534E-02) * pow(xs, 3) - (1.66352E-04) * pow(xs, 4);
        double B = 4.5751 - 0.146924 * xs + (6.307226E-03) * pow(xs, 2) - (1.38054E-04) * pow(xs, 3) + (1.06690E-06) * pow(xs, 4);
        double C = (-8.09689E-04) + (2.18145E-04) * xs - (1.36194E-05) * pow(xs, 2) + (3.20998E-07) * pow(xs, 3) - (2.64266E-09) * pow(xs, 4);
        double h = A + B * ts + C * pow(ts, 2);
        double hs = h / 2.326;

        return (hs);
    };
    
    Real64 tfhx9(Real64 h, Real64 x)
    {
        // FUNCTION INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   April 1, 2009
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // Given the specific enthalpy, relative humidity, and the
        // barometric pressure, the function returns the dry bulb temperature.

        // METHODOLOGY EMPLOYED:
        // Inverts PsyHFnTdbRhPb

        // REFERENCES:
        // none

        // Using/Aliasing
        using General::RoundSigDigits;
        using General::SolveRoot;

        // Return value
        Real64 T; // result=> humidity ratio

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // FUNCTION PARAMETER DEFINITIONS:
        int const MaxIte(500); // Maximum number of iterations
        Real64 const Acc(1.0); // Accuracy of result

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int SolFla;               // Flag of solver
        Real64 T0;                // lower bound for Tprov [C]
        Real64 T1;                // upper bound for Tprov [C]
        static Real64 Tprov(0.0); // provisional value of drybulb temperature [C]
        Array1D<Real64> Par(3);   // Par(1) = desired enthaply H [J/kg]
        // Par(2) = desired relative humidity (0.0 - 1.0)
        // Par(3) = barometric pressure [N/m2 (Pascals)]

        T0 = 1.0;
        T1 = 100.0;
        Par(1) = h;
        Par(2) = x;
        SolveRoot(Acc, MaxIte, SolFla, Tprov, SolnTempResidual, T0, T1, Par);
        // if the numerical inversion failed, issue error messages.
        if (SolFla == -1) {
            ShowSevereError("Calculation of soultion temperature failed in tfhx9(h,x)");
            ShowContinueError("   Iteration limit exceeded");
            //ShowContinueError("   H=[" + RoundSigDigits(H, 6) + "], RH=[" + RoundSigDigits(RH, 4) + "], PB=[" + RoundSigDigits(PB, 5) + "].");
        } else if (SolFla == -2) {
            ShowSevereError("Calculation of drybulb temperature failed in tfhx9(h,x)");
            ShowContinueError("  Bad starting values for Tdb");
            //ShowContinueError("   H=[" + RoundSigDigits(H, 6) + "], RH=[" + RoundSigDigits(RH, 4) + "], PB=[" + RoundSigDigits(PB, 5) + "].");
        }
        if (SolFla < 0) {
            T = 0.0;
        } else {
            T = Tprov;
        }

        return T;
    }
          
    Real64 SolnTempResidual(Real64 const t,        // test value of Tdb [C]
                            Array1D<Real64> const &Par // Par(1) = desired enthaply H [J/kg]
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR        
        //       DATE WRITTEN   
        //       MODIFIED
        
        // PURPOSE OF THIS FUNCTION:
        // Calculates residual function hdesired - hftx

        // METHODOLOGY EMPLOYED:
        // Calls PsyHFnTdbRhPb

        // REFERENCES:

        // Using/Aliasing
        //using Psychrometrics::PsyHFnTdbRhPb;

        // Return value
        Real64 Residuum; // residual to be minimized to zero

        // Argument array dimensioning

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:
        // Par(2) = desired relative humidity (0.0 - 1.0)
        // Par(3) = barometric pressure [N/m2 (Pascals)]

        // FUNCTION PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:

        Residuum = Par(1) - hftx9(t, Par(2));

        return Residuum;
    };

    double LDSatEnthalpy(double t, double x, double dPatm)
    {
        double Wlsati = wftx9(t, x);
        double dHret = PsyHFnTdbW((t-32)/1.8, Wlsati);
        return (dHret);
    };

    double PsyHFnTdbW_new(double T, double W)
    {
        const double cpad = 0.24050, hfgd = 1064.0, cpwd = 0.4095;
        //double W = max(0.0, W);
        if (W < 0.0) {
            W = 0.0;
        }
        double _AIR_H_TW = cpad * T + W * (hfgd + cpwd * T);
        return (_AIR_H_TW);
    };

    // Beginning of Update subroutines for the WaterCoil Module
    // *****************************************************************************
    void UpdateLiquideDesiccantCoil(int const CoilNum)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Richard Liesen
        //       DATE WRITTEN   1998
        //       MODIFIED       April 2004: Rahul Chillar
        //                      Feb 2010 B. Griffith, plant upgrades
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This subroutine updates the coil outlet nodes.

        // METHODOLOGY EMPLOYED:
        // Data is moved from the coil data structure to the coil outlet nodes.

        // REFERENCES:
        // na

        // Using/Aliasing
        using DataContaminantBalance::Contaminant;
        using PlantUtilities::SetComponentFlowRate;

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int AirInletNode;
        int WaterInletNode;
        int AirOutletNode;
        int WaterOutletNode;

        AirInletNode = LiquidDesiccantCoil(CoilNum).AirInletNodeNum;
        WaterInletNode = LiquidDesiccantCoil(CoilNum).WaterInletNodeNum;
        AirOutletNode = LiquidDesiccantCoil(CoilNum).AirOutletNodeNum;
        WaterOutletNode = LiquidDesiccantCoil(CoilNum).WaterOutletNodeNum;

        // Set the outlet air nodes of the LiquidDesiccantCoil
        Node(AirOutletNode).MassFlowRate = LiquidDesiccantCoil(CoilNum).OutletAirMassFlowRate;
        Node(AirOutletNode).Temp = LiquidDesiccantCoil(CoilNum).OutletAirTemp;
        Node(AirOutletNode).HumRat = LiquidDesiccantCoil(CoilNum).OutletAirHumRat;
        Node(AirOutletNode).Enthalpy = LiquidDesiccantCoil(CoilNum).OutletAirEnthalpy;

        Node(WaterOutletNode).Temp = LiquidDesiccantCoil(CoilNum).OutletWaterTemp;
        Node(WaterOutletNode).Enthalpy = LiquidDesiccantCoil(CoilNum).OutletWaterEnthalpy;

        // Set the outlet nodes for properties that just pass through & not used
        Node(AirOutletNode).Quality = Node(AirInletNode).Quality;
        Node(AirOutletNode).Press = Node(AirInletNode).Press;
        Node(AirOutletNode).MassFlowRateMin = Node(AirInletNode).MassFlowRateMin;
        Node(AirOutletNode).MassFlowRateMax = Node(AirInletNode).MassFlowRateMax;
        Node(AirOutletNode).MassFlowRateMinAvail = Node(AirInletNode).MassFlowRateMinAvail;
        Node(AirOutletNode).MassFlowRateMaxAvail = Node(AirInletNode).MassFlowRateMaxAvail;
        if (Contaminant.CO2Simulation) {
            Node(AirOutletNode).CO2 = Node(AirInletNode).CO2;
        }
        if (Contaminant.GenericContamSimulation) {
            Node(AirOutletNode).GenContam = Node(AirInletNode).GenContam;
        }
    }

    //        End of Update subroutines for the WaterCoil Module
    // *****************************************************************************

    // Beginning of Reporting subroutines for the WaterCoil Module
    // *****************************************************************************
    void ReportLiquideDesiccantCoil(int const CoilNum)
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Richard Liesen
        //       DATE WRITTEN   1998
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This subroutine updates the report variable for the coils.

        // METHODOLOGY EMPLOYED:
        // NA

        // REFERENCES:
        // na

        // Using/Aliasing
        //using DataWater::WaterStorage;

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        static std::string const RoutineName("ReportLiquidDesiccantCoil");

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        Real64 RhoWater;
        Real64 Tavg;
        Real64 SpecHumOut;
        Real64 SpecHumIn;
        Real64 ReportingConstant;

        if (LiquidDesiccantCoil(CoilNum).reportCoilFinalSizes) {
            if (!DataGlobals::WarmupFlag && !DataGlobals::DoingHVACSizingSimulations && !DataGlobals::DoingSizing) {
                std::string coilObjClassName;
             //   if (LiquidDesiccantCoil(CoilNum).WaterCoilType_Num == WaterCoil_SimpleHeating) {
             //       coilObjClassName = "Coil:Heating:Water";
             //       coilSelectionReportObj->setCoilFinalSizes(LiquidDesiccantCoil(CoilNum).Name,
             //                                                 coilObjClassName,
             //                                                 LiquidDesiccantCoil(CoilNum).DesWaterHeatingCoilRate,
             //                                                 LiquidDesiccantCoil(CoilNum).DesWaterHeatingCoilRate,
             //                                                 LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate,
             //                                                 LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate);
             //       LiquidDesiccantCoil(CoilNum).reportCoilFinalSizes = false;
             //   } else if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_DetFlatFinCooling) {
             //       coilObjClassName = "Coil:Cooling:Water:DetailedGeometry";
             //       coilSelectionReportObj->setCoilFinalSizes(WaterCoil(CoilNum).Name,
             //                                                 coilObjClassName,
             //                                                 WaterCoil(CoilNum).DesWaterCoolingCoilRate,
             //                                                 -999.0,
             //                                                 WaterCoil(CoilNum).DesAirVolFlowRate,
             //                                                 WaterCoil(CoilNum).MaxWaterVolFlowRate);
             //       WaterCoil(CoilNum).reportCoilFinalSizes = false;
             //   } else 
                if (LiquidDesiccantCoil(CoilNum).LiquidDesiccantCoilType_Num == LiquidDesiccantCoil_Cooling) {
                    coilObjClassName = "Coil:Cooling:LiquidDesiccant";
                    coilSelectionReportObj->setCoilFinalSizes(LiquidDesiccantCoil(CoilNum).Name,
                                                              coilObjClassName,
                                                              LiquidDesiccantCoil(CoilNum).DesWaterCoolingCoilRate,
                                                              -999.0,
                                                              LiquidDesiccantCoil(CoilNum).DesAirVolFlowRate,
                                                              LiquidDesiccantCoil(CoilNum).MaxWaterVolFlowRate);
                    LiquidDesiccantCoil(CoilNum).reportCoilFinalSizes = false;
                }
            }
        }
        ReportingConstant = TimeStepSys * SecInHour;
        // report the WaterCoil energy from this component
       // LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilEnergy = LiquidDesiccantCoil(CoilNum).TotWaterHeatingCoilRate * ReportingConstant;
        LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilEnergy = LiquidDesiccantCoil(CoilNum).TotWaterCoolingCoilRate * ReportingConstant;
        LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilEnergy = LiquidDesiccantCoil(CoilNum).SenWaterCoolingCoilRate * ReportingConstant;

        // report the WaterCoil water collection to water storage tank (if needed)
        /*
        if (LiquidDesiccantCoil(CoilNum).CondensateCollectMode == CondensateToTank) {
            // calculate and report condensation rates  (how much water extracted from the air stream)
            // water volumetric flow of water in m3/s for water system interactions
            //  put here to catch all types of DX coils
            Tavg = (LiquidDesiccantCoil(CoilNum).InletAirTemp - LiquidDesiccantCoil(CoilNum).OutletAirTemp) / 2.0;

            RhoWater = GetDensityGlycol(
                PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidName, Tavg, PlantLoop(LiquidDesiccantCoil(CoilNum).WaterLoopNum).FluidIndex, RoutineName);
            //   CR9155 Remove specific humidity calculations
            SpecHumIn = LiquidDesiccantCoil(CoilNum).InletAirHumRat;
            SpecHumOut = LiquidDesiccantCoil(CoilNum).OutletAirHumRat;
            //  mdot * del HumRat / rho water
            LiquidDesiccantCoil(CoilNum).CondensateVdot = max(0.0, (LiquidDesiccantCoil(CoilNum).InletAirMassFlowRate * (SpecHumIn - SpecHumOut) / RhoWater));
            LiquidDesiccantCoil(CoilNum).CondensateVol = LiquidDesiccantCoil(CoilNum).CondensateVdot * ReportingConstant;

            WaterStorage(LiquidDesiccantCoil(CoilNum).CondensateTankID).VdotAvailSupply(LiquidDesiccantCoil(CoilNum).CondensateTankSupplyARRID) =
                LiquidDesiccantCoil(CoilNum).CondensateVdot;
            WaterStorage(LiquidDesiccantCoil(CoilNum).CondensateTankID).TwaterSupply(LiquidDesiccantCoil(CoilNum).CondensateTankSupplyARRID) =
                LiquidDesiccantCoil(CoilNum).OutletAirTemp;
        }
        */


    }

    //        End of Reporting subroutines for the WaterCoil Module
    // *****************************************************************************

    // Beginning of Coil Utility subroutines for the Detailed Model
    // *****************************************************************************

    // Real64 SimpleHeatingCoilUAResidual
    /*
    Real64 SimpleHeatingCoilUAResidual(Real64 const UA,           // UA of coil
                                       Array1D<Real64> const &Par // par(1) = design coil load [W]
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   November 2001
        //       MODIFIED
        //       RE-ENGINEERED

        // PURPOSE OF THIS FUNCTION:
        // Calculates residual function (Design Coil Load - Coil Heating Output) / Design Coil Load.
        // Coil Heating Output depends on the UA which is being varied to zero the residual.

        // METHODOLOGY EMPLOYED:
        // Puts UA into the water coil data structure, calls CalcSimpleHeatingCoil, and calculates
        // the residual as defined above.

        // REFERENCES:

        // USE STATEMENTS:
        using DataSizing::DataDesignCoilCapacity; // Data variable used in eq component sizing routines

        // Return value
        Real64 Residuum; // residual to be minimized to zero

        // Argument array dimensioning

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // FUNCTION PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int CoilIndex;
        int FanOpMode;
        Real64 PartLoadRatio;

        CoilIndex = int(Par(2));
        FanOpMode = (Par(3) == 1.0 ? CycFanCycCoil : ContFanCycCoil);
        PartLoadRatio = Par(4);
        LiquidDesiccantCoil(CoilIndex).UACoilVariable = UA;
        CalcSimpleHeatingCoil(CoilIndex, FanOpMode, PartLoadRatio, SimCalc);
        Residuum = (Par(1) - LiquidDesiccantCoil(CoilIndex).TotWaterHeatingCoilRate) / Par(1);
        DataDesignCoilCapacity = LiquidDesiccantCoil(CoilIndex).TotWaterHeatingCoilRate;

        return Residuum;
    }
    */

    //  SimpleCoolingCoilUAResidualused by ReportSizingManager.cc
    /*
    Real64 SimpleCoolingCoilUAResidual(Real64 const UA,           // UA of coil
                                       Array1D<Real64> const &Par // par(1) = design coil load [W]
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   September 2011
        //       MODIFIED
        //       RE-ENGINEERED

        // PURPOSE OF THIS FUNCTION:
        // Calculates residual function (Design Coil Load - Coil Cooling Output) / Design Coil Load.
        // Coil Cooling Output depends on the UA which is being varied to zero the residual.

        // METHODOLOGY EMPLOYED:
        // Puts UA into the water coil data structure, calls CoolingCoil, and calculates
        // the residual as defined above.

        // REFERENCES:

        // USE STATEMENTS:
        // na

        // Return value
        Real64 Residuum; // residual to be minimized to zero

        // Argument array dimensioning

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // FUNCTION PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int CoilIndex;
        int FanOpMode;
        Real64 PartLoadRatio;

        CoilIndex = int(Par(2));
        FanOpMode = (Par(3) == 1.0 ? CycFanCycCoil : ContFanCycCoil);
        PartLoadRatio = Par(4);
        LiquidDesiccantCoil(CoilIndex).UACoilExternal = UA;
        LiquidDesiccantCoil(CoilIndex).UACoilInternal = LiquidDesiccantCoil(CoilIndex).UACoilExternal * 3.3;
        LiquidDesiccantCoil(CoilIndex).UACoilTotal = 1.0 / (1.0 / LiquidDesiccantCoil(CoilIndex).UACoilExternal + 1.0 / LiquidDesiccantCoil(CoilIndex).UACoilInternal);
        LiquidDesiccantCoil(CoilIndex).TotCoilOutsideSurfArea = EstimateHEXSurfaceArea(CoilIndex);
        LiquidDesiccantCoil(CoilIndex).UACoilInternalPerUnitArea = WaterCoil(CoilIndex).UACoilInternal / WaterCoil(CoilIndex).TotCoilOutsideSurfArea;
        WaterCoil(CoilIndex).UAWetExtPerUnitArea = WaterCoil(CoilIndex).UACoilExternal / WaterCoil(CoilIndex).TotCoilOutsideSurfArea;
        WaterCoil(CoilIndex).UADryExtPerUnitArea = WaterCoil(CoilIndex).UAWetExtPerUnitArea;

        CoolingCoil(CoilIndex, true, DesignCalc, FanOpMode, PartLoadRatio);

        Residuum = (Par(1) - WaterCoil(CoilIndex).TotWaterCoolingCoilRate) / Par(1);

        return Residuum;
    }
    */

    // Iterate Routine for Cooling Coil

    // void CheckWaterCoilSchedule used by OutdoorAirUnit.cc , UnitVentilator.cc ....
    /*
    void CheckWaterCoilSchedule(std::string const &EP_UNUSED(CompType), // unused1208
                                std::string const &CompName,
                                Real64 &Value,
                                int &CompIndex)
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Linda Lawrie
        //       DATE WRITTEN   October 2005
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // <description>

        // Using/Aliasing
        using General::TrimSigDigits;

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int CoilNum;

        // Obtains and Allocates WaterCoil related parameters from input file
        if (GetWaterCoilsInputFlag) { // First time subroutine has been entered
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        // Find the correct Coil number
        if (CompIndex == 0) {
            CoilNum = UtilityRoutines::FindItemInList(CompName, WaterCoil);
            if (CoilNum == 0) {
                ShowFatalError("CheckWaterCoilSchedule: Coil not found=" + CompName);
            }
            CompIndex = CoilNum;
            Value = GetCurrentScheduleValue(WaterCoil(CoilNum).SchedPtr); // not scheduled?
        } else {
            CoilNum = CompIndex;
            if (CoilNum > NumWaterCoils || CoilNum < 1) {
                ShowFatalError("CheckWaterCoilSchedule: Invalid CompIndex passed=" + TrimSigDigits(CoilNum) +
                               ", Number of Heating Coils=" + TrimSigDigits(NumWaterCoils) + ", Coil name=" + CompName);
            }
            if (CompName != WaterCoil(CoilNum).Name) {
                ShowFatalError("CheckWaterCoilSchedule: Invalid CompIndex passed=" + TrimSigDigits(CoilNum) + ", Coil name=" + CompName +
                               ", stored Coil Name for that index=" + WaterCoil(CoilNum).Name);
            }
            Value = GetCurrentScheduleValue(WaterCoil(CoilNum).SchedPtr); // not scheduled?
        }
    }
    */
    
    // Real64 GetCoilMaxWaterFlowRate used by AirLoopHVACDOAS.cc ....
    /*
    Real64 GetCoilMaxWaterFlowRate(std::string const &CoilType, // must match coil types in this module
                                   std::string const &CoilName, // must match coil names for the coil type
                                   bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Linda Lawrie
        //       DATE WRITTEN   November 2006
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the max water flow rate for the given coil and returns it.  If
        // incorrect coil type or name is given, ErrorsFound is returned as true and capacity is returned
        // as negative.

        // Return value
        Real64 MaxWaterFlowRate; // returned max water flow rate of matched coil

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;

        // Obtains and Allocates WaterCoil related parameters from input file
        if (GetWaterCoilsInputFlag) { // First time subroutine has been entered
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        WhichCoil = 0;
        if (UtilityRoutines::SameString(CoilType, "Coil:Heating:Water") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water:DetailedGeometry") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                // coil does not specify MaxWaterFlowRate
                MaxWaterFlowRate = WaterCoil(WhichCoil).MaxWaterVolFlowRate;
            }
        } else {
            WhichCoil = 0;
        }

        if (WhichCoil == 0) {
            ShowSevereError("GetCoilMaxWaterFlowRate: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
            ShowContinueError("... Max Water Flow rate returned as -1000.");
            ErrorsFound = true;
            MaxWaterFlowRate = -1000.0;
        }

        return MaxWaterFlowRate;
    }
    */

    //int GetCoilInletNode
    /*
    int GetCoilInletNode(EnergyPlusData &EP_UNUSED(state), std::string const &CoilType, // must match coil types in this module
                         std::string const &CoilName, // must match coil names for the coil type
                         bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         R. Raustad
        //       DATE WRITTEN   March 2007
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the given coil and returns the inlet node number.  If
        // incorrect coil type or name is given, ErrorsFound is returned as true and node number is returned
        // as zero.

        // Return value
        int NodeNumber; // returned node number of matched coil

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;

        // Obtains and Allocates DXCoils
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        NodeNumber = 0;
        WhichCoil = 0;
        if (UtilityRoutines::SameString(CoilType, "Coil:Heating:Water") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water:DetailedGeometry") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                NodeNumber = WaterCoil(WhichCoil).AirInletNodeNum;
            }
        } else {
            WhichCoil = 0;
        }

        if (WhichCoil == 0) {
            ShowSevereError("GetCoilInletNode: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
            ErrorsFound = true;
            NodeNumber = 0;
        }

        return NodeNumber;
    }
    */

    //int GetCoilOutletNode
    /*
    int GetCoilOutletNode(EnergyPlusData &EP_UNUSED(state), std::string const &CoilType, // must match coil types in this module
                          std::string const &CoilName, // must match coil names for the coil type
                          bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         R. Raustad
        //       DATE WRITTEN   March 2007
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the given coil and returns the inlet node number.  If
        // incorrect coil type or name is given, ErrorsFound is returned as true and node number is returned
        // as zero.

        // Return value
        int NodeNumber; // returned node number of matched coil

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;

        // Obtains and Allocates DXCoils
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        WhichCoil = 0;
        NodeNumber = 0;
        if (UtilityRoutines::SameString(CoilType, "Coil:Heating:Water") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water:DetailedGeometry") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                NodeNumber = WaterCoil(WhichCoil).AirOutletNodeNum;
            }
        } else {
            WhichCoil = 0;
        }

        if (WhichCoil == 0) {
            ShowSevereError("GetCoilOutletNode: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName +
                            "\" when accessing coil outlet node number.");
            ErrorsFound = true;
            NodeNumber = 0;
        }

        return NodeNumber;
    }
    */

    //int GetCoilWaterInletNode
    /*
    int GetCoilWaterInletNode(std::string const &CoilType, // must match coil types in this module
                              std::string const &CoilName, // must match coil names for the coil type
                              bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         R. Raustad
        //       DATE WRITTEN   July 2007
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the given coil and returns the inlet water control node number.  If
        // incorrect coil type or name is given, ErrorsFound is returned as true and node number is returned
        // as zero.

        // Return value
        int NodeNumber; // returned node number of matched coil

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;

        // Obtains and Allocates DXCoils
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        NodeNumber = 0;
        WhichCoil = 0;
        if (UtilityRoutines::SameString(CoilType, "Coil:Heating:Water") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water:DetailedGeometry") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                NodeNumber = WaterCoil(WhichCoil).WaterInletNodeNum;
            }
        } else {
            WhichCoil = 0;
        }

        if (WhichCoil == 0) {
            ShowSevereError("GetCoilWaterInletNode: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
            ErrorsFound = true;
            NodeNumber = 0;
        }

        return NodeNumber;
    }
    */

    // int GetCoilWaterOutletNode
    /*
    int GetCoilWaterOutletNode(std::string const &CoilType, // must match coil types in this module
                               std::string const &CoilName, // must match coil names for the coil type
                               bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         R. Raustad
        //       DATE WRITTEN   July 2007
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the given coil and returns the outlet water node number.  If
        // incorrect coil type or name is given, ErrorsFound is returned as true and node number is returned
        // as zero.

        // Return value
        int NodeNumber; // returned node number of matched coil

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;

        // Obtains and Allocates DXCoils
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        NodeNumber = 0;
        WhichCoil = 0;
        if (UtilityRoutines::SameString(CoilType, "Coil:Heating:Water") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water:DetailedGeometry") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                NodeNumber = WaterCoil(WhichCoil).WaterOutletNodeNum;
            }
        } else {
            WhichCoil = 0;
        }

        if (WhichCoil == 0) {
            ShowSevereError("GetCoilWaterOutletNode: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
            ErrorsFound = true;
            NodeNumber = 0;
        }

        return NodeNumber;
    }
    */


    //void SetCoilDesFlow
    /*
    void SetCoilDesFlow(std::string const &CoilType, // must match coil types in this module
                        std::string const &CoilName, // must match coil names for the coil type
                        Real64 const CoilDesFlow,    // coil volumetric air flow rate [m3/s]
                        bool &ErrorsFound            // set to true if problem
    )
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   May 2009
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This routine is designed to set the design air volume flow rate in the
        // water coil data structure. Some of the coil types do not have this datum as
        // an input parameter and it is needed for calculating capacity for output reporting.

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int WhichCoil; // index to coil

        if (GetWaterCoilsInputFlag) { // First time subroutine has been entered
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        if (UtilityRoutines::SameString(CoilType, "Coil:Heating:Water") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water:DetailedGeometry") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                if (UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water") && WaterCoil(WhichCoil).DesAirVolFlowRate < 0.0) {
                    WaterCoil(WhichCoil).DesAirVolFlowRate = CoilDesFlow;
                } else {
                    WaterCoil(WhichCoil).DesAirVolFlowRate = CoilDesFlow;
                }
            } else {
                ShowSevereError("GetCoilMaxWaterFlowRate: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
                ErrorsFound = true;
            }
        }
    }
    */

    // GetWaterCoilDesAirFlow
    /*
    Real64 GetWaterCoilDesAirFlow(std::string const &CoilType, // must match coil types in this module
                                  std::string const &CoilName, // must match coil names for the coil type
                                  bool &ErrorsFound            // set to true if problem
    )
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   May 2009
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This routine is designed to set the design air volume flow rate in the
        // water coil data structure. Some of the coil types do not have this datum as
        // an input parameter and it is needed for calculating capacity for output reporting.

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int WhichCoil; // index to coil
        Real64 CoilDesAirFlow;

        CoilDesAirFlow = 0.0;

        if (GetWaterCoilsInputFlag) { // First time subroutine has been entered
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        if (UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                CoilDesAirFlow = WaterCoil(WhichCoil).DesAirVolFlowRate;
            } else {
                ShowSevereError("GetWaterCoilDesAirFlowRate: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
                ErrorsFound = true;
            }
        } else {
            ShowSevereError("GetWaterCoilDesAirFlowRate: Funciton not valid for Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
            ErrorsFound = true;
        }

        return CoilDesAirFlow;
    }
    */

    // CheckActuatorNode
    /*
    void CheckActuatorNode(int const ActuatorNodeNum, // input actuator node number
                           int &iNodeType,            // Cooling or Heating or 0
                           bool &NodeNotFound         // true if matching water inlet node not found
    )
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   January 2009
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This subroutine checks that the input actuator node number is matched by
        // the water inlet node number of some water coil

        // METHODOLOGY EMPLOYED:
        // na

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // FUNCTION PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;
        int CoilNum;

        // Obtains and Allocates DXCoils
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        WhichCoil = 0;
        iNodeType = 0;
        NodeNotFound = true;
        for (CoilNum = 1; CoilNum <= NumWaterCoils; ++CoilNum) {
            if (WaterCoil(CoilNum).WaterInletNodeNum == ActuatorNodeNum) {
                WhichCoil = CoilNum;
                iNodeType = WaterCoil(CoilNum).WaterCoilType;
                NodeNotFound = false;
            }
        }
    }
    */

    /*
    void CheckForSensorAndSetPointNode(EnergyPlusData &state, int const SensorNodeNum, // controller sensor node number
                                       int const ControlledVar, // controlled variable type
                                       bool &NodeNotFound       // true if matching air outlet node not found
    )
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Bereket Nigusse
        //       DATE WRITTEN   March 2013
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // This subroutine checks that the sensor node number matches the air outlet node number
        // of some water coils

        // METHODOLOGY EMPLOYED:
        // na

        // REFERENCES:
        // na

        // Using/Aliasing
        using EMSManager::CheckIfNodeSetPointManagedByEMS;
        using EMSManager::iHumidityRatioMaxSetPoint;
        using EMSManager::iTemperatureSetPoint;
        using SetPointManager::iCtrlVarType_MaxHumRat;
        using SetPointManager::iCtrlVarType_Temp;
        using SetPointManager::NodeHasSPMCtrlVarType;

        // USE HVACControllers,     ONLY: iTemperature, iHumidityRatio, iTemperatureAndHumidityRatio

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        static std::string const RoutineName("CheckForSensorAndSetpointNode: ");
        int const iTemperature(1);
        int const iHumidityRatio(2);
        int const iTemperatureAndHumidityRatio(3);

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;             // water coil index
        int CoilNum;               // counter
        std::string WaterCoilType; // water coil type
        bool EMSSetPointErrorFlag; // flag true is EMS is used to set node setpoints

        // Obtains and Allocates DXCoils
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        WhichCoil = 0;
        NodeNotFound = true;

        for (CoilNum = 1; CoilNum <= NumWaterCoils; ++CoilNum) {
            if (SensorNodeNum != WaterCoil(CoilNum).AirOutletNodeNum) continue;
            NodeNotFound = false;
            WhichCoil = CoilNum;
            break;
        }
        // now if the sensor node is on the water coil air outlet node then check that
        // a setpoint is also specified on the water coil outlet node
        if (!NodeNotFound) {
            if (WhichCoil > 0) {
               // if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_DetFlatFinCooling) {
               //     WaterCoilType = "Coil:Cooling:Water:DetailedGeometry";
               // } else 
                if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_Cooling) {
                    WaterCoilType = "Coil:Cooling:Water";
                } else if (WaterCoil(CoilNum).WaterCoilType_Num == WaterCoil_SimpleHeating) {
                    WaterCoilType = "Coil:Heating:Water";
                }
                EMSSetPointErrorFlag = false;
                {
                    auto const SELECT_CASE_var(ControlledVar);
                    if (SELECT_CASE_var == iTemperature) {
                        CheckIfNodeSetPointManagedByEMS(SensorNodeNum, iTemperatureSetPoint, EMSSetPointErrorFlag);
                        if (EMSSetPointErrorFlag) {
                            if (!NodeHasSPMCtrlVarType(state, SensorNodeNum, iCtrlVarType_Temp)) {
                                ShowWarningError(RoutineName + WaterCoilType + "=\"" + WaterCoil(WhichCoil).Name + "\". ");
                                ShowContinueError(" ..Temperature setpoint not found on coil air outlet node.");
                                ShowContinueError(
                                    " ..The setpoint may have been placed on a node downstream of the coil or on an airloop outlet node.");
                                ShowContinueError(" ..Specify the setpoint and the sensor on the coil air outlet node when possible.");
                            }
                        }
                    } else if (SELECT_CASE_var == iHumidityRatio) {
                        CheckIfNodeSetPointManagedByEMS(SensorNodeNum, iHumidityRatioMaxSetPoint, EMSSetPointErrorFlag);
                        if (EMSSetPointErrorFlag) {
                            if (!NodeHasSPMCtrlVarType(state, SensorNodeNum, iCtrlVarType_MaxHumRat)) {
                                ShowWarningError(RoutineName + WaterCoilType + "=\"" + WaterCoil(WhichCoil).Name + "\". ");
                                ShowContinueError(" ..Humidity ratio setpoint not found on coil air outlet node.");
                                ShowContinueError(
                                    " ..The setpoint may have been placed on a node downstream of the coil or on an airloop outlet node.");
                                ShowContinueError(" ..Specify the setpoint and the sensor on the coil air outlet node when possible.");
                            }
                        }
                    } else if (SELECT_CASE_var == iTemperatureAndHumidityRatio) {
                        CheckIfNodeSetPointManagedByEMS(SensorNodeNum, iTemperatureSetPoint, EMSSetPointErrorFlag);
                        if (EMSSetPointErrorFlag) {
                            if (!NodeHasSPMCtrlVarType(state, SensorNodeNum, iCtrlVarType_Temp)) {
                                ShowWarningError(RoutineName + WaterCoilType + "=\"" + WaterCoil(WhichCoil).Name + "\". ");
                                ShowContinueError(" ..Temperature setpoint not found on coil air outlet node.");
                                ShowContinueError(
                                    " ..The setpoint may have been placed on a node downstream of the coil or on an airloop outlet node.");
                                ShowContinueError(" ..Specify the setpoint and the sensor on the coil air outlet node when possible.");
                            }
                        }
                        EMSSetPointErrorFlag = false;
                        CheckIfNodeSetPointManagedByEMS(SensorNodeNum, iHumidityRatioMaxSetPoint, EMSSetPointErrorFlag);
                        if (EMSSetPointErrorFlag) {
                            if (!NodeHasSPMCtrlVarType(state, SensorNodeNum, iCtrlVarType_MaxHumRat)) {
                                ShowWarningError(RoutineName + WaterCoilType + "=\"" + WaterCoil(WhichCoil).Name + "\". ");
                                ShowContinueError(" ..Humidity ratio setpoint not found on coil air outlet node.");
                                ShowContinueError(
                                    " ..The setpoint may have been placed on a node downstream of the coil or on an airloop outlet node.");
                                ShowContinueError(" ..Specify the setpoint and the sensor on the coil air outlet node when possible.");
                            }
                        }
                    }
                }
            }
        }
    }
    */

    // TdbFnHRhPb, EnthalpyResidual
    /*
    Real64 TdbFnHRhPb(Real64 const H,  // specific enthalpy {J/kg}
                      Real64 const RH, // relative humidity value (0.0-1.0)
                      Real64 const PB  // barometric pressure {Pascals}
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   April 1, 2009
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // Given the specific enthalpy, relative humidity, and the
        // barometric pressure, the function returns the dry bulb temperature.

        // METHODOLOGY EMPLOYED:
        // Inverts PsyHFnTdbRhPb

        // REFERENCES:
        // none

        // Using/Aliasing
        using General::RoundSigDigits;
        using General::SolveRoot;

        // Return value
        Real64 T; // result=> humidity ratio

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // FUNCTION PARAMETER DEFINITIONS:
        int const MaxIte(500); // Maximum number of iterations
        Real64 const Acc(1.0); // Accuracy of result

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int SolFla;               // Flag of solver
        Real64 T0;                // lower bound for Tprov [C]
        Real64 T1;                // upper bound for Tprov [C]
        static Real64 Tprov(0.0); // provisional value of drybulb temperature [C]
        Array1D<Real64> Par(3);   // Par(1) = desired enthaply H [J/kg]
        // Par(2) = desired relative humidity (0.0 - 1.0)
        // Par(3) = barometric pressure [N/m2 (Pascals)]

        T0 = 1.0;
        T1 = 50.0;
        Par(1) = H;
        Par(2) = RH;
        Par(3) = PB;
        SolveRoot(Acc, MaxIte, SolFla, Tprov, EnthalpyResidual, T0, T1, Par);
        // if the numerical inversion failed, issue error messages.
        if (SolFla == -1) {
            ShowSevereError("Calculation of drybulb temperature failed in TdbFnHRhPb(H,RH,PB)");
            ShowContinueError("   Iteration limit exceeded");
            ShowContinueError("   H=[" + RoundSigDigits(H, 6) + "], RH=[" + RoundSigDigits(RH, 4) + "], PB=[" + RoundSigDigits(PB, 5) + "].");
        } else if (SolFla == -2) {
            ShowSevereError("Calculation of drybulb temperature failed in TdbFnHRhPb(H,RH,PB)");
            ShowContinueError("  Bad starting values for Tdb");
            ShowContinueError("   H=[" + RoundSigDigits(H, 6) + "], RH=[" + RoundSigDigits(RH, 4) + "], PB=[" + RoundSigDigits(PB, 5) + "].");
        }
        if (SolFla < 0) {
            T = 0.0;
        } else {
            T = Tprov;
        }

        return T;
    }
    */

    /*
    Real64 EnthalpyResidual(Real64 const Tprov,        // test value of Tdb [C]
                            Array1D<Real64> const &Par // Par(1) = desired enthaply H [J/kg]
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Fred Buhl
        //       DATE WRITTEN   April 2009
        //       MODIFIED
        //       RE-ENGINEERED

        // PURPOSE OF THIS FUNCTION:
        // Calculates residual function Hdesired - H(Tdb,Rh,Pb)

        // METHODOLOGY EMPLOYED:
        // Calls PsyHFnTdbRhPb

        // REFERENCES:

        // Using/Aliasing
        using Psychrometrics::PsyHFnTdbRhPb;

        // Return value
        Real64 Residuum; // residual to be minimized to zero

        // Argument array dimensioning

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:
        // Par(2) = desired relative humidity (0.0 - 1.0)
        // Par(3) = barometric pressure [N/m2 (Pascals)]

        // FUNCTION PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:

        Residuum = Par(1) - PsyHFnTdbRhPb(Tprov, Par(2), Par(3));

        return Residuum;
    }
    */

    // used by SimpleCoolingCoilUAResidual
    /*
    Real64 EstimateHEXSurfaceArea(int const CoilNum) // coil number, [-]
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Bereket A Nigusse, FSEC
        //       DATE WRITTEN   July 2010
        //       MODIFIED
        //       RE-ENGINEERED

        // PURPOSE OF THIS FUNCTION:
        // Splits the UA value of a simple coil:cooling:water heat exchanger model into
        // "A" and U" values.

        // METHODOLOGY EMPLOYED:
        // A typical design U overall heat transfer coefficient is used to split the "UA" into "A"
        // and "U" values. Currently a constant U value calculated for a typical cooling coil is
        // used. The assumptions used to calculate a typical U value are:
        //     (1) tube side water velocity of 2.0 [m/s]
        //     (2) inside to outside total surface area ratio (Ai/Ao) =  0.07 [-]
        //     (3) fins overall efficiency = 0.92 based on aluminum fin, 12 fins per inch, and
        //         fins area to total outside surafce area ratio of about 90%.
        //     (4) air side convection coefficient of 140.0 [W/m2C].  Assumes sensible convection
        //         of 58.0 [W/m2C] and 82.0 [W/m2C] sensible convection equivalent of the mass
        //         transfer coefficient converted using the approximate relation:
        //         hequivalent = hmasstransfer/CpAir.

        // REFERENCES:

        // USE STATEMENTS:

        // Return value

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // FUNCTION PARAMETER DEFINITIONS:
        static Real64 const OverallFinEfficiency(0.92); // Assumes aluminum fins, 12 fins per inch, fins
        // area of about 90% of external surface area Ao.

        static Real64 const AreaRatio(0.07); // Heat exchanger Inside to Outside surface area ratio
        // design values range from (Ai/Ao) = 0.06 to 0.08

        // Constant value air side heat transfer coefficient is assumed. This coefficient has sensible
        // (58.d0 [W/m2C]) and latent (82.d0 [W/m2C]) heat transfer coefficient components.
        static Real64 const hAirTubeOutside(58.0 + 82.0); // Air side heat transfer coefficient [W/m2C]

        // Tube side water convection heat transfer coefficient of the cooling coil is calculated for
        // inside tube diameter of 0.0122m (~0.5 inch nominal diameter) and water velocity 2.0 m/s:
        static Real64 const hWaterTubeInside(1429.0 * std::pow(2.0, 0.8) *
                                             std::pow(0.0122, -0.2)); // water (tube) side heat transfer coefficient [W/m2C]

        // Estimate the overall heat transfer coefficient, UOverallHeatTransferCoef in [W/(m2C)].
        // Neglecting tube wall and fouling resistance, the overall U value can be estimated as:
        // 1/UOverallHeatTransferCoef = 1/(hi*AreaRatio) + 1/(ho*OverallFinEfficiency)
        static Real64 const UOverallHeatTransferCoef_inv(
            1.0 / (hWaterTubeInside * AreaRatio) +
            1.0 / (hAirTubeOutside * OverallFinEfficiency)); // Inverse of overall heat transfer coefficient for coil [W/m2C]

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // FUNCTION LOCAL VARIABLE DECLARATIONS:

        WaterCoil(CoilNum).UACoilTotal = 1.0 / (1.0 / WaterCoil(CoilNum).UACoilExternal + 1.0 / WaterCoil(CoilNum).UACoilInternal);

        // the heat exchanger surface area is calculated as follows:
        return WaterCoil(CoilNum).UACoilTotal * UOverallHeatTransferCoef_inv; // Heat exchanger surface area [m2]
    }
    */

    /*
    int GetWaterCoilIndex(std::string const &CoilType, // must match coil types in this module
                          std::string const &CoilName, // must match coil names for the coil type
                          bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         B. Nigusse, FSEC
        //       DATE WRITTEN   Feb 2012
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the index for the given coil and returns it.  If incorrect coil
        // type or name is given, ErrorsFound is returned as true and node number is returned
        // as zero.

        // Return value
        int IndexNum; // returned coil index if matched coil

        // Obtains and allocates WaterCoil related parameters from input file
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        IndexNum = 0;
        if (CoilType == "COIL:HEATING:WATER") {
            IndexNum = UtilityRoutines::FindItemInList(CoilName, WaterCoil);
        } else if (CoilType == "COIL:COOLING:WATER") {
            IndexNum = UtilityRoutines::FindItemInList(CoilName, WaterCoil);
        } else if (CoilType == "COIL:COOLING:WATER:DETAILEDGEOMETRY") {
            IndexNum = UtilityRoutines::FindItemInList(CoilName, WaterCoil);
        } else {
            IndexNum = 0;
        }

        if (IndexNum == 0) {
            ShowSevereError("GetWaterCoilIndex: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
            ErrorsFound = true;
        }

        return IndexNum;
    }
    */

    // used by other subroutine such DesiccantDehumidifiers.cc ....
    /*
    Real64 GetWaterCoilCapacity(std::string const &CoilType, // must match coil types in this module
                                std::string const &CoilName, // must match coil names for the coil type
                                bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         R. Raustad, FSEC
        //       DATE WRITTEN   Sep 2013
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the capacity for the given coil and returns it.  If incorrect coil
        // type or name is given, ErrorsFound is returned as true and capacity is returned
        // as zero.

        // Return value
        Real64 Capacity; // returned coil capacity if matched coil

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int IndexNum; // index to water coil

        // Obtains and allocates WaterCoil related parameters from input file
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        Capacity = -1.0;

        if (CoilType == "COIL:HEATING:WATER") {
            IndexNum = UtilityRoutines::FindItemInList(CoilName, WaterCoil);
            Capacity = WaterCoil(IndexNum).DesWaterHeatingCoilRate;
        } else if (CoilType == "COIL:COOLING:WATER") {
            IndexNum = UtilityRoutines::FindItemInList(CoilName, WaterCoil);
            Capacity = WaterCoil(IndexNum).DesWaterCoolingCoilRate;
        } else if (CoilType == "COIL:COOLING:WATER:DETAILEDGEOMETRY") {
            IndexNum = UtilityRoutines::FindItemInList(CoilName, WaterCoil);
            Capacity = WaterCoil(IndexNum).DesWaterCoolingCoilRate;
        } else {
            IndexNum = 0;
        }

        if (IndexNum == 0) {
            ShowSevereError("GetWaterCoilCapacity: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
            ErrorsFound = true;
        }

        return Capacity;
    }
    */


    /*
    void UpdateWaterToAirCoilPlantConnection(int const CoilTypeNum,
                                             std::string const &CoilName,
                                             int const EP_UNUSED(EquipFlowCtrl), // Flow control mode for the equipment
                                             int const LoopNum,                  // Plant loop index for where called from
                                             int const LoopSide,                 // Plant loop side index for where called from
                                             int &CompIndex,                     // Chiller number pointer
                                             bool const EP_UNUSED(FirstHVACIteration),
                                             bool &InitLoopEquip // If not zero, calculate the max load for operating conditions
    )
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         B. Griffith
        //       DATE WRITTEN   February 2010
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // update sim routine called from plant

        // Using/Aliasing
        using DataGlobals::KickOffSimulation;
        using DataHVACGlobals::SimAirLoopsFlag;
        using DataHVACGlobals::SimZoneEquipmentFlag;
        using DataLoopNode::Node;
        using DataPlant::ccSimPlantEquipTypes;
        using DataPlant::PlantLoop;
        using General::TrimSigDigits;

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:

        int CoilNum;
        static bool DidAnythingChange(false); // set to true if conditions changed
        int InletNodeNum;
        int OutletNodeNum;

        // Find the correct water coil
        if (CompIndex == 0) {
            CoilNum = UtilityRoutines::FindItemInList(CoilName, WaterCoil);
            if (CoilNum == 0) {
                ShowFatalError("UpdateWaterToAirCoilPlantConnection: Specified Coil not one of Valid water coils=" + CoilName);
            }
            CompIndex = CoilNum;
        } else {
            CoilNum = CompIndex;
            if (CoilNum > NumWaterCoils || CoilNum < 1) {
                ShowFatalError("UpdateWaterToAirCoilPlantConnection:  Invalid CompIndex passed=" + TrimSigDigits(CoilNum) +
                               ", Number of Coils=" + TrimSigDigits(NumWaterCoils) + ", Entered Coil name=" + CoilName);
            }
            if (KickOffSimulation) {
                if (CoilName != WaterCoil(CoilNum).Name) {
                    ShowFatalError("UpdateWaterToAirCoilPlantConnection: Invalid CompIndex passed=" + TrimSigDigits(CoilNum) +
                                   ", Coil name=" + CoilName + ", stored Coil Name for that index=" + WaterCoil(CoilNum).Name);
                }
                if (CoilTypeNum != WaterCoil(CoilNum).WaterCoilType_Num) {
                    ShowFatalError("UpdateWaterToAirCoilPlantConnection: Invalid CompIndex passed=" + TrimSigDigits(CoilNum) +
                                   ", Coil name=" + CoilName + ", stored Coil Name for that index=" + ccSimPlantEquipTypes(CoilTypeNum));
                }
            }
        }

        if (InitLoopEquip) {
            return;
        }

        DidAnythingChange = false;

        InletNodeNum = WaterCoil(CoilNum).WaterInletNodeNum;
        OutletNodeNum = WaterCoil(CoilNum).WaterOutletNodeNum;

        if (Node(InletNodeNum).Temp != WaterCoil(CoilNum).InletWaterTemp) DidAnythingChange = true;

        if (Node(OutletNodeNum).Temp != WaterCoil(CoilNum).OutletWaterTemp) DidAnythingChange = true;

        if (Node(InletNodeNum).MassFlowRate != WaterCoil(CoilNum).OutletWaterMassFlowRate) {
            DidAnythingChange = true;
            Node(OutletNodeNum).MassFlowRate = Node(InletNodeNum).MassFlowRate; // make sure flows are consistent
        }

        if (Node(OutletNodeNum).MassFlowRate != WaterCoil(CoilNum).OutletWaterMassFlowRate) DidAnythingChange = true;

        if (DidAnythingChange) {
            // set sim flag for this loop
            PlantLoop(LoopNum).LoopSide(LoopSide).SimLoopSideNeeded = true;
            // set sim flags for air side users of coils

            SimAirLoopsFlag = true;
            SimZoneEquipmentFlag = true;
        } else { // nothing changed so turn off sim flag
            PlantLoop(LoopNum).LoopSide(LoopSide).SimLoopSideNeeded = false;
        }
    }
    */

    // used by other subroutine such UnitarySystem.cc 
    /*
    int GetWaterCoilAvailScheduleIndex(std::string const &CoilType, // must match coil types in this module
                                       std::string const &CoilName, // must match coil names for the coil type
                                       bool &ErrorsFound            // set to true if problem
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Chandan Sharma, FSEC
        //       DATE WRITTEN   February 2013
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function looks up the given coil and returns the availability schedule index.  If
        // incorrect coil type or name is given, ErrorsFound is returned as true and index is returned
        // as zero.

        // Return value
        int AvailSchIndex; // returned availability schedule of matched coil

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        int WhichCoil;

        // Obtains and Allocates HeatingCoil related parameters from input file
        // Obtains and Allocates DXCoils
        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        WhichCoil = 0;
        AvailSchIndex = 0;

        if (UtilityRoutines::SameString(CoilType, "Coil:Heating:Water") || UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water") ||
            UtilityRoutines::SameString(CoilType, "Coil:Cooling:Water:DetailedGeometry")) {
            WhichCoil = UtilityRoutines::FindItem(CoilName, WaterCoil);
            if (WhichCoil != 0) {
                AvailSchIndex = WaterCoil(WhichCoil).SchedPtr;
            }
        } else {
            WhichCoil = 0;
        }

        if (WhichCoil == 0) {
            ShowSevereError("GetCoilAvailScheduleIndex: Could not find Coil, Type=\"" + CoilType + "\" Name=\"" + CoilName + "\"");
            ErrorsFound = true;
            AvailSchIndex = 0;
        }

        return AvailSchIndex;
    }
    */

    // used by other subroutine such DesiccantDehumidifiers.cc ....
    /*
    void SetWaterCoilData(int const CoilNum,                       // Number of hot water heating Coil
                          bool &ErrorsFound,                       // Set to true if certain errors found
                          Optional_bool DesiccantRegenerationCoil, // Flag that this coil is used as regeneration air heating coil
                          Optional_int DesiccantDehumIndex         // Index for the desiccant dehum system where this caoil is used
    )
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Bereket Nigusse
        //       DATE WRITTEN   February 2016
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // This function sets data to water Heating Coil using the coil index and arguments passed

        // Using/Aliasing
        using General::TrimSigDigits;

        if (GetWaterCoilsInputFlag) {
            GetWaterCoilInput();
            GetWaterCoilsInputFlag = false;
        }

        if (CoilNum <= 0 || CoilNum > NumWaterCoils) {
            ShowSevereError("SetHeatingCoilData: called with heating coil Number out of range=" + TrimSigDigits(CoilNum) + " should be >0 and <" +
                            TrimSigDigits(NumWaterCoils));
            ErrorsFound = true;
            return;
        }

        if (present(DesiccantRegenerationCoil)) {
            WaterCoil(CoilNum).DesiccantRegenerationCoil = DesiccantRegenerationCoil;
        }

        if (present(DesiccantDehumIndex)) {
            WaterCoil(CoilNum).DesiccantDehumNum = DesiccantDehumIndex;
        }
    }
    */

    // used by SizeWaterCoil / heating coil
    /*
    void EstimateCoilInletWaterTemp(int const CoilNum,                // index to heating coil
                                    int const FanOpMode,              // fan operating mode
                                    Real64 const PartLoadRatio,       // part-load ratio of heating coil
                                    Real64 const UAMax,               // maximum UA-Value = design heating capacity
                                    Real64 &DesCoilInletWaterTempUsed // estimated coil design inlet water temperature
    )
    {
        // SUBROUTINE INFORMATION:

        // PURPOSE OF THIS SUBROUTINE:
        // returns estimated coil inlet water temperature given UA value for assumed
        // maximum effectiveness value for heating coil

        // METHODOLOGY EMPLOYED:
        // applies energy balance around the water coil and estimates coil water inlet temperature
        // assuming coil effectiveness of 0.8

        // REFERENCES:
        // na

        // Using/Aliasing
        using DataBranchAirLoopPlant::MassFlowTolerance;

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        static std::string const RoutineName("EstimateCoilInletWaterTemp");
        Real64 const EffectivnessMaxAssumed(0.80);

        // INTERFACE BLOCK SPECIFICATIONS
        // na

        // DERIVED TYPE DEFINITIONS
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        Real64 WaterMassFlowRate;
        Real64 AirMassFlow;
        Real64 TempAirIn;
        Real64 TempAirOut; // [C]
        Real64 Win;
        Real64 TempWaterIn;
        Real64 UA;
        Real64 CapacitanceAir;
        Real64 CapacitanceWater;
        Real64 CapacitanceMin;
        Real64 CapacitanceMax;
        Real64 NTU;
        Real64 ETA;
        Real64 A;
        Real64 CapRatio;
        Real64 E1;
        Real64 E2;
        Real64 Effec;
        Real64 Cp;

        UA = UAMax;
        DesCoilInletWaterTempUsed = DesCoilHWInletTempMin;
        TempAirIn = WaterCoil(CoilNum).InletAirTemp;
        Win = WaterCoil(CoilNum).InletAirHumRat;
        TempWaterIn = WaterCoil(CoilNum).InletWaterTemp;
        // adjust mass flow rates for cycling fan cycling coil operation
        if (FanOpMode == CycFanCycCoil) {
            if (PartLoadRatio > 0.0) {
                AirMassFlow = WaterCoil(CoilNum).InletAirMassFlowRate / PartLoadRatio;
                WaterMassFlowRate = min(WaterCoil(CoilNum).InletWaterMassFlowRate / PartLoadRatio, WaterCoil(CoilNum).MaxWaterMassFlowRate);
            } else {
                AirMassFlow = 0.0;
                WaterMassFlowRate = 0.0;
                return;
            }
        } else {
            AirMassFlow = WaterCoil(CoilNum).InletAirMassFlowRate;
            WaterMassFlowRate = WaterCoil(CoilNum).InletWaterMassFlowRate;
        }
        if (WaterMassFlowRate > MassFlowTolerance) { // if the coil is operating
            CapacitanceAir = PsyCpAirFnW(Win) * AirMassFlow;
            Cp = GetSpecificHeatGlycol(PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidName,
                                       TempWaterIn,
                                       PlantLoop(WaterCoil(CoilNum).WaterLoopNum).FluidIndex,
                                       RoutineName);
            CapacitanceWater = Cp * WaterMassFlowRate;
            CapacitanceMin = min(CapacitanceAir, CapacitanceWater);
            CapacitanceMax = max(CapacitanceAir, CapacitanceWater);
        } else {
            CapacitanceAir = 0.0;
            CapacitanceWater = 0.0;
            return;
        }
        // calculate DesCoilInletWaterTempUsed
        if (((CapacitanceAir > 0.0) && (CapacitanceWater > 0.0))) {

            if (UA <= 0.0) {
                ShowWarningError("UA is zero for COIL:Heating:Water " + WaterCoil(CoilNum).Name);
                return;
            }
            NTU = UA / CapacitanceMin;
            ETA = std::pow(NTU, 0.22);
            CapRatio = CapacitanceMin / CapacitanceMax;
            A = CapRatio * NTU / ETA;

            if (A > 20.0) {
                A = ETA * 1.0 / CapRatio;
            } else {
                E1 = std::exp(-A);
                A = ETA * (1.0 - E1) / CapRatio;
            }

            if (A > 20.0) {
                Effec = 1.0;
            } else {
                E2 = std::exp(-A);
                Effec = 1.0 - E2;
            }
            TempAirOut = TempAirIn + Effec * CapacitanceMin * (TempWaterIn - TempAirIn) / CapacitanceAir;
            // this formulation assumes coil effectiveness of 0.80 to increase the estimated coil water inlet temperatures
            DesCoilInletWaterTempUsed = CapacitanceAir * (TempAirOut - TempAirIn) / (CapacitanceMin * EffectivnessMaxAssumed) + TempAirIn;
            // water coil should not be sized at coil water inlet temperature lower than 46.0C (for convergence problem in Regulafalsi)
            DesCoilInletWaterTempUsed = max(DesCoilInletWaterTempUsed, DesCoilHWInletTempMin);
        }
    }

    */

    // End of Coil Utility subroutines
    // *****************************************************************************

} // namespace WaterCoils

} // namespace EnergyPlus
