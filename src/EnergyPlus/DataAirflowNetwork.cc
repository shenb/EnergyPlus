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
#include <DataAirflowNetwork.hh>
#include <DataPrecisionGlobals.hh>

namespace EnergyPlus {

namespace DataAirflowNetwork {

    // MODULE INFORMATION:
    //       AUTHOR         Lixing Gu, Don Shirey, and Muthusamy V. Swami
    //       DATE WRITTEN   Aug. 2003
    //       MODIFIED       na
    //       RE-ENGINEERED  na

    // PURPOSE OF THIS MODULE:
    // This module should contain the information that is needed to simulate
    // performance of air distribution system, including pressure, temperature
    // and moisture levels at each node, and airflow and sensible and latent energy losses
    // at each element

    // Using/Aliasing
    using namespace DataPrecisionGlobals;

    // Data
    // module should be available to other modules and routines.  Thus,
    // all variables in this module must be PUBLIC.

    // MODULE PARAMETER DEFINITIONS:
    thread_local int const CompTypeNum_DOP(1);  // Detailed large opening component
    thread_local int const CompTypeNum_SOP(2);  // Simple opening component
    thread_local int const CompTypeNum_SCR(3);  // Surface crack component
    thread_local int const CompTypeNum_SEL(4);  // Surface effective leakage ratio component
    thread_local int const CompTypeNum_PLR(5);  // Distribution system crack component
    thread_local int const CompTypeNum_DWC(6);  // Distribution system duct component
    thread_local int const CompTypeNum_CVF(7);  // Distribution system constant volume fan component
    thread_local int const CompTypeNum_FAN(8);  // Distribution system detailed fan component
    thread_local int const CompTypeNum_MRR(9);  // Distribution system multiple curve fit power law resistant flow component
    thread_local int const CompTypeNum_DMP(10); // Distribution system damper component
    thread_local int const CompTypeNum_ELR(11); // Distribution system effective leakage ratio component
    thread_local int const CompTypeNum_CPD(12); // Distribution system constant pressure drop component
    thread_local int const CompTypeNum_COI(13); // Distribution system coil component
    thread_local int const CompTypeNum_TMU(14); // Distribution system terminal unit component
    thread_local int const CompTypeNum_EXF(15); // Zone exhaust fan
    thread_local int const CompTypeNum_HEX(16); // Distribution system heat exchanger
    thread_local int const CompTypeNum_HOP(17); // Horizontal opening component
    thread_local int const CompTypeNum_RVD(18); // Reheat VAV terminal damper
    thread_local int const CompTypeNum_OAF(19); // Distribution system OA
    thread_local int const CompTypeNum_REL(20); // Distribution system relief air

    // EPlus component Type
    thread_local int const EPlusTypeNum_SCN(1); // Supply connection
    thread_local int const EPlusTypeNum_RCN(2); // Return connection
    thread_local int const EPlusTypeNum_RHT(3); // Reheat terminal
    thread_local int const EPlusTypeNum_FAN(4); // Fan
    thread_local int const EPlusTypeNum_COI(5); // Heating or cooling coil
    thread_local int const EPlusTypeNum_HEX(6); // Heat exchanger
    thread_local int const EPlusTypeNum_RVD(7); // Reheat VAV terminal damper

    // EPlus node type
    thread_local int const EPlusTypeNum_ZIN(1);  // Zone inlet node
    thread_local int const EPlusTypeNum_ZOU(2);  // Zone outlet node
    thread_local int const EPlusTypeNum_SPL(3);  // Splitter node
    thread_local int const EPlusTypeNum_MIX(4);  // Mixer node
    thread_local int const EPlusTypeNum_OAN(5);  // Outside air system node
    thread_local int const EPlusTypeNum_EXT(6);  // OA system inlet node
    thread_local int const EPlusTypeNum_FIN(7);  // Fan Inlet node
    thread_local int const EPlusTypeNum_FOU(8);  // Fan Outlet Node
    thread_local int const EPlusTypeNum_COU(9);  // Coil Outlet Node
    thread_local int const EPlusTypeNum_HXO(10); // Heat exchanger Outlet Node
    thread_local int const EPlusTypeNum_DIN(11); // Damper Inlet node
    thread_local int const EPlusTypeNum_DOU(12); // Damper Outlet Node
    thread_local int const EPlusTypeNum_SPI(13); // Splitter inlet Node
    thread_local int const EPlusTypeNum_SPO(14); // Splitter Outlet Node

    thread_local int const iWPCCntr_Input(1);
    thread_local int const iWPCCntr_SurfAvg(2);

    thread_local int const PressureCtrlExhaust(1);
    thread_local int const PressureCtrlRelief(2);

    // DERIVED TYPE DEFINITIONS:

    // MODULE VARIABLE DECLARATIONS:
    // Node simulation variable in air distribution system
    // Link simulation variable in air distribution system
    // Sensible and latent exchange variable in air distribution system

    thread_local int SimulateAirflowNetwork(1);
    // Vent Control  DistSys Control  Flag    Description
    //  NONE           NONE           0      No AirflowNetwork and SIMPLE
    //  SIMPLE         NONE           1      Simple calculations only
    //  MULTIZONE      NONE           2      Perform multizone calculations only
    //  NONE           DISTSYS        3      Perform distribution system during system on time only
    //  SIMPLE         DISTSYS        4      Perform distribution system during system on time and simple calculations during off time
    //  MULTIZONE      DISTSYS        5      Perform distribution system during system on time and multizone calculations during off time

    thread_local int const AirflowNetworkControlSimple(1);    // Simple calculations only
    thread_local int const AirflowNetworkControlMultizone(2); // Perform multizone calculations only
    thread_local int const AirflowNetworkControlSimpleADS(4); // Perform distribution system during system
    // on time and simple calculations during off time
    thread_local int const AirflowNetworkControlMultiADS(5); // Perform distribution system during system on time
    // and multizone calculations during off time

    thread_local Array1D_bool AirflowNetworkZoneFlag;

    thread_local int NumOfNodesMultiZone(0);    // Number of nodes for multizone calculation
    thread_local int NumOfNodesDistribution(0); // Number of nodes for distribution system calculation
    thread_local int NumOfLinksMultiZone(0);    // Number of links for multizone calculation
    thread_local int NumOfLinksDistribution(0); // Number of links for distribution system calculation
    thread_local int NumOfNodesIntraZone(0);    // Number of nodes for intrazone calculation
    thread_local int NumOfLinksIntraZone(0);    // Number of links for intrazone calculation

    thread_local int AirflowNetworkNumOfNodes(0); // Number of nodes for AirflowNetwork calculation
    // = NumOfNodesMultiZone+NumOfNodesDistribution
    thread_local int AirflowNetworkNumOfComps(0); // Number of components for AirflowNetwork calculation
    thread_local int AirflowNetworkNumOfLinks(0); // Number of links for AirflowNetwork calculation
    // = NumOfLinksMultiZone+NumOfLinksDistribution
    // RoomAirManager use
    thread_local int AirflowNetworkNumOfSurfaces(0); // The number of surfaces for multizone calculation
    thread_local int AirflowNetworkNumOfZones(0);    // The number of zones for multizone calculation

    thread_local bool RollBackFlag(false);                  // Roll back flag when system time step down shifting
    thread_local Array1D<Real64> ANZT;                      // Local zone air temperature for roll back use
    thread_local Array1D<Real64> ANZW;                      // Local zone air humidity ratio for roll back use
    thread_local Array1D<Real64> ANCO;                      // Local zone air CO2 for roll back use
    thread_local Array1D<Real64> ANGC;                      // Local zone air generic contaminant for roll back use
    thread_local int AirflowNetworkNumOfExhFan(0);          // Number of zone exhaust fans
    thread_local Array1D_bool AirflowNetworkZoneExhaustFan; // Logical to use zone exhaust fans
    thread_local bool AirflowNetworkFanActivated(false);    // Supply fan activation flag
    thread_local bool AirflowNetworkUnitarySystem(false);   // set to TRUE for unitary systems (to make answers equal, will remove eventually)
    // Multispeed HP only
    thread_local int MultiSpeedHPIndicator(0); // Indicator for multispeed heat pump use
    // Additional airflow needed for an VAV fan to compensate the leakage losses and supply pathway pressure losses [kg/s]
    thread_local Real64 VAVTerminalRatio(0.0);       // The terminal flow ratio when a supply VAV fan reach its max flow rate
    thread_local bool VAVSystem(false);              // This flag is used to represent a VAV system
    thread_local Real64 ExhaustFanMassFlowRate(0.0); // Exhaust fan flow rate used in PressureStat
    thread_local int PressureSetFlag(0);             // PressureSet flag
    thread_local Real64 ReliefMassFlowRate(0.0);     // OA Mixer relief node flow rate used in PressureStat

    // Object Data
    thread_local Array1D<AirflowNetworkNodeSimuData> AirflowNetworkNodeSimu;
    thread_local Array1D<AirflowNetworkLinkSimuData> AirflowNetworkLinkSimu;
    thread_local Array1D<AirflowNetworkExchangeProp> AirflowNetworkExchangeData;
    thread_local Array1D<AirflowNetworkExchangeProp> AirflowNetworkMultiExchangeData;
    thread_local Array1D<AirflowNetworkLinkReportData> AirflowNetworkLinkReport;
    thread_local Array1D<AirflowNetworkNodeReportData> AirflowNetworkNodeReport;
    thread_local Array1D<AirflowNetworkLinkReportData> AirflowNetworkLinkReport1;
    thread_local AirflowNetworkSimuProp AirflowNetworkSimu;
    thread_local Array1D<AirflowNetworkNodeProp> AirflowNetworkNodeData;
    thread_local Array1D<AirflowNetworkCompProp> AirflowNetworkCompData;
    thread_local Array1D<AirflowNetworkLinkageProp> AirflowNetworkLinkageData;
    thread_local Array1D<MultizoneZoneProp> MultizoneZoneData;
    thread_local Array1D<MultizoneSurfaceProp> MultizoneSurfaceData;
    thread_local Array1D<MultizoneCompDetOpeningProp> MultizoneCompDetOpeningData;
    thread_local Array1D<MultizoneCompSimpleOpeningProp> MultizoneCompSimpleOpeningData;
    thread_local Array1D<MultizoneCompHorOpeningProp> MultizoneCompHorOpeningData;
    thread_local Array1D<MultizoneSurfaceCrackStdCndns> MultizoneSurfaceStdConditionsCrackData;
    thread_local Array1D<MultizoneSurfaceCrackProp> MultizoneSurfaceCrackData;
    thread_local Array1D<MultizoneSurfaceELAProp> MultizoneSurfaceELAData;
    thread_local Array1D<MultizoneExternalNodeProp> MultizoneExternalNodeData;
    thread_local Array1D<DeltaCpProp> DeltaCp;
    thread_local Array1D<DeltaCpProp> EPDeltaCP;
    thread_local Array1D<MultizoneCompExhaustFanProp> MultizoneCompExhaustFanData;
    thread_local Array1D<IntraZoneNodeProp> IntraZoneNodeData;
    thread_local Array1D<IntraZoneLinkageProp> IntraZoneLinkageData;
    thread_local Array1D<DisSysNodeProp> DisSysNodeData;
    thread_local Array1D<DisSysCompLeakProp> DisSysCompLeakData;
    thread_local Array1D<DisSysCompELRProp> DisSysCompELRData;
    thread_local Array1D<DisSysCompDuctProp> DisSysCompDuctData;
    thread_local Array1D<DisSysCompDamperProp> DisSysCompDamperData;
    thread_local Array1D<DisSysCompCVFProp> DisSysCompCVFData;
    thread_local Array1D<DisSysCompDetFanProp> DisSysCompDetFanData;
    thread_local Array1D<DisSysCompCoilProp> DisSysCompCoilData;
    thread_local Array1D<DisSysCompHXProp> DisSysCompHXData;
    thread_local Array1D<DisSysCompTermUnitProp> DisSysCompTermUnitData;
    thread_local Array1D<DisSysCompCPDProp> DisSysCompCPDData;
    thread_local Array1D<AiflowNetworkReportProp> AirflowNetworkReportData;
    thread_local Array1D<PressureControllerProp> PressureControllerData;
    thread_local Array1D<DisSysCompAirflowProp> DisSysCompOutdoorAirData;
    thread_local Array1D<DisSysCompAirflowProp> DisSysCompReliefAirData;
    thread_local Array1D<AirflowNetworkLinkageViewFactorProp> AirflowNetworkLinkageViewFactorData;

    void clear_state()
    {
        SimulateAirflowNetwork = 1;
        AirflowNetworkZoneFlag.deallocate();
        NumOfNodesMultiZone = 0;
        NumOfNodesDistribution = 0;
        NumOfLinksMultiZone = 0;
        NumOfLinksDistribution = 0;
        NumOfNodesIntraZone = 0;
        NumOfLinksIntraZone = 0;
        AirflowNetworkNumOfNodes = 0;
        AirflowNetworkNumOfComps = 0;
        AirflowNetworkNumOfLinks = 0;
        AirflowNetworkNumOfSurfaces = 0;
        AirflowNetworkNumOfZones = 0;
        RollBackFlag = false;
        ANZT.deallocate();
        ANZW.deallocate();
        ANCO.deallocate();
        ANGC.deallocate();
        AirflowNetworkNumOfExhFan = 0;
        AirflowNetworkZoneExhaustFan.deallocate();
        AirflowNetworkFanActivated = false;
        AirflowNetworkUnitarySystem = false;
        MultiSpeedHPIndicator = 0;
        VAVTerminalRatio = 0.0;
        VAVSystem = false;
        AirflowNetworkNodeSimu.deallocate();
        AirflowNetworkLinkSimu.deallocate();
        AirflowNetworkExchangeData.deallocate();
        AirflowNetworkMultiExchangeData.deallocate();
        AirflowNetworkLinkReport.deallocate();
        AirflowNetworkNodeReport.deallocate();
        AirflowNetworkLinkReport1.deallocate();
        AirflowNetworkSimu = AirflowNetworkSimuProp();
        AirflowNetworkNodeData.deallocate();
        AirflowNetworkCompData.deallocate();
        AirflowNetworkLinkageData.deallocate();
        MultizoneZoneData.deallocate();
        MultizoneSurfaceData.deallocate();
        MultizoneCompDetOpeningData.deallocate();
        MultizoneCompSimpleOpeningData.deallocate();
        MultizoneCompHorOpeningData.deallocate();
        MultizoneSurfaceStdConditionsCrackData.deallocate();
        MultizoneSurfaceCrackData.deallocate();
        MultizoneSurfaceELAData.deallocate();
        MultizoneExternalNodeData.deallocate();
        DeltaCp.deallocate();
        EPDeltaCP.deallocate();
        MultizoneCompExhaustFanData.deallocate();
        IntraZoneNodeData.deallocate();
        IntraZoneLinkageData.deallocate();
        DisSysNodeData.deallocate();
        DisSysCompLeakData.deallocate();
        DisSysCompELRData.deallocate();
        DisSysCompDuctData.deallocate();
        DisSysCompDamperData.deallocate();
        DisSysCompCVFData.deallocate();
        DisSysCompDetFanData.deallocate();
        DisSysCompCoilData.deallocate();
        DisSysCompHXData.deallocate();
        DisSysCompTermUnitData.deallocate();
        DisSysCompCPDData.deallocate();
        AirflowNetworkReportData.deallocate();
        AirflowNetworkLinkageViewFactorData.deallocate();
    }

} // namespace DataAirflowNetwork

} // namespace EnergyPlus
