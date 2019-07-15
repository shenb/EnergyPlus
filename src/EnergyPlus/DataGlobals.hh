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

#ifndef DataGlobals_hh_INCLUDED
#define DataGlobals_hh_INCLUDED

// C++ Headers
#include <iosfwd>
#include <string>

// EnergyPlus Headers
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace DataGlobals {

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    EP_GLOBAL extern bool runReadVars;
    EP_GLOBAL extern bool DDOnlySimulation;
    EP_GLOBAL extern bool AnnualSimulation;
    EP_GLOBAL extern bool outputEpJSONConversion;
    EP_GLOBAL extern bool isEpJSON;
    EP_GLOBAL extern bool isCBOR;
    EP_GLOBAL extern bool isMsgPack;
    EP_GLOBAL extern bool preserveIDFOrder;

    // MODULE PARAMETER DEFINITIONS:
    EP_GLOBAL extern int const BeginDay;
    EP_GLOBAL extern int const DuringDay;
    EP_GLOBAL extern int const EndDay;
    EP_GLOBAL extern int const EndZoneSizingCalc;
    EP_GLOBAL extern int const EndSysSizingCalc;

    // Parameters for KindOfSim
    EP_GLOBAL extern int const ksDesignDay;
    EP_GLOBAL extern int const ksRunPeriodDesign;
    EP_GLOBAL extern int const ksRunPeriodWeather;
    EP_GLOBAL extern int const ksHVACSizeDesignDay;       // a regular design day run during HVAC Sizing Simulation
    EP_GLOBAL extern int const ksHVACSizeRunPeriodDesign; // a weather period design day run during HVAC Sizing Simulation
    EP_GLOBAL extern int const ksReadAllWeatherData;      // a weather period for reading all weather data prior to the simulation

    EP_GLOBAL extern int const ZoneTSReporting; // value for Zone Time Step Reporting (UpdateDataAndReport)
    EP_GLOBAL extern int const HVACTSReporting; // value for HVAC Time Step Reporting (UpdateDataAndReport)

    EP_GLOBAL extern Real64 const MaxEXPArg; // maximum exponent in EXP() function
    EP_GLOBAL extern Real64 const Pi;        // Pi 3.1415926535897932384626435
    EP_GLOBAL extern Real64 const PiOvr2;    // Pi/2
    EP_GLOBAL extern Real64 const TwoPi;     // 2*Pi 6.2831853071795864769252868
    EP_GLOBAL extern Real64 const GravityConstant;
    EP_GLOBAL extern Real64 const DegToRadians;                  // Conversion for Degrees to Radians
    EP_GLOBAL extern Real64 const RadToDeg;                      // Conversion for Radians to Degrees
    EP_GLOBAL extern Real64 const SecInHour;                     // Conversion for hours to seconds
    EP_GLOBAL extern Real64 const HoursInDay;                    // Number of Hours in Day
    EP_GLOBAL extern Real64 const SecsInDay;                     // Number of seconds in Day
    EP_GLOBAL extern Real64 const BigNumber;                     // Max Number real used for initializations
    EP_GLOBAL extern Real64 const rTinyValue;                    // Tiny value to replace use of TINY(x)
    EP_GLOBAL extern std::string::size_type const MaxNameLength; // Maximum Name Length in Characters -- should be the same
    // as MaxAlphaArgLength in InputProcessor module

    EP_GLOBAL extern Real64 const KelvinConv;        // Conversion factor for C to K and K to C
    EP_GLOBAL extern Real64 const InitConvTemp;      // [deg C], standard init vol to mass flow conversion temp
    EP_GLOBAL extern Real64 const AutoCalculate;     // automatically calculate some fields.
    EP_GLOBAL extern Real64 const CWInitConvTemp;    // [deg C], standard init chilled water vol to mass flow conversion temp
    EP_GLOBAL extern Real64 const HWInitConvTemp;    // [deg C], standard init hot water vol to mass flow conversion temp
    EP_GLOBAL extern Real64 const SteamInitConvTemp; // [deg C], standard init steam vol to mass flow conversion temp

    EP_GLOBAL extern Real64 const StefanBoltzmann;   // Stefan-Boltzmann constant in W/(m2*K4)
    EP_GLOBAL extern Real64 const UniversalGasConst; // (J/mol*K)

    EP_GLOBAL extern Real64 const convertJtoGJ; // Conversion factor for J to GJ

    // Parameters for EMS Calling Points
    EP_GLOBAL extern int const emsCallFromZoneSizing;                           // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromSystemSizing;                         // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromBeginNewEvironment;                   // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromBeginNewEvironmentAfterWarmUp;        // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromBeginTimestepBeforePredictor;         // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromBeforeHVACManagers;                   // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromAfterHVACManagers;                    // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromHVACIterationLoop;                    // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromEndSystemTimestepBeforeHVACReporting; // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromEndSystemTimestepAfterHVACReporting;  // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromEndZoneTimestepBeforeZoneReporting;   // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromEndZoneTimestepAfterZoneReporting;    // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromSetupSimulation;                      // identify where EMS called from,
    // this is for input processing only
    EP_GLOBAL extern int const emsCallFromExternalInterface;         // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromComponentGetInput;         // EMS called from end of get input for a component
    EP_GLOBAL extern int const emsCallFromUserDefinedComponentModel; // EMS called from inside a custom user component model
    EP_GLOBAL extern int const emsCallFromUnitarySystemSizing;       // EMS called from unitary system compound component
    EP_GLOBAL extern int const emsCallFromBeginZoneTimestepBeforeInitHeatBalance; // Identity where EMS called from
    EP_GLOBAL extern int const emsCallFromBeginZoneTimestepAfterInitHeatBalance; // Identity where EMS called from

    EP_GLOBAL extern int const ScheduleAlwaysOn; // Value when passed to schedule routines gives back 1.0 (on)

    // DERIVED TYPE DEFINITIONS:
    // na

    // INTERFACE BLOCK SPECIFICATIONS:
    // see DataOmterfaces fpr global interface statements

    // MODULE VARIABLE DECLARATIONS:

    struct JsonOutputStreams
    {
        std::ostream *json_stream = nullptr; // Internal stream used for json output
        std::ostream *json_TSstream_Zone = nullptr;
        std::ostream *json_TSstream_HVAC = nullptr;
        std::ostream *json_TSstream = nullptr;
        std::ostream *json_HRstream = nullptr;
        std::ostream *json_MNstream = nullptr;
        std::ostream *json_DYstream = nullptr;
        std::ostream *json_SMstream = nullptr;
        std::ostream *json_YRstream = nullptr;
        std::ostream *cbor_stream = nullptr; // Internal stream used for cbor output
        std::ostream *cbor_TSstream_Zone = nullptr;
        std::ostream *cbor_TSstream_HVAC = nullptr;
        std::ostream *cbor_TSstream = nullptr;
        std::ostream *cbor_HRstream = nullptr;
        std::ostream *cbor_MNstream = nullptr;
        std::ostream *cbor_DYstream = nullptr;
        std::ostream *cbor_SMstream = nullptr;
        std::ostream *cbor_YRstream = nullptr;
        std::ostream *msgpack_stream = nullptr; // Internal stream used for messagepack output
        std::ostream *msgpack_TSstream_Zone = nullptr;
        std::ostream *msgpack_TSstream_HVAC = nullptr;
        std::ostream *msgpack_TSstream = nullptr;
        std::ostream *msgpack_HRstream = nullptr;
        std::ostream *msgpack_MNstream = nullptr;
        std::ostream *msgpack_DYstream = nullptr;
        std::ostream *msgpack_SMstream = nullptr;
        std::ostream *msgpack_YRstream = nullptr;

        int OutputFileJson = 0; // Unit number for Schema output
        int OutputFileTSZoneJson = 0;
        int OutputFileTSHVACJson = 0;
        int OutputFileTSJson = 0;
        int OutputFileHRJson = 0;
        int OutputFileDYJson = 0;
        int OutputFileMNJson = 0;
        int OutputFileSMJson = 0;
        int OutputFileYRJson = 0;
        int OutputFileCBOR = 0; // Unit number for Schema output
        int OutputFileTSZoneCBOR = 0;
        int OutputFileTSHVACCBOR = 0;
        int OutputFileTSCBOR = 0;
        int OutputFileHRCBOR = 0;
        int OutputFileDYCBOR = 0;
        int OutputFileMNCBOR = 0;
        int OutputFileSMCBOR = 0;
        int OutputFileYRCBOR = 0;
        int OutputFileMsgPack = 0; // Unit number for Schema output
        int OutputFileTSZoneMsgPack = 0;
        int OutputFileTSHVACMsgPack = 0;
        int OutputFileTSMsgPack = 0;
        int OutputFileHRMsgPack = 0;
        int OutputFileDYMsgPack = 0;
        int OutputFileMNMsgPack = 0;
        int OutputFileSMMsgPack = 0;
        int OutputFileYRMsgPack = 0;
    };

    EP_GLOBAL extern bool BeginDayFlag;           // True at the start of each day, False after first time step in day
    EP_GLOBAL extern bool BeginEnvrnFlag;         // True at the start of each environment, False after first time step in environ
    EP_GLOBAL extern bool BeginHourFlag;          // True at the start of each hour, False after first time step in hour
    EP_GLOBAL extern bool BeginSimFlag;           // True until any actual simulation (full or sizing) has begun, False after first time step
    EP_GLOBAL extern bool BeginFullSimFlag;       // True until full simulation has begun, False after first time step
    EP_GLOBAL extern bool BeginTimeStepFlag;      // True at the start of each time step, False after first subtime step of time step
    EP_GLOBAL extern int DayOfSim;                // Counter for days (during the simulation)
    EP_GLOBAL extern std::string DayOfSimChr;     // Counter for days (during the simulation) (character -- for reporting)
    EP_GLOBAL extern int CalendarYear;            // Calendar year of the current day of simulation
    EP_GLOBAL extern std::string CalendarYearChr; // Calendar year of the current day of simulation (character -- for reporting)
    EP_GLOBAL extern bool EndEnvrnFlag;           // True at the end of each environment (last time step of last hour of last day of environ)
    EP_GLOBAL extern bool EndDesignDayEnvrnsFlag; // True at the end of the last design day environment
    // (last time step of last hour of last day of environ which is a design day)
    EP_GLOBAL extern bool EndDayFlag;                          // True at the end of each day (last time step of last hour of day)
    EP_GLOBAL extern bool EndHourFlag;                         // True at the end of each hour (last time step of hour)
    EP_GLOBAL extern int PreviousHour;                         // Previous Hour Index
    EP_GLOBAL extern int HourOfDay;                            // Counter for hours in a simulation day
    EP_GLOBAL extern Real64 WeightPreviousHour;                // Weighting of value for previous hour
    EP_GLOBAL extern Real64 WeightNow;                         // Weighting of value for current hour
    EP_GLOBAL extern int NumOfDayInEnvrn;                      // Number of days in the simulation for a particular environment
    EP_GLOBAL extern int NumOfTimeStepInHour;                  // Number of time steps in each hour of the simulation
    EP_GLOBAL extern int NumOfZones;                           // Total number of Zones for simulation
    EP_GLOBAL extern int TimeStep;                             // Counter for time steps (fractional hours)
    EP_GLOBAL extern Real64 TimeStepZone;                      // Zone time step in fractional hours
    EP_GLOBAL extern bool WarmupFlag;                          // True during the warmup portion of a simulation
    EP_GLOBAL extern int OutputFileStandard;                   // Unit number for the standard output file (hourly data only)
    EP_GLOBAL extern std::ostream *eso_stream;                 // Internal stream used for eso output (used for performance)
    EP_GLOBAL extern JsonOutputStreams jsonOutputStreams;      // Internal streams used for json outputs
    EP_GLOBAL extern int OutputStandardError;                  // Unit number for the standard error output file
    EP_GLOBAL extern std::ostream *err_stream;                 // Internal stream used for err output (used for performance)
    EP_GLOBAL extern int StdOutputRecordCount;                 // Count of Standard output records
    EP_GLOBAL extern int OutputFileInits;                      // Unit number for the standard Initialization output file
    EP_GLOBAL extern std::ostream *eio_stream;                 // Internal stream used for eio output (used for unit tests)
    EP_GLOBAL extern int OutputFileDebug;                      // Unit number for debug outputs
    EP_GLOBAL extern int OutputFileZoneSizing;                 // Unit number of zone sizing calc output file
    EP_GLOBAL extern int OutputFileSysSizing;                  // Unit number of system sizing calc output file
    EP_GLOBAL extern int OutputFileMeters;                     // Unit number for meters output
    EP_GLOBAL extern std::ostream *mtr_stream;                 // Internal stream used for mtr output (used for performance)
    EP_GLOBAL extern int OutputFileShadingFrac;                // Unit number for shading output
    EP_GLOBAL extern int StdMeterRecordCount;                  // Count of Meter output records
    EP_GLOBAL extern int OutputFileBNDetails;                  // Unit number for Branch-Node Details
    EP_GLOBAL extern int OutputDElightIn;                      // Unit number for the DElight In file
    EP_GLOBAL extern std::ostream *delightin_stream;           // Internal stream used for DElight In file
    EP_GLOBAL extern bool ZoneSizingCalc;                      // TRUE if zone sizing calculation
    EP_GLOBAL extern bool SysSizingCalc;                       // TRUE if system sizing calculation
    EP_GLOBAL extern bool DoZoneSizing;                        // User input in SimulationControl object
    EP_GLOBAL extern bool DoSystemSizing;                      // User input in SimulationControl object
    EP_GLOBAL extern bool DoPlantSizing;                       // User input in SimulationControl object
    EP_GLOBAL extern bool DoDesDaySim;                         // User input in SimulationControl object
    EP_GLOBAL extern bool DoWeathSim;                          // User input in SimulationControl object
    EP_GLOBAL extern bool DoHVACSizingSimulation;              // User input in SimulationControl object
    EP_GLOBAL extern int HVACSizingSimMaxIterations;           // User input in SimulationControl object
    EP_GLOBAL extern bool WeathSimReq;                         // Input has a RunPeriod request
    EP_GLOBAL extern int KindOfSim;                            // See parameters. (ksDesignDay, ksRunPeriodDesign, ksRunPeriodWeather)
    EP_GLOBAL extern bool DoOutputReporting;                   // TRUE if variables to be written out
    EP_GLOBAL extern bool DoingSizing;                         // TRUE when "sizing" is being performed (some error messages won't be displayed)
    EP_GLOBAL extern bool DoingHVACSizingSimulations;          // true when HVAC Sizing Simulations are being performed.
    EP_GLOBAL extern bool DoingInputProcessing;                // TRUE when "IP" is being performed (some error messages are cached)
    EP_GLOBAL extern bool DisplayAllWarnings;                  // True when selection for  "DisplayAllWarnings" is entered (turns on other warning flags)
    EP_GLOBAL extern bool DisplayExtraWarnings;                // True when selection for  "DisplayExtraWarnings" is entered
    EP_GLOBAL extern bool DisplayUnusedObjects;                // True when selection for  "DisplayUnusedObjects" is entered
    EP_GLOBAL extern bool DisplayUnusedSchedules;              // True when selection for  "DisplayUnusedSchedules" is entered
    EP_GLOBAL extern bool DisplayAdvancedReportVariables;      // True when selection for  "DisplayAdvancedReportVariables" is entered
    EP_GLOBAL extern bool DisplayZoneAirHeatBalanceOffBalance; // True when selection for  "DisplayZoneAirHeatBalanceOffBalance" is entered
    EP_GLOBAL extern bool DisplayInputInAudit;                 // True when environmental variable "DisplayInputInAudit" is used
    EP_GLOBAL extern bool CreateMinimalSurfaceVariables;       // True when selection for  "CreateMinimalSurfaceVariables" is entered
    EP_GLOBAL extern Real64 CurrentTime;                       // CurrentTime, in fractional hours, from start of day. Uses Loads time step.
    EP_GLOBAL extern int SimTimeSteps;                         // Number of (Loads) timesteps since beginning of run period (environment).
    EP_GLOBAL extern int MinutesPerTimeStep;                   // Minutes per time step calculated from NumTimeStepInHour (number of minutes per load time step)
    EP_GLOBAL extern Real64 TimeStepZoneSec;                   // Seconds per time step
    EP_GLOBAL extern bool MetersHaveBeenInitialized;
    EP_GLOBAL extern bool KickOffSimulation;                 // Kick off simulation -- meaning run each environment for 1 or 2 time steps.
    EP_GLOBAL extern bool KickOffSizing;                     // Kick off sizing -- meaning run each environment for 1 or 2 time steps.
    EP_GLOBAL extern bool RedoSizesHVACSimulation;           // doing kick off simulation for redoing sizes as part of sizing
    EP_GLOBAL extern bool FinalSizingHVACSizingSimIteration; // true if this will be no more HVAC sizing sim iterations
    EP_GLOBAL extern bool AnyEnergyManagementSystemInModel;  // true if there is any EMS or Erl in model.  otherwise false
    EP_GLOBAL extern bool AnyLocalEnvironmentsInModel;       // true if there is any local environmental data objected defined in model, otherwise false
    EP_GLOBAL extern bool AnyPlantInModel;                   // true if there are any plant or condenser loops in model, otherwise false
    EP_GLOBAL extern int CacheIPErrorFile;                   // Cache IP errors until IDF processing done.
    EP_GLOBAL extern bool AnyIdealCondEntSetPointInModel;    // true if there is any ideal condenser entering set point manager in model.
    EP_GLOBAL extern bool RunOptCondEntTemp;                 // true if the ideal condenser entering set point optimization is running
    EP_GLOBAL extern bool CompLoadReportIsReq;               // true if the extra sizing calcs are performed to create a "pulse" for the load component report
    EP_GLOBAL extern bool isPulseZoneSizing;                 // true during the set of zone sizing calcs that include the "pulse" for the load component report
    EP_GLOBAL extern int
        OutputFileZonePulse; // file handle for special zone sizing report that contains the result of the "pulse" for the load component report
    EP_GLOBAL extern bool doLoadComponentPulseNow; // true for the time step that is the "pulse" for the load component report
    EP_GLOBAL extern bool ShowDecayCurvesInEIO;    // true if the Radiant to Convective Decay Curves should appear in the EIO file
    EP_GLOBAL extern bool AnySlabsInModel;         // true if there are any zone-coupled ground domains in the input file
    EP_GLOBAL extern bool AnyBasementsInModel;     // true if there are any basements in the input file

    EP_GLOBAL extern int Progress;
    EP_GLOBAL extern void (*fProgressPtr)(int const);
    EP_GLOBAL extern void (*fMessagePtr)(std::string const &);

    // Clears the global data in DataGlobals.
    // Needed for unit tests, should not be normally called.
    void clear_state();

} // namespace DataGlobals

} // namespace EnergyPlus

#endif
