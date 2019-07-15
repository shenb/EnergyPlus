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

// ObjexxFCL Headers
#include <ObjexxFCL/string.functions.hh>

// EnergyPlus Headers
#include <DataPrecisionGlobals.hh>
#include <DataRuntimeLanguage.hh>
#include <UtilityRoutines.hh>

namespace EnergyPlus {

// Data only module for EMS runtime language

namespace DataRuntimeLanguage {

    // MODULE INFORMATION:
    //       AUTHOR         Peter Graham Ellis
    //       DATE WRITTEN   June 2006
    //       MODIFIED       Brent Griffith, May 2009
    //       RE-ENGINEERED  na

    // PURPOSE OF THIS MODULE:

    // METHODOLOGY EMPLOYED: na

    // Using/Aliasing
    using namespace DataPrecisionGlobals;

    // Data
    // module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    // MODULE PARAMETER DEFINITIONS:
    EP_GLOBAL int const ValueNull(0);       // Erl entity type, "Null" value
    EP_GLOBAL int const ValueNumber(1);     // Erl entity type,  hard numeric value
    EP_GLOBAL int const ValueString(2);     // Erl entity type,  character data
    EP_GLOBAL int const ValueArray(3);      // Erl entity type,  not used yet, for future array type
    EP_GLOBAL int const ValueVariable(4);   // Erl entity type,  Erl variable
    EP_GLOBAL int const ValueExpression(5); // Erl entity type,  Erl expression
    EP_GLOBAL int const ValueTrend(6);      // Erl entity type,  Erl trend variable
    EP_GLOBAL int const ValueError(7);      // Erl entity type, processing of an expression failed, returned error

    EP_GLOBAL int const PntrReal(301);    // data type for overloaded pointer management, double real
    EP_GLOBAL int const PntrInteger(302); // data type for overloaded pointer management, integer
    EP_GLOBAL int const PntrLogical(303); // data type for overloaded pointer management, logical

    EP_GLOBAL int const MaxWhileLoopIterations(1000000); // protect from infinite loop in WHILE loops

    // Parameters for identifying operator types in Erl
    // The number of these parameters indicates the order of precedence
    EP_GLOBAL int const OperatorLiteral(1);         // Just stores a literal value
    EP_GLOBAL int const OperatorNegative(2);        // -  (unary) No LHS?
    EP_GLOBAL int const OperatorDivide(3);          // /
    EP_GLOBAL int const OperatorMultiply(4);        // *
    EP_GLOBAL int const OperatorSubtract(5);        // -  (binary)
    EP_GLOBAL int const OperatorAdd(6);             // +  (binary)
    EP_GLOBAL int const OperatorEqual(7);           // ==
    EP_GLOBAL int const OperatorNotEqual(8);        // <>
    EP_GLOBAL int const OperatorLessOrEqual(9);     // <=
    EP_GLOBAL int const OperatorGreaterOrEqual(10); // >=
    EP_GLOBAL int const OperatorLessThan(11);       // <
    EP_GLOBAL int const OperatorGreaterThan(12);    // >
    EP_GLOBAL int const OperatorRaiseToPower(13);   // ^
    EP_GLOBAL int const OperatorLogicalAND(14);     // &&
    EP_GLOBAL int const OperatiorLogicalOR(15);     // ||
    // note there is an important check "> 15" to distinguish operators from functions
    //  so becareful if renumber these parameters.  Binary operator additions should get inserted here rather than appended

    // parameters for built-in Erl functions, these are processed like operators and numbering
    // must be sequential with the operators.
    // math functions
    EP_GLOBAL int const FuncRound(16);    // accessor for Fortran's DNINT()
    EP_GLOBAL int const FuncMod(17);      // accessor for Fortran's MOD()
    EP_GLOBAL int const FuncSin(18);      // accessor for Fortran's SIN()
    EP_GLOBAL int const FuncCos(19);      // accessor for Fortran's COS()
    EP_GLOBAL int const FuncArcSin(20);   // accessor for Fortran's ASIN()
    EP_GLOBAL int const FuncArcCos(21);   // accessor for Fortran's ACOS()
    EP_GLOBAL int const FuncDegToRad(22); // Multiplies degrees by DegToRad
    EP_GLOBAL int const FuncRadToDeg(23); // Divides radians by DegToRad
    EP_GLOBAL int const FuncExp(24);      // accessor for Fortran's EXP()
    EP_GLOBAL int const FuncLn(25);       // accessor for Fortran's LOG()
    EP_GLOBAL int const FuncMax(26);      // accessor for Fortran's MAX()
    EP_GLOBAL int const FuncMin(27);      // accessor for Fortran's MIN()
    EP_GLOBAL int const FuncABS(28);      // accessor for Fortran's ABS()
    EP_GLOBAL int const FuncRandU(29);    // accessor for Fortran's Random_Number() intrinsic, uniform distribution
    EP_GLOBAL int const FuncRandG(30);    // accessor for Gaussian/normal distribution random number
    EP_GLOBAL int const FuncRandSeed(31); // accessor for Fortran's Random_Seed() intrinsic

    // begin psychrometric routines
    EP_GLOBAL int const FuncRhoAirFnPbTdbW(32);    // accessor for E+ psych routine
    EP_GLOBAL int const FuncCpAirFnWTdb(33);       // accessor for E+ psych routine
    EP_GLOBAL int const FuncHfgAirFnWTdb(34);      // accessor for E+ psych routine
    EP_GLOBAL int const FuncHgAirFnWTdb(35);       // accessor for E+ psych routine
    EP_GLOBAL int const FuncTdpFnTdbTwbPb(36);     // accessor for E+ psych routine
    EP_GLOBAL int const FuncTdpFnWPb(37);          // accessor for E+ psych routine
    EP_GLOBAL int const FuncHFnTdbW(38);           // accessor for E+ psych routine
    EP_GLOBAL int const FuncHFnTdbRhPb(39);        // accessor for E+ psych routine
    EP_GLOBAL int const FuncTdbFnHW(40);           // accessor for E+ psych routine
    EP_GLOBAL int const FuncRhovFnTdbRh(41);       // accessor for E+ psych routine
    EP_GLOBAL int const FuncRhovFnTdbRhLBnd0C(42); // accessor for E+ psych routine
    EP_GLOBAL int const FuncRhovFnTdbWPb(43);      // accessor for E+ psych routine
    EP_GLOBAL int const FuncRhFnTdbRhov(44);       // accessor for E+ psych routine
    EP_GLOBAL int const FuncRhFnTdbRhovLBnd0C(45); // accessor for E+ psych routine
    EP_GLOBAL int const FuncRhFnTdbWPb(46);        // accessor for E+ psych routine
    EP_GLOBAL int const FuncTwbFnTdbWPb(47);       // accessor for E+ psych routine
    EP_GLOBAL int const FuncVFnTdbWPb(48);         // accessor for E+ psych routine
    EP_GLOBAL int const FuncWFnTdpPb(49);          // accessor for E+ psych routine
    EP_GLOBAL int const FuncWFnTdbH(50);           // accessor for E+ psych routine
    EP_GLOBAL int const FuncWFnTdbTwbPb(51);       // accessor for E+ psych routine
    EP_GLOBAL int const FuncWFnTdbRhPb(52);        // accessor for E+ psych routine
    EP_GLOBAL int const FuncPsatFnTemp(53);        // accessor for E+ psych routine
    EP_GLOBAL int const FuncTsatFnHPb(54);         // accessor for E+ psych routine
    EP_GLOBAL int const FuncTsatFnPb(55);          // not public in PsychRoutines.cc so not really available in EMS.
    EP_GLOBAL int const FuncCpCW(56);              // accessor for E+ psych routine
    EP_GLOBAL int const FuncCpHW(57);              // accessor for E+ psych routine
    EP_GLOBAL int const FuncRhoH2O(58);            // accessor for E+ psych routine

    // Simulation Management Functions
    EP_GLOBAL int const FuncFatalHaltEp(59);  // accessor for E+ error management, "Fatal" level
    EP_GLOBAL int const FuncSevereWarnEp(60); // accessor for E+ error management, "Severe" level
    EP_GLOBAL int const FuncWarnEp(61);       // accessor for E+ error management, "Warning" level

    // Trend variable handling Functions
    EP_GLOBAL int const FuncTrendValue(62);     // accessor for Erl Trend variables, instance value
    EP_GLOBAL int const FuncTrendAverage(63);   // accessor for Erl Trend variables, average value
    EP_GLOBAL int const FuncTrendMax(64);       // accessor for Erl Trend variables, max value
    EP_GLOBAL int const FuncTrendMin(65);       // accessor for Erl Trend variables, min value
    EP_GLOBAL int const FuncTrendDirection(66); // accessor for Erl Trend variables, slope value
    EP_GLOBAL int const FuncTrendSum(67);       // accessor for Erl Trend variables, sum value

    // Curve and Table access function
    EP_GLOBAL int const FuncCurveValue(68);

    EP_GLOBAL int const NumPossibleOperators(68); // total number of operators and built-in functions

    // DERIVED TYPE DEFINITIONS:

    // MODULE VARIABLE TYPE DECLARATIONS:

    // INTERFACE BLOCK SPECIFICATIONS: na

    // MODULE VARIABLE DECLARATIONS:
    EP_GLOBAL Array1D_int EMSProgram;

    EP_GLOBAL int NumProgramCallManagers(0);      // count of Erl program managers with calling points
    EP_GLOBAL int NumSensors(0);                  // count of EMS sensors used in model (data from output variables)
    EP_GLOBAL int numActuatorsUsed(0);            // count of EMS actuators used in model
    EP_GLOBAL int numEMSActuatorsAvailable(0);    // count of EMS actuators available for use in such a model
    EP_GLOBAL int maxEMSActuatorsAvailable(0);    // count of EMS current maximum actuators available for use in such a model
    EP_GLOBAL int NumInternalVariablesUsed(0);    // count of EMS internal variables used in model
    EP_GLOBAL int numEMSInternalVarsAvailable(0); // count of EMS internal variables available for use in such a model
    EP_GLOBAL int maxEMSInternalVarsAvailable(0); // count of EMS current maximum internal variables available for use in such a model
    EP_GLOBAL int varsAvailableAllocInc(1000);    // allocation increment for variable arrays

    EP_GLOBAL int NumErlPrograms(0);               // count of Erl programs in model
    EP_GLOBAL int NumErlSubroutines(0);            // count of Erl subroutines in model
    EP_GLOBAL int NumUserGlobalVariables(0);       // count of global EMS variables defined by user
    EP_GLOBAL int NumErlVariables(0);              // count of Erl variables
    EP_GLOBAL int NumErlStacks(0);                 // count of Erl program stacks in model. sum of programs and subroutines
    EP_GLOBAL int NumExpressions(0);               // count of Erl expressions
    EP_GLOBAL int NumEMSOutputVariables(0);        // count of EMS output variables, custom output variables from Erl
    EP_GLOBAL int NumEMSMeteredOutputVariables(0); // count of EMS metered output variables, custom meters from Erl
    EP_GLOBAL int NumErlTrendVariables(0);         // count of EMS trend variables in model
    EP_GLOBAL int NumEMSCurveIndices(0);           // count of EMS curve index variables in model
    EP_GLOBAL int NumEMSConstructionIndices(0);    // count of EMS construction index variables in model

    //######################################################################################################################################
    // code for ExternalInterface
    EP_GLOBAL int NumExternalInterfaceGlobalVariables(0);                           // count of ExternalInterface runtime variable
    EP_GLOBAL int NumExternalInterfaceFunctionalMockupUnitImportGlobalVariables(0); // count of ExternalInterface runtime variable for FMUImport
    // will be updated with values from ExternalInterface
    EP_GLOBAL int NumExternalInterfaceFunctionalMockupUnitExportGlobalVariables(0); // count of ExternalInterface runtime variable for FMUExport
    // will be updated with values from ExternalInterface
    EP_GLOBAL int NumExternalInterfaceActuatorsUsed(0);                           // count of ExternalInterface Actuators
    EP_GLOBAL int NumExternalInterfaceFunctionalMockupUnitImportActuatorsUsed(0); // count of ExternalInterface Actuators for FMUImport
    EP_GLOBAL int NumExternalInterfaceFunctionalMockupUnitExportActuatorsUsed(0); // count of ExternalInterface Actuators for FMUExport

    //######################################################################################################################################

    EP_GLOBAL int OutputEMSFileUnitNum(0);             // file lun handle for open EMS output file
    EP_GLOBAL bool OutputEDDFile(false);               // set to true if user requests EDD output file be written
    EP_GLOBAL bool OutputFullEMSTrace(false);          // how much to write out to trace, if true do verbose for each line
    EP_GLOBAL bool OutputEMSErrors(false);             // how much to write out to trace, if true include Erl error messages
    EP_GLOBAL bool OutputEMSActuatorAvailFull(false);  // how much to write out to EDD file, if true dump full combinatorial actuator list
    EP_GLOBAL bool OutputEMSActuatorAvailSmall(false); // how much to write out to EDD file, if true dump actuator list without key names
    EP_GLOBAL bool OutputEMSInternalVarsFull(false);   // how much to write out to EDD file, if true dump full combinatorial internal list
    EP_GLOBAL bool OutputEMSInternalVarsSmall(false);  // how much to write out to EDD file, if true dump internal list without key names

    EP_GLOBAL Array2D_bool EMSConstructActuatorChecked;
    EP_GLOBAL Array2D_bool EMSConstructActuatorIsOkay;

    // Object Data
    EP_GLOBAL Array1D<ErlVariableType> ErlVariable;                        // holds Erl variables in a structure array
    EP_GLOBAL Array1D<ErlStackType> ErlStack;                              // holds Erl programs in separate "stacks"
    EP_GLOBAL Array1D<ErlExpressionType> ErlExpression;                    // holds Erl expressions in structure array
    EP_GLOBAL Array1D<OperatorType> PossibleOperators;                     // hard library of available operators and functions
    EP_GLOBAL Array1D<TrendVariableType> TrendVariable;                    // holds Erl trend varialbes in a structure array
    EP_GLOBAL Array1D<OutputVarSensorType> Sensor;                         // EMS:SENSOR objects used (from output variables)
    EP_GLOBAL Array1D<EMSActuatorAvailableType> EMSActuatorAvailable;      // actuators that could be used
    EP_GLOBAL Array1D<ActuatorUsedType> EMSActuatorUsed;                   // actuators that are used
    EP_GLOBAL Array1D<InternalVarsAvailableType> EMSInternalVarsAvailable; // internal data that could be used
    EP_GLOBAL Array1D<InternalVarsUsedType> EMSInternalVarsUsed;           // internal data that are used
    EP_GLOBAL Array1D<EMSProgramCallManagementType> EMSProgramCallManager; // program calling managers
    EP_GLOBAL ErlValueType Null(0, 0.0, "", 0, 0, false, 0, "", true);     // special "null" Erl variable value instance
    EP_GLOBAL ErlValueType False(0, 0.0, "", 0, 0, false, 0, "", true);    // special "false" Erl variable value instance
    EP_GLOBAL ErlValueType True(0, 0.0, "", 0, 0, false, 0, "", true);     // special "True" Erl variable value instance, gets reset

    // EMS Actuator fast duplicate check lookup support
    EP_GLOBAL std::unordered_set<std::tuple<std::string, std::string, std::string>, EMSActuatorKey_hash> EMSActuator_lookup; // Fast duplicate lookup structure

    // Functions
    void clear_state()
    {
        EMSProgram.deallocate();
        NumProgramCallManagers = 0;
        NumSensors = 0;
        numActuatorsUsed = 0;
        numEMSActuatorsAvailable = 0;
        maxEMSActuatorsAvailable = 0;
        NumInternalVariablesUsed = 0;
        numEMSInternalVarsAvailable = 0;
        maxEMSInternalVarsAvailable = 0;
        varsAvailableAllocInc = 1000;
        NumErlPrograms = 0;
        NumErlSubroutines = 0;
        NumUserGlobalVariables = 0;
        NumErlVariables = 0;
        NumErlStacks = 0;
        NumExpressions = 0;
        NumEMSOutputVariables = 0;
        NumEMSMeteredOutputVariables = 0;
        NumErlTrendVariables = 0;
        NumEMSCurveIndices = 0;
        NumEMSConstructionIndices = 0;
        NumExternalInterfaceGlobalVariables = 0;
        NumExternalInterfaceFunctionalMockupUnitImportGlobalVariables = 0;
        NumExternalInterfaceFunctionalMockupUnitExportGlobalVariables = 0;
        NumExternalInterfaceActuatorsUsed = 0;
        NumExternalInterfaceFunctionalMockupUnitImportActuatorsUsed = 0;
        NumExternalInterfaceFunctionalMockupUnitExportActuatorsUsed = 0;
        OutputEMSFileUnitNum = 0;
        OutputEDDFile = false;
        OutputFullEMSTrace = false;
        OutputEMSErrors = false;
        OutputEMSActuatorAvailFull = false;
        OutputEMSActuatorAvailSmall = false;
        OutputEMSInternalVarsFull = false;
        OutputEMSInternalVarsSmall = false;
        EMSConstructActuatorChecked.deallocate();
        EMSConstructActuatorIsOkay.deallocate();
        ErlVariable.deallocate();              // holds Erl variables in a structure array
        ErlStack.deallocate();                 // holds Erl programs in separate "stacks"
        ErlExpression.deallocate();            // holds Erl expressions in structure array
        PossibleOperators.deallocate();        // hard library of available operators and functions
        TrendVariable.deallocate();            // holds Erl trend varialbes in a structure array
        Sensor.deallocate();                   // EMS:SENSOR objects used (from output variables)
        EMSActuatorAvailable.deallocate();     // actuators that could be used
        EMSActuatorUsed.deallocate();          // actuators that are used
        EMSInternalVarsAvailable.deallocate(); // internal data that could be used
        EMSInternalVarsUsed.deallocate();      // internal data that are used
        EMSProgramCallManager.deallocate();    // program calling managers
        EMSActuator_lookup.clear();            // Fast duplicate lookup structure
    }

    void ValidateEMSVariableName(std::string const &cModuleObject, // the current object name
                                 std::string const &cFieldValue,   // the field value
                                 std::string const &cFieldName,    // the current field name
                                 bool &errFlag,                    // true if errors found in this routine, false otherwise.
                                 bool &ErrorsFound                 // true if errors found in this routine, untouched otherwise.
    )
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Linda Lawrie
        //       DATE WRITTEN   May 2012
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // Consolidate error checking on EMS variable names.

        // METHODOLOGY EMPLOYED:
        // na

        // REFERENCES:
        // na

        // Using/Aliasing

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        EP_GLOBAL static std::string const InvalidStartCharacters("0123456789");

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:

        errFlag = false;
        if (has(cFieldValue, ' ')) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used as EMS variables cannot contain spaces");
            errFlag = true;
            ErrorsFound = true;
        }
        if (has(cFieldValue, '-')) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used as EMS variables cannot contain \"-\" characters.");
            errFlag = true;
            ErrorsFound = true;
        }
        if (has(cFieldValue, '+')) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used as EMS variables cannot contain \"+\" characters.");
            errFlag = true;
            ErrorsFound = true;
        }
        if (has(cFieldValue, '.')) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used as EMS variables cannot contain \".\" characters.");
            errFlag = true;
            ErrorsFound = true;
        }
        if ((cFieldValue.length() > 0) && (has_any_of(cFieldValue[0], InvalidStartCharacters))) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used as EMS variables cannot start with numeric characters.");
            errFlag = true;
            ErrorsFound = true;
        }
    }

    void ValidateEMSProgramName(std::string const &cModuleObject, // the current object name
                                std::string const &cFieldValue,   // the field value
                                std::string const &cFieldName,    // the current field name
                                std::string const &cSubType,      // sub type = Program or Subroutine
                                bool &errFlag,                    // true if errors found in this routine, false otherwise.
                                bool &ErrorsFound                 // true if errors found in this routine, untouched otherwise.
    )
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Linda Lawrie
        //       DATE WRITTEN   May 2012
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // Consolidate error checking on EMS variable names.

        // METHODOLOGY EMPLOYED:
        // na

        // REFERENCES:
        // na

        // Using/Aliasing

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        EP_GLOBAL static std::string const InvalidStartCharacters("0123456789");

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        // INTEGER :: pos

        errFlag = false;
        if (has(cFieldValue, ' ')) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used for EMS " + cSubType + " cannot contain spaces");
            errFlag = true;
            ErrorsFound = true;
        }
        if (has(cFieldValue, '-')) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used for EMS " + cSubType + " cannot contain \"-\" characters.");
            errFlag = true;
            ErrorsFound = true;
        }
        if (has(cFieldValue, '+')) {
            ShowSevereError(cModuleObject + "=\"" + cFieldValue + "\", Invalid variable name entered.");
            ShowContinueError("..." + cFieldName + "; Names used for EMS " + cSubType + " cannot contain \"+\" characters.");
            errFlag = true;
            ErrorsFound = true;
        }
        //  pos=SCAN(cFieldValue(1:1),InvalidStartCharacters)
        //  IF (pos > 0) THEN
        //    CALL ShowSevereError(TRIM(cModuleObject)//'="'//TRIM(cFieldValue)//'", Invalid variable name entered.')
        //    CALL ShowContinueError('...'//TRIM(cFieldName)//'; Names used as EMS variables cannot start with numeric characters.')
        //    errFlag=.TRUE.
        //    ErrorsFound = .TRUE.
        //  ENDIF
    }

} // namespace DataRuntimeLanguage

} // namespace EnergyPlus
