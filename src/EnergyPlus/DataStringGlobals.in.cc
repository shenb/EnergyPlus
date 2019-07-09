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
#include <DataStringGlobals.hh>

namespace EnergyPlus {

namespace DataStringGlobals {

    // MODULE INFORMATION:
    //       AUTHOR         Linda K. Lawrie
    //       DATE WRITTEN   September 1997
    //       MODIFIED       na
    //       RE-ENGINEERED  na

    // PURPOSE OF THIS MODULE:
    // This data-only module is a repository for string variables used in parsing
    // "pieces" of EnergyPlus.

    // METHODOLOGY EMPLOYED:
    // na

    // REFERENCES:
    // na

    // OTHER NOTES:
    // na

    // USE STATEMENTS:
    // None!--This module is USEd by other modules; it should not USE anything.

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    // MODULE PARAMETER DEFINITIONS:
    thread_local std::string const UpperCase("ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝ");
    thread_local std::string const LowerCase("abcdefghijklmnopqrstuvwxyzàáâãäåæçèéêëìíîïðñòóôõöøùúûüý");
    thread_local std::string const AccentedUpperCase("ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝ");
    thread_local std::string const AccentedLowerCase("àáâãäåæçèéêëìíîïðñòóôõöøùúûüý");
    thread_local std::string const AllCase("àáâãäåæçèéêëìíîïðñòóôõöøùúûüýÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
#ifdef _WIN32
    thread_local std::string const NL("\r\n"); // Platform newline
#else
    thread_local std::string const NL("\n"); // Platform newline
#endif
#ifdef _WIN32
    thread_local char const pathChar('\\');
    thread_local char const altpathChar('/');
#elif __linux__
    thread_local char const pathChar('/');
    thread_local char const altpathChar('\\');
#elif __unix__
    thread_local char const pathChar('/');
    thread_local char const altpathChar('\\');
#elif __posix__
    thread_local char const pathChar('/');
    thread_local char const altpathChar('\\');
#elif __APPLE__
    thread_local char const pathChar('/');
    thread_local char const altpathChar('\\');
#else
#error "Invalid platform detection in DataStringGlobals."
#endif
    thread_local char const CharComma(',');     // comma
    thread_local char const CharSemicolon(';'); // semicolon
    thread_local char const CharTab('\t');      // tab
    thread_local char const CharSpace(' ');     // space

    // DERIVED TYPE DEFINITIONS
    // na

    // INTERFACE BLOCK SPECIFICATIONS
    // na

    // MODULE VARIABLE DECLARATIONS:
    thread_local std::string outputAuditFileName("eplusout.audit");
    thread_local std::string outputBndFileName("eplusout.bnd");
    thread_local std::string outputDxfFileName("eplusout.dxf");
    thread_local std::string outputEioFileName("eplusout.eio");
    thread_local std::string outputEndFileName("eplusout.end");
    thread_local std::string outputErrFileName("eplusout.err");
    thread_local std::string outputEsoFileName("eplusout.eso");
    thread_local std::string outputJsonFileName("eplusout.json");
    thread_local std::string outputTSHvacJsonFileName("eplusout_detailed_HVAC.json");
    thread_local std::string outputTSZoneJsonFileName("eplusout_detailed_zone.json");
    thread_local std::string outputTSJsonFileName("eplusout_timestep.json");
    thread_local std::string outputYRJsonFileName("eplusout_yearly.json");
    thread_local std::string outputMNJsonFileName("eplusout_monthly.json");
    thread_local std::string outputDYJsonFileName("eplusout_daily.json");
    thread_local std::string outputHRJsonFileName("eplusout_hourly.json");
    thread_local std::string outputSMJsonFileName("eplusout_runperiod.json");
    thread_local std::string outputCborFileName("eplusout.cbor");
    thread_local std::string outputTSHvacCborFileName("eplusout_detailed_HVAC.cbor");
    thread_local std::string outputTSZoneCborFileName("eplusout_detailed_zone.cbor");
    thread_local std::string outputTSCborFileName("eplusout_timestep.cbor");
    thread_local std::string outputYRCborFileName("eplusout_yearly.cbor");
    thread_local std::string outputMNCborFileName("eplusout_monthly.cbor");
    thread_local std::string outputDYCborFileName("eplusout_daily.cbor");
    thread_local std::string outputHRCborFileName("eplusout_hourly.cbor");
    thread_local std::string outputSMCborFileName("eplusout_runperiod.cbor");
    thread_local std::string outputMsgPackFileName("eplusout.msgpack");
    thread_local std::string outputTSHvacMsgPackFileName("eplusout_detailed_HVAC.msgpack");
    thread_local std::string outputTSZoneMsgPackFileName("eplusout_detailed_zone.msgpack");
    thread_local std::string outputTSMsgPackFileName("eplusout_timestep.msgpack");
    thread_local std::string outputYRMsgPackFileName("eplusout_yearly.msgpack");
    thread_local std::string outputMNMsgPackFileName("eplusout_monthly.msgpack");
    thread_local std::string outputDYMsgPackFileName("eplusout_daily.msgpack");
    thread_local std::string outputHRMsgPackFileName("eplusout_hourly.msgpack");
    thread_local std::string outputSMMsgPackFileName("eplusout_runperiod.msgpack");
    thread_local std::string outputMtdFileName("eplusout.mtd");
    thread_local std::string outputMddFileName("eplusout.mdd");
    thread_local std::string outputMtrFileName("eplusout.mtr");
    thread_local std::string outputRddFileName("eplusout.rdd");
    thread_local std::string outputShdFileName("eplusout.shd");
    thread_local std::string outputTblCsvFileName("eplustbl.csv");
    thread_local std::string outputTblHtmFileName("eplustbl.htm");
    thread_local std::string outputTblTabFileName("eplustbl.tab");
    thread_local std::string outputTblTxtFileName("eplustbl.txt");
    thread_local std::string outputTblXmlFileName("eplustbl.xml");
    thread_local std::string outputAdsFileName("eplusADS.out");
    thread_local std::string outputDfsFileName("eplusout.dfs");
    thread_local std::string outputGLHEFileName("eplusout.glhe");
    thread_local std::string outputDelightInFileName("eplusout.delightin");
    thread_local std::string outputDelightOutFileName("eplusout.delightout");
    thread_local std::string outputDelightEldmpFileName("eplusout.delighteldmp");
    thread_local std::string outputDelightDfdmpFileName("eplusout.delightdfdmp");
    thread_local std::string outputMapTabFileName("eplusmap.tab");
    thread_local std::string outputMapCsvFileName("eplusmap.csv");
    thread_local std::string outputMapTxtFileName("eplusmap.txt");
    thread_local std::string outputEddFileName("eplusout.edd");
    thread_local std::string outputIperrFileName("eplusout.iperr");
    thread_local std::string outputDbgFileName("eplusout.dbg");
    thread_local std::string outputSlnFileName("eplusout.sln");
    thread_local std::string outputSciFileName("eplusout.sci");
    thread_local std::string outputWrlFileName("eplusout.wrl");
    thread_local std::string outputZszCsvFileName("epluszsz.csv");
    thread_local std::string outputZszTabFileName("epluszsz.tab");
    thread_local std::string outputZszTxtFileName("epluszsz.txt");
    thread_local std::string outputSszCsvFileName("eplusssz.csv");
    thread_local std::string outputSszTabFileName("eplusssz.tab");
    thread_local std::string outputSszTxtFileName("eplusssz.txt");
    thread_local std::string outputScreenCsvFileName("eplusscreen.csv");
    thread_local std::string outputSqlFileName("eplusout.sql");
    thread_local std::string outputSqliteErrFileName("eplussqlite.err");
    thread_local std::string TarcogIterationsFileName("TarcogIterations.dbg");
    thread_local std::string outputCsvFileName("eplusout.csv");
    thread_local std::string outputMtrCsvFileName("eplusmtr.csv");
    thread_local std::string outputRvauditFileName("eplusout.rvaudit");
    thread_local std::string outputExtShdFracFileName("eplusshading.csv");

    thread_local std::string EnergyPlusIniFileName;
    thread_local std::string inStatFileName;
    thread_local std::string eplusADSFileName;
    thread_local std::string idfFileNameOnly;
    thread_local std::string idfDirPathName;
    thread_local std::string outDirPathName;
    thread_local std::string inputFileNameOnly;
    thread_local std::string inputDirPathName;
    thread_local std::string outputDirPathName;
    thread_local std::string exeDirectory;
    thread_local std::string inputFileName;
    thread_local std::string inputIddFileName;
    thread_local std::string inputEpJSONSchemaFileName;
    thread_local std::string inputWeatherFileName;
    thread_local std::string FullName;
    thread_local std::string weatherFileNameOnly;
    thread_local std::string ProgramPath;          // Path for Program from INI file
    thread_local std::string CurrentWorkingFolder; // Current working directory for run
    thread_local std::string CurrentDateTime;      // For printing current date and time at start of run
    thread_local std::string IDDVerString;         // Version information from the IDD (line 1)

    thread_local std::string
        VerString("EnergyPlus, Version ${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}.${CMAKE_VERSION_PATCH}-${CMAKE_VERSION_BUILD}"); // String that
                                                                                                                                      // represents
                                                                                                                                      // version
                                                                                                                                      // information
    thread_local std::string MatchVersion("${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}"); // String to be matched by Version object


    void clear_state()
    {
        EnergyPlusIniFileName.clear();
        inStatFileName.clear();
        eplusADSFileName.clear();
        idfFileNameOnly.clear();
        idfDirPathName.clear();
        outDirPathName.clear();
        inputFileNameOnly.clear();
        inputDirPathName.clear();
        outputDirPathName.clear();
        exeDirectory.clear();
        inputFileName.clear();
        inputIddFileName.clear();
        inputEpJSONSchemaFileName.clear();
        inputWeatherFileName.clear();
        FullName.clear();
        weatherFileNameOnly.clear();
        ProgramPath.clear();
        CurrentWorkingFolder.clear();
        CurrentDateTime.clear();
        IDDVerString.clear();
    }
} // namespace DataStringGlobals

} // namespace EnergyPlus
