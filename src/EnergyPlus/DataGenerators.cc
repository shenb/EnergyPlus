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
#include <DataGenerators.hh>
#include <DataPrecisionGlobals.hh>

namespace EnergyPlus {

namespace DataGenerators {

    // MODULE INFORMATION:
    //       AUTHOR         B Griffith
    //       DATE WRITTEN   March 2005
    //       MODIFIED
    //       RE-ENGINEERED  July 2006 BG, generalized and added data for ICE/SE model micro CHP

    // PURPOSE OF THIS MODULE:
    // This data-only module is a repository for the variables that relate specifically
    // to the Fuel cell and Micro CHP modeling in EnergyPlus
    //  the data for the older BLAST generators are in those component's modules

    // METHODOLOGY EMPLOYED:

    // REFERENCES:
    // na

    // OTHER NOTES:
    // na

    // Using/Aliasing
    using namespace DataPrecisionGlobals;

    // Data
    // -only module should be available to other modules and routines.
    // Thus, all variables in this module must be PUBLIC.

    // MODULE PARAMETER DEFINITIONS:
    EP_GLOBAL int const NormalizedCurveMode(1); // mode where efficiency curves are modifier curves
    EP_GLOBAL int const DirectCurveMode(2);     // mode where efficiency curves are direct

    EP_GLOBAL int const ConstantRateSkinLoss(1);  // fixed rate mode for skin losses
    EP_GLOBAL int const UADTSkinLoss(2);          // UAdelta T mode for skin losses
    EP_GLOBAL int const QuadraticFuelNdotSkin(3); // Quadratic function of fuel flow for skin losses

    EP_GLOBAL int const QuadraticFuncofNdot(1);  // function of fuel rate mode for air flow
    EP_GLOBAL int const ConstantStoicsAirRat(2); // Constant air ratio in stoics with fuel constituents
    EP_GLOBAL int const QuadraticFuncofPel(3);   // function of electric power mode

    EP_GLOBAL int const NoRecoveryOnAirIntake(101);  // mode for controlling intake air heat recovery
    EP_GLOBAL int const RecoverBurnInvertBatt(102);  // mode for controlling intake air heat recovery
    EP_GLOBAL int const RecoverAuxiliaryBurner(103); // mode for controlling intake air heat recovery
    EP_GLOBAL int const RecoverInverterBatt(104);    // mode for controlling intake air heat recovery
    EP_GLOBAL int const RecoverInverter(105);        // mode for controlling intake air heat recovery
    EP_GLOBAL int const RecoverBattery(106);         // mode for controlling intake air heat recovery

    EP_GLOBAL int const RegularAir(1);
    EP_GLOBAL int const UserDefinedConstituents(2);

    EP_GLOBAL int const FuelInTempFromNode(1);
    EP_GLOBAL int const FuelInTempSchedule(2);

    EP_GLOBAL int const WaterInReformMains(21);
    EP_GLOBAL int const WaterInReformAirNode(22);
    EP_GLOBAL int const WaterInReformWaterNode(23);
    EP_GLOBAL int const WaterInReformSchedule(24);

    EP_GLOBAL int const InverterEffConstant(1);
    EP_GLOBAL int const InverterEffQuadratic(2);

    EP_GLOBAL int const FixedEffectiveness(11);   // exhaust gas HX modeling mode
    EP_GLOBAL int const LMTDempiricalUAeff(12);   // exhaust gas HX modeling mode
    EP_GLOBAL int const LMTDfundementalUAeff(13); // exhaust gas HX modeling mode
    EP_GLOBAL int const Condensing(14);           // exhaust gas HX modeling mode

    EP_GLOBAL int const SimpleEffConstraints(21);         // electrical storage modeling mode
    EP_GLOBAL int const LeadAcidBatterySaupe(22);         // electrical storage modeling mode
    EP_GLOBAL int const LeadAcidBatterManwellMcGowan(23); // electrical storage modeling mode

    EP_GLOBAL int const SurroundingZone(31);
    EP_GLOBAL int const AirInletForFC(32);

    EP_GLOBAL int const OpModeOff(1);      // CHP operating mode OFF
    EP_GLOBAL int const OpModeStandby(2);  // CHP operating mode Stand By
    EP_GLOBAL int const OpModeWarmUp(3);   // CHP operating mode Warm Up or start up
    EP_GLOBAL int const OpModeNormal(4);   // CHP operating mode Normal
    EP_GLOBAL int const OpModeCoolDown(5); // CHP operating mode Cool down or shut down

    EP_GLOBAL int const fuelModeGaseousConstituents(301);
    EP_GLOBAL int const fuelModeGenericLiquid(302);

    EP_GLOBAL Real64 const MinProductGasTemp(-100.0); // Minimum bound on search for product gas temps
    EP_GLOBAL Real64 const MaxProductGasTemp(2000.0); // Maximum bound on search for product gas temps

    EP_GLOBAL int const NISTShomate(41);
    EP_GLOBAL int const NASAPolynomial(42);

    EP_GLOBAL Real64 const RinKJperMolpK(0.0083145); // R is ideal gas constant (kJ/mol-K)
    EP_GLOBAL Real64 const InitHRTemp(50.0);         // Initialization temperature for heat recovery water

    EP_GLOBAL Real64 const ImBalanceTol(0.00001); // used as fraction of electrical power at power module

    // DERIVED TYPE DEFINITIONS

    // MODULE VARIABLE DECLARATIONS:

    EP_GLOBAL int NumFuelConstit(0);
    EP_GLOBAL int NumGeneratorFuelSups(0);
    EP_GLOBAL int NumFuelCellGenerators(0); // number of SOFC Generators specified in input
    EP_GLOBAL int NumMicroCHPs(0);
    EP_GLOBAL int NumMicroCHPParams(0); // number of parameter sets for micro chp
    EP_GLOBAL int NumGensWDynamics(0);  // number of dynamics controls for generators

    // Object Data
    EP_GLOBAL Array1D<FCDataStruct> FuelCell; // dimension to number of machines
    EP_GLOBAL Array1D<GasPropertyDataStruct> GasPhaseThermoChemistryData;
    EP_GLOBAL Array1D<GeneratorFuelSupplyDataStruct> FuelSupply; // fuel supply (reused across various)
    EP_GLOBAL Array1D<MicroCHPDataStruct> MicroCHP;
    EP_GLOBAL Array1D<MicroCHPParamsNonNormalized> MicroCHPParamInput; // Used during get input then put into nested
    EP_GLOBAL Array1D<GeneratorDynamicsManagerStruct> GeneratorDynamics;

    void clear_state()
    {
        NumFuelConstit = 0;
        NumGeneratorFuelSups = 0;
        NumFuelCellGenerators = 0;
        NumMicroCHPs = 0;
        NumMicroCHPParams = 0;
        NumGensWDynamics = 0;
        FuelCell.deallocate();
        GasPhaseThermoChemistryData.deallocate();
        FuelSupply.deallocate();
        MicroCHP.deallocate();
        MicroCHPParamInput.deallocate();
        GeneratorDynamics.deallocate();
    }

} // namespace DataGenerators

} // namespace EnergyPlus
