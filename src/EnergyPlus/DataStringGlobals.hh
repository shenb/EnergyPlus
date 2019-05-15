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

    thread_local extern std::string outputAuditFileName;
    thread_local extern std::string outputBndFileName;
    thread_local extern std::string outputDxfFileName;
    thread_local extern std::string outputEioFileName;
    thread_local extern std::string outputEndFileName;
    thread_local extern std::string outputErrFileName;
    thread_local extern std::string outputEsoFileName;
    thread_local extern std::string outputMtdFileName;
    thread_local extern std::string outputMddFileName;
    thread_local extern std::string outputMtrFileName;
    thread_local extern std::string outputRddFileName;
    thread_local extern std::string outputShdFileName;
    thread_local extern std::string outputTblCsvFileName;
    thread_local extern std::string outputTblHtmFileName;
    thread_local extern std::string outputTblTabFileName;
    thread_local extern std::string outputTblTxtFileName;
    thread_local extern std::string outputTblXmlFileName;
    thread_local extern std::string inputFileName;
    thread_local extern std::string inputIddFileName;
    thread_local extern std::string inputEpJSONSchemaFileName;
    thread_local extern std::string inputEpJSONSchemaFileName;
    thread_local extern std::string inputWeatherFileName;
    thread_local extern std::string outputAdsFileName;
    thread_local extern std::string outputDfsFileName;
    thread_local extern std::string outputGLHEFileName;
    thread_local extern std::string outputDelightInFileName;
    thread_local extern std::string outputDelightOutFileName;
    thread_local extern std::string outputDelightEldmpFileName;
    thread_local extern std::string outputDelightDfdmpFileName;
    thread_local extern std::string outputMapTabFileName;
    thread_local extern std::string outputMapCsvFileName;
    thread_local extern std::string outputMapTxtFileName;
    thread_local extern std::string outputEddFileName;
    thread_local extern std::string outputIperrFileName;
    thread_local extern std::string outputDbgFileName;
    thread_local extern std::string outputSlnFileName;
    thread_local extern std::string outputSciFileName;
    thread_local extern std::string outputWrlFileName;
    thread_local extern std::string outputZszCsvFileName;
    thread_local extern std::string outputZszTabFileName;
    thread_local extern std::string outputZszTxtFileName;
    thread_local extern std::string outputSszCsvFileName;
    thread_local extern std::string outputSszTabFileName;
    thread_local extern std::string outputSszTxtFileName;
    thread_local extern std::string outputScreenCsvFileName;
    thread_local extern std::string outputSqlFileName;
    thread_local extern std::string outputSqliteErrFileName;
    thread_local extern std::string EnergyPlusIniFileName;
    thread_local extern std::string inStatFileName;
    thread_local extern std::string TarcogIterationsFileName;
    thread_local extern std::string eplusADSFileName;
    thread_local extern std::string outputCsvFileName;
    thread_local extern std::string outputMtrCsvFileName;
    thread_local extern std::string outputRvauditFileName;
    thread_local extern std::string outputExtShdFracFileName;

    thread_local extern std::string weatherFileNameOnly;
    thread_local extern std::string idfDirPathName;
    thread_local extern std::string outDirPathName;
    thread_local extern std::string idfFileNameOnly;
    thread_local extern std::string inputDirPathName;
    thread_local extern std::string outputDirPathName;
    thread_local extern std::string inputFileNameOnly;
    thread_local extern std::string exeDirectory;

    // MODULE PARAMETER DEFINITIONS:
    extern std::string const UpperCase;
    extern std::string const LowerCase;
    extern std::string const AccentedUpperCase;
    extern std::string const AccentedLowerCase;
    extern std::string const AllCase;
    extern std::string const NL; // Platform newline
    extern char const pathChar;
    extern char const altpathChar;
    extern char const CharComma;     // comma
    extern char const CharSemicolon; // semicolon
    extern char const CharTab;       // tab
    extern char const CharSpace;     // space

    // DERIVED TYPE DEFINITIONS
    // na

    // INTERFACE BLOCK SPECIFICATIONS
    // na

    // MODULE VARIABLE DECLARATIONS:
    thread_local extern std::string ProgramPath;          // Path for Program from INI file
    thread_local extern std::string CurrentWorkingFolder; // Current working directory for run
    thread_local extern std::string FullName;             // Full name of file to open, including path
    thread_local extern std::string IDDVerString;         // Version information from the IDD (line 1)
    thread_local extern std::string VerString;            // String that represents version information
    thread_local extern std::string MatchVersion;         // String to be matched by Version object
    thread_local extern std::string CurrentDateTime;      // For printing current date and time at start of run

} // namespace DataStringGlobals

} // namespace EnergyPlus

#endif
