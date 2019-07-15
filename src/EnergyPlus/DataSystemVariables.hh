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

#ifndef DataSystemVariables_hh_INCLUDED
#define DataSystemVariables_hh_INCLUDED

// C++ Headers
#include <string>

// EnergyPlus Headers
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace DataSystemVariables {

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    // MODULE PARAMETER DEFINITIONS:
    EP_GLOBAL extern int const iASCII_CR;    // endline value when just CR instead of CR/LF
    EP_GLOBAL extern int const iUnicode_end; // endline value when Unicode file
    EP_GLOBAL extern char const tabchar;
    EP_GLOBAL extern int const GoodIOStatValue;       // good value for IOStat during reads/writes
    EP_GLOBAL extern int const MaxTimingStringLength; // string length for timing string array

    EP_GLOBAL extern std::string const DDOnlyEnvVar;             // Only run design days
    EP_GLOBAL extern std::string const ReverseDDEnvVar;          // Reverse DD during run
    EP_GLOBAL extern std::string const DisableGLHECachingEnvVar; // GLHE Caching
    EP_GLOBAL extern std::string const FullAnnualSimulation;     // Generate annual run
    EP_GLOBAL extern std::string const cDeveloperFlag;
    EP_GLOBAL extern std::string const cDisplayAllWarnings;
    EP_GLOBAL extern std::string const cDisplayExtraWarnings;
    EP_GLOBAL extern std::string const cDisplayAdvancedReportVariables;
    EP_GLOBAL extern std::string const cDisplayUnusedObjects;
    EP_GLOBAL extern std::string const cDisplayUnusedSchedules;
    EP_GLOBAL extern std::string const cDisplayZoneAirHeatBalanceOffBalance;
    EP_GLOBAL extern std::string const cSortIDD;
    EP_GLOBAL extern std::string const cReportDuringWarmup;
    EP_GLOBAL extern std::string const cReportDuringHVACSizingSimulation;
    EP_GLOBAL extern std::string const cIgnoreSolarRadiation;
    EP_GLOBAL extern std::string const cIgnoreBeamRadiation;
    EP_GLOBAL extern std::string const cIgnoreDiffuseRadiation;
    EP_GLOBAL extern std::string const cSutherlandHodgman;
    EP_GLOBAL extern std::string const cMinimalSurfaceVariables;
    EP_GLOBAL extern std::string const cMinimalShadowing;
    EP_GLOBAL extern std::string const cNumActiveSims;
    EP_GLOBAL extern std::string const cInputPath1; // EP-Launch setting.  Full path + project name
    EP_GLOBAL extern std::string const cInputPath2; // RunEplus.bat setting.  Full path
    EP_GLOBAL extern std::string const cProgramPath;
    EP_GLOBAL extern std::string const cTimingFlag;
    EP_GLOBAL extern std::string const TrackAirLoopEnvVar; // To generate a file with runtime statistics
    // for each controller on each air loop
    EP_GLOBAL extern std::string const TraceAirLoopEnvVar; // To generate a trace file with the converged
    // solutions of all controllers on each air loop at each call to SimAirLoop()
    EP_GLOBAL extern std::string const TraceHVACControllerEnvVar; // To generate a trace file for
    //  each individual HVAC controller with all controller iterations

    EP_GLOBAL extern std::string const MinReportFrequencyEnvVar;   // environment var for reporting frequency.
    EP_GLOBAL extern std::string const cDisplayInputInAuditEnvVar; // environmental variable that enables the echoing of the input file into the audit file

    // DERIVED TYPE DEFINITIONS
    // na

    // INTERFACE BLOCK SPECIFICATIONS
    // na

    // MODULE VARIABLE DECLARATIONS:
    EP_GLOBAL extern bool DDOnly;                           // TRUE if design days (sizingperiod:*) only are to be run.
    EP_GLOBAL extern bool ReverseDD;                        // TRUE if reverse design days (reordering sizingperiod:*) are to be run.
    EP_GLOBAL extern bool DisableGLHECaching;               // TRUE if GLHE caching is to be disabled, for example, during unit tests
    EP_GLOBAL extern bool FullAnnualRun;                    // TRUE if full annual simulation is to be run.
    EP_GLOBAL extern bool DeveloperFlag;                    // TRUE if developer flag is turned on. (turns on more displays to console)
    EP_GLOBAL extern bool TimingFlag;                       // TRUE if timing flag is turned on. (turns on more timing displays to console)
    EP_GLOBAL extern bool SutherlandHodgman;                // TRUE if SutherlandHodgman algorithm for polygon clipping is to be used.
    EP_GLOBAL extern bool DetailedSkyDiffuseAlgorithm;      // use detailed diffuse shading algorithm for sky (shading transmittance varies)
    EP_GLOBAL extern bool DetailedSolarTimestepIntegration; // when true, use detailed timestep integration for all solar,shading, etc.
    EP_GLOBAL extern bool TrackAirLoopEnvFlag;              // If TRUE generates a file with runtime statistics for each HVAC
    //  controller on each air loop
    EP_GLOBAL extern bool TraceAirLoopEnvFlag; // If TRUE generates a trace file with the converged solutions of all
    // HVAC controllers on each air loop at each call to SimAirLoop()
    EP_GLOBAL extern bool TraceHVACControllerEnvFlag; // If TRUE generates a trace file for each individual HVAC
    // controller with all controller iterations
    EP_GLOBAL extern bool ReportDuringWarmup;                      // True when the report outputs even during warmup
    EP_GLOBAL extern bool ReportDuringHVACSizingSimulation;        // true when reporting outputs during HVAC sizing Simulation
    EP_GLOBAL extern bool ReportDetailedWarmupConvergence;         // True when the detailed warmup convergence is requested
    EP_GLOBAL extern bool UpdateDataDuringWarmupExternalInterface; // variable sets in the external interface.
    EP_GLOBAL extern bool UseScheduledSunlitFrac;                  // when true, the external shading calculation results will be exported
    EP_GLOBAL extern bool ReportExtShadingSunlitFrac;              // when true, the sunlit fraction for all surfaces are exported as a csv format output
    EP_GLOBAL extern bool UseImportedSunlitFrac;                   // when true, the sunlit fraction for all surfaces are imported altogether as a CSV file

    EP_GLOBAL extern bool DisableGroupSelfShading; // when true, defined shadowing surfaces group is ignored when calculating sunlit fraction
    EP_GLOBAL extern bool DisableAllSelfShading;   // when true, all external shadowing surfaces is ignored when calculating sunlit fraction

    // This update the value during the warmup added for FMI
    EP_GLOBAL extern Real64 Elapsed_Time;            // For showing elapsed time at end of run
    EP_GLOBAL extern Real64 Time_Start;              // Call to CPU_Time for start time of simulation
    EP_GLOBAL extern Real64 Time_Finish;             // Call to CPU_Time for end time of simulation
    EP_GLOBAL extern std::string MinReportFrequency; // String for minimum reporting frequency
    EP_GLOBAL extern bool SortedIDD;                 // after processing, use sorted IDD to obtain Defs, etc.
    EP_GLOBAL extern bool lMinimalShadowing;         // TRUE if MinimalShadowing is to override Solar Distribution flag
    EP_GLOBAL extern std::string TempFullFileName;
    EP_GLOBAL extern std::string envinputpath1;
    EP_GLOBAL extern std::string envinputpath2;
    EP_GLOBAL extern std::string envprogrampath;
    EP_GLOBAL extern bool TestAllPaths;
    EP_GLOBAL extern int iEnvSetThreads;
    EP_GLOBAL extern bool lEnvSetThreadsInput;
    EP_GLOBAL extern int iepEnvSetThreads;
    EP_GLOBAL extern bool lepSetThreadsInput;
    EP_GLOBAL extern int iIDFSetThreads;
    EP_GLOBAL extern bool lIDFSetThreadsInput;
    EP_GLOBAL extern int inumActiveSims;
    EP_GLOBAL extern bool lnumActiveSims;
    EP_GLOBAL extern int MaxNumberOfThreads;
    EP_GLOBAL extern int NumberIntRadThreads;
    EP_GLOBAL extern int iNominalTotSurfaces;
    EP_GLOBAL extern bool Threading;

    // Functions

    void CheckForActualFileName(std::string const &originalInputFileName, // name as input for object
                                bool &FileFound,                          // Set to true if file found and is in CheckedFileName
                                std::string &CheckedFileName              // Blank if not found.
    );

    // Needed for unit tests, should not be normally called.
    void clear_state();

} // namespace DataSystemVariables

} // namespace EnergyPlus

#endif
