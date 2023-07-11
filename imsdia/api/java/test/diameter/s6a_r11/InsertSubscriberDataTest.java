package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class InsertSubscriberDataTest {

    public static void testInsertSubscriberDataRequest() throws Exception {
        InsertSubscriberDataRequest insertSubscriberDataRequest = new InsertSubscriberDataRequest(false, false);
        insertSubscriberDataRequest.setSessionId(new diameter.base.SessionId("utf8string-1950171374"));
        insertSubscriberDataRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        insertSubscriberDataRequest.setOriginHost(new diameter.base.OriginHost("id-1618927828.diameter.com"));
        insertSubscriberDataRequest.setOriginRealm(new diameter.base.OriginRealm("id518527471.diameter.com"));
        insertSubscriberDataRequest.setDestinationHost(new diameter.base.DestinationHost("id-1701903606.diameter.com"));
        insertSubscriberDataRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1802999733.diameter.com"));
        insertSubscriberDataRequest.setUserName(new diameter.base.UserName("utf8string-1989401401"));
        {
            SubscriptionData subscriptionData = new SubscriptionData();
            subscriptionData.setSubscriberStatus(new SubscriberStatus(SubscriberStatus.Value.OPERATORDETERMINEDBARRING));
            subscriptionData.setMSISDN(new MSISDN("octetstring1947420198"));
            subscriptionData.setAMSISDN(new AMSISDN("octetstring-1932235081"));
            subscriptionData.setSTNSR(new STNSR("octetstring-1071675407"));
            subscriptionData.setICSIndicator(new ICSIndicator(ICSIndicator.Value.FALSE));
            subscriptionData.setNetworkAccessMode(new NetworkAccessMode(NetworkAccessMode.Value.PACKET_AND_CIRCUIT));
            subscriptionData.setOperatorDeterminedBarring(new OperatorDeterminedBarring(new Integer(1309294093)));
            subscriptionData.setHPLMNODB(new HPLMNODB(new Integer(1286358271)));
            subscriptionData.addRegionalSubscriptionZoneCode(new RegionalSubscriptionZoneCode("octetstring-812542350"));
            subscriptionData.setAccessRestrictionData(new AccessRestrictionData(new Integer(1458131147)));
            subscriptionData.setAPNOIReplacement(new APNOIReplacement("utf8string742733569"));
            {
                LCSInfo lCSInfo = new LCSInfo();
                lCSInfo.addGMLCNumber(new GMLCNumber("octetstring1364714301"));
                {
                    LCSPrivacyException lCSPrivacyException = new LCSPrivacyException();
                    lCSPrivacyException.setSSCode(new SSCode("octetstring-373309686"));
                    lCSPrivacyException.setSSStatus(new SSStatus("octetstring1013338796"));
                    lCSPrivacyException.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE));
                    {
                        ExternalClient externalClient = new ExternalClient();
                        externalClient.setClientIdentity(new ClientIdentity("octetstring618808371"));
                        externalClient.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.GMLC_LIST));
                        externalClient.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFY_LOCATION_ALLOWED));
                        // add more AVP as ANY values to externalClient
                        lCSPrivacyException.addExternalClient(externalClient);
                    }
                    lCSPrivacyException.addPLMNClient(new PLMNClient(PLMNClient.Value.ANONYMOUS_LOCATION));
                    {
                        ServiceType serviceType = new ServiceType();
                        serviceType.setServiceTypeIdentity(new ServiceTypeIdentity(new Integer(1170383656)));
                        serviceType.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.HOME_COUNTRY));
                        serviceType.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE));
                        // add more AVP as ANY values to serviceType
                        lCSPrivacyException.addServiceType(serviceType);
                    }
                    // add more AVP as ANY values to lCSPrivacyException
                    lCSInfo.addLCSPrivacyException(lCSPrivacyException);
                }
                {
                    MOLR mOLR = new MOLR();
                    mOLR.setSSCode(new SSCode("octetstring-223797772"));
                    mOLR.setSSStatus(new SSStatus("octetstring1790347499"));
                    // add more AVP as ANY values to mOLR
                    lCSInfo.addMOLR(mOLR);
                }
                // add more AVP as ANY values to lCSInfo
                subscriptionData.setLCSInfo(lCSInfo);
            }
            {
                TeleserviceList teleserviceList = new TeleserviceList();
                teleserviceList.addTSCode(new TSCode("octetstring-1404544490"));
                // add more AVP as ANY values to teleserviceList
                subscriptionData.setTeleserviceList(teleserviceList);
            }
            {
                CallBarringInforList callBarringInforList = new CallBarringInforList();
                callBarringInforList.addSSCode(new SSCode("octetstring1296611799"));
                // add more AVP as ANY values to callBarringInforList
                subscriptionData.setCallBarringInforList(callBarringInforList);
            }
            subscriptionData.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string1755477586"));
            {
                AMBR aMBR = new AMBR();
                aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-1436174384)));
                aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-210325122)));
                // add more AVP as ANY values to aMBR
                subscriptionData.setAMBR(aMBR);
            }
            {
                APNConfigurationProfile aPNConfigurationProfile = new APNConfigurationProfile();
                aPNConfigurationProfile.setContextIdentifier(new ContextIdentifier(new Integer(-1997407953)));
                aPNConfigurationProfile.setAllAPNConfigurationsIncludedIndicator(new AllAPNConfigurationsIncludedIndicator(AllAPNConfigurationsIncludedIndicator.Value.MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED));
                {
                    APNConfiguration aPNConfiguration = new APNConfiguration();
                    aPNConfiguration.setContextIdentifier(new ContextIdentifier(new Integer(1586123769)));
                    aPNConfiguration.setPDNType(new PDNType(PDNType.Value.IPv6));
                    aPNConfiguration.setServiceSelection(new ServiceSelection("utf8string-1121369405"));
                    aPNConfiguration.addServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "41.214.234.73")));
                    {
                        EPSSubscribedQoSProfile ePSSubscribedQoSProfile = new EPSSubscribedQoSProfile();
                        ePSSubscribedQoSProfile.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_5));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1225308946)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            ePSSubscribedQoSProfile.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        // add more AVP as ANY values to ePSSubscribedQoSProfile
                        aPNConfiguration.setEPSSubscribedQoSProfile(ePSSubscribedQoSProfile);
                    }
                    aPNConfiguration.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.ALLOWED));
                    {
                        MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                        mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "222.79.180.53")));
                        {
                            MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                            mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-653594974.diameter.com"));
                            mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1971173178.diameter.com"));
                            // add more AVP as ANY values to mIPHomeAgentHost
                            mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                        }
                        mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-2061770017"));
                        // add more AVP as ANY values to mIP6AgentInfo
                        aPNConfiguration.setMIP6AgentInfo(mIP6AgentInfo);
                    }
                    aPNConfiguration.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring-1758676658"));
                    aPNConfiguration.setPDNGWAllocationType(new PDNGWAllocationType(PDNGWAllocationType.Value.DYNAMIC));
                    aPNConfiguration.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string-629980177"));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-470085488)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(78684024)));
                        // add more AVP as ANY values to aMBR
                        aPNConfiguration.setAMBR(aMBR);
                    }
                    {
                        SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                        specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string263224240"));
                        {
                            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "221.108.100.160")));
                            {
                                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-274422334.diameter.com"));
                                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1250524771.diameter.com"));
                                // add more AVP as ANY values to mIPHomeAgentHost
                                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                            }
                            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-713807177"));
                            // add more AVP as ANY values to mIP6AgentInfo
                            specificAPNInfo.setMIP6AgentInfo(mIP6AgentInfo);
                        }
                        specificAPNInfo.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring-1812307209"));
                        // add more AVP as ANY values to specificAPNInfo
                        aPNConfiguration.addSpecificAPNInfo(specificAPNInfo);
                    }
                    aPNConfiguration.setAPNOIReplacement(new APNOIReplacement("utf8string-1012146964"));
                    aPNConfiguration.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_ALLOWED));
                    aPNConfiguration.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_PROHIBITED));
                    // add more AVP as ANY values to aPNConfiguration
                    aPNConfigurationProfile.addAPNConfiguration(aPNConfiguration);
                }
                // add more AVP as ANY values to aPNConfigurationProfile
                subscriptionData.setAPNConfigurationProfile(aPNConfigurationProfile);
            }
            subscriptionData.setRATFrequencySelectionPriorityID(new RATFrequencySelectionPriorityID(new Integer(1515808312)));
            {
                TraceData traceData = new TraceData();
                traceData.setTraceReference(new TraceReference("octetstring-961054478"));
                traceData.setTraceDepth(new TraceDepth(TraceDepth.Value.Medium));
                traceData.setTraceNETypeList(new TraceNETypeList("octetstring1750316464"));
                traceData.setTraceEventList(new TraceEventList("octetstring-63034342"));
                traceData.setTraceCollectionEntity(new TraceCollectionEntity(new Address(Address.Family.IPV4, "42.216.94.143")));
                traceData.setTraceInterfaceList(new TraceInterfaceList("octetstring-655259811"));
                traceData.setOMCId(new OMCId("octetstring1338452106"));
                {
                    MDTConfiguration mDTConfiguration = new MDTConfiguration();
                    mDTConfiguration.setJobType(new JobType(JobType.Value.LOGGED_MDT_ONLY));
                    {
                        AreaScope areaScope = new AreaScope();
                        areaScope.addCellGlobalIdentity(new CellGlobalIdentity("octetstring-1271643135"));
                        areaScope.addEUTRANCellGlobalIdentity(new EUTRANCellGlobalIdentity("octetstring1065880509"));
                        areaScope.addRoutingAreaIdentity(new RoutingAreaIdentity("octetstring-1106556182"));
                        areaScope.addLocationAreaIdentity(new LocationAreaIdentity("octetstring-1439066110"));
                        areaScope.addTrackingAreaIdentity(new TrackingAreaIdentity("octetstring-965688098"));
                        // add more AVP as ANY values to areaScope
                        mDTConfiguration.setAreaScope(areaScope);
                    }
                    mDTConfiguration.setListOfMeasurements(new ListOfMeasurements(new Integer(-1824506857)));
                    mDTConfiguration.setReportingTrigger(new ReportingTrigger(new Integer(1642178722)));
                    mDTConfiguration.setReportInterval(new ReportInterval(ReportInterval.Value.MSEC_20000));
                    mDTConfiguration.setReportAmount(new ReportAmount(ReportAmount.Value.NUM_REPORTS_8));
                    mDTConfiguration.setEventThresholdRSRP(new EventThresholdRSRP(new Integer(-588683708)));
                    mDTConfiguration.setEventThresholdRSRQ(new EventThresholdRSRQ(new Integer(-1805090214)));
                    mDTConfiguration.setLoggingInterval(new LoggingInterval(LoggingInterval.Value.LOG_PERIODICITY_20_48));
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
                    pDPContext.setContextIdentifier(new ContextIdentifier(new Integer(-1441935267)));
                    pDPContext.setPDPType(new PDPType("octetstring-2132542292"));
                    pDPContext.setQoSSubscribed(new QoSSubscribed("octetstring1286797577"));
                    pDPContext.setServiceSelection(new ServiceSelection("utf8string-1865652914"));
                    pDPContext.setPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "123.138.223.194")));
                    pDPContext.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.NOTALLOWED));
                    pDPContext.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string-300738581"));
                    pDPContext.setExtPDPType(new ExtPDPType("octetstring-1248181555"));
                    pDPContext.setExtPDPAddress(new ExtPDPAddress(new Address(Address.Family.IPV4, "225.5.38.22")));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-1649805986)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-482489034)));
                        // add more AVP as ANY values to aMBR
                        pDPContext.setAMBR(aMBR);
                    }
                    pDPContext.setAPNOIReplacement(new APNOIReplacement("utf8string-44868615"));
                    pDPContext.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_ALLOWED));
                    pDPContext.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_PROHIBITED));
                    // add more AVP as ANY values to pDPContext
                    gPRSSubscriptionData.addPDPContext(pDPContext);
                }
                // add more AVP as ANY values to gPRSSubscriptionData
                subscriptionData.setGPRSSubscriptionData(gPRSSubscriptionData);
            }
            {
                CSGSubscriptionData cSGSubscriptionData = new CSGSubscriptionData();
                cSGSubscriptionData.setCSGId(new CSGId(new Integer(-130298220)));
                cSGSubscriptionData.setExpirationDate(new ExpirationDate(-1948488039));
                cSGSubscriptionData.addServiceSelection(new ServiceSelection("utf8string-1378028718"));
                cSGSubscriptionData.setVisitedPLMNId(new VisitedPLMNId("octetstring-1396915814"));
                // add more AVP as ANY values to cSGSubscriptionData
                subscriptionData.addCSGSubscriptionData(cSGSubscriptionData);
            }
            subscriptionData.setRoamingRestrictedDueToUnsupportedFeature(new RoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature.Value.Roaming_Restricted_Due_To_Unsupported_Feature));
            subscriptionData.setSubscribedPeriodicRAUTAUTimer(new SubscribedPeriodicRAUTAUTimer(new Integer(1398786057)));
            subscriptionData.setMPSPriority(new MPSPriority(new Integer(1810539559)));
            subscriptionData.setVPLMNLIPAAllowed(new VPLMNLIPAAllowed(VPLMNLIPAAllowed.Value.LIPA_ALLOWED));
            subscriptionData.setRelayNodeIndicator(new RelayNodeIndicator(RelayNodeIndicator.Value.RELAY_NODE));
            subscriptionData.setMDTUserConsent(new MDTUserConsent(MDTUserConsent.Value.CONSENT_GIVEN));
            subscriptionData.setSubscribedVSRVCC(new SubscribedVSRVCC(SubscribedVSRVCC.Value.VSRVCC_SUBSCRIBED));
            subscriptionData.setSubscriptionDataFlags(new SubscriptionDataFlags(new Integer(-2049059571)));
            // add more AVP as ANY values to subscriptionData
            insertSubscriberDataRequest.setSubscriptionData(subscriptionData);
        }
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1018936694)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1135243811)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(431489399)));
            insertSubscriberDataRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        insertSubscriberDataRequest.setIDRFlags(new IDRFlags(new Integer(1140266307)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1142529369)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(961630538)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1392603538)));
            // add more AVP as ANY values to supportedFeatures
            insertSubscriberDataRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id183514754.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1860342631"));
            // add more AVP as ANY values to proxyInfo
            insertSubscriberDataRequest.addProxyInfo(proxyInfo);
        }
        insertSubscriberDataRequest.addRouteRecord(new diameter.base.RouteRecord("id1460735395.diameter.com"));
        // add more AVP as ANY values to insertSubscriberDataRequest

        byte[] buffer = insertSubscriberDataRequest.encode();
        InsertSubscriberDataRequest insertSubscriberDataRequest2 = new InsertSubscriberDataRequest(buffer);
        String s1 = insertSubscriberDataRequest.toString();
        String s2 = insertSubscriberDataRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("insertSubscriberDataRequest1 = " + s1);
            System.err.println("insertSubscriberDataRequest2 = " + s2);
            throw new VerificationException("InsertSubscriberDataRequest encoding/decoding failure");
        }
    }

    public static void testInsertSubscriberDataAnswer() throws Exception {
        InsertSubscriberDataAnswer insertSubscriberDataAnswer = new InsertSubscriberDataAnswer(false, false);
        insertSubscriberDataAnswer.setSessionId(new diameter.base.SessionId("utf8string-1122593459"));
        insertSubscriberDataAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        insertSubscriberDataAnswer.setOriginHost(new diameter.base.OriginHost("id-2048656553.diameter.com"));
        insertSubscriberDataAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1748977696.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1533705412)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(806928248)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1044683199)));
            insertSubscriberDataAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1188314696)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(631986352)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-229722095)));
            // add more AVP as ANY values to supportedFeatures
            insertSubscriberDataAnswer.addSupportedFeatures(supportedFeatures);
        }
        insertSubscriberDataAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-103878555)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-117440261)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1566605000)));
            insertSubscriberDataAnswer.setExperimentalResult(experimentalResult);
        }
        insertSubscriberDataAnswer.setIMSVoiceOverPSSessionsSupported(new IMSVoiceOverPSSessionsSupported(IMSVoiceOverPSSessionsSupported.Value.NOT_SUPPORTED));
        insertSubscriberDataAnswer.setLastUEActivityTime(new LastUEActivityTime(1157841590));
        insertSubscriberDataAnswer.setRATType(new RATType(RATType.Value.VIRTUAL));
        insertSubscriberDataAnswer.setIDAFlags(new IDAFlags(new Integer(-112364951)));
        {
            EPSUserState ePSUserState = new EPSUserState();
            {
                MMEUserState mMEUserState = new MMEUserState();
                mMEUserState.setUserState(new UserState(UserState.Value.CONNECTED_REACHABLE_FOR_PAGING));
                // add more AVP as ANY values to mMEUserState
                ePSUserState.setMMEUserState(mMEUserState);
            }
            {
                SGSNUserState sGSNUserState = new SGSNUserState();
                sGSNUserState.setUserState(new UserState(UserState.Value.CONNECTED_REACHABLE_FOR_PAGING));
                // add more AVP as ANY values to sGSNUserState
                ePSUserState.setSGSNUserState(sGSNUserState);
            }
            // add more AVP as ANY values to ePSUserState
            insertSubscriberDataAnswer.setEPSUserState(ePSUserState);
        }
        {
            EPSLocationInformation ePSLocationInformation = new EPSLocationInformation();
            {
                MMELocationInformation mMELocationInformation = new MMELocationInformation();
                mMELocationInformation.setEUTRANCellGlobalIdentity(new EUTRANCellGlobalIdentity("octetstring-764387656"));
                mMELocationInformation.setTrackingAreaIdentity(new TrackingAreaIdentity("octetstring-1634213918"));
                mMELocationInformation.setGeographicalInformation(new GeographicalInformation("octetstring1017342563"));
                mMELocationInformation.setGeodeticInformation(new GeodeticInformation("octetstring-507984655"));
                mMELocationInformation.setCurrentLocationRetrieved(new CurrentLocationRetrieved(CurrentLocationRetrieved.Value.ACTIVE_LOCATION_RETRIEVAL));
                mMELocationInformation.setAgeOfLocationInformation(new AgeOfLocationInformation(new Integer(-32724086)));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(140623475)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.CLOSED_MODE));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.NOT_CSG_MEMBER));
                    mMELocationInformation.setUserCSGInformation(userCSGInformation);
                }
                // add more AVP as ANY values to mMELocationInformation
                ePSLocationInformation.setMMELocationInformation(mMELocationInformation);
            }
            {
                SGSNLocationInformation sGSNLocationInformation = new SGSNLocationInformation();
                sGSNLocationInformation.setCellGlobalIdentity(new CellGlobalIdentity("octetstring-1851714021"));
                sGSNLocationInformation.setLocationAreaIdentity(new LocationAreaIdentity("octetstring809018202"));
                sGSNLocationInformation.setServiceAreaIdentity(new ServiceAreaIdentity("octetstring2065214981"));
                sGSNLocationInformation.setRoutingAreaIdentity(new RoutingAreaIdentity("octetstring-1487725761"));
                sGSNLocationInformation.setGeographicalInformation(new GeographicalInformation("octetstring-35523612"));
                sGSNLocationInformation.setGeodeticInformation(new GeodeticInformation("octetstring1183124557"));
                sGSNLocationInformation.setCurrentLocationRetrieved(new CurrentLocationRetrieved(CurrentLocationRetrieved.Value.ACTIVE_LOCATION_RETRIEVAL));
                sGSNLocationInformation.setAgeOfLocationInformation(new AgeOfLocationInformation(new Integer(-61685389)));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(40626634)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.CLOSED_MODE));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.CSG_MEMBER));
                    sGSNLocationInformation.setUserCSGInformation(userCSGInformation);
                }
                // add more AVP as ANY values to sGSNLocationInformation
                ePSLocationInformation.setSGSNLocationInformation(sGSNLocationInformation);
            }
            // add more AVP as ANY values to ePSLocationInformation
            insertSubscriberDataAnswer.setEPSLocationInformation(ePSLocationInformation);
        }
        {
            LocalTimeZone localTimeZone = new LocalTimeZone();
            localTimeZone.setS6A3GPPMSTimeZone(new S6A3GPPMSTimeZone("octetstring1364302229"));
            localTimeZone.setDaylightSavingTime(new DaylightSavingTime(DaylightSavingTime.Value.NO_ADJUSTMENT));
            // add more AVP as ANY values to localTimeZone
            insertSubscriberDataAnswer.setLocalTimeZone(localTimeZone);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-700595011.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1606555363"));
            // add more AVP as ANY values to proxyInfo
            insertSubscriberDataAnswer.addProxyInfo(proxyInfo);
        }
        insertSubscriberDataAnswer.addRouteRecord(new diameter.base.RouteRecord("id-385407216.diameter.com"));
        // add more AVP as ANY values to insertSubscriberDataAnswer

        byte[] buffer = insertSubscriberDataAnswer.encode();
        InsertSubscriberDataAnswer insertSubscriberDataAnswer2 = new InsertSubscriberDataAnswer(buffer);
        String s1 = insertSubscriberDataAnswer.toString();
        String s2 = insertSubscriberDataAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("insertSubscriberDataAnswer1 = " + s1);
            System.err.println("insertSubscriberDataAnswer2 = " + s2);
            throw new VerificationException("InsertSubscriberDataAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testInsertSubscriberDataRequest();
        testInsertSubscriberDataAnswer();
    }
}
