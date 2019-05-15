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

#ifndef DataGlobalConstants_hh_INCLUDED
#define DataGlobalConstants_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>

// EnergyPlus Headers
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace DataGlobalConstants {

    // Data
    // MODULE PARAMETER DEFINITIONS:
    // End Use Parameters
    thread_local extern int const NumEndUses;

    thread_local extern int const endUseHeating;
    thread_local extern int const endUseCooling;
    thread_local extern int const endUseInteriorLights;
    thread_local extern int const endUseExteriorLights;
    thread_local extern int const endUseInteriorEquipment;
    thread_local extern int const endUseExteriorEquipment;
    thread_local extern int const endUseFans;
    thread_local extern int const endUsePumps;
    thread_local extern int const endUseHeatRejection;
    thread_local extern int const endUseHumidification;
    thread_local extern int const endUseHeatRecovery;
    thread_local extern int const endUseWaterSystem;
    thread_local extern int const endUseRefrigeration;
    thread_local extern int const endUseCogeneration;

    // Resource Types
    thread_local extern std::string const cRT_None;
    thread_local extern std::string const cRT_NoneUC;
    thread_local extern int const iRT_None;
    thread_local extern std::string const cRT_Electricity;
    thread_local extern std::string const cRT_ElectricityUC;
    thread_local extern int const iRT_Electricity;
    thread_local extern std::string const cRT_Natural_Gas;
    thread_local extern std::string const cRT_Natural_GasUC;
    thread_local extern int const iRT_Natural_Gas;
    thread_local extern std::string const cRT_Gas;
    thread_local extern std::string const cRT_GasUC;
    thread_local extern int const iRT_Gas;
    thread_local extern std::string const cRT_Gasoline;
    thread_local extern std::string const cRT_GasolineUC;
    thread_local extern int const iRT_Gasoline;
    thread_local extern std::string const cRT_Diesel;
    thread_local extern std::string const cRT_DieselUC;
    thread_local extern int const iRT_Diesel;
    thread_local extern std::string const cRT_Coal;
    thread_local extern std::string const cRT_CoalUC;
    thread_local extern int const iRT_Coal;
    thread_local extern std::string const cRT_FuelOil_1;
    thread_local extern std::string const cRT_FuelOil_1UC;
    thread_local extern int const iRT_FuelOil_1;
    thread_local extern std::string const cRT_DistillateOil;
    thread_local extern std::string const cRT_DistillateOilUC;
    thread_local extern int const iRT_DistillateOil;
    thread_local extern std::string const cRT_FuelOil_2;
    thread_local extern std::string const cRT_FuelOil_2UC;
    thread_local extern int const iRT_FuelOil_2;
    thread_local extern std::string const cRT_ResidualOil;
    thread_local extern std::string const cRT_ResidualOilUC;
    thread_local extern int const iRT_ResidualOil;
    thread_local extern std::string const cRT_Propane;
    thread_local extern std::string const cRT_PropaneUC;
    thread_local extern int const iRT_Propane;
    thread_local extern std::string const cRT_LPG;
    thread_local extern std::string const cRT_LPGUC;
    thread_local extern int const iRT_LPG;
    thread_local extern std::string const cRT_Water;
    thread_local extern std::string const cRT_WaterUC;
    thread_local extern int const iRT_Water;
    thread_local extern std::string const cRT_EnergyTransfer;
    thread_local extern std::string const cRT_EnergyTransferUC;
    thread_local extern int const iRT_EnergyTransfer;
    thread_local extern std::string const cRT_Steam;
    thread_local extern std::string const cRT_SteamUC;
    thread_local extern int const iRT_Steam;
    thread_local extern std::string const cRT_DistrictCooling;
    thread_local extern std::string const cRT_DistrictCoolingUC;
    thread_local extern int const iRT_DistrictCooling;
    thread_local extern std::string const cRT_DistrictHeating;
    thread_local extern std::string const cRT_DistrictHeatingUC;
    thread_local extern int const iRT_DistrictHeating;
    thread_local extern std::string const cRT_ElectricityProduced;
    thread_local extern std::string const cRT_ElectricityProducedUC;
    thread_local extern int const iRT_ElectricityProduced;
    thread_local extern std::string const cRT_ElectricityPurchased;
    thread_local extern std::string const cRT_ElectricityPurchasedUC;
    thread_local extern int const iRT_ElectricityPurchased;
    thread_local extern std::string const cRT_ElectricitySurplusSold;
    thread_local extern std::string const cRT_ElectricitySurplusSoldUC;
    thread_local extern int const iRT_ElectricitySurplusSold;
    thread_local extern std::string const cRT_ElectricityNet;
    thread_local extern std::string const cRT_ElectricityNetUC;
    thread_local extern int const iRT_ElectricityNet;
    thread_local extern std::string const cRT_SolarWater;
    thread_local extern std::string const cRT_SolarWaterUC;
    thread_local extern int const iRT_SolarWater;
    thread_local extern std::string const cRT_SolarAir;
    thread_local extern std::string const cRT_SolarAirUC;
    thread_local extern int const iRT_SolarAir;
    thread_local extern std::string const cRT_SO2;
    thread_local extern std::string const cRT_SO2UC;
    thread_local extern int const iRT_SO2;
    thread_local extern std::string const cRT_NOx;
    thread_local extern std::string const cRT_NOxUC;
    thread_local extern int const iRT_NOx;
    thread_local extern std::string const cRT_N2O;
    thread_local extern std::string const cRT_N2OUC;
    thread_local extern int const iRT_N2O;
    thread_local extern std::string const cRT_PM;
    thread_local extern std::string const cRT_PMUC;
    thread_local extern int const iRT_PM;
    thread_local extern std::string const cRT_PM2_5;
    thread_local extern std::string const cRT_PM2_5UC;
    thread_local extern int const iRT_PM2_5;
    thread_local extern std::string const cRT_PM10;
    thread_local extern std::string const cRT_PM10UC;
    thread_local extern int const iRT_PM10;
    thread_local extern std::string const cRT_CO;
    thread_local extern std::string const cRT_COUC;
    thread_local extern int const iRT_CO;
    thread_local extern std::string const cRT_CO2;
    thread_local extern std::string const cRT_CO2UC;
    thread_local extern int const iRT_CO2;
    thread_local extern std::string const cRT_CH4;
    thread_local extern std::string const cRT_CH4UC;
    thread_local extern int const iRT_CH4;
    thread_local extern std::string const cRT_NH3;
    thread_local extern std::string const cRT_NH3UC;
    thread_local extern int const iRT_NH3;
    thread_local extern std::string const cRT_NMVOC;
    thread_local extern std::string const cRT_NMVOCUC;
    thread_local extern int const iRT_NMVOC;
    thread_local extern std::string const cRT_Hg;
    thread_local extern std::string const cRT_HgUC;
    thread_local extern int const iRT_Hg;
    thread_local extern std::string const cRT_Pb;
    thread_local extern std::string const cRT_PbUC;
    thread_local extern int const iRT_Pb;
    thread_local extern std::string const cRT_NuclearHigh;
    thread_local extern std::string const cRT_NuclearHighUC;
    thread_local extern int const iRT_NuclearHigh;
    thread_local extern std::string const cRT_NuclearLow;
    thread_local extern std::string const cRT_NuclearLowUC;
    thread_local extern int const iRT_NuclearLow;
    thread_local extern std::string const cRT_WaterEnvironmentalFactors;
    thread_local extern std::string const cRT_WaterEnvironmentalFactorsUC;
    thread_local extern int const iRT_WaterEnvironmentalFactors;
    thread_local extern std::string const cRT_CarbonEquivalent;
    thread_local extern std::string const cRT_CarbonEquivalentUC;
    thread_local extern int const iRT_CarbonEquivalent;
    thread_local extern std::string const cRT_Source;
    thread_local extern std::string const cRT_SourceUC;
    thread_local extern int const iRT_Source;
    thread_local extern std::string const cRT_PlantLoopHeatingDemand;
    thread_local extern std::string const cRT_PlantLoopHeatingDemandUC;
    thread_local extern int const iRT_PlantLoopHeatingDemand;
    thread_local extern std::string const cRT_PlantLoopCoolingDemand;
    thread_local extern std::string const cRT_PlantLoopCoolingDemandUC;
    thread_local extern int const iRT_PlantLoopCoolingDemand;
    thread_local extern std::string const cRT_OnSiteWater;
    thread_local extern std::string const cRT_OnSiteWaterUC;
    thread_local extern int const iRT_OnSiteWater;
    thread_local extern std::string const cRT_MainsWater;
    thread_local extern std::string const cRT_MainsWaterUC;
    thread_local extern int const iRT_MainsWater;
    thread_local extern std::string const cRT_RainWater;
    thread_local extern std::string const cRT_RainWaterUC;
    thread_local extern int const iRT_RainWater;
    thread_local extern std::string const cRT_WellWater;
    thread_local extern std::string const cRT_WellWaterUC;
    thread_local extern int const iRT_WellWater;
    thread_local extern std::string const cRT_Condensate;
    thread_local extern std::string const cRT_CondensateUC;
    thread_local extern int const iRT_Condensate;
    thread_local extern std::string const cRT_OtherFuel1;
    thread_local extern std::string const cRT_OtherFuel1UC;
    thread_local extern int const iRT_OtherFuel1;
    thread_local extern std::string const cRT_OtherFuel2;
    thread_local extern std::string const cRT_OtherFuel2UC;
    thread_local extern int const iRT_OtherFuel2;
    thread_local extern int const NumOfResourceTypes;
    thread_local extern int const ResourceTypeInitialOffset; // to reach "ValidTypes"
    thread_local extern Array1D_string const cRT_ValidTypes;

    thread_local extern int const iGeneratorICEngine;
    thread_local extern int const iGeneratorCombTurbine;
    thread_local extern int const iGeneratorPV;
    thread_local extern int const iGeneratorFuelCell;
    thread_local extern int const iGeneratorMicroCHP;
    thread_local extern int const iGeneratorMicroturbine;
    thread_local extern int const iGeneratorWindTurbine;
    thread_local extern int const iGeneratorPVWatts;

    thread_local extern int const iEvapCoolerDirectCELDEKPAD;
    thread_local extern int const iEvapCoolerInDirectCELDEKPAD;
    thread_local extern int const iEvapCoolerInDirectWETCOIL;
    thread_local extern int const iEvapCoolerInDirectRDDSpecial;
    thread_local extern int const iEvapCoolerDirectResearchSpecial;

    // DERIVED TYPE DEFINITIONS:
    // na

    // MODULE VARIABLE DECLARATIONS:
    // na

    // SUBROUTINE SPECIFICATIONS FOR MODULE DataGlobalConstants

    // Functions

    int AssignResourceTypeNum(std::string const &ResourceTypeChar);

    std::string GetResourceTypeChar(int const ResourceTypeNum);

} // namespace DataGlobalConstants

} // namespace EnergyPlus

#endif
