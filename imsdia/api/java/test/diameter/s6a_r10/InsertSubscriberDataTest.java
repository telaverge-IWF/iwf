package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class InsertSubscriberDataTest {

    public static void testInsertSubscriberDataRequest() throws Exception {
        InsertSubscriberDataRequest insertSubscriberDataRequest = new InsertSubscriberDataRequest(false, false);
        insertSubscriberDataRequest.setSessionId(new diameter.base.SessionId("utf8string276346462"));
        insertSubscriberDataRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        insertSubscriberDataRequest.setOriginHost(new diameter.base.OriginHost("id1972054369.diameter.com"));
        insertSubscriberDataRequest.setOriginRealm(new diameter.base.OriginRealm("id1926075077.diameter.com"));
        insertSubscriberDataRequest.setDestinationHost(new diameter.base.DestinationHost("id-866565126.diameter.com"));
        insertSubscriberDataRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1619186136.diameter.com"));
        insertSubscriberDataRequest.setUserName(new diameter.base.UserName("utf8string1870036478"));
        {
            SubscriptionData subscriptionData = new SubscriptionData();
            subscriptionData.setSubscriberStatus(new SubscriberStatus(SubscriberStatus.Value.OPERATORDETERMINEDBARRING));
            subscriptionData.setMSISDN(new MSISDN("octetstring-1242053142"));
            subscriptionData.setSTNSR(new STNSR("octetstring-984733151"));
            subscriptionData.setICSIndicator(new ICSIndicator(ICSIndicator.Value.FALSE));
            subscriptionData.setNetworkAccessMode(new NetworkAccessMode(NetworkAccessMode.Value.ONLY_PACKET));
            subscriptionData.setOperatorDeterminedBarring(new OperatorDeterminedBarring(new Integer(-1043623938)));
            subscriptionData.setHPLMNODB(new HPLMNODB(new Integer(822591376)));
            subscriptionData.addRegionalSubscriptionZoneCode(new RegionalSubscriptionZoneCode("octetstring-616580074"));
            subscriptionData.setAccessRestrictionData(new AccessRestrictionData(new Integer(666860974)));
            subscriptionData.setAPNOIReplacement(new APNOIReplacement("utf8string825311572"));
            {
                LCSInfo lCSInfo = new LCSInfo();
                lCSInfo.addGMLCNumber(new GMLCNumber("octetstring-823924349"));
                {
                    LCSPrivacyException lCSPrivacyException = new LCSPrivacyException();
                    lCSPrivacyException.setSSCode(new SSCode("octetstring282887651"));
                    lCSPrivacyException.setSSStatus(new SSStatus("octetstring-988581789"));
                    lCSPrivacyException.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE));
                    {
                        ExternalClient externalClient = new ExternalClient();
                        externalClient.setClientIdentity(new ClientIdentity("octetstring1532027128"));
                        externalClient.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.HOME_COUNTRY));
                        externalClient.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.LOCATION_NOT_ALLOWED));
                        // add more AVP as ANY values to externalClient
                        lCSPrivacyException.addExternalClient(externalClient);
                    }
                    lCSPrivacyException.addPLMNClient(new PLMNClient(PLMNClient.Value.O_AND_M_VPLMN));
                    {
                        ServiceType serviceType = new ServiceType();
                        serviceType.setServiceTypeIdentity(new ServiceTypeIdentity(new Integer(192425388)));
                        serviceType.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.HOME_COUNTRY));
                        serviceType.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.LOCATION_NOT_ALLOWED));
                        // add more AVP as ANY values to serviceType
                        lCSPrivacyException.addServiceType(serviceType);
                    }
                    // add more AVP as ANY values to lCSPrivacyException
                    lCSInfo.addLCSPrivacyException(lCSPrivacyException);
                }
                {
                    MOLR mOLR = new MOLR();
                    mOLR.setSSCode(new SSCode("octetstring-572418867"));
                    mOLR.setSSStatus(new SSStatus("octetstring-4108188"));
                    // add more AVP as ANY values to mOLR
                    lCSInfo.addMOLR(mOLR);
                }
                // add more AVP as ANY values to lCSInfo
                subscriptionData.setLCSInfo(lCSInfo);
            }
            {
                TeleserviceList teleserviceList = new TeleserviceList();
                teleserviceList.addTSCode(new TSCode("octetstring-1324373474"));
                // add more AVP as ANY values to teleserviceList
                subscriptionData.setTeleserviceList(teleserviceList);
            }
            {
                CallBarringInforList callBarringInforList = new CallBarringInforList();
                callBarringInforList.addSSCode(new SSCode("octetstring1456805081"));
                // add more AVP as ANY values to callBarringInforList
                subscriptionData.setCallBarringInforList(callBarringInforList);
            }
            subscriptionData.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string68127767"));
            {
                AMBR aMBR = new AMBR();
                aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-1373356407)));
                aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-513470222)));
                // add more AVP as ANY values to aMBR
                subscriptionData.setAMBR(aMBR);
            }
            {
                APNConfigurationProfile aPNConfigurationProfile = new APNConfigurationProfile();
                aPNConfigurationProfile.setContextIdentifier(new ContextIdentifier(new Integer(1148871068)));
                aPNConfigurationProfile.setAllAPNConfigurationsIncludedIndicator(new AllAPNConfigurationsIncludedIndicator(AllAPNConfigurationsIncludedIndicator.Value.All_APN_CONFIGURATIONS_INCLUDED));
                {
                    APNConfiguration aPNConfiguration = new APNConfiguration();
                    aPNConfiguration.setContextIdentifier(new ContextIdentifier(new Integer(-1762688262)));
                    aPNConfiguration.setPDNType(new PDNType(PDNType.Value.IPv6));
                    aPNConfiguration.setServiceSelection(new ServiceSelection("utf8string-348849166"));
                    aPNConfiguration.addServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "148.29.64.235")));
                    {
                        EPSSubscribedQoSProfile ePSSubscribedQoSProfile = new EPSSubscribedQoSProfile();
                        ePSSubscribedQoSProfile.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.TRAFFIC_CLASS_E));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1440854217)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            ePSSubscribedQoSProfile.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        // add more AVP as ANY values to ePSSubscribedQoSProfile
                        aPNConfiguration.setEPSSubscribedQoSProfile(ePSSubscribedQoSProfile);
                    }
                    aPNConfiguration.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.NOTALLOWED));
                    {
                        MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                        mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "253.4.243.143")));
                        {
                            MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                            mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id912278379.diameter.com"));
                            mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id586454302.diameter.com"));
                            // add more AVP as ANY values to mIPHomeAgentHost
                            mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                        }
                        mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-624919442"));
                        // add more AVP as ANY values to mIP6AgentInfo
                        aPNConfiguration.setMIP6AgentInfo(mIP6AgentInfo);
                    }
                    aPNConfiguration.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring1737539022"));
                    aPNConfiguration.setPDNGWAllocationType(new PDNGWAllocationType(PDNGWAllocationType.Value.STATIC));
                    aPNConfiguration.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string1374771255"));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1137194888)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1655070282)));
                        // add more AVP as ANY values to aMBR
                        aPNConfiguration.setAMBR(aMBR);
                    }
                    {
                        SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                        specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string1734298680"));
                        {
                            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "89.23.136.220")));
                            {
                                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-1889702699.diameter.com"));
                                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id773068848.diameter.com"));
                                // add more AVP as ANY values to mIPHomeAgentHost
                                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                            }
                            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring2135903909"));
                            // add more AVP as ANY values to mIP6AgentInfo
                            specificAPNInfo.setMIP6AgentInfo(mIP6AgentInfo);
                        }
                        specificAPNInfo.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring1006807831"));
                        // add more AVP as ANY values to specificAPNInfo
                        aPNConfiguration.addSpecificAPNInfo(specificAPNInfo);
                    }
                    aPNConfiguration.setAPNOIReplacement(new APNOIReplacement("utf8string1127295112"));
                    aPNConfiguration.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_NOTALLOWED));
                    aPNConfiguration.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_ONLY));
                    // add more AVP as ANY values to aPNConfiguration
                    aPNConfigurationProfile.addAPNConfiguration(aPNConfiguration);
                }
                // add more AVP as ANY values to aPNConfigurationProfile
                subscriptionData.setAPNConfigurationProfile(aPNConfigurationProfile);
            }
            subscriptionData.setRATFrequencySelectionPriorityID(new RATFrequencySelectionPriorityID(new Integer(-1858432919)));
            {
                TraceData traceData = new TraceData();
                traceData.setTraceReference(new TraceReference("octetstring24478816"));
                traceData.setTraceDepth(new TraceDepth(TraceDepth.Value.MediumWithoutVendorSpecificExtension));
                traceData.setTraceNETypeList(new TraceNETypeList("octetstring1495649683"));
                traceData.setTraceEventList(new TraceEventList("octetstring-194167597"));
                traceData.setTraceCollectionEntity(new TraceCollectionEntity(new Address(Address.Family.IPV4, "30.82.24.98")));
                traceData.setTraceInterfaceList(new TraceInterfaceList("octetstring1236243292"));
                traceData.setOMCId(new OMCId("octetstring1505445461"));
                {
                    MDTConfiguration mDTConfiguration = new MDTConfiguration();
                    mDTConfiguration.setJobType(new JobType(JobType.Value.LOGGED_MDT_ONLY));
                    {
                        AreaScope areaScope = new AreaScope();
                        areaScope.addCellGlobalIdentity(new CellGlobalIdentity("octetstring-569503733"));
                        areaScope.addEUTRANCellGlobalIdentity(new EUTRANCellGlobalIdentity("octetstring-1561249582"));
                        areaScope.addRoutingAreaIdentity(new RoutingAreaIdentity("octetstring1756269666"));
                        areaScope.addLocationAreaIdentity(new LocationAreaIdentity("octetstring2118686403"));
                        areaScope.addTrackingAreaIdentity(new TrackingAreaIdentity("octetstring-1761685314"));
                        // add more AVP as ANY values to areaScope
                        mDTConfiguration.setAreaScope(areaScope);
                    }
                    mDTConfiguration.setListOfMeasurements(new ListOfMeasurements(new Integer(-2126746156)));
                    mDTConfiguration.setReportingTrigger(new ReportingTrigger(new Integer(1793902053)));
                    mDTConfiguration.setReportInterval(new ReportInterval(ReportInterval.Value.MSEC_24000));
                    mDTConfiguration.setReportAmount(new ReportAmount(ReportAmount.Value.NUM_REPORTS_2));
                    mDTConfiguration.setEventThresholdRSRP(new EventThresholdRSRP(new Integer(-639526114)));
                    mDTConfiguration.setEventThresholdRSRQ(new EventThresholdRSRQ(new Integer(1743718013)));
                    mDTConfiguration.setLoggingInterval(new LoggingInterval(LoggingInterval.Value.LOG_PERIODICITY_2_56));
                    mDTConfiguration.setLoggingDuration(new LoggingDuration(LoggingDuration.Value.SEC_5400));
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
                    pDPContext.setContextIdentifier(new ContextIdentifier(new Integer(-654116438)));
                    pDPContext.setPDPType(new PDPType("octetstring1066093325"));
                    pDPContext.setQoSSubscribed(new QoSSubscribed("octetstring757032341"));
                    pDPContext.setServiceSelection(new ServiceSelection("utf8string1755024323"));
                    pDPContext.setPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "196.31.237.236")));
                    pDPContext.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.ALLOWED));
                    pDPContext.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string393601635"));
                    pDPContext.setExtPDPType(new ExtPDPType("octetstring-1245140790"));
                    pDPContext.setExtPDPAddress(new ExtPDPAddress(new Address(Address.Family.IPV4, "67.203.124.151")));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1787165108)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-2119996751)));
                        // add more AVP as ANY values to aMBR
                        pDPContext.setAMBR(aMBR);
                    }
                    pDPContext.setSIPTOPermission(new SIPTOPermission(SIPTOPermission.Value.SIPTO_ALLOWED));
                    pDPContext.setLIPAPermission(new LIPAPermission(LIPAPermission.Value.LIPA_ONLY));
                    // add more AVP as ANY values to pDPContext
                    gPRSSubscriptionData.addPDPContext(pDPContext);
                }
                // add more AVP as ANY values to gPRSSubscriptionData
                subscriptionData.setGPRSSubscriptionData(gPRSSubscriptionData);
            }
            {
                CSGSubscriptionData cSGSubscriptionData = new CSGSubscriptionData();
                cSGSubscriptionData.setCSGId(new CSGId(new Integer(552069990)));
                cSGSubscriptionData.setExpirationDate(new ExpirationDate(400621597));
                cSGSubscriptionData.addServiceSelection(new ServiceSelection("utf8string-1536472514"));
                // add more AVP as ANY values to cSGSubscriptionData
                subscriptionData.addCSGSubscriptionData(cSGSubscriptionData);
            }
            subscriptionData.setRoamingRestrictedDueToUnsupportedFeature(new RoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature.Value.Roaming_Restricted_Due_To_Unsupported_Feature));
            subscriptionData.setSubscribedPeriodicRAUTAUTimer(new SubscribedPeriodicRAUTAUTimer(new Integer(-1080400318)));
            subscriptionData.setMPSPriority(new MPSPriority(new Integer(-1451328603)));
            subscriptionData.setVPLMNLIPAAllowed(new VPLMNLIPAAllowed(VPLMNLIPAAllowed.Value.LIPA_NOTALLOWED));
            subscriptionData.setRelayNodeIndicator(new RelayNodeIndicator(RelayNodeIndicator.Value.RELAY_NODE));
            subscriptionData.setMDTUserConsent(new MDTUserConsent(MDTUserConsent.Value.CONSENT_NOT_GIVEN));
            // add more AVP as ANY values to subscriptionData
            insertSubscriberDataRequest.setSubscriptionData(subscriptionData);
        }
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1907134285)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(2084746675)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(143238145)));
            insertSubscriberDataRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        insertSubscriberDataRequest.setIDRFlags(new IDRFlags(new Integer(1420714165)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-2078802639)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1044910025)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(648192478)));
            // add more AVP as ANY values to supportedFeatures
            insertSubscriberDataRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-500648446.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-249354623"));
            // add more AVP as ANY values to proxyInfo
            insertSubscriberDataRequest.addProxyInfo(proxyInfo);
        }
        insertSubscriberDataRequest.addRouteRecord(new diameter.base.RouteRecord("id-1584424944.diameter.com"));
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
        insertSubscriberDataAnswer.setSessionId(new diameter.base.SessionId("utf8string-376054897"));
        insertSubscriberDataAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        insertSubscriberDataAnswer.setOriginHost(new diameter.base.OriginHost("id1568510384.diameter.com"));
        insertSubscriberDataAnswer.setOriginRealm(new diameter.base.OriginRealm("id1795539094.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(551880582)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-178469153)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1147865834)));
            insertSubscriberDataAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1929692946)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1402216582)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(337331410)));
            // add more AVP as ANY values to supportedFeatures
            insertSubscriberDataAnswer.addSupportedFeatures(supportedFeatures);
        }
        insertSubscriberDataAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1002475567)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-1725574481)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-765537929)));
            insertSubscriberDataAnswer.setExperimentalResult(experimentalResult);
        }
        insertSubscriberDataAnswer.setIMSVoiceOverPSSessionsSupported(new IMSVoiceOverPSSessionsSupported(IMSVoiceOverPSSessionsSupported.Value.NOT_SUPPORTED));
        insertSubscriberDataAnswer.setLastUEActivityTime(new LastUEActivityTime(25416518));
        insertSubscriberDataAnswer.setRATType(new RATType(RATType.Value.HRPD));
        insertSubscriberDataAnswer.setIDAFlags(new IDAFlags(new Integer(-726119811)));
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
                sGSNUserState.setUserState(new UserState(UserState.Value.ATTACHED_NOT_REACHABLE_FOR_PAGING));
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
                mMELocationInformation.setEUTRANCellGlobalIdentity(new EUTRANCellGlobalIdentity("octetstring1592882335"));
                mMELocationInformation.setTrackingAreaIdentity(new TrackingAreaIdentity("octetstring1095422790"));
                mMELocationInformation.setGeographicalInformation(new GeographicalInformation("octetstring-212475033"));
                mMELocationInformation.setGeodeticInformation(new GeodeticInformation("octetstring648940387"));
                mMELocationInformation.setCurrentLocationRetrieved(new CurrentLocationRetrieved(CurrentLocationRetrieved.Value.ACTIVE_LOCATION_RETRIEVAL));
                mMELocationInformation.setAgeOfLocationInformation(new AgeOfLocationInformation(new Integer(-2010272093)));
                // add more AVP as ANY values to mMELocationInformation
                ePSLocationInformation.setMMELocationInformation(mMELocationInformation);
            }
            {
                SGSNLocationInformation sGSNLocationInformation = new SGSNLocationInformation();
                sGSNLocationInformation.setCellGlobalIdentity(new CellGlobalIdentity("octetstring-997789118"));
                sGSNLocationInformation.setLocationAreaIdentity(new LocationAreaIdentity("octetstring-1980314129"));
                sGSNLocationInformation.setServiceAreaIdentity(new ServiceAreaIdentity("octetstring573247018"));
                sGSNLocationInformation.setRoutingAreaIdentity(new RoutingAreaIdentity("octetstring157098842"));
                sGSNLocationInformation.setGeographicalInformation(new GeographicalInformation("octetstring1277905549"));
                sGSNLocationInformation.setGeodeticInformation(new GeodeticInformation("octetstring-587010047"));
                sGSNLocationInformation.setCurrentLocationRetrieved(new CurrentLocationRetrieved(CurrentLocationRetrieved.Value.ACTIVE_LOCATION_RETRIEVAL));
                sGSNLocationInformation.setAgeOfLocationInformation(new AgeOfLocationInformation(new Integer(2120859193)));
                // add more AVP as ANY values to sGSNLocationInformation
                ePSLocationInformation.setSGSNLocationInformation(sGSNLocationInformation);
            }
            // add more AVP as ANY values to ePSLocationInformation
            insertSubscriberDataAnswer.setEPSLocationInformation(ePSLocationInformation);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id831478893.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-917255855"));
            // add more AVP as ANY values to proxyInfo
            insertSubscriberDataAnswer.addProxyInfo(proxyInfo);
        }
        insertSubscriberDataAnswer.addRouteRecord(new diameter.base.RouteRecord("id1346515253.diameter.com"));
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
