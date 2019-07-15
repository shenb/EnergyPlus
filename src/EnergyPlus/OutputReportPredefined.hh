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
    EP_GLOBAL extern int pdrClim;
    EP_GLOBAL extern int pdstDesDay;
    EP_GLOBAL extern int pdchDDmaxDB;
    EP_GLOBAL extern int pdchDDrange;
    EP_GLOBAL extern int pdchDDhumid;
    EP_GLOBAL extern int pdchDDhumTyp;
    EP_GLOBAL extern int pdchDDwindSp;
    EP_GLOBAL extern int pdchDDwindDr;
    EP_GLOBAL extern int pdstWthr;
    EP_GLOBAL extern int pdchWthrVal;

    // HVAC Equipment Report
    EP_GLOBAL extern int pdrEquip;
    EP_GLOBAL extern int pdstMech;
    EP_GLOBAL extern int pdchMechType;
    EP_GLOBAL extern int pdchMechNomCap;
    EP_GLOBAL extern int pdchMechNomEff;
    EP_GLOBAL extern int pdchMechIPLVSI;
    EP_GLOBAL extern int pdchMechIPLVIP;
    // Fan subtable
    EP_GLOBAL extern int pdstFan;
    EP_GLOBAL extern int pdchFanType;
    EP_GLOBAL extern int pdchFanTotEff;
    EP_GLOBAL extern int pdchFanDeltaP;
    EP_GLOBAL extern int pdchFanVolFlow;
    EP_GLOBAL extern int pdchFanMotorIn;
    EP_GLOBAL extern int pdchFanEnergyIndex;
    EP_GLOBAL extern int pdchFanEndUse;
    EP_GLOBAL extern int pdchFanPwr;
    EP_GLOBAL extern int pdchFanPwrPerFlow;
    EP_GLOBAL extern int pdchFanDesDay;
    EP_GLOBAL extern int pdchFanPkTime;
    // Pump subtable
    EP_GLOBAL extern int pdstPump;
    EP_GLOBAL extern int pdchPumpType;
    EP_GLOBAL extern int pdchPumpControl;
    EP_GLOBAL extern int pdchPumpHead;
    EP_GLOBAL extern int pdchPumpFlow;
    EP_GLOBAL extern int pdchPumpPower;
    EP_GLOBAL extern int pdchPumpPwrPerFlow;
    EP_GLOBAL extern int pdchPumpEndUse;
    EP_GLOBAL extern int pdchMotEff;
    // Cooling coil subtable
    EP_GLOBAL extern int pdstCoolCoil;
    EP_GLOBAL extern int pdchCoolCoilType;
    EP_GLOBAL extern int pdchCoolCoilDesCap;
    EP_GLOBAL extern int pdchCoolCoilTotCap;
    EP_GLOBAL extern int pdchCoolCoilSensCap;
    EP_GLOBAL extern int pdchCoolCoilLatCap;
    EP_GLOBAL extern int pdchCoolCoilSHR;
    EP_GLOBAL extern int pdchCoolCoilNomEff;
    EP_GLOBAL extern int pdchCoolCoilUATotal;
    EP_GLOBAL extern int pdchCoolCoilArea;

    // DX Cooling Coil subtable
    EP_GLOBAL extern int pdstDXCoolCoil;
    EP_GLOBAL extern int pdchDXCoolCoilType; // DX cooling coil type

    EP_GLOBAL extern int pdchDXCoolCoilNetCapSI; // Standard Rated (Net) Cooling Capacity [W]
    EP_GLOBAL extern int pdchDXCoolCoilCOP;      // EER/COP value in SI unit at AHRI std. 340/360 conditions [W/W]
    EP_GLOBAL extern int pdchDXCoolCoilSEERIP;   // SEER value in IP unit at AHRI std. 210/240 conditions [Btu/W-hr]
    EP_GLOBAL extern int pdchDXCoolCoilEERIP;    // EER value in IP unit at AHRI std. 340/360 conditions [Btu/W-h]
    EP_GLOBAL extern int pdchDXCoolCoilIEERIP;   // IEER value in IP unit at AHRI std. 340/360 conditions

    // DX Cooling Coil subtable per ANSI/ASHRAE Std 127 for Tests A, B, C and D
    EP_GLOBAL extern int pdstDXCoolCoil2;
    EP_GLOBAL extern int pdchDXCoolCoilNetCapSIA;  // Standard Rated (Net) Cooling Capacity [W], Test A
    EP_GLOBAL extern int pdchDXCoolCoilElecPowerA; // Standard Rated Electric Power [W], Test A
    EP_GLOBAL extern int pdchDXCoolCoilNetCapSIB;  // Standard Rated (Net) Cooling Capacity [W], Test B
    EP_GLOBAL extern int pdchDXCoolCoilElecPowerB; // Standard Rated Electric Power [W], Test B
    EP_GLOBAL extern int pdchDXCoolCoilNetCapSIC;  // Standard Rated (Net) Cooling Capacity [W], Test C
    EP_GLOBAL extern int pdchDXCoolCoilElecPowerC; // Standard Rated Electric Power [W], Test C
    EP_GLOBAL extern int pdchDXCoolCoilNetCapSID;  // Standard Rated (Net) Cooling Capacity [W], Test D
    EP_GLOBAL extern int pdchDXCoolCoilElecPowerD; // Standard Rated Electric Power [W], Test D

    // VAV DX Cooling Ratings Details
    EP_GLOBAL extern int pdstVAVDXCoolCoil; // details for Packaged VAV rating under AHRI 340/360
    EP_GLOBAL extern int pdchVAVDXCoolCoilType;
    EP_GLOBAL extern int pdchVAVDXFanName;
    EP_GLOBAL extern int pdchVAVDXCoolCoilNetCapSI;
    EP_GLOBAL extern int pdchVAVDXCoolCoilCOP;
    EP_GLOBAL extern int pdchVAVDXCoolCoilIEERIP;
    EP_GLOBAL extern int pdchVAVDXCoolCoilEERIP;
    EP_GLOBAL extern int pdchVAVDXCoolCoilMdotA;
    EP_GLOBAL extern int pdchVAVDXCoolCoilCOP_B;
    EP_GLOBAL extern int pdchVAVDXCoolCoilEER_B_IP;
    EP_GLOBAL extern int pdchVAVDXCoolCoilMdotB;
    EP_GLOBAL extern int pdchVAVDXCoolCoilCOP_C;
    EP_GLOBAL extern int pdchVAVDXCoolCoilEER_C_IP;
    EP_GLOBAL extern int pdchVAVDXCoolCoilMdotC;
    EP_GLOBAL extern int pdchVAVDXCoolCoilCOP_D;
    EP_GLOBAL extern int pdchVAVDXCoolCoilEER_D_IP;
    EP_GLOBAL extern int pdchVAVDXCoolCoilMdotD;

    // DX Heating Coil subtable
    EP_GLOBAL extern int pdstDXHeatCoil;
    EP_GLOBAL extern int pdchDXHeatCoilType; // DX Heating coil type
    EP_GLOBAL extern int pdchDXHeatCoilHighCap;
    EP_GLOBAL extern int pdchDXHeatCoilLowCap;
    EP_GLOBAL extern int pdchDXHeatCoilHSPFSI;    // HSPF value in SI unit at AHRI std. 340/360 conditions [W/W]
    EP_GLOBAL extern int pdchDXHeatCoilHSPFIP;    // HSPF value in IP unit at AHRI std. 340/360 conditions [Btu/W-hr]
    EP_GLOBAL extern int pdchDXHeatCoilRegionNum; // Region number for which HSPF is calculated

    // Heating Coil subtable
    EP_GLOBAL extern int pdstHeatCoil;
    EP_GLOBAL extern int pdchHeatCoilType;
    EP_GLOBAL extern int pdchHeatCoilDesCap;
    EP_GLOBAL extern int pdchHeatCoilNomCap;
    EP_GLOBAL extern int pdchHeatCoilNomEff;
    // SWH subtable
    EP_GLOBAL extern int pdstSWH;
    EP_GLOBAL extern int pdchSWHType;
    EP_GLOBAL extern int pdchSWHVol;
    EP_GLOBAL extern int pdchSWHHeatIn;
    EP_GLOBAL extern int pdchSWHThEff;
    EP_GLOBAL extern int pdchSWHRecEff;
    EP_GLOBAL extern int pdchSWHEnFac;

    // Envelope Report
    EP_GLOBAL extern int pdrEnvelope;
    EP_GLOBAL extern int pdstOpaque;
    EP_GLOBAL extern int pdchOpCons;
    EP_GLOBAL extern int pdchOpRefl;
    EP_GLOBAL extern int pdchOpUfactFilm;
    EP_GLOBAL extern int pdchOpUfactNoFilm;
    EP_GLOBAL extern int pdchOpGrArea;
    EP_GLOBAL extern int pdchOpNetArea;
    EP_GLOBAL extern int pdchOpAzimuth;
    EP_GLOBAL extern int pdchOpTilt;
    EP_GLOBAL extern int pdchOpDir;
    EP_GLOBAL extern int pdstFen;
    EP_GLOBAL extern int pdchFenCons;
    EP_GLOBAL extern int pdchFenAreaOf1;
    EP_GLOBAL extern int pdchFenGlassAreaOf1;
    EP_GLOBAL extern int pdchFenFrameAreaOf1;
    EP_GLOBAL extern int pdchFenDividerAreaOf1;
    EP_GLOBAL extern int pdchFenArea;
    EP_GLOBAL extern int pdchFenUfact;
    EP_GLOBAL extern int pdchFenSHGC;
    EP_GLOBAL extern int pdchFenVisTr;
    EP_GLOBAL extern int pdchFenFrameConductance;
    EP_GLOBAL extern int pdchFenDividerConductance;
    EP_GLOBAL extern int pdchFenSwitchable;
    EP_GLOBAL extern int pdchFenParent;
    EP_GLOBAL extern int pdchFenAzimuth;
    EP_GLOBAL extern int pdchFenTilt;
    EP_GLOBAL extern int pdchFenDir;
    EP_GLOBAL extern int pdstDoor;
    EP_GLOBAL extern int pdchDrCons;
    EP_GLOBAL extern int pdchDrUfactFilm;
    EP_GLOBAL extern int pdchDrUfactNoFilm;
    EP_GLOBAL extern int pdchDrGrArea;
    EP_GLOBAL extern int pdchDrParent;
    EP_GLOBAL extern int pdstIntFen;
    EP_GLOBAL extern int pdchIntFenCons;
    EP_GLOBAL extern int pdchIntFenAreaOf1;
    // Include these if interzone windows ever get frame and dividers
    // INTEGER :: pdchIntFenGlassAreaOf1
    // INTEGER :: pdchIntFenFrameAreaOf1
    // INTEGER :: pdchIntFenDividerAreaOf1
    // INTEGER :: pdchIntFenFrameConductance
    // INTEGER :: pdchIntFenDividerConductance
    EP_GLOBAL extern int pdchIntFenArea;
    EP_GLOBAL extern int pdchIntFenUfact;
    EP_GLOBAL extern int pdchIntFenSHGC;
    EP_GLOBAL extern int pdchIntFenVisTr;
    EP_GLOBAL extern int pdchIntFenParent;

    // Shading Report
    EP_GLOBAL extern int pdrShading;
    EP_GLOBAL extern int pdstSunlitFrac;
    EP_GLOBAL extern int pdchSlfMar21_9;
    EP_GLOBAL extern int pdchSlfMar21_12;
    EP_GLOBAL extern int pdchSlfMar21_15;
    EP_GLOBAL extern int pdchSlfJun21_9;
    EP_GLOBAL extern int pdchSlfJun21_12;
    EP_GLOBAL extern int pdchSlfJun21_15;
    EP_GLOBAL extern int pdchSlfDec21_9;
    EP_GLOBAL extern int pdchSlfDec21_12;
    EP_GLOBAL extern int pdchSlfDec21_15;
    EP_GLOBAL extern int pdstWindowControl;
    EP_GLOBAL extern int pdchWscName;
    EP_GLOBAL extern int pdchWscShading;
    EP_GLOBAL extern int pdchWscShadCons;
    EP_GLOBAL extern int pdchWscControl;
    EP_GLOBAL extern int pdchWscGlare;

    // Lighting Report
    EP_GLOBAL extern int pdrLighting;
    EP_GLOBAL extern int pdstInLite;
    EP_GLOBAL extern int pdchInLtZone;
    EP_GLOBAL extern int pdchInLtDens;
    EP_GLOBAL extern int pdchInLtArea;
    EP_GLOBAL extern int pdchInLtPower;
    EP_GLOBAL extern int pdchInLtEndUse;
    EP_GLOBAL extern int pdchInLtSchd;
    EP_GLOBAL extern int pdchInLtAvgHrSchd;
    EP_GLOBAL extern int pdchInLtAvgHrOper;
    EP_GLOBAL extern int pdchInLtFullLoadHrs;
    EP_GLOBAL extern int pdchInLtRetAir;
    EP_GLOBAL extern int pdchInLtCond;
    EP_GLOBAL extern int pdchInLtConsump;
    EP_GLOBAL extern int pdstExtLite;
    EP_GLOBAL extern int pdchExLtPower;
    EP_GLOBAL extern int pdchExLtClock;
    EP_GLOBAL extern int pdchExLtSchd;
    EP_GLOBAL extern int pdchExLtAvgHrSchd;
    EP_GLOBAL extern int pdchExLtAvgHrOper;
    EP_GLOBAL extern int pdchExLtFullLoadHrs;
    EP_GLOBAL extern int pdchExLtConsump;
    EP_GLOBAL extern int pdstDaylight;
    EP_GLOBAL extern int pdchDyLtZone;
    EP_GLOBAL extern int pdchDyLtCtrlName;
    EP_GLOBAL extern int pdchDyLtKind;
    EP_GLOBAL extern int pdchDyLtCtrlType;
    EP_GLOBAL extern int pdchDyLtFrac;
    EP_GLOBAL extern int pdchDyLtWInst;
    EP_GLOBAL extern int pdchDyLtWCtrl;

    // Sizing Report
    EP_GLOBAL extern int pdrSizing;
    EP_GLOBAL extern int pdstZoneClSize;
    EP_GLOBAL extern int pdchZnClCalcDesLd;
    EP_GLOBAL extern int pdchZnClUserDesLd;
    EP_GLOBAL extern int pdchZnClUserDesLdPerArea;
    EP_GLOBAL extern int pdchZnClCalcDesAirFlow;
    EP_GLOBAL extern int pdchZnClUserDesAirFlow;
    EP_GLOBAL extern int pdchZnClDesDay;
    EP_GLOBAL extern int pdchZnClPkTime;
    EP_GLOBAL extern int pdchZnClPkTstatTemp;
    EP_GLOBAL extern int pdchZnClPkIndTemp;
    EP_GLOBAL extern int pdchZnClPkIndHum;
    EP_GLOBAL extern int pdchZnClPkOATemp;
    EP_GLOBAL extern int pdchZnClPkOAHum;
    EP_GLOBAL extern int pdchZnClPkOAMinFlow;
    EP_GLOBAL extern int pdchZnClPkDOASHeatGain;
    EP_GLOBAL extern int pdstZoneHtSize;
    EP_GLOBAL extern int pdchZnHtCalcDesLd;
    EP_GLOBAL extern int pdchZnHtUserDesLd;
    EP_GLOBAL extern int pdchZnHtUserDesLdPerArea;
    EP_GLOBAL extern int pdchZnHtCalcDesAirFlow;
    EP_GLOBAL extern int pdchZnHtUserDesAirFlow;
    EP_GLOBAL extern int pdchZnHtDesDay;
    EP_GLOBAL extern int pdchZnHtPkTime;
    EP_GLOBAL extern int pdchZnHtPkTstatTemp;
    EP_GLOBAL extern int pdchZnHtPkIndTemp;
    EP_GLOBAL extern int pdchZnHtPkIndHum;
    EP_GLOBAL extern int pdchZnHtPkOATemp;
    EP_GLOBAL extern int pdchZnHtPkOAHum;
    EP_GLOBAL extern int pdchZnHtPkOAMinFlow;
    EP_GLOBAL extern int pdchZnHtPkDOASHeatGain;
    EP_GLOBAL extern int pdstSystemSize;
    EP_GLOBAL extern int pdchSysSizCalcClAir;
    EP_GLOBAL extern int pdchSysSizUserClAir;
    EP_GLOBAL extern int pdchSysSizCalcHtAir;
    EP_GLOBAL extern int pdchSysSizUserHtAir;
    EP_GLOBAL extern int pdchSysSizAdjustedClAir;
    EP_GLOBAL extern int pdchSysSizAdjustedHtAir;
    EP_GLOBAL extern int pdchSysSizAdjustedMainAir;
    EP_GLOBAL extern int pdchSysSizCalcHeatFlowRatio;
    EP_GLOBAL extern int pdchSysSizUserHeatFlowRatio;
    EP_GLOBAL extern int pdstPlantSize;
    EP_GLOBAL extern int pdchPlantSizCalcVdot;
    EP_GLOBAL extern int pdchPlantSizMeasVdot;
    EP_GLOBAL extern int pdchPlantSizPrevVdot;
    //	extern int pdchPlantSizPass;
    EP_GLOBAL extern int pdchPlantSizCoincYesNo;
    EP_GLOBAL extern int pdchPlantSizDesDay;
    EP_GLOBAL extern int pdchPlantSizPkTimeDayOfSim;
    EP_GLOBAL extern int pdchPlantSizPkTimeHour;
    EP_GLOBAL extern int pdchPlantSizPkTimeMin;

    // Coil Sizing Details
    EP_GLOBAL extern int pdrCoilSizingDetailsTable;
    EP_GLOBAL extern int pdstCoilSummaryCoilSelection;
    EP_GLOBAL extern int pdchCoilName;
    EP_GLOBAL extern int pdchCoilLocation;
    EP_GLOBAL extern int pdchCoilHVACType;
    EP_GLOBAL extern int pdchCoilHVACName;
    EP_GLOBAL extern int pdchCoilZoneName;
    EP_GLOBAL extern int pdchCoilType;
    EP_GLOBAL extern int pdchSysSizingMethCoinc;
    EP_GLOBAL extern int pdchSysSizingMethCap;
    EP_GLOBAL extern int pdchSysSizingMethAir;

    EP_GLOBAL extern int pdchCoilIsCapAutosized;
    EP_GLOBAL extern int pdchCoilIsAirFlowAutosized;
    EP_GLOBAL extern int pdchCoilIsWaterFlowAutosized;
    EP_GLOBAL extern int pdchCoilIsOATreated;

    EP_GLOBAL extern int pdchCoilFinalTotalCap;
    EP_GLOBAL extern int pdchCoilFinalSensCap;
    EP_GLOBAL extern int pdchCoilFinalAirVolFlowRate;
    EP_GLOBAL extern int pdchCoilFinalPlantVolFlowRate;

    EP_GLOBAL extern int pdchCoilDDnameSensIdealPeak;
    EP_GLOBAL extern int pdchCoilDateTimeSensIdealPeak;
    EP_GLOBAL extern int pdchCoilDDnameTotIdealPeak;
    EP_GLOBAL extern int pdchCoilDateTimeTotIdealPeak;
    EP_GLOBAL extern int pdchCoilDDnameAirFlowIdealPeak;
    EP_GLOBAL extern int pdchCoilDateTimeAirFlowIdealPeak;
    EP_GLOBAL extern int pdchCoilTotalCapIdealPeak;
    EP_GLOBAL extern int pdchCoilSensCapIdealPeak;
    EP_GLOBAL extern int pdchCoilOffRatingCapacityModifierIdealPeak;
    EP_GLOBAL extern int pdchCoilAirMassFlowIdealPeak;
    EP_GLOBAL extern int pdchCoilAirVolumeFlowIdealPeak;
    EP_GLOBAL extern int pdchCoilEntDryBulbIdealPeak;
    EP_GLOBAL extern int pdchCoilEntWetBulbIdealPeak;
    EP_GLOBAL extern int pdchCoilEntHumRatIdealPeak;
    EP_GLOBAL extern int pdchCoilEntEnthalpyIdealPeak;
    EP_GLOBAL extern int pdchCoilLvgDryBulbIdealPeak;
    EP_GLOBAL extern int pdchCoilLvgWetBulbIdealPeak;
    EP_GLOBAL extern int pdchCoilLvgHumRatIdealPeak;
    EP_GLOBAL extern int pdchCoilLvgEnthalpyIdealPeak;
    EP_GLOBAL extern int pdchCoilWaterMassFlowIdealPeak;
    EP_GLOBAL extern int pdchCoilEntWaterTempIdealPeak;
    EP_GLOBAL extern int pdchCoilLvgWaterTempIdealPeak;
    EP_GLOBAL extern int pdchCoilWaterDeltaTempIdealPeak;
    EP_GLOBAL extern int pdchCoilRatedTotalCap;
    EP_GLOBAL extern int pdchCoilRatedSensCap;
    EP_GLOBAL extern int pdchCoilRatedAirMass;
    EP_GLOBAL extern int pdchCoilRatedEntDryBulb;
    EP_GLOBAL extern int pdchCoilRatedEntWetBulb;
    EP_GLOBAL extern int pdchCoilRatedEntHumRat;
    EP_GLOBAL extern int pdchCoilRatedEntEnthalpy;
    EP_GLOBAL extern int pdchCoilRatedLvgDryBulb;
    EP_GLOBAL extern int pdchCoilRatedLvgWetBulb;
    EP_GLOBAL extern int pdchCoilRatedLvgHumRat;
    EP_GLOBAL extern int pdchCoilRatedLvgEnthalpy;

    EP_GLOBAL extern int pdchFanAssociatedWithCoilName;
    EP_GLOBAL extern int pdchFanAssociatedWithCoilType;
    EP_GLOBAL extern int pdchFanAssociatedVdotSize;
    EP_GLOBAL extern int pdchFanAssociatedMdotSize;

    EP_GLOBAL extern int pdchFanHeatGainIdealPeak;
    EP_GLOBAL extern int pdchCoilNetTotalCapacityIdealPeak;
    EP_GLOBAL extern int pdchCoilPlantLoopName;
    EP_GLOBAL extern int pdchPlantMassFlowMaximum;
    EP_GLOBAL extern int pdchPlantRetTempDesign;
    EP_GLOBAL extern int pdchPlantSupTempDesign;
    EP_GLOBAL extern int pdchPlantDeltaTempDesign;
    EP_GLOBAL extern int pdchPlantCapacity;
    EP_GLOBAL extern int pdchCoilCapPrcntPlantCapacity;
    EP_GLOBAL extern int pdchCoilFlowPrcntPlantFlow;
    EP_GLOBAL extern int pdchOADryBulbIdealPeak;
    EP_GLOBAL extern int pdchOAHumRatIdealPeak;
    EP_GLOBAL extern int pdchOAWetBulbatIdealPeak;
    EP_GLOBAL extern int pdchOAVolFlowIdealPeak;
    EP_GLOBAL extern int pdchOAFlowPrcntIdealPeak;
    EP_GLOBAL extern int pdchAirSysRADryBulbIdealPeak;
    EP_GLOBAL extern int pdchAirSysRAHumRatIdealPeak;
    EP_GLOBAL extern int pdchZoneAirDryBulbIdealPeak;
    EP_GLOBAL extern int pdchZoneAirHumRatIdealPeak;
    EP_GLOBAL extern int pdchZoneAirRelHumIdealPeak;
    //	extern int pdchAirSysFanHeatGain;
    EP_GLOBAL extern int pdchCoilUA;
    EP_GLOBAL extern int pdchZoneSensibleLoadIdealPeak;
    EP_GLOBAL extern int pdchZoneLatentLoadIdealPeak;
    EP_GLOBAL extern int pdchCoilIdealSizCapOverSimPeak;
    EP_GLOBAL extern int pdchCoilIdealSizCapUnderSimPeak;
    EP_GLOBAL extern int pdchReheatCoilMultiplier;
    EP_GLOBAL extern int pdchFlowCapRatioLowCapIncreaseRatio;
    EP_GLOBAL extern int pdchFlowCapRatioHiCapDecreaseRatio;
    EP_GLOBAL extern int pdchPlantFluidSpecificHeat;
    EP_GLOBAL extern int pdchPlantFluidDensity;
    EP_GLOBAL extern int pdchMoistAirSpecificHeat;
    EP_GLOBAL extern int pdchDryAirSpecificHeat;
    EP_GLOBAL extern int pdchStandRhoAir;

    // Coil Sizing Summary (subset of Coil Selection Table)
    EP_GLOBAL extern int pdst2CoilSummaryCoilSelection;
    EP_GLOBAL extern int pdch2CoilName;
    EP_GLOBAL extern int pdch2CoilType;
    EP_GLOBAL extern int pdch2CoilHVACType;
    EP_GLOBAL extern int pdch2CoilHVACName;

    EP_GLOBAL extern int pdch2CoilFinalTotalCap;
    EP_GLOBAL extern int pdch2CoilFinalSensCap;
    EP_GLOBAL extern int pdch2CoilFinalAirVolFlowRate;
    EP_GLOBAL extern int pdch2CoilFinalPlantVolFlowRate;
    EP_GLOBAL extern int pdch2CoilUA;

    EP_GLOBAL extern int pdch2CoilDDnameSensIdealPeak;
    EP_GLOBAL extern int pdch2CoilDateTimeSensIdealPeak;
    EP_GLOBAL extern int pdch2CoilDDnameAirFlowIdealPeak;
    EP_GLOBAL extern int pdch2CoilDateTimeAirFlowIdealPeak;
    EP_GLOBAL extern int pdch2CoilTotalCapIdealPeak;
    EP_GLOBAL extern int pdch2CoilSensCapIdealPeak;
    EP_GLOBAL extern int pdch2CoilAirVolumeFlowIdealPeak;
    EP_GLOBAL extern int pdch2CoilEntDryBulbIdealPeak;
    EP_GLOBAL extern int pdch2CoilEntWetBulbIdealPeak;
    EP_GLOBAL extern int pdch2CoilEntHumRatIdealPeak;
    EP_GLOBAL extern int pdch2CoilLvgDryBulbIdealPeak;
    EP_GLOBAL extern int pdch2CoilLvgWetBulbIdealPeak;
    EP_GLOBAL extern int pdch2CoilLvgHumRatIdealPeak;
    EP_GLOBAL extern int pdch2CoilRatedTotalCap;
    EP_GLOBAL extern int pdch2CoilRatedSensCap;

    EP_GLOBAL extern int pdch2OADryBulbIdealPeak;
    EP_GLOBAL extern int pdch2OAHumRatIdealPeak;
    EP_GLOBAL extern int pdch2OAWetBulbatIdealPeak;
    EP_GLOBAL extern int pdch2OAFlowPrcntIdealPeak;
    EP_GLOBAL extern int pdch2ZoneAirDryBulbIdealPeak;
    EP_GLOBAL extern int pdch2ZoneAirHumRatIdealPeak;
    EP_GLOBAL extern int pdch2ZoneAirRelHumIdealPeak;
    EP_GLOBAL extern int pdch2ZoneSensibleLoadIdealPeak;
    EP_GLOBAL extern int pdch2ZoneLatentLoadIdealPeak;

    // System summary
    EP_GLOBAL extern int pdrSystem;
    EP_GLOBAL extern int pdstEconomizer;
    EP_GLOBAL extern int pdchEcoKind;
    EP_GLOBAL extern int pdchEcoMinOA;
    EP_GLOBAL extern int pdchEcoMaxOA;
    EP_GLOBAL extern int pdchEcoRetTemp;
    EP_GLOBAL extern int pdchEcoRetEnth;
    EP_GLOBAL extern int pdchEcoOATempLim;
    EP_GLOBAL extern int pdchEcoOAEnthLim;
    EP_GLOBAL extern int pdstDemCntlVent;
    EP_GLOBAL extern int pdchDCVventMechName;
    EP_GLOBAL extern int pdchDCVperPerson;
    EP_GLOBAL extern int pdchDCVperArea;
    EP_GLOBAL extern int pdchDCVperZone;
    EP_GLOBAL extern int pdchDCVperACH;
    EP_GLOBAL extern int pdchDCVMethod;
    EP_GLOBAL extern int pdchDCVOASchName;

    // added for new DCV
    EP_GLOBAL extern int pdchDCVZoneADEffCooling;
    EP_GLOBAL extern int pdchDCVZoneADEffHeating;
    EP_GLOBAL extern int pdchDCVZoneADEffSchName;

    EP_GLOBAL extern int pdstSimpleComfort;
    EP_GLOBAL extern int pdchSCwinterClothes;
    EP_GLOBAL extern int pdchSCsummerClothes;
    EP_GLOBAL extern int pdchSCeitherClothes;
    EP_GLOBAL extern int pdstUnmetLoads;
    EP_GLOBAL extern int pdchULnotMetHeat;
    EP_GLOBAL extern int pdchULnotMetCool;
    EP_GLOBAL extern int pdchULnotMetHeatOcc;
    EP_GLOBAL extern int pdchULnotMetCoolOcc;

    // Outside Air Report
    EP_GLOBAL extern int pdrOutsideAir;
    EP_GLOBAL extern int pdstOAavgOcc;
    EP_GLOBAL extern int pdchOaoAvgNumOcc1;
    EP_GLOBAL extern int pdchOaoNomNumOcc1;
    EP_GLOBAL extern int pdchOaoZoneVol1;
    EP_GLOBAL extern int pdchOaoAvgMechVent;
    EP_GLOBAL extern int pdchOaoAvgInfil;
    EP_GLOBAL extern int pdchOaoAvgAFNInfil;
    EP_GLOBAL extern int pdchOaoAvgSimpVent;
    EP_GLOBAL extern int pdchOaoAvgTotVent;
    EP_GLOBAL extern int pdstOAminOcc;
    EP_GLOBAL extern int pdchOaoAvgNumOcc2;
    EP_GLOBAL extern int pdchOaoNomNumOcc2;
    EP_GLOBAL extern int pdchOaoZoneVol2;
    EP_GLOBAL extern int pdchOaoMinMechVent;
    EP_GLOBAL extern int pdchOaoMinInfil;
    EP_GLOBAL extern int pdchOaoMinAFNInfil;
    EP_GLOBAL extern int pdchOaoMinSimpVent;
    EP_GLOBAL extern int pdchOaoMinTotVent;

    // Object Count Report
    EP_GLOBAL extern int pdrObjCnt;
    EP_GLOBAL extern int pdstSurfCnt;
    EP_GLOBAL extern int pdchSurfCntTot;
    EP_GLOBAL extern int pdchSurfCntExt;
    EP_GLOBAL extern int pdstHVACcnt;
    EP_GLOBAL extern int pdchHVACcntVal;
    EP_GLOBAL extern int pdstFieldCnt;
    EP_GLOBAL extern int pdchFieldCntVal;

    // Energy Meters Report
    EP_GLOBAL extern int pdrEnergyMeters;

    EP_GLOBAL extern int pdstEMelecvalues;
    EP_GLOBAL extern int pdchEMelecannual;
    EP_GLOBAL extern int pdchEMelecminvalue;
    EP_GLOBAL extern int pdchEMelecminvaluetime;
    EP_GLOBAL extern int pdchEMelecmaxvalue;
    EP_GLOBAL extern int pdchEMelecmaxvaluetime;

    EP_GLOBAL extern int pdstEMgasvalues;
    EP_GLOBAL extern int pdchEMgasannual;
    EP_GLOBAL extern int pdchEMgasminvalue;
    EP_GLOBAL extern int pdchEMgasminvaluetime;
    EP_GLOBAL extern int pdchEMgasmaxvalue;
    EP_GLOBAL extern int pdchEMgasmaxvaluetime;

    EP_GLOBAL extern int pdstEMcoolvalues;
    EP_GLOBAL extern int pdchEMcoolannual;
    EP_GLOBAL extern int pdchEMcoolminvalue;
    EP_GLOBAL extern int pdchEMcoolminvaluetime;
    EP_GLOBAL extern int pdchEMcoolmaxvalue;
    EP_GLOBAL extern int pdchEMcoolmaxvaluetime;

    EP_GLOBAL extern int pdstEMwatervalues;
    EP_GLOBAL extern int pdchEMwaterannual;
    EP_GLOBAL extern int pdchEMwaterminvalue;
    EP_GLOBAL extern int pdchEMwaterminvaluetime;
    EP_GLOBAL extern int pdchEMwatermaxvalue;
    EP_GLOBAL extern int pdchEMwatermaxvaluetime;

    EP_GLOBAL extern int pdstEMotherJvalues;
    EP_GLOBAL extern int pdchEMotherJannual;
    EP_GLOBAL extern int pdchEMotherJminvalue;
    EP_GLOBAL extern int pdchEMotherJminvaluetime;
    EP_GLOBAL extern int pdchEMotherJmaxvalue;
    EP_GLOBAL extern int pdchEMotherJmaxvaluetime;

    EP_GLOBAL extern int pdstEMotherKGvalues;
    EP_GLOBAL extern int pdchEMotherKGannual;
    EP_GLOBAL extern int pdchEMotherKGminvalue;
    EP_GLOBAL extern int pdchEMotherKGminvaluetime;
    EP_GLOBAL extern int pdchEMotherKGmaxvalue;
    EP_GLOBAL extern int pdchEMotherKGmaxvaluetime;

    EP_GLOBAL extern int pdstEMotherM3values;
    EP_GLOBAL extern int pdchEMotherM3annual;
    EP_GLOBAL extern int pdchEMotherM3minvalue;
    EP_GLOBAL extern int pdchEMotherM3minvaluetime;
    EP_GLOBAL extern int pdchEMotherM3maxvalue;
    EP_GLOBAL extern int pdchEMotherM3maxvaluetime;

    EP_GLOBAL extern int pdstEMotherLvalues;
    EP_GLOBAL extern int pdchEMotherLannual;
    EP_GLOBAL extern int pdchEMotherLminvalue;
    EP_GLOBAL extern int pdchEMotherLminvaluetime;
    EP_GLOBAL extern int pdchEMotherLmaxvalue;
    EP_GLOBAL extern int pdchEMotherLmaxvaluetime;

    // Sensible Heat Gas Component Report
    EP_GLOBAL extern int pdrSensibleGain;
    // annual
    EP_GLOBAL extern int pdstSHGSannual;
    EP_GLOBAL extern int pdchSHGSAnHvacHt;
    EP_GLOBAL extern int pdchSHGSAnHvacCl;
    EP_GLOBAL extern int pdchSHGSAnHvacATUHt;
    EP_GLOBAL extern int pdchSHGSAnHvacATUCl;
    EP_GLOBAL extern int pdchSHGSAnSurfHt;
    EP_GLOBAL extern int pdchSHGSAnSurfCl;
    EP_GLOBAL extern int pdchSHGSAnPeoplAdd;
    EP_GLOBAL extern int pdchSHGSAnLiteAdd;
    EP_GLOBAL extern int pdchSHGSAnEquipAdd;
    EP_GLOBAL extern int pdchSHGSAnWindAdd;
    EP_GLOBAL extern int pdchSHGSAnIzaAdd;
    EP_GLOBAL extern int pdchSHGSAnInfilAdd;
    EP_GLOBAL extern int pdchSHGSAnOtherAdd;
    EP_GLOBAL extern int pdchSHGSAnEquipRem;
    EP_GLOBAL extern int pdchSHGSAnWindRem;
    EP_GLOBAL extern int pdchSHGSAnIzaRem;
    EP_GLOBAL extern int pdchSHGSAnInfilRem;
    EP_GLOBAL extern int pdchSHGSAnOtherRem;
    // peak cooling
    EP_GLOBAL extern int pdstSHGSpkCl;
    EP_GLOBAL extern int pdchSHGSClTimePeak;
    EP_GLOBAL extern int pdchSHGSClHvacHt;
    EP_GLOBAL extern int pdchSHGSClHvacCl;
    EP_GLOBAL extern int pdchSHGSClHvacATUHt;
    EP_GLOBAL extern int pdchSHGSClHvacATUCl;
    EP_GLOBAL extern int pdchSHGSClSurfHt;
    EP_GLOBAL extern int pdchSHGSClSurfCl;
    EP_GLOBAL extern int pdchSHGSClPeoplAdd;
    EP_GLOBAL extern int pdchSHGSClLiteAdd;
    EP_GLOBAL extern int pdchSHGSClEquipAdd;
    EP_GLOBAL extern int pdchSHGSClWindAdd;
    EP_GLOBAL extern int pdchSHGSClIzaAdd;
    EP_GLOBAL extern int pdchSHGSClInfilAdd;
    EP_GLOBAL extern int pdchSHGSClOtherAdd;
    EP_GLOBAL extern int pdchSHGSClEquipRem;
    EP_GLOBAL extern int pdchSHGSClWindRem;
    EP_GLOBAL extern int pdchSHGSClIzaRem;
    EP_GLOBAL extern int pdchSHGSClInfilRem;
    EP_GLOBAL extern int pdchSHGSClOtherRem;
    // peak heating
    EP_GLOBAL extern int pdstSHGSpkHt;
    EP_GLOBAL extern int pdchSHGSHtTimePeak;
    EP_GLOBAL extern int pdchSHGSHtHvacHt;
    EP_GLOBAL extern int pdchSHGSHtHvacCl;
    EP_GLOBAL extern int pdchSHGSHtHvacATUHt;
    EP_GLOBAL extern int pdchSHGSHtHvacATUCl;
    EP_GLOBAL extern int pdchSHGSHtSurfHt;
    EP_GLOBAL extern int pdchSHGSHtSurfCl;
    EP_GLOBAL extern int pdchSHGSHtPeoplAdd;
    EP_GLOBAL extern int pdchSHGSHtLiteAdd;
    EP_GLOBAL extern int pdchSHGSHtEquipAdd;
    EP_GLOBAL extern int pdchSHGSHtWindAdd;
    EP_GLOBAL extern int pdchSHGSHtIzaAdd;
    EP_GLOBAL extern int pdchSHGSHtInfilAdd;
    EP_GLOBAL extern int pdchSHGSHtOtherAdd;
    EP_GLOBAL extern int pdchSHGSHtEquipRem;
    EP_GLOBAL extern int pdchSHGSHtWindRem;
    EP_GLOBAL extern int pdchSHGSHtIzaRem;
    EP_GLOBAL extern int pdchSHGSHtInfilRem;
    EP_GLOBAL extern int pdchSHGSHtOtherRem;
    // Standard62Report
    EP_GLOBAL extern int pdrStd62;
    EP_GLOBAL extern int pdstS62sysVentReqCool;
    EP_GLOBAL extern int pdchS62svrClSumVpz;
    EP_GLOBAL extern int pdchS62svrClPs;
    EP_GLOBAL extern int pdchS62svrClSumPz;
    EP_GLOBAL extern int pdchS62svrClD;
    EP_GLOBAL extern int pdchS62svrClVou;
    EP_GLOBAL extern int pdchS62svrClVps;
    EP_GLOBAL extern int pdchS62svrClXs;
    EP_GLOBAL extern int pdchS62svrClEv;
    EP_GLOBAL extern int pdchS62svrClVot;
    EP_GLOBAL extern int pdchS62svrClPercOA;
    EP_GLOBAL extern int pdchS62svrClEnvironmentOfPs;
    EP_GLOBAL extern int pdchS62svrClTimeOfPs;

    EP_GLOBAL extern int pdstS62sysVentReqHeat;
    EP_GLOBAL extern int pdchS62svrHtSumVpz;
    EP_GLOBAL extern int pdchS62svrHtPs;
    EP_GLOBAL extern int pdchS62svrHtSumPz;
    EP_GLOBAL extern int pdchS62svrHtD;
    EP_GLOBAL extern int pdchS62svrHtVou;
    EP_GLOBAL extern int pdchS62svrHtVps;
    EP_GLOBAL extern int pdchS62svrHtXs;
    EP_GLOBAL extern int pdchS62svrHtEv;
    EP_GLOBAL extern int pdchS62svrHtVot;
    EP_GLOBAL extern int pdchS62svrHtPercOA;
    EP_GLOBAL extern int pdchS62svrHtEnvironmentOfPs;
    EP_GLOBAL extern int pdchS62svrHtTimeOfPs;

    EP_GLOBAL extern int pdstS62znVentPar;
    EP_GLOBAL extern int pdchS62zvpAlN;
    EP_GLOBAL extern int pdchS62zvpRp;
    EP_GLOBAL extern int pdchS62zvpPz;
    EP_GLOBAL extern int pdchS62zvpRa;
    EP_GLOBAL extern int pdchS62zvpAz;
    EP_GLOBAL extern int pdchS62zvpVbz;
    EP_GLOBAL extern int pdchS62zvpClEz;
    EP_GLOBAL extern int pdchS62zvpClVoz;
    EP_GLOBAL extern int pdchS62zvpHtEz;
    EP_GLOBAL extern int pdchS62zvpHtVoz;

    EP_GLOBAL extern int pdstS62sysVentPar;
    EP_GLOBAL extern int pdchS62svpRp;
    EP_GLOBAL extern int pdchS62svpPz;
    EP_GLOBAL extern int pdchS62svpRa;
    EP_GLOBAL extern int pdchS62svpAz;
    EP_GLOBAL extern int pdchS62svpVbz;
    EP_GLOBAL extern int pdchS62svpClVoz;
    EP_GLOBAL extern int pdchS62svpHtVoz;

    EP_GLOBAL extern int pdstS62znCoolDes;
    EP_GLOBAL extern int pdchS62zcdAlN;
    EP_GLOBAL extern int pdchS62zcdBox;
    EP_GLOBAL extern int pdchS62zcdVpz;
    EP_GLOBAL extern int pdchS62zcdVps;
    EP_GLOBAL extern int pdchS62zcdVsec;
    EP_GLOBAL extern int pdchS62zcdVdz;
    EP_GLOBAL extern int pdchS62zcdVpzmin;
    EP_GLOBAL extern int pdchS62zcdVozclg;
    EP_GLOBAL extern int pdchS62zcdZpz;
    EP_GLOBAL extern int pdchS62zcdEp;
    EP_GLOBAL extern int pdchS62zcdEr;
    EP_GLOBAL extern int pdchS62zcdFa;
    EP_GLOBAL extern int pdchS62zcdFb;
    EP_GLOBAL extern int pdchS62zcdFc;
    EP_GLOBAL extern int pdchS62zcdEvz;

    EP_GLOBAL extern int pdstS62sysCoolDes;
    EP_GLOBAL extern int pdchS62scdVpz;
    EP_GLOBAL extern int pdchS62scdVps;
    EP_GLOBAL extern int pdchS62scdVsec;
    EP_GLOBAL extern int pdchS62scdVdz;
    EP_GLOBAL extern int pdchS62scdVpzmin;
    EP_GLOBAL extern int pdchS62scdVozclg;
    EP_GLOBAL extern int pdchS62scdEvz;

    EP_GLOBAL extern int pdstS62znHeatDes;
    EP_GLOBAL extern int pdchS62zhdAlN;
    EP_GLOBAL extern int pdchS62zhdBox;
    EP_GLOBAL extern int pdchS62zhdVpz;
    EP_GLOBAL extern int pdchS62zhdVps;
    EP_GLOBAL extern int pdchS62zhdVsec;
    EP_GLOBAL extern int pdchS62zhdVdz;
    EP_GLOBAL extern int pdchS62zhdVpzmin;
    EP_GLOBAL extern int pdchS62zhdVozhtg;
    EP_GLOBAL extern int pdchS62zhdZpz;
    EP_GLOBAL extern int pdchS62zhdEp;
    EP_GLOBAL extern int pdchS62zhdEr;
    EP_GLOBAL extern int pdchS62zhdFa;
    EP_GLOBAL extern int pdchS62zhdFb;
    EP_GLOBAL extern int pdchS62zhdFc;
    EP_GLOBAL extern int pdchS62zhdEvz;

    EP_GLOBAL extern int pdstS62sysHeatDes;
    EP_GLOBAL extern int pdchS62shdVpz;
    EP_GLOBAL extern int pdchS62shdVps;
    EP_GLOBAL extern int pdchS62shdVsec;
    EP_GLOBAL extern int pdchS62shdVdz;
    EP_GLOBAL extern int pdchS62shdVpzmin;
    EP_GLOBAL extern int pdchS62shdVozhtg;
    EP_GLOBAL extern int pdchS62shdEvz;

    //  LEED Summary
    EP_GLOBAL extern int pdrLeed;
    EP_GLOBAL extern int pdstLeedGenInfo;
    EP_GLOBAL extern int pdchLeedGenData;

    EP_GLOBAL extern int pdstLeedSpaceUsageType;
    EP_GLOBAL extern int pdchLeedSutName;
    EP_GLOBAL extern int pdchLeedSutSpArea;
    EP_GLOBAL extern int pdchLeedSutOcArea;
    EP_GLOBAL extern int pdchLeedSutUnArea;
    EP_GLOBAL extern int pdchLeedSutHrsWeek;

    EP_GLOBAL extern int pdstLeedAdvsMsg;
    EP_GLOBAL extern int pdchLeedAmData;

    EP_GLOBAL extern int pdstLeedEneTypSum;
    EP_GLOBAL extern int pdchLeedEtsType;
    EP_GLOBAL extern int pdchLeedEtsRtNm;
    EP_GLOBAL extern int pdchLeedEtsVirt;
    EP_GLOBAL extern int pdchLeedEtsEneUnt;
    EP_GLOBAL extern int pdchLeedEtsDemUnt;

    EP_GLOBAL extern int pdstLeedPerf;
    EP_GLOBAL extern int pdchLeedPerfRot;
    EP_GLOBAL extern int pdchLeedPerfElEneUse;
    EP_GLOBAL extern int pdchLeedPerfElDem;
    EP_GLOBAL extern int pdchLeedPerfGasEneUse;
    EP_GLOBAL extern int pdchLeedPerfGasDem;
    EP_GLOBAL extern int pdchLeedPerfAddFuelEneUse;
    EP_GLOBAL extern int pdchLeedPerfAddFuelDem;
    EP_GLOBAL extern int pdchLeedPerfDisClEneUse;
    EP_GLOBAL extern int pdchLeedPerfDisClDem;
    EP_GLOBAL extern int pdchLeedPerfDisHtEneUse;
    EP_GLOBAL extern int pdchLeedPerfDisHtDem;

    EP_GLOBAL extern int pdstLeedEneUseSum;
    EP_GLOBAL extern int pdchLeedEusUnt;
    EP_GLOBAL extern int pdchLeedEusProc;
    EP_GLOBAL extern int pdchLeedEusTotal;

    EP_GLOBAL extern int pdstLeedEneCostSum;
    EP_GLOBAL extern int pdchLeedEcUnt;
    EP_GLOBAL extern int pdchLeedEcsProc;
    EP_GLOBAL extern int pdchLeedEcsTotal;
    EP_GLOBAL extern Real64 LEEDelecCostTotal;
    EP_GLOBAL extern Real64 LEEDgasCostTotal;
    EP_GLOBAL extern Real64 LEEDothrCostTotal;

    EP_GLOBAL extern int pdstLeedRenewSum;
    EP_GLOBAL extern int pdchLeedRenRatCap;
    EP_GLOBAL extern int pdchLeedRenAnGen;

    EP_GLOBAL extern int pdstLeedEneUseIntEl;
    EP_GLOBAL extern int pdchLeedEuiElec;
    EP_GLOBAL extern int pdstLeedEneUseIntNatG;
    EP_GLOBAL extern int pdchLeedEuiNatG;
    EP_GLOBAL extern int pdstLeedEneUseIntOthr;
    EP_GLOBAL extern int pdchLeedEuiOthr;

    EP_GLOBAL extern int pdstLeedEneUsePerc;
    EP_GLOBAL extern int pdchLeedEupPerc;

    EP_GLOBAL extern int pdstLeedEqFlLdHrs;
    EP_GLOBAL extern int pdchLeedEflhEflh;
    EP_GLOBAL extern int pdchLeedEflhNonZerHrs;

    EP_GLOBAL extern int pdstLeedSchedSetPts;
    EP_GLOBAL extern int pdChLeedSchStPtFirstObjUsed;
    EP_GLOBAL extern int pdChLeedSchStPtMonthUsed;
    EP_GLOBAL extern int pdchLeedSchStPt11amWednesday;
    EP_GLOBAL extern int pdchLeedSchStPt11amWedCnt;
    EP_GLOBAL extern int pdchLeedSchStPt11pmWednesday;
    EP_GLOBAL extern int pdchLeedSchStPt11pmWedCnt;

    // Internal data structures to store information provided by calls

    EP_GLOBAL extern int const sizeIncrement;

    EP_GLOBAL extern int sizeReportName;
    EP_GLOBAL extern int numReportName;

    EP_GLOBAL extern int sizeSubTable;
    EP_GLOBAL extern int numSubTable;

    EP_GLOBAL extern int sizeColumnTag;
    EP_GLOBAL extern int numColumnTag;

    EP_GLOBAL extern int sizeTableEntry;
    EP_GLOBAL extern int numTableEntry;

    EP_GLOBAL extern int sizeCompSizeTableEntry;
    EP_GLOBAL extern int numCompSizeTableEntry;

    EP_GLOBAL extern int sizeShadowRelate;
    EP_GLOBAL extern int numShadowRelate;
    EP_GLOBAL extern int const recKindSurface;
    EP_GLOBAL extern int const recKindSubsurface;

    EP_GLOBAL extern Real64 TotalNotMetHeatingOccupiedForABUPS;
    EP_GLOBAL extern Real64 TotalNotMetCoolingOccupiedForABUPS;
    EP_GLOBAL extern Real64 TotalNotMetOccupiedForABUPS;
    EP_GLOBAL extern Real64 TotalTimeNotSimpleASH55EitherForABUPS;

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
    EP_GLOBAL extern Array1D<reportNameType> reportName;
    EP_GLOBAL extern Array1D<SubTableType> subTable;
    EP_GLOBAL extern Array1D<ColumnTagType> columnTag;
    EP_GLOBAL extern Array1D<TableEntryType> tableEntry;
    EP_GLOBAL extern Array1D<CompSizeTableEntryType> CompSizeTableEntry;
    EP_GLOBAL extern Array1D<ShadowRelateType> ShadowRelate;

    // Functions
    void clear_state();

    void SetPredefinedTables();


    // Creates an entry for predefined tables when the entry
    // is a real variable. numSigDigits defaults to 2, and if supplied must be in [0-9]
    // Internally it uses a Fortran-Style write statement, meaning numbers are rounded rather than trimmed
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
