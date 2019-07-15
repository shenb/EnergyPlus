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
    EP_GLOBAL std::string const UpperCase("ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝ");
    EP_GLOBAL std::string const LowerCase("abcdefghijklmnopqrstuvwxyzàáâãäåæçèéêëìíîïðñòóôõöøùúûüý");
    EP_GLOBAL std::string const AccentedUpperCase("ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝ");
    EP_GLOBAL std::string const AccentedLowerCase("àáâãäåæçèéêëìíîïðñòóôõöøùúûüý");
    EP_GLOBAL std::string const AllCase("àáâãäåæçèéêëìíîïðñòóôõöøùúûüýÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
#ifdef _WIN32
    EP_GLOBAL std::string const NL("\r\n"); // Platform newline
#else
    EP_GLOBAL std::string const NL("\n"); // Platform newline
#endif
#ifdef _WIN32
    EP_GLOBAL char const pathChar('\\');
    EP_GLOBAL char const altpathChar('/');
#elif __linux__
    EP_GLOBAL char const pathChar('/');
    EP_GLOBAL char const altpathChar('\\');
#elif __unix__
    EP_GLOBAL char const pathChar('/');
    EP_GLOBAL char const altpathChar('\\');
#elif __posix__
    EP_GLOBAL char const pathChar('/');
    EP_GLOBAL char const altpathChar('\\');
#elif __APPLE__
    EP_GLOBAL char const pathChar('/');
    EP_GLOBAL char const altpathChar('\\');
#else
#error "Invalid platform detection in DataStringGlobals."
#endif
    EP_GLOBAL char const CharComma(',');     // comma
    EP_GLOBAL char const CharSemicolon(';'); // semicolon
    EP_GLOBAL char const CharTab('\t');      // tab
    EP_GLOBAL char const CharSpace(' ');     // space

    // DERIVED TYPE DEFINITIONS
    // na

    // INTERFACE BLOCK SPECIFICATIONS
    // na

    // MODULE VARIABLE DECLARATIONS:
    EP_GLOBAL std::string outputAuditFileName("eplusout.audit");
    EP_GLOBAL std::string outputBndFileName("eplusout.bnd");
    EP_GLOBAL std::string outputDxfFileName("eplusout.dxf");
    EP_GLOBAL std::string outputEioFileName("eplusout.eio");
    EP_GLOBAL std::string outputEndFileName("eplusout.end");
    EP_GLOBAL std::string outputErrFileName("eplusout.err");
    EP_GLOBAL std::string outputEsoFileName("eplusout.eso");
    EP_GLOBAL std::string outputJsonFileName("eplusout.json");
    EP_GLOBAL std::string outputTSHvacJsonFileName("eplusout_detailed_HVAC.json");
    EP_GLOBAL std::string outputTSZoneJsonFileName("eplusout_detailed_zone.json");
    EP_GLOBAL std::string outputTSJsonFileName("eplusout_timestep.json");
    EP_GLOBAL std::string outputYRJsonFileName("eplusout_yearly.json");
    EP_GLOBAL std::string outputMNJsonFileName("eplusout_monthly.json");
    EP_GLOBAL std::string outputDYJsonFileName("eplusout_daily.json");
    EP_GLOBAL std::string outputHRJsonFileName("eplusout_hourly.json");
    EP_GLOBAL std::string outputSMJsonFileName("eplusout_runperiod.json");
    EP_GLOBAL std::string outputCborFileName("eplusout.cbor");
    EP_GLOBAL std::string outputTSHvacCborFileName("eplusout_detailed_HVAC.cbor");
    EP_GLOBAL std::string outputTSZoneCborFileName("eplusout_detailed_zone.cbor");
    EP_GLOBAL std::string outputTSCborFileName("eplusout_timestep.cbor");
    EP_GLOBAL std::string outputYRCborFileName("eplusout_yearly.cbor");
    EP_GLOBAL std::string outputMNCborFileName("eplusout_monthly.cbor");
    EP_GLOBAL std::string outputDYCborFileName("eplusout_daily.cbor");
    EP_GLOBAL std::string outputHRCborFileName("eplusout_hourly.cbor");
    EP_GLOBAL std::string outputSMCborFileName("eplusout_runperiod.cbor");
    EP_GLOBAL std::string outputMsgPackFileName("eplusout.msgpack");
    EP_GLOBAL std::string outputTSHvacMsgPackFileName("eplusout_detailed_HVAC.msgpack");
    EP_GLOBAL std::string outputTSZoneMsgPackFileName("eplusout_detailed_zone.msgpack");
    EP_GLOBAL std::string outputTSMsgPackFileName("eplusout_timestep.msgpack");
    EP_GLOBAL std::string outputYRMsgPackFileName("eplusout_yearly.msgpack");
    EP_GLOBAL std::string outputMNMsgPackFileName("eplusout_monthly.msgpack");
    EP_GLOBAL std::string outputDYMsgPackFileName("eplusout_daily.msgpack");
    EP_GLOBAL std::string outputHRMsgPackFileName("eplusout_hourly.msgpack");
    EP_GLOBAL std::string outputSMMsgPackFileName("eplusout_runperiod.msgpack");
    EP_GLOBAL std::string outputMtdFileName("eplusout.mtd");
    EP_GLOBAL std::string outputMddFileName("eplusout.mdd");
    EP_GLOBAL std::string outputMtrFileName("eplusout.mtr");
    EP_GLOBAL std::string outputRddFileName("eplusout.rdd");
    EP_GLOBAL std::string outputShdFileName("eplusout.shd");
    EP_GLOBAL std::string outputTblCsvFileName("eplustbl.csv");
    EP_GLOBAL std::string outputTblHtmFileName("eplustbl.htm");
    EP_GLOBAL std::string outputTblTabFileName("eplustbl.tab");
    EP_GLOBAL std::string outputTblTxtFileName("eplustbl.txt");
    EP_GLOBAL std::string outputTblXmlFileName("eplustbl.xml");
    EP_GLOBAL std::string outputAdsFileName("eplusADS.out");
    EP_GLOBAL std::string outputDfsFileName("eplusout.dfs");
    EP_GLOBAL std::string outputGLHEFileName("eplusout.glhe");
    EP_GLOBAL std::string outputDelightInFileName("eplusout.delightin");
    EP_GLOBAL std::string outputDelightOutFileName("eplusout.delightout");
    EP_GLOBAL std::string outputDelightEldmpFileName("eplusout.delighteldmp");
    EP_GLOBAL std::string outputDelightDfdmpFileName("eplusout.delightdfdmp");
    EP_GLOBAL std::string outputMapTabFileName("eplusmap.tab");
    EP_GLOBAL std::string outputMapCsvFileName("eplusmap.csv");
    EP_GLOBAL std::string outputMapTxtFileName("eplusmap.txt");
    EP_GLOBAL std::string outputEddFileName("eplusout.edd");
    EP_GLOBAL std::string outputIperrFileName("eplusout.iperr");
    EP_GLOBAL std::string outputDbgFileName("eplusout.dbg");
    EP_GLOBAL std::string outputSlnFileName("eplusout.sln");
    EP_GLOBAL std::string outputSciFileName("eplusout.sci");
    EP_GLOBAL std::string outputWrlFileName("eplusout.wrl");
    EP_GLOBAL std::string outputZszCsvFileName("epluszsz.csv");
    EP_GLOBAL std::string outputZszTabFileName("epluszsz.tab");
    EP_GLOBAL std::string outputZszTxtFileName("epluszsz.txt");
    EP_GLOBAL std::string outputSszCsvFileName("eplusssz.csv");
    EP_GLOBAL std::string outputSszTabFileName("eplusssz.tab");
    EP_GLOBAL std::string outputSszTxtFileName("eplusssz.txt");
    EP_GLOBAL std::string outputScreenCsvFileName("eplusscreen.csv");
    EP_GLOBAL std::string outputSqlFileName("eplusout.sql");
    EP_GLOBAL std::string outputSqliteErrFileName("eplussqlite.err");
    EP_GLOBAL std::string TarcogIterationsFileName("TarcogIterations.dbg");
    EP_GLOBAL std::string outputCsvFileName("eplusout.csv");
    EP_GLOBAL std::string outputMtrCsvFileName("eplusmtr.csv");
    EP_GLOBAL std::string outputRvauditFileName("eplusout.rvaudit");
    EP_GLOBAL std::string outputExtShdFracFileName("eplusshading.csv");

    EP_GLOBAL std::string EnergyPlusIniFileName;
    EP_GLOBAL std::string inStatFileName;
    EP_GLOBAL std::string eplusADSFileName;
    EP_GLOBAL std::string idfFileNameOnly;
    EP_GLOBAL std::string idfDirPathName;
    EP_GLOBAL std::string outDirPathName;
    EP_GLOBAL std::string inputFileNameOnly;
    EP_GLOBAL std::string inputDirPathName;
    EP_GLOBAL std::string outputDirPathName;
    EP_GLOBAL std::string exeDirectory;
    EP_GLOBAL std::string inputFileName;
    EP_GLOBAL std::string inputIddFileName;
    EP_GLOBAL std::string inputEpJSONSchemaFileName;
    EP_GLOBAL std::string inputWeatherFileName;
    EP_GLOBAL std::string FullName;
    EP_GLOBAL std::string weatherFileNameOnly;
    EP_GLOBAL std::string ProgramPath;          // Path for Program from INI file
    EP_GLOBAL std::string CurrentWorkingFolder; // Current working directory for run
    EP_GLOBAL std::string CurrentDateTime;      // For printing current date and time at start of run
    EP_GLOBAL std::string IDDVerString;         // Version information from the IDD (line 1)

    EP_GLOBAL std::string
        VerString("EnergyPlus, Version ${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}.${CMAKE_VERSION_PATCH}-${CMAKE_VERSION_BUILD}"); // String that
                                                                                                                                      // represents
                                                                                                                                      // version
                                                                                                                                      // information
    EP_GLOBAL std::string MatchVersion("${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}"); // String to be matched by Version object


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
