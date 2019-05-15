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

#ifndef OutputReportPredefined_hh_INCLUDED
#define OutputReportPredefined_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>
#include <ObjexxFCL/Optional.hh>

// EnergyPlus Headers
#include <DataGlobals.hh>
#include <EnergyPlus.hh>

namespace EnergyPlus {

namespace OutputReportPredefined {

    // Using/Aliasing

    // Data
    // The following section initializes the predefined column heading variables
    // The variables get their value in AssignPredefined

    // Climate Summary Report
    thread_local extern int pdrClim;
    thread_local extern int pdstDesDay;
    thread_local extern int pdchDDmaxDB;
    thread_local extern int pdchDDrange;
    thread_local extern int pdchDDhumid;
    thread_local extern int pdchDDhumTyp;
    thread_local extern int pdchDDwindSp;
    thread_local extern int pdchDDwindDr;
    thread_local extern int pdstWthr;
    thread_local extern int pdchWthrVal;

    // HVAC Equipment Report
    thread_local extern int pdrEquip;
    thread_local extern int pdstMech;
    thread_local extern int pdchMechType;
    thread_local extern int pdchMechNomCap;
    thread_local extern int pdchMechNomEff;
    thread_local extern int pdchMechIPLVSI;
    thread_local extern int pdchMechIPLVIP;
    // Fan subtable
    thread_local extern int pdstFan;
    thread_local extern int pdchFanType;
    thread_local extern int pdchFanTotEff;
    thread_local extern int pdchFanDeltaP;
    thread_local extern int pdchFanVolFlow;
    thread_local extern int pdchFanMotorIn;
    thread_local extern int pdchFanEnergyIndex;
    thread_local extern int pdchFanEndUse;
    thread_local extern int pdchFanPwr;
    thread_local extern int pdchFanPwrPerFlow;
    thread_local extern int pdchFanDesDay;
    thread_local extern int pdchFanPkTime;
    // Pump subtable
    thread_local extern int pdstPump;
    thread_local extern int pdchPumpType;
    thread_local extern int pdchPumpControl;
    thread_local extern int pdchPumpHead;
    thread_local extern int pdchPumpFlow;
    thread_local extern int pdchPumpPower;
    thread_local extern int pdchPumpPwrPerFlow;
    thread_local extern int pdchMotEff;
    // Cooling coil subtable
    thread_local extern int pdstCoolCoil;
    thread_local extern int pdchCoolCoilType;
    thread_local extern int pdchCoolCoilDesCap;
    thread_local extern int pdchCoolCoilTotCap;
    thread_local extern int pdchCoolCoilSensCap;
    thread_local extern int pdchCoolCoilLatCap;
    thread_local extern int pdchCoolCoilSHR;
    thread_local extern int pdchCoolCoilNomEff;
    thread_local extern int pdchCoolCoilUATotal;
    thread_local extern int pdchCoolCoilArea;

    // DX Cooling Coil subtable
    thread_local extern int pdstDXCoolCoil;
    thread_local extern int pdchDXCoolCoilType; // DX cooling coil type

    thread_local extern int pdchDXCoolCoilNetCapSI; // Standard Rated (Net) Cooling Capacity [W]
    thread_local extern int pdchDXCoolCoilCOP;      // EER/COP value in SI unit at AHRI std. 340/360 conditions [W/W]
    thread_local extern int pdchDXCoolCoilSEERIP;   // SEER value in IP unit at AHRI std. 210/240 conditions [Btu/W-hr]
    thread_local extern int pdchDXCoolCoilEERIP;    // EER value in IP unit at AHRI std. 340/360 conditions [Btu/W-h]
    thread_local extern int pdchDXCoolCoilIEERIP;   // IEER value in IP unit at AHRI std. 340/360 conditions

    // DX Cooling Coil subtable per ANSI/ASHRAE Std 127 for Tests A, B, C and D
    thread_local extern int pdstDXCoolCoil2;
    thread_local extern int pdchDXCoolCoilNetCapSIA;  // Standard Rated (Net) Cooling Capacity [W], Test A
    thread_local extern int pdchDXCoolCoilElecPowerA; // Standard Rated Electric Power [W], Test A
    thread_local extern int pdchDXCoolCoilNetCapSIB;  // Standard Rated (Net) Cooling Capacity [W], Test B
    thread_local extern int pdchDXCoolCoilElecPowerB; // Standard Rated Electric Power [W], Test B
    thread_local extern int pdchDXCoolCoilNetCapSIC;  // Standard Rated (Net) Cooling Capacity [W], Test C
    thread_local extern int pdchDXCoolCoilElecPowerC; // Standard Rated Electric Power [W], Test C
    thread_local extern int pdchDXCoolCoilNetCapSID;  // Standard Rated (Net) Cooling Capacity [W], Test D
    thread_local extern int pdchDXCoolCoilElecPowerD; // Standard Rated Electric Power [W], Test D

    // VAV DX Cooling Ratings Details
    thread_local extern int pdstVAVDXCoolCoil; // details for Packaged VAV rating under AHRI 340/360
    thread_local extern int pdchVAVDXCoolCoilType;
    thread_local extern int pdchVAVDXFanName;
    thread_local extern int pdchVAVDXCoolCoilNetCapSI;
    thread_local extern int pdchVAVDXCoolCoilCOP;
    thread_local extern int pdchVAVDXCoolCoilIEERIP;
    thread_local extern int pdchVAVDXCoolCoilEERIP;
    thread_local extern int pdchVAVDXCoolCoilMdotA;
    thread_local extern int pdchVAVDXCoolCoilCOP_B;
    thread_local extern int pdchVAVDXCoolCoilEER_B_IP;
    thread_local extern int pdchVAVDXCoolCoilMdotB;
    thread_local extern int pdchVAVDXCoolCoilCOP_C;
    thread_local extern int pdchVAVDXCoolCoilEER_C_IP;
    thread_local extern int pdchVAVDXCoolCoilMdotC;
    thread_local extern int pdchVAVDXCoolCoilCOP_D;
    thread_local extern int pdchVAVDXCoolCoilEER_D_IP;
    thread_local extern int pdchVAVDXCoolCoilMdotD;

    // DX Heating Coil subtable
    thread_local extern int pdstDXHeatCoil;
    thread_local extern int pdchDXHeatCoilType; // DX Heating coil type
    thread_local extern int pdchDXHeatCoilHighCap;
    thread_local extern int pdchDXHeatCoilLowCap;
    thread_local extern int pdchDXHeatCoilHSPFSI;    // HSPF value in SI unit at AHRI std. 340/360 conditions [W/W]
    thread_local extern int pdchDXHeatCoilHSPFIP;    // HSPF value in IP unit at AHRI std. 340/360 conditions [Btu/W-hr]
    thread_local extern int pdchDXHeatCoilRegionNum; // Region number for which HSPF is calculated

    // Heating Coil subtable
    thread_local extern int pdstHeatCoil;
    thread_local extern int pdchHeatCoilType;
    thread_local extern int pdchHeatCoilDesCap;
    thread_local extern int pdchHeatCoilNomCap;
    thread_local extern int pdchHeatCoilNomEff;
    // SWH subtable
    thread_local extern int pdstSWH;
    thread_local extern int pdchSWHType;
    thread_local extern int pdchSWHVol;
    thread_local extern int pdchSWHHeatIn;
    thread_local extern int pdchSWHThEff;
    thread_local extern int pdchSWHRecEff;
    thread_local extern int pdchSWHEnFac;

    // Envelope Report
    thread_local extern int pdrEnvelope;
    thread_local extern int pdstOpaque;
    thread_local extern int pdchOpCons;
    thread_local extern int pdchOpRefl;
    thread_local extern int pdchOpUfactFilm;
    thread_local extern int pdchOpUfactNoFilm;
    thread_local extern int pdchOpGrArea;
    thread_local extern int pdchOpNetArea;
    thread_local extern int pdchOpAzimuth;
    thread_local extern int pdchOpTilt;
    thread_local extern int pdchOpDir;
    thread_local extern int pdstFen;
    thread_local extern int pdchFenCons;
    thread_local extern int pdchFenAreaOf1;
    thread_local extern int pdchFenGlassAreaOf1;
    thread_local extern int pdchFenFrameAreaOf1;
    thread_local extern int pdchFenDividerAreaOf1;
    thread_local extern int pdchFenArea;
    thread_local extern int pdchFenUfact;
    thread_local extern int pdchFenSHGC;
    thread_local extern int pdchFenVisTr;
    thread_local extern int pdchFenFrameConductance;
    thread_local extern int pdchFenDividerConductance;
    thread_local extern int pdchFenSwitchable;
    thread_local extern int pdchFenParent;
    thread_local extern int pdchFenAzimuth;
    thread_local extern int pdchFenTilt;
    thread_local extern int pdchFenDir;
    thread_local extern int pdstDoor;
    thread_local extern int pdchDrCons;
    thread_local extern int pdchDrUfactFilm;
    thread_local extern int pdchDrUfactNoFilm;
    thread_local extern int pdchDrGrArea;
    thread_local extern int pdchDrParent;
    thread_local extern int pdstIntFen;
    thread_local extern int pdchIntFenCons;
    thread_local extern int pdchIntFenAreaOf1;
    // Include these if interzone windows ever get frame and dividers
    // INTEGER :: pdchIntFenGlassAreaOf1
    // INTEGER :: pdchIntFenFrameAreaOf1
    // INTEGER :: pdchIntFenDividerAreaOf1
    // INTEGER :: pdchIntFenFrameConductance
    // INTEGER :: pdchIntFenDividerConductance
    thread_local extern int pdchIntFenArea;
    thread_local extern int pdchIntFenUfact;
    thread_local extern int pdchIntFenSHGC;
    thread_local extern int pdchIntFenVisTr;
    thread_local extern int pdchIntFenParent;

    // Shading Report
    thread_local extern int pdrShading;
    thread_local extern int pdstSunlitFrac;
    thread_local extern int pdchSlfMar21_9;
    thread_local extern int pdchSlfMar21_12;
    thread_local extern int pdchSlfMar21_15;
    thread_local extern int pdchSlfJun21_9;
    thread_local extern int pdchSlfJun21_12;
    thread_local extern int pdchSlfJun21_15;
    thread_local extern int pdchSlfDec21_9;
    thread_local extern int pdchSlfDec21_12;
    thread_local extern int pdchSlfDec21_15;
    thread_local extern int pdstWindowControl;
    thread_local extern int pdchWscName;
    thread_local extern int pdchWscShading;
    thread_local extern int pdchWscShadCons;
    thread_local extern int pdchWscControl;
    thread_local extern int pdchWscGlare;

    // Lighting Report
    thread_local extern int pdrLighting;
    thread_local extern int pdstInLite;
    thread_local extern int pdchInLtZone;
    thread_local extern int pdchInLtDens;
    thread_local extern int pdchInLtArea;
    thread_local extern int pdchInLtPower;
    thread_local extern int pdchInLtEndUse;
    thread_local extern int pdchInLtSchd;
    thread_local extern int pdchInLtAvgHrSchd;
    thread_local extern int pdchInLtAvgHrOper;
    thread_local extern int pdchInLtFullLoadHrs;
    thread_local extern int pdchInLtRetAir;
    thread_local extern int pdchInLtCond;
    thread_local extern int pdchInLtConsump;
    thread_local extern int pdstExtLite;
    thread_local extern int pdchExLtPower;
    thread_local extern int pdchExLtClock;
    thread_local extern int pdchExLtSchd;
    thread_local extern int pdchExLtAvgHrSchd;
    thread_local extern int pdchExLtAvgHrOper;
    thread_local extern int pdchExLtFullLoadHrs;
    thread_local extern int pdchExLtConsump;
    thread_local extern int pdstDaylight;
    thread_local extern int pdchDyLtZone;
    thread_local extern int pdchDyLtCtrlName;
    thread_local extern int pdchDyLtKind;
    thread_local extern int pdchDyLtCtrlType;
    thread_local extern int pdchDyLtFrac;
    thread_local extern int pdchDyLtWInst;
    thread_local extern int pdchDyLtWCtrl;

    // Sizing Report
    thread_local extern int pdrSizing;
    thread_local extern int pdstZoneClSize;
    thread_local extern int pdchZnClCalcDesLd;
    thread_local extern int pdchZnClUserDesLd;
    thread_local extern int pdchZnClUserDesLdPerArea;
    thread_local extern int pdchZnClCalcDesAirFlow;
    thread_local extern int pdchZnClUserDesAirFlow;
    thread_local extern int pdchZnClDesDay;
    thread_local extern int pdchZnClPkTime;
    thread_local extern int pdchZnClPkTstatTemp;
    thread_local extern int pdchZnClPkIndTemp;
    thread_local extern int pdchZnClPkIndHum;
    thread_local extern int pdchZnClPkOATemp;
    thread_local extern int pdchZnClPkOAHum;
    thread_local extern int pdchZnClPkOAMinFlow;
    thread_local extern int pdchZnClPkDOASHeatGain;
    thread_local extern int pdstZoneHtSize;
    thread_local extern int pdchZnHtCalcDesLd;
    thread_local extern int pdchZnHtUserDesLd;
    thread_local extern int pdchZnHtUserDesLdPerArea;
    thread_local extern int pdchZnHtCalcDesAirFlow;
    thread_local extern int pdchZnHtUserDesAirFlow;
    thread_local extern int pdchZnHtDesDay;
    thread_local extern int pdchZnHtPkTime;
    thread_local extern int pdchZnHtPkTstatTemp;
    thread_local extern int pdchZnHtPkIndTemp;
    thread_local extern int pdchZnHtPkIndHum;
    thread_local extern int pdchZnHtPkOATemp;
    thread_local extern int pdchZnHtPkOAHum;
    thread_local extern int pdchZnHtPkOAMinFlow;
    thread_local extern int pdchZnHtPkDOASHeatGain;
    thread_local extern int pdstSystemSize;
    thread_local extern int pdchSysSizCalcClAir;
    thread_local extern int pdchSysSizUserClAir;
    thread_local extern int pdchSysSizCalcHtAir;
    thread_local extern int pdchSysSizUserHtAir;
    thread_local extern int pdchSysSizAdjustedClAir;
    thread_local extern int pdchSysSizAdjustedHtAir;
    thread_local extern int pdchSysSizAdjustedMainAir;
    thread_local extern int pdchSysSizCalcHeatFlowRatio;
    thread_local extern int pdchSysSizUserHeatFlowRatio;
    thread_local extern int pdstPlantSize;
    thread_local extern int pdchPlantSizCalcVdot;
    thread_local extern int pdchPlantSizMeasVdot;
    thread_local extern int pdchPlantSizPrevVdot;
    //	extern int pdchPlantSizPass;
    thread_local extern int pdchPlantSizCoincYesNo;
    thread_local extern int pdchPlantSizDesDay;
    thread_local extern int pdchPlantSizPkTimeDayOfSim;
    thread_local extern int pdchPlantSizPkTimeHour;
    thread_local extern int pdchPlantSizPkTimeMin;

    // Coil Sizing Details
    thread_local extern int pdrCoilSizingDetailsTable;
    thread_local extern int pdstCoilSummaryCoilSelection;
    thread_local extern int pdchCoilName;
    thread_local extern int pdchCoilLocation;
    thread_local extern int pdchCoilHVACType;
    thread_local extern int pdchCoilHVACName;
    thread_local extern int pdchCoilZoneName;
    thread_local extern int pdchCoilType;
    thread_local extern int pdchSysSizingMethCoinc;
    thread_local extern int pdchSysSizingMethCap;
    thread_local extern int pdchSysSizingMethAir;

    thread_local extern int pdchCoilIsCapAutosized;
    thread_local extern int pdchCoilIsAirFlowAutosized;
    thread_local extern int pdchCoilIsWaterFlowAutosized;
    thread_local extern int pdchCoilIsOATreated;

    thread_local extern int pdchCoilFinalTotalCap;
    thread_local extern int pdchCoilFinalSensCap;
    thread_local extern int pdchCoilFinalAirVolFlowRate;
    thread_local extern int pdchCoilFinalPlantVolFlowRate;

    thread_local extern int pdchCoilDDnameSensIdealPeak;
    thread_local extern int pdchCoilDateTimeSensIdealPeak;
    thread_local extern int pdchCoilDDnameTotIdealPeak;
    thread_local extern int pdchCoilDateTimeTotIdealPeak;
    thread_local extern int pdchCoilDDnameAirFlowIdealPeak;
    thread_local extern int pdchCoilDateTimeAirFlowIdealPeak;
    thread_local extern int pdchCoilTotalCapIdealPeak;
    thread_local extern int pdchCoilSensCapIdealPeak;
    thread_local extern int pdchCoilOffRatingCapacityModifierIdealPeak;
    thread_local extern int pdchCoilAirMassFlowIdealPeak;
    thread_local extern int pdchCoilAirVolumeFlowIdealPeak;
    thread_local extern int pdchCoilEntDryBulbIdealPeak;
    thread_local extern int pdchCoilEntWetBulbIdealPeak;
    thread_local extern int pdchCoilEntHumRatIdealPeak;
    thread_local extern int pdchCoilEntEnthalpyIdealPeak;
    thread_local extern int pdchCoilLvgDryBulbIdealPeak;
    thread_local extern int pdchCoilLvgWetBulbIdealPeak;
    thread_local extern int pdchCoilLvgHumRatIdealPeak;
    thread_local extern int pdchCoilLvgEnthalpyIdealPeak;
    thread_local extern int pdchCoilWaterMassFlowIdealPeak;
    thread_local extern int pdchCoilEntWaterTempIdealPeak;
    thread_local extern int pdchCoilLvgWaterTempIdealPeak;
    thread_local extern int pdchCoilWaterDeltaTempIdealPeak;
    thread_local extern int pdchCoilRatedTotalCap;
    thread_local extern int pdchCoilRatedSensCap;
    thread_local extern int pdchCoilRatedAirMass;
    thread_local extern int pdchCoilRatedEntDryBulb;
    thread_local extern int pdchCoilRatedEntWetBulb;
    thread_local extern int pdchCoilRatedEntHumRat;
    thread_local extern int pdchCoilRatedEntEnthalpy;
    thread_local extern int pdchCoilRatedLvgDryBulb;
    thread_local extern int pdchCoilRatedLvgWetBulb;
    thread_local extern int pdchCoilRatedLvgHumRat;
    thread_local extern int pdchCoilRatedLvgEnthalpy;

    thread_local extern int pdchFanAssociatedWithCoilName;
    thread_local extern int pdchFanAssociatedWithCoilType;
    thread_local extern int pdchFanAssociatedVdotSize;
    thread_local extern int pdchFanAssociatedMdotSize;

    thread_local extern int pdchFanHeatGainIdealPeak;
    thread_local extern int pdchCoilNetTotalCapacityIdealPeak;
    thread_local extern int pdchCoilPlantLoopName;
    thread_local extern int pdchPlantMassFlowMaximum;
    thread_local extern int pdchPlantRetTempDesign;
    thread_local extern int pdchPlantSupTempDesign;
    thread_local extern int pdchPlantDeltaTempDesign;
    thread_local extern int pdchPlantCapacity;
    thread_local extern int pdchCoilCapPrcntPlantCapacity;
    thread_local extern int pdchCoilFlowPrcntPlantFlow;
    thread_local extern int pdchOADryBulbIdealPeak;
    thread_local extern int pdchOAHumRatIdealPeak;
    thread_local extern int pdchOAWetBulbatIdealPeak;
    thread_local extern int pdchOAVolFlowIdealPeak;
    thread_local extern int pdchOAFlowPrcntIdealPeak;
    thread_local extern int pdchAirSysRADryBulbIdealPeak;
    thread_local extern int pdchAirSysRAHumRatIdealPeak;
    thread_local extern int pdchZoneAirDryBulbIdealPeak;
    thread_local extern int pdchZoneAirHumRatIdealPeak;
    thread_local extern int pdchZoneAirRelHumIdealPeak;
    //	extern int pdchAirSysFanHeatGain;
    thread_local extern int pdchCoilUA;
    thread_local extern int pdchZoneSensibleLoadIdealPeak;
    thread_local extern int pdchZoneLatentLoadIdealPeak;
    thread_local extern int pdchCoilIdealSizCapOverSimPeak;
    thread_local extern int pdchCoilIdealSizCapUnderSimPeak;
    thread_local extern int pdchReheatCoilMultiplier;
    thread_local extern int pdchFlowCapRatioLowCapIncreaseRatio;
    thread_local extern int pdchFlowCapRatioHiCapDecreaseRatio;
    thread_local extern int pdchPlantFluidSpecificHeat;
    thread_local extern int pdchPlantFluidDensity;
    thread_local extern int pdchMoistAirSpecificHeat;
    thread_local extern int pdchDryAirSpecificHeat;
    thread_local extern int pdchStandRhoAir;

    // Coil Sizing Summary (subset of Coil Selection Table)
    thread_local extern int pdst2CoilSummaryCoilSelection;
    thread_local extern int pdch2CoilName;
    thread_local extern int pdch2CoilType;
    thread_local extern int pdch2CoilHVACType;
    thread_local extern int pdch2CoilHVACName;

    thread_local extern int pdch2CoilFinalTotalCap;
    thread_local extern int pdch2CoilFinalSensCap;
    thread_local extern int pdch2CoilFinalAirVolFlowRate;
    thread_local extern int pdch2CoilFinalPlantVolFlowRate;
    thread_local extern int pdch2CoilUA;

    thread_local extern int pdch2CoilDDnameSensIdealPeak;
    thread_local extern int pdch2CoilDateTimeSensIdealPeak;
    thread_local extern int pdch2CoilDDnameAirFlowIdealPeak;
    thread_local extern int pdch2CoilDateTimeAirFlowIdealPeak;
    thread_local extern int pdch2CoilTotalCapIdealPeak;
    thread_local extern int pdch2CoilSensCapIdealPeak;
    thread_local extern int pdch2CoilAirVolumeFlowIdealPeak;
    thread_local extern int pdch2CoilEntDryBulbIdealPeak;
    thread_local extern int pdch2CoilEntWetBulbIdealPeak;
    thread_local extern int pdch2CoilEntHumRatIdealPeak;
    thread_local extern int pdch2CoilLvgDryBulbIdealPeak;
    thread_local extern int pdch2CoilLvgWetBulbIdealPeak;
    thread_local extern int pdch2CoilLvgHumRatIdealPeak;
    thread_local extern int pdch2CoilRatedTotalCap;
    thread_local extern int pdch2CoilRatedSensCap;

    thread_local extern int pdch2OADryBulbIdealPeak;
    thread_local extern int pdch2OAHumRatIdealPeak;
    thread_local extern int pdch2OAWetBulbatIdealPeak;
    thread_local extern int pdch2OAFlowPrcntIdealPeak;
    thread_local extern int pdch2ZoneAirDryBulbIdealPeak;
    thread_local extern int pdch2ZoneAirHumRatIdealPeak;
    thread_local extern int pdch2ZoneAirRelHumIdealPeak;
    thread_local extern int pdch2ZoneSensibleLoadIdealPeak;
    thread_local extern int pdch2ZoneLatentLoadIdealPeak;

    // System summary
    thread_local extern int pdrSystem;
    thread_local extern int pdstEconomizer;
    thread_local extern int pdchEcoKind;
    thread_local extern int pdchEcoMinOA;
    thread_local extern int pdchEcoMaxOA;
    thread_local extern int pdchEcoRetTemp;
    thread_local extern int pdchEcoRetEnth;
    thread_local extern int pdchEcoOATempLim;
    thread_local extern int pdchEcoOAEnthLim;
    thread_local extern int pdstDemCntlVent;
    thread_local extern int pdchDCVventMechName;
    thread_local extern int pdchDCVperPerson;
    thread_local extern int pdchDCVperArea;
    thread_local extern int pdchDCVperZone;
    thread_local extern int pdchDCVperACH;
    thread_local extern int pdchDCVMethod;
    thread_local extern int pdchDCVOASchName;

    // added for new DCV
    thread_local extern int pdchDCVZoneADEffCooling;
    thread_local extern int pdchDCVZoneADEffHeating;
    thread_local extern int pdchDCVZoneADEffSchName;

    thread_local extern int pdstSimpleComfort;
    thread_local extern int pdchSCwinterClothes;
    thread_local extern int pdchSCsummerClothes;
    thread_local extern int pdchSCeitherClothes;
    thread_local extern int pdstUnmetLoads;
    thread_local extern int pdchULnotMetHeat;
    thread_local extern int pdchULnotMetCool;
    thread_local extern int pdchULnotMetHeatOcc;
    thread_local extern int pdchULnotMetCoolOcc;

    // Outside Air Report
    thread_local extern int pdrOutsideAir;
    thread_local extern int pdstOAavgOcc;
    thread_local extern int pdchOaoAvgNumOcc1;
    thread_local extern int pdchOaoNomNumOcc1;
    thread_local extern int pdchOaoZoneVol1;
    thread_local extern int pdchOaoAvgMechVent;
    thread_local extern int pdchOaoAvgInfil;
    thread_local extern int pdchOaoAvgAFNInfil;
    thread_local extern int pdchOaoAvgSimpVent;
    thread_local extern int pdchOaoAvgTotVent;
    thread_local extern int pdstOAminOcc;
    thread_local extern int pdchOaoAvgNumOcc2;
    thread_local extern int pdchOaoNomNumOcc2;
    thread_local extern int pdchOaoZoneVol2;
    thread_local extern int pdchOaoMinMechVent;
    thread_local extern int pdchOaoMinInfil;
    thread_local extern int pdchOaoMinAFNInfil;
    thread_local extern int pdchOaoMinSimpVent;
    thread_local extern int pdchOaoMinTotVent;

    // Object Count Report
    thread_local extern int pdrObjCnt;
    thread_local extern int pdstSurfCnt;
    thread_local extern int pdchSurfCntTot;
    thread_local extern int pdchSurfCntExt;
    thread_local extern int pdstHVACcnt;
    thread_local extern int pdchHVACcntVal;
    thread_local extern int pdstFieldCnt;
    thread_local extern int pdchFieldCntVal;

    // Energy Meters Report
    thread_local extern int pdrEnergyMeters;

    thread_local extern int pdstEMelecvalues;
    thread_local extern int pdchEMelecannual;
    thread_local extern int pdchEMelecminvalue;
    thread_local extern int pdchEMelecminvaluetime;
    thread_local extern int pdchEMelecmaxvalue;
    thread_local extern int pdchEMelecmaxvaluetime;

    thread_local extern int pdstEMgasvalues;
    thread_local extern int pdchEMgasannual;
    thread_local extern int pdchEMgasminvalue;
    thread_local extern int pdchEMgasminvaluetime;
    thread_local extern int pdchEMgasmaxvalue;
    thread_local extern int pdchEMgasmaxvaluetime;

    thread_local extern int pdstEMcoolvalues;
    thread_local extern int pdchEMcoolannual;
    thread_local extern int pdchEMcoolminvalue;
    thread_local extern int pdchEMcoolminvaluetime;
    thread_local extern int pdchEMcoolmaxvalue;
    thread_local extern int pdchEMcoolmaxvaluetime;

    thread_local extern int pdstEMwatervalues;
    thread_local extern int pdchEMwaterannual;
    thread_local extern int pdchEMwaterminvalue;
    thread_local extern int pdchEMwaterminvaluetime;
    thread_local extern int pdchEMwatermaxvalue;
    thread_local extern int pdchEMwatermaxvaluetime;

    thread_local extern int pdstEMotherJvalues;
    thread_local extern int pdchEMotherJannual;
    thread_local extern int pdchEMotherJminvalue;
    thread_local extern int pdchEMotherJminvaluetime;
    thread_local extern int pdchEMotherJmaxvalue;
    thread_local extern int pdchEMotherJmaxvaluetime;

    thread_local extern int pdstEMotherKGvalues;
    thread_local extern int pdchEMotherKGannual;
    thread_local extern int pdchEMotherKGminvalue;
    thread_local extern int pdchEMotherKGminvaluetime;
    thread_local extern int pdchEMotherKGmaxvalue;
    thread_local extern int pdchEMotherKGmaxvaluetime;

    thread_local extern int pdstEMotherM3values;
    thread_local extern int pdchEMotherM3annual;
    thread_local extern int pdchEMotherM3minvalue;
    thread_local extern int pdchEMotherM3minvaluetime;
    thread_local extern int pdchEMotherM3maxvalue;
    thread_local extern int pdchEMotherM3maxvaluetime;

    thread_local extern int pdstEMotherLvalues;
    thread_local extern int pdchEMotherLannual;
    thread_local extern int pdchEMotherLminvalue;
    thread_local extern int pdchEMotherLminvaluetime;
    thread_local extern int pdchEMotherLmaxvalue;
    thread_local extern int pdchEMotherLmaxvaluetime;

    // Sensible Heat Gas Component Report
    thread_local extern int pdrSensibleGain;
    // annual
    thread_local extern int pdstSHGSannual;
    thread_local extern int pdchSHGSAnHvacHt;
    thread_local extern int pdchSHGSAnHvacCl;
    thread_local extern int pdchSHGSAnHvacATUHt;
    thread_local extern int pdchSHGSAnHvacATUCl;
    thread_local extern int pdchSHGSAnSurfHt;
    thread_local extern int pdchSHGSAnSurfCl;
    thread_local extern int pdchSHGSAnPeoplAdd;
    thread_local extern int pdchSHGSAnLiteAdd;
    thread_local extern int pdchSHGSAnEquipAdd;
    thread_local extern int pdchSHGSAnWindAdd;
    thread_local extern int pdchSHGSAnIzaAdd;
    thread_local extern int pdchSHGSAnInfilAdd;
    thread_local extern int pdchSHGSAnOtherAdd;
    thread_local extern int pdchSHGSAnEquipRem;
    thread_local extern int pdchSHGSAnWindRem;
    thread_local extern int pdchSHGSAnIzaRem;
    thread_local extern int pdchSHGSAnInfilRem;
    thread_local extern int pdchSHGSAnOtherRem;
    // peak cooling
    thread_local extern int pdstSHGSpkCl;
    thread_local extern int pdchSHGSClTimePeak;
    thread_local extern int pdchSHGSClHvacHt;
    thread_local extern int pdchSHGSClHvacCl;
    thread_local extern int pdchSHGSClHvacATUHt;
    thread_local extern int pdchSHGSClHvacATUCl;
    thread_local extern int pdchSHGSClSurfHt;
    thread_local extern int pdchSHGSClSurfCl;
    thread_local extern int pdchSHGSClPeoplAdd;
    thread_local extern int pdchSHGSClLiteAdd;
    thread_local extern int pdchSHGSClEquipAdd;
    thread_local extern int pdchSHGSClWindAdd;
    thread_local extern int pdchSHGSClIzaAdd;
    thread_local extern int pdchSHGSClInfilAdd;
    thread_local extern int pdchSHGSClOtherAdd;
    thread_local extern int pdchSHGSClEquipRem;
    thread_local extern int pdchSHGSClWindRem;
    thread_local extern int pdchSHGSClIzaRem;
    thread_local extern int pdchSHGSClInfilRem;
    thread_local extern int pdchSHGSClOtherRem;
    // peak heating
    thread_local extern int pdstSHGSpkHt;
    thread_local extern int pdchSHGSHtTimePeak;
    thread_local extern int pdchSHGSHtHvacHt;
    thread_local extern int pdchSHGSHtHvacCl;
    thread_local extern int pdchSHGSHtHvacATUHt;
    thread_local extern int pdchSHGSHtHvacATUCl;
    thread_local extern int pdchSHGSHtSurfHt;
    thread_local extern int pdchSHGSHtSurfCl;
    thread_local extern int pdchSHGSHtPeoplAdd;
    thread_local extern int pdchSHGSHtLiteAdd;
    thread_local extern int pdchSHGSHtEquipAdd;
    thread_local extern int pdchSHGSHtWindAdd;
    thread_local extern int pdchSHGSHtIzaAdd;
    thread_local extern int pdchSHGSHtInfilAdd;
    thread_local extern int pdchSHGSHtOtherAdd;
    thread_local extern int pdchSHGSHtEquipRem;
    thread_local extern int pdchSHGSHtWindRem;
    thread_local extern int pdchSHGSHtIzaRem;
    thread_local extern int pdchSHGSHtInfilRem;
    thread_local extern int pdchSHGSHtOtherRem;
    // Standard62Report
    thread_local extern int pdrStd62;
    thread_local extern int pdstS62sysVentReqCool;
    thread_local extern int pdchS62svrClSumVpz;
    thread_local extern int pdchS62svrClPs;
    thread_local extern int pdchS62svrClSumPz;
    thread_local extern int pdchS62svrClD;
    thread_local extern int pdchS62svrClVou;
    thread_local extern int pdchS62svrClVps;
    thread_local extern int pdchS62svrClXs;
    thread_local extern int pdchS62svrClEv;
    thread_local extern int pdchS62svrClVot;
    thread_local extern int pdchS62svrClPercOA;
    thread_local extern int pdchS62svrClEnvironmentOfPs;
    thread_local extern int pdchS62svrClTimeOfPs;

    thread_local extern int pdstS62sysVentReqHeat;
    thread_local extern int pdchS62svrHtSumVpz;
    thread_local extern int pdchS62svrHtPs;
    thread_local extern int pdchS62svrHtSumPz;
    thread_local extern int pdchS62svrHtD;
    thread_local extern int pdchS62svrHtVou;
    thread_local extern int pdchS62svrHtVps;
    thread_local extern int pdchS62svrHtXs;
    thread_local extern int pdchS62svrHtEv;
    thread_local extern int pdchS62svrHtVot;
    thread_local extern int pdchS62svrHtPercOA;
    thread_local extern int pdchS62svrHtEnvironmentOfPs;
    thread_local extern int pdchS62svrHtTimeOfPs;

    thread_local extern int pdstS62znVentPar;
    thread_local extern int pdchS62zvpAlN;
    thread_local extern int pdchS62zvpRp;
    thread_local extern int pdchS62zvpPz;
    thread_local extern int pdchS62zvpRa;
    thread_local extern int pdchS62zvpAz;
    thread_local extern int pdchS62zvpVbz;
    thread_local extern int pdchS62zvpClEz;
    thread_local extern int pdchS62zvpClVoz;
    thread_local extern int pdchS62zvpHtEz;
    thread_local extern int pdchS62zvpHtVoz;

    thread_local extern int pdstS62sysVentPar;
    thread_local extern int pdchS62svpRp;
    thread_local extern int pdchS62svpPz;
    thread_local extern int pdchS62svpRa;
    thread_local extern int pdchS62svpAz;
    thread_local extern int pdchS62svpVbz;
    thread_local extern int pdchS62svpClVoz;
    thread_local extern int pdchS62svpHtVoz;

    thread_local extern int pdstS62znCoolDes;
    thread_local extern int pdchS62zcdAlN;
    thread_local extern int pdchS62zcdBox;
    thread_local extern int pdchS62zcdVpz;
    thread_local extern int pdchS62zcdVps;
    thread_local extern int pdchS62zcdVsec;
    thread_local extern int pdchS62zcdVdz;
    thread_local extern int pdchS62zcdVpzmin;
    thread_local extern int pdchS62zcdVozclg;
    thread_local extern int pdchS62zcdZpz;
    thread_local extern int pdchS62zcdEp;
    thread_local extern int pdchS62zcdEr;
    thread_local extern int pdchS62zcdFa;
    thread_local extern int pdchS62zcdFb;
    thread_local extern int pdchS62zcdFc;
    thread_local extern int pdchS62zcdEvz;

    thread_local extern int pdstS62sysCoolDes;
    thread_local extern int pdchS62scdVpz;
    thread_local extern int pdchS62scdVps;
    thread_local extern int pdchS62scdVsec;
    thread_local extern int pdchS62scdVdz;
    thread_local extern int pdchS62scdVpzmin;
    thread_local extern int pdchS62scdVozclg;
    thread_local extern int pdchS62scdEvz;

    thread_local extern int pdstS62znHeatDes;
    thread_local extern int pdchS62zhdAlN;
    thread_local extern int pdchS62zhdBox;
    thread_local extern int pdchS62zhdVpz;
    thread_local extern int pdchS62zhdVps;
    thread_local extern int pdchS62zhdVsec;
    thread_local extern int pdchS62zhdVdz;
    thread_local extern int pdchS62zhdVpzmin;
    thread_local extern int pdchS62zhdVozhtg;
    thread_local extern int pdchS62zhdZpz;
    thread_local extern int pdchS62zhdEp;
    thread_local extern int pdchS62zhdEr;
    thread_local extern int pdchS62zhdFa;
    thread_local extern int pdchS62zhdFb;
    thread_local extern int pdchS62zhdFc;
    thread_local extern int pdchS62zhdEvz;

    thread_local extern int pdstS62sysHeatDes;
    thread_local extern int pdchS62shdVpz;
    thread_local extern int pdchS62shdVps;
    thread_local extern int pdchS62shdVsec;
    thread_local extern int pdchS62shdVdz;
    thread_local extern int pdchS62shdVpzmin;
    thread_local extern int pdchS62shdVozhtg;
    thread_local extern int pdchS62shdEvz;

    //  LEED Summary
    thread_local extern int pdrLeed;
    thread_local extern int pdstLeedGenInfo;
    thread_local extern int pdchLeedGenData;

    thread_local extern int pdstLeedSpaceUsageType;
    thread_local extern int pdchLeedSutName;
    thread_local extern int pdchLeedSutSpArea;
    thread_local extern int pdchLeedSutOcArea;
    thread_local extern int pdchLeedSutUnArea;
    thread_local extern int pdchLeedSutHrsWeek;

    thread_local extern int pdstLeedAdvsMsg;
    thread_local extern int pdchLeedAmData;

    thread_local extern int pdstLeedEneTypSum;
    thread_local extern int pdchLeedEtsType;
    thread_local extern int pdchLeedEtsRtNm;
    thread_local extern int pdchLeedEtsVirt;
    thread_local extern int pdchLeedEtsEneUnt;
    thread_local extern int pdchLeedEtsDemUnt;

    thread_local extern int pdstLeedPerf;
    thread_local extern int pdchLeedPerfRot;
    thread_local extern int pdchLeedPerfElEneUse;
    thread_local extern int pdchLeedPerfElDem;
    thread_local extern int pdchLeedPerfGasEneUse;
    thread_local extern int pdchLeedPerfGasDem;
    thread_local extern int pdchLeedPerfAddFuelEneUse;
    thread_local extern int pdchLeedPerfAddFuelDem;
    thread_local extern int pdchLeedPerfDisClEneUse;
    thread_local extern int pdchLeedPerfDisClDem;
    thread_local extern int pdchLeedPerfDisHtEneUse;
    thread_local extern int pdchLeedPerfDisHtDem;

    thread_local extern int pdstLeedEneUseSum;
    thread_local extern int pdchLeedEusUnt;
    thread_local extern int pdchLeedEusProc;
    thread_local extern int pdchLeedEusTotal;

    thread_local extern int pdstLeedEneCostSum;
    thread_local extern int pdchLeedEcUnt;
    thread_local extern int pdchLeedEcsProc;
    thread_local extern int pdchLeedEcsTotal;
    thread_local extern Real64 LEEDelecCostTotal;
    thread_local extern Real64 LEEDgasCostTotal;
    thread_local extern Real64 LEEDothrCostTotal;

    thread_local extern int pdstLeedRenewSum;
    thread_local extern int pdchLeedRenRatCap;
    thread_local extern int pdchLeedRenAnGen;

    thread_local extern int pdstLeedEneUseIntEl;
    thread_local extern int pdchLeedEuiElec;
    thread_local extern int pdstLeedEneUseIntNatG;
    thread_local extern int pdchLeedEuiNatG;
    thread_local extern int pdstLeedEneUseIntOthr;
    thread_local extern int pdchLeedEuiOthr;

    thread_local extern int pdstLeedEneUsePerc;
    thread_local extern int pdchLeedEupPerc;

    thread_local extern int pdstLeedEqFlLdHrs;
    thread_local extern int pdchLeedEflhEflh;
    thread_local extern int pdchLeedEflhNonZerHrs;

    thread_local extern int pdstLeedSchedSetPts;
    thread_local extern int pdChLeedSchStPtFirstObjUsed;
    thread_local extern int pdChLeedSchStPtMonthUsed;
    thread_local extern int pdchLeedSchStPt11amWednesday;
    thread_local extern int pdchLeedSchStPt11amWedCnt;
    thread_local extern int pdchLeedSchStPt11pmWednesday;
    thread_local extern int pdchLeedSchStPt11pmWedCnt;

    // Internal data structures to store information provided by calls

    thread_local extern int const sizeIncrement;

    thread_local extern int sizeReportName;
    thread_local extern int numReportName;

    thread_local extern int sizeSubTable;
    thread_local extern int numSubTable;

    thread_local extern int sizeColumnTag;
    thread_local extern int numColumnTag;

    thread_local extern int sizeTableEntry;
    thread_local extern int numTableEntry;

    thread_local extern int sizeCompSizeTableEntry;
    thread_local extern int numCompSizeTableEntry;

    thread_local extern int sizeShadowRelate;
    thread_local extern int numShadowRelate;
    thread_local extern int const recKindSurface;
    thread_local extern int const recKindSubsurface;

    thread_local extern Real64 TotalNotMetHeatingOccupiedForABUPS;
    thread_local extern Real64 TotalNotMetCoolingOccupiedForABUPS;
    thread_local extern Real64 TotalNotMetOccupiedForABUPS;
    thread_local extern Real64 TotalTimeNotSimpleASH55EitherForABUPS;

    // Types

    struct reportNameType
    {
        // Members
        std::string name;
        std::string namewithspaces; // a "prettier version" than the key value
        std::string abrev;
        bool show;

        // Default Constructor
        reportNameType() : show(false)
        {
        }
    };

    struct SubTableType
    {
        // Members
        std::string name;
        int indexReportName;
        std::string footnote;

        // Default Constructor
        SubTableType() : indexReportName(0)
        {
        }
    };

    struct ColumnTagType
    {
        // Members
        std::string heading;
        int indexSubTable;

        // Default Constructor
        ColumnTagType() : indexSubTable(0)
        {
        }
    };

    struct TableEntryType
    {
        // Members
        std::string charEntry;
        std::string objectName;
        int indexColumn;
        int subTableIndex;
        int uniqueObjName;
        Real64 origRealEntry;
        int significantDigits;
        bool origEntryIsReal;

        // Default Constructor
        TableEntryType() : indexColumn(0), subTableIndex(0), uniqueObjName(0), origRealEntry(0.0), significantDigits(0), origEntryIsReal(false)
        {
        }
    };

    struct CompSizeTableEntryType
    {
        // Members
        std::string typeField;
        std::string nameField;
        std::string description;
        Real64 valField;
        bool active;
        bool written;

        // Default Constructor
        CompSizeTableEntryType() : valField(0.0), active(false), written(false)
        {
        }
    };

    struct ShadowRelateType
    {
        // Members
        //  CHARACTER(len=MaxNameLength)  :: castSurf          = ''
        //  CHARACTER(len=MaxNameLength)  :: recSurf           = ''
        int castSurf;
        int recSurf;
        int recKind;

        // Default Constructor
        ShadowRelateType() : castSurf(0), recSurf(0), recKind(0)
        {
        }
    };

    // Object Data
    thread_local extern Array1D<reportNameType> reportName;
    thread_local extern Array1D<SubTableType> subTable;
    thread_local extern Array1D<ColumnTagType> columnTag;
    thread_local extern Array1D<TableEntryType> tableEntry;
    thread_local extern Array1D<CompSizeTableEntryType> CompSizeTableEntry;
    thread_local extern Array1D<ShadowRelateType> ShadowRelate;

    // Functions
    void clear_state();

    void SetPredefinedTables();

    void PreDefTableEntry(int const columnIndex, std::string const &objName, Real64 const tableEntryReal, Optional_int_const numSigDigits = _);

    void PreDefTableEntry(int const columnIndex, std::string const &objName, std::string const &tableEntryChar);

    void PreDefTableEntry(int const columnIndex, std::string const &objName, int const tableEntryInt);

    std::string RetrievePreDefTableEntry(int const columnIndex, std::string const &objName);

    void incrementTableEntry();

    void
    AddCompSizeTableEntry(std::string const &FieldType, std::string const &FieldName, std::string const &FieldDescription, Real64 const FieldValue);

    void AddShadowRelateTableEntry(int const castingField, int const receivingField, int const receivingKind);

    int newPreDefReport(std::string const &inReportName, std::string const &inReportAbrev, std::string const &inReportNamewithSpaces);

    int newPreDefSubTable(int const reportIndex, std::string const &subTableName);

    void addFootNoteSubTable(int const subTableIndex, std::string const &footnoteText);

    int newPreDefColumn(int const subTableIndex, std::string const &columnHeading);

} // namespace OutputReportPredefined

} // namespace EnergyPlus

#endif
