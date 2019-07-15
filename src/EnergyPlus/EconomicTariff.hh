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

#ifndef EconomicTariff_hh_INCLUDED
#define EconomicTariff_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1A.hh>
#include <ObjexxFCL/Array2D.hh>

// EnergyPlus Headers
#include <DataGlobals.hh>
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace EconomicTariff {

    // Using/Aliasing

    // Data
    // ECONOMCIS:TARIFF enumerated lists

    EP_GLOBAL extern int const kindUnknown;
    EP_GLOBAL extern int const kindTariff;
    EP_GLOBAL extern int const kindQualify;
    EP_GLOBAL extern int const kindChargeSimple;
    EP_GLOBAL extern int const kindChargeBlock;
    EP_GLOBAL extern int const kindRatchet;
    EP_GLOBAL extern int const kindVariable;
    EP_GLOBAL extern int const kindComputation;
    EP_GLOBAL extern int const kindCategory;
    EP_GLOBAL extern int const kindNative;
    EP_GLOBAL extern int const kindAssignCompute;

    EP_GLOBAL extern int const conversionUSERDEF;
    EP_GLOBAL extern int const conversionKWH;
    EP_GLOBAL extern int const conversionTHERM;
    EP_GLOBAL extern int const conversionMMBTU; // million btu
    EP_GLOBAL extern int const conversionMJ;
    EP_GLOBAL extern int const conversionKBTU;
    EP_GLOBAL extern int const conversionMCF; // thousand cubic feet
    EP_GLOBAL extern int const conversionCCF; // hundred cubic feet
    EP_GLOBAL extern int const conversionM3;  // cubic meter
    EP_GLOBAL extern int const conversionGAL;
    EP_GLOBAL extern int const conversionKGAL; // thousand gallons

    EP_GLOBAL extern Array1D_string const convEneStrings;
    EP_GLOBAL extern Array1D_string const convDemStrings;

    EP_GLOBAL extern int const demandWindowQuarter;
    EP_GLOBAL extern int const demandWindowHalf;
    EP_GLOBAL extern int const demandWindowHour;
    EP_GLOBAL extern int const demandWindowDay;
    EP_GLOBAL extern int const demandWindowWeek;

    EP_GLOBAL extern Array1D_string const demWindowStrings;

    EP_GLOBAL extern int const buyFromUtility;
    EP_GLOBAL extern int const sellToUtility;
    EP_GLOBAL extern int const netMetering;

    // For several different objects that reference seasons
    EP_GLOBAL extern int const seasonWinter;
    EP_GLOBAL extern int const seasonSpring;
    EP_GLOBAL extern int const seasonSummer;
    EP_GLOBAL extern int const seasonFall;
    EP_GLOBAL extern int const seasonAnnual;
    EP_GLOBAL extern int const seasonMonthly;

    // For AssignVariablePt
    EP_GLOBAL extern int const varIsArgument; // if used as a value or on right side of expression
    EP_GLOBAL extern int const varIsAssigned; // if variable is assigned to or on left side of expression

    // For ComputeSteps
    // All are negative because all variables are positive
    EP_GLOBAL extern int const opSUM;
    EP_GLOBAL extern int const opMULTIPLY;
    EP_GLOBAL extern int const opSUBTRACT;
    EP_GLOBAL extern int const opDIVIDE;
    EP_GLOBAL extern int const opABSOLUTE;
    EP_GLOBAL extern int const opINTEGER;
    EP_GLOBAL extern int const opSIGN;
    EP_GLOBAL extern int const opROUND;
    EP_GLOBAL extern int const opMAXIMUM;
    EP_GLOBAL extern int const opMINIMUM;
    EP_GLOBAL extern int const opEXCEEDS;
    EP_GLOBAL extern int const opANNUALMINIMUM;
    EP_GLOBAL extern int const opANNUALMAXIMUM;
    EP_GLOBAL extern int const opANNUALSUM;
    EP_GLOBAL extern int const opANNUALAVERAGE;
    EP_GLOBAL extern int const opANNUALOR;
    EP_GLOBAL extern int const opANNUALAND;
    EP_GLOBAL extern int const opANNUALMAXIMUMZERO;
    EP_GLOBAL extern int const opANNUALMINIMUMZERO;
    EP_GLOBAL extern int const opIF;
    EP_GLOBAL extern int const opGREATERTHAN;
    EP_GLOBAL extern int const opGREATEREQUAL;
    EP_GLOBAL extern int const opLESSTHAN;
    EP_GLOBAL extern int const opLESSEQUAL;
    EP_GLOBAL extern int const opEQUAL;
    EP_GLOBAL extern int const opNOTEQUAL;
    EP_GLOBAL extern int const opAND;
    EP_GLOBAL extern int const opOR;
    EP_GLOBAL extern int const opNOT;
    EP_GLOBAL extern int const opADD;
    EP_GLOBAL extern int const opNOOP; // no operation - just list the operand variables - shown as FROM

    // not predefined variable (user defined name - many variables and all objects)
    // used in econvar%specific
    EP_GLOBAL extern int const varUserDefined;
    EP_GLOBAL extern int const varNotYetDefined;

    // category variables (used in econvar%specific)
    EP_GLOBAL extern int const catEnergyCharges;
    EP_GLOBAL extern int const catDemandCharges;
    EP_GLOBAL extern int const catServiceCharges;
    EP_GLOBAL extern int const catBasis;
    EP_GLOBAL extern int const catAdjustment;
    EP_GLOBAL extern int const catSurcharge;
    EP_GLOBAL extern int const catSubtotal;
    EP_GLOBAL extern int const catTaxes;
    EP_GLOBAL extern int const catTotal;
    EP_GLOBAL extern int const catNotIncluded;

    // native variables (based on energy and demands from the simulation) used in econvar%specific
    EP_GLOBAL extern int const nativeTotalEnergy;
    EP_GLOBAL extern int const nativeTotalDemand;
    EP_GLOBAL extern int const nativePeakEnergy;
    EP_GLOBAL extern int const nativePeakDemand;
    EP_GLOBAL extern int const nativeShoulderEnergy;
    EP_GLOBAL extern int const nativeShoulderDemand;
    EP_GLOBAL extern int const nativeOffPeakEnergy;
    EP_GLOBAL extern int const nativeOffPeakDemand;
    EP_GLOBAL extern int const nativeMidPeakEnergy;
    EP_GLOBAL extern int const nativeMidPeakDemand;
    EP_GLOBAL extern int const nativePeakExceedsOffPeak;
    EP_GLOBAL extern int const nativeOffPeakExceedsPeak;
    EP_GLOBAL extern int const nativePeakExceedsMidPeak;
    EP_GLOBAL extern int const nativeMidPeakExceedsPeak;
    EP_GLOBAL extern int const nativePeakExceedsShoulder;
    EP_GLOBAL extern int const nativeShoulderExceedsPeak;
    EP_GLOBAL extern int const nativeIsWinter;
    EP_GLOBAL extern int const nativeIsNotWinter;
    EP_GLOBAL extern int const nativeIsSpring;
    EP_GLOBAL extern int const nativeIsNotSpring;
    EP_GLOBAL extern int const nativeIsSummer;
    EP_GLOBAL extern int const nativeIsNotSummer;
    EP_GLOBAL extern int const nativeIsAutumn;
    EP_GLOBAL extern int const nativeIsNotAutumn;

    EP_GLOBAL extern int const nativePeakAndShoulderEnergy;
    EP_GLOBAL extern int const nativePeakAndShoulderDemand;
    EP_GLOBAL extern int const nativePeakAndMidPeakEnergy;
    EP_GLOBAL extern int const nativePeakAndMidPeakDemand;
    EP_GLOBAL extern int const nativeShoulderAndOffPeakEnergy;
    EP_GLOBAL extern int const nativeShoulderAndOffPeakDemand;
    EP_GLOBAL extern int const nativePeakAndOffPeakEnergy;
    EP_GLOBAL extern int const nativePeakAndOffPeakDemand;

    EP_GLOBAL extern int const nativeRealTimePriceCosts;
    EP_GLOBAL extern int const nativeAboveCustomerBaseCosts;
    EP_GLOBAL extern int const nativeBelowCustomerBaseCosts;
    EP_GLOBAL extern int const nativeAboveCustomerBaseEnergy;
    EP_GLOBAL extern int const nativeBelowCustomerBaseEnergy;

    EP_GLOBAL extern int const countPeriod;
    EP_GLOBAL extern int const MaxNumMonths;
    EP_GLOBAL extern int const maxNumBlk;

    EP_GLOBAL extern int const periodPeak;
    EP_GLOBAL extern int const periodShoulder;
    EP_GLOBAL extern int const periodOffPeak;
    EP_GLOBAL extern int const periodMidPeak;

    EP_GLOBAL extern int const kindMeterNotElectric; // must be zero because testing of >0 done later.
    EP_GLOBAL extern int const kindMeterElecSimple;
    EP_GLOBAL extern int const kindMeterElecProduced;
    EP_GLOBAL extern int const kindMeterElecPurchased;
    EP_GLOBAL extern int const kindMeterElecSurplusSold;
    EP_GLOBAL extern int const kindMeterElecNet;

    EP_GLOBAL extern int const kindMeterNotWater;
    EP_GLOBAL extern int const kindMeterWater;

    EP_GLOBAL extern int const kindMeterNotGas;
    EP_GLOBAL extern int const kindMeterGas;

    EP_GLOBAL extern int const varUnitTypeEnergy;
    EP_GLOBAL extern int const varUnitTypeDemand;
    EP_GLOBAL extern int const varUnitTypeDimensionless;
    EP_GLOBAL extern int const varUnitTypeCurrency;

    // MODULE PARAMETER DEFINITIONS:

    EP_GLOBAL extern int numEconVar;
    EP_GLOBAL extern int sizeEconVar;

    // holds the outbound connections for each variable
    EP_GLOBAL extern Array1D_int operand; // sized to sizeOperand
    EP_GLOBAL extern int numOperand;
    EP_GLOBAL extern int sizeOperand;

    EP_GLOBAL extern int numTariff;

    EP_GLOBAL extern int numQualify;

    EP_GLOBAL extern int numChargeSimple;

    EP_GLOBAL extern int numChargeBlock;

    EP_GLOBAL extern int numRatchet;

    EP_GLOBAL extern int numComputation;

    // list of pointers to variable, 0 end of line, negative indicate operations
    EP_GLOBAL extern Array1D_int steps;
    EP_GLOBAL extern Array1D_int stepsCopy;
    EP_GLOBAL extern int numSteps;
    EP_GLOBAL extern int sizeSteps;

    EP_GLOBAL extern int topOfStack;
    EP_GLOBAL extern int sizeStack;

    // MODULE VARIABLE DECLARATIONS:

    // SUBROUTINE SPECIFICATIONS FOR MODULE

    // Types

    struct EconVarType
    {
        // Members
        std::string name;       // name of the economics object or variable
        int tariffIndx;         // index of the tariff name in the tariff array
        int kindOfObj;          // enumerated list for the kind of economics object
        int index;              // pointer to item in specific array
        Array1D<Real64> values; // values
        // the following items are not part of the object description
        bool isArgument; // flag if the variable is ever used as an argument (value needed)
        bool isAssigned; // flag if the variable is ever assigned to
        int specific;    // the specific type of variable - see enumerated lists
        // the following items are used in determinging the dependency relationship of variables
        // and consist of an operator and a list of variables.
        int cntMeDependOn; // count of items in depend this line depends upon
        int Operator;      // operator used in equation (usually opSUM or opNOOP)
        int firstOperand;  // first item in the operand array
        int lastOperand;   // last item in the operand array
        bool activeNow;    // flag if the econVar is used in the current tariff
        bool isEvaluated;  // flag if the economics object that results in this variable
        // has already been evaulated
        bool isReported; // flag if the econVar has been reported in the output file
        int varUnitType; // variable unit type: energy, demand, dimensionless, currency

        // Default Constructor
        EconVarType()
            : tariffIndx(0), kindOfObj(0), index(0), values(MaxNumMonths, 0.0), isArgument(false), isAssigned(false), specific(0), cntMeDependOn(0),
              Operator(0), firstOperand(0), lastOperand(0), activeNow(false), isEvaluated(false), isReported(false), varUnitType(0)
        {
        }
    };

    struct TariffType
    {
        // Members
        std::string tariffName;     // name of the tariff
        std::string reportMeter;    // name of the report meter
        int reportMeterIndx;        // index of the report meter
        int kindElectricMtr;        // kind of electric meter - see enumerated list above, 0 is not electric
        int kindWaterMtr;           // kinf of water meter - 0 (default) is not water, 1 is water
        int kindGasMtr;             // kinf of gas meter - 0 (default) is not gas, 1 is gas
        int resourceNum;            // based on list of DataGlobalConstants
        int convChoice;             // enumerated choice index of the conversion factor
        Real64 energyConv;          // energy conversion factor
        Real64 demandConv;          // demand conversion factor
        std::string periodSchedule; // name of the period schedule (time of day)
        int periodSchIndex;         // index to the period schedule
        std::string seasonSchedule; // name of the season schedule (winter/summer)
        int seasonSchIndex;         // index to the season schedule
        std::string monthSchedule;  // name of month schedule (when months end)
        int monthSchIndex;          // index to the month schedule
        int demandWindow;           // enumerated list of the kind of demand window
        Real64 demWinTime;          // length of time for the demand window
        Real64 monthChgVal;         // monthly charge value
        int monthChgPt;             // pointer to a variable that contains the monthly charge
        // if 0 then use monthChgVal
        Real64 minMonthChgVal; // minimum monthly charge value
        int minMonthChgPt;     // pointer to a variable that contains the minimum monthly charge
        // if 0 then use minMonthChgVal
        std::string chargeSchedule;  // name of the charge schedule (for real time pricing)
        int chargeSchIndex;          // index to the charge schedule
        std::string baseUseSchedule; // name of the baseline use schedule (for real time pricing)
        int baseUseSchIndex;         // index to the baseline use schedule
        std::string groupName;       // name of the group
        std::string monetaryUnit;    // text string representing monetary unit, usually $
        int buyOrSell;               // enumerated choice index of the buy or sell options
        // index to the first and last category variables
        int firstCategory; // first category referenced
        int lastCategory;  // last category referenced
        // pointers to econ variables for categories
        int ptEnergyCharges;
        int ptDemandCharges;
        int ptServiceCharges;
        int ptBasis;
        int ptAdjustment;
        int ptSurcharge;
        int ptSubtotal;
        int ptTaxes;
        int ptTotal;
        int ptNotIncluded;
        // index to the first and last native variables (energies and demands from the simulation)
        int firstNative;
        int lastNative;
        // native variables (based on energy and demands from the simulation)
        int nativeTotalEnergy;
        int nativeTotalDemand;
        int nativePeakEnergy;
        int nativePeakDemand;
        int nativeShoulderEnergy;
        int nativeShoulderDemand;
        int nativeOffPeakEnergy;
        int nativeOffPeakDemand;
        int nativeMidPeakEnergy;
        int nativeMidPeakDemand;
        int nativePeakExceedsOffPeak;
        int nativeOffPeakExceedsPeak;
        int nativePeakExceedsMidPeak;
        int nativeMidPeakExceedsPeak;
        int nativePeakExceedsShoulder;
        int nativeShoulderExceedsPeak;
        int nativeIsWinter;
        int nativeIsNotWinter;
        int nativeIsSpring;
        int nativeIsNotSpring;
        int nativeIsSummer;
        int nativeIsNotSummer;
        int nativeIsAutumn;
        int nativeIsNotAutumn;
        int nativePeakAndShoulderEnergy;
        int nativePeakAndShoulderDemand;
        int nativePeakAndMidPeakEnergy;
        int nativePeakAndMidPeakDemand;
        int nativeShoulderAndOffPeakEnergy;
        int nativeShoulderAndOffPeakDemand;
        int nativePeakAndOffPeakEnergy;
        int nativePeakAndOffPeakDemand;
        // real time pricing native variable pointers
        int nativeRealTimePriceCosts;
        int nativeAboveCustomerBaseCosts;
        int nativeBelowCustomerBaseCosts;
        int nativeAboveCustomerBaseEnergy;
        int nativeBelowCustomerBaseEnergy;
        // arrays for holding gathered values
        Array2D<Real64> gatherEnergy;
        Array2D<Real64> gatherDemand;
        Real64 collectTime;
        Real64 collectEnergy;
        // arryas for holding real time pricing gathered values
        Array1D<Real64> RTPcost;
        Array1D<Real64> RTPaboveBaseCost;
        Array1D<Real64> RTPbelowBaseCost;
        Array1D<Real64> RTPaboveBaseEnergy;
        Array1D<Real64> RTPbelowBaseEnergy;
        Array1D_int seasonForMonth;
        // overall qualification of the rate
        bool isQualified;
        int ptDisqualifier;
        // overall selection and annual cost
        bool isSelected;
        Real64 totalAnnualCost;
        Real64 totalAnnualEnergy;

        // Default Constructor
        TariffType()
            : reportMeterIndx(0), kindElectricMtr(0), kindWaterMtr(0), kindGasMtr(0), resourceNum(0), convChoice(0), energyConv(0.0), demandConv(0.0),
              periodSchIndex(0), seasonSchIndex(0), monthSchIndex(0), demandWindow(0), demWinTime(0.0), monthChgVal(0.0), monthChgPt(0),
              minMonthChgVal(0.0), minMonthChgPt(0), chargeSchIndex(0), baseUseSchIndex(0), buyOrSell(0), firstCategory(0), lastCategory(0),
              ptEnergyCharges(0), ptDemandCharges(0), ptServiceCharges(0), ptBasis(0), ptAdjustment(0), ptSurcharge(0), ptSubtotal(0), ptTaxes(0),
              ptTotal(0), ptNotIncluded(0), firstNative(0), lastNative(0), nativeTotalEnergy(0), nativeTotalDemand(0), nativePeakEnergy(0),
              nativePeakDemand(0), nativeShoulderEnergy(0), nativeShoulderDemand(0), nativeOffPeakEnergy(0), nativeOffPeakDemand(0),
              nativeMidPeakEnergy(0), nativeMidPeakDemand(0), nativePeakExceedsOffPeak(0), nativeOffPeakExceedsPeak(0), nativePeakExceedsMidPeak(0),
              nativeMidPeakExceedsPeak(0), nativePeakExceedsShoulder(0), nativeShoulderExceedsPeak(0), nativeIsWinter(0), nativeIsNotWinter(0),
              nativeIsSpring(0), nativeIsNotSpring(0), nativeIsSummer(0), nativeIsNotSummer(0), nativeIsAutumn(0), nativeIsNotAutumn(0),
              nativePeakAndShoulderEnergy(0), nativePeakAndShoulderDemand(0), nativePeakAndMidPeakEnergy(0), nativePeakAndMidPeakDemand(0),
              nativeShoulderAndOffPeakEnergy(0), nativeShoulderAndOffPeakDemand(0), nativePeakAndOffPeakEnergy(0), nativePeakAndOffPeakDemand(0),
              nativeRealTimePriceCosts(0), nativeAboveCustomerBaseCosts(0), nativeBelowCustomerBaseCosts(0), nativeAboveCustomerBaseEnergy(0),
              nativeBelowCustomerBaseEnergy(0), gatherEnergy(MaxNumMonths, countPeriod, 0.0), gatherDemand(MaxNumMonths, countPeriod, 0.0),
              collectTime(0.0), collectEnergy(0.0), RTPcost(MaxNumMonths, 0.0), RTPaboveBaseCost(MaxNumMonths, 0.0),
              RTPbelowBaseCost(MaxNumMonths, 0.0), RTPaboveBaseEnergy(MaxNumMonths, 0.0), RTPbelowBaseEnergy(MaxNumMonths, 0.0),
              seasonForMonth(MaxNumMonths, 0), isQualified(false), ptDisqualifier(0), isSelected(false), totalAnnualCost(0.0), totalAnnualEnergy(0.0)
        {
        }
    };

    struct QualifyType
    {
        // Members
        int namePt;          // index of the name and variable in the variable array
        int tariffIndx;      // index of the tariff name in the tariff array
        int sourcePt;        // index of the variable in the variable array
        bool isMaximum;      // indicator if maximum test otherwise minimum
        Real64 thresholdVal; // value of the threshold
        int thresholdPt;     // pointer to the variable holding the values
        int season;          // enumerated list of the kind of season
        bool isConsecutive;  // indicator if consecutive months otherwise count
        int numberOfMonths;  // number of months the test must be good for

        // Default Constructor
        QualifyType()
            : namePt(0), tariffIndx(0), sourcePt(0), isMaximum(false), thresholdVal(0.0), thresholdPt(0), season(0), isConsecutive(false),
              numberOfMonths(0)
        {
        }
    };

    struct ChargeSimpleType
    {
        // Members
        int namePt;        // index of the name and variable in the variable array
        int tariffIndx;    // index of the tariff name in the tariff array
        int sourcePt;      // index of the variable in the variable array
        int season;        // enumerated list of the kind of season
        int categoryPt;    // index of the category in the variable array
        Real64 costPerVal; // cost per unit value
        int costPerPt;     // cost per unit index in the variable array (0 is flag for no variable)

        // Default Constructor
        ChargeSimpleType() : namePt(0), tariffIndx(0), sourcePt(0), season(0), categoryPt(0), costPerVal(0.0), costPerPt(0)
        {
        }
    };

    struct ChargeBlockType
    {
        // Members
        int namePt;                 // index of the name and variable in the variable array
        int tariffIndx;             // index of the tariff name in the tariff array
        int sourcePt;               // index of the variable in the variable array
        int season;                 // enumerated list of the kind of season
        int categoryPt;             // index of the category in the variable array
        int remainingPt;            // index of the remaining into variable in the variable array
        Real64 blkSzMultVal;        // block size multiplier value
        int blkSzMultPt;            // block size variable in the variable array (0 is flag for no variable)
        int numBlk;                 // number of blocks used
        Array1D<Real64> blkSzVal;   // array of block size values
        Array1D_int blkSzPt;        // block size variables index to the variable array (0 is no variable)
        Array1D<Real64> blkCostVal; // array of block cost values
        Array1D_int blkCostPt;      // block cost variables index to the variable array (0 is no variable)

        // Default Constructor
        ChargeBlockType()
            : namePt(0), tariffIndx(0), sourcePt(0), season(0), categoryPt(0), remainingPt(0), blkSzMultVal(0.0), blkSzMultPt(0), numBlk(0),
              blkSzVal(maxNumBlk, 0.0), blkSzPt(maxNumBlk, 0), blkCostVal(maxNumBlk, 0.0), blkCostPt(maxNumBlk, 0)
        {
        }
    };

    struct RatchetType
    {
        // Members
        int namePt;           // index of the name and variable in the variable array
        int tariffIndx;       // index of the tariff name in the tariff array
        int baselinePt;       // index of the baseline variable in the variable array
        int adjustmentPt;     // index fo the adjustment variable in the variable array
        int seasonFrom;       // enumerated list of the kind of season
        int seasonTo;         // enumerated list of the kind of season
        Real64 multiplierVal; // value of the ratchet multiplier
        int multiplierPt;     // multiplier variable in the variable array (0 for no variable)
        Real64 offsetVal;     // value of the ratchet offset
        int offsetPt;         // offset variable in the variable array (0 for no variable)

        // Default Constructor
        RatchetType()
            : namePt(0), tariffIndx(0), baselinePt(0), adjustmentPt(0), seasonFrom(0), seasonTo(0), multiplierVal(0.0), multiplierPt(0),
              offsetVal(0.0), offsetPt(0)
        {
        }
    };

    struct ComputationType
    {
        // Members
        std::string computeName; // name of the compute
        int firstStep;           // index to steps array for the first step in this compute steps
        int lastStep;            // index to steps array for the last step in this compute steps
        bool isUserDef;          // if the computation steps were user defined

        // Default Constructor
        ComputationType() : firstStep(0), lastStep(0), isUserDef(false)
        {
        }
    };

    struct StackType
    {
        // Members
        int varPt;              // pointer to item in specific array
        Array1D<Real64> values; // values

        // Default Constructor
        StackType() : varPt(0), values(MaxNumMonths, 0.0)
        {
        }
    };

    // Object Data
    EP_GLOBAL extern Array1D<EconVarType> econVar;
    EP_GLOBAL extern Array1D<TariffType> tariff;
    EP_GLOBAL extern Array1D<QualifyType> qualify;
    EP_GLOBAL extern Array1D<ChargeSimpleType> chargeSimple;
    EP_GLOBAL extern Array1D<ChargeBlockType> chargeBlock;
    EP_GLOBAL extern Array1D<RatchetType> ratchet;
    EP_GLOBAL extern Array1D<ComputationType> computation;
    EP_GLOBAL extern Array1D<StackType> stack;

    // Functions

    void UpdateUtilityBills();

    //======================================================================================================================
    //======================================================================================================================

    //    GET INPUT ROUTINES

    //======================================================================================================================
    //======================================================================================================================

    void GetInputEconomicsTariff(bool &ErrorsFound); // true if errors found during getting input objects.

    void GetInputEconomicsQualify(bool &ErrorsFound); // true if errors found during getting input objects.

    void GetInputEconomicsChargeSimple(bool &ErrorsFound); // true if errors found during getting input objects.

    void GetInputEconomicsChargeBlock(bool &ErrorsFound); // true if errors found during getting input objects.

    void GetInputEconomicsRatchet(bool &ErrorsFound); // true if errors found during getting input objects.

    void GetInputEconomicsVariable(bool &ErrorsFound); // true if errors found during getting input objects.

    void GetInputEconomicsComputation(bool &ErrorsFound); // true if errors found during getting input objects.

    void GetInputEconomicsCurrencyType(bool &ErrorsFound); // true if errors found during getting input objects.

    void parseComputeLine(std::string const &lineOfCompute, int const fromTariff);

    void GetLastWord(std::string const &lineOfText, std::string::size_type &endOfScan, std::string &aWord);

    void initializeMonetaryUnit();

    int LookUpSeason(std::string const &nameOfSeason, std::string const &nameOfReferingObj);

    int FindTariffIndex(std::string const &nameOfTariff, std::string const &nameOfReferingObj, bool &ErrorsFound, std::string const &nameOfCurObj);

    void warnIfNativeVarname(std::string const &objName, int const curTariffIndex, bool &ErrorsFound, std::string const &curobjName);

    int AssignVariablePt(std::string const &stringIn,
                         bool const flagIfNotNumeric,
                         int const useOfVar,
                         int const varSpecific,
                         int const econObjKind,
                         int const objIndex,
                         int const tariffPt);

    void incrementEconVar();

    void incrementSteps();

    std::string RemoveSpaces(std::string const &StringIn);

    void CreateCategoryNativeVariables();

    int lookupOperator(std::string const &opString);

    //======================================================================================================================
    //======================================================================================================================

    //    DEFAULT COMPUTATION RELATED ROUTINES

    //======================================================================================================================
    //======================================================================================================================

    void CreateDefaultComputation();

    void addOperand(int const varMe, int const varOperand);

    void addChargesToOperand(int const curTariff, int const curPointer);

    //======================================================================================================================
    //======================================================================================================================

    //    GATHER TIMESTEP VALUES ROUTINE

    //======================================================================================================================
    //======================================================================================================================

    void GatherForEconomics();

    bool isWithinRange(int const testVal, int const minThreshold, int const maxThreshold);

    //======================================================================================================================
    //======================================================================================================================

    //    COMPUTE THE UTILITY BILLS AND CREATE REPORTS

    //======================================================================================================================
    //======================================================================================================================

    void ComputeTariff();

    void pushStack(Array1A<Real64> const monthlyArray, int const variablePointer);

    void popStack(Array1A<Real64> monthlyArray, int &variablePointer);

    void evaluateChargeSimple(int const usingVariable);

    void evaluateChargeBlock(int const usingVariable);

    void evaluateRatchet(int const usingVariable);

    void evaluateQualify(int const usingVariable);

    void addMonthlyCharge(int const usingVariable);

    void checkMinimumMonthlyCharge(int const curTariff);

    void setNativeVariables();

    void LEEDtariffReporting();

    void WriteTabularTariffReports();

    void showWarningsBasedOnTotal();

    void getMaxAndSum(int const varPointer, Real64 &sumResult, Real64 &maxResult);

    void
    ReportEconomicVariable(std::string const &titleString, bool const includeCategory, bool const showCurrencySymbol, std::string const &forString);

    void selectTariff();

    void GetMonthlyCostForResource(int const inResourceNumber, Array1A<Real64> outMonthlyCosts);

    void clear_state();

} // namespace EconomicTariff

} // namespace EnergyPlus

#endif
