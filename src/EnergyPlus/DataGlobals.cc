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

// C++ Headers
#include <ostream>

// ObjexxFCL Headers
#include <ObjexxFCL/numeric.hh>

// EnergyPlus Headers
#include <DataGlobals.hh>

namespace EnergyPlus {

namespace DataGlobals {

    // MODULE INFORMATION:
    //       AUTHOR         Rick Strand
    //       DATE WRITTEN   January 1997
    //       MODIFIED       May 1997 (RKS) Added Weather Variables
    //       MODIFIED       December 1997 (RKS,DF,LKL) Split into DataGlobals and DataEnvironment
    //       MODIFIED       February 1999 (FW) Added NextHour, WGTNEXT, WGTNOW
    //       MODIFIED       September 1999 (LKL) Rename WGTNEXT,WGTNOW for clarity
    //       RE-ENGINEERED  na

    // PURPOSE OF THIS MODULE:
    // This data-only module is a repository for all variables which are considered
    // to be "global" in nature in EnergyPlus.

    // METHODOLOGY EMPLOYED:
    // na

    // REFERENCES:
    // na

    // OTHER NOTES:
    // na

    // Using/Aliasing

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.
    EP_GLOBAL bool runReadVars(false);
    EP_GLOBAL bool DDOnlySimulation(false);
    EP_GLOBAL bool AnnualSimulation(false);
    EP_GLOBAL bool outputEpJSONConversion(false);
    EP_GLOBAL bool isEpJSON(false);
    EP_GLOBAL bool isCBOR(false);
    EP_GLOBAL bool isMsgPack(false);
    EP_GLOBAL bool preserveIDFOrder(true);

    // MODULE PARAMETER DEFINITIONS:
    EP_GLOBAL int const BeginDay(1);
    EP_GLOBAL int const DuringDay(2);
    EP_GLOBAL int const EndDay(3);
    EP_GLOBAL int const EndZoneSizingCalc(4);
    EP_GLOBAL int const EndSysSizingCalc(5);

    // Parameters for KindOfSim
    EP_GLOBAL int const ksDesignDay(1);
    EP_GLOBAL int const ksRunPeriodDesign(2);
    EP_GLOBAL int const ksRunPeriodWeather(3);
    EP_GLOBAL int const ksHVACSizeDesignDay(4);       // a regular design day run during HVAC Sizing Simulation
    EP_GLOBAL int const ksHVACSizeRunPeriodDesign(5); // a weather period design day run during HVAC Sizing Simulation
    EP_GLOBAL int const ksReadAllWeatherData(6);      // a weather period for reading all weather data prior to the simulation

    EP_GLOBAL int const ZoneTSReporting(1); // value for Zone Time Step Reporting (UpdateDataAndReport)
    EP_GLOBAL int const HVACTSReporting(2); // value for HVAC Time Step Reporting (UpdateDataAndReport)

    EP_GLOBAL Real64 const MaxEXPArg(709.78);       // maximum exponent in EXP() function
    EP_GLOBAL Real64 const Pi(3.14159265358979324); // Pi 3.1415926535897932384626435
    EP_GLOBAL Real64 const PiOvr2(Pi / 2.0);        // Pi/2
    EP_GLOBAL Real64 const TwoPi(2.0 * Pi);         // 2*Pi 6.2831853071795864769252868
    EP_GLOBAL Real64 const GravityConstant(9.807);
    EP_GLOBAL Real64 const DegToRadians(Pi / 180.0);           // Conversion for Degrees to Radians
    EP_GLOBAL Real64 const RadToDeg(180.0 / Pi);               // Conversion for Radians to Degrees
    EP_GLOBAL Real64 const SecInHour(3600.0);                  // Conversion for hours to seconds
    EP_GLOBAL Real64 const HoursInDay(24.0);                   // Number of Hours in Day
    EP_GLOBAL Real64 const SecsInDay(SecInHour *HoursInDay);   // Number of seconds in Day
    EP_GLOBAL Real64 const BigNumber(HUGE_(1.0));              // Max Number real used for initializations
    EP_GLOBAL Real64 const rTinyValue(EPSILON(1.0));           // Tiny value to replace use of TINY(x)
    EP_GLOBAL std::string::size_type const MaxNameLength(100); // Maximum Name Length in Characters -- should be the same
    // as MaxAlphaArgLength in InputProcessor module

    EP_GLOBAL Real64 const KelvinConv(273.15);       // Conversion factor for C to K and K to C
    EP_GLOBAL Real64 const InitConvTemp(5.05);       // [deg C], standard init vol to mass flow conversion temp
    EP_GLOBAL Real64 const AutoCalculate(-99999.0);  // automatically calculate some fields.
    EP_GLOBAL Real64 const CWInitConvTemp(5.05);     // [deg C], standard init chilled water vol to mass flow conversion temp
    EP_GLOBAL Real64 const HWInitConvTemp(60.0);     // [deg C], standard init hot water vol to mass flow conversion temp
    EP_GLOBAL Real64 const SteamInitConvTemp(100.0); // [deg C], standard init steam vol to mass flow conversion temp

    EP_GLOBAL Real64 const StefanBoltzmann(5.6697E-8);     // Stefan-Boltzmann constant in W/(m2*K4)
    EP_GLOBAL Real64 const UniversalGasConst(8314.462175); // (J/mol*K)

    EP_GLOBAL Real64 const convertJtoGJ(1.0E-9); // Conversion factor for J to GJ

    // Parameters for EMS Calling Points
    EP_GLOBAL int const emsCallFromZoneSizing(1);                           // Identity where EMS called from
    EP_GLOBAL int const emsCallFromSystemSizing(2);                         // Identity where EMS called from
    EP_GLOBAL int const emsCallFromBeginNewEvironment(3);                   // Identity where EMS called from
    EP_GLOBAL int const emsCallFromBeginNewEvironmentAfterWarmUp(4);        // Identity where EMS called from
    EP_GLOBAL int const emsCallFromBeginTimestepBeforePredictor(5);         // Identity where EMS called from
    EP_GLOBAL int const emsCallFromBeforeHVACManagers(6);                   // Identity where EMS called from
    EP_GLOBAL int const emsCallFromAfterHVACManagers(7);                    // Identity where EMS called from
    EP_GLOBAL int const emsCallFromHVACIterationLoop(8);                    // Identity where EMS called from
    EP_GLOBAL int const emsCallFromEndSystemTimestepBeforeHVACReporting(9); // Identity where EMS called from
    EP_GLOBAL int const emsCallFromEndSystemTimestepAfterHVACReporting(10); // Identity where EMS called from
    EP_GLOBAL int const emsCallFromEndZoneTimestepBeforeZoneReporting(11);  // Identity where EMS called from
    EP_GLOBAL int const emsCallFromEndZoneTimestepAfterZoneReporting(12);   // Identity where EMS called from
    EP_GLOBAL int const emsCallFromSetupSimulation(13);                     // identify where EMS called from,
    // this is for input processing only
    EP_GLOBAL int const emsCallFromExternalInterface(14);         // Identity where EMS called from
    EP_GLOBAL int const emsCallFromComponentGetInput(15);         // EMS called from end of get input for a component
    EP_GLOBAL int const emsCallFromUserDefinedComponentModel(16); // EMS called from inside a custom user component model
    EP_GLOBAL int const emsCallFromUnitarySystemSizing(17);       // EMS called from unitary system compound component
    EP_GLOBAL int const emsCallFromBeginZoneTimestepBeforeInitHeatBalance(18); // Identity where EMS called from
    EP_GLOBAL int const emsCallFromBeginZoneTimestepAfterInitHeatBalance(19); // Identity where EMS called from

    EP_GLOBAL int const ScheduleAlwaysOn(-1); // Value when passed to schedule routines gives back 1.0 (on)

    // DERIVED TYPE DEFINITIONS:
    // na

    // INTERFACE BLOCK SPECIFICATIONS:
    // see DataOmterfaces fpr global interface statements

    // MODULE VARIABLE DECLARATIONS:

    EP_GLOBAL bool BeginDayFlag(false);           // True at the start of each day, False after first time step in day
    EP_GLOBAL bool BeginEnvrnFlag(false);         // True at the start of each environment, False after first time step in environ
    EP_GLOBAL bool BeginHourFlag(false);          // True at the start of each hour, False after first time step in hour
    EP_GLOBAL bool BeginSimFlag(false);           // True until any actual simulation (full or sizing) has begun, False after first time step
    EP_GLOBAL bool BeginFullSimFlag(false);       // True until full simulation has begun, False after first time step
    EP_GLOBAL bool BeginTimeStepFlag(false);      // True at the start of each time step, False after first subtime step of time step
    EP_GLOBAL int DayOfSim(0);                    // Counter for days (during the simulation)
    EP_GLOBAL std::string DayOfSimChr("0");       // Counter for days (during the simulation) (character -- for reporting)
    EP_GLOBAL int CalendarYear(0);                // Calendar year of the current day of simulation
    EP_GLOBAL std::string CalendarYearChr;        // Calendar year of the current day of simulation (character -- for reporting)
    EP_GLOBAL bool EndEnvrnFlag(false);           // True at the end of each environment (last time step of last hour of last day of environ)
    EP_GLOBAL bool EndDesignDayEnvrnsFlag(false); // True at the end of the last design day environment
    // (last time step of last hour of last day of environ which is a design day)
    EP_GLOBAL bool EndDayFlag(false);            // True at the end of each day (last time step of last hour of day)
    EP_GLOBAL bool EndHourFlag(false);           // True at the end of each hour (last time step of hour)
    EP_GLOBAL int PreviousHour(0);               // Previous Hour Index
    EP_GLOBAL int HourOfDay(0);                  // Counter for hours in a simulation day
    EP_GLOBAL Real64 WeightPreviousHour(0.0);    // Weighting of value for previous hour
    EP_GLOBAL Real64 WeightNow(0.0);             // Weighting of value for current hour
    EP_GLOBAL int NumOfDayInEnvrn(0);            // Number of days in the simulation for a particular environment
    EP_GLOBAL int NumOfTimeStepInHour(0);        // Number of time steps in each hour of the simulation
    EP_GLOBAL int NumOfZones(0);                 // Total number of Zones for simulation
    EP_GLOBAL int TimeStep(0);                   // Counter for time steps (fractional hours)
    EP_GLOBAL Real64 TimeStepZone(0.0);          // Zone time step in fractional hours
    EP_GLOBAL bool WarmupFlag(false);            // True during the warmup portion of a simulation
    EP_GLOBAL int OutputFileStandard(0);         // Unit number for the standard output file (hourly data only)
    EP_GLOBAL std::ostream *eso_stream(nullptr); // Internal stream used for eso output (used for performance)
    EP_GLOBAL JsonOutputStreams jsonOutputStreams;
    EP_GLOBAL int OutputStandardError(0);                      // Unit number for the standard error output file
    EP_GLOBAL std::ostream *err_stream(nullptr);               // Internal stream used for err output (used for performance)
    EP_GLOBAL int StdOutputRecordCount(0);                     // Count of Standard output records
    EP_GLOBAL int OutputFileInits(0);                          // Unit number for the standard Initialization output file
    EP_GLOBAL std::ostream *eio_stream(nullptr);               // Internal stream used for eio output (used for unit tests)
    EP_GLOBAL int OutputFileDebug(0);                          // Unit number for debug outputs
    EP_GLOBAL int OutputFileZoneSizing(0);                     // Unit number of zone sizing calc output file
    EP_GLOBAL int OutputFileSysSizing(0);                      // Unit number of system sizing calc output file
    EP_GLOBAL int OutputFileMeters(0);                         // Unit number for meters output
    EP_GLOBAL std::ostream *mtr_stream(nullptr);               // Internal stream used for mtr output (used for performance)
    EP_GLOBAL int OutputFileShadingFrac(0);                    // Unit number for shading output
    EP_GLOBAL int StdMeterRecordCount(0);                      // Count of Meter output records
    EP_GLOBAL int OutputFileBNDetails(0);                      // Unit number for Branch-Node Details
    EP_GLOBAL int OutputDElightIn(0);                          // Unit number for the DElight In file
    EP_GLOBAL std::ostream *delightin_stream(nullptr);         // Internal stream used for DElight In file
    EP_GLOBAL bool ZoneSizingCalc(false);                      // TRUE if zone sizing calculation
    EP_GLOBAL bool SysSizingCalc(false);                       // TRUE if system sizing calculation
    EP_GLOBAL bool DoZoneSizing(false);                        // User input in SimulationControl object
    EP_GLOBAL bool DoSystemSizing(false);                      // User input in SimulationControl object
    EP_GLOBAL bool DoPlantSizing(false);                       // User input in SimulationControl object
    EP_GLOBAL bool DoDesDaySim(false);                         // User input in SimulationControl object
    EP_GLOBAL bool DoWeathSim(false);                          // User input in SimulationControl object
    EP_GLOBAL bool DoHVACSizingSimulation(false);              // User input in SimulationControl object
    EP_GLOBAL int HVACSizingSimMaxIterations(0);               // User input in SimulationControl object
    EP_GLOBAL bool WeathSimReq(false);                         // Input has a RunPeriod request
    EP_GLOBAL int KindOfSim(0);                                // See parameters. (ksDesignDay, ksRunPeriodDesign, ksRunPeriodWeather)
    EP_GLOBAL bool DoOutputReporting(false);                   // TRUE if variables to be written out
    EP_GLOBAL bool DoingSizing(false);                         // TRUE when "sizing" is being performed (some error messages won't be displayed)
    EP_GLOBAL bool DoingHVACSizingSimulations(false);          // true when HVAC Sizing Simulations are being performed.
    EP_GLOBAL bool DoingInputProcessing(false);                // TRUE when "IP" is being performed (some error messages are cached)
    EP_GLOBAL bool DisplayAllWarnings(false);                  // True when selection for  "DisplayAllWarnings" is entered (turns on other warning flags)
    EP_GLOBAL bool DisplayExtraWarnings(false);                // True when selection for  "DisplayExtraWarnings" is entered
    EP_GLOBAL bool DisplayUnusedObjects(false);                // True when selection for  "DisplayUnusedObjects" is entered
    EP_GLOBAL bool DisplayUnusedSchedules(false);              // True when selection for  "DisplayUnusedSchedules" is entered
    EP_GLOBAL bool DisplayAdvancedReportVariables(false);      // True when selection for  "DisplayAdvancedReportVariables" is entered
    EP_GLOBAL bool DisplayZoneAirHeatBalanceOffBalance(false); // True when selection for  "DisplayZoneAirHeatBalanceOffBalance" is entered
    EP_GLOBAL bool DisplayInputInAudit(false);                 // True when environmental variable "DisplayInputInAudit" is used
    EP_GLOBAL bool CreateMinimalSurfaceVariables(false);       // True when selection for  "CreateMinimalSurfaceVariables" is entered
    EP_GLOBAL Real64 CurrentTime(0.0);                         // CurrentTime, in fractional hours, from start of day. Uses Loads time step.
    EP_GLOBAL int SimTimeSteps(0);                             // Number of (Loads) timesteps since beginning of run period (environment).
    EP_GLOBAL int MinutesPerTimeStep(0);                       // Minutes per time step calculated from NumTimeStepInHour (number of minutes per load time step)
    EP_GLOBAL Real64 TimeStepZoneSec(0.0);                     // Seconds per time step
    EP_GLOBAL bool MetersHaveBeenInitialized(false);
    EP_GLOBAL bool KickOffSimulation(false);                 // Kick off simulation -- meaning run each environment for 1 or 2 time steps.
    EP_GLOBAL bool KickOffSizing(false);                     // Kick off sizing -- meaning run each environment for 1 or 2 time steps.
    EP_GLOBAL bool RedoSizesHVACSimulation(false);           // doing kick off simulation for redoing sizes as part of sizing
    EP_GLOBAL bool FinalSizingHVACSizingSimIteration(false); // when doing HVAC sizing Simulation
    EP_GLOBAL bool AnyEnergyManagementSystemInModel(false);  // true if there is any EMS or Erl in model.  otherwise false
    EP_GLOBAL bool AnyLocalEnvironmentsInModel(false);       // true if there is any local environmental data objected defined in model, otherwise false
    EP_GLOBAL bool AnyPlantInModel(false);                   // true if there are any plant or condenser loops in model, otherwise false
    EP_GLOBAL int CacheIPErrorFile(0);                       // Cache IP errors until IDF processing done.
    EP_GLOBAL bool AnyIdealCondEntSetPointInModel(false);    // true if there is any ideal condenser entering set point manager in model.
    EP_GLOBAL bool RunOptCondEntTemp(false);                 // true if the ideal condenser entering set point optimization is running
    EP_GLOBAL bool CompLoadReportIsReq(false);               // true if the extra sizing calcs are performed to create a "pulse" for the load component report
    EP_GLOBAL bool isPulseZoneSizing(false);                 // true during the set of zone sizing calcs that include the "pulse" for the load component report
    EP_GLOBAL int OutputFileZonePulse(0); // file handle for special zone sizing report that contains the result of the "pulse" for the load component report
    EP_GLOBAL bool doLoadComponentPulseNow(false); // true for the time step that is the "pulse" for the load component report
    EP_GLOBAL bool ShowDecayCurvesInEIO(false);    // true if the Radiant to Convective Decay Curves should appear in the EIO file
    EP_GLOBAL bool AnySlabsInModel(false);         // true if there are any zone-coupled ground domains in the input file
    EP_GLOBAL bool AnyBasementsInModel(false);     // true if there are any basements in the input file

    EP_GLOBAL int Progress(0); // current progress (0-100)
    EP_GLOBAL void (*fProgressPtr)(int const);
    EP_GLOBAL void (*fMessagePtr)(std::string const &);

    // Clears the global data in DataGlobals.
    // Needed for unit tests, should not be normally called.
    void clear_state()
    {
        runReadVars = false;
        DDOnlySimulation = false;
        AnnualSimulation = false;
        outputEpJSONConversion = false;
        isEpJSON = false;
        isCBOR = false;
        isMsgPack = false;
        preserveIDFOrder = true;
        BeginDayFlag = false;
        BeginEnvrnFlag = false;
        BeginHourFlag = false;
        BeginSimFlag = false;
        BeginFullSimFlag = false;
        BeginTimeStepFlag = false;
        DayOfSim = 0;
        DayOfSimChr = "0";
        CalendarYear = 0;
        CalendarYearChr = "0";
        EndEnvrnFlag = false;
        EndDesignDayEnvrnsFlag = false;
        EndDayFlag = false;
        EndHourFlag = false;
        PreviousHour = 0;
        HourOfDay = 0;
        WeightPreviousHour = 0.0;
        WeightNow = 0.0;
        NumOfDayInEnvrn = 0;
        NumOfTimeStepInHour = 0;
        NumOfZones = 0;
        TimeStep = 0;
        TimeStepZone = 0.0;
        WarmupFlag = false;
        OutputFileStandard = 0;
        OutputStandardError = 0;
        StdOutputRecordCount = 0;
        OutputFileInits = 0;
        OutputFileDebug = 0;
        OutputFileZoneSizing = 0;
        OutputFileSysSizing = 0;
        OutputFileMeters = 0;
        OutputFileShadingFrac = 0;
        StdMeterRecordCount = 0;
        OutputFileBNDetails = 0;
        ZoneSizingCalc = false;
        SysSizingCalc = false;
        DoZoneSizing = false;
        DoSystemSizing = false;
        DoPlantSizing = false;
        DoDesDaySim = false;
        DoWeathSim = false;
        DoHVACSizingSimulation = false;
        HVACSizingSimMaxIterations = 0;
        WeathSimReq = false;
        KindOfSim = 0;
        DoOutputReporting = false;
        DoingSizing = false;
        DoingHVACSizingSimulations = false;
        DoingInputProcessing = false;
        DisplayAllWarnings = false;
        DisplayExtraWarnings = false;
        DisplayUnusedObjects = false;
        DisplayUnusedSchedules = false;
        DisplayAdvancedReportVariables = false;
        DisplayZoneAirHeatBalanceOffBalance = false;
        DisplayInputInAudit = false;
        CreateMinimalSurfaceVariables = false;
        CurrentTime = 0.0;
        SimTimeSteps = 0;
        MinutesPerTimeStep = 0;
        TimeStepZoneSec = 0.0;
        MetersHaveBeenInitialized = false;
        KickOffSimulation = false;
        KickOffSizing = false;
        RedoSizesHVACSimulation = false;
        FinalSizingHVACSizingSimIteration = false;
        AnyEnergyManagementSystemInModel = false;
        AnyLocalEnvironmentsInModel = false;
        AnyPlantInModel = false;
        CacheIPErrorFile = 0;
        AnyIdealCondEntSetPointInModel = false;
        RunOptCondEntTemp = false;
        CompLoadReportIsReq = false;
        isPulseZoneSizing = false;
        OutputFileZonePulse = 0;
        doLoadComponentPulseNow = false;
        ShowDecayCurvesInEIO = false;
        AnySlabsInModel = false;
        AnyBasementsInModel = false;
        Progress = 0;
        eso_stream = nullptr;
        mtr_stream = nullptr;
        err_stream = nullptr;
        eio_stream = nullptr;
        delightin_stream = nullptr;
    }

} // namespace DataGlobals

} // namespace EnergyPlus
