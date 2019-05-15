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
    thread_local extern int const iASCII_CR;    // endline value when just CR instead of CR/LF
    thread_local extern int const iUnicode_end; // endline value when Unicode file
    thread_local extern char const tabchar;
    thread_local extern int const GoodIOStatValue;       // good value for IOStat during reads/writes
    thread_local extern int const MaxTimingStringLength; // string length for timing string array

    thread_local extern std::string const DDOnlyEnvVar;             // Only run design days
    thread_local extern std::string const ReverseDDEnvVar;          // Reverse DD during run
    thread_local extern std::string const DisableGLHECachingEnvVar; // GLHE Caching
    thread_local extern std::string const FullAnnualSimulation;     // Generate annual run
    thread_local extern std::string const cDeveloperFlag;
    thread_local extern std::string const cDisplayAllWarnings;
    thread_local extern std::string const cDisplayExtraWarnings;
    thread_local extern std::string const cDisplayAdvancedReportVariables;
    thread_local extern std::string const cDisplayUnusedObjects;
    thread_local extern std::string const cDisplayUnusedSchedules;
    thread_local extern std::string const cDisplayZoneAirHeatBalanceOffBalance;
    thread_local extern std::string const cSortIDD;
    thread_local extern std::string const cReportDuringWarmup;
    thread_local extern std::string const cReportDuringHVACSizingSimulation;
    thread_local extern std::string const cIgnoreSolarRadiation;
    thread_local extern std::string const cIgnoreBeamRadiation;
    thread_local extern std::string const cIgnoreDiffuseRadiation;
    thread_local extern std::string const cSutherlandHodgman;
    thread_local extern std::string const cMinimalSurfaceVariables;
    thread_local extern std::string const cMinimalShadowing;
    thread_local extern std::string const cNumActiveSims;
    thread_local extern std::string const cInputPath1; // EP-Launch setting.  Full path + project name
    thread_local extern std::string const cInputPath2; // RunEplus.bat setting.  Full path
    thread_local extern std::string const cProgramPath;
    thread_local extern std::string const cTimingFlag;
    thread_local extern std::string const TrackAirLoopEnvVar; // To generate a file with runtime statistics
    // for each controller on each air loop
    thread_local extern std::string const TraceAirLoopEnvVar; // To generate a trace file with the converged
    // solutions of all controllers on each air loop at each call to SimAirLoop()
    thread_local extern std::string const TraceHVACControllerEnvVar; // To generate a trace file for
    //  each individual HVAC controller with all controller iterations

    thread_local extern std::string const MinReportFrequencyEnvVar;   // environment var for reporting frequency.
    thread_local extern std::string const cDisplayInputInAuditEnvVar; // environmental variable that enables the echoing of the input file into the audit file

    // DERIVED TYPE DEFINITIONS
    // na

    // INTERFACE BLOCK SPECIFICATIONS
    // na

    // MODULE VARIABLE DECLARATIONS:
    thread_local extern bool DDOnly;                           // TRUE if design days (sizingperiod:*) only are to be run.
    thread_local extern bool ReverseDD;                        // TRUE if reverse design days (reordering sizingperiod:*) are to be run.
    thread_local extern bool DisableGLHECaching;               // TRUE if GLHE caching is to be disabled, for example, during unit tests
    thread_local extern bool FullAnnualRun;                    // TRUE if full annual simulation is to be run.
    thread_local extern bool DeveloperFlag;                    // TRUE if developer flag is turned on. (turns on more displays to console)
    thread_local extern bool TimingFlag;                       // TRUE if timing flag is turned on. (turns on more timing displays to console)
    thread_local extern bool SutherlandHodgman;                // TRUE if SutherlandHodgman algorithm for polygon clipping is to be used.
    thread_local extern bool DetailedSkyDiffuseAlgorithm;      // use detailed diffuse shading algorithm for sky (shading transmittance varies)
    thread_local extern bool DetailedSolarTimestepIntegration; // when true, use detailed timestep integration for all solar,shading, etc.
    thread_local extern bool TrackAirLoopEnvFlag;              // If TRUE generates a file with runtime statistics for each HVAC
    //  controller on each air loop
    thread_local extern bool TraceAirLoopEnvFlag; // If TRUE generates a trace file with the converged solutions of all
    // HVAC controllers on each air loop at each call to SimAirLoop()
    thread_local extern bool TraceHVACControllerEnvFlag; // If TRUE generates a trace file for each individual HVAC
    // controller with all controller iterations
    thread_local extern bool ReportDuringWarmup;                      // True when the report outputs even during warmup
    thread_local extern bool ReportDuringHVACSizingSimulation;        // true when reporting outputs during HVAC sizing Simulation
    thread_local extern bool ReportDetailedWarmupConvergence;         // True when the detailed warmup convergence is requested
    thread_local extern bool UpdateDataDuringWarmupExternalInterface; // variable sets in the external interface.
    thread_local extern bool UseScheduledSunlitFrac;                  // when true, the external shading calculation results will be exported
    thread_local extern bool ReportExtShadingSunlitFrac;              // when true, the sunlit fraction for all surfaces are exported as a csv format output
    thread_local extern bool UseImportedSunlitFrac;                   // when true, the sunlit fraction for all surfaces are imported altogether as a CSV file

    thread_local extern bool DisableGroupSelfShading; // when true, defined shadowing surfaces group is ignored when calculating sunlit fraction
    thread_local extern bool DisableAllSelfShading;   // when true, all external shadowing surfaces is ignored when calculating sunlit fraction

    // This update the value during the warmup added for FMI
    thread_local extern Real64 Elapsed_Time;            // For showing elapsed time at end of run
    thread_local extern Real64 Time_Start;              // Call to CPU_Time for start time of simulation
    thread_local extern Real64 Time_Finish;             // Call to CPU_Time for end time of simulation
    thread_local extern std::string MinReportFrequency; // String for minimum reporting frequency
    thread_local extern bool SortedIDD;                 // after processing, use sorted IDD to obtain Defs, etc.
    thread_local extern bool lMinimalShadowing;         // TRUE if MinimalShadowing is to override Solar Distribution flag
    thread_local extern std::string TempFullFileName;
    thread_local extern std::string envinputpath1;
    thread_local extern std::string envinputpath2;
    thread_local extern std::string envprogrampath;
    thread_local extern bool TestAllPaths;
    thread_local extern int iEnvSetThreads;
    thread_local extern bool lEnvSetThreadsInput;
    thread_local extern int iepEnvSetThreads;
    thread_local extern bool lepSetThreadsInput;
    thread_local extern int iIDFSetThreads;
    thread_local extern bool lIDFSetThreadsInput;
    thread_local extern int inumActiveSims;
    thread_local extern bool lnumActiveSims;
    thread_local extern int MaxNumberOfThreads;
    thread_local extern int NumberIntRadThreads;
    thread_local extern int iNominalTotSurfaces;
    thread_local extern bool Threading;

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
