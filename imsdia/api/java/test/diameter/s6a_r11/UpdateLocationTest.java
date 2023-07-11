package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class UpdateLocationTest {

    public static void testUpdateLocationRequest() throws Exception {
        UpdateLocationRequest updateLocationRequest = new UpdateLocationRequest(false, false);
        updateLocationRequest.setSessionId(new diameter.base.SessionId("utf8string1957918559"));
        updateLocationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        updateLocationRequest.setOriginHost(new diameter.base.OriginHost("id597461216.diameter.com"));
        updateLocationRequest.setOriginRealm(new diameter.base.OriginRealm("id-546765457.diameter.com"));
        updateLocationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1617594184.diameter.com"));
        updateLocationRequest.setUserName(new diameter.base.UserName("utf8string-1390942651"));
        updateLocationRequest.setULRFlags(new ULRFlags(new Integer(-1013311570)));
        updateLocationRequest.setVisitedPLMNId(new VisitedPLMNId("octetstring1513031475"));
        updateLocationRequest.setRATType(new RATType(RATType.Value.UMB));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-979335700)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(677339219)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(376683090)));
            updateLocationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        updateLocationRequest.setSGSNNumber(new SGSNNumber("octetstring1941584975"));
        updateLocationRequest.setDestinationHost(new diameter.base.DestinationHost("id-1256311071.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1909418014)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(485822219)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(667625610)));
            // add more AVP as ANY values to supportedFeatures
            updateLocationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string-1037147885"));
            terminalInformation.setS6a3GPP2MEID(new S6a3GPP2MEID("octetstring1298566089"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string1016164401"));
            // add more AVP as ANY values to terminalInformation
            updateLocationRequest.setTerminalInformation(terminalInformation);
        }
        updateLocationRequest.setUESRVCCCapability(new UESRVCCCapability(UESRVCCCapability.Value.UE_SRVCC_NOT_SUPPORTED));
        updateLocationRequest.setHomogeneousSupportofIMSVoiceOverPSSessions(new HomogeneousSupportofIMSVoiceOverPSSessions(HomogeneousSupportofIMSVoiceOverPSSessions.Value.NOT_SUPPORTED));
        updateLocationRequest.setGMLCAddress(new GMLCAddress(new Address(Address.Family.IPV4, "1.98.232.230")));
        {
            EquivalentPLMNList equivalentPLMNList = new EquivalentPLMNList();
            equivalentPLMNList.addVisitedPLMNId(new VisitedPLMNId("octetstring1767719461"));
            // add more AVP as ANY values to equivalentPLMNList
            updateLocationRequest.setEquivalentPLMNList(equivalentPLMNList);
        }
        updateLocationRequest.setMMENumberforMTSMS(new MMENumberforMTSMS("octetstring-1155918721"));
        updateLocationRequest.setSMSReqisterRequest(new SMSReqisterRequest(SMSReqisterRequest.Value.NO_PREFERENCE));
        {
            ActiveAPN activeAPN = new ActiveAPN();
            activeAPN.setContextIdentifier(new ContextIdentifier(new Integer(1712851872)));
            activeAPN.setServiceSelection(new ServiceSelection("utf8string178697038"));
            {
                MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "87.162.50.143")));
                {
                    MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                    mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-2078682459.diameter.com"));
                    mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-45860523.diameter.com"));
                    // add more AVP as ANY values to mIPHomeAgentHost
                    mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                }
                mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring1477076736"));
                // add more AVP as ANY values to mIP6AgentInfo
                activeAPN.setMIP6AgentInfo(mIP6AgentInfo);
            }
            activeAPN.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring-2030295171"));
            {
                SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string-392706244"));
                {
                    MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                    mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "166.28.241.128")));
                    {
                        MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                        mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-993449178.diameter.com"));
                        mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id1612452568.diameter.com"));
                        // add more AVP as ANY values to mIPHomeAgentHost
                        mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                    }
                    mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring667735052"));
                    // add more AVP as ANY values to mIP6AgentInfo
                    specificAPNInfo.setMIP6AgentInfo(mIP6AgentInfo);
                }
                specificAPNInfo.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring1640892696"));
                // add more AVP as ANY values to specificAPNInfo
                activeAPN.addSpecificAPNInfo(specificAPNInfo);
            }
            // add more AVP as ANY values to activeAPN
            updateLocationRequest.addActiveAPN(activeAPN);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id245474695.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1409739420"));
            // add more AVP as ANY values to proxyInfo
            updateLocationRequest.addProxyInfo(proxyInfo);
        }
        updateLocationRequest.addRouteRecord(new diameter.base.RouteRecord("id1104117114.diameter.com"));
        // add more AVP as ANY values to updateLocationRequest

        byte[] buffer = updateLocationRequest.encode();
        UpdateLocationRequest updateLocationRequest2 = new UpdateLocationRequest(buffer);
        String s1 = updateLocationRequest.toString();
        String s2 = updateLocationRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("updateLocationRequest1 = " + s1);
            System.err.println("updateLocationRequest2 = " + s2);
            throw new VerificationException("UpdateLocationRequest encoding/decoding failure");
        }
    }

    public static void testUpdateLocationAnswer() throws Exception {
        UpdateLocationAnswer updateLocationAnswer = new UpdateLocationAnswer(false, false);
        updateLocationAnswer.setSessionId(new diameter.base.SessionId("utf8string-1234628895"));
        updateLocationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        updateLocationAnswer.setOriginHost(new diameter.base.OriginHost("id1213649145.diameter.com"));
        updateLocationAnswer.setOriginRealm(new diameter.base.OriginRealm("id1298273531.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(396854053)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1331163910)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1347482883)));
            updateLocationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        updateLocationAnswer.setULAFlags(new ULAFlags(new Integer(-2078191329)));
        updateLocationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1671612428)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-260376479)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(1628041160)));
            updateLocationAnswer.setExperimentalResult(experimentalResult);
        }
        updateLocationAnswer.setErrorDiagnostic(new ErrorDiagnostic(ErrorDiagnostic.Value.GPRS_DATA_SUBSCRIBED));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-296266414)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-855510181)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(211120223)));
            // add more AVP as ANY values to supportedFeatures
            updateLocationAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            SubscriptionData subscriptionData = new SubscriptionData();
            subscriptionData.setSubscriberStatus(new SubscriberStatus(SubscriberStatus.Value.SERVICEGRANTED));
            subscriptionData.setMSISDN(new MSISDN("octetstring216446521"));
            subscriptionData.setAMSISDN(new AMSISDN("octetstring-571187040"));
            subscriptionData.setSTNSR(new STNSR("octetstring-1188050752"));
            subscriptionData.setICSIndicator(new ICSIndicator(ICSIndicator.Value.FALSE));
            subscriptionData.setNetworkAccessMode(new NetworkAccessMode(NetworkAccessMode.Value.ONLY_PACKET));
            subscriptionData.setOperatorDeterminedBarring(new OperatorDeterminedBarring(new Integer(-250480090)));
            subscriptionData.setHPLMNODB(new HPLMNODB(new Integer(450211381)));
            subscriptionData.addRegionalSubscriptionZoneCode(new RegionalSubscriptionZoneCode("octetstring-327340711"));
            subscriptionData.setAccessRestrictionData(new AccessRestrictionData(new Integer(-1725769705)));
            subscriptionData.setAPNOIReplacement(new APNOIReplacement("utf8string1422516862"));
            {
                LCSInfo lCSInfo = new LCSInfo();
                lCSInfo.addGMLCNumber(new GMLCNumber("octetstring898928365"));
                {
                    LCSPrivacyException lCSPrivacyException = new LCSPrivacyException();
                    lCSPrivacyException.setSSCode(new SSCode("octetstring-1237286315"));
                    lCSPrivacyException.setSSStatus(new SSStatus("octetstring-2072914870"));
                    lCSPrivacyException.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE));
                    {
                        ExternalClient externalClient = new ExternalClient();
                        externalClient.setClientIdentity(new ClientIdentity("octetstring-827803960"));
                        externalClient.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.HOME_COUNTRY));
                        externalClient.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE));
                        // add more AVP as ANY values to externalClient
                        lCSPrivacyException.addExternalClient(externalClient);
                    }
                    lCSPrivacyException.addPLMNClient(new PLMNClient(PLMNClient.Value.ANONYMOUS_LOCATION));
                    {
                        ServiceType serviceType = new ServiceType();
                        serviceType.setServiceTypeIdentity(new ServiceTypeIdentity(new Integer(-6787727)));
                        serviceType.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.HOME_COUNTRY));
                        serviceType.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE));
                        // add more AVP as ANY values to serviceType
                        lCSPrivacyException.addServiceType(serviceType);
                    }
                    // add more AVP as ANY values to lCSPrivacyException
                    lCSInfo.addLCSPrivacyException(lCSPrivacyException);
                }
                {
                    MOLR mOLR = new MOLR();
                    mOLR.setSSCode(new SSCode("octetstring807746473"));
                    mOLR.setSSStatus(new SSStatus("octetstring-2103811663"));
                    // add more AVP as ANY values to mOLR
                    lCSInfo.addMOLR(mOLR);
                }
                // add more AVP as ANY values to lCSInfo
                subscriptionData.setLCSInfo(lCSInfo);
            }
            {
                TeleserviceList teleserviceList = new TeleserviceList();
                teleserviceList.addTSCode(new TSCode("octetstring1390252167"));
                // add more AVP as ANY values to teleserviceList
                subscriptionData.setTeleserviceList(teleserviceList);
            }
            {
                CallBarringInforList callBarringInforList = new CallBarringInforList();
                callBarringInforList.addSSCode(new SSCode("octetstring263306454"));
                // add more AVP as ANY values to callBarringInforList
                subscriptionData.setCallBarringInforList(callBarringInforList);
            }
            subscriptionData.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string515585037"));
            {
                AMBR aMBR = new AMBR();
                aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1168569858)));
                aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(266751634)));
                // add more AVP as ANY values to aMBR
                subscriptionData.setAMBR(aMBR);
            }
            {
                APNConfigurationProfile aPNConfigurationProfile = new APNConfigurationProfile();
                aPNConfigurationProfile.setContextIdentifier(new ContextIdentifier(new Integer(-56868218)));
                aPNConfigurationProfile.setAllAPNConfigurationsIncludedIndicator(new AllAPNConfigurationsIncludedIndicator(AllAPNConfigurationsIncludedIndicator.Value.MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED));
                {
                    APNConfiguration aPNConfiguration = new APNConfiguration();
                    aPNConfiguration.setContextIdentifier(new ContextIdentifier(new Integer(-1887878557)));
                    aPNConfiguration.setPDNType(new PDNType(PDNType.Value.IPv6));
                    aPNConfiguration.setServiceSelection(new ServiceSelection("utf8string528537557"));
                    aPNConfiguration.addServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "178.106.189.234")));
                    {
                        EPSSubscribedQoSProfile ePSSubscribedQoSProfile = new EPSSubscribedQoSProfile();
                        ePSSubscribedQoSProfile.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_9));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1492831903)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            ePSSubscribedQoSProfile.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        // add more AVP as ANY values to ePSSubscribedQoSProfile
                        aPNConfiguration.setEPSSubscribedQoSProfile(ePSSubscribedQoSProfile);
                    }
                    aPNConfiguration.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.ALLOWED));
                    {
                        MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                        mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "6.193.202.118")));
                        {
                            MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                            mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-213003011.diameter.com"));
                            mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id163854618.diameter.com"));
                            // add more AVP as ANY values to mIPHomeAgentHost
                            mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                        }
                        mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring1934668034"));
                        // add more AVP as ANY values to mIP6AgentInfo
                        aPNConfiguration.setMIP6AgentInfo(mIP6AgentInfo);
                    }
                    aPNConfiguration.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring698230343"));
                    aPNConfiguration.setPDNGWAllocationType(new PDNGWAllocationType(PDNGWAllocationType.Value.DYNAMIC));
                    aPNConfiguration.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string1025830078"));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-249378559)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-445577990)));
                        // add more AVP as ANY values to aMBR
                        aPNConfiguration.setAMBR(aMBR);
                    }
                    {
                        SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                        specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string320160618"));
                        {
                            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "165.132.4.54")));
                            {
                                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id2027335643.diameter.com"));
                                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-795212004.diameter.com"));
                                // add more AVP as ANY values to mIPHomeAgentHost
                                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                            }
                            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring799273293"));
                            // add more AVP as ANY values to mIP6AgentInfo
                            specificAPNInfo.setMIP6AgentInfo(mIP6AgentInfo);
                        }
                        specificAPNInfo.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring-293257820"));
                        // add more AVP as ANY values to specificAPNInfo
                        aPNConfiguration.addSpecificAPNInfo(specificAPNInfo);
                    }
                    aPNConfiguration.setAPNOIReplacement(new APNOIReplacement("utf8string-32437814"));
                    aPNConfiguration.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_ALLOWED));
                    aPNConfiguration.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_CONDITIONAL));
                    // add more AVP as ANY values to aPNConfiguration
                    aPNConfigurationProfile.addAPNConfiguration(aPNConfiguration);
                }
                // add more AVP as ANY values to aPNConfigurationProfile
                subscriptionData.setAPNConfigurationProfile(aPNConfigurationProfile);
            }
            subscriptionData.setRATFrequencySelectionPriorityID(new RATFrequencySelectionPriorityID(new Integer(-1406496024)));
            {
                TraceData traceData = new TraceData();
                traceData.setTraceReference(new TraceReference("octetstring1570550719"));
                traceData.setTraceDepth(new TraceDepth(TraceDepth.Value.MinimumWithoutVendorSpecificExtension));
                traceData.setTraceNETypeList(new TraceNETypeList("octetstring-1642356981"));
                traceData.setTraceEventList(new TraceEventList("octetstring329024448"));
                traceData.setTraceCollectionEntity(new TraceCollectionEntity(new Address(Address.Family.IPV4, "166.30.207.13")));
                traceData.setTraceInterfaceList(new TraceInterfaceList("octetstring-170912488"));
                traceData.setOMCId(new OMCId("octetstring956362432"));
                {
                    MDTConfiguration mDTConfiguration = new MDTConfiguration();
                    mDTConfiguration.setJobType(new JobType(JobType.Value.LOGGED_MDT_ONLY));
                    {
                        AreaScope areaScope = new AreaScope();
                        areaScope.addCellGlobalIdentity(new CellGlobalIdentity("octetstring-55301979"));
                        areaScope.addEUTRANCellGlobalIdentity(new EUTRANCellGlobalIdentity("octetstring566838679"));
                        areaScope.addRoutingAreaIdentity(new RoutingAreaIdentity("octetstring210725826"));
                        areaScope.addLocationAreaIdentity(new LocationAreaIdentity("octetstring94362242"));
                        areaScope.addTrackingAreaIdentity(new TrackingAreaIdentity("octetstring-908367001"));
                        // add more AVP as ANY values to areaScope
                        mDTConfiguration.setAreaScope(areaScope);
                    }
                    mDTConfiguration.setListOfMeasurements(new ListOfMeasurements(new Integer(-1683837672)));
                    mDTConfiguration.setReportingTrigger(new ReportingTrigger(new Integer(241431915)));
                    mDTConfiguration.setReportInterval(new ReportInterval(ReportInterval.Value.MSEC_240));
                    mDTConfiguration.setReportAmount(new ReportAmount(ReportAmount.Value.NUM_REPORTS_4));
                    mDTConfiguration.setEventThresholdRSRP(new EventThresholdRSRP(new Integer(466806209)));
                    mDTConfiguration.setEventThresholdRSRQ(new EventThresholdRSRQ(new Integer(-1004627776)));
                    mDTConfiguration.setLoggingInterval(new LoggingInterval(LoggingInterval.Value.LOG_PERIODICITY_5_12));
                    mDTConfiguration.setLoggingDuration(new LoggingDuration(LoggingDuration.Value.SEC_1200));
                    // add more AVP as ANY values to mDTConfiguration
                    traceData.setMDTConfiguration(mDTConfiguration);
                }
                // add more AVP as ANY values to traceData
                subscriptionData.setTraceData(traceData);
            }
            {
                GPRSSubscriptionData gPRSSubscriptionData = new GPRSSubscriptionData();
                gPRSSubscriptionData.setCompleteDataListIncludedIndicator(new CompleteDataListIncludedIndicator(CompleteDataListIncludedIndicator.Value.MODIFIED_ADDED_PDP_CONTEXTS_INCLUDED));
                {
                    PDPContext pDPContext = new PDPContext();
                    pDPContext.setContextIdentifier(new ContextIdentifier(new Integer(725452860)));
                    pDPContext.setPDPType(new PDPType("octetstring1463186070"));
                    pDPContext.setQoSSubscribed(new QoSSubscribed("octetstring-1697190004"));
                    pDPContext.setServiceSelection(new ServiceSelection("utf8string953138057"));
                    pDPContext.setPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "192.72.33.98")));
                    pDPContext.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.NOTALLOWED));
                    pDPContext.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string-549004159"));
                    pDPContext.setExtPDPType(new ExtPDPType("octetstring1113956354"));
                    pDPContext.setExtPDPAddress(new ExtPDPAddress(new Address(Address.Family.IPV4, "28.223.217.233")));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(86063906)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(289441876)));
                        // add more AVP as ANY values to aMBR
                        pDPContext.setAMBR(aMBR);
                    }
                    pDPContext.setAPNOIReplacement(new APNOIReplacement("utf8string-587562613"));
                    pDPContext.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_NOTALLOWED));
                    pDPContext.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_PROHIBITED));
                    // add more AVP as ANY values to pDPContext
                    gPRSSubscriptionData.addPDPContext(pDPContext);
                }
                // add more AVP as ANY values to gPRSSubscriptionData
                subscriptionData.setGPRSSubscriptionData(gPRSSubscriptionData);
            }
            {
                CSGSubscriptionData cSGSubscriptionData = new CSGSubscriptionData();
                cSGSubscriptionData.setCSGId(new CSGId(new Integer(1869206318)));
                cSGSubscriptionData.setExpirationDate(new ExpirationDate(-203208105));
                cSGSubscriptionData.addServiceSelection(new ServiceSelection("utf8string-1574746955"));
                cSGSubscriptionData.setVisitedPLMNId(new VisitedPLMNId("octetstring262170998"));
                // add more AVP as ANY values to cSGSubscriptionData
                subscriptionData.addCSGSubscriptionData(cSGSubscriptionData);
            }
            subscriptionData.setRoamingRestrictedDueToUnsupportedFeature(new RoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature.Value.Roaming_Restricted_Due_To_Unsupported_Feature));
            subscriptionData.setSubscribedPeriodicRAUTAUTimer(new SubscribedPeriodicRAUTAUTimer(new Integer(-419483735)));
            subscriptionData.setMPSPriority(new MPSPriority(new Integer(-434266744)));
            subscriptionData.setVPLMNLIPAAllowed(new VPLMNLIPAAllowed(VPLMNLIPAAllowed.Value.LIPA_NOTALLOWED));
            subscriptionData.setRelayNodeIndicator(new RelayNodeIndicator(RelayNodeIndicator.Value.RELAY_NODE));
            subscriptionData.setMDTUserConsent(new MDTUserConsent(MDTUserConsent.Value.CONSENT_GIVEN));
            subscriptionData.setSubscribedVSRVCC(new SubscribedVSRVCC(SubscribedVSRVCC.Value.VSRVCC_SUBSCRIBED));
            subscriptionData.setSubscriptionDataFlags(new SubscriptionDataFlags(new Integer(1956412833)));
            // add more AVP as ANY values to subscriptionData
            updateLocationAnswer.setSubscriptionData(subscriptionData);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id2077581070.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-15011467"));
            // add more AVP as ANY values to proxyInfo
            updateLocationAnswer.addProxyInfo(proxyInfo);
        }
        updateLocationAnswer.addRouteRecord(new diameter.base.RouteRecord("id-593053309.diameter.com"));
        // add more AVP as ANY values to updateLocationAnswer

        byte[] buffer = updateLocationAnswer.encode();
        UpdateLocationAnswer updateLocationAnswer2 = new UpdateLocationAnswer(buffer);
        String s1 = updateLocationAnswer.toString();
        String s2 = updateLocationAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("updateLocationAnswer1 = " + s1);
            System.err.println("updateLocationAnswer2 = " + s2);
            throw new VerificationException("UpdateLocationAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testUpdateLocationRequest();
        testUpdateLocationAnswer();
    }
}
