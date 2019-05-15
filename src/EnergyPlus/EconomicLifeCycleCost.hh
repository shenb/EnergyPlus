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
    thread_local extern int const disConvBeginOfYear;
    thread_local extern int const disConvMidYear;
    thread_local extern int const disConvEndOfYear;

    thread_local extern int const inflAppConstantDollar;
    thread_local extern int const inflAppCurrentDollar;

    // ModifiedAcceleratedCostRecoverySystem or Straight Line
    thread_local extern int const depMethMACRS3;
    thread_local extern int const depMethMACRS5;
    thread_local extern int const depMethMACRS7;
    thread_local extern int const depMethMACRS10;
    thread_local extern int const depMethMACRS15;
    thread_local extern int const depMethMACRS20;
    thread_local extern int const depMethStraight27;
    thread_local extern int const depMethStraight31;
    thread_local extern int const depMethStraight39;
    thread_local extern int const depMethStraight40;
    thread_local extern int const depMethNone;

    thread_local extern int const costCatMaintenance;
    thread_local extern int const costCatRepair;
    thread_local extern int const costCatOperation;
    thread_local extern int const costCatReplacement;
    thread_local extern int const costCatMinorOverhaul;
    thread_local extern int const costCatMajorOverhaul;
    thread_local extern int const costCatOtherOperational;
    thread_local extern int const costCatConstruction;
    thread_local extern int const costCatSalvage;
    thread_local extern int const costCatOtherCapital;
    thread_local extern int const costCatWater;
    thread_local extern int const costCatEnergy;
    thread_local extern int const costCatTotEnergy;
    thread_local extern int const costCatTotOper;
    thread_local extern int const costCatTotCaptl;
    thread_local extern int const costCatTotGrand;

    thread_local extern int const countOfCostCat; // count of the number of cost categories

    // The NIST supplement includes UPV* factors for
    //   Electricity
    //   Natural gas
    //   Distillate oil
    //   Liquified petroleum gas
    //   Residual oil
    //   Coal

    thread_local extern int const startServicePeriod;
    thread_local extern int const startBasePeriod;

    // DERIVED TYPE DEFINITIONS:
    // na

    // MODULE VARIABLE DECLARATIONS:

    // related to LifeCycleCost:Parameters
    thread_local extern bool LCCparamPresent;       // If a LifeCycleCost:Parameters object is present
    thread_local extern std::string LCCname;        // Name
    thread_local extern int discountConvension;     // Discounting Convention
    thread_local extern int inflationApproach;      // Inflation Approach
    thread_local extern Real64 realDiscountRate;    // Real Discount Rate
    thread_local extern Real64 nominalDiscountRate; // Nominal Discount Rate
    thread_local extern Real64 inflation;           // Inflation
    thread_local extern int baseDateMonth;          // Base Date Month (1=Jan, 12=Dec)
    thread_local extern int baseDateYear;           // Base Date Year  1900-2100
    thread_local extern int serviceDateMonth;       // Service Date Month (1=Jan, 12=Dec)
    thread_local extern int serviceDateYear;        // Service Date Year 1900-2100
    thread_local extern int lengthStudyYears;       // Length of Study Period in Years
    thread_local extern int lengthStudyTotalMonths; // Length of Study expressed in months (years x 12)
    thread_local extern Real64 taxRate;             // Tax rate
    thread_local extern int depreciationMethod;     // Depreciation Method
    // derived
    thread_local extern int lastDateMonth; // Last Date Month (the month before the base date month)
    thread_local extern int lastDateYear;  // Last Date Year (base date year + length of study period in years)

    thread_local extern int numRecurringCosts;

    thread_local extern int numNonrecurringCost;

    thread_local extern int numUsePriceEscalation;

    thread_local extern int numUseAdjustment;

    thread_local extern int numCashFlow;
    thread_local extern int const skRecurring;
    thread_local extern int const skNonrecurring;
    thread_local extern int const skResource;
    thread_local extern int const skSum;
    thread_local extern int const pvkEnergy;
    thread_local extern int const pvkNonEnergy;
    thread_local extern int const pvkNotComputed;
    thread_local extern int numResourcesUsed;

    // present value factors
    thread_local extern Array1D<Real64> SPV;
    thread_local extern Array2D<Real64> energySPV; // yearly equivalent to FEMP UPV* values

    // arrays related to computing after tax cashflow and present value
    thread_local extern Array1D<Real64> DepreciatedCapital;
    thread_local extern Array1D<Real64> TaxableIncome;
    thread_local extern Array1D<Real64> Taxes;
    thread_local extern Array1D<Real64> AfterTaxCashFlow;
    thread_local extern Array1D<Real64> AfterTaxPresentValue;

    thread_local extern Array1D_string const MonthNames;

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
    thread_local extern Array1D<RecurringCostsType> RecurringCosts;
    thread_local extern Array1D<NonrecurringCostType> NonrecurringCost;
    thread_local extern Array1D<UsePriceEscalationType> UsePriceEscalation;
    thread_local extern Array1D<UseAdjustmentType> UseAdjustment;
    thread_local extern Array1D<CashFlowType> CashFlow;

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
