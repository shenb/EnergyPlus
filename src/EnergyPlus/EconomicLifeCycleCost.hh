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

#ifndef EconomicLifeCycleCost_hh_INCLUDED
#define EconomicLifeCycleCost_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>
#include <ObjexxFCL/Array2D.hh>

// EnergyPlus Headers
#include <DataGlobals.hh>
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace EconomicLifeCycleCost {

    // Using/Aliasing

    // Data
    // MODULE PARAMETER DEFINITIONS:
    EP_GLOBAL extern int const disConvBeginOfYear;
    EP_GLOBAL extern int const disConvMidYear;
    EP_GLOBAL extern int const disConvEndOfYear;

    EP_GLOBAL extern int const inflAppConstantDollar;
    EP_GLOBAL extern int const inflAppCurrentDollar;

    // ModifiedAcceleratedCostRecoverySystem or Straight Line
    EP_GLOBAL extern int const depMethMACRS3;
    EP_GLOBAL extern int const depMethMACRS5;
    EP_GLOBAL extern int const depMethMACRS7;
    EP_GLOBAL extern int const depMethMACRS10;
    EP_GLOBAL extern int const depMethMACRS15;
    EP_GLOBAL extern int const depMethMACRS20;
    EP_GLOBAL extern int const depMethStraight27;
    EP_GLOBAL extern int const depMethStraight31;
    EP_GLOBAL extern int const depMethStraight39;
    EP_GLOBAL extern int const depMethStraight40;
    EP_GLOBAL extern int const depMethNone;

    EP_GLOBAL extern int const costCatMaintenance;
    EP_GLOBAL extern int const costCatRepair;
    EP_GLOBAL extern int const costCatOperation;
    EP_GLOBAL extern int const costCatReplacement;
    EP_GLOBAL extern int const costCatMinorOverhaul;
    EP_GLOBAL extern int const costCatMajorOverhaul;
    EP_GLOBAL extern int const costCatOtherOperational;
    EP_GLOBAL extern int const costCatConstruction;
    EP_GLOBAL extern int const costCatSalvage;
    EP_GLOBAL extern int const costCatOtherCapital;
    EP_GLOBAL extern int const costCatWater;
    EP_GLOBAL extern int const costCatEnergy;
    EP_GLOBAL extern int const costCatTotEnergy;
    EP_GLOBAL extern int const costCatTotOper;
    EP_GLOBAL extern int const costCatTotCaptl;
    EP_GLOBAL extern int const costCatTotGrand;

    EP_GLOBAL extern int const countOfCostCat; // count of the number of cost categories

    // The NIST supplement includes UPV* factors for
    //   Electricity
    //   Natural gas
    //   Distillate oil
    //   Liquified petroleum gas
    //   Residual oil
    //   Coal

    EP_GLOBAL extern int const startServicePeriod;
    EP_GLOBAL extern int const startBasePeriod;

    // DERIVED TYPE DEFINITIONS:
    // na

    // MODULE VARIABLE DECLARATIONS:

    // related to LifeCycleCost:Parameters
    EP_GLOBAL extern bool LCCparamPresent;       // If a LifeCycleCost:Parameters object is present
    EP_GLOBAL extern std::string LCCname;        // Name
    EP_GLOBAL extern int discountConvension;     // Discounting Convention
    EP_GLOBAL extern int inflationApproach;      // Inflation Approach
    EP_GLOBAL extern Real64 realDiscountRate;    // Real Discount Rate
    EP_GLOBAL extern Real64 nominalDiscountRate; // Nominal Discount Rate
    EP_GLOBAL extern Real64 inflation;           // Inflation
    EP_GLOBAL extern int baseDateMonth;          // Base Date Month (1=Jan, 12=Dec)
    EP_GLOBAL extern int baseDateYear;           // Base Date Year  1900-2100
    EP_GLOBAL extern int serviceDateMonth;       // Service Date Month (1=Jan, 12=Dec)
    EP_GLOBAL extern int serviceDateYear;        // Service Date Year 1900-2100
    EP_GLOBAL extern int lengthStudyYears;       // Length of Study Period in Years
    EP_GLOBAL extern int lengthStudyTotalMonths; // Length of Study expressed in months (years x 12)
    EP_GLOBAL extern Real64 taxRate;             // Tax rate
    EP_GLOBAL extern int depreciationMethod;     // Depreciation Method
    // derived
    EP_GLOBAL extern int lastDateMonth; // Last Date Month (the month before the base date month)
    EP_GLOBAL extern int lastDateYear;  // Last Date Year (base date year + length of study period in years)

    EP_GLOBAL extern int numRecurringCosts;

    EP_GLOBAL extern int numNonrecurringCost;

    EP_GLOBAL extern int numUsePriceEscalation;

    EP_GLOBAL extern int numUseAdjustment;

    EP_GLOBAL extern int numCashFlow;
    EP_GLOBAL extern int const skRecurring;
    EP_GLOBAL extern int const skNonrecurring;
    EP_GLOBAL extern int const skResource;
    EP_GLOBAL extern int const skSum;
    EP_GLOBAL extern int const pvkEnergy;
    EP_GLOBAL extern int const pvkNonEnergy;
    EP_GLOBAL extern int const pvkNotComputed;
    EP_GLOBAL extern int numResourcesUsed;

    // present value factors
    EP_GLOBAL extern Array1D<Real64> SPV;
    EP_GLOBAL extern Array2D<Real64> energySPV; // yearly equivalent to FEMP UPV* values

    // arrays related to computing after tax cashflow and present value
    EP_GLOBAL extern Array1D<Real64> DepreciatedCapital;
    EP_GLOBAL extern Array1D<Real64> TaxableIncome;
    EP_GLOBAL extern Array1D<Real64> Taxes;
    EP_GLOBAL extern Array1D<Real64> AfterTaxCashFlow;
    EP_GLOBAL extern Array1D<Real64> AfterTaxPresentValue;

    EP_GLOBAL extern Array1D_string const MonthNames;

    // SUBROUTINE SPECIFICATIONS FOR MODULE <module_name>:

    // Types

    struct RecurringCostsType
    {
        // Members
        std::string name;            // Name
        std::string lineItem;        // Line Item
        int category;                // Category
        Real64 cost;                 // Cost
        int startOfCosts;            // Start of Costs
        int yearsFromStart;          // Years from Start 0 - 100
        int monthsFromStart;         // Months from Start 0 - 11
        int totalMonthsFromStart;    // Total months (12 x years) + months
        int repeatPeriodYears;       // Repeat Period Years 1 - 100
        int repeatPeriodMonths;      // Repeat Period Months 0 - 11
        int totalRepeatPeriodMonths; // Total months (12 x years) + months
        Real64 annualEscalationRate; // Annual escalation rate

        // Default Constructor
        RecurringCostsType()
            : category(costCatMaintenance), startOfCosts(startServicePeriod), yearsFromStart(0), monthsFromStart(0), totalMonthsFromStart(0),
              repeatPeriodYears(0), repeatPeriodMonths(0), totalRepeatPeriodMonths(0), annualEscalationRate(0.0)
        {
        }
    };

    struct NonrecurringCostType
    {
        // Members
        std::string name;         // Name
        std::string lineItem;     // Line Item
        int category;             // Category
        Real64 cost;              // Cost
        int startOfCosts;         // Start of Costs
        int yearsFromStart;       // Years from Start 0 - 100
        int monthsFromStart;      // Months from Start 0 - 11
        int totalMonthsFromStart; // Total months (12 x years) + months

        // Default Constructor
        NonrecurringCostType()
            : category(costCatConstruction), startOfCosts(startServicePeriod), yearsFromStart(0), monthsFromStart(0), totalMonthsFromStart(0)
        {
        }
    };

    struct UsePriceEscalationType
    {
        // Members
        std::string name;           // Name
        int resource;               // resource like electricity or natural gas (uses definitions from DataGlobalConstants)
        int escalationStartYear;    // Escalation Start Year 1900-2100
        int escalationStartMonth;   // Escalation Start Month 1 to 12
        Array1D<Real64> Escalation; // Escalation by year, first year is baseDateYear
        // last year is baseDateYear + lengthStudyYears - 1

        // Default Constructor
        UsePriceEscalationType() : escalationStartYear(0), escalationStartMonth(0)
        {
        }
    };

    struct UseAdjustmentType
    {
        // Members
        std::string name;           // Name
        int resource;               // resource like electricity or natural gas (uses definitions from DataGlobalConstants)
        Array1D<Real64> Adjustment; // Adjustment by year, first year is baseDateYear
        // last year is baseDateYear + lengthStudyYears - 1

        // Default Constructor
        UseAdjustmentType()
        {
        }
    };

    struct CashFlowType
    {
        // Members
        std::string name;         // Name - just for labeling output - use Category for aggregation
        int SourceKind;           // 1=recurring, 2=nonrecurring, 3=resource
        int Resource;             // resource like electricity or natural gas (uses definitions from DataGlobalConstants)
        int Category;             // uses "costCat" constants above
        Array1D<Real64> mnAmount; // cashflow dollar amount by month, first year is baseDateYear
        // last year is baseDateYear + lengthStudyYears - 1
        Array1D<Real64> yrAmount;  // cashflow dollar amount by year, first year is baseDateYear
        int pvKind;                // kind of present value 1=energy, 2=non-energy,3=not computed but summed
        Real64 presentValue;       // total present value for cashflow
        Real64 orginalCost;        // original cost from recurring, non-recurring or energy cost
        Array1D<Real64> yrPresVal; // present value by year, first year is baseDateYear

        // Default Constructor
        CashFlowType() : pvKind(0)
        {
        }
    };

    // Object Data
    EP_GLOBAL extern Array1D<RecurringCostsType> RecurringCosts;
    EP_GLOBAL extern Array1D<NonrecurringCostType> NonrecurringCost;
    EP_GLOBAL extern Array1D<UsePriceEscalationType> UsePriceEscalation;
    EP_GLOBAL extern Array1D<UseAdjustmentType> UseAdjustment;
    EP_GLOBAL extern Array1D<CashFlowType> CashFlow;

    // Functions

    void GetInputForLifeCycleCost();

    void ComputeLifeCycleCostAndReport();

    //======================================================================================================================
    //======================================================================================================================

    //    GET INPUT ROUTINES

    //======================================================================================================================
    //======================================================================================================================

    void GetInputLifeCycleCostParameters();

    void GetInputLifeCycleCostRecurringCosts();

    void GetInputLifeCycleCostNonrecurringCost();

    void GetInputLifeCycleCostUsePriceEscalation();

    void GetInputLifeCycleCostUseAdjustment();

    int MonthToMonthNumber(std::string const &inMonthString, int const inDefaultMonth);

    //======================================================================================================================
    //======================================================================================================================

    //    COMPUTATION ROUTINES

    //======================================================================================================================
    //======================================================================================================================

    void ExpressAsCashFlows();

    void ComputePresentValue();

    void ComputeTaxAndDepreciation();

    //======================================================================================================================
    //======================================================================================================================

    //    OUTPUT ROUTINES

    //======================================================================================================================
    //======================================================================================================================

    void WriteTabularLifeCycleCostReport();

    void clear_state();

} // namespace EconomicLifeCycleCost

} // namespace EnergyPlus

#endif
