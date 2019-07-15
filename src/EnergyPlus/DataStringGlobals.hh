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

#ifndef DataStringGlobals_hh_INCLUDED
#define DataStringGlobals_hh_INCLUDED

// C++ Headers
#include <string>

// EnergyPlus Headers
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace DataStringGlobals {

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    EP_GLOBAL extern std::string outputAuditFileName;
    EP_GLOBAL extern std::string outputBndFileName;
    EP_GLOBAL extern std::string outputDxfFileName;
    EP_GLOBAL extern std::string outputEioFileName;
    EP_GLOBAL extern std::string outputEndFileName;
    EP_GLOBAL extern std::string outputErrFileName;
    EP_GLOBAL extern std::string outputEsoFileName;

    EP_GLOBAL extern std::string outputJsonFileName;
    EP_GLOBAL extern std::string outputTSHvacJsonFileName;
    EP_GLOBAL extern std::string outputTSZoneJsonFileName;
    EP_GLOBAL extern std::string outputTSJsonFileName;
    EP_GLOBAL extern std::string outputYRJsonFileName;
    EP_GLOBAL extern std::string outputMNJsonFileName;
    EP_GLOBAL extern std::string outputDYJsonFileName;
    EP_GLOBAL extern std::string outputHRJsonFileName;
    EP_GLOBAL extern std::string outputSMJsonFileName;
    EP_GLOBAL extern std::string outputCborFileName;
    EP_GLOBAL extern std::string outputTSHvacCborFileName;
    EP_GLOBAL extern std::string outputTSZoneCborFileName;
    EP_GLOBAL extern std::string outputTSCborFileName;
    EP_GLOBAL extern std::string outputYRCborFileName;
    EP_GLOBAL extern std::string outputMNCborFileName;
    EP_GLOBAL extern std::string outputDYCborFileName;
    EP_GLOBAL extern std::string outputHRCborFileName;
    EP_GLOBAL extern std::string outputSMCborFileName;
    EP_GLOBAL extern std::string outputMsgPackFileName;
    EP_GLOBAL extern std::string outputTSHvacMsgPackFileName;
    EP_GLOBAL extern std::string outputTSZoneMsgPackFileName;
    EP_GLOBAL extern std::string outputTSMsgPackFileName;
    EP_GLOBAL extern std::string outputYRMsgPackFileName;
    EP_GLOBAL extern std::string outputMNMsgPackFileName;
    EP_GLOBAL extern std::string outputDYMsgPackFileName;
    EP_GLOBAL extern std::string outputHRMsgPackFileName;
    EP_GLOBAL extern std::string outputSMMsgPackFileName;

    EP_GLOBAL extern std::string outputMtdFileName;
    EP_GLOBAL extern std::string outputMddFileName;
    EP_GLOBAL extern std::string outputMtrFileName;
    EP_GLOBAL extern std::string outputRddFileName;
    EP_GLOBAL extern std::string outputShdFileName;
    EP_GLOBAL extern std::string outputTblCsvFileName;
    EP_GLOBAL extern std::string outputTblHtmFileName;
    EP_GLOBAL extern std::string outputTblTabFileName;
    EP_GLOBAL extern std::string outputTblTxtFileName;
    EP_GLOBAL extern std::string outputTblXmlFileName;
    EP_GLOBAL extern std::string inputFileName;
    EP_GLOBAL extern std::string inputIddFileName;
    EP_GLOBAL extern std::string inputEpJSONSchemaFileName;
    EP_GLOBAL extern std::string inputEpJSONSchemaFileName;
    EP_GLOBAL extern std::string inputWeatherFileName;
    EP_GLOBAL extern std::string outputAdsFileName;
    EP_GLOBAL extern std::string outputDfsFileName;
    EP_GLOBAL extern std::string outputGLHEFileName;
    EP_GLOBAL extern std::string outputDelightInFileName;
    EP_GLOBAL extern std::string outputDelightOutFileName;
    EP_GLOBAL extern std::string outputDelightEldmpFileName;
    EP_GLOBAL extern std::string outputDelightDfdmpFileName;
    EP_GLOBAL extern std::string outputMapTabFileName;
    EP_GLOBAL extern std::string outputMapCsvFileName;
    EP_GLOBAL extern std::string outputMapTxtFileName;
    EP_GLOBAL extern std::string outputEddFileName;
    EP_GLOBAL extern std::string outputIperrFileName;
    EP_GLOBAL extern std::string outputDbgFileName;
    EP_GLOBAL extern std::string outputSlnFileName;
    EP_GLOBAL extern std::string outputSciFileName;
    EP_GLOBAL extern std::string outputWrlFileName;
    EP_GLOBAL extern std::string outputZszCsvFileName;
    EP_GLOBAL extern std::string outputZszTabFileName;
    EP_GLOBAL extern std::string outputZszTxtFileName;
    EP_GLOBAL extern std::string outputSszCsvFileName;
    EP_GLOBAL extern std::string outputSszTabFileName;
    EP_GLOBAL extern std::string outputSszTxtFileName;
    EP_GLOBAL extern std::string outputScreenCsvFileName;
    EP_GLOBAL extern std::string outputSqlFileName;
    EP_GLOBAL extern std::string outputSqliteErrFileName;
    EP_GLOBAL extern std::string EnergyPlusIniFileName;
    EP_GLOBAL extern std::string inStatFileName;
    EP_GLOBAL extern std::string TarcogIterationsFileName;
    EP_GLOBAL extern std::string eplusADSFileName;
    EP_GLOBAL extern std::string outputCsvFileName;
    EP_GLOBAL extern std::string outputMtrCsvFileName;
    EP_GLOBAL extern std::string outputRvauditFileName;
    EP_GLOBAL extern std::string outputExtShdFracFileName;

    EP_GLOBAL extern std::string weatherFileNameOnly;
    EP_GLOBAL extern std::string idfDirPathName;
    EP_GLOBAL extern std::string outDirPathName;
    EP_GLOBAL extern std::string idfFileNameOnly;
    EP_GLOBAL extern std::string inputDirPathName;
    EP_GLOBAL extern std::string outputDirPathName;
    EP_GLOBAL extern std::string inputFileNameOnly;
    EP_GLOBAL extern std::string exeDirectory;

    // MODULE PARAMETER DEFINITIONS:
    EP_GLOBAL extern std::string const UpperCase;
    EP_GLOBAL extern std::string const LowerCase;
    EP_GLOBAL extern std::string const AccentedUpperCase;
    EP_GLOBAL extern std::string const AccentedLowerCase;
    EP_GLOBAL extern std::string const AllCase;
    EP_GLOBAL extern std::string const NL; // Platform newline
    EP_GLOBAL extern char const pathChar;
    EP_GLOBAL extern char const altpathChar;
    EP_GLOBAL extern char const CharComma;     // comma
    EP_GLOBAL extern char const CharSemicolon; // semicolon
    EP_GLOBAL extern char const CharTab;       // tab
    EP_GLOBAL extern char const CharSpace;     // space

    // DERIVED TYPE DEFINITIONS
    // na

    // INTERFACE BLOCK SPECIFICATIONS
    // na

    // MODULE VARIABLE DECLARATIONS:
    EP_GLOBAL extern std::string ProgramPath;          // Path for Program from INI file
    EP_GLOBAL extern std::string CurrentWorkingFolder; // Current working directory for run
    EP_GLOBAL extern std::string FullName;             // Full name of file to open, including path
    EP_GLOBAL extern std::string IDDVerString;         // Version information from the IDD (line 1)
    EP_GLOBAL extern std::string VerString;            // String that represents version information
    EP_GLOBAL extern std::string MatchVersion;         // String to be matched by Version object
    EP_GLOBAL extern std::string CurrentDateTime;      // For printing current date and time at start of run

    // Functions
    void clear_state();

} // namespace DataStringGlobals

} // namespace EnergyPlus

#endif
