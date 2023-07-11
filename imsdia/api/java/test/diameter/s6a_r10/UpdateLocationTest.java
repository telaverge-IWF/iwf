package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class UpdateLocationTest {

    public static void testUpdateLocationRequest() throws Exception {
        UpdateLocationRequest updateLocationRequest = new UpdateLocationRequest(false, false);
        updateLocationRequest.setSessionId(new diameter.base.SessionId("utf8string840319867"));
        updateLocationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        updateLocationRequest.setOriginHost(new diameter.base.OriginHost("id-1244938738.diameter.com"));
        updateLocationRequest.setOriginRealm(new diameter.base.OriginRealm("id1131513074.diameter.com"));
        updateLocationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-301425955.diameter.com"));
        updateLocationRequest.setUserName(new diameter.base.UserName("utf8string-1364905035"));
        updateLocationRequest.setULRFlags(new ULRFlags(new Integer(-875278898)));
        updateLocationRequest.setVisitedPLMNId(new VisitedPLMNId("octetstring-823554722"));
        updateLocationRequest.setRATType(new RATType(RATType.Value.UMB));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-5337440)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1406783537)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1208207618)));
            updateLocationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        updateLocationRequest.setSGSNNumber(new SGSNNumber("octetstring-1949143573"));
        updateLocationRequest.setDestinationHost(new diameter.base.DestinationHost("id7168915.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1238849326)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1453018317)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1005393192)));
            // add more AVP as ANY values to supportedFeatures
            updateLocationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string1752777463"));
            terminalInformation.setS6a3GPP2MEID(new S6a3GPP2MEID("octetstring-291771400"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string-384914477"));
            // add more AVP as ANY values to terminalInformation
            updateLocationRequest.setTerminalInformation(terminalInformation);
        }
        updateLocationRequest.setUESRVCCCapability(new UESRVCCCapability(UESRVCCCapability.Value.UE_SRVCC_NOT_SUPPORTED));
        updateLocationRequest.setHomogeneousSupportofIMSVoiceOverPSSessions(new HomogeneousSupportofIMSVoiceOverPSSessions(HomogeneousSupportofIMSVoiceOverPSSessions.Value.SUPPORTED));
        updateLocationRequest.setGMLCAddress(new GMLCAddress(new Address(Address.Family.IPV4, "117.205.21.182")));
        {
            ActiveAPN activeAPN = new ActiveAPN();
            activeAPN.setContextIdentifier(new ContextIdentifier(new Integer(281965698)));
            activeAPN.setServiceSelection(new ServiceSelection("utf8string1495669261"));
            {
                MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "184.237.152.159")));
                {
                    MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                    mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-1070141980.diameter.com"));
                    mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id951706519.diameter.com"));
                    // add more AVP as ANY values to mIPHomeAgentHost
                    mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                }
                mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-1634200102"));
                // add more AVP as ANY values to mIP6AgentInfo
                activeAPN.setMIP6AgentInfo(mIP6AgentInfo);
            }
            activeAPN.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring2076320685"));
            {
                SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string-386771843"));
                {
                    MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                    mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "255.210.36.157")));
                    {
                        MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                        mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-356864613.diameter.com"));
                        mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1213775521.diameter.com"));
                        // add more AVP as ANY values to mIPHomeAgentHost
                        mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                    }
                    mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-136749418"));
                    // add more AVP as ANY values to mIP6AgentInfo
                    specificAPNInfo.setMIP6AgentInfo(mIP6AgentInfo);
                }
                specificAPNInfo.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring492406183"));
                // add more AVP as ANY values to specificAPNInfo
                activeAPN.addSpecificAPNInfo(specificAPNInfo);
            }
            // add more AVP as ANY values to activeAPN
            updateLocationRequest.addActiveAPN(activeAPN);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-32825965.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring313414894"));
            // add more AVP as ANY values to proxyInfo
            updateLocationRequest.addProxyInfo(proxyInfo);
        }
        updateLocationRequest.addRouteRecord(new diameter.base.RouteRecord("id821952865.diameter.com"));
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
        updateLocationAnswer.setSessionId(new diameter.base.SessionId("utf8string1142472604"));
        updateLocationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        updateLocationAnswer.setOriginHost(new diameter.base.OriginHost("id809154536.diameter.com"));
        updateLocationAnswer.setOriginRealm(new diameter.base.OriginRealm("id-735679215.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1284928940)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-722440832)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(2032308843)));
            updateLocationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        updateLocationAnswer.setULAFlags(new ULAFlags(new Integer(772167170)));
        updateLocationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(32359696)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(766850137)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(1279820859)));
            updateLocationAnswer.setExperimentalResult(experimentalResult);
        }
        updateLocationAnswer.setErrorDiagnostic(new ErrorDiagnostic(ErrorDiagnostic.Value.NO_GPRS_DATA_SUBSCRIBED));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(247162646)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(349048607)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(256454650)));
            // add more AVP as ANY values to supportedFeatures
            updateLocationAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            SubscriptionData subscriptionData = new SubscriptionData();
            subscriptionData.setSubscriberStatus(new SubscriberStatus(SubscriberStatus.Value.SERVICEGRANTED));
            subscriptionData.setMSISDN(new MSISDN("octetstring1597755773"));
            subscriptionData.setSTNSR(new STNSR("octetstring-819812122"));
            subscriptionData.setICSIndicator(new ICSIndicator(ICSIndicator.Value.TRUE));
            subscriptionData.setNetworkAccessMode(new NetworkAccessMode(NetworkAccessMode.Value.ONLY_PACKET));
            subscriptionData.setOperatorDeterminedBarring(new OperatorDeterminedBarring(new Integer(1840941058)));
            subscriptionData.setHPLMNODB(new HPLMNODB(new Integer(-482360629)));
            subscriptionData.addRegionalSubscriptionZoneCode(new RegionalSubscriptionZoneCode("octetstring2128625668"));
            subscriptionData.setAccessRestrictionData(new AccessRestrictionData(new Integer(486734155)));
            subscriptionData.setAPNOIReplacement(new APNOIReplacement("utf8string1991013178"));
            {
                LCSInfo lCSInfo = new LCSInfo();
                lCSInfo.addGMLCNumber(new GMLCNumber("octetstring-704601031"));
                {
                    LCSPrivacyException lCSPrivacyException = new LCSPrivacyException();
                    lCSPrivacyException.setSSCode(new SSCode("octetstring883247659"));
                    lCSPrivacyException.setSSStatus(new SSStatus("octetstring-895327975"));
                    lCSPrivacyException.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFY_LOCATION_ALLOWED));
                    {
                        ExternalClient externalClient = new ExternalClient();
                        externalClient.setClientIdentity(new ClientIdentity("octetstring2049493864"));
                        externalClient.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.GMLC_LIST));
                        externalClient.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFY_LOCATION_ALLOWED));
                        // add more AVP as ANY values to externalClient
                        lCSPrivacyException.addExternalClient(externalClient);
                    }
                    lCSPrivacyException.addPLMNClient(new PLMNClient(PLMNClient.Value.O_AND_M_VPLMN));
                    {
                        ServiceType serviceType = new ServiceType();
                        serviceType.setServiceTypeIdentity(new ServiceTypeIdentity(new Integer(-188112346)));
                        serviceType.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.GMLC_LIST));
                        serviceType.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.LOCATION_NOT_ALLOWED));
                        // add more AVP as ANY values to serviceType
                        lCSPrivacyException.addServiceType(serviceType);
                    }
                    // add more AVP as ANY values to lCSPrivacyException
                    lCSInfo.addLCSPrivacyException(lCSPrivacyException);
                }
                {
                    MOLR mOLR = new MOLR();
                    mOLR.setSSCode(new SSCode("octetstring-115658309"));
                    mOLR.setSSStatus(new SSStatus("octetstring-204981542"));
                    // add more AVP as ANY values to mOLR
                    lCSInfo.addMOLR(mOLR);
                }
                // add more AVP as ANY values to lCSInfo
                subscriptionData.setLCSInfo(lCSInfo);
            }
            {
                TeleserviceList teleserviceList = new TeleserviceList();
                teleserviceList.addTSCode(new TSCode("octetstring-1850644829"));
                // add more AVP as ANY values to teleserviceList
                subscriptionData.setTeleserviceList(teleserviceList);
            }
            {
                CallBarringInforList callBarringInforList = new CallBarringInforList();
                callBarringInforList.addSSCode(new SSCode("octetstring-1415316963"));
                // add more AVP as ANY values to callBarringInforList
                subscriptionData.setCallBarringInforList(callBarringInforList);
            }
            subscriptionData.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string-1027769559"));
            {
                AMBR aMBR = new AMBR();
                aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1184061892)));
                aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(118624131)));
                // add more AVP as ANY values to aMBR
                subscriptionData.setAMBR(aMBR);
            }
            {
                APNConfigurationProfile aPNConfigurationProfile = new APNConfigurationProfile();
                aPNConfigurationProfile.setContextIdentifier(new ContextIdentifier(new Integer(1213914421)));
                aPNConfigurationProfile.setAllAPNConfigurationsIncludedIndicator(new AllAPNConfigurationsIncludedIndicator(AllAPNConfigurationsIncludedIndicator.Value.MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED));
                {
                    APNConfiguration aPNConfiguration = new APNConfiguration();
                    aPNConfiguration.setContextIdentifier(new ContextIdentifier(new Integer(-1017491831)));
                    aPNConfiguration.setPDNType(new PDNType(PDNType.Value.IPv4));
                    aPNConfiguration.setServiceSelection(new ServiceSelection("utf8string710808082"));
                    aPNConfiguration.addServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "174.238.237.228")));
                    {
                        EPSSubscribedQoSProfile ePSSubscribedQoSProfile = new EPSSubscribedQoSProfile();
                        ePSSubscribedQoSProfile.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.TRAFFIC_CLASS_E));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1490607075)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                            ePSSubscribedQoSProfile.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        // add more AVP as ANY values to ePSSubscribedQoSProfile
                        aPNConfiguration.setEPSSubscribedQoSProfile(ePSSubscribedQoSProfile);
                    }
                    aPNConfiguration.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.ALLOWED));
                    {
                        MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                        mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "196.217.14.196")));
                        {
                            MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                            mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-290665254.diameter.com"));
                            mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id1925390229.diameter.com"));
                            // add more AVP as ANY values to mIPHomeAgentHost
                            mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                        }
                        mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-747339106"));
                        // add more AVP as ANY values to mIP6AgentInfo
                        aPNConfiguration.setMIP6AgentInfo(mIP6AgentInfo);
                    }
                    aPNConfiguration.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring2052218520"));
                    aPNConfiguration.setPDNGWAllocationType(new PDNGWAllocationType(PDNGWAllocationType.Value.DYNAMIC));
                    aPNConfiguration.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string-1798863938"));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-1911703525)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1180966260)));
                        // add more AVP as ANY values to aMBR
                        aPNConfiguration.setAMBR(aMBR);
                    }
                    {
                        SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                        specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string-933057438"));
                        {
                            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "68.37.201.64")));
                            {
                                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id300324354.diameter.com"));
                                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1741813418.diameter.com"));
                                // add more AVP as ANY values to mIPHomeAgentHost
                                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                            }
                            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-1777799979"));
                            // add more AVP as ANY values to mIP6AgentInfo
                            specificAPNInfo.setMIP6AgentInfo(mIP6AgentInfo);
                        }
                        specificAPNInfo.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring968114933"));
                        // add more AVP as ANY values to specificAPNInfo
                        aPNConfiguration.addSpecificAPNInfo(specificAPNInfo);
                    }
                    aPNConfiguration.setAPNOIReplacement(new APNOIReplacement("utf8string-748309525"));
                    aPNConfiguration.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_ALLOWED));
                    aPNConfiguration.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_CONDITIONAL));
                    // add more AVP as ANY values to aPNConfiguration
                    aPNConfigurationProfile.addAPNConfiguration(aPNConfiguration);
                }
                // add more AVP as ANY values to aPNConfigurationProfile
                subscriptionData.setAPNConfigurationProfile(aPNConfigurationProfile);
            }
            subscriptionData.setRATFrequencySelectionPriorityID(new RATFrequencySelectionPriorityID(new Integer(1216562425)));
            {
                TraceData traceData = new TraceData();
                traceData.setTraceReference(new TraceReference("octetstring-926153852"));
                traceData.setTraceDepth(new TraceDepth(TraceDepth.Value.MediumWithoutVendorSpecificExtension));
                traceData.setTraceNETypeList(new TraceNETypeList("octetstring-1847679907"));
                traceData.setTraceEventList(new TraceEventList("octetstring-1518779633"));
                traceData.setTraceCollectionEntity(new TraceCollectionEntity(new Address(Address.Family.IPV4, "145.221.212.130")));
                traceData.setTraceInterfaceList(new TraceInterfaceList("octetstring-739292141"));
                traceData.setOMCId(new OMCId("octetstring1402158334"));
                {
                    MDTConfiguration mDTConfiguration = new MDTConfiguration();
                    mDTConfiguration.setJobType(new JobType(JobType.Value.IMMEDIATE_MDT_AND_TRACE));
                    {
                        AreaScope areaScope = new AreaScope();
                        areaScope.addCellGlobalIdentity(new CellGlobalIdentity("octetstring1146160561"));
                        areaScope.addEUTRANCellGlobalIdentity(new EUTRANCellGlobalIdentity("octetstring-1711119759"));
                        areaScope.addRoutingAreaIdentity(new RoutingAreaIdentity("octetstring-404249258"));
                        areaScope.addLocationAreaIdentity(new LocationAreaIdentity("octetstring185227249"));
                        areaScope.addTrackingAreaIdentity(new TrackingAreaIdentity("octetstring807935694"));
                        // add more AVP as ANY values to areaScope
                        mDTConfiguration.setAreaScope(areaScope);
                    }
                    mDTConfiguration.setListOfMeasurements(new ListOfMeasurements(new Integer(-509502220)));
                    mDTConfiguration.setReportingTrigger(new ReportingTrigger(new Integer(182577398)));
                    mDTConfiguration.setReportInterval(new ReportInterval(ReportInterval.Value.MSEC_6000));
                    mDTConfiguration.setReportAmount(new ReportAmount(ReportAmount.Value.NUM_REPORTS_INFINITE));
                    mDTConfiguration.setEventThresholdRSRP(new EventThresholdRSRP(new Integer(605284728)));
                    mDTConfiguration.setEventThresholdRSRQ(new EventThresholdRSRQ(new Integer(1779081763)));
                    mDTConfiguration.setLoggingInterval(new LoggingInterval(LoggingInterval.Value.LOG_PERIODICITY_1_28));
                    mDTConfiguration.setLoggingDuration(new LoggingDuration(LoggingDuration.Value.SEC_7200));
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
                    pDPContext.setContextIdentifier(new ContextIdentifier(new Integer(-1114678986)));
                    pDPContext.setPDPType(new PDPType("octetstring7238661"));
                    pDPContext.setQoSSubscribed(new QoSSubscribed("octetstring964055593"));
                    pDPContext.setServiceSelection(new ServiceSelection("utf8string-1709529910"));
                    pDPContext.setPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "195.122.78.3")));
                    pDPContext.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.ALLOWED));
                    pDPContext.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string137503490"));
                    pDPContext.setExtPDPType(new ExtPDPType("octetstring-1859694827"));
                    pDPContext.setExtPDPAddress(new ExtPDPAddress(new Address(Address.Family.IPV4, "61.89.160.189")));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-132731777)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1866992784)));
                        // add more AVP as ANY values to aMBR
                        pDPContext.setAMBR(aMBR);
                    }
                    pDPContext.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_NOTALLOWED));
                    pDPContext.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_ONLY));
                    // add more AVP as ANY values to pDPContext
                    gPRSSubscriptionData.addPDPContext(pDPContext);
                }
                // add more AVP as ANY values to gPRSSubscriptionData
                subscriptionData.setGPRSSubscriptionData(gPRSSubscriptionData);
            }
            {
                CSGSubscriptionData cSGSubscriptionData = new CSGSubscriptionData();
                cSGSubscriptionData.setCSGId(new CSGId(new Integer(-1991923748)));
                cSGSubscriptionData.setExpirationDate(new ExpirationDate(-481242071));
                cSGSubscriptionData.addServiceSelection(new ServiceSelection("utf8string-508625818"));
                // add more AVP as ANY values to cSGSubscriptionData
                subscriptionData.addCSGSubscriptionData(cSGSubscriptionData);
            }
            subscriptionData.setRoamingRestrictedDueToUnsupportedFeature(new RoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature.Value.Roaming_Restricted_Due_To_Unsupported_Feature));
            subscriptionData.setSubscribedPeriodicRAUTAUTimer(new SubscribedPeriodicRAUTAUTimer(new Integer(773521383)));
            subscriptionData.setMPSPriority(new MPSPriority(new Integer(1094181398)));
            subscriptionData.setVPLMNLIPAAllowed(new VPLMNLIPAAllowed(VPLMNLIPAAllowed.Value.LIPA_NOTALLOWED));
            subscriptionData.setRelayNodeIndicator(new RelayNodeIndicator(RelayNodeIndicator.Value.RELAY_NODE));
            subscriptionData.setMDTUserConsent(new MDTUserConsent(MDTUserConsent.Value.CONSENT_NOT_GIVEN));
            // add more AVP as ANY values to subscriptionData
            updateLocationAnswer.setSubscriptionData(subscriptionData);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-799607266.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1138960444"));
            // add more AVP as ANY values to proxyInfo
            updateLocationAnswer.addProxyInfo(proxyInfo);
        }
        updateLocationAnswer.addRouteRecord(new diameter.base.RouteRecord("id742336391.diameter.com"));
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
