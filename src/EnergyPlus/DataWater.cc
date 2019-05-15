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

// EnergyPlus Headers
#include <DataPrecisionGlobals.hh>
#include <DataWater.hh>

namespace EnergyPlus {

namespace DataWater {

    // Module containing the routines dealing with the DataWater

    // MODULE INFORMATION:
    //       AUTHOR         B. Griffith
    //       DATE WRITTEN   August 2006
    //       MODIFIED       D. Sailor -- to add ecoroof irrigation
    //       RE-ENGINEERED  na

    // PURPOSE OF THIS MODULE:
    // This data-only module is a repository for the variables that relate specifically
    // to the management of water in the simulation

    // METHODOLOGY EMPLOYED:
    // <description>

    // REFERENCES:
    // na

    // OTHER NOTES:
    // na

    // Using/Aliasing
    using namespace DataPrecisionGlobals;

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLI

    // MODULE PARAMETER DEFINITION

    thread_local int const ScheduledTankTemp(101);      // tank water temperature is user input via schedule
    thread_local int const TankZoneThermalCoupled(102); // tank water temperature is modeled using simple UA

    thread_local int const RainSchedDesign(201); // mode of Rainfall determination is Scheduled Design
    thread_local int const IrrSchedDesign(202);  // mode of Irrigation determination is Scheduled Design (DJS -PSU)
    thread_local int const IrrSmartSched(203);   // mode of irrigation DJS - PSU

    thread_local int const ConstantRainLossFactor(301);
    thread_local int const ScheduledRainLossFactor(302);

    thread_local int const AmbientTempSchedule(1); // ambient temperature around tank (or HPWH inlet air) is scheduled
    thread_local int const AmbientTempZone(2);     // tank is located in a zone or HPWH inlet air is zone air only
    thread_local int const AmbientTempExterior(3); // tank is located outdoors or HPWH inlet air is outdoor air only

    thread_local int const ConstantWaterTable(401);
    thread_local int const ScheduledWaterTable(402);

    thread_local int const NoControlLevel(501);
    thread_local int const MainsFloatValve(502);
    thread_local int const WellFloatValve(503);
    thread_local int const WellFloatMainsBackup(504);
    thread_local int const OtherTankFloatValve(505);
    thread_local int const TankMainsBackup(506);

    thread_local int const OverflowDiscarded(601);
    thread_local int const OverflowToTank(602);

    // DERIVED TYPE DEFINITIONS:

    // MODULE VARIABLE DECLARATIONS:
    thread_local int NumWaterStorageTanks(0); // number of water Storage tanks in model
    thread_local int NumRainCollectors(0);    // number of rainfall collectors in model
    thread_local int NumGroundWaterWells(0);  // number of
    thread_local int NumSiteRainFall(0);
    thread_local int NumIrrigation(0);                  // DJS PSU Dec 2006 number of irrigation descriptions (1 allowed)
    thread_local bool AnyWaterSystemsInModel(false);    // control flag set true if any water systems
    thread_local bool WaterSystemGetInputCalled(false); // set true once input data gotten.
    thread_local bool AnyIrrigationInModel(false);      // control flag set true if irrigation input for ecoroof DJS PSU Dec 2006

    // Object Data
    thread_local SiteRainFallDataStruct
        RainFall; // type of rainfall modeling | design annual rain | rain sched id | nominal annual rain | current rate | current amount
    thread_local IrrigationDataStruct Irrigation; // type of irrigation modeling | Irrigation schedule id | scheduled amount | actual amount | irrigation threshold
    thread_local Array1D<StorageTankDataStruct> WaterStorage;
    thread_local Array1D<RainfallCollectorDataStruct> RainCollector;
    thread_local Array1D<GroundwaterWellDataStruct> GroundwaterWell;

} // namespace DataWater

} // namespace EnergyPlus
