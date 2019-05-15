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

// C++ Headers
#include <cmath>

// EnergyPlus Headers
#include <DataEnvironment.hh>
#include <DataGlobals.hh>
#include <DataPrecisionGlobals.hh>
#include <General.hh>
#include <UtilityRoutines.hh>

namespace EnergyPlus {

namespace DataEnvironment {

    // MODULE INFORMATION:
    //       AUTHOR         Rick Strand, Dan Fisher, Linda Lawrie
    //       DATE WRITTEN   December 1997
    //       MODIFIED       November 1998, Fred Winkelmann
    //       MODIFIED       June 1999,June 2000, Linda Lawrie
    //       RE-ENGINEERED  na

    // PURPOSE OF THIS MODULE:
    // This data-only module is a repository for the variables that relate specifically
    // to the "environment" (i.e. current date data, tomorrow's date data, and
    // current weather variables)

    // METHODOLOGY EMPLOYED:
    // na

    // REFERENCES:
    // na

    // OTHER NOTES:
    // na

    // Using/Aliasing
    using namespace DataPrecisionGlobals;
    using DataGlobals::KelvinConv;

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    // MODULE PARAMETER DEFINITIONS:
    thread_local Real64 const EarthRadius(6356000.0);          // Radius of the Earth (m)
    thread_local Real64 const AtmosphericTempGradient(0.0065); // Standard atmospheric air temperature gradient (K/m)
    thread_local Real64 const SunIsUpValue(0.00001);           // if Cos Zenith Angle of the sun is >= this value, the sun is "up"
    thread_local Real64 const StdPressureSeaLevel(101325.0);   // Standard barometric pressure at sea level (Pa)

    // DERIVED TYPE DEFINITIONS:
    // na

    // INTERFACE BLOCK SPECIFICATIONS:
    // na

    // MODULE VARIABLE DECLARATIONS:
    thread_local Real64 BeamSolarRad;                   // Current beam normal solar irradiance
    thread_local bool EMSBeamSolarRadOverrideOn(false); // EMS flag for beam normal solar irradiance
    thread_local Real64 EMSBeamSolarRadOverrideValue;   // EMS override value for beam normal solar irradiance
    thread_local int DayOfMonth;                        // Current day of the month
    thread_local int DayOfMonthTomorrow;                // Tomorrow's day of the month
    thread_local int DayOfWeek;                         // Current day of the week (Sunday=1, Monday=2, ...)
    thread_local int DayOfWeekTomorrow;                 // Tomorrow's day of the week (Sunday=1, Monday=2, ...)
    thread_local int DayOfYear;                         // Current day of the year (01JAN=1, 02JAN=2, ...)
    thread_local int DayOfYear_Schedule;                // Schedule manager always assumes leap years...
    thread_local Real64 DifSolarRad;                    // Current sky diffuse solar horizontal irradiance
    thread_local bool EMSDifSolarRadOverrideOn(false);  // EMS flag for sky diffuse solar horizontal irradiance
    thread_local Real64 EMSDifSolarRadOverrideValue;    // EMS override value for sky diffuse solar horizontal irradiance
    thread_local int DSTIndicator;                      // Daylight Saving Time Indicator (1=yes, 0=no) for Today
    thread_local Real64 Elevation;                      // Elevation of this building site
    thread_local bool EndMonthFlag;                     // Set to true on last day of month
    thread_local bool EndYearFlag;                      // Set to true on the last day of year
    thread_local Real64 GndReflectanceForDayltg;        // Ground visible reflectance for use in daylighting calc
    thread_local Real64 GndReflectance;                 // Ground visible reflectance from input
    thread_local Real64 GndSolarRad;                    // Current ground reflected radiation
    thread_local Real64 GroundTemp;                     // Current ground temperature {C}
    thread_local Real64 GroundTempKelvin;               // Current ground temperature {K}
    thread_local Real64 GroundTempFC;                   // Current ground temperature defined for F or C factor method {C}
    thread_local Real64 GroundTemp_Surface;             // Current surface ground temperature {C}
    thread_local Real64 GroundTemp_Deep;                // Current deep ground temperature
    thread_local int HolidayIndex;                      // Indicates whether current day is a holiday and if so what type
    // HolidayIndex=(0-no holiday, 1-holiday type 1, ...)
    thread_local int HolidayIndexTomorrow;                 // Tomorrow's Holiday Index
    thread_local bool IsRain;                              // Surfaces are wet for this time interval
    thread_local bool IsSnow;                              // Snow on the ground for this time interval
    thread_local Real64 Latitude;                          // Latitude of building location
    thread_local Real64 Longitude;                         // Longitude of building location
    thread_local int Month;                                // Current calendar month
    thread_local int MonthTomorrow;                        // Tomorrow's calendar month
    thread_local Real64 OutBaroPress;                      // Current outdoor air barometric pressure
    thread_local Real64 OutDryBulbTemp;                    // Current outdoor air dry bulb temperature
    thread_local bool EMSOutDryBulbOverrideOn(false);      // EMS flag for outdoor air dry bulb temperature
    thread_local Real64 EMSOutDryBulbOverrideValue;        // EMS override value for outdoor air dry bulb temperature
    thread_local Real64 OutHumRat;                         // Current outdoor air humidity ratio
    thread_local Real64 OutRelHum;                         // Current outdoor relative humidity [%]
    thread_local Real64 OutRelHumValue;                    // Current outdoor relative humidity value [0.0-1.0]
    thread_local bool EMSOutRelHumOverrideOn(false);       // EMS flag for outdoor relative humidity value
    thread_local Real64 EMSOutRelHumOverrideValue;         // EMS override value for outdoor relative humidity value
    thread_local Real64 OutEnthalpy;                       // Current outdoor enthalpy
    thread_local Real64 OutAirDensity;                     // Current outdoor air density
    thread_local Real64 OutWetBulbTemp;                    // Current outdoor air wet bulb temperature
    thread_local Real64 OutDewPointTemp;                   // Current outdoor dewpoint temperature
    thread_local bool EMSOutDewPointTempOverrideOn(false); // EMS flag for outdoor dewpoint temperature
    thread_local Real64 EMSOutDewPointTempOverrideValue;   // EMS override value for outdoor dewpoint temperature
    thread_local Real64 SkyTemp;                           // Current sky temperature {C}
    thread_local Real64 SkyTempKelvin;                     // Current sky temperature {K}
    thread_local Real64 LiquidPrecipitation;               // Current liquid precipitation amount (rain) {m}
    thread_local bool SunIsUp;                             // True when Sun is over horizon, False when not
    thread_local Real64 WindDir;                           // Current outdoor air wind direction
    thread_local bool EMSWindDirOverrideOn(false);         // EMS flag for outdoor air wind direction
    thread_local Real64 EMSWindDirOverrideValue;           // EMS override value for outdoor air wind direction
    thread_local Real64 WindSpeed;                         // Current outdoor air wind speed
    thread_local bool EMSWindSpeedOverrideOn(false);       // EMS flag for outdoor air wind speed
    thread_local Real64 EMSWindSpeedOverrideValue;         // EMS override value for outdoor air wind speed
    thread_local Real64 WaterMainsTemp;                    // Current water mains temperature
    thread_local int Year;                                 // Current calendar year of the simulation from the weather file
    thread_local int YearTomorrow;                         // Tomorrow's calendar year of the simulation
    thread_local Array1D<Real64> SOLCOS(3);                // Solar direction cosines at current time step
    thread_local Real64 CloudFraction;                     // Fraction of sky covered by clouds
    thread_local Real64 HISKF;                             // Exterior horizontal illuminance from sky (lux).
    thread_local Real64 HISUNF;                            // Exterior horizontal beam illuminance (lux)
    thread_local Real64 HISUNFnorm;                        // Exterior beam normal illuminance (lux)
    thread_local Real64 PDIRLW;                            // Luminous efficacy (lum/W) of beam solar radiation
    thread_local Real64 PDIFLW;                            // Luminous efficacy (lum/W) of sky diffuse solar radiation
    thread_local Real64 SkyClearness;                      // Sky clearness (see subr. DayltgLuminousEfficacy)
    thread_local Real64 SkyBrightness;                     // Sky brightness (see subr. DayltgLuminousEfficacy)
    thread_local Real64 StdBaroPress(StdPressureSeaLevel); // Standard "atmospheric pressure" based on elevation (ASHRAE HOF p6.1)
    thread_local Real64 StdRhoAir;                         // Standard "rho air" set in WeatherManager - based on StdBaroPress
    thread_local Real64 rhoAirSTP;                         // Standard density of dry air at 101325 Pa, 20.0C temperaure
    thread_local Real64 TimeZoneNumber;                    // Time Zone Number of building location
    thread_local Real64 TimeZoneMeridian;                  // Standard Meridian of TimeZone
    thread_local std::string EnvironmentName;              // Current environment name (longer for weather file names)
    thread_local std::string WeatherFileLocationTitle;     // Location Title from Weather File
    thread_local std::string CurMnDyHr;                    // Current Month/Day/Hour timestamp info
    thread_local std::string CurMnDy;                      // Current Month/Day timestamp info
    thread_local std::string CurMnDyYr;                    // Current Month/Day/Year timestamp info
    thread_local int CurEnvirNum;                          // current environment number
    thread_local int TotDesDays(0);                        // Total number of Design days to Setup
    thread_local int TotRunDesPersDays(0);                 // Total number of Run Design Periods [Days] (Weather data) to Setup
    thread_local int CurrentOverallSimDay;                 // Count of current simulation day in total of all sim days
    thread_local int TotalOverallSimDays;                  // Count of all possible simulation days in all environments
    thread_local int MaxNumberSimYears;                    // Maximum number of simulation years requested in all RunPeriod statements
    thread_local int RunPeriodStartDayOfWeek;              // Day of week of the first day of the run period. (or design day - day of week)

    thread_local Real64 CosSolarDeclinAngle; // Cosine of the solar declination angle
    thread_local Real64 EquationOfTime;      // Value of the equation of time formula
    thread_local Real64 SinLatitude;         // Sine of Latitude
    thread_local Real64 CosLatitude;         // Cosine of Latitude
    thread_local Real64 SinSolarDeclinAngle; // Sine of the solar declination angle
    thread_local Real64 TS1TimeOffset(-0.5); // offset when TS=1 for solar calculations

    thread_local Real64 WeatherFileWindModCoeff(1.5863); // =(WindBLHeight/WindSensorHeight)**WindExp for conditions at the weather station
    thread_local Real64 WeatherFileTempModCoeff(0.0);    // =AtmosphericTempGradient*EarthRadius*SensorHeight/(EarthRadius+SensorHeight)

    thread_local Real64 SiteWindExp(0.22);        // Exponent for the wind velocity profile at the site
    thread_local Real64 SiteWindBLHeight(370.0);  // Boundary layer height for the wind velocity profile at the site (m)
    thread_local Real64 SiteTempGradient(0.0065); // Air temperature gradient coefficient (K/m)

    thread_local bool GroundTempObjInput(false);         // Ground temperature object input
    thread_local bool GroundTemp_SurfaceObjInput(false); // Surface ground temperature object input
    thread_local bool GroundTemp_DeepObjInput(false);    // Deep ground temperature object input
    thread_local bool FCGroundTemps(false);
    thread_local bool DisplayWeatherMissingDataWarnings(false); // Display missing/out of range weather warnings
    thread_local bool IgnoreSolarRadiation(false);              // TRUE if all solar radiation is to be ignored
    thread_local bool IgnoreBeamRadiation(false);               // TRUE if beam (aka direct normal) radiation is to be ignored
    thread_local bool IgnoreDiffuseRadiation(false);            // TRUE if diffuse horizontal radiation is to be ignored

    thread_local bool PrintEnvrnStampWarmup(false);
    thread_local bool PrintEnvrnStampWarmupPrinted(false);

    thread_local bool RunPeriodEnvironment(false);  // True if Run Period, False if DesignDay
    thread_local std::string EnvironmentStartEnd;   // Start/End dates for Environment
    thread_local bool CurrentYearIsLeapYear(false); // true when current year is leap year (convoluted logic dealing with
    // whether weather file allows leap years, runperiod inputs.

    thread_local int varyingLocationSchedIndexLat(0);
    thread_local int varyingLocationSchedIndexLong(0);
    thread_local int varyingOrientationSchedIndex(0);

    // SUBROUTINE SPECIFICATIONS FOR MODULE DataEnvironment:
    // PUBLIC OutBaroPressAt
    // PUBLIC OutAirDensityAt

    // Functions

    // Clears the global data in DataEnvironment.
    // Needed for unit tests, should not be normally called.
    void clear_state()
    {
        BeamSolarRad = Real64();
        EMSBeamSolarRadOverrideOn = false;
        EMSBeamSolarRadOverrideValue = Real64();
        DayOfMonth = int();
        DayOfMonthTomorrow = int();
        DayOfWeek = int();
        DayOfWeekTomorrow = int();
        DayOfYear = int();
        DayOfYear_Schedule = int();
        DifSolarRad = Real64();
        EMSDifSolarRadOverrideOn = false;
        EMSDifSolarRadOverrideValue = Real64();
        DSTIndicator = int();
        Elevation = Real64();
        EndMonthFlag = bool();
        GndReflectanceForDayltg = Real64();
        GndReflectance = Real64();
        GndSolarRad = Real64();
        GroundTemp = Real64();
        GroundTempKelvin = Real64();
        GroundTempFC = Real64();
        GroundTemp_Surface = Real64();
        GroundTemp_Deep = Real64();
        HolidayIndex = int();
        HolidayIndexTomorrow = int();
        IsRain = bool();
        IsSnow = bool();
        Latitude = Real64();
        Longitude = Real64();
        Month = int();
        MonthTomorrow = int();
        OutBaroPress = Real64();
        OutDryBulbTemp = Real64();
        EMSOutDryBulbOverrideOn = false;
        EMSOutDryBulbOverrideValue = Real64();
        OutHumRat = Real64();
        OutRelHum = Real64();
        OutRelHumValue = Real64();
        EMSOutRelHumOverrideOn = false;
        EMSOutRelHumOverrideValue = Real64();
        OutEnthalpy = Real64();
        OutAirDensity = Real64();
        OutWetBulbTemp = Real64();
        OutDewPointTemp = Real64();
        EMSOutDewPointTempOverrideOn = false;
        EMSOutDewPointTempOverrideValue = Real64();
        SkyTemp = Real64();
        SkyTempKelvin = Real64();
        LiquidPrecipitation = Real64();
        SunIsUp = bool();
        WindDir = Real64();
        EMSWindDirOverrideOn = false;
        EMSWindDirOverrideValue = Real64();
        WindSpeed = Real64();
        EMSWindSpeedOverrideOn = false;
        EMSWindSpeedOverrideValue = Real64();
        WaterMainsTemp = Real64();
        Year = int();
        YearTomorrow = int();
        SOLCOS.dimension(3);
        CloudFraction = Real64();
        HISKF = Real64();
        HISUNF = Real64();
        HISUNFnorm = Real64();
        PDIRLW = Real64();
        PDIFLW = Real64();
        SkyClearness = Real64();
        SkyBrightness = Real64();
        StdBaroPress = 101325.0;
        StdRhoAir = Real64();
        TimeZoneNumber = Real64();
        TimeZoneMeridian = Real64();
        EnvironmentName = std::string();
        WeatherFileLocationTitle = std::string();
        CurMnDyHr = std::string();
        CurMnDy = std::string();
        CurMnDyYr = std::string();
        CurEnvirNum = int();
        TotDesDays = 0;
        TotRunDesPersDays = 0;
        CurrentOverallSimDay = int();
        TotalOverallSimDays = int();
        MaxNumberSimYears = int();
        RunPeriodStartDayOfWeek = int();
        CosSolarDeclinAngle = Real64();
        EquationOfTime = Real64();
        SinLatitude = Real64();
        CosLatitude = Real64();
        SinSolarDeclinAngle = Real64();
        TS1TimeOffset = -0.5;
        WeatherFileWindModCoeff = 1.5863;
        WeatherFileTempModCoeff = 0.0;
        SiteWindExp = 0.22;
        SiteWindBLHeight = 370.0;
        SiteTempGradient = 0.0065;
        GroundTempObjInput = false;
        GroundTemp_SurfaceObjInput = false;
        GroundTemp_DeepObjInput = false;
        FCGroundTemps = false;
        DisplayWeatherMissingDataWarnings = false;
        IgnoreSolarRadiation = false;
        IgnoreBeamRadiation = false;
        IgnoreDiffuseRadiation = false;
        PrintEnvrnStampWarmup = false;
        PrintEnvrnStampWarmupPrinted = false;
        RunPeriodEnvironment = false;
        EnvironmentStartEnd = std::string();
        CurrentYearIsLeapYear = false;
        varyingLocationSchedIndexLat = 0;
        varyingLocationSchedIndexLong = 0;
        varyingOrientationSchedIndex = 0;
    }

    Real64 OutDryBulbTempAt(Real64 const Z) // Height above ground (m)
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Peter Graham Ellis
        //       DATE WRITTEN   January 2006
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // Calculates outdoor dry bulb temperature at a given altitude.

        // METHODOLOGY EMPLOYED:
        // 1976 U.S. Standard Atmosphere.

        // REFERENCES:
        // 1976 U.S. Standard Atmosphere. 1976. U.S. Government Printing Office, Washington, D.C.

        // Using/Aliasing
        using General::RoundSigDigits;

        // Return value
        Real64 LocalOutDryBulbTemp; // Return result for function (C)

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        Real64 BaseTemp; // Base temperature at Z = 0 (C)

        BaseTemp = OutDryBulbTemp + WeatherFileTempModCoeff;

        if (SiteTempGradient == 0.0) {
            LocalOutDryBulbTemp = OutDryBulbTemp;
        } else if (Z <= 0.0) {
            LocalOutDryBulbTemp = BaseTemp;
        } else {
            LocalOutDryBulbTemp = BaseTemp - SiteTempGradient * EarthRadius * Z / (EarthRadius + Z);
        }

        if (LocalOutDryBulbTemp < -100.0) {
            ShowSevereError("OutDryBulbTempAt: outdoor drybulb temperature < -100 C");
            ShowContinueError("...check heights, this height=[" + RoundSigDigits(Z, 0) + "].");
            ShowFatalError("Program terminates due to preceding condition(s).");
        }

        return LocalOutDryBulbTemp;
    }

    Real64 OutWetBulbTempAt(Real64 const Z) // Height above ground (m)
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Peter Graham Ellis
        //       DATE WRITTEN   January 2006
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // Calculates outdoor wet bulb temperature at a given altitude.

        // METHODOLOGY EMPLOYED:
        // 1976 U.S. Standard Atmosphere.

        // REFERENCES:
        // 1976 U.S. Standard Atmosphere. 1976. U.S. Government Printing Office, Washington, D.C.

        // Using/Aliasing
        using General::RoundSigDigits;

        // Return value
        Real64 LocalOutWetBulbTemp; // Return result for function (C)

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        Real64 BaseTemp; // Base temperature at Z = 0 (C)

        BaseTemp = OutWetBulbTemp + WeatherFileTempModCoeff;

        if (SiteTempGradient == 0.0) {
            LocalOutWetBulbTemp = OutWetBulbTemp;
        } else if (Z <= 0.0) {
            LocalOutWetBulbTemp = BaseTemp;
        } else {
            LocalOutWetBulbTemp = BaseTemp - SiteTempGradient * EarthRadius * Z / (EarthRadius + Z);
        }

        if (LocalOutWetBulbTemp < -100.0) {
            ShowSevereError("OutWetBulbTempAt: outdoor wetbulb temperature < -100 C");
            ShowContinueError("...check heights, this height=[" + RoundSigDigits(Z, 0) + "].");
            ShowFatalError("Program terminates due to preceding condition(s).");
        }

        return LocalOutWetBulbTemp;
    }

    Real64 OutDewPointTempAt(Real64 const Z) // Height above ground (m)
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Linda Lawrie
        //       DATE WRITTEN   March 2007
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // Calculates outdoor dew point temperature at a given altitude.

        // METHODOLOGY EMPLOYED:
        // 1976 U.S. Standard Atmosphere.
        // copied from outwetbulbtempat

        // REFERENCES:
        // 1976 U.S. Standard Atmosphere. 1976. U.S. Government Printing Office, Washington, D.C.

        // Using/Aliasing
        using General::RoundSigDigits;

        // Return value
        Real64 LocalOutDewPointTemp; // Return result for function (C)

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        Real64 BaseTemp; // Base temperature at Z = 0 (C)

        BaseTemp = OutDewPointTemp + WeatherFileTempModCoeff;

        if (SiteTempGradient == 0.0) {
            LocalOutDewPointTemp = OutDewPointTemp;
        } else if (Z <= 0.0) {
            LocalOutDewPointTemp = BaseTemp;
        } else {
            LocalOutDewPointTemp = BaseTemp - SiteTempGradient * EarthRadius * Z / (EarthRadius + Z);
        }

        if (LocalOutDewPointTemp < -100.0) {
            ShowSevereError("OutDewPointTempAt: outdoor dewpoint temperature < -100 C");
            ShowContinueError("...check heights, this height=[" + RoundSigDigits(Z, 0) + "].");
            ShowFatalError("Program terminates due to preceding condition(s).");
        }

        return LocalOutDewPointTemp;
    }

    Real64 WindSpeedAt(Real64 const Z) // Height above ground (m)
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Peter Graham Ellis
        //       DATE WRITTEN   January 2006
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // Calculates local wind speed at a given altitude.

        // METHODOLOGY EMPLOYED:
        // 2005 ASHRAE Fundamentals, Chapter 16, Equation 4.  (Different depending on terrain).

        // REFERENCES:
        // 2005 ASHRAE Fundamentals, Chapter 16, Equation 4.  (Different depending on terrain).
        // Terrain variables are set in HeatBalanceManager or entered by the user.

        // Return value
        Real64 LocalWindSpeed; // Return result for function (m/s)

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        if (Z <= 0.0) {
            LocalWindSpeed = 0.0;
        } else if (SiteWindExp == 0.0) {
            LocalWindSpeed = WindSpeed;
        } else {
            //  [Met] - at meterological Station, Height of measurement is usually 10m above ground
            //  LocalWindSpeed = Windspeed [Met] * (Wind Boundary LayerThickness [Met]/Height [Met])**Wind Exponent[Met] &
            //                     * (Height above ground / Site Wind Boundary Layer Thickness) ** Site Wind Exponent
            LocalWindSpeed = WindSpeed * WeatherFileWindModCoeff * std::pow(Z / SiteWindBLHeight, SiteWindExp);
        }

        return LocalWindSpeed;
    }

    Real64 OutBaroPressAt(Real64 const Z) // Height above ground (m)
    {

        // FUNCTION INFORMATION:
        //       AUTHOR         Daeho Kang
        //       DATE WRITTEN   August 2009
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS FUNCTION:
        // Calculates local air barometric pressure at a given altitude.

        // METHODOLOGY EMPLOYED:
        // U.S. Standard Atmosphere1976, Part 1, Chapter 1.3, Equation 33b.

        // REFERENCES:
        // U.S. Standard Atmosphere1976, Part 1, Chapter 1.3, Equation 33b.

        // Return value
        Real64 LocalAirPressure; // Return result for function (Pa)

        // Locals
        // FUNCTION ARGUMENT DEFINITIONS:

        // FNCTION PARAMETER DEFINITIONS:
        Real64 const StdGravity(9.80665);    // The acceleration of gravity at the sea level (m/s2)
        Real64 const AirMolarMass(0.028964); // Molar mass of Earth's air (kg/mol)
        Real64 const GasConstant(8.31432);   // Molar gas constant (J/Mol-K)
        Real64 const TempGradient(-0.0065);  // Molecular-scale temperature gradient (K/m)
        Real64 const GeopotentialH(0.0);     // Geopotential height (zero within 11km from the sea level) (m)

        // FUNCTION LOCAL VARIABLE DECLARATIONS:
        Real64 BaseTemp; // Base temperature at Z

        BaseTemp = OutDryBulbTempAt(Z) + KelvinConv;

        if (Z <= 0.0) {
            LocalAirPressure = 0.0;
        } else if (SiteTempGradient == 0.0) {
            LocalAirPressure = OutBaroPress;
        } else {
            LocalAirPressure = StdBaroPress * std::pow(BaseTemp / (BaseTemp + TempGradient * (Z - GeopotentialH)),
                                                       (StdGravity * AirMolarMass) / (GasConstant * TempGradient));
        }

        return LocalAirPressure;
    }

    void SetOutBulbTempAt_error(std::string const &Settings, Real64 const max_height, std::string const &SettingsName)
    {
        // Using/Aliasing
        using General::RoundSigDigits;

        ShowSevereError("SetOutBulbTempAt: " + Settings + " Outdoor Temperatures < -100 C");
        ShowContinueError("...check " + Settings + " Heights - Maximum " + Settings + " Height=[" + RoundSigDigits(max_height, 0) + "].");
        if (max_height >= 20000.0) {
            ShowContinueError("...according to your maximum Z height, your building is somewhere in the Stratosphere.");
            ShowContinueError("...look at " + Settings + " Name= " + SettingsName);
        }
        ShowFatalError("Program terminates due to preceding condition(s).");
    }

    void SetWindSpeedAt(int const NumItems, Array1S<Real64> const Heights, Array1S<Real64> LocalWindSpeed, std::string const &EP_UNUSED(Settings))
    {

        // SUBROUTINE INFORMATION:
        //       AUTHOR         Linda Lawrie
        //       DATE WRITTEN   June 2013
        //       MODIFIED       na
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        // Routine provides facility for doing bulk Set Windspeed at Height.

        // METHODOLOGY EMPLOYED:
        // na

        // REFERENCES:
        // na

        // Using/Aliasing

        // Argument array dimensioning

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:

        if (SiteWindExp == 0.0) {
            LocalWindSpeed = WindSpeed;
        } else {
            Real64 const fac(WindSpeed * WeatherFileWindModCoeff * std::pow(SiteWindBLHeight, -SiteWindExp));
            Real64 Z; // Centroid value
            for (int i = 1; i <= NumItems; ++i) {
                Z = Heights(i);
                if (Z <= 0.0) {
                    LocalWindSpeed(i) = 0.0;
                } else {
                    //  [Met] - at meterological Station, Height of measurement is usually 10m above ground
                    //  LocalWindSpeed = Windspeed [Met] * (Wind Boundary LayerThickness [Met]/Height [Met])**Wind Exponent[Met] &
                    //                     * (Height above ground / Site Wind Boundary Layer Thickness) ** Site Wind Exponent
                    LocalWindSpeed(i) = fac * std::pow(Z, SiteWindExp);
                }
            }
        }
    }

} // namespace DataEnvironment

} // namespace EnergyPlus
