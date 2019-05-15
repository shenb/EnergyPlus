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

// ObjexxFCL Headers
#include <ObjexxFCL/Array.functions.hh>
#include <ObjexxFCL/gio.hh>

// EnergyPlus Headers
#include <DataPrecisionGlobals.hh>
#include <OutputReportPredefined.hh>

namespace EnergyPlus {

namespace OutputReportPredefined {

    // MODULE INFORMATION:
    //    AUTHOR         Jason Glazer of GARD Analytics, Inc.
    //    DATE WRITTEN   August 2006
    //    MODIFIED       na
    //    RE-ENGINEERED  na
    // PURPOSE OF THIS MODULE:
    //    Support the creation of predefined tabular output.
    // METHODOLOGY EMPLOYED:
    // REFERENCES:
    //    None.
    // OTHER NOTES:.
    // Using/Aliasing
    using namespace DataPrecisionGlobals;

    // Data
    // The following section initializes the predefined column heading variables
    // The variables get their value in AssignPredefined

    // Climate Summary Report
    thread_local int pdrClim;
    thread_local int pdstDesDay;
    thread_local int pdchDDmaxDB;
    thread_local int pdchDDrange;
    thread_local int pdchDDhumid;
    thread_local int pdchDDhumTyp;
    thread_local int pdchDDwindSp;
    thread_local int pdchDDwindDr;
    thread_local int pdstWthr;
    thread_local int pdchWthrVal;

    // HVAC Equipment Report
    thread_local int pdrEquip;
    thread_local int pdstMech;
    thread_local int pdchMechType;
    thread_local int pdchMechNomCap;
    thread_local int pdchMechNomEff;
    thread_local int pdchMechIPLVSI;
    thread_local int pdchMechIPLVIP;
    // Fan subtable
    thread_local int pdstFan;
    thread_local int pdchFanType;
    thread_local int pdchFanTotEff;
    thread_local int pdchFanDeltaP;
    thread_local int pdchFanVolFlow;
    thread_local int pdchFanMotorIn;
    thread_local int pdchFanEnergyIndex;
    thread_local int pdchFanEndUse;
    thread_local int pdchFanPwr;
    thread_local int pdchFanPwrPerFlow;
    thread_local int pdchFanDesDay;
    thread_local int pdchFanPkTime;
    // Pump subtable
    thread_local int pdstPump;
    thread_local int pdchPumpType;
    thread_local int pdchPumpControl;
    thread_local int pdchPumpHead;
    thread_local int pdchPumpFlow;
    thread_local int pdchPumpPower;
    thread_local int pdchPumpPwrPerFlow;
    thread_local int pdchMotEff;
    // Cooling coil subtable
    thread_local int pdstCoolCoil;
    thread_local int pdchCoolCoilType;
    thread_local int pdchCoolCoilDesCap;
    thread_local int pdchCoolCoilTotCap;
    thread_local int pdchCoolCoilSensCap;
    thread_local int pdchCoolCoilLatCap;
    thread_local int pdchCoolCoilSHR;
    thread_local int pdchCoolCoilNomEff;
    thread_local int pdchCoolCoilUATotal;
    thread_local int pdchCoolCoilArea;

    // DX Cooling Coil subtable
    thread_local int pdstDXCoolCoil;
    thread_local int pdchDXCoolCoilType; // DX cooling coil type

    thread_local int pdchDXCoolCoilNetCapSI; // Standard Rated (Net) Cooling Capacity [W]
    thread_local int pdchDXCoolCoilCOP;      // EER/COP value in SI unit at AHRI std. 340/360 conditions [W/W]
    thread_local int pdchDXCoolCoilSEERIP;   // SEER value in IP unit at AHRI std. 210/240 conditions [Btu/W-hr]
    thread_local int pdchDXCoolCoilEERIP;    // EER value in IP unit at AHRI std. 340/360 conditions [Btu/W-h]
    thread_local int pdchDXCoolCoilIEERIP;   // IEER value in IP unit at AHRI std. 340/360 conditions

    // DX Cooling Coil subtable per ANSI/ASHRAE Std 127 for Tests A, B, C and D
    thread_local int pdstDXCoolCoil2;
    thread_local int pdchDXCoolCoilNetCapSIA;  // Standard Rated (Net) Cooling Capacity [W], Test A
    thread_local int pdchDXCoolCoilElecPowerA; // Standard Rated Electric Power [W], Test A
    thread_local int pdchDXCoolCoilNetCapSIB;  // Standard Rated (Net) Cooling Capacity [W], Test B
    thread_local int pdchDXCoolCoilElecPowerB; // Standard Rated Electric Power [W], Test B
    thread_local int pdchDXCoolCoilNetCapSIC;  // Standard Rated (Net) Cooling Capacity [W], Test C
    thread_local int pdchDXCoolCoilElecPowerC; // Standard Rated Electric Power [W], Test C
    thread_local int pdchDXCoolCoilNetCapSID;  // Standard Rated (Net) Cooling Capacity [W], Test D
    thread_local int pdchDXCoolCoilElecPowerD; // Standard Rated Electric Power [W], Test D

    // VAV DX Cooling Ratings Details
    thread_local int pdstVAVDXCoolCoil; // details for Packaged VAV rating under AHRI 340/360
    thread_local int pdchVAVDXCoolCoilType;
    thread_local int pdchVAVDXFanName;
    thread_local int pdchVAVDXCoolCoilNetCapSI;
    thread_local int pdchVAVDXCoolCoilCOP;
    thread_local int pdchVAVDXCoolCoilIEERIP;
    thread_local int pdchVAVDXCoolCoilEERIP;
    thread_local int pdchVAVDXCoolCoilMdotA;
    thread_local int pdchVAVDXCoolCoilCOP_B;
    thread_local int pdchVAVDXCoolCoilEER_B_IP;
    thread_local int pdchVAVDXCoolCoilMdotB;
    thread_local int pdchVAVDXCoolCoilCOP_C;
    thread_local int pdchVAVDXCoolCoilEER_C_IP;
    thread_local int pdchVAVDXCoolCoilMdotC;
    thread_local int pdchVAVDXCoolCoilCOP_D;
    thread_local int pdchVAVDXCoolCoilEER_D_IP;
    thread_local int pdchVAVDXCoolCoilMdotD;

    // DX Heating Coil subtable
    thread_local int pdstDXHeatCoil;
    thread_local int pdchDXHeatCoilType; // DX Heating coil type
    thread_local int pdchDXHeatCoilHighCap;
    thread_local int pdchDXHeatCoilLowCap;
    thread_local int pdchDXHeatCoilHSPFSI;    // HSPF value in SI unit at AHRI std. 340/360 conditions [W/W]
    thread_local int pdchDXHeatCoilHSPFIP;    // HSPF value in IP unit at AHRI std. 340/360 conditions [Btu/W-hr]
    thread_local int pdchDXHeatCoilRegionNum; // Region number for which HSPF is calculated

    // Heating Coil subtable
    thread_local int pdstHeatCoil;
    thread_local int pdchHeatCoilType;
    thread_local int pdchHeatCoilDesCap;
    thread_local int pdchHeatCoilNomCap;
    thread_local int pdchHeatCoilNomEff;
    // SWH subtable
    thread_local int pdstSWH;
    thread_local int pdchSWHType;
    thread_local int pdchSWHVol;
    thread_local int pdchSWHHeatIn;
    thread_local int pdchSWHThEff;
    thread_local int pdchSWHRecEff;
    thread_local int pdchSWHEnFac;

    // Envelope Report
    thread_local int pdrEnvelope;
    thread_local int pdstOpaque;
    thread_local int pdchOpCons;
    thread_local int pdchOpRefl;
    thread_local int pdchOpUfactFilm;
    thread_local int pdchOpUfactNoFilm;
    thread_local int pdchOpGrArea;
    thread_local int pdchOpNetArea;
    thread_local int pdchOpAzimuth;
    thread_local int pdchOpTilt;
    thread_local int pdchOpDir;
    thread_local int pdstFen;
    thread_local int pdchFenCons;
    thread_local int pdchFenAreaOf1;
    thread_local int pdchFenGlassAreaOf1;
    thread_local int pdchFenFrameAreaOf1;
    thread_local int pdchFenDividerAreaOf1;
    thread_local int pdchFenArea;
    thread_local int pdchFenUfact;
    thread_local int pdchFenSHGC;
    thread_local int pdchFenVisTr;
    thread_local int pdchFenFrameConductance;
    thread_local int pdchFenDividerConductance;
    thread_local int pdchFenSwitchable;
    thread_local int pdchFenParent;
    thread_local int pdchFenAzimuth;
    thread_local int pdchFenTilt;
    thread_local int pdchFenDir;
    thread_local int pdstDoor;
    thread_local int pdchDrCons;
    thread_local int pdchDrUfactFilm;
    thread_local int pdchDrUfactNoFilm;
    thread_local int pdchDrGrArea;
    thread_local int pdchDrParent;
    thread_local int pdstIntFen;
    thread_local int pdchIntFenCons;
    thread_local int pdchIntFenAreaOf1;
    // Include these if interzone windows ever get frame and dividers
    // INTEGER :: pdchIntFenGlassAreaOf1
    // INTEGER :: pdchIntFenFrameAreaOf1
    // INTEGER :: pdchIntFenDividerAreaOf1
    // INTEGER :: pdchIntFenFrameConductance
    // INTEGER :: pdchIntFenDividerConductance
    thread_local int pdchIntFenArea;
    thread_local int pdchIntFenUfact;
    thread_local int pdchIntFenSHGC;
    thread_local int pdchIntFenVisTr;
    thread_local int pdchIntFenParent;

    // Shading Report
    thread_local int pdrShading;
    thread_local int pdstSunlitFrac;
    thread_local int pdchSlfMar21_9;
    thread_local int pdchSlfMar21_12;
    thread_local int pdchSlfMar21_15;
    thread_local int pdchSlfJun21_9;
    thread_local int pdchSlfJun21_12;
    thread_local int pdchSlfJun21_15;
    thread_local int pdchSlfDec21_9;
    thread_local int pdchSlfDec21_12;
    thread_local int pdchSlfDec21_15;
    thread_local int pdstWindowControl;
    thread_local int pdchWscName;
    thread_local int pdchWscShading;
    thread_local int pdchWscShadCons;
    thread_local int pdchWscControl;
    thread_local int pdchWscGlare;

    // Lighting Report
    thread_local int pdrLighting;
    thread_local int pdstInLite;
    thread_local int pdchInLtZone;
    thread_local int pdchInLtDens;
    thread_local int pdchInLtArea;
    thread_local int pdchInLtPower;
    thread_local int pdchInLtEndUse;
    thread_local int pdchInLtSchd;
    thread_local int pdchInLtAvgHrSchd;
    thread_local int pdchInLtAvgHrOper;
    thread_local int pdchInLtFullLoadHrs;
    thread_local int pdchInLtRetAir;
    thread_local int pdchInLtCond;
    thread_local int pdchInLtConsump;
    thread_local int pdstExtLite;
    thread_local int pdchExLtPower;
    thread_local int pdchExLtClock;
    thread_local int pdchExLtSchd;
    thread_local int pdchExLtAvgHrSchd;
    thread_local int pdchExLtAvgHrOper;
    thread_local int pdchExLtFullLoadHrs;
    thread_local int pdchExLtConsump;
    thread_local int pdstDaylight;
    thread_local int pdchDyLtZone;
    thread_local int pdchDyLtCtrlName;
    thread_local int pdchDyLtKind;
    thread_local int pdchDyLtCtrlType;
    thread_local int pdchDyLtFrac;
    thread_local int pdchDyLtWInst;
    thread_local int pdchDyLtWCtrl;

    // Sizing Report
    thread_local int pdrSizing;
    thread_local int pdstZoneClSize;
    thread_local int pdchZnClCalcDesLd;
    thread_local int pdchZnClUserDesLd;
    thread_local int pdchZnClUserDesLdPerArea;
    thread_local int pdchZnClCalcDesAirFlow;
    thread_local int pdchZnClUserDesAirFlow;
    thread_local int pdchZnClDesDay;
    thread_local int pdchZnClPkTime;
    thread_local int pdchZnClPkTstatTemp;
    thread_local int pdchZnClPkIndTemp;
    thread_local int pdchZnClPkIndHum;
    thread_local int pdchZnClPkOATemp;
    thread_local int pdchZnClPkOAHum;
    thread_local int pdchZnClPkOAMinFlow;
    thread_local int pdchZnClPkDOASHeatGain;
    thread_local int pdstZoneHtSize;
    thread_local int pdchZnHtCalcDesLd;
    thread_local int pdchZnHtUserDesLd;
    thread_local int pdchZnHtUserDesLdPerArea;
    thread_local int pdchZnHtCalcDesAirFlow;
    thread_local int pdchZnHtUserDesAirFlow;
    thread_local int pdchZnHtDesDay;
    thread_local int pdchZnHtPkTime;
    thread_local int pdchZnHtPkTstatTemp;
    thread_local int pdchZnHtPkIndTemp;
    thread_local int pdchZnHtPkIndHum;
    thread_local int pdchZnHtPkOATemp;
    thread_local int pdchZnHtPkOAHum;
    thread_local int pdchZnHtPkOAMinFlow;
    thread_local int pdchZnHtPkDOASHeatGain;
    thread_local int pdstSystemSize;
    thread_local int pdchSysSizCalcClAir;
    thread_local int pdchSysSizUserClAir;
    thread_local int pdchSysSizCalcHtAir;
    thread_local int pdchSysSizUserHtAir;
    thread_local int pdchSysSizAdjustedClAir;
    thread_local int pdchSysSizAdjustedHtAir;
    thread_local int pdchSysSizAdjustedMainAir;
    thread_local int pdchSysSizCalcHeatFlowRatio;
    thread_local int pdchSysSizUserHeatFlowRatio;
    thread_local int pdstPlantSize;
    thread_local int pdchPlantSizCalcVdot;
    thread_local int pdchPlantSizMeasVdot;
    thread_local int pdchPlantSizPrevVdot;
    //	int pdchPlantSizPass;
    thread_local int pdchPlantSizCoincYesNo;
    thread_local int pdchPlantSizDesDay;
    thread_local int pdchPlantSizPkTimeHour;
    thread_local int pdchPlantSizPkTimeDayOfSim;
    thread_local int pdchPlantSizPkTimeMin;

    // Coil Selection Table
    thread_local int pdrCoilSizingDetailsTable;
    thread_local int pdstCoilSummaryCoilSelection;
    thread_local int pdchCoilLocation;
    thread_local int pdchCoilHVACType;
    thread_local int pdchCoilHVACName;
    thread_local int pdchCoilZoneName;
    thread_local int pdchCoilName;
    thread_local int pdchCoilType;
    thread_local int pdchSysSizingMethCoinc;
    thread_local int pdchSysSizingMethCap;
    thread_local int pdchSysSizingMethAir;

    thread_local int pdchCoilIsCapAutosized;
    thread_local int pdchCoilIsAirFlowAutosized;
    thread_local int pdchCoilIsWaterFlowAutosized;
    thread_local int pdchCoilIsOATreated;
    thread_local int pdchCoilFinalTotalCap;
    thread_local int pdchCoilFinalSensCap;
    thread_local int pdchCoilFinalAirVolFlowRate;
    thread_local int pdchCoilFinalPlantVolFlowRate;

    thread_local int pdchCoilDDnameSensIdealPeak;
    thread_local int pdchCoilDateTimeSensIdealPeak;
    thread_local int pdchCoilDDnameTotIdealPeak;
    thread_local int pdchCoilDateTimeTotIdealPeak;
    thread_local int pdchCoilDDnameAirFlowIdealPeak;
    thread_local int pdchCoilDateTimeAirFlowIdealPeak;
    thread_local int pdchCoilTotalCapIdealPeak;
    thread_local int pdchCoilSensCapIdealPeak;
    thread_local int pdchCoilAirMassFlowIdealPeak;
    thread_local int pdchCoilAirVolumeFlowIdealPeak;
    thread_local int pdchCoilEntDryBulbIdealPeak;
    thread_local int pdchCoilEntWetBulbIdealPeak;
    thread_local int pdchCoilEntHumRatIdealPeak;
    thread_local int pdchCoilEntEnthalpyIdealPeak;
    thread_local int pdchCoilLvgDryBulbIdealPeak;
    thread_local int pdchCoilLvgWetBulbIdealPeak;
    thread_local int pdchCoilLvgHumRatIdealPeak;
    thread_local int pdchCoilLvgEnthalpyIdealPeak;
    thread_local int pdchCoilWaterMassFlowIdealPeak;
    thread_local int pdchCoilEntWaterTempIdealPeak;
    thread_local int pdchCoilLvgWaterTempIdealPeak;
    thread_local int pdchCoilWaterDeltaTempIdealPeak;
    thread_local int pdchCoilRatedTotalCap;
    thread_local int pdchCoilRatedSensCap;
    thread_local int pdchCoilOffRatingCapacityModifierIdealPeak;
    thread_local int pdchCoilOffRatingCapacityModifierSimPeak;
    thread_local int pdchCoilRatedAirMass;
    thread_local int pdchCoilRatedEntDryBulb;
    thread_local int pdchCoilRatedEntWetBulb;
    thread_local int pdchCoilRatedEntHumRat;
    thread_local int pdchCoilRatedEntEnthalpy;
    thread_local int pdchCoilRatedLvgDryBulb;
    thread_local int pdchCoilRatedLvgWetBulb;
    thread_local int pdchCoilRatedLvgHumRat;
    thread_local int pdchCoilRatedLvgEnthalpy;
    thread_local int pdchCoilRatedWaterMass;
    thread_local int pdchCoilRatedEntWaterTemp;
    thread_local int pdchCoilRatedLvgWaterTemp;
    thread_local int pdchCoilRatedWaterDeltaTemp;

    thread_local int pdchFanAssociatedWithCoilName;
    thread_local int pdchFanAssociatedWithCoilType;
    thread_local int pdchFanAssociatedVdotSize;
    thread_local int pdchFanAssociatedMdotSize;

    thread_local int pdchFanHeatGainIdealPeak;
    thread_local int pdchCoilNetTotalCapacityIdealPeak;

    thread_local int pdchCoilPlantLoopName;

    thread_local int pdchPlantMassFlowMaximum;
    thread_local int pdchPlantRetTempDesign;
    thread_local int pdchPlantSupTempDesign;
    thread_local int pdchPlantDeltaTempDesign;
    thread_local int pdchPlantCapacity;
    thread_local int pdchCoilCapPrcntPlantCapacity;
    thread_local int pdchCoilFlowPrcntPlantFlow;
    thread_local int pdchOADryBulbIdealPeak;
    thread_local int pdchOAHumRatIdealPeak;
    thread_local int pdchOAWetBulbatIdealPeak;
    thread_local int pdchOAVolFlowIdealPeak;
    thread_local int pdchOAFlowPrcntIdealPeak;
    thread_local int pdchOABarometricPressureIdealPeak;

    thread_local int pdchAirSysRADryBulbIdealPeak;
    thread_local int pdchAirSysRAHumRatIdealPeak;
    thread_local int pdchZoneAirDryBulbIdealPeak;
    thread_local int pdchZoneAirHumRatIdealPeak;
    thread_local int pdchZoneAirRelHumIdealPeak;
    thread_local int pdchCoilUA;
    thread_local int pdchZoneSensibleLoadIdealPeak;
    thread_local int pdchZoneLatentLoadIdealPeak;
    thread_local int pdchCoilIdealSizCapOverSimPeak;
    thread_local int pdchCoilIdealSizCapUnderSimPeak;
    thread_local int pdchReheatCoilMultiplier;
    thread_local int pdchFlowCapRatioLowCapIncreaseRatio;
    thread_local int pdchFlowCapRatioHiCapDecreaseRatio;
    thread_local int pdchPlantFluidSpecificHeat;
    thread_local int pdchPlantFluidDensity;
    thread_local int pdchMoistAirSpecificHeat;
    thread_local int pdchDryAirSpecificHeat;
    thread_local int pdchStandRhoAir;

    // Coil Sizing Summary (subset of Coil Selection Table)
    thread_local int pdst2CoilSummaryCoilSelection;
    thread_local int pdch2CoilName;
    thread_local int pdch2CoilType;
    thread_local int pdch2CoilHVACType;
    thread_local int pdch2CoilHVACName;

    thread_local int pdch2CoilFinalTotalCap;
    thread_local int pdch2CoilFinalSensCap;
    thread_local int pdch2CoilFinalAirVolFlowRate;
    thread_local int pdch2CoilFinalPlantVolFlowRate;
    thread_local int pdch2CoilUA;

    thread_local int pdch2CoilDDnameSensIdealPeak;
    thread_local int pdch2CoilDateTimeSensIdealPeak;
    thread_local int pdch2CoilDDnameAirFlowIdealPeak;
    thread_local int pdch2CoilDateTimeAirFlowIdealPeak;
    thread_local int pdch2CoilTotalCapIdealPeak;
    thread_local int pdch2CoilSensCapIdealPeak;
    thread_local int pdch2CoilAirVolumeFlowIdealPeak;
    thread_local int pdch2CoilEntDryBulbIdealPeak;
    thread_local int pdch2CoilEntWetBulbIdealPeak;
    thread_local int pdch2CoilEntHumRatIdealPeak;
    thread_local int pdch2CoilLvgDryBulbIdealPeak;
    thread_local int pdch2CoilLvgWetBulbIdealPeak;
    thread_local int pdch2CoilLvgHumRatIdealPeak;
    thread_local int pdch2CoilRatedTotalCap;
    thread_local int pdch2CoilRatedSensCap;

    thread_local int pdch2OADryBulbIdealPeak;
    thread_local int pdch2OAHumRatIdealPeak;
    thread_local int pdch2OAWetBulbatIdealPeak;
    thread_local int pdch2OAFlowPrcntIdealPeak;
    thread_local int pdch2ZoneAirDryBulbIdealPeak;
    thread_local int pdch2ZoneAirHumRatIdealPeak;
    thread_local int pdch2ZoneAirRelHumIdealPeak;
    thread_local int pdch2ZoneSensibleLoadIdealPeak;
    thread_local int pdch2ZoneLatentLoadIdealPeak;

    // System summary
    thread_local int pdrSystem;
    thread_local int pdstEconomizer;
    thread_local int pdchEcoKind;
    thread_local int pdchEcoMinOA;
    thread_local int pdchEcoMaxOA;
    thread_local int pdchEcoRetTemp;
    thread_local int pdchEcoRetEnth;
    thread_local int pdchEcoOATempLim;
    thread_local int pdchEcoOAEnthLim;
    thread_local int pdstDemCntlVent;
    thread_local int pdchDCVventMechName;
    thread_local int pdchDCVperPerson;
    thread_local int pdchDCVperArea;
    thread_local int pdchDCVperZone;
    thread_local int pdchDCVperACH;
    thread_local int pdchDCVMethod;
    thread_local int pdchDCVOASchName;

    // added for new DCV
    thread_local int pdchDCVZoneADEffCooling;
    thread_local int pdchDCVZoneADEffHeating;
    thread_local int pdchDCVZoneADEffSchName;

    thread_local int pdstSimpleComfort;
    thread_local int pdchSCwinterClothes;
    thread_local int pdchSCsummerClothes;
    thread_local int pdchSCeitherClothes;
    thread_local int pdstUnmetLoads;
    thread_local int pdchULnotMetHeat;
    thread_local int pdchULnotMetCool;
    thread_local int pdchULnotMetHeatOcc;
    thread_local int pdchULnotMetCoolOcc;

    // Outside Air Report
    thread_local int pdrOutsideAir;
    thread_local int pdstOAavgOcc;
    thread_local int pdchOaoAvgNumOcc1;
    thread_local int pdchOaoNomNumOcc1;
    thread_local int pdchOaoZoneVol1;
    thread_local int pdchOaoAvgMechVent;
    thread_local int pdchOaoAvgInfil;
    thread_local int pdchOaoAvgAFNInfil;
    thread_local int pdchOaoAvgSimpVent;
    thread_local int pdchOaoAvgTotVent;
    thread_local int pdstOAminOcc;
    thread_local int pdchOaoAvgNumOcc2;
    thread_local int pdchOaoNomNumOcc2;
    thread_local int pdchOaoZoneVol2;
    thread_local int pdchOaoMinMechVent;
    thread_local int pdchOaoMinInfil;
    thread_local int pdchOaoMinAFNInfil;
    thread_local int pdchOaoMinSimpVent;
    thread_local int pdchOaoMinTotVent;

    // Object Count Report
    thread_local int pdrObjCnt;
    thread_local int pdstSurfCnt;
    thread_local int pdchSurfCntTot;
    thread_local int pdchSurfCntExt;
    thread_local int pdstHVACcnt;
    thread_local int pdchHVACcntVal;
    thread_local int pdstFieldCnt;
    thread_local int pdchFieldCntVal;

    // Energy Meters Report
    thread_local int pdrEnergyMeters;

    thread_local int pdstEMelecvalues;
    thread_local int pdchEMelecannual;
    thread_local int pdchEMelecminvalue;
    thread_local int pdchEMelecminvaluetime;
    thread_local int pdchEMelecmaxvalue;
    thread_local int pdchEMelecmaxvaluetime;

    thread_local int pdstEMgasvalues;
    thread_local int pdchEMgasannual;
    thread_local int pdchEMgasminvalue;
    thread_local int pdchEMgasminvaluetime;
    thread_local int pdchEMgasmaxvalue;
    thread_local int pdchEMgasmaxvaluetime;

    thread_local int pdstEMcoolvalues;
    thread_local int pdchEMcoolannual;
    thread_local int pdchEMcoolminvalue;
    thread_local int pdchEMcoolminvaluetime;
    thread_local int pdchEMcoolmaxvalue;
    thread_local int pdchEMcoolmaxvaluetime;

    thread_local int pdstEMwatervalues;
    thread_local int pdchEMwaterannual;
    thread_local int pdchEMwaterminvalue;
    thread_local int pdchEMwaterminvaluetime;
    thread_local int pdchEMwatermaxvalue;
    thread_local int pdchEMwatermaxvaluetime;

    thread_local int pdstEMotherJvalues;
    thread_local int pdchEMotherJannual;
    thread_local int pdchEMotherJminvalue;
    thread_local int pdchEMotherJminvaluetime;
    thread_local int pdchEMotherJmaxvalue;
    thread_local int pdchEMotherJmaxvaluetime;

    thread_local int pdstEMotherKGvalues;
    thread_local int pdchEMotherKGannual;
    thread_local int pdchEMotherKGminvalue;
    thread_local int pdchEMotherKGminvaluetime;
    thread_local int pdchEMotherKGmaxvalue;
    thread_local int pdchEMotherKGmaxvaluetime;

    thread_local int pdstEMotherM3values;
    thread_local int pdchEMotherM3annual;
    thread_local int pdchEMotherM3minvalue;
    thread_local int pdchEMotherM3minvaluetime;
    thread_local int pdchEMotherM3maxvalue;
    thread_local int pdchEMotherM3maxvaluetime;

    thread_local int pdstEMotherLvalues;
    thread_local int pdchEMotherLannual;
    thread_local int pdchEMotherLminvalue;
    thread_local int pdchEMotherLminvaluetime;
    thread_local int pdchEMotherLmaxvalue;
    thread_local int pdchEMotherLmaxvaluetime;

    // Sensible Heat Gas Component Report
    thread_local int pdrSensibleGain;
    // annual
    thread_local int pdstSHGSannual;
    thread_local int pdchSHGSAnHvacHt;
    thread_local int pdchSHGSAnHvacCl;
    thread_local int pdchSHGSAnHvacATUHt;
    thread_local int pdchSHGSAnHvacATUCl;
    thread_local int pdchSHGSAnSurfHt;
    thread_local int pdchSHGSAnSurfCl;
    thread_local int pdchSHGSAnPeoplAdd;
    thread_local int pdchSHGSAnLiteAdd;
    thread_local int pdchSHGSAnEquipAdd;
    thread_local int pdchSHGSAnWindAdd;
    thread_local int pdchSHGSAnIzaAdd;
    thread_local int pdchSHGSAnInfilAdd;
    thread_local int pdchSHGSAnOtherAdd;
    thread_local int pdchSHGSAnEquipRem;
    thread_local int pdchSHGSAnWindRem;
    thread_local int pdchSHGSAnIzaRem;
    thread_local int pdchSHGSAnInfilRem;
    thread_local int pdchSHGSAnOtherRem;
    // peak cooling
    thread_local int pdstSHGSpkCl;
    thread_local int pdchSHGSClTimePeak;
    thread_local int pdchSHGSClHvacHt;
    thread_local int pdchSHGSClHvacCl;
    thread_local int pdchSHGSClHvacATUHt;
    thread_local int pdchSHGSClHvacATUCl;
    thread_local int pdchSHGSClSurfHt;
    thread_local int pdchSHGSClSurfCl;
    thread_local int pdchSHGSClPeoplAdd;
    thread_local int pdchSHGSClLiteAdd;
    thread_local int pdchSHGSClEquipAdd;
    thread_local int pdchSHGSClWindAdd;
    thread_local int pdchSHGSClIzaAdd;
    thread_local int pdchSHGSClInfilAdd;
    thread_local int pdchSHGSClOtherAdd;
    thread_local int pdchSHGSClEquipRem;
    thread_local int pdchSHGSClWindRem;
    thread_local int pdchSHGSClIzaRem;
    thread_local int pdchSHGSClInfilRem;
    thread_local int pdchSHGSClOtherRem;
    // peak heating
    thread_local int pdstSHGSpkHt;
    thread_local int pdchSHGSHtTimePeak;
    thread_local int pdchSHGSHtHvacHt;
    thread_local int pdchSHGSHtHvacCl;
    thread_local int pdchSHGSHtHvacATUHt;
    thread_local int pdchSHGSHtHvacATUCl;
    thread_local int pdchSHGSHtSurfHt;
    thread_local int pdchSHGSHtSurfCl;
    thread_local int pdchSHGSHtPeoplAdd;
    thread_local int pdchSHGSHtLiteAdd;
    thread_local int pdchSHGSHtEquipAdd;
    thread_local int pdchSHGSHtWindAdd;
    thread_local int pdchSHGSHtIzaAdd;
    thread_local int pdchSHGSHtInfilAdd;
    thread_local int pdchSHGSHtOtherAdd;
    thread_local int pdchSHGSHtEquipRem;
    thread_local int pdchSHGSHtWindRem;
    thread_local int pdchSHGSHtIzaRem;
    thread_local int pdchSHGSHtInfilRem;
    thread_local int pdchSHGSHtOtherRem;
    // Standard62Report
    thread_local int pdrStd62;
    thread_local int pdstS62sysVentReqCool;
    thread_local int pdchS62svrClSumVpz;
    thread_local int pdchS62svrClPs;
    thread_local int pdchS62svrClSumPz;
    thread_local int pdchS62svrClD;
    thread_local int pdchS62svrClVou;
    thread_local int pdchS62svrClVps;
    thread_local int pdchS62svrClXs;
    thread_local int pdchS62svrClEv;
    thread_local int pdchS62svrClVot;
    thread_local int pdchS62svrClPercOA;
    thread_local int pdchS62svrClEnvironmentOfPs;
    thread_local int pdchS62svrClTimeOfPs;

    thread_local int pdstS62sysVentReqHeat;
    thread_local int pdchS62svrHtSumVpz;
    thread_local int pdchS62svrHtPs;
    thread_local int pdchS62svrHtSumPz;
    thread_local int pdchS62svrHtD;
    thread_local int pdchS62svrHtVou;
    thread_local int pdchS62svrHtVps;
    thread_local int pdchS62svrHtXs;
    thread_local int pdchS62svrHtEv;
    thread_local int pdchS62svrHtVot;
    thread_local int pdchS62svrHtPercOA;
    thread_local int pdchS62svrHtEnvironmentOfPs;
    thread_local int pdchS62svrHtTimeOfPs;

    thread_local int pdstS62znVentPar;
    thread_local int pdchS62zvpAlN;
    thread_local int pdchS62zvpRp;
    thread_local int pdchS62zvpPz;
    thread_local int pdchS62zvpRa;
    thread_local int pdchS62zvpAz;
    thread_local int pdchS62zvpVbz;
    thread_local int pdchS62zvpClEz;
    thread_local int pdchS62zvpClVoz;
    thread_local int pdchS62zvpHtEz;
    thread_local int pdchS62zvpHtVoz;

    thread_local int pdstS62sysVentPar;
    thread_local int pdchS62svpRp;
    thread_local int pdchS62svpPz;
    thread_local int pdchS62svpRa;
    thread_local int pdchS62svpAz;
    thread_local int pdchS62svpVbz;
    thread_local int pdchS62svpClVoz;
    thread_local int pdchS62svpHtVoz;

    thread_local int pdstS62znCoolDes;
    thread_local int pdchS62zcdAlN;
    thread_local int pdchS62zcdBox;
    thread_local int pdchS62zcdVpz;
    thread_local int pdchS62zcdVps;
    thread_local int pdchS62zcdVsec;
    thread_local int pdchS62zcdVdz;
    thread_local int pdchS62zcdVpzmin;
    thread_local int pdchS62zcdVozclg;
    thread_local int pdchS62zcdZpz;
    thread_local int pdchS62zcdEp;
    thread_local int pdchS62zcdEr;
    thread_local int pdchS62zcdFa;
    thread_local int pdchS62zcdFb;
    thread_local int pdchS62zcdFc;
    thread_local int pdchS62zcdEvz;

    thread_local int pdstS62sysCoolDes;
    thread_local int pdchS62scdVpz;
    thread_local int pdchS62scdVps;
    thread_local int pdchS62scdVsec;
    thread_local int pdchS62scdVdz;
    thread_local int pdchS62scdVpzmin;
    thread_local int pdchS62scdVozclg;
    thread_local int pdchS62scdEvz;

    thread_local int pdstS62znHeatDes;
    thread_local int pdchS62zhdAlN;
    thread_local int pdchS62zhdBox;
    thread_local int pdchS62zhdVpz;
    thread_local int pdchS62zhdVps;
    thread_local int pdchS62zhdVsec;
    thread_local int pdchS62zhdVdz;
    thread_local int pdchS62zhdVpzmin;
    thread_local int pdchS62zhdVozhtg;
    thread_local int pdchS62zhdZpz;
    thread_local int pdchS62zhdEp;
    thread_local int pdchS62zhdEr;
    thread_local int pdchS62zhdFa;
    thread_local int pdchS62zhdFb;
    thread_local int pdchS62zhdFc;
    thread_local int pdchS62zhdEvz;

    thread_local int pdstS62sysHeatDes;
    thread_local int pdchS62shdVpz;
    thread_local int pdchS62shdVps;
    thread_local int pdchS62shdVsec;
    thread_local int pdchS62shdVdz;
    thread_local int pdchS62shdVpzmin;
    thread_local int pdchS62shdVozhtg;
    thread_local int pdchS62shdEvz;

    //  LEED Summary
    thread_local int pdrLeed;
    thread_local int pdstLeedGenInfo;
    thread_local int pdchLeedGenData;

    thread_local int pdstLeedSpaceUsageType;
    thread_local int pdchLeedSutName;
    thread_local int pdchLeedSutSpArea;
    thread_local int pdchLeedSutOcArea;
    thread_local int pdchLeedSutUnArea;
    thread_local int pdchLeedSutHrsWeek;

    thread_local int pdstLeedAdvsMsg;
    thread_local int pdchLeedAmData;

    thread_local int pdstLeedEneTypSum;
    thread_local int pdchLeedEtsType;
    thread_local int pdchLeedEtsRtNm;
    thread_local int pdchLeedEtsVirt;
    thread_local int pdchLeedEtsEneUnt;
    thread_local int pdchLeedEtsDemUnt;

    thread_local int pdstLeedPerf;
    thread_local int pdchLeedPerfRot;
    thread_local int pdchLeedPerfElEneUse;
    thread_local int pdchLeedPerfElDem;
    thread_local int pdchLeedPerfGasEneUse;
    thread_local int pdchLeedPerfGasDem;
    thread_local int pdchLeedPerfAddFuelEneUse;
    thread_local int pdchLeedPerfAddFuelDem;
    thread_local int pdchLeedPerfDisClEneUse;
    thread_local int pdchLeedPerfDisClDem;
    thread_local int pdchLeedPerfDisHtEneUse;
    thread_local int pdchLeedPerfDisHtDem;

    thread_local int pdstLeedEneUseSum;
    thread_local int pdchLeedEusUnt;
    thread_local int pdchLeedEusProc;
    thread_local int pdchLeedEusTotal;

    thread_local int pdstLeedEneCostSum;
    thread_local int pdchLeedEcUnt;
    thread_local int pdchLeedEcsProc;
    thread_local int pdchLeedEcsTotal;
    thread_local Real64 LEEDelecCostTotal;
    thread_local Real64 LEEDgasCostTotal;
    thread_local Real64 LEEDothrCostTotal;

    thread_local int pdstLeedRenewSum;
    thread_local int pdchLeedRenRatCap;
    thread_local int pdchLeedRenAnGen;

    thread_local int pdstLeedEneUseIntEl;
    thread_local int pdchLeedEuiElec;
    thread_local int pdstLeedEneUseIntNatG;
    thread_local int pdchLeedEuiNatG;
    thread_local int pdstLeedEneUseIntOthr;
    thread_local int pdchLeedEuiOthr;

    thread_local int pdstLeedEneUsePerc;
    thread_local int pdchLeedEupPerc;

    thread_local int pdstLeedEqFlLdHrs;
    thread_local int pdchLeedEflhEflh;
    thread_local int pdchLeedEflhNonZerHrs;

    thread_local int pdstLeedSchedSetPts;
    thread_local int pdChLeedSchStPtFirstObjUsed;
    thread_local int pdChLeedSchStPtMonthUsed;
    thread_local int pdchLeedSchStPt11amWednesday;
    thread_local int pdchLeedSchStPt11amWedCnt;
    thread_local int pdchLeedSchStPt11pmWednesday;
    thread_local int pdchLeedSchStPt11pmWedCnt;

    // Internal data structures to store information provided by calls

    thread_local int const sizeIncrement(100);

    thread_local int sizeReportName;
    thread_local int numReportName;

    thread_local int sizeSubTable;
    thread_local int numSubTable;

    thread_local int sizeColumnTag;
    thread_local int numColumnTag;

    thread_local int sizeTableEntry;
    thread_local int numTableEntry;

    thread_local int sizeCompSizeTableEntry(0); // Autodesk Was used uninitialized in output to .audit files
    thread_local int numCompSizeTableEntry(0);  // Autodesk Was used uninitialized in WriteComponentSizing

    thread_local int sizeShadowRelate;
    thread_local int numShadowRelate;
    thread_local int const recKindSurface(1);
    thread_local int const recKindSubsurface(2);

    thread_local Real64 TotalNotMetHeatingOccupiedForABUPS(0.0);
    thread_local Real64 TotalNotMetCoolingOccupiedForABUPS(0.0);
    thread_local Real64 TotalNotMetOccupiedForABUPS(0.0);
    thread_local Real64 TotalTimeNotSimpleASH55EitherForABUPS(0.0);

    // Object Data
    thread_local Array1D<reportNameType> reportName;
    thread_local Array1D<SubTableType> subTable;
    thread_local Array1D<ColumnTagType> columnTag;
    thread_local Array1D<TableEntryType> tableEntry;
    thread_local Array1D<CompSizeTableEntryType> CompSizeTableEntry;
    thread_local Array1D<ShadowRelateType> ShadowRelate;

    // Functions
    void clear_state()
    {
        pdrClim = 0;
        pdstDesDay = 0;
        pdchDDmaxDB = 0;
        pdchDDrange = 0;
        pdchDDhumid = 0;
        pdchDDhumTyp = 0;
        pdchDDwindSp = 0;
        pdchDDwindDr = 0;
        pdstWthr = 0;
        pdchWthrVal = 0;
        pdrEquip = 0;
        pdstMech = 0;
        pdchMechType = 0;
        pdchMechNomCap = 0;
        pdchMechNomEff = 0;
        pdchMechIPLVSI = 0;
        pdchMechIPLVIP = 0;
        pdstFan = 0;
        pdchFanType = 0;
        pdchFanTotEff = 0;
        pdchFanDeltaP = 0;
        pdchFanVolFlow = 0;
        pdchFanMotorIn = 0;
        pdchFanEnergyIndex = 0;
        pdchFanEndUse = 0;
        pdchFanPwr = 0;
        pdchFanPwrPerFlow = 0;
        pdchFanDesDay = 0;
        pdchFanPkTime = 0;
        pdstPump = 0;
        pdchPumpType = 0;
        pdchPumpControl = 0;
        pdchPumpHead = 0;
        pdchPumpFlow = 0;
        pdchPumpPower = 0;
        pdchPumpPwrPerFlow = 0;
        pdchMotEff = 0;
        pdstCoolCoil = 0;
        pdchCoolCoilType = 0;
        pdchCoolCoilDesCap = 0;
        pdchCoolCoilTotCap = 0;
        pdchCoolCoilSensCap = 0;
        pdchCoolCoilLatCap = 0;
        pdchCoolCoilSHR = 0;
        pdchCoolCoilNomEff = 0;
        pdchCoolCoilUATotal = 0;
        pdchCoolCoilArea = 0;
        pdstDXCoolCoil = 0;
        pdchDXCoolCoilType = 0;     // DX cooling coil type
        pdchDXCoolCoilNetCapSI = 0; // Standard Rated (Net) Cooling Capacity [W]
        pdchDXCoolCoilCOP = 0;      // EER/COP value in SI unit at AHRI std. 340/360 conditions [W/W]
        pdchDXCoolCoilSEERIP = 0;   // SEER value in IP unit at AHRI std. 210/240 conditions [Btu/W-hr]
        pdchDXCoolCoilEERIP = 0;    // EER value in IP unit at AHRI std. 340/360 conditions [Btu/W-h]
        pdchDXCoolCoilIEERIP = 0;   // IEER value in IP unit at AHRI std. 340/360 conditions
        pdstDXCoolCoil2 = 0;
        pdchDXCoolCoilNetCapSIA = 0;  // Standard Rated (Net) Cooling Capacity [W], Test A
        pdchDXCoolCoilElecPowerA = 0; // Standard Rated Electric Power [W], Test A
        pdchDXCoolCoilNetCapSIB = 0;  // Standard Rated (Net) Cooling Capacity [W], Test B
        pdchDXCoolCoilElecPowerB = 0; // Standard Rated Electric Power [W], Test B
        pdchDXCoolCoilNetCapSIC = 0;  // Standard Rated (Net) Cooling Capacity [W], Test C
        pdchDXCoolCoilElecPowerC = 0; // Standard Rated Electric Power [W], Test C
        pdchDXCoolCoilNetCapSID = 0;  // Standard Rated (Net) Cooling Capacity [W], Test D
        pdchDXCoolCoilElecPowerD = 0; // Standard Rated Electric Power [W], Test D
        pdstVAVDXCoolCoil = 0;        // details for Packaged VAV rating under AHRI 340/360
        pdchVAVDXCoolCoilType = 0;
        pdchVAVDXFanName = 0;
        pdchVAVDXCoolCoilNetCapSI = 0;
        pdchVAVDXCoolCoilCOP = 0;
        pdchVAVDXCoolCoilIEERIP = 0;
        pdchVAVDXCoolCoilEERIP = 0;
        pdchVAVDXCoolCoilMdotA = 0;
        pdchVAVDXCoolCoilCOP_B = 0;
        pdchVAVDXCoolCoilEER_B_IP = 0;
        pdchVAVDXCoolCoilMdotB = 0;
        pdchVAVDXCoolCoilCOP_C = 0;
        pdchVAVDXCoolCoilEER_C_IP = 0;
        pdchVAVDXCoolCoilMdotC = 0;
        pdchVAVDXCoolCoilCOP_D = 0;
        pdchVAVDXCoolCoilEER_D_IP = 0;
        pdchVAVDXCoolCoilMdotD = 0;
        pdstDXHeatCoil = 0;
        pdchDXHeatCoilType = 0; // DX Heating coil type
        pdchDXHeatCoilHighCap = 0;
        pdchDXHeatCoilLowCap = 0;
        pdchDXHeatCoilHSPFSI = 0;    // HSPF value in SI unit at AHRI std. 340/360 conditions [W/W]
        pdchDXHeatCoilHSPFIP = 0;    // HSPF value in IP unit at AHRI std. 340/360 conditions [Btu/W-hr]
        pdchDXHeatCoilRegionNum = 0; // Region number for which HSPF is calculated
        pdstHeatCoil = 0;
        pdchHeatCoilType = 0;
        pdchHeatCoilDesCap = 0;
        pdchHeatCoilNomCap = 0;
        pdchHeatCoilNomEff = 0;
        pdstSWH = 0;
        pdchSWHType = 0;
        pdchSWHVol = 0;
        pdchSWHHeatIn = 0;
        pdchSWHThEff = 0;
        pdchSWHRecEff = 0;
        pdchSWHEnFac = 0;
        pdrEnvelope = 0;
        pdstOpaque = 0;
        pdchOpCons = 0;
        pdchOpRefl = 0;
        pdchOpUfactFilm = 0;
        pdchOpUfactNoFilm = 0;
        pdchOpGrArea = 0;
        pdchOpNetArea = 0;
        pdchOpAzimuth = 0;
        pdchOpTilt = 0;
        pdchOpDir = 0;
        pdstFen = 0;
        pdchFenCons = 0;
        pdchFenAreaOf1 = 0;
        pdchFenGlassAreaOf1 = 0;
        pdchFenFrameAreaOf1 = 0;
        pdchFenDividerAreaOf1 = 0;
        pdchFenArea = 0;
        pdchFenUfact = 0;
        pdchFenSHGC = 0;
        pdchFenVisTr = 0;
        pdchFenFrameConductance = 0;
        pdchFenDividerConductance = 0;
        pdchFenSwitchable = 0;
        pdchFenParent = 0;
        pdchFenAzimuth = 0;
        pdchFenTilt = 0;
        pdchFenDir = 0;
        pdstDoor = 0;
        pdchDrCons = 0;
        pdchDrUfactFilm = 0;
        pdchDrUfactNoFilm = 0;
        pdchDrGrArea = 0;
        pdchDrParent = 0;
        pdstIntFen = 0;
        pdchIntFenCons = 0;
        pdchIntFenAreaOf1 = 0;
        pdchIntFenArea = 0;
        pdchIntFenUfact = 0;
        pdchIntFenSHGC = 0;
        pdchIntFenVisTr = 0;
        pdchIntFenParent = 0;
        pdrShading = 0;
        pdstSunlitFrac = 0;
        pdchSlfMar21_9 = 0;
        pdchSlfMar21_12 = 0;
        pdchSlfMar21_15 = 0;
        pdchSlfJun21_9 = 0;
        pdchSlfJun21_12 = 0;
        pdchSlfJun21_15 = 0;
        pdchSlfDec21_9 = 0;
        pdchSlfDec21_12 = 0;
        pdchSlfDec21_15 = 0;
        pdstWindowControl = 0;
        pdchWscName = 0;
        pdchWscShading = 0;
        pdchWscShadCons = 0;
        pdchWscControl = 0;
        pdchWscGlare = 0;
        pdrLighting = 0;
        pdstInLite = 0;
        pdchInLtZone = 0;
        pdchInLtDens = 0;
        pdchInLtArea = 0;
        pdchInLtPower = 0;
        pdchInLtEndUse = 0;
        pdchInLtSchd = 0;
        pdchInLtAvgHrSchd = 0;
        pdchInLtAvgHrOper = 0;
        pdchInLtFullLoadHrs = 0;
        pdchInLtRetAir = 0;
        pdchInLtCond = 0;
        pdchInLtConsump = 0;
        pdstExtLite = 0;
        pdchExLtPower = 0;
        pdchExLtClock = 0;
        pdchExLtSchd = 0;
        pdchExLtAvgHrSchd = 0;
        pdchExLtAvgHrOper = 0;
        pdchExLtFullLoadHrs = 0;
        pdchExLtConsump = 0;
        pdstDaylight = 0;
        pdchDyLtZone = 0;
        pdchDyLtCtrlName = 0;
        pdchDyLtKind = 0;
        pdchDyLtCtrlType = 0;
        pdchDyLtFrac = 0;
        pdchDyLtWInst = 0;
        pdchDyLtWCtrl = 0;
        pdrSizing = 0;
        pdstZoneClSize = 0;
        pdchZnClCalcDesLd = 0;
        pdchZnClUserDesLd = 0;
        pdchZnClUserDesLdPerArea = 0;
        pdchZnClCalcDesAirFlow = 0;
        pdchZnClUserDesAirFlow = 0;
        pdchZnClDesDay = 0;
        pdchZnClPkTime = 0;
        pdchZnClPkTstatTemp = 0;
        pdchZnClPkIndTemp = 0;
        pdchZnClPkIndHum = 0;
        pdchZnClPkOATemp = 0;
        pdchZnClPkOAHum = 0;
        pdstZoneHtSize = 0;
        pdchZnHtCalcDesLd = 0;
        pdchZnHtUserDesLd = 0;
        pdchZnHtUserDesLdPerArea = 0;
        pdchZnHtCalcDesAirFlow = 0;
        pdchZnHtUserDesAirFlow = 0;
        pdchZnHtDesDay = 0;
        pdchZnHtPkTime = 0;
        pdchZnHtPkTstatTemp = 0;
        pdchZnHtPkIndTemp = 0;
        pdchZnHtPkIndHum = 0;
        pdchZnHtPkOATemp = 0;
        pdchZnHtPkOAHum = 0;
        pdstSystemSize = 0;
        pdchSysSizCalcClAir = 0;
        pdchSysSizUserClAir = 0;
        pdchSysSizCalcHtAir = 0;
        pdchSysSizUserHtAir = 0;
        pdchSysSizAdjustedClAir = 0;
        pdchSysSizAdjustedHtAir = 0;
        pdchSysSizAdjustedMainAir = 0;
        pdchSysSizCalcHeatFlowRatio = 0;
        pdchSysSizUserHeatFlowRatio = 0;
        pdstPlantSize = 0;
        pdchPlantSizCalcVdot = 0;
        pdchPlantSizMeasVdot = 0;
        pdchPlantSizPrevVdot = 0;
        pdchPlantSizCoincYesNo = 0;
        pdchPlantSizDesDay = 0;
        pdchPlantSizPkTimeHour = 0;
        pdchPlantSizPkTimeDayOfSim = 0;
        pdchPlantSizPkTimeMin = 0;

        pdrCoilSizingDetailsTable = 0;
        pdstCoilSummaryCoilSelection = 0;
        pdchCoilLocation = 0;
        pdchCoilHVACType = 0;
        pdchCoilHVACName = 0;
        pdchCoilZoneName = 0;
        pdchCoilName = 0;
        pdchCoilType = 0;
        pdchSysSizingMethCoinc = 0;
        pdchSysSizingMethCap = 0;
        pdchSysSizingMethAir = 0;
        pdchCoilIsCapAutosized = 0;
        pdchCoilIsAirFlowAutosized = 0;
        pdchCoilIsWaterFlowAutosized = 0;
        pdchCoilIsOATreated = 0;
        pdchCoilFinalTotalCap = 0;
        pdchCoilFinalSensCap = 0;
        pdchCoilFinalAirVolFlowRate = 0;
        pdchCoilFinalPlantVolFlowRate = 0;
        pdchCoilDDnameSensIdealPeak = 0;
        pdchCoilDateTimeSensIdealPeak = 0;
        pdchCoilDDnameTotIdealPeak = 0;
        pdchCoilDateTimeTotIdealPeak = 0;
        pdchCoilDDnameAirFlowIdealPeak = 0;
        pdchCoilDateTimeAirFlowIdealPeak = 0;
        pdchCoilTotalCapIdealPeak = 0;
        pdchCoilSensCapIdealPeak = 0;
        pdchCoilAirMassFlowIdealPeak = 0;
        pdchCoilAirVolumeFlowIdealPeak = 0;
        pdchCoilEntDryBulbIdealPeak = 0;
        pdchCoilEntWetBulbIdealPeak = 0;
        pdchCoilEntHumRatIdealPeak = 0;
        pdchCoilEntEnthalpyIdealPeak = 0;
        pdchCoilLvgDryBulbIdealPeak = 0;
        pdchCoilLvgWetBulbIdealPeak = 0;
        pdchCoilLvgHumRatIdealPeak = 0;
        pdchCoilLvgEnthalpyIdealPeak = 0;
        pdchCoilWaterMassFlowIdealPeak = 0;
        pdchCoilEntWaterTempIdealPeak = 0;
        pdchCoilLvgWaterTempIdealPeak = 0;
        pdchCoilWaterDeltaTempIdealPeak = 0;
        pdchCoilRatedTotalCap = 0;
        pdchCoilRatedSensCap = 0;
        pdchCoilOffRatingCapacityModifierIdealPeak = 0;

        pdchCoilRatedAirMass = 0;
        pdchCoilRatedEntDryBulb = 0;
        pdchCoilRatedEntWetBulb = 0;
        pdchCoilRatedEntHumRat = 0;
        pdchCoilRatedEntEnthalpy = 0;
        pdchCoilRatedLvgDryBulb = 0;
        pdchCoilRatedLvgWetBulb = 0;
        pdchCoilRatedLvgHumRat = 0;
        pdchCoilRatedLvgEnthalpy = 0;
        pdchCoilRatedWaterMass = 0;
        pdchCoilRatedEntWaterTemp = 0;
        pdchCoilRatedLvgWaterTemp = 0;
        pdchCoilRatedWaterDeltaTemp = 0;

        pdchFanAssociatedWithCoilName = 0;
        pdchFanAssociatedWithCoilType = 0;
        pdchFanAssociatedVdotSize = 0;
        pdchFanAssociatedMdotSize = 0;

        pdchFanHeatGainIdealPeak = 0;
        pdchCoilNetTotalCapacityIdealPeak = 0;

        pdchCoilPlantLoopName = 0;

        pdchPlantMassFlowMaximum = 0;
        pdchPlantRetTempDesign = 0;
        pdchPlantSupTempDesign = 0;
        pdchPlantDeltaTempDesign = 0;
        pdchPlantCapacity = 0;
        pdchCoilCapPrcntPlantCapacity = 0;
        pdchCoilFlowPrcntPlantFlow = 0;
        pdchOADryBulbIdealPeak = 0;
        pdchOAWetBulbatIdealPeak = 0;
        pdchOAHumRatIdealPeak = 0;
        pdchOAVolFlowIdealPeak = 0;
        pdchOAFlowPrcntIdealPeak = 0;
        pdchAirSysRADryBulbIdealPeak = 0;
        pdchAirSysRAHumRatIdealPeak = 0;
        pdchZoneAirDryBulbIdealPeak = 0;
        pdchZoneAirHumRatIdealPeak = 0;
        pdchZoneAirRelHumIdealPeak = 0;
        pdchCoilUA = 0;
        pdchZoneSensibleLoadIdealPeak = 0;
        pdchZoneLatentLoadIdealPeak = 0;

        pdchReheatCoilMultiplier = 0;
        pdchFlowCapRatioLowCapIncreaseRatio = 0;
        pdchFlowCapRatioHiCapDecreaseRatio = 0;
        pdchPlantFluidSpecificHeat = 0;
        pdchPlantFluidDensity = 0;
        pdchMoistAirSpecificHeat = 0;
        pdchDryAirSpecificHeat = 0;
        pdchStandRhoAir = 0;

        // Coil Sizing Summary (subset of Coil Selection Table)
        pdst2CoilSummaryCoilSelection = 0;
        pdch2CoilName = 0;
        pdch2CoilType = 0;
        pdch2CoilHVACType = 0;
        pdch2CoilHVACName = 0;

        pdch2CoilFinalTotalCap = 0;
        pdch2CoilFinalSensCap = 0;
        pdch2CoilFinalAirVolFlowRate = 0;
        pdch2CoilFinalPlantVolFlowRate = 0;
        pdch2CoilUA = 0;

        pdch2CoilDDnameSensIdealPeak = 0;
        pdch2CoilDateTimeSensIdealPeak = 0;
        pdch2CoilDDnameAirFlowIdealPeak = 0;
        pdch2CoilDateTimeAirFlowIdealPeak = 0;
        pdch2CoilTotalCapIdealPeak = 0;
        pdch2CoilSensCapIdealPeak = 0;
        pdch2CoilAirVolumeFlowIdealPeak = 0;
        pdch2CoilEntDryBulbIdealPeak = 0;
        pdch2CoilEntWetBulbIdealPeak = 0;
        pdch2CoilEntHumRatIdealPeak = 0;
        pdch2CoilLvgDryBulbIdealPeak = 0;
        pdch2CoilLvgWetBulbIdealPeak = 0;
        pdch2CoilLvgHumRatIdealPeak = 0;
        pdch2CoilRatedTotalCap = 0;
        pdch2CoilRatedSensCap = 0;

        pdch2OADryBulbIdealPeak = 0;
        pdch2OAHumRatIdealPeak = 0;
        pdch2OAWetBulbatIdealPeak = 0;
        pdch2OAFlowPrcntIdealPeak = 0;
        pdch2ZoneAirDryBulbIdealPeak = 0;
        pdch2ZoneAirHumRatIdealPeak = 0;
        pdch2ZoneAirRelHumIdealPeak = 0;
        pdch2ZoneSensibleLoadIdealPeak = 0;
        pdch2ZoneLatentLoadIdealPeak = 0;

        pdrSystem = 0;
        pdstEconomizer = 0;
        pdchEcoKind = 0;
        pdchEcoMinOA = 0;
        pdchEcoMaxOA = 0;
        pdchEcoRetTemp = 0;
        pdchEcoRetEnth = 0;
        pdchEcoOATempLim = 0;
        pdchEcoOAEnthLim = 0;
        pdstDemCntlVent = 0;
        pdchDCVventMechName = 0;
        pdchDCVperPerson = 0;
        pdchDCVperArea = 0;
        pdchDCVperZone = 0;
        pdchDCVperACH = 0;
        pdchDCVMethod = 0;
        pdchDCVOASchName = 0;
        pdchDCVZoneADEffCooling = 0;
        pdchDCVZoneADEffHeating = 0;
        pdchDCVZoneADEffSchName = 0;
        pdstSimpleComfort = 0;
        pdchSCwinterClothes = 0;
        pdchSCsummerClothes = 0;
        pdchSCeitherClothes = 0;
        pdstUnmetLoads = 0;
        pdchULnotMetHeat = 0;
        pdchULnotMetCool = 0;
        pdchULnotMetHeatOcc = 0;
        pdchULnotMetCoolOcc = 0;
        pdrOutsideAir = 0;
        pdstOAavgOcc = 0;
        pdchOaoAvgNumOcc1 = 0;
        pdchOaoNomNumOcc1 = 0;
        pdchOaoZoneVol1 = 0;
        pdchOaoAvgMechVent = 0;
        pdchOaoAvgInfil = 0;
        pdchOaoAvgAFNInfil = 0;
        pdchOaoAvgSimpVent = 0;
        pdchOaoAvgTotVent = 0;
        pdstOAminOcc = 0;
        pdchOaoAvgNumOcc2 = 0;
        pdchOaoNomNumOcc2 = 0;
        pdchOaoZoneVol2 = 0;
        pdchOaoMinMechVent = 0;
        pdchOaoMinInfil = 0;
        pdchOaoMinAFNInfil = 0;
        pdchOaoMinSimpVent = 0;
        pdchOaoMinTotVent = 0;
        pdrObjCnt = 0;
        pdstSurfCnt = 0;
        pdchSurfCntTot = 0;
        pdchSurfCntExt = 0;
        pdstHVACcnt = 0;
        pdchHVACcntVal = 0;
        pdstFieldCnt = 0;
        pdchFieldCntVal = 0;
        pdrEnergyMeters = 0;
        pdstEMelecvalues = 0;
        pdchEMelecannual = 0;
        pdchEMelecminvalue = 0;
        pdchEMelecminvaluetime = 0;
        pdchEMelecmaxvalue = 0;
        pdchEMelecmaxvaluetime = 0;
        pdstEMgasvalues = 0;
        pdchEMgasannual = 0;
        pdchEMgasminvalue = 0;
        pdchEMgasminvaluetime = 0;
        pdchEMgasmaxvalue = 0;
        pdchEMgasmaxvaluetime = 0;
        pdstEMcoolvalues = 0;
        pdchEMcoolannual = 0;
        pdchEMcoolminvalue = 0;
        pdchEMcoolminvaluetime = 0;
        pdchEMcoolmaxvalue = 0;
        pdchEMcoolmaxvaluetime = 0;
        pdstEMwatervalues = 0;
        pdchEMwaterannual = 0;
        pdchEMwaterminvalue = 0;
        pdchEMwaterminvaluetime = 0;
        pdchEMwatermaxvalue = 0;
        pdchEMwatermaxvaluetime = 0;
        pdstEMotherJvalues = 0;
        pdchEMotherJannual = 0;
        pdchEMotherJminvalue = 0;
        pdchEMotherJminvaluetime = 0;
        pdchEMotherJmaxvalue = 0;
        pdchEMotherJmaxvaluetime = 0;
        pdstEMotherKGvalues = 0;
        pdchEMotherKGannual = 0;
        pdchEMotherKGminvalue = 0;
        pdchEMotherKGminvaluetime = 0;
        pdchEMotherKGmaxvalue = 0;
        pdchEMotherKGmaxvaluetime = 0;
        pdstEMotherM3values = 0;
        pdchEMotherM3annual = 0;
        pdchEMotherM3minvalue = 0;
        pdchEMotherM3minvaluetime = 0;
        pdchEMotherM3maxvalue = 0;
        pdchEMotherM3maxvaluetime = 0;
        pdstEMotherLvalues = 0;
        pdchEMotherLannual = 0;
        pdchEMotherLminvalue = 0;
        pdchEMotherLminvaluetime = 0;
        pdchEMotherLmaxvalue = 0;
        pdchEMotherLmaxvaluetime = 0;
        pdrSensibleGain = 0;
        pdstSHGSannual = 0;
        pdchSHGSAnHvacHt = 0;
        pdchSHGSAnHvacCl = 0;
        pdchSHGSAnSurfHt = 0;
        pdchSHGSAnSurfCl = 0;
        pdchSHGSAnPeoplAdd = 0;
        pdchSHGSAnLiteAdd = 0;
        pdchSHGSAnEquipAdd = 0;
        pdchSHGSAnWindAdd = 0;
        pdchSHGSAnIzaAdd = 0;
        pdchSHGSAnInfilAdd = 0;
        pdchSHGSAnOtherAdd = 0;
        pdchSHGSAnEquipRem = 0;
        pdchSHGSAnWindRem = 0;
        pdchSHGSAnIzaRem = 0;
        pdchSHGSAnInfilRem = 0;
        pdchSHGSAnOtherRem = 0;
        pdstSHGSpkCl = 0;
        pdchSHGSClTimePeak = 0;
        pdchSHGSClHvacHt = 0;
        pdchSHGSClHvacCl = 0;
        pdchSHGSClSurfHt = 0;
        pdchSHGSClSurfCl = 0;
        pdchSHGSClPeoplAdd = 0;
        pdchSHGSClLiteAdd = 0;
        pdchSHGSClEquipAdd = 0;
        pdchSHGSClWindAdd = 0;
        pdchSHGSClIzaAdd = 0;
        pdchSHGSClInfilAdd = 0;
        pdchSHGSClOtherAdd = 0;
        pdchSHGSClEquipRem = 0;
        pdchSHGSClWindRem = 0;
        pdchSHGSClIzaRem = 0;
        pdchSHGSClInfilRem = 0;
        pdchSHGSClOtherRem = 0;
        pdstSHGSpkHt = 0;
        pdchSHGSHtTimePeak = 0;
        pdchSHGSHtHvacHt = 0;
        pdchSHGSHtHvacCl = 0;
        pdchSHGSHtSurfHt = 0;
        pdchSHGSHtSurfCl = 0;
        pdchSHGSHtPeoplAdd = 0;
        pdchSHGSHtLiteAdd = 0;
        pdchSHGSHtEquipAdd = 0;
        pdchSHGSHtWindAdd = 0;
        pdchSHGSHtIzaAdd = 0;
        pdchSHGSHtInfilAdd = 0;
        pdchSHGSHtOtherAdd = 0;
        pdchSHGSHtEquipRem = 0;
        pdchSHGSHtWindRem = 0;
        pdchSHGSHtIzaRem = 0;
        pdchSHGSHtInfilRem = 0;
        pdchSHGSHtOtherRem = 0;
        pdrStd62 = 0;
        pdstS62sysVentReqCool = 0;
        pdchS62svrClSumVpz = 0;
        pdchS62svrClPs = 0;
        pdchS62svrClSumPz = 0;
        pdchS62svrClD = 0;
        pdchS62svrClVou = 0;
        pdchS62svrClVps = 0;
        pdchS62svrClXs = 0;
        pdchS62svrClEv = 0;
        pdchS62svrClVot = 0;
        pdchS62svrClPercOA = 0;
        pdchS62svrClEnvironmentOfPs = 0;
        pdchS62svrClTimeOfPs = 0;

        pdstS62sysVentReqHeat = 0;
        pdchS62svrHtSumVpz = 0;
        pdchS62svrHtPs = 0;
        pdchS62svrHtSumPz = 0;
        pdchS62svrHtD = 0;
        pdchS62svrHtVou = 0;
        pdchS62svrHtVps = 0;
        pdchS62svrHtXs = 0;
        pdchS62svrHtEv = 0;
        pdchS62svrHtVot = 0;
        pdchS62svrHtPercOA = 0;
        pdchS62svrHtEnvironmentOfPs = 0;
        pdchS62svrHtTimeOfPs = 0;

        pdstS62znVentPar = 0;
        pdchS62zvpAlN = 0;
        pdchS62zvpRp = 0;
        pdchS62zvpPz = 0;
        pdchS62zvpRa = 0;
        pdchS62zvpAz = 0;
        pdchS62zvpVbz = 0;
        pdchS62zvpClEz = 0;
        pdchS62zvpClVoz = 0;
        pdchS62zvpHtEz = 0;
        pdchS62zvpHtVoz = 0;
        pdstS62sysVentPar = 0;
        pdchS62svpRp = 0;
        pdchS62svpPz = 0;
        pdchS62svpRa = 0;
        pdchS62svpAz = 0;
        pdchS62svpVbz = 0;
        pdchS62svpClVoz = 0;
        pdchS62svpHtVoz = 0;
        pdstS62znCoolDes = 0;
        pdchS62zcdAlN = 0;
        pdchS62zcdBox = 0;
        pdchS62zcdVpz = 0;
        pdchS62zcdVps = 0;
        pdchS62zcdVsec = 0;
        pdchS62zcdVdz = 0;
        pdchS62zcdVpzmin = 0;
        pdchS62zcdVozclg = 0;
        pdchS62zcdZpz = 0;
        pdchS62zcdEp = 0;
        pdchS62zcdEr = 0;
        pdchS62zcdFa = 0;
        pdchS62zcdFb = 0;
        pdchS62zcdFc = 0;
        pdchS62zcdEvz = 0;
        pdstS62sysCoolDes = 0;
        pdchS62scdVpz = 0;
        pdchS62scdVps = 0;
        pdchS62scdVsec = 0;
        pdchS62scdVdz = 0;
        pdchS62scdVpzmin = 0;
        pdchS62scdVozclg = 0;
        pdchS62scdEvz = 0;
        pdstS62znHeatDes = 0;
        pdchS62zhdAlN = 0;
        pdchS62zhdBox = 0;
        pdchS62zhdVpz = 0;
        pdchS62zhdVps = 0;
        pdchS62zhdVsec = 0;
        pdchS62zhdVdz = 0;
        pdchS62zhdVpzmin = 0;
        pdchS62zhdVozhtg = 0;
        pdchS62zhdZpz = 0;
        pdchS62zhdEp = 0;
        pdchS62zhdEr = 0;
        pdchS62zhdFa = 0;
        pdchS62zhdFb = 0;
        pdchS62zhdFc = 0;
        pdchS62zhdEvz = 0;
        pdstS62sysHeatDes = 0;
        pdchS62shdVpz = 0;
        pdchS62shdVps = 0;
        pdchS62shdVsec = 0;
        pdchS62shdVdz = 0;
        pdchS62shdVpzmin = 0;
        pdchS62shdVozhtg = 0;
        pdchS62shdEvz = 0;
        pdrLeed = 0;
        pdstLeedGenInfo = 0;
        pdchLeedGenData = 0;
        pdstLeedSpaceUsageType = 0;
        pdchLeedSutName = 0;
        pdchLeedSutSpArea = 0;
        pdchLeedSutOcArea = 0;
        pdchLeedSutUnArea = 0;
        pdchLeedSutHrsWeek = 0;
        pdstLeedAdvsMsg = 0;
        pdchLeedAmData = 0;
        pdstLeedEneTypSum = 0;
        pdchLeedEtsType = 0;
        pdchLeedEtsRtNm = 0;
        pdchLeedEtsVirt = 0;
        pdchLeedEtsEneUnt = 0;
        pdchLeedEtsDemUnt = 0;
        pdstLeedPerf = 0;
        pdchLeedPerfRot = 0;
        pdchLeedPerfElEneUse = 0;
        pdchLeedPerfElDem = 0;
        pdchLeedPerfGasEneUse = 0;
        pdchLeedPerfGasDem = 0;
        pdchLeedPerfAddFuelEneUse = 0;
        pdchLeedPerfAddFuelDem = 0;
        pdchLeedPerfDisClEneUse = 0;
        pdchLeedPerfDisClDem = 0;
        pdchLeedPerfDisHtEneUse = 0;
        pdchLeedPerfDisHtDem = 0;
        pdstLeedEneUseSum = 0;
        pdchLeedEusUnt = 0;
        pdchLeedEusProc = 0;
        pdchLeedEusTotal = 0;
        pdstLeedEneCostSum = 0;
        pdchLeedEcUnt = 0;
        pdchLeedEcsProc = 0;
        pdchLeedEcsTotal = 0;
        LEEDelecCostTotal = 0.0;
        LEEDgasCostTotal = 0.0;
        LEEDothrCostTotal = 0.0;
        pdstLeedRenewSum = 0;
        pdchLeedRenRatCap = 0;
        pdchLeedRenAnGen = 0;
        pdstLeedEneUseIntEl = 0;
        pdchLeedEuiElec = 0;
        pdstLeedEneUseIntNatG = 0;
        pdchLeedEuiNatG = 0;
        pdstLeedEneUseIntOthr = 0;
        pdchLeedEuiOthr = 0;
        pdstLeedEneUsePerc = 0;
        pdchLeedEupPerc = 0;
        sizeReportName = 0;
        numReportName = 0;
        sizeSubTable = 0;
        numSubTable = 0;
        sizeColumnTag = 0;
        numColumnTag = 0;
        sizeTableEntry = 0;
        numTableEntry = 0;
        sizeCompSizeTableEntry = 0; // Autodesk Was used uninitialized in output to .audit files
        numCompSizeTableEntry = 0;  // Autodesk Was used uninitialized in WriteComponentSizing
        sizeShadowRelate = 0;
        numShadowRelate = 0;
        TotalNotMetHeatingOccupiedForABUPS = 0.0;
        TotalNotMetCoolingOccupiedForABUPS = 0.0;
        TotalNotMetOccupiedForABUPS = 0.0;
        TotalTimeNotSimpleASH55EitherForABUPS = 0.0;
        reportName.deallocate();
        subTable.deallocate();
        columnTag.deallocate();
        tableEntry.deallocate();
        CompSizeTableEntry.deallocate();
        ShadowRelate.deallocate();
    }

    void SetPredefinedTables()
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Creates the structure of the predefined reports
        //   including the name and abreviation of the report
        //   the subtables involved and the column headings.
        //   The variables defined for the columns are then
        //   used throughout the program to assign values
        //   to the subtables.

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // Using/Aliasing
        using DataGlobals::DoSystemSizing;
        using DataGlobals::DoZoneSizing;

        // SUBROUTINE ARGUMENT DEFINITIONS:
        // na

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:

        // Climate Summary Report
        pdrClim = newPreDefReport("ClimaticDataSummary", "Clim", "Climatic Data Summary");

        pdstDesDay = newPreDefSubTable(pdrClim, "SizingPeriod:DesignDay");

        pdchDDmaxDB = newPreDefColumn(pdstDesDay, "Maximum Dry Bulb [C]");
        pdchDDrange = newPreDefColumn(pdstDesDay, "Daily Temperature Range [deltaC]");
        pdchDDhumid = newPreDefColumn(pdstDesDay, "Humidity Value");
        pdchDDhumTyp = newPreDefColumn(pdstDesDay, "Humidity Type");
        pdchDDwindSp = newPreDefColumn(pdstDesDay, "Wind Speed [m/s]");
        pdchDDwindDr = newPreDefColumn(pdstDesDay, "Wind Direction");

        pdstWthr = newPreDefSubTable(pdrClim, "Weather Statistics File");
        pdchWthrVal = newPreDefColumn(pdstWthr, "Value");

        // Envelope Report

        pdrEnvelope = newPreDefReport("EnvelopeSummary", "Env", "Envelope Summary");

        pdstOpaque = newPreDefSubTable(pdrEnvelope, "Opaque Exterior");

        pdchOpCons = newPreDefColumn(pdstOpaque, "Construction");
        pdchOpRefl = newPreDefColumn(pdstOpaque, "Reflectance");
        pdchOpUfactFilm = newPreDefColumn(pdstOpaque, "U-Factor with Film [W/m2-K]");
        pdchOpUfactNoFilm = newPreDefColumn(pdstOpaque, "U-Factor no Film [W/m2-K]");
        pdchOpGrArea = newPreDefColumn(pdstOpaque, "Gross Area [m2]");
        pdchOpNetArea = newPreDefColumn(pdstOpaque, "Net Area [m2]");
        pdchOpAzimuth = newPreDefColumn(pdstOpaque, "Azimuth [deg]");
        pdchOpTilt = newPreDefColumn(pdstOpaque, "Tilt [deg]");
        pdchOpDir = newPreDefColumn(pdstOpaque, "Cardinal Direction");

        pdstFen = newPreDefSubTable(pdrEnvelope, "Exterior Fenestration");

        pdchFenCons = newPreDefColumn(pdstFen, "Construction");
        pdchFenGlassAreaOf1 = newPreDefColumn(pdstFen, "Glass Area [m2]");
        pdchFenFrameAreaOf1 = newPreDefColumn(pdstFen, "Frame Area [m2]");
        pdchFenDividerAreaOf1 = newPreDefColumn(pdstFen, "Divider Area [m2]");
        pdchFenAreaOf1 = newPreDefColumn(pdstFen, "Area of One Opening [m2]");
        pdchFenArea = newPreDefColumn(pdstFen, "Area of Multiplied Openings [m2]");
        pdchFenUfact = newPreDefColumn(pdstFen, "Glass U-Factor [W/m2-K]");
        pdchFenSHGC = newPreDefColumn(pdstFen, "Glass SHGC");
        pdchFenVisTr = newPreDefColumn(pdstFen, "Glass Visible Transmittance");
        pdchFenFrameConductance = newPreDefColumn(pdstFen, "Frame Conductance [W/m2-K]");
        pdchFenDividerConductance = newPreDefColumn(pdstFen, "Divider Conductance [W/m2-K]");
        pdchFenSwitchable = newPreDefColumn(pdstFen, "Shade Control");
        pdchFenParent = newPreDefColumn(pdstFen, "Parent Surface");
        pdchFenAzimuth = newPreDefColumn(pdstFen, "Azimuth [deg]");
        pdchFenTilt = newPreDefColumn(pdstFen, "Tilt [deg]");
        pdchFenDir = newPreDefColumn(pdstFen, "Cardinal Direction");

        pdstIntFen = newPreDefSubTable(pdrEnvelope, "Interior Fenestration");

        pdchIntFenCons = newPreDefColumn(pdstIntFen, "Construction");
        pdchIntFenAreaOf1 = newPreDefColumn(pdstIntFen, "Area of One Opening [m2]");
        pdchIntFenArea = newPreDefColumn(pdstIntFen, "Area of Openings [m2]");
        pdchIntFenUfact = newPreDefColumn(pdstIntFen, "Glass U-Factor [W/m2-K]");
        pdchIntFenSHGC = newPreDefColumn(pdstIntFen, "Glass SHGC");
        pdchIntFenVisTr = newPreDefColumn(pdstIntFen, "Glass Visible Transmittance");
        // pdchIntFenGlassAreaOf1 =   newPreDefColumn(pdstIntFen,'Glass Area [m2]')
        // pdchIntFenFrameAreaOf1 =   newPreDefColumn(pdstIntFen,'Frame Area [m2]')
        // pdchIntFenDividerAreaOf1 =   newPreDefColumn(pdstIntFen,'Divider Area [m2]')
        // pdchIntFenFrameConductance =  newPreDefColumn(pdstIntFen,'Frame Conductance [W/m2-K]')
        // pdchIntFenDividerConductance =  newPreDefColumn(pdstIntFen,'Divider Conductance [W/m2-K]')
        pdchIntFenParent = newPreDefColumn(pdstIntFen, "Parent Surface");

        pdstDoor = newPreDefSubTable(pdrEnvelope, "Exterior Door");

        pdchDrCons = newPreDefColumn(pdstDoor, "Construction");
        pdchDrUfactFilm = newPreDefColumn(pdstDoor, "U-Factor with Film [W/m2-K]");
        pdchDrUfactNoFilm = newPreDefColumn(pdstDoor, "U-Factor no Film [W/m2-K]");
        pdchDrGrArea = newPreDefColumn(pdstDoor, "Gross Area [m2]");
        pdchDrParent = newPreDefColumn(pdstDoor, "Parent Surface");

        // Shading Report
        pdrShading = newPreDefReport("ShadingSummary", "Shade", "Shading Summary");

        pdstSunlitFrac = newPreDefSubTable(pdrShading, "Sunlit Fraction");

        pdchSlfMar21_9 = newPreDefColumn(pdstSunlitFrac, "March 21 9am");
        pdchSlfMar21_12 = newPreDefColumn(pdstSunlitFrac, "March 21 noon");
        pdchSlfMar21_15 = newPreDefColumn(pdstSunlitFrac, "March 21 3pm");
        pdchSlfJun21_9 = newPreDefColumn(pdstSunlitFrac, "June 21 9am");
        pdchSlfJun21_12 = newPreDefColumn(pdstSunlitFrac, "June 21 noon");
        pdchSlfJun21_15 = newPreDefColumn(pdstSunlitFrac, "June 21 3pm");
        pdchSlfDec21_9 = newPreDefColumn(pdstSunlitFrac, "December 21 9am");
        pdchSlfDec21_12 = newPreDefColumn(pdstSunlitFrac, "December 21 noon");
        pdchSlfDec21_15 = newPreDefColumn(pdstSunlitFrac, "December 21 3pm");

        pdstWindowControl = newPreDefSubTable(pdrShading, "Window Control");

        pdchWscName = newPreDefColumn(pdstWindowControl, "Name");
        pdchWscShading = newPreDefColumn(pdstWindowControl, "Type");
        pdchWscShadCons = newPreDefColumn(pdstWindowControl, "Shaded Construction");
        pdchWscControl = newPreDefColumn(pdstWindowControl, "Control");
        pdchWscGlare = newPreDefColumn(pdstWindowControl, "Glare Control");

        // Lighting Report
        pdrLighting = newPreDefReport("LightingSummary", "Light", "Lighting Summary");

        pdstInLite = newPreDefSubTable(pdrLighting, "Interior Lighting");

        pdchInLtZone = newPreDefColumn(pdstInLite, "Zone");
        pdchInLtDens = newPreDefColumn(pdstInLite, "Lighting Power Density [W/m2]");
        pdchInLtArea = newPreDefColumn(pdstInLite, "Zone Area [m2]");
        pdchInLtPower = newPreDefColumn(pdstInLite, "Total Power [W]");
        pdchInLtEndUse = newPreDefColumn(pdstInLite, "End Use Subcategory");
        pdchInLtSchd = newPreDefColumn(pdstInLite, "Schedule Name");
        pdchInLtAvgHrSchd = newPreDefColumn(pdstInLite, "Scheduled Hours/Week [hr]");
        pdchInLtAvgHrOper = newPreDefColumn(pdstInLite, "Hours/Week > 1% [hr]");
        pdchInLtFullLoadHrs = newPreDefColumn(pdstInLite, "Full Load Hours/Week [hr]");
        pdchInLtRetAir = newPreDefColumn(pdstInLite, "Return Air Fraction");
        pdchInLtCond = newPreDefColumn(pdstInLite, "Conditioned (Y/N)");
        pdchInLtConsump = newPreDefColumn(pdstInLite, "Consumption [GJ]");

        pdstDaylight = newPreDefSubTable(pdrLighting, "Daylighting");

        pdchDyLtZone = newPreDefColumn(pdstDaylight, "Zone");
        pdchDyLtCtrlName = newPreDefColumn(pdstDaylight, "Control Name");
        pdchDyLtKind = newPreDefColumn(pdstDaylight, "Daylighting Method"); // detailed or DElight
        pdchDyLtCtrlType = newPreDefColumn(pdstDaylight, "Control Type");   // stepped or continuous
        pdchDyLtFrac = newPreDefColumn(pdstDaylight, "Fraction Controlled");
        pdchDyLtWInst = newPreDefColumn(pdstDaylight, "Lighting Installed in Zone [W]");
        pdchDyLtWCtrl = newPreDefColumn(pdstDaylight, "Lighting Controlled [W]");

        pdstExtLite = newPreDefSubTable(pdrLighting, "Exterior Lighting");

        pdchExLtPower = newPreDefColumn(pdstExtLite, "Total Watts");
        pdchExLtClock = newPreDefColumn(pdstExtLite, "Astronomical Clock/Schedule");
        pdchExLtSchd = newPreDefColumn(pdstExtLite, "Schedule Name");
        pdchExLtAvgHrSchd = newPreDefColumn(pdstExtLite, "Scheduled Hours/Week [hr]");
        pdchExLtAvgHrOper = newPreDefColumn(pdstExtLite, "Hours/Week > 1% [hr]");
        pdchExLtFullLoadHrs = newPreDefColumn(pdstExtLite, "Full Load Hours/Week [hr]");
        pdchExLtConsump = newPreDefColumn(pdstExtLite, "Consumption [GJ]");

        // HVAC Equipment Report

        pdrEquip = newPreDefReport("EquipmentSummary", "Equip", "Equipment Summary");

        pdstMech = newPreDefSubTable(pdrEquip, "Central Plant");

        pdchMechType = newPreDefColumn(pdstMech, "Type");
        pdchMechNomCap = newPreDefColumn(pdstMech, "Nominal Capacity [W]");
        pdchMechNomEff = newPreDefColumn(pdstMech, "Nominal Efficiency [W/W]");
        pdchMechIPLVSI = newPreDefColumn(pdstMech, "IPLV in SI Units [W/W]");
        pdchMechIPLVIP = newPreDefColumn(pdstMech, "IPLV in IP Units [Btu/W-h]");

        // Ok Constant                        Object Name                            Module                   Example File
        // -- ------------------------------- -------------------------------------- ------------------------ -----------------
        // o  CoilDX_CoolingSingleSpeed       Coil:Cooling:DX:SingleSpeed            DXCoil                   FurnaceWithDXSystem
        // x  CoilDX_CoolingTwoSpeed          Coil:Cooling:DX:TwoSpeed               DXCoil                   5ZoneAutoDXVAV
        // o  CoilDX_CoolingTwoStageWHumControl    Coil:Cooling:DX:                 DXCoil                   SmOffPSZ-MultiModeDX
        //                                    TwoStageWithHumidityControlMode
        // o  CoilDX_MultiSpeedCooling        Coil:Cooling:DX:MultiSpeed             DXCoil                   MultispeedHeatPump
        // o  Coil_CoolingWater               Coil:Cooling:Water                     HVACWaterCoilComponent   5ZoneAirCooled
        // o  Coil_CoolingWaterDetailed       Coil:Cooling:Water:DetailedGeometry    HVACWaterCoilComponent   5zoneWaterSystems
        // o  Coil_CoolingWaterToAirHP        Coil:Cooling:WaterToAirHeatPump:       HVACWaterToAir           5ZoneWaterLoopHeatPump
        //                                      ParameterEstimation
        // o  Coil_CoolingWaterToAirHPSimple  Coil:Cooling:WaterToAirHeatPump:       HVACWaterToAir           HeatPumpWaterToAirEquationFit
        //                                      EquationFit

        // o  CoilDX_HeatingEmpirical         Coil:Heating:DX:SingleSpeed            DXCoil                   HeatPumpAuto
        // o  CoilDX_MultiSpeedHeating        Coil:Heating:DX:MultiSpeed             DXCoil                   MultispeedHeatPump
        // o  Coil_HeatingGasOrOtherFuel                 Coil:Heating:Fuel                       HVACHeatingCoils         5ZoneAutoDXVAV
        // o  Coil_HeatingElectric            Coil:Heating:Electric                  HVACHeatingCoils         PackagedTerminalAirConditioner
        // o  Coil_HeatingDesuperheater       Coil:Heating:Desuperheater             HVACHeatingCoils         SuperMarket_DesuperHeatingCoil
        // o  Coil_HeatingWater               Coil:Heating:Water                     HVACWaterCoilComponent   5ZoneAirCooled
        // o  Coil_HeatingWaterToAirHP        Coil:Heating:WaterToAirHeatPump:       HVACWaterToAir           5ZoneWaterLoopHeatPump
        //                                      ParameterEstimation
        // o  Coil_HeatingWaterToAirHPSimple  Coil:Heating:WaterToAirHeatPump:       HVACWaterToAir           HeatPumpWaterToAirEquationFit
        //                                      EquationFit
        // o  CoilDX_HeatPumpWaterHeater      Coil:WaterHeating:AirToWaterHeatPump   DXCoil                   HeatPumpWaterHeater

        // NOT INCLUDED:
        //    CoilDX_CoolingHXAssisted        CoilSystem:Cooling:DX:                 HVACHXAssistedCooolingCoil
        //                                      HeatExchangerAssisted
        //    CoilWater_CoolingHXAssisted     CoilSystem:Cooling:Water:              HVACHXAssistedCooolingCoil
        //                                      HeatExchangerAssisted

        pdstCoolCoil = newPreDefSubTable(pdrEquip, "Cooling Coils");

        pdchCoolCoilType = newPreDefColumn(pdstCoolCoil, "Type");
        pdchCoolCoilDesCap = newPreDefColumn(pdstCoolCoil, "Design Coil Load [W]");
        pdchCoolCoilTotCap = newPreDefColumn(pdstCoolCoil, "Nominal Total Capacity [W]");
        pdchCoolCoilSensCap = newPreDefColumn(pdstCoolCoil, "Nominal Sensible Capacity [W]");
        pdchCoolCoilLatCap = newPreDefColumn(pdstCoolCoil, "Nominal Latent Capacity [W]");
        pdchCoolCoilSHR = newPreDefColumn(pdstCoolCoil, "Nominal Sensible Heat Ratio");
        pdchCoolCoilNomEff = newPreDefColumn(pdstCoolCoil, "Nominal Efficiency [W/W]");
        pdchCoolCoilUATotal = newPreDefColumn(pdstCoolCoil, "Nominal Coil UA Value [W/C]");
        pdchCoolCoilArea = newPreDefColumn(pdstCoolCoil, "Nominal Coil Surface Area [m2]");

        pdstDXCoolCoil = newPreDefSubTable(pdrEquip, "DX Cooling Coils");
        pdchDXCoolCoilType = newPreDefColumn(pdstDXCoolCoil, "DX Cooling Coil Type");
        pdchDXCoolCoilNetCapSI = newPreDefColumn(pdstDXCoolCoil, "Standard Rated Net Cooling Capacity [W]");

        pdchDXCoolCoilCOP = newPreDefColumn(pdstDXCoolCoil, "Standard Rated Net COP [W/W]");
        pdchDXCoolCoilEERIP = newPreDefColumn(pdstDXCoolCoil, "EER [Btu/W-h]");
        pdchDXCoolCoilSEERIP = newPreDefColumn(pdstDXCoolCoil, "SEER [Btu/W-h]");
        pdchDXCoolCoilIEERIP = newPreDefColumn(pdstDXCoolCoil, "IEER [Btu/W-h]");

        // for DX Cooling Coil ASHRAE 127-12 Report
        pdstDXCoolCoil2 = newPreDefSubTable(pdrEquip, "DX Cooling Coil ASHRAE 127 Standard Ratings Report");
        pdchDXCoolCoilType = newPreDefColumn(pdstDXCoolCoil2, "DX Cooling Coil Type");
        pdchDXCoolCoilNetCapSIA = newPreDefColumn(pdstDXCoolCoil2, "Rated Net Cooling Capacity Test A [W]");
        pdchDXCoolCoilElecPowerA = newPreDefColumn(pdstDXCoolCoil2, "Rated Electric Power Test A [W]");
        pdchDXCoolCoilNetCapSIB = newPreDefColumn(pdstDXCoolCoil2, "Rated Net Cooling Capacity Test B [W]");
        pdchDXCoolCoilElecPowerB = newPreDefColumn(pdstDXCoolCoil2, "Rated Electric Power Test B [W]");
        pdchDXCoolCoilNetCapSIC = newPreDefColumn(pdstDXCoolCoil2, "Rated Net Cooling Capacity Test C [W]");
        pdchDXCoolCoilElecPowerC = newPreDefColumn(pdstDXCoolCoil2, "Rated Electric Power Test C [W]");
        pdchDXCoolCoilNetCapSID = newPreDefColumn(pdstDXCoolCoil2, "Rated Net Cooling Capacity Test D [W]");
        pdchDXCoolCoilElecPowerD = newPreDefColumn(pdstDXCoolCoil2, "Rated Electric Power Test D [W]");

        pdstDXHeatCoil = newPreDefSubTable(pdrEquip, "DX Heating Coils");
        pdchDXHeatCoilType = newPreDefColumn(pdstDXHeatCoil, "DX Heating Coil Type");
        pdchDXHeatCoilHighCap = newPreDefColumn(pdstDXHeatCoil, "High Temperature Heating (net) Rating Capacity [W]");
        pdchDXHeatCoilLowCap = newPreDefColumn(pdstDXHeatCoil, "Low Temperature Heating (net) Rating Capacity [W]");
        pdchDXHeatCoilHSPFIP = newPreDefColumn(pdstDXHeatCoil, "HSPF [Btu/W-h]");
        pdchDXHeatCoilRegionNum = newPreDefColumn(pdstDXHeatCoil, "Region Number");

        pdstHeatCoil = newPreDefSubTable(pdrEquip, "Heating Coils");

        pdchHeatCoilType = newPreDefColumn(pdstHeatCoil, "Type");
        pdchHeatCoilDesCap = newPreDefColumn(pdstHeatCoil, "Design Coil Load [W]");
        pdchHeatCoilNomCap = newPreDefColumn(pdstHeatCoil, "Nominal Total Capacity [W]");
        pdchHeatCoilNomEff = newPreDefColumn(pdstHeatCoil, "Nominal Efficiency [W/W]");

        pdstFan = newPreDefSubTable(pdrEquip, "Fans");

        pdchFanType = newPreDefColumn(pdstFan, "Type");
        pdchFanTotEff = newPreDefColumn(pdstFan, "Total Efficiency [W/W]");
        pdchFanDeltaP = newPreDefColumn(pdstFan, "Delta Pressure [pa]");
        pdchFanVolFlow = newPreDefColumn(pdstFan, "Max Air Flow Rate [m3/s]");
        pdchFanPwr = newPreDefColumn(pdstFan, "Rated Electric Power [W]");
        pdchFanPwrPerFlow = newPreDefColumn(pdstFan, "Rated Power Per Max Air Flow Rate [W-s/m3]");
        pdchFanMotorIn = newPreDefColumn(pdstFan, "Motor Heat In Air Fraction");
        pdchFanEnergyIndex = newPreDefColumn(pdstFan, "Fan Energy Index");
        pdchFanEndUse = newPreDefColumn(pdstFan, "End Use");
        pdchFanDesDay = newPreDefColumn(pdstFan, "Design Day Name for Fan Sizing Peak");
        pdchFanPkTime = newPreDefColumn(pdstFan, "Date/Time for Fan Sizing Peak");

        pdstPump = newPreDefSubTable(pdrEquip, "Pumps");
        pdchPumpType = newPreDefColumn(pdstPump, "Type");
        pdchPumpControl = newPreDefColumn(pdstPump, "Control");
        pdchPumpHead = newPreDefColumn(pdstPump, "Head [pa]");
        pdchPumpFlow = newPreDefColumn(pdstPump, "Water Flow [m3/s]");
        pdchPumpPower = newPreDefColumn(pdstPump, "Electric Power [W]");
        pdchPumpPwrPerFlow = newPreDefColumn(pdstPump, "Power Per Water Flow Rate [W-s/m3]");
        pdchMotEff = newPreDefColumn(pdstPump, "Motor Efficiency [W/W]");

        pdstSWH = newPreDefSubTable(pdrEquip, "Service Water Heating");
        pdchSWHType = newPreDefColumn(pdstSWH, "Type");
        pdchSWHVol = newPreDefColumn(pdstSWH, "Storage Volume [m3]");
        pdchSWHHeatIn = newPreDefColumn(pdstSWH, "Input [W]");
        pdchSWHThEff = newPreDefColumn(pdstSWH, "Thermal Efficiency [W/W]");
        pdchSWHRecEff = newPreDefColumn(pdstSWH, "Recovery Efficiency [W/W]");
        pdchSWHEnFac = newPreDefColumn(pdstSWH, "Energy Factor");

        // Sizing Report

        pdrSizing = newPreDefReport("HVACSizingSummary", "Size", "HVAC Sizing Summary");

        pdstZoneClSize = newPreDefSubTable(pdrSizing, "Zone Sensible Cooling");

        pdchZnClCalcDesLd = newPreDefColumn(pdstZoneClSize, "Calculated Design Load [W]");
        pdchZnClUserDesLd = newPreDefColumn(pdstZoneClSize, "User Design Load [W]");
        pdchZnClUserDesLdPerArea = newPreDefColumn(pdstZoneClSize, "User Design Load per Area [W/m2]");
        pdchZnClCalcDesAirFlow = newPreDefColumn(pdstZoneClSize, "Calculated Design Air Flow [m3/s]");
        pdchZnClUserDesAirFlow = newPreDefColumn(pdstZoneClSize, "User Design Air Flow [m3/s]");
        pdchZnClDesDay = newPreDefColumn(pdstZoneClSize, "Design Day Name");
        pdchZnClPkTime = newPreDefColumn(pdstZoneClSize, "Date/Time Of Peak {TIMESTAMP}");
        pdchZnClPkTstatTemp = newPreDefColumn(pdstZoneClSize, "Thermostat Setpoint Temperature at Peak Load [C]");
        pdchZnClPkIndTemp = newPreDefColumn(pdstZoneClSize, "Indoor Temperature at Peak Load [C]");
        pdchZnClPkIndHum = newPreDefColumn(pdstZoneClSize, "Indoor Humidity Ratio at Peak Load [kgWater/kgAir]");
        pdchZnClPkOATemp = newPreDefColumn(pdstZoneClSize, "Outdoor Temperature at Peak Load [C]");
        pdchZnClPkOAHum = newPreDefColumn(pdstZoneClSize, "Outdoor Humidity Ratio at Peak Load [kgWater/kgAir]");
        pdchZnClPkOAMinFlow = newPreDefColumn(pdstZoneClSize, "Minimum Outdoor Air Flow Rate [m3/s]");
        pdchZnClPkDOASHeatGain = newPreDefColumn(pdstZoneClSize, "Heat Gain Rate from DOAS [W]");
        addFootNoteSubTable(pdstZoneClSize,
                            "The Design Load is the zone sensible load only. It does not include any system effects or ventilation loads.");
        pdstZoneHtSize = newPreDefSubTable(pdrSizing, "Zone Sensible Heating");

        pdchZnHtCalcDesLd = newPreDefColumn(pdstZoneHtSize, "Calculated Design Load [W]");
        pdchZnHtUserDesLd = newPreDefColumn(pdstZoneHtSize, "User Design Load [W]");
        pdchZnHtUserDesLdPerArea = newPreDefColumn(pdstZoneHtSize, "User Design Load per Area [W/m2]");
        pdchZnHtCalcDesAirFlow = newPreDefColumn(pdstZoneHtSize, "Calculated Design Air Flow [m3/s]");
        pdchZnHtUserDesAirFlow = newPreDefColumn(pdstZoneHtSize, "User Design Air Flow [m3/s]");
        pdchZnHtDesDay = newPreDefColumn(pdstZoneHtSize, "Design Day Name");
        pdchZnHtPkTime = newPreDefColumn(pdstZoneHtSize, "Date/Time Of Peak {TIMESTAMP}");
        pdchZnHtPkTstatTemp = newPreDefColumn(pdstZoneHtSize, "Thermostat Setpoint Temperature at Peak Load [C]");
        pdchZnHtPkIndTemp = newPreDefColumn(pdstZoneHtSize, "Indoor Temperature at Peak Load [C]");
        pdchZnHtPkIndHum = newPreDefColumn(pdstZoneHtSize, "Indoor Humidity Ratio at Peak Load [kgWater/kgAir]");
        pdchZnHtPkOATemp = newPreDefColumn(pdstZoneHtSize, "Outdoor Temperature at Peak Load [C]");
        pdchZnHtPkOAHum = newPreDefColumn(pdstZoneHtSize, "Outdoor Humidity Ratio at Peak Load [kgWater/kgAir]");
        pdchZnHtPkOAMinFlow = newPreDefColumn(pdstZoneHtSize, "Minimum Outdoor Air Flow Rate [m3/s]");
        pdchZnHtPkDOASHeatGain = newPreDefColumn(pdstZoneHtSize, "Heat Gain Rate from DOAS [W]");
        addFootNoteSubTable(pdstZoneHtSize,
                            "The Design Load is the zone sensible load only. It does not include any system effects or ventilation loads.");
        pdstSystemSize = newPreDefSubTable(pdrSizing, "System Design Air Flow Rates");

        pdchSysSizCalcClAir = newPreDefColumn(pdstSystemSize, "Calculated cooling [m3/s]");
        pdchSysSizUserClAir = newPreDefColumn(pdstSystemSize, "User cooling [m3/s]");
        pdchSysSizCalcHtAir = newPreDefColumn(pdstSystemSize, "Calculated heating [m3/s]");
        pdchSysSizUserHtAir = newPreDefColumn(pdstSystemSize, "User heating [m3/s]");
        pdchSysSizAdjustedClAir = newPreDefColumn(pdstSystemSize, "Adjusted cooling [m3/s]");
        pdchSysSizAdjustedHtAir = newPreDefColumn(pdstSystemSize, "Adjusted heating [m3/s]");
        pdchSysSizAdjustedMainAir = newPreDefColumn(pdstSystemSize, "Adjusted main [m3/s]");
        pdchSysSizCalcHeatFlowRatio = newPreDefColumn(pdstSystemSize, "Calculated Heating Air Flow Ratio []");
        pdchSysSizUserHeatFlowRatio = newPreDefColumn(pdstSystemSize, "User Heating Air Flow Ratio []");

        pdstPlantSize = newPreDefSubTable(pdrSizing, "Plant Loop Coincident Design Fluid Flow Rate Adjustments");
        //		pdchPlantSizPass = newPreDefColumn( pdstPlantSize, "Sizing Pass" );
        pdchPlantSizPrevVdot = newPreDefColumn(pdstPlantSize, "Previous Design Volume Flow Rate [m3/s]");
        pdchPlantSizMeasVdot = newPreDefColumn(pdstPlantSize, "Algorithm Volume Flow Rate [m3/s]");
        pdchPlantSizCalcVdot = newPreDefColumn(pdstPlantSize, "Coincident Design Volume Flow Rate [m3/s]");
        pdchPlantSizCoincYesNo = newPreDefColumn(pdstPlantSize, "Coincident Size Adjusted");
        pdchPlantSizDesDay = newPreDefColumn(pdstPlantSize, "Peak Sizing Period Name");
        pdchPlantSizPkTimeDayOfSim = newPreDefColumn(pdstPlantSize, "Peak Day into Period {TIMESTAMP}[day]");
        pdchPlantSizPkTimeHour = newPreDefColumn(pdstPlantSize, "Peak Hour Of Day {TIMESTAMP}[hr]");
        pdchPlantSizPkTimeMin = newPreDefColumn(pdstPlantSize, "Peak Step Start Minute {TIMESTAMP}[min]");

        pdst2CoilSummaryCoilSelection = newPreDefSubTable(pdrSizing, "Coil Sizing Summary");
        // coil meta data information
        //	the first column will be the coil name, the unique user name from input. It has no header or column definition
        pdch2CoilType = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Type");
        pdch2CoilHVACType = newPreDefColumn(pdst2CoilSummaryCoilSelection, "HVAC Type");
        pdch2CoilHVACName = newPreDefColumn(pdst2CoilSummaryCoilSelection, "HVAC Name");

        // coil Final size summary, regardless of how determined (
        pdch2CoilFinalTotalCap = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Final Gross Total Capacity [W]");
        pdch2CoilFinalSensCap = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Final Gross Sensible Capacity [W]");
        pdch2CoilFinalAirVolFlowRate = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Final Reference Air Volume Flow Rate [m3/s]");
        pdch2CoilFinalPlantVolFlowRate = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Final Reference Plant Fluid Volume Flow Rate [m3/s]");
        pdch2CoilUA = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil U-value Times Area Value [W/K]");

        // results from regular zone and system sizing calcs, "At Ideal Loads Peak"
        pdch2CoilDDnameSensIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Design Day Name at Sensible Ideal Loads Peak");
        pdch2CoilDateTimeSensIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Date/Time at Sensible Ideal Loads Peak");
        pdch2CoilDDnameAirFlowIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Design Day Name at Air Flow Ideal Loads Peak");
        pdch2CoilDateTimeAirFlowIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Date/Time at Air Flow Ideal Loads Peak");

        pdch2CoilTotalCapIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Total Capacity at Ideal Loads Peak [W]");
        pdch2CoilSensCapIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Sensible Capacity at Ideal Loads Peak [W]");
        pdch2CoilAirVolumeFlowIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Air Volume Flow Rate at Ideal Loads Peak [m3/s]");
        pdch2CoilEntDryBulbIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Entering Air Drybulb at Ideal Loads Peak [C]");
        pdch2CoilEntWetBulbIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Entering Air Wetbulb at Ideal Loads Peak [C]");
        pdch2CoilEntHumRatIdealPeak =
            newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Entering Air Humidity Ratio at Ideal Loads Peak [KGWATER/KGDRYAIR]");
        pdch2CoilLvgDryBulbIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Leaving Air Drybulb at Ideal Loads Peak [C]");
        pdch2CoilLvgWetBulbIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Leaving Air Wetbulb at Ideal Loads Peak [C]");
        pdch2CoilLvgHumRatIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Leaving Air Humidity Ratio at Ideal Loads Peak [C]");
        pdch2OADryBulbIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Outdoor Air Drybulb at Ideal Loads Peak [C]");
        pdch2OAHumRatIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Outdoor Air Humidity Ratio at Ideal Loads Peak [KGWATER/KGDRYAIR]");
        pdch2OAWetBulbatIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Outdoor Air Wetbulb at Ideal Loads Peak [C]");
        pdch2OAFlowPrcntIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Outdoor Air Flow Percentage at Ideal Loads Peak [%]");
        pdch2ZoneAirDryBulbIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Zone Air Drybulb at Ideal Loads Peak [C]");
        pdch2ZoneAirHumRatIdealPeak =
            newPreDefColumn(pdst2CoilSummaryCoilSelection, "Zone Air Humidity Ratio at Ideal Loads Peak [KGWATER/KGDRYAIR]");
        pdch2ZoneAirRelHumIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Zone Air Relative Humidity at Ideal Loads Peak [%]");
        pdch2ZoneSensibleLoadIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Zone Sensible Heat Gain at Ideal Loads Peak [W]");
        pdch2ZoneLatentLoadIdealPeak = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Zone Latent Heat Gain at Ideal Loads Peak [W]");
        // results for coil at Rated Conditions
        pdch2CoilRatedTotalCap = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Total Capacity at Rating Conditions [W]");
        pdch2CoilRatedSensCap = newPreDefColumn(pdst2CoilSummaryCoilSelection, "Coil Sensible Capacity at Rating Conditions [W]");

        pdrCoilSizingDetailsTable = newPreDefReport("CoilSizingDetails", "Coil", "Coil Sizing Details");
        pdstCoilSummaryCoilSelection = newPreDefSubTable(pdrCoilSizingDetailsTable, "Coils");
        // coil meta data information
        //	the first column will be the coil name, the unique user name from input. It has no header or column definition
        pdchCoilType = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Type");
        pdchCoilLocation = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Location");
        pdchCoilHVACType = newPreDefColumn(pdstCoilSummaryCoilSelection, "HVAC Type");
        pdchCoilHVACName = newPreDefColumn(pdstCoilSummaryCoilSelection, "HVAC Name");
        pdchCoilZoneName = newPreDefColumn(pdstCoilSummaryCoilSelection, "Zone Name(s)");

        pdchSysSizingMethCoinc = newPreDefColumn(pdstCoilSummaryCoilSelection, "System Sizing Method Concurrence");
        pdchSysSizingMethCap = newPreDefColumn(pdstCoilSummaryCoilSelection, "System Sizing Method Capacity");
        pdchSysSizingMethAir = newPreDefColumn(pdstCoilSummaryCoilSelection, "System Sizing Method Air Flow");

        pdchCoilIsCapAutosized = newPreDefColumn(pdstCoilSummaryCoilSelection, "Autosized Coil Capacity?");
        pdchCoilIsAirFlowAutosized = newPreDefColumn(pdstCoilSummaryCoilSelection, "Autosized Coil Airflow?");
        pdchCoilIsWaterFlowAutosized = newPreDefColumn(pdstCoilSummaryCoilSelection, "Autosized Coil Water Flow?");
        pdchCoilIsOATreated = newPreDefColumn(pdstCoilSummaryCoilSelection, "OA Pretreated prior to coil inlet?");

        // coil Final size summary, regardless of how determined (
        // get rid of these, this will be the same as At Rating Conditions.
        pdchCoilFinalTotalCap = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Final Gross Total Capacity [W]");
        pdchCoilFinalSensCap = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Final Gross Sensible Capacity [W]");
        pdchCoilFinalAirVolFlowRate = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Final Reference Air Volume Flow Rate [m3/s]");
        pdchCoilFinalPlantVolFlowRate = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Final Reference Plant Fluid Volume Flow Rate [m3/s]");

        // Misc Design output
        pdchCoilUA = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil U-value Times Area Value [W/K]");
        pdchReheatCoilMultiplier = newPreDefColumn(pdstCoilSummaryCoilSelection, "Terminal Unit Reheat Coil Multiplier");
        pdchFlowCapRatioLowCapIncreaseRatio =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "DX Coil Capacity Increase Ratio from Too Low Flow/Capacity Ratio");
        pdchFlowCapRatioHiCapDecreaseRatio =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "DX Coil Capacity Decrease Ratio from Too High Flow/Capacity Ratio");

        pdchMoistAirSpecificHeat =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Moist Air Heat Capacity [J/kg-K]");                    // standard? for ideal sizing calcs?
        pdchDryAirSpecificHeat = newPreDefColumn(pdstCoilSummaryCoilSelection, "Dry Air Heat Capacity [J/kg-K]"); // standard? for ideal sizing calcs?
        pdchStandRhoAir = newPreDefColumn(pdstCoilSummaryCoilSelection, "Standard Air Density Adjusted for Elevation [kg/m3]");

        // Fan info for coil
        pdchFanAssociatedWithCoilName = newPreDefColumn(pdstCoilSummaryCoilSelection, "Supply Fan Name for Coil");
        pdchFanAssociatedWithCoilType = newPreDefColumn(pdstCoilSummaryCoilSelection, "Supply Fan Type for Coil");
        pdchFanAssociatedVdotSize = newPreDefColumn(pdstCoilSummaryCoilSelection, "Supply Fan Maximum Air Volume Flow Rate [m3/s]");
        pdchFanAssociatedMdotSize = newPreDefColumn(pdstCoilSummaryCoilSelection, "Supply Fan Maximum Air Mass Flow Rate [kg/s]");

        // Plant info for coil
        pdchCoilPlantLoopName = newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Name for Coil");
        pdchPlantFluidSpecificHeat = newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Fluid Specific Heat Capacity [J/kg-K]"); // standard/inits ?
        pdchPlantFluidDensity =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Fluid Density [kg/m3]"); // standard/inits ? for ideal sizing calcs?
        pdchPlantMassFlowMaximum = newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Maximum Fluid Mass Flow Rate [kg/s]");
        pdchPlantRetTempDesign = newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Design Fluid Return Temperature [C]");
        pdchPlantSupTempDesign = newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Design Fluid Supply Temperature [C]");
        pdchPlantDeltaTempDesign = newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Design Fluid Temperature Difference [deltaC]");
        pdchPlantCapacity = newPreDefColumn(pdstCoilSummaryCoilSelection, "Plant Design Capacity [W]");
        pdchCoilCapPrcntPlantCapacity = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Capacity Percentage of Plant Design Capacity [%]");
        pdchCoilFlowPrcntPlantFlow = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Fluid Flow Rate Percentage of Plant Design Flow Rate [%]");

        // results from regular zone and system sizing calcs, "At Ideal Loads Peak"
        pdchCoilDDnameSensIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Design Day Name at Sensible Ideal Loads Peak");
        pdchCoilDateTimeSensIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Date/Time at Sensible Ideal Loads Peak");
        pdchCoilDDnameTotIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Design Day Name at Total Ideal Loads Peak");
        pdchCoilDateTimeTotIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Date/Time at Total Ideal Loads Peak");
        pdchCoilDDnameAirFlowIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Design Day Name at Air Flow Ideal Loads Peak");
        pdchCoilDateTimeAirFlowIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Date/Time at Air Flow Ideal Loads Peak");

        pdchCoilTotalCapIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Total Capacity at Ideal Loads Peak [W]");
        pdchCoilSensCapIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Sensible Capacity at Ideal Loads Peak [W]");
        pdchCoilOffRatingCapacityModifierIdealPeak =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Off-Rating Capacity Modifier at Ideal Loads Peak [ ]");
        pdchCoilAirMassFlowIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Air Mass Flow Rate at Ideal Loads Peak [kg/s]");
        pdchCoilAirVolumeFlowIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Air Volume Flow Rate at Ideal Loads Peak [m3/s]");
        pdchCoilEntDryBulbIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Drybulb at Ideal Loads Peak [C]");
        pdchCoilEntWetBulbIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Wetbulb at Ideal Loads Peak [C]");
        pdchCoilEntHumRatIdealPeak =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Humidity Ratio at Ideal Loads Peak [KGWATER/KGDRYAIR]");
        pdchCoilEntEnthalpyIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Enthalpy at Ideal Loads Peak [J/KG-K]");
        pdchCoilLvgDryBulbIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Drybulb at Ideal Loads Peak [C]");
        pdchCoilLvgWetBulbIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Wetbulb at Ideal Loads Peak [C]");
        pdchCoilLvgHumRatIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Humidity Ratio at Ideal Loads Peak [C]");
        pdchCoilLvgEnthalpyIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Enthalpy at Ideal Loads Peak [J/KG-K]");
        pdchCoilWaterMassFlowIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Plant Fluid Mass Flow Rate at Ideal Loads Peak [kg/s]");
        pdchCoilEntWaterTempIdealPeak =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Plant Fluid Temperature at Ideal Loads Peak [C]");
        pdchCoilLvgWaterTempIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Plant Fluid Temperature at Ideal Loads Peak [C]");
        pdchCoilWaterDeltaTempIdealPeak =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Plant Fluid Temperature Difference at Ideal Loads Peak [deltaC]");
        pdchFanHeatGainIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Supply Fan Air Heat Gain at Ideal Loads Peak [W]");
        pdchCoilNetTotalCapacityIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil and Fan Net Total Capacity at Ideal Loads Peak [W]");
        pdchOADryBulbIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Outdoor Air Drybulb at Ideal Loads Peak [C]");
        pdchOAHumRatIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Outdoor Air Humidity Ratio at Ideal Loads Peak [KGWATER/KGDRYAIR]");
        pdchOAWetBulbatIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Outdoor Air Wetbulb at Ideal Loads Peak [C]");
        pdchOAVolFlowIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Outdoor Air Volume Flow Rate at Ideal Loads Peak [m3/s]");
        pdchOAFlowPrcntIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Outdoor Air Flow Percentage at Ideal Loads Peak [%]");
        pdchAirSysRADryBulbIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "System Return Air Drybulb at Ideal Loads Peak [C]");
        pdchAirSysRAHumRatIdealPeak =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "System Return Air Humidity Ratio at Ideal Loads Peak [KGWATER/KGDRYAIR]");
        pdchZoneAirDryBulbIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Zone Air Drybulb at Ideal Loads Peak [C]");
        pdchZoneAirHumRatIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Zone Air Humidity Ratio at Ideal Loads Peak [KGWATER/KGDRYAIR]");
        pdchZoneAirRelHumIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Zone Air Relative Humidity at Ideal Loads Peak [%]");
        pdchZoneSensibleLoadIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Zone Sensible Heat Gain at Ideal Loads Peak [W]");
        pdchZoneLatentLoadIdealPeak = newPreDefColumn(pdstCoilSummaryCoilSelection, "Zone Latent Heat Gain at Ideal Loads Peak [W]");
        // results for coil at Rated Conditions
        pdchCoilRatedTotalCap = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Total Capacity at Rating Conditions [W]");
        pdchCoilRatedSensCap = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Sensible Capacity at Rating Conditions [W]");

        pdchCoilRatedAirMass = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Air Mass Flow Rate at Rating Conditions [kg/s]");
        pdchCoilRatedEntDryBulb = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Drybulb at Rating Conditions [C]");
        pdchCoilRatedEntWetBulb = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Wetbulb at Rating Conditions [C]");
        pdchCoilRatedEntHumRat =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Humidity Ratio at Rating Conditions [KGWATER/KGDRYAIR]");
        pdchCoilRatedEntEnthalpy = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Entering Air Enthalpy at Rating Conditions [J/KG-K]");
        pdchCoilRatedLvgDryBulb = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Drybulb at Rating Conditions [C]");
        pdchCoilRatedLvgWetBulb = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Wetbulb at Rating Conditions [C]");
        pdchCoilRatedLvgHumRat =
            newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Humidity Ratio at Rating Conditions [KGWATER/KGDRYAIR]");
        pdchCoilRatedLvgEnthalpy = newPreDefColumn(pdstCoilSummaryCoilSelection, "Coil Leaving Air Enthalpy at Rating Conditions [J/KG-K]");

        // System Summary Report

        pdrSystem = newPreDefReport("SystemSummary", "Sys", "System Summary");

        pdstEconomizer = newPreDefSubTable(pdrSystem, "Economizer");

        pdchEcoKind = newPreDefColumn(pdstEconomizer, "High Limit Shutoff Control");
        pdchEcoMinOA = newPreDefColumn(pdstEconomizer, "Minimum Outdoor Air [m3/s]");
        pdchEcoMaxOA = newPreDefColumn(pdstEconomizer, "Maximum Outdoor Air [m3/s]");
        pdchEcoRetTemp = newPreDefColumn(pdstEconomizer, "Return Air Temp Limit");
        pdchEcoRetEnth = newPreDefColumn(pdstEconomizer, "Return Air Enthalpy Limit");
        pdchEcoOATempLim = newPreDefColumn(pdstEconomizer, "Outdoor Air Temperature Limit [C]");
        pdchEcoOAEnthLim = newPreDefColumn(pdstEconomizer, "Outdoor Air Enthalpy Limit [C]");

        pdstDemCntlVent = newPreDefSubTable(pdrSystem, "Demand Controlled Ventilation using Controller:MechanicalVentilation");
        pdchDCVventMechName = newPreDefColumn(pdstDemCntlVent, "Controller:MechanicalVentilation Name");
        pdchDCVperPerson = newPreDefColumn(pdstDemCntlVent, "Outdoor Air Per Person [m3/s-person]");
        pdchDCVperArea = newPreDefColumn(pdstDemCntlVent, "Outdoor Air Per Area [m3/s-m2]");
        pdchDCVperZone = newPreDefColumn(pdstDemCntlVent, "Outdoor Air Per Zone [m3/s]");
        pdchDCVperACH = newPreDefColumn(pdstDemCntlVent, "Outdoor Air ACH [ach]");
        pdchDCVMethod = newPreDefColumn(pdstDemCntlVent, "Outdoor Air Method");
        pdchDCVOASchName = newPreDefColumn(pdstDemCntlVent, "Outdoor Air Schedule Name");

        // added for new DCV
        pdchDCVZoneADEffCooling = newPreDefColumn(pdstDemCntlVent, "Air Distribution Effectiveness in Cooling Mode");
        pdchDCVZoneADEffHeating = newPreDefColumn(pdstDemCntlVent, "Air Distribution Effectiveness in Heating Mode");
        pdchDCVZoneADEffSchName = newPreDefColumn(pdstDemCntlVent, "Air Distribution Effectiveness Schedule Name");

        pdstSimpleComfort = newPreDefSubTable(pdrSystem, "Time Not Comfortable Based on Simple ASHRAE 55-2004");
        pdchSCwinterClothes = newPreDefColumn(pdstSimpleComfort, "Winter Clothes [hr]");
        pdchSCsummerClothes = newPreDefColumn(pdstSimpleComfort, "Summer Clothes [hr]");
        pdchSCeitherClothes = newPreDefColumn(pdstSimpleComfort, "Summer or Winter Clothes [hr]");

        pdstUnmetLoads = newPreDefSubTable(pdrSystem, "Time Setpoint Not Met");
        pdchULnotMetHeat = newPreDefColumn(pdstUnmetLoads, "During Heating [hr]");
        pdchULnotMetCool = newPreDefColumn(pdstUnmetLoads, "During Cooling [hr]");
        pdchULnotMetHeatOcc = newPreDefColumn(pdstUnmetLoads, "During Occupied Heating [hr]");
        pdchULnotMetCoolOcc = newPreDefColumn(pdstUnmetLoads, "During Occupied Cooling [hr]");

        // Outside Air Report
        pdrOutsideAir = newPreDefReport("OutdoorAirSummary", "OA", "Outdoor Air Summary");

        pdstOAavgOcc = newPreDefSubTable(pdrOutsideAir, "Average Outdoor Air During Occupied Hours");

        pdchOaoAvgNumOcc1 = newPreDefColumn(pdstOAavgOcc, "Average Number of Occupants");
        pdchOaoNomNumOcc1 = newPreDefColumn(pdstOAavgOcc, "Nominal Number of Occupants");
        pdchOaoZoneVol1 = newPreDefColumn(pdstOAavgOcc, "Zone Volume [m3]");
        pdchOaoAvgMechVent = newPreDefColumn(pdstOAavgOcc, "Mechanical Ventilation [ach]");
        pdchOaoAvgInfil = newPreDefColumn(pdstOAavgOcc, "Infiltration [ach]");
        pdchOaoAvgAFNInfil = newPreDefColumn(pdstOAavgOcc, "AFN Infiltration [ach]");
        pdchOaoAvgSimpVent = newPreDefColumn(pdstOAavgOcc, "Simple Ventilation [ach]");
        // pdchOaoAvgTotVent =   newPreDefColumn(pdstOAavgOcc,'Total Ventilation [ach]')

        addFootNoteSubTable(pdstOAavgOcc, "Values shown for a single zone without multipliers");

        pdstOAminOcc = newPreDefSubTable(pdrOutsideAir, "Minimum Outdoor Air During Occupied Hours");

        pdchOaoAvgNumOcc2 = newPreDefColumn(pdstOAminOcc, "Average Number of Occupants");
        pdchOaoNomNumOcc2 = newPreDefColumn(pdstOAminOcc, "Nominal Number of Occupants");
        pdchOaoZoneVol2 = newPreDefColumn(pdstOAminOcc, "Zone Volume [m3]");
        pdchOaoMinMechVent = newPreDefColumn(pdstOAminOcc, "Mechanical Ventilation [ach]");
        pdchOaoMinInfil = newPreDefColumn(pdstOAminOcc, "Infiltration [ach]");
        pdchOaoMinAFNInfil = newPreDefColumn(pdstOAminOcc, "AFN Infiltration [ach]");
        pdchOaoMinSimpVent = newPreDefColumn(pdstOAminOcc, "Simple Ventilation [ach]");
        // pdchOaoMinTotVent =   newPreDefColumn(pdstOAminOcc,'Total Ventilation [ach]')
        addFootNoteSubTable(pdstOAminOcc, "Values shown for a single zone without multipliers");

        // Object Count Report
        pdrObjCnt = newPreDefReport("ObjectCountSummary", "Count", "Object Count Summary");

        pdstSurfCnt = newPreDefSubTable(pdrObjCnt, "Surfaces by Class");
        pdchSurfCntTot = newPreDefColumn(pdstSurfCnt, "Total");
        pdchSurfCntExt = newPreDefColumn(pdstSurfCnt, "Outdoors");

        pdstHVACcnt = newPreDefSubTable(pdrObjCnt, "HVAC");
        pdchHVACcntVal = newPreDefColumn(pdstHVACcnt, "Count");

        pdstFieldCnt = newPreDefSubTable(pdrObjCnt, "Input Fields");
        pdchFieldCntVal = newPreDefColumn(pdstFieldCnt, "Count");

        // Energy Meters report
        pdrEnergyMeters = newPreDefReport("EnergyMeters", "Meters", "Energy Meters");

        // pdstEMvalues = newPreDefSubTable(pdrEnergyMeters,'Annual and Peak Values')
        // pdchEMannual = newPreDefColumn(pdstEMvalues,'Annual Value [GJ]')
        // pdchEMminvalue = newPreDefColumn(pdstEMvalues,'Minimum Value [J]')
        // pdchEMminvaluetime = newPreDefColumn(pdstEMvalues,'Timestamp of Minimum')
        // pdchEMmaxvalue = newPreDefColumn(pdstEMvalues,'Maximum Value [J]')
        // pdchEMmaxvaluetime = newPreDefColumn(pdstEMvalues,'Timestamp of Maximum')
        // Electricity Sub Table
        pdstEMelecvalues = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Electricity");
        pdchEMelecannual = newPreDefColumn(pdstEMelecvalues, "Electricity Annual Value [GJ]");
        pdchEMelecminvalue = newPreDefColumn(pdstEMelecvalues, "Electricity Minimum Value [W]");
        pdchEMelecminvaluetime = newPreDefColumn(pdstEMelecvalues, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMelecmaxvalue = newPreDefColumn(pdstEMelecvalues, "Electricity Maximum Value [W]");
        pdchEMelecmaxvaluetime = newPreDefColumn(pdstEMelecvalues, "Timestamp of Maximum {TIMESTAMP}");

        // Gas Sub Table
        pdstEMgasvalues = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Gas");
        pdchEMgasannual = newPreDefColumn(pdstEMgasvalues, "Gas Annual Value [GJ]");
        pdchEMgasminvalue = newPreDefColumn(pdstEMgasvalues, "Gas Minimum Value [W]");
        pdchEMgasminvaluetime = newPreDefColumn(pdstEMgasvalues, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMgasmaxvalue = newPreDefColumn(pdstEMgasvalues, "Gas Maximum Value [W]");
        pdchEMgasmaxvaluetime = newPreDefColumn(pdstEMgasvalues, "Timestamp of Maximum {TIMESTAMP}");

        // Cool SubTable
        pdstEMcoolvalues = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Cooling");
        pdchEMcoolannual = newPreDefColumn(pdstEMcoolvalues, "Cooling Annual Value [GJ]");
        pdchEMcoolminvalue = newPreDefColumn(pdstEMcoolvalues, "Cooling Minimum Value [W]");
        pdchEMcoolminvaluetime = newPreDefColumn(pdstEMcoolvalues, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMcoolmaxvalue = newPreDefColumn(pdstEMcoolvalues, "Cooling Maximum Value [W]");
        pdchEMcoolmaxvaluetime = newPreDefColumn(pdstEMcoolvalues, "Timestamp of Maximum {TIMESTAMP}");

        // Water SubTable
        pdstEMwatervalues = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Water");
        pdchEMwaterannual = newPreDefColumn(pdstEMwatervalues, "Annual Value [m3]");
        pdchEMwaterminvalue = newPreDefColumn(pdstEMwatervalues, "Minimum Value [m3/s]");
        pdchEMwaterminvaluetime = newPreDefColumn(pdstEMwatervalues, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMwatermaxvalue = newPreDefColumn(pdstEMwatervalues, "Maximum Value [m3/s]");
        pdchEMwatermaxvaluetime = newPreDefColumn(pdstEMwatervalues, "Timestamp of Maximum {TIMESTAMP}");

        // Other KG SubTable
        pdstEMotherKGvalues = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Other by Weight/Mass");
        pdchEMotherKGannual = newPreDefColumn(pdstEMotherKGvalues, "Annual Value [kg]");
        pdchEMotherKGminvalue = newPreDefColumn(pdstEMotherKGvalues, "Minimum Value [kg/s]");
        pdchEMotherKGminvaluetime = newPreDefColumn(pdstEMotherKGvalues, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMotherKGmaxvalue = newPreDefColumn(pdstEMotherKGvalues, "Maximum Value [kg/s]");
        pdchEMotherKGmaxvaluetime = newPreDefColumn(pdstEMotherKGvalues, "Timestamp of Maximum {TIMESTAMP}");

        // Other M3 SubTable
        pdstEMotherM3values = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Other Volumetric");
        pdchEMotherM3annual = newPreDefColumn(pdstEMotherM3values, "Annual Value [m3]");
        pdchEMotherM3minvalue = newPreDefColumn(pdstEMotherM3values, "Minimum Value [m3/s]");
        pdchEMotherM3minvaluetime = newPreDefColumn(pdstEMotherM3values, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMotherM3maxvalue = newPreDefColumn(pdstEMotherM3values, "Maximum Value [m3/s]");
        pdchEMotherM3maxvaluetime = newPreDefColumn(pdstEMotherM3values, "Timestamp of Maximum {TIMESTAMP}");

        // Other M3 SubTable
        pdstEMotherLvalues = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Other Liquid/Gas");
        pdchEMotherLannual = newPreDefColumn(pdstEMotherLvalues, "Annual Value [L]");
        pdchEMotherLminvalue = newPreDefColumn(pdstEMotherLvalues, "Minimum Value [L]");
        pdchEMotherLminvaluetime = newPreDefColumn(pdstEMotherLvalues, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMotherLmaxvalue = newPreDefColumn(pdstEMotherLvalues, "Maximum Value [L]");
        pdchEMotherLmaxvaluetime = newPreDefColumn(pdstEMotherLvalues, "Timestamp of Maximum {TIMESTAMP}");

        // Other J SubTable
        pdstEMotherJvalues = newPreDefSubTable(pdrEnergyMeters, "Annual and Peak Values - Other");
        pdchEMotherJannual = newPreDefColumn(pdstEMotherJvalues, "Annual Value [GJ]");
        pdchEMotherJminvalue = newPreDefColumn(pdstEMotherJvalues, "Minimum Value [W]");
        pdchEMotherJminvaluetime = newPreDefColumn(pdstEMotherJvalues, "Timestamp of Minimum {TIMESTAMP}");
        pdchEMotherJmaxvalue = newPreDefColumn(pdstEMotherJvalues, "Maximum Value [W]");
        pdchEMotherJmaxvaluetime = newPreDefColumn(pdstEMotherJvalues, "Timestamp of Maximum {TIMESTAMP}");

        // Sensible Heat Gain Component Report
        pdrSensibleGain = newPreDefReport("SensibleHeatGainSummary", "SHGS", "Sensible Heat Gain Summary");

        pdstSHGSannual = newPreDefSubTable(pdrSensibleGain, "Annual Building Sensible Heat Gain Components");

        pdchSHGSAnHvacHt = newPreDefColumn(pdstSHGSannual, "HVAC Zone Eq & Other Sensible Air Heating [GJ]");
        pdchSHGSAnHvacCl = newPreDefColumn(pdstSHGSannual, "HVAC Zone Eq & Other Sensible Air Cooling [GJ]");
        pdchSHGSAnHvacATUHt = newPreDefColumn(pdstSHGSannual, "HVAC Terminal Unit Sensible Air Heating [GJ]");
        pdchSHGSAnHvacATUCl = newPreDefColumn(pdstSHGSannual, "HVAC Terminal Unit Sensible Air Cooling [GJ]");
        pdchSHGSAnSurfHt = newPreDefColumn(pdstSHGSannual, "HVAC Input Heated Surface Heating [GJ]");
        pdchSHGSAnSurfCl = newPreDefColumn(pdstSHGSannual, "HVAC Input Cooled Surface Cooling [GJ]");
        pdchSHGSAnPeoplAdd = newPreDefColumn(pdstSHGSannual, "People Sensible Heat Addition [GJ]");
        pdchSHGSAnLiteAdd = newPreDefColumn(pdstSHGSannual, "Lights Sensible Heat Addition [GJ]");
        pdchSHGSAnEquipAdd = newPreDefColumn(pdstSHGSannual, "Equipment Sensible Heat Addition [GJ]");
        pdchSHGSAnWindAdd = newPreDefColumn(pdstSHGSannual, "Window Heat Addition [GJ]");
        pdchSHGSAnIzaAdd = newPreDefColumn(pdstSHGSannual, "Interzone Air Transfer Heat Addition [GJ]");
        pdchSHGSAnInfilAdd = newPreDefColumn(pdstSHGSannual, "Infiltration Heat Addition [GJ]");
        pdchSHGSAnOtherAdd = newPreDefColumn(pdstSHGSannual, "Opaque Surface Conduction and Other Heat Addition [GJ]");
        pdchSHGSAnEquipRem = newPreDefColumn(pdstSHGSannual, "Equipment Sensible Heat Removal [GJ]");
        pdchSHGSAnWindRem = newPreDefColumn(pdstSHGSannual, "Window Heat Removal [GJ]");
        pdchSHGSAnIzaRem = newPreDefColumn(pdstSHGSannual, "Interzone Air Transfer Heat Removal [GJ]");
        pdchSHGSAnInfilRem = newPreDefColumn(pdstSHGSannual, "Infiltration Heat Removal [GJ]");
        pdchSHGSAnOtherRem = newPreDefColumn(pdstSHGSannual, "Opaque Surface Conduction and Other Heat Removal [GJ]");

        pdstSHGSpkCl = newPreDefSubTable(pdrSensibleGain, "Peak Cooling Sensible Heat Gain Components");

        pdchSHGSClTimePeak = newPreDefColumn(pdstSHGSpkCl, "Time of Peak {TIMESTAMP}");
        pdchSHGSClHvacHt = newPreDefColumn(pdstSHGSpkCl, "HVAC Zone Eq & Other Sensible Air Heating [W]");
        pdchSHGSClHvacCl = newPreDefColumn(pdstSHGSpkCl, "HVAC Zone Eq & Other Sensible Air Cooling [W]");
        pdchSHGSClHvacATUHt = newPreDefColumn(pdstSHGSpkCl, "HVAC Terminal Unit Sensible Air Heating [W]");
        pdchSHGSClHvacATUCl = newPreDefColumn(pdstSHGSpkCl, "HVAC Terminal Unit Sensible Air Cooling [W]");
        pdchSHGSClSurfHt = newPreDefColumn(pdstSHGSpkCl, "HVAC Input Heated Surface Heating [W]");
        pdchSHGSClSurfCl = newPreDefColumn(pdstSHGSpkCl, "HVAC Input Cooled Surface Cooling [W]");
        pdchSHGSClPeoplAdd = newPreDefColumn(pdstSHGSpkCl, "People Sensible Heat Addition [W]");
        pdchSHGSClLiteAdd = newPreDefColumn(pdstSHGSpkCl, "Lights Sensible Heat Addition [W]");
        pdchSHGSClEquipAdd = newPreDefColumn(pdstSHGSpkCl, "Equipment Sensible Heat Addition [W]");
        pdchSHGSClWindAdd = newPreDefColumn(pdstSHGSpkCl, "Window Heat Addition [W]");
        pdchSHGSClIzaAdd = newPreDefColumn(pdstSHGSpkCl, "Interzone Air Transfer Heat Addition [W]");
        pdchSHGSClInfilAdd = newPreDefColumn(pdstSHGSpkCl, "Infiltration Heat Addition [W]");
        pdchSHGSClOtherAdd = newPreDefColumn(pdstSHGSpkCl, "Opaque Surface Conduction and Other Heat Addition [W]");
        pdchSHGSClEquipRem = newPreDefColumn(pdstSHGSpkCl, "Equipment Sensible Heat Removal [W]");
        pdchSHGSClWindRem = newPreDefColumn(pdstSHGSpkCl, "Window Heat Removal [W]");
        pdchSHGSClIzaRem = newPreDefColumn(pdstSHGSpkCl, "Interzone Air Transfer Heat Removal [W]");
        pdchSHGSClInfilRem = newPreDefColumn(pdstSHGSpkCl, "Infiltration Heat Removal [W]");
        pdchSHGSClOtherRem = newPreDefColumn(pdstSHGSpkCl, "Opaque Surface Conduction and Other Heat Removal [W]");

        pdstSHGSpkHt = newPreDefSubTable(pdrSensibleGain, "Peak Heating Sensible Heat Gain Components");

        pdchSHGSHtTimePeak = newPreDefColumn(pdstSHGSpkHt, "Time of Peak {TIMESTAMP}");
        pdchSHGSHtHvacHt = newPreDefColumn(pdstSHGSpkHt, "HVAC Zone Eq & Other Sensible Air Heating [W]");
        pdchSHGSHtHvacCl = newPreDefColumn(pdstSHGSpkHt, "HVAC Zone Eq & Other Sensible Air Cooling [W]");
        pdchSHGSHtHvacATUHt = newPreDefColumn(pdstSHGSpkHt, "HVAC Terminal Unit Sensible Air Heating [W]");
        pdchSHGSHtHvacATUCl = newPreDefColumn(pdstSHGSpkHt, "HVAC Terminal Unit Sensible Air Cooling [W]");
        pdchSHGSHtSurfHt = newPreDefColumn(pdstSHGSpkHt, "HVAC Input Heated Surface Heating [W]");
        pdchSHGSHtSurfCl = newPreDefColumn(pdstSHGSpkHt, "HVAC Input Cooled Surface Cooling [W]");
        pdchSHGSHtPeoplAdd = newPreDefColumn(pdstSHGSpkHt, "People Sensible Heat Addition [W]");
        pdchSHGSHtLiteAdd = newPreDefColumn(pdstSHGSpkHt, "Lights Sensible Heat Addition [W]");
        pdchSHGSHtEquipAdd = newPreDefColumn(pdstSHGSpkHt, "Equipment Sensible Heat Addition [W]");
        pdchSHGSHtWindAdd = newPreDefColumn(pdstSHGSpkHt, "Window Heat Addition [W]");
        pdchSHGSHtIzaAdd = newPreDefColumn(pdstSHGSpkHt, "Interzone Air Transfer Heat Addition [W]");
        pdchSHGSHtInfilAdd = newPreDefColumn(pdstSHGSpkHt, "Infiltration Heat Addition [W]");
        pdchSHGSHtOtherAdd = newPreDefColumn(pdstSHGSpkHt, "Opaque Surface Conduction and Other Heat Addition [W]");
        pdchSHGSHtEquipRem = newPreDefColumn(pdstSHGSpkHt, "Equipment Sensible Heat Removal [W]");
        pdchSHGSHtWindRem = newPreDefColumn(pdstSHGSpkHt, "Window Heat Removal [W]");
        pdchSHGSHtIzaRem = newPreDefColumn(pdstSHGSpkHt, "Interzone Air Transfer Heat Removal [W]");
        pdchSHGSHtInfilRem = newPreDefColumn(pdstSHGSpkHt, "Infiltration Heat Removal [W]");
        pdchSHGSHtOtherRem = newPreDefColumn(pdstSHGSpkHt, "Opaque Surface Conduction and Other Heat Removal [W]");

        // Standard62Report
        if (DoZoneSizing || DoSystemSizing) {
            pdrStd62 = newPreDefReport("Standard62.1Summary", "Std62", "Standard 62.1 Summary");

            pdstS62sysVentReqCool = newPreDefSubTable(pdrStd62, "System Ventilation Requirements for Cooling");

            pdchS62svrClSumVpz = newPreDefColumn(pdstS62sysVentReqCool, "Sum of Zone Primary Air Flow - Vpz-sum [m3/s]");
            pdchS62svrClPs = newPreDefColumn(pdstS62sysVentReqCool, "System Population - Ps");
            pdchS62svrClSumPz = newPreDefColumn(pdstS62sysVentReqCool, "Sum of Zone Population - Pz-sum");
            pdchS62svrClD = newPreDefColumn(pdstS62sysVentReqCool, "Occupant Diversity - D");
            pdchS62svrClVou = newPreDefColumn(pdstS62sysVentReqCool, "Uncorrected Outdoor Air Intake Airflow - Vou [m3/s]");
            pdchS62svrClVps = newPreDefColumn(pdstS62sysVentReqCool, "System Primary Airflow - Vps [m3/s]");
            pdchS62svrClXs = newPreDefColumn(pdstS62sysVentReqCool, "Average Outdoor Air Fraction - Xs");
            pdchS62svrClEv = newPreDefColumn(pdstS62sysVentReqCool, "System Ventilation Efficiency - Ev");
            pdchS62svrClVot = newPreDefColumn(pdstS62sysVentReqCool, "Outdoor Air Intake Flow - Vot [m3/s]");
            pdchS62svrClPercOA = newPreDefColumn(pdstS62sysVentReqCool, "Percent Outdoor Air - %OA");
            pdchS62svrClEnvironmentOfPs = newPreDefColumn(pdstS62sysVentReqCool, "Environment Name of Peak System Population - Ps");
            pdchS62svrClTimeOfPs = newPreDefColumn(pdstS62sysVentReqCool, "Date and Time of Last Peak System Population - Ps");

            pdstS62sysVentReqHeat = newPreDefSubTable(pdrStd62, "System Ventilation Requirements for Heating");

            pdchS62svrHtSumVpz = newPreDefColumn(pdstS62sysVentReqHeat, "Sum of Zone Primary Air Flow - Vpz-sum [m3/s]");
            pdchS62svrHtPs = newPreDefColumn(pdstS62sysVentReqHeat, "System Population - Ps");
            pdchS62svrHtSumPz = newPreDefColumn(pdstS62sysVentReqHeat, "Sum of Zone Population - Pz-sum");
            pdchS62svrHtD = newPreDefColumn(pdstS62sysVentReqHeat, "Occupant Diversity - D");
            pdchS62svrHtVou = newPreDefColumn(pdstS62sysVentReqHeat, "Uncorrected Outdoor Air Intake Airflow - Vou [m3/s]");
            pdchS62svrHtVps = newPreDefColumn(pdstS62sysVentReqHeat, "System Primary Airflow - Vps [m3/s]");
            pdchS62svrHtXs = newPreDefColumn(pdstS62sysVentReqHeat, "Average Outdoor Air Fraction - Xs");
            pdchS62svrHtEv = newPreDefColumn(pdstS62sysVentReqHeat, "System Ventilation Efficiency - Ev");
            pdchS62svrHtVot = newPreDefColumn(pdstS62sysVentReqHeat, "Outdoor Air Intake Flow Vot [m3/s]");
            pdchS62svrHtPercOA = newPreDefColumn(pdstS62sysVentReqHeat, "Percent Outdoor Air - %OA");
            pdchS62svrHtEnvironmentOfPs = newPreDefColumn(pdstS62sysVentReqHeat, "Environment Name of Peak System Population - Ps");
            pdchS62svrHtTimeOfPs = newPreDefColumn(pdstS62sysVentReqHeat, "Date and Time of Last Peak System Population - Ps");

            pdstS62znVentPar = newPreDefSubTable(pdrStd62, "Zone Ventilation Parameters");

            pdchS62zvpAlN = newPreDefColumn(pdstS62znVentPar, "AirLoop Name");
            pdchS62zvpRp = newPreDefColumn(pdstS62znVentPar, "People Outdoor Air Rate - Rp [m3/s-person]");
            pdchS62zvpPz = newPreDefColumn(pdstS62znVentPar, "Zone Population - Pz");
            pdchS62zvpRa = newPreDefColumn(pdstS62znVentPar, "Area Outdoor Air Rate - Ra [m3/s-m2]");
            pdchS62zvpAz = newPreDefColumn(pdstS62znVentPar, "Zone Floor Area - Az [m2]");
            pdchS62zvpVbz = newPreDefColumn(pdstS62znVentPar, "Breathing Zone Outdoor Airflow - Vbz [m3/s]");
            pdchS62zvpClEz = newPreDefColumn(pdstS62znVentPar, "Cooling Zone Air Distribution Effectiveness - Ez-clg");
            pdchS62zvpClVoz = newPreDefColumn(pdstS62znVentPar, "Cooling Zone Outdoor Airflow - Voz-clg [m3/s]");
            pdchS62zvpHtEz = newPreDefColumn(pdstS62znVentPar, "Heating Zone Air Distribution Effectiveness - Ez-htg");
            pdchS62zvpHtVoz = newPreDefColumn(pdstS62znVentPar, "Heating Zone Outdoor Airflow - Voz-htg [m3/s]");

            pdstS62sysVentPar = newPreDefSubTable(pdrStd62, "System Ventilation Parameters");

            pdchS62svpRp = newPreDefColumn(pdstS62sysVentPar, "People Outdoor Air Rate - Rp [m3/s-person]");
            pdchS62svpPz = newPreDefColumn(pdstS62sysVentPar, "Sum of Zone Population - Pz-sum");
            pdchS62svpRa = newPreDefColumn(pdstS62sysVentPar, "Area Outdoor Air Rate - Ra [m3/s-m2]");
            pdchS62svpAz = newPreDefColumn(pdstS62sysVentPar, "Sum of Zone Floor Area - Az-sum [m2]");
            pdchS62svpVbz = newPreDefColumn(pdstS62sysVentPar, "Breathing Zone Outdoor Airflow - Vbz [m3/s]");
            pdchS62svpClVoz = newPreDefColumn(pdstS62sysVentPar, "Cooling Zone Outdoor Airflow - Voz-clg [m3/s]");
            pdchS62svpHtVoz = newPreDefColumn(pdstS62sysVentPar, "Heating Zone Outdoor Airflow - Voz-htg [m3/s]");

            pdstS62znCoolDes = newPreDefSubTable(pdrStd62, "Zone Ventilation Calculations for Cooling Design");

            pdchS62zcdAlN = newPreDefColumn(pdstS62znCoolDes, "AirLoop Name");
            pdchS62zcdBox = newPreDefColumn(pdstS62znCoolDes, "Box Type");
            pdchS62zcdVpz = newPreDefColumn(pdstS62znCoolDes, "Zone Primary Airflow - Vpz [m3/s]");
            // pdchS62zcdVps =         newPreDefColumn(pdstS62znCoolDes,'System Primary Airflow - Vps [m3/s]')
            // pdchS62zcdVsec =        newPreDefColumn(pdstS62znCoolDes,'Secondary Fan Airflow - Vsec [m3/s]')
            pdchS62zcdVdz = newPreDefColumn(pdstS62znCoolDes, "Zone Discharge Airflow - Vdz [m3/s]");
            pdchS62zcdVpzmin = newPreDefColumn(pdstS62znCoolDes, "Minimum Zone Primary Airflow - Vpz-min [m3/s]");
            pdchS62zcdVozclg = newPreDefColumn(pdstS62znCoolDes, "Zone Outdoor Airflow Cooling - Voz-clg [m3/s]");
            pdchS62zcdZpz = newPreDefColumn(pdstS62znCoolDes, "Primary Outdoor Air Fraction - Zpz");
            pdchS62zcdEp = newPreDefColumn(pdstS62znCoolDes, "Primary Air Fraction - Ep");
            pdchS62zcdEr = newPreDefColumn(pdstS62znCoolDes, "Secondary Recirculation Fraction- Er");
            pdchS62zcdFa = newPreDefColumn(pdstS62znCoolDes, "Supply Air Fraction- Fa");
            pdchS62zcdFb = newPreDefColumn(pdstS62znCoolDes, "Mixed Air Fraction - Fb");
            pdchS62zcdFc = newPreDefColumn(pdstS62znCoolDes, "Outdoor Air Fraction - Fc");
            pdchS62zcdEvz = newPreDefColumn(pdstS62znCoolDes, "Zone Ventilation Efficiency - Evz");

            pdstS62sysCoolDes = newPreDefSubTable(pdrStd62, "System Ventilation Calculations for Cooling Design");

            pdchS62scdVpz = newPreDefColumn(pdstS62sysCoolDes, "Sum of Zone Primary Airflow - Vpz-sum [m3/s]");
            pdchS62scdVps = newPreDefColumn(pdstS62sysCoolDes, "System Primary Airflow - Vps [m3/s]");
            // pdchS62scdVsec =        newPreDefColumn(pdstS62sysCoolDes,'Secondary Fan Airflow - Vsec [m3/s]')
            pdchS62scdVdz = newPreDefColumn(pdstS62sysCoolDes, "Sum of Zone Discharge Airflow - Vdz-sum [m3/s]");
            pdchS62scdVpzmin = newPreDefColumn(pdstS62sysCoolDes, "Sum of Min Zone Primary Airflow - Vpz-min [m3/s]");
            pdchS62scdVozclg = newPreDefColumn(pdstS62sysCoolDes, "Zone Outdoor Airflow Cooling - Voz-clg [m3/s]");
            pdchS62scdEvz = newPreDefColumn(pdstS62sysCoolDes, "Zone Ventilation Efficiency - Evz-min");

            pdstS62znHeatDes = newPreDefSubTable(pdrStd62, "Zone Ventilation Calculations for Heating Design");

            pdchS62zhdAlN = newPreDefColumn(pdstS62znHeatDes, "AirLoop Name");
            pdchS62zhdBox = newPreDefColumn(pdstS62znHeatDes, "Box Type");
            pdchS62zhdVpz = newPreDefColumn(pdstS62znHeatDes, "Zone Primary Airflow - Vpz [m3/s]");
            // pdchS62zhdVps =         newPreDefColumn(pdstS62znHeatDes,'System Primary Airflow - Vps [m3/s]')
            // pdchS62zhdVsec =        newPreDefColumn(pdstS62znHeatDes,'Secondary Fan Airflow - Vsec [m3/s]')
            pdchS62zhdVdz = newPreDefColumn(pdstS62znHeatDes, "Zone Discharge Airflow - Vdz [m3/s]");
            pdchS62zhdVpzmin = newPreDefColumn(pdstS62znHeatDes, "Minimum Zone Primary Airflow - Vpz-min [m3/s]");
            pdchS62zhdVozhtg = newPreDefColumn(pdstS62znHeatDes, "Zone Outdoor Airflow Heating - Voz-htg [m3/s]");
            pdchS62zhdZpz = newPreDefColumn(pdstS62znHeatDes, "Primary Outdoor Air Fraction - Zpz");
            pdchS62zhdEp = newPreDefColumn(pdstS62znHeatDes, "Primary Air Fraction - Ep");
            pdchS62zhdEr = newPreDefColumn(pdstS62znHeatDes, "Secondary Recirculation Fraction- Er");
            pdchS62zhdFa = newPreDefColumn(pdstS62znHeatDes, "Supply Air Fraction- Fa");
            pdchS62zhdFb = newPreDefColumn(pdstS62znHeatDes, "Mixed Air Fraction - Fb");
            pdchS62zhdFc = newPreDefColumn(pdstS62znHeatDes, "Outdoor Air Fraction - Fc");
            pdchS62zhdEvz = newPreDefColumn(pdstS62znHeatDes, "Zone Ventilation Efficiency - Evz");

            pdstS62sysHeatDes = newPreDefSubTable(pdrStd62, "System Ventilation Calculations for Heating Design");

            pdchS62shdVpz = newPreDefColumn(pdstS62sysHeatDes, "Sum of Zone Primary Airflow - Vpz-sum [m3/s]");
            pdchS62shdVps = newPreDefColumn(pdstS62sysHeatDes, "System Primary Airflow - Vps [m3/s]");
            // pdchS62shdVsec =        newPreDefColumn(pdstS62sysHeatDes,'Secondary Fan Airflow - Vsec [m3/s]')
            pdchS62shdVdz = newPreDefColumn(pdstS62sysHeatDes, "Sum of Zone Discharge Airflow - Vdz-sum [m3/s]");
            pdchS62shdVpzmin = newPreDefColumn(pdstS62sysHeatDes, "Sum of Min Zone Primary Airflow - Vpz-min [m3/s]");
            pdchS62shdVozhtg = newPreDefColumn(pdstS62sysHeatDes, "Zone Outdoor Airflow Heating - Voz-htg [m3/s]");
            pdchS62shdEvz = newPreDefColumn(pdstS62sysHeatDes, "Zone Ventilation Efficiency - Evz-min");
        }

        pdrLeed = newPreDefReport("LEEDsummary", "LEED", "LEED Summary");

        pdstLeedGenInfo = newPreDefSubTable(pdrLeed, "Sec1.1A-General Information");
        // single column with rows of:
        //    Principal Heating Source
        //    Weather File
        //    Climate Zone
        //    Heating Degree Days
        //    Cooling Degree Days
        //    HDD and CDD data source
        //    Total gross floor area
        pdchLeedGenData = newPreDefColumn(pdstLeedGenInfo, "Data");

        pdstLeedSpaceUsageType = newPreDefSubTable(pdrLeed, "EAp2-1. Space Usage Type");
        pdchLeedSutSpArea = newPreDefColumn(pdstLeedSpaceUsageType, "Space Area [m2]");
        pdchLeedSutOcArea = newPreDefColumn(pdstLeedSpaceUsageType, "Regularly Occupied Area [m2]");
        pdchLeedSutUnArea = newPreDefColumn(pdstLeedSpaceUsageType, "Unconditioned Area [m2]");
        pdchLeedSutHrsWeek = newPreDefColumn(pdstLeedSpaceUsageType, "Typical Hours/Week in Operation [hr/wk]");

        pdstLeedAdvsMsg = newPreDefSubTable(pdrLeed, "EAp2-2. Advisory Messages");
        // single column with rows of:
        //    Number of hours heating loads not met
        //    Number of hours cooling loads not met
        //    Total
        //    Difference
        //    Number of warning messages
        //    Number of error messages
        //    Number of defaults overridden
        pdchLeedAmData = newPreDefColumn(pdstLeedAdvsMsg, "Data");

        pdstLeedEneTypSum = newPreDefSubTable(pdrLeed, "EAp2-3. Energy Type Summary");
        // multiple columns with rows of
        //    Electricity
        //    Natural Gas
        //    <additional fuels>
        pdchLeedEtsRtNm = newPreDefColumn(pdstLeedEneTypSum, "Utility Rate");
        pdchLeedEtsVirt = newPreDefColumn(pdstLeedEneTypSum, "Virtual Rate [$/unit energy]");
        pdchLeedEtsEneUnt = newPreDefColumn(pdstLeedEneTypSum, "Units of Energy");
        pdchLeedEtsDemUnt = newPreDefColumn(pdstLeedEneTypSum, "Units of Demand");

        pdstLeedPerf = newPreDefSubTable(pdrLeed, "EAp2-4/5. Performance Rating Method Compliance");
        // Multiple colums with rows of:
        //     Interior Lighting
        //     Exterior Lighting
        //     Space Heating
        //     Space Cooling
        //     Pumps
        //     Heat Rejection
        //     Fans-Interior
        //     Fans-Parking Garage
        //     Service Water Heating
        //     Receptacle Equipment
        //     Interior Lighting (process)
        //     Refrigeration Equipment
        //     Cooking
        //     Industrial Process
        //     Elevators and Escalators
        //     Total
        pdchLeedPerfElEneUse = newPreDefColumn(pdstLeedPerf, "Electric Energy Use [GJ]");
        pdchLeedPerfElDem = newPreDefColumn(pdstLeedPerf, "Electric Demand [W]");
        pdchLeedPerfGasEneUse = newPreDefColumn(pdstLeedPerf, "Natural Gas Energy Use [GJ]");
        pdchLeedPerfGasDem = newPreDefColumn(pdstLeedPerf, "Natural Gas Demand [W]");
        pdchLeedPerfAddFuelEneUse = newPreDefColumn(pdstLeedPerf, "Additional Fuel Use [GJ]");
        pdchLeedPerfAddFuelDem = newPreDefColumn(pdstLeedPerf, "Additional Fuel Demand [W]");
        pdchLeedPerfDisClEneUse = newPreDefColumn(pdstLeedPerf, "District Cooling Use [GJ]");
        pdchLeedPerfDisClDem = newPreDefColumn(pdstLeedPerf, "District Cooling Demand [W]");
        pdchLeedPerfDisHtEneUse = newPreDefColumn(pdstLeedPerf, "District Heating Use [GJ]");
        pdchLeedPerfDisHtDem = newPreDefColumn(pdstLeedPerf, "District Heating Demand [W]");

        pdstLeedEneUseSum = newPreDefSubTable(pdrLeed, "EAp2-6. Energy Use Summary");
        // Multiple columns with rows of:
        //    Electricity
        //    Natural Gas
        //    <additional fuels>
        //    Total
        pdchLeedEusProc = newPreDefColumn(pdstLeedEneUseSum, "Process Subtotal [GJ]");
        pdchLeedEusTotal = newPreDefColumn(pdstLeedEneUseSum, "Total Energy Use [GJ]");

        pdstLeedEneCostSum = newPreDefSubTable(pdrLeed, "EAp2-7. Energy Cost Summary");
        // Multiple columns with rows of:
        //    Electricity
        //    Natural Gas
        //    <additional fuels>
        //    Total
        pdchLeedEcsProc = newPreDefColumn(pdstLeedEneCostSum, "Process Subtotal [$]");
        pdchLeedEcsTotal = newPreDefColumn(pdstLeedEneCostSum, "Total Energy Cost [$]");

        pdstLeedRenewSum = newPreDefSubTable(pdrLeed, "L-1. Renewable Energy Source Summary");
        // Multiple columns with rows of each renewable source
        pdchLeedRenRatCap = newPreDefColumn(pdstLeedRenewSum, "Rated Capacity [kW]");
        pdchLeedRenAnGen = newPreDefColumn(pdstLeedRenewSum, "Annual Energy Generated [GJ]");

        pdstLeedEneUseIntEl = newPreDefSubTable(pdrLeed, "EAp2-17a. Energy Use Intensity - Electricity");
        // Single column with rows of:
        //    Interior lighting
        //    Space heating
        //    Space cooling
        //    Fans-interior
        //    Service water heating
        //    Receptacle equipment
        //    Miscellaneous
        //    Subtotal
        pdchLeedEuiElec = newPreDefColumn(pdstLeedEneUseIntEl, "Electricty [MJ/m2]");

        pdstLeedEneUseIntNatG = newPreDefSubTable(pdrLeed, "EAp2-17b. Energy Use Intensity - Natural Gas");
        // Single column with rows of:
        //    Space heating
        //    Service water heating
        //    Miscellaneous
        //    Subtotal
        pdchLeedEuiNatG = newPreDefColumn(pdstLeedEneUseIntNatG, "Natural Gas [MJ/m2]");

        pdstLeedEneUseIntOthr = newPreDefSubTable(pdrLeed, "EAp2-17c. Energy Use Intensity - Additional");
        // Single column with rows of:
        //    Miscellaneous
        //    Subtotal
        pdchLeedEuiOthr = newPreDefColumn(pdstLeedEneUseIntOthr, "Additional [MJ/m2]");

        pdstLeedEneUsePerc = newPreDefSubTable(pdrLeed, "EAp2-18. End Use Percentage");
        // single column with rows of:
        //    Interior Lighting
        //    Space heating
        //    Space cooling
        //    Fans-Interior
        //    Service Water Heating
        //    Receptacle Equipment
        //    Miscellaneous
        pdchLeedEupPerc = newPreDefColumn(pdstLeedEneUsePerc, "Percent [%]");

        pdstLeedEqFlLdHrs = newPreDefSubTable(pdrLeed, "Schedules-Equivalent Full Load Hours (Schedule Type=Fraction)");
        pdchLeedEflhEflh = newPreDefColumn(pdstLeedEqFlLdHrs, "Equivalent Full Load Hours of Operation Per Year [hr]");
        pdchLeedEflhNonZerHrs = newPreDefColumn(pdstLeedEqFlLdHrs, "Hours > 1% [hr]");

        pdstLeedSchedSetPts = newPreDefSubTable(pdrLeed, "Schedules-SetPoints (Schedule Type=Temperature)");
        pdChLeedSchStPtFirstObjUsed = newPreDefColumn(pdstLeedSchedSetPts, "First Object Used");
        pdChLeedSchStPtMonthUsed = newPreDefColumn(pdstLeedSchedSetPts, "Month Assumed");
        pdchLeedSchStPt11amWednesday = newPreDefColumn(pdstLeedSchedSetPts, "11am First Wednesday [C]");
        pdchLeedSchStPt11amWedCnt = newPreDefColumn(pdstLeedSchedSetPts, "Days with Same 11am Value");
        pdchLeedSchStPt11pmWednesday = newPreDefColumn(pdstLeedSchedSetPts, "11pm First Wednesday [C]");
        pdchLeedSchStPt11pmWedCnt = newPreDefColumn(pdstLeedSchedSetPts, "Days with Same 11pm Value");
    }

    void PreDefTableEntry(int const columnIndex, std::string const &objName, Real64 const tableEntryReal, Optional_int_const numSigDigits)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Creates an entry for predefined tables when the entry
        //   is a real variable

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        thread_local static gio::Fmt fmtI1("(I1)");

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        int sigDigitCount;
        std::string digitString;
        std::string formatConvert;
        std::string stringEntry;
        int IOS;

        incrementTableEntry();
        // check for number of significant digits
        if (present(numSigDigits)) {
            if ((numSigDigits <= 9) && (numSigDigits >= 0)) {
                sigDigitCount = numSigDigits;
            } else {
                sigDigitCount = 2;
            }
        } else {
            sigDigitCount = 2;
        }
        // convert the integer to a string for the number of digits
        gio::write(digitString, fmtI1) << sigDigitCount;
        // build up the format string
        if (tableEntryReal < 1e8) { // change from 1e10 for more robust entry writing
            formatConvert = "(F12." + digitString + ')';
        } else {
            formatConvert = "(E12." + digitString + ')';
        }
        {
            IOFlags flags;
            gio::write(stringEntry, formatConvert, flags) << tableEntryReal;
            IOS = flags.ios();
        }
        if (IOS != 0) stringEntry = "  Too Big";
        tableEntry(numTableEntry).charEntry = stringEntry;
        tableEntry(numTableEntry).objectName = objName;
        tableEntry(numTableEntry).indexColumn = columnIndex;
        tableEntry(numTableEntry).origRealEntry = tableEntryReal;
        tableEntry(numTableEntry).significantDigits = sigDigitCount;
        tableEntry(numTableEntry).origEntryIsReal = true;
    }

    void PreDefTableEntry(int const columnIndex, std::string const &objName, std::string const &tableEntryChar)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Creates an entry for predefined tables when the entry
        //   is a character variable

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:

        incrementTableEntry();
        tableEntry(numTableEntry).charEntry = tableEntryChar;
        tableEntry(numTableEntry).objectName = objName;
        tableEntry(numTableEntry).indexColumn = columnIndex;
    }

    void PreDefTableEntry(int const columnIndex, std::string const &objName, int const tableEntryInt)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Creates an entry for predefined tables when the entry
        //   is a integer variable

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        thread_local static gio::Fmt fmtLD("*");

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        std::string stringEntry;

        incrementTableEntry();
        // convert the integer to a string
        gio::write(stringEntry, fmtLD) << tableEntryInt;
        tableEntry(numTableEntry).charEntry = stringEntry;
        tableEntry(numTableEntry).objectName = objName;
        tableEntry(numTableEntry).indexColumn = columnIndex;
    }

    std::string RetrievePreDefTableEntry(int const columnIndex, std::string const &objName)
    {
        for (int iTableEntry = 1; iTableEntry <= numTableEntry; ++iTableEntry) {
            if (tableEntry(iTableEntry).indexColumn == columnIndex && tableEntry(iTableEntry).objectName == objName) {
                return trimmed(ljustified(tableEntry(iTableEntry).charEntry));
                break;
            }
        }
        return "NOT FOUND";
    }

    void incrementTableEntry()
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Manages the resizing of the TableEntry Array

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // SUBROUTINE ARGUMENT DEFINITIONS:
        // na

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        if (!allocated(tableEntry)) {
            tableEntry.allocate(sizeIncrement);
            sizeTableEntry = sizeIncrement;
            numTableEntry = 1;
        } else {
            ++numTableEntry;
            // if larger than current size grow the array
            if (numTableEntry > sizeTableEntry) {
                tableEntry.redimension(sizeTableEntry *=
                                       2); // Tuned Changed += sizeIncrement to *= 2 for reduced heap allocations (at some space cost)
            }
        }
    }

    void
    AddCompSizeTableEntry(std::string const &FieldType, std::string const &FieldName, std::string const &FieldDescription, Real64 const FieldValue)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   July 2007
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Creates an entry for component size tables.

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:

        if (!allocated(CompSizeTableEntry)) {
            CompSizeTableEntry.allocate(sizeIncrement);
            sizeCompSizeTableEntry = sizeIncrement;
            numCompSizeTableEntry = 1;
        } else {
            ++numCompSizeTableEntry;
            // if larger than current size grow the array
            if (numCompSizeTableEntry > sizeCompSizeTableEntry) {
                CompSizeTableEntry.redimension(sizeCompSizeTableEntry *=
                                               2); // Tuned Changed += sizeIncrement to *= 2 for reduced heap allocations (at some space cost)
            }
        }
        CompSizeTableEntry(numCompSizeTableEntry).typeField = FieldType;
        CompSizeTableEntry(numCompSizeTableEntry).nameField = FieldName;
        CompSizeTableEntry(numCompSizeTableEntry).description = FieldDescription;
        CompSizeTableEntry(numCompSizeTableEntry).valField = FieldValue;
    }

    void AddShadowRelateTableEntry(int const castingField, int const receivingField, int const receivingKind)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   July 2007
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Creates an entry for any shadow hierarchy tables that consist
        //   of items and one or more subitems for each item.

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:
        // CHARACTER(len=*),INTENT(IN)  :: castingField
        // CHARACTER(len=*),INTENT(IN)  :: receivingField

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:

        if (!allocated(ShadowRelate)) {
            ShadowRelate.allocate(sizeIncrement);
            sizeShadowRelate = sizeIncrement;
            numShadowRelate = 1;
        } else {
            ++numShadowRelate;
            // if larger than current size grow the array
            if (numShadowRelate > sizeShadowRelate) {
                ShadowRelate.redimension(sizeShadowRelate *=
                                         2); // Tuned Changed += sizeIncrement to *= 2 for reduced heap allocations (at some space cost)
            }
        }
        ShadowRelate(numShadowRelate).castSurf = castingField;
        ShadowRelate(numShadowRelate).recSurf = receivingField;
        ShadowRelate(numShadowRelate).recKind = receivingKind;
    }

    int newPreDefReport(std::string const &inReportName, std::string const &inReportAbrev, std::string const &inReportNamewithSpaces)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Creates a new index for the next predefined report

        // METHODOLOGY EMPLOYED:
        // na

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Return value
        int newPreDefReport;

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:
        // na

        // SUBROUTINE PARAMETER DEFINITIONS:

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        if (!allocated(reportName)) {
            reportName.allocate(sizeIncrement);
            sizeReportName = sizeIncrement;
            numReportName = 1;
        } else {
            ++numReportName;
            // if larger than current size grow the array
            if (numReportName > sizeReportName) {
                reportName.redimension(sizeReportName *=
                                       2); // Tuned Changed += sizeIncrement to *= 2 for reduced heap allocations (at some space cost)
            }
        }
        // initialize new record
        reportName(numReportName).name = inReportName;
        reportName(numReportName).abrev = inReportAbrev;
        reportName(numReportName).namewithspaces = inReportNamewithSpaces;
        reportName(numReportName).show = false;
        newPreDefReport = numReportName;
        return newPreDefReport;
    }

    int newPreDefSubTable(int const reportIndex, std::string const &subTableName)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Assigns the index for predefined sub-tables

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Return value

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        if (!allocated(subTable)) {
            subTable.allocate(sizeIncrement);
            sizeSubTable = sizeIncrement;
            numSubTable = 1;
        } else {
            ++numSubTable;
            // if larger than current size then grow the array
            if (numSubTable > sizeSubTable) {
                subTable.redimension(sizeSubTable *= 2); // Tuned Changed += sizeIncrement to *= 2 for reduced heap allocations (at some space cost)
            }
        }
        // initialize new record)
        subTable(numSubTable).name = subTableName;
        subTable(numSubTable).indexReportName = reportIndex;
        return numSubTable;
    }

    void addFootNoteSubTable(int const subTableIndex, std::string const &footnoteText)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2008
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Adds a footnote to a subtable

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        if ((subTableIndex >= 0) && (subTableIndex <= numSubTable)) {
            subTable(subTableIndex).footnote = footnoteText;
        }
    }

    int newPreDefColumn(int const subTableIndex, std::string const &columnHeading)
    {
        // SUBROUTINE INFORMATION:
        //       AUTHOR         Jason Glazer
        //       DATE WRITTEN   August 2006
        //       MODIFIED
        //       RE-ENGINEERED  na

        // PURPOSE OF THIS SUBROUTINE:
        //   Assigns the index variables for all predefined reports

        // METHODOLOGY EMPLOYED:
        //   Simple assignments to public variables.

        // REFERENCES:
        // na

        // USE STATEMENTS:

        // Return value
        int newPreDefColumn;

        // Locals
        // SUBROUTINE ARGUMENT DEFINITIONS:

        // SUBROUTINE PARAMETER DEFINITIONS:
        // na

        // INTERFACE BLOCK SPECIFICATIONS:
        // na

        // DERIVED TYPE DEFINITIONS:
        // na

        // SUBROUTINE LOCAL VARIABLE DECLARATIONS:
        if (!allocated(columnTag)) {
            columnTag.allocate(sizeIncrement);
            sizeColumnTag = sizeIncrement;
            numColumnTag = 1;
        } else {
            ++numColumnTag;
            // if larger than current size grow the array
            if (numColumnTag > sizeColumnTag) {
                columnTag.redimension(sizeColumnTag *= 2); // Tuned Changed += sizeIncrement to *= 2 for reduced heap allocations (at some space cost)
            }
        }
        // initialize new record)
        columnTag(numColumnTag).heading = columnHeading;
        columnTag(numColumnTag).indexSubTable = subTableIndex;
        newPreDefColumn = numColumnTag;
        return newPreDefColumn;
    }

} // namespace OutputReportPredefined

} // namespace EnergyPlus
