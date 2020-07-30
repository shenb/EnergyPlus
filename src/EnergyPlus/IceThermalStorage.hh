// EnergyPlus, Copyright (c) 1996-2020, The Board of Trustees of the University of Illinois,
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

#ifndef IceThermalStorage_hh_INCLUDED
#define IceThermalStorage_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>

// EnergyPlus Headers
#include <EnergyPlus/DataGlobals.hh>
#include <EnergyPlus/EnergyPlus.hh>
#include <EnergyPlus/PlantComponent.hh>

namespace EnergyPlus {
    // Forward declarations
    struct EnergyPlusData;

namespace IceThermalStorage {

    // MODULE PARAMETER DEFINITIONS
    extern std::string const cIceStorageSimple;
    extern std::string const cIceStorageDetailed;
    extern std::string const cPcmStorageSimple;

    // ITS numbers and FoundOrNot
    extern int NumSimpleIceStorage;
    extern int NumDetailedIceStorage;
    extern int TotalNumIceStorage;

    enum class IceStorageType
    {
        Simple,
        Detailed
    };

    enum class CurveVars
    {
        FracChargedLMTD,
        FracDischargedLMTD,
        LMTDMassFlow,
        LMTDFracCharged
    };

    enum class DetIce
    {
        InsideMelt, // Inside melt system--charge starting with bare coil
        OutsideMelt // Outside melt system--charge from existing ice layer on coil
    };

    enum class ITSType
    {
        IceOnCoilInternal,
        IceOnCoilExternal
    };

    struct SimpleIceStorageData : PlantComponent
    {
        std::string Name;     // User identifier
        std::string ITSType;  // Ice Thermal Storage Type
        enum ITSType ITSType_Num;      // Storage Type as number (IceOnCoilInternal,IceOnCoilExternal)
        int MapNum;           // Number to Map structure
        int UratePtr;         // Charging/Discharging SchedulePtr: u value schedule
        Real64 ITSNomCap;     // Design nominal capacity of Ice Thermal Storage [J] (user input in GJ)
        int PltInletNodeNum;  // Node number on the inlet side of the plant
        int PltOutletNodeNum; // Node number on the outlet side of the plant
        // loop topology variables
        int LoopNum;
        int LoopSideNum;
        int BranchNum;
        int CompNum;
        Real64 DesignMassFlowRate;
        Real64 FreezeTemp;
        bool ResetXForITSFlag;
        bool MyEnvrnFlag;
        Real64 UAIceCh;
        Real64 UAIceDisCh;
        Real64 HLoss;
        Real64 XCurIceFrac;
        Real64 ITSMassFlowRate;
        Real64 ITSInletTemp;
        Real64 ITSOutletTemp;
        Real64 ITSOutletSetPointTemp;
        Real64 ITSCoolingRate;
        Real64 ITSCoolingEnergy;
        bool CheckEquipName;

        Real64 MyLoad;            // load requested by plant [W]
        Real64 Urate;             // [fraction]
        Real64 IceFracRemain;     // Fraction of ice remaining in storage [fraction]
        Real64 ITSChargingRate;   // [W]
        Real64 ITSChargingEnergy; // [J]
        Real64 ITSmdot;           // [kg/s]

        // Duplicated reporting vars for now. Investigate diffs when time to remove.
        Real64 ITSCoolingRate_rep;   // [W]
        Real64 ITSCoolingEnergy_rep; // [J]

        bool MyPlantScanFlag;
        bool MyEnvrnFlag2;

        // Default Constructor
        SimpleIceStorageData()
            : MapNum(0), UratePtr(0), ITSNomCap(0.0), PltInletNodeNum(0), PltOutletNodeNum(0), LoopNum(0), LoopSideNum(0),
              BranchNum(0), CompNum(0), DesignMassFlowRate(0.0), FreezeTemp(0.0), ResetXForITSFlag(false), MyEnvrnFlag(true), UAIceCh(0.0),
              UAIceDisCh(0.0), HLoss(0.0), XCurIceFrac(0.0), ITSMassFlowRate(0.0), ITSInletTemp(0.0), ITSOutletTemp(0.0), ITSOutletSetPointTemp(0.0),
              ITSCoolingRate(0.0), ITSCoolingEnergy(0.0), CheckEquipName(true), MyLoad(0.0), Urate(0.0), IceFracRemain(0.0), ITSChargingRate(0.0),
              ITSChargingEnergy(0.0), ITSmdot(0.0), ITSCoolingRate_rep(0.0), ITSCoolingEnergy_rep(0.0), MyPlantScanFlag(true), MyEnvrnFlag2(true)
        {
        }

        static PlantComponent *factory(std::string const &objectName);

        void simulate(EnergyPlusData &EP_UNUSED(state), const PlantLocation &calledFromLocation, bool FirstHVACIteration, Real64 &CurLoad, bool RunFlag) override;

        void InitSimpleIceStorage(BranchInputManagerData &dataBranchInputManager);

        void CalcIceStorageDormant();

        void CalcIceStorageCapacity(Real64 &MaxCap, Real64 &MinCap, Real64 &OptCap);

        void CalcIceStorageDischarge(Real64 myLoad, bool RunFlag, Real64 MaxCap);

        void CalcQiceDischageMax(Real64 &QiceMin);

        void CalcIceStorageCharge();

        void CalcQiceChargeMaxByChiller(Real64 &QiceMaxByChiller);

        void CalcQiceChargeMaxByITS(Real64 chillerOutletTemp, Real64 &QiceMaxByITS);

        void CalcUAIce(Real64 XCurIceFrac_loc, Real64 &UAIceCh_loc, Real64 &UAIceDisCh_loc, Real64 &HLoss_loc);

        void UpdateNode(Real64 myLoad, bool RunFlag);

        void RecordOutput(Real64 myLoad, bool RunFlag);

        void setupOutputVars();
    };

    struct DetailedIceStorageData : PlantComponent
    {
        std::string Name;         // User identifier
        std::string ScheduleName; // User identifier
        int ScheduleIndex;        // Plant inlet node number for ice storage unit
        Real64 NomCapacity;       // Design storage capacity of Ice Thermal Storage system [W-hr]
        // (User input for this parameter in GJ--need to convert to W-hr)
        int PlantInNodeNum;  // Plant inlet node number for ice storage unit
        int PlantOutNodeNum; // Plant outlet node number for ice storage unit
        int PlantLoopNum;
        int PlantLoopSideNum;
        int PlantBranchNum;
        int PlantCompNum;
        Real64 DesignMassFlowRate;
        int MapNum;                     // Number to Map structure
        std::string DischargeCurveName; // Curve name for discharging (used to find the curve index)
        int DischargeCurveNum;          // Curve index for discharging
        enum CurveVars DischargeCurveTypeNum;    // Integer version of discharging curve independent variables type
        std::string ChargeCurveName;    // Curve name for charging (used to find the curve index)
        int ChargeCurveNum;             // Curve index for charging
        enum CurveVars ChargeCurveTypeNum;       // Integer version of charging curve independent variables type
        Real64 CurveFitTimeStep;        // Time step used to generate performance data [hours]
        Real64 DischargeParaElecLoad;   // Parasitic electric load duing discharging [dimensionless]
        // (This is multiplied by the tank capacity to obtain elec consump)
        Real64 ChargeParaElecLoad; // Parasitic electric load duing charging [dimensionless]
        // (This is multiplied by the tank capacity to obtain elec consump)
        Real64 TankLossCoeff; // Fraction of total storage capacity lost per hour [1/hours]
        Real64 FreezingTemp;  // Freezing/melting temperature of ice storage unit [C]
        // Reporting data
        Real64 CompLoad;                  // load requested by plant [W]
        Real64 IceFracChange;             // Change in fraction of ice stored during the time step [fraction]
        Real64 IceFracRemaining;          // Fraction of ice remaining in storage [fraction]
        std::string ThawProcessIndicator; // User input determining whether system is inside or outside melt
        enum DetIce ThawProcessIndex;             // Conversion of thaw process indicator to integer index
        Real64 IceFracOnCoil;             // Fraction of ice on the coil (affects charging) [fraction]
        Real64 DischargingRate;           // Rate at which energy is being added (thawing) to ice unit [W]
        Real64 DischargingEnergy;         // Total energy added to the ice storage unit [J]
        Real64 ChargingRate;              // Rate at which energy is removed (freezing) to ice unit [W]
        Real64 ChargingEnergy;            // Total energy removed from ice storage unit [J]
        Real64 MassFlowRate;              // Total mass flow rate to component [kg/s]
        Real64 BypassMassFlowRate;        // Mass flow rate that bypasses the ice unit locally [kg/s]
        Real64 TankMassFlowRate;          // Mass flow rate through the ice storage unit [kg/s]
        Real64 InletTemp;                 // Component inlet temperature (same as bypass temperature) [C]
        Real64 OutletTemp;                // Component outlet temperature (blended) [C]
        Real64 TankOutletTemp;            // Ice storage unit outlet temperature [C]
        Real64 ParasiticElecRate;         // Parasitic electrical energy rate consumed by ice storage [W]
        Real64 ParasiticElecEnergy;       // Total parasitic electrical energy consumed by ice storage [J]
        int DischargeIterErrors;          // Number of max iterations exceeded errors during discharging
        int DischargeErrorCount;          // Index for error counting routine
        int ChargeIterErrors;             // Number of max iterations exceeded errors during charging
        int ChargeErrorCount;             // Index for error counting routine
        bool ResetXForITSFlag;
        bool MyEnvrnFlag;
        bool CheckEquipName;
        bool MyPlantScanFlag;
        bool MyEnvrnFlag2;

        // Default Constructor
        DetailedIceStorageData()
            : ScheduleIndex(0), NomCapacity(0.0), PlantInNodeNum(0), PlantOutNodeNum(0), PlantLoopNum(0), PlantLoopSideNum(0), PlantBranchNum(0),
              PlantCompNum(0), DesignMassFlowRate(0.0), MapNum(0), DischargeCurveNum(0), ChargeCurveNum(0), CurveFitTimeStep(1.0),
              DischargeParaElecLoad(0.0), ChargeParaElecLoad(0.0), TankLossCoeff(0.0), FreezingTemp(0.0), CompLoad(0.0), IceFracChange(0.0),
              IceFracRemaining(1.0), IceFracOnCoil(1.0), DischargingRate(0.0), DischargingEnergy(0.0), ChargingRate(0.0),
              ChargingEnergy(0.0), MassFlowRate(0.0), BypassMassFlowRate(0.0), TankMassFlowRate(0.0), InletTemp(0.0), OutletTemp(0.0),
              TankOutletTemp(0.0), ParasiticElecRate(0.0), ParasiticElecEnergy(0.0), DischargeIterErrors(0), DischargeErrorCount(0),
              ChargeIterErrors(0), ChargeErrorCount(0), ResetXForITSFlag(false), MyEnvrnFlag(true), CheckEquipName(true), MyPlantScanFlag(true),
              MyEnvrnFlag2(true)
        {
        }

        static PlantComponent *factory(std::string const &objectName);

        void simulate(EnergyPlusData &EP_UNUSED(state), const PlantLocation &calledFromLocation, bool FirstHVACIteration, Real64 &CurLoad, bool RunFlag) override;

        void InitDetailedIceStorage(BranchInputManagerData &dataBranchInputManager);

        void SimDetailedIceStorage();

        void UpdateDetailedIceStorage();

        void ReportDetailedIceStorage();

        void setupOutputVars();
    };

    struct SimplePcmStorageData : PlantComponent
    {
        std::string Name;         // User identifier
        std::string PcmTSType;      // PCM Thermal Storage Type
        enum ITSType PcmTSType_Num; // Storage Type as number (PcmOnCoilInternal,PcmOnCoilExternal)
        int MapNum;               // Number to Map structure
        int UratePtr;             // Charging/Discharging SchedulePtr: u value schedule
        Real64 PcmTSNomCap;         // Design nominal capacity of Pcm Thermal Storage [J] (user input in GJ)
        int PltInletNodeNum;      // Node number on the inlet side of the plant
        int PltOutletNodeNum;     // Node number on the outlet side of the plant
        // loop topology variables
        int LoopNum;
        int LoopSideNum;
        int BranchNum;
        int CompNum;
        Real64 DesignMassFlowRate;
        Real64 FreezeTemp; // check if needed or not 
        bool ResetXForPcmTSFlag;
        bool MyEnvrnFlag;
        Real64 UAIceCh; // replace with new variable
        Real64 UAIceDisCh; // replace with new variable
        Real64 HLoss;
        Real64 XCurPcmFrac;
        Real64 PcmTSMassFlowRate;
        Real64 PcmTSInletTemp;
        Real64 PcmTSOutletTemp;
        Real64 PcmTSOutletSetPointTemp;
        Real64 PcmTSCoolingRate;
        Real64 PcmTSCoolingEnergy;
        bool CheckEquipName;

        Real64 MyLoad;            // load requested by plant [W]
        Real64 Urate;             // [fraction]
        Real64 PcmFracRemain;     // Fraction of ice remaining in storage [fraction]
        Real64 PcmTSChargingRate;   // [W]
        Real64 PcmTSChargingEnergy; // [J]
        Real64 PcmTSmdot;           // [kg/s]

        // Duplicated reporting vars for now. Investigate diffs when time to remove.
        Real64 PcmTSCoolingRate_rep;   // [W]
        Real64 PcmTSCoolingEnergy_rep; // [J]

        bool MyPlantScanFlag;
        bool MyEnvrnFlag2;

                // Default Constructor
        SimplePcmStorageData()
            : MapNum(0), UratePtr(0), PcmTSNomCap(0.0), PltInletNodeNum(0), PltOutletNodeNum(0), LoopNum(0), LoopSideNum(0), BranchNum(0), CompNum(0),
              DesignMassFlowRate(0.0), FreezeTemp(0.0), ResetXForPcmTSFlag(false), MyEnvrnFlag(true), UAIceCh(0.0), UAIceDisCh(0.0), HLoss(0.0),
              XCurPcmFrac(0.0), PcmTSMassFlowRate(0.0), PcmTSInletTemp(0.0), PcmTSOutletTemp(0.0), PcmTSOutletSetPointTemp(0.0), PcmTSCoolingRate(0.0),
              PcmTSCoolingEnergy(0.0), CheckEquipName(true), MyLoad(0.0), Urate(0.0), PcmFracRemain(0.0), PcmTSChargingRate(0.0), PcmTSChargingEnergy(0.0),
              PcmTSmdot(0.0), PcmTSCoolingRate_rep(0.0), PcmTSCoolingEnergy_rep(0.0), MyPlantScanFlag(true), MyEnvrnFlag2(true)
        {
        }

        static PlantComponent *factory(std::string const &objectName);

        void simulate(EnergyPlusData &EP_UNUSED(state),
                      const PlantLocation &calledFromLocation,
                      bool FirstHVACIteration,
                      Real64 &CurLoad,
                      bool RunFlag) override;

        void InitSimplePcmStorage(BranchInputManagerData &dataBranchInputManager);

        void CalcPcmStorageDormant();

        void CalcPcmStorageCapacity(Real64 &MaxCap, Real64 &MinCap, Real64 &OptCap);

        void CalcPcmStorageDischarge(Real64 myLoad, bool RunFlag, Real64 MaxCap);

        void CalcQpcmDischageMax(Real64 &QpcmMin);

        void CalcPcmStorageCharge();

        //void CalcQpcmChargeMaxByChiller(Real64 &QiceMaxByChiller);

        void CalcQpcmChargeMaxByNtu(Real64 chillerOutletTemp, Real64 &QpcmMaxByPcmTS);

        //void CalcUAIce(Real64 XCurIceFrac_loc, Real64 &UAIceCh_loc, Real64 &UAIceDisCh_loc, Real64 &HLoss_loc);

        void UpdateNode(Real64 myLoad, bool RunFlag);

        void RecordOutput(Real64 myLoad, bool RunFlag);

        void setupOutputVars();

    };

    // Object Data
    extern Array1D<SimpleIceStorageData> SimpleIceStorage;     // dimension to number of machines
    extern Array1D<DetailedIceStorageData> DetailedIceStorage; // Derived type for detailed ice storage model
    extern Array1D<SimplePcmStorageData> SimplePcmStorage; 

    // Static Functions
    void clear_state();

    void GetIceStorageInput();

    Real64 CalcDetIceStorLMTDstar(Real64 Tin,  // ice storage unit inlet temperature
                                  Real64 Tout, // ice storage unit outlet (setpoint) temperature
                                  Real64 Tfr   // freezing temperature
    );

    Real64 CalcQstar(int CurveIndex,      // curve index
                     enum CurveVars CurveIndVarType, // independent variable type for ice storage
                     Real64 FracCharged,  // fraction charged for ice storage unit
                     Real64 LMTDstar,     // normalized log mean temperature difference across the ice storage unit
                     Real64 MassFlowstar  // normalized mass flow rate through the ice storage unit
    );

    Real64 TempSItoIP(Real64 Temp);

    Real64 TempIPtoSI(Real64 Temp);

    void UpdateIceFractions();

    

} // namespace IceThermalStorage

} // namespace EnergyPlus

#endif
