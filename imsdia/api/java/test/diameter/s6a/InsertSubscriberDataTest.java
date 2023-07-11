package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class InsertSubscriberDataTest {

    public static void testInsertSubscriberDataRequest() throws Exception {
        InsertSubscriberDataRequest insertSubscriberDataRequest = new InsertSubscriberDataRequest(false, false);
        insertSubscriberDataRequest.setSessionId(new diameter.base.SessionId("utf8string2032947896"));
        insertSubscriberDataRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        insertSubscriberDataRequest.setOriginHost(new diameter.base.OriginHost("id-656999988.diameter.com"));
        insertSubscriberDataRequest.setOriginRealm(new diameter.base.OriginRealm("id-948580611.diameter.com"));
        insertSubscriberDataRequest.setDestinationHost(new diameter.base.DestinationHost("id-64944413.diameter.com"));
        insertSubscriberDataRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-24291356.diameter.com"));
        insertSubscriberDataRequest.setUserName(new diameter.base.UserName("utf8string-183907214"));
        {
            SubscriptionData subscriptionData = new SubscriptionData();
            subscriptionData.setSubscriberStatus(new SubscriberStatus(SubscriberStatus.Value.SERVICEGRANTED));
            subscriptionData.setMSISDN(new MSISDN("octetstring-1560863047"));
            subscriptionData.setSTNSR(new STNSR("octetstring-394055157"));
            subscriptionData.setNetworkAccessMode(new NetworkAccessMode(NetworkAccessMode.Value.ONLY_PACKET));
            subscriptionData.setOperatorDeterminedBarring(new OperatorDeterminedBarring(new Integer(2018436933)));
            subscriptionData.setHPLMNODB(new HPLMNODB(new Integer(1020714638)));
            subscriptionData.addRegionalSubscriptionZoneCode(new RegionalSubscriptionZoneCode("octetstring-562541875"));
            subscriptionData.setAccessRestrictionData(new AccessRestrictionData(new Integer(-1438453172)));
            subscriptionData.setAPNOIReplacement(new APNOIReplacement("utf8string-1763817934"));
            {
                LCSInfo lCSInfo = new LCSInfo();
                lCSInfo.addGMLCNumber(new GMLCNumber("octetstring529557725"));
                {
                    LCSPrivacyException lCSPrivacyException = new LCSPrivacyException();
                    lCSPrivacyException.setSSCode(new SSCode("octetstring940042582"));
                    lCSPrivacyException.setSSStatus(new SSStatus("octetstring-1700623376"));
                    lCSPrivacyException.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE));
                    {
                        ExternalClient externalClient = new ExternalClient();
                        externalClient.setClientIdentity(new ClientIdentity("octetstring-1814244756"));
                        externalClient.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.GMLC_LIST));
                        externalClient.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE));
                        // add more AVP as ANY values to externalClient
                        lCSPrivacyException.addExternalClient(externalClient);
                    }
                    lCSPrivacyException.addPLMNClient(new PLMNClient(PLMNClient.Value.TARGET_UE_SUBSCRIBED_SERVICE));
                    {
                        ServiceType serviceType = new ServiceType();
                        serviceType.setServiceTypeIdentity(new ServiceTypeIdentity(new Integer(1582945453)));
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
                    mOLR.setSSCode(new SSCode("octetstring-1333827169"));
                    mOLR.setSSStatus(new SSStatus("octetstring1688453735"));
                    // add more AVP as ANY values to mOLR
                    lCSInfo.addMOLR(mOLR);
                }
                // add more AVP as ANY values to lCSInfo
                subscriptionData.setLCSInfo(lCSInfo);
            }
            {
                TeleserviceList teleserviceList = new TeleserviceList();
                teleserviceList.addTSCode(new TSCode("octetstring1104167606"));
                // add more AVP as ANY values to teleserviceList
                subscriptionData.setTeleserviceList(teleserviceList);
            }
            {
                CallBarringInforList callBarringInforList = new CallBarringInforList();
                callBarringInforList.addSSCode(new SSCode("octetstring-1759180266"));
                // add more AVP as ANY values to callBarringInforList
                subscriptionData.setCallBarringInforList(callBarringInforList);
            }
            subscriptionData.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string2061515969"));
            {
                AMBR aMBR = new AMBR();
                aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-1912102251)));
                aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-725320067)));
                // add more AVP as ANY values to aMBR
                subscriptionData.setAMBR(aMBR);
            }
            {
                APNConfigurationProfile aPNConfigurationProfile = new APNConfigurationProfile();
                aPNConfigurationProfile.setContextIdentifier(new ContextIdentifier(new Integer(502853537)));
                aPNConfigurationProfile.setAllAPNConfigurationsIncludedIndicator(new AllAPNConfigurationsIncludedIndicator(AllAPNConfigurationsIncludedIndicator.Value.MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED));
                {
                    APNConfiguration aPNConfiguration = new APNConfiguration();
                    aPNConfiguration.setContextIdentifier(new ContextIdentifier(new Integer(1652659598)));
                    aPNConfiguration.setPDNType(new PDNType(PDNType.Value.IPv4v6));
                    aPNConfiguration.setServiceSelection(new ServiceSelection("utf8string338905688"));
                    aPNConfiguration.addServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "249.101.128.127")));
                    {
                        EPSSubscribedQoSProfile ePSSubscribedQoSProfile = new EPSSubscribedQoSProfile();
                        ePSSubscribedQoSProfile.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.TRAFFIC_CLASS_I));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(821394066)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            ePSSubscribedQoSProfile.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        // add more AVP as ANY values to ePSSubscribedQoSProfile
                        aPNConfiguration.setEPSSubscribedQoSProfile(ePSSubscribedQoSProfile);
                    }
                    aPNConfiguration.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.NOTALLOWED));
                    {
                        MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                        mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "209.9.184.215")));
                        {
                            MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                            mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id1124317258.diameter.com"));
                            mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1961228990.diameter.com"));
                            // add more AVP as ANY values to mIPHomeAgentHost
                            mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                        }
                        mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring1740981664"));
                        // add more AVP as ANY values to mIP6AgentInfo
                        aPNConfiguration.setMIP6AgentInfo(mIP6AgentInfo);
                    }
                    aPNConfiguration.setPDNGWAllocationType(new PDNGWAllocationType(PDNGWAllocationType.Value.DYNAMIC));
                    aPNConfiguration.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string2046206193"));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(814572830)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(1158148719)));
                        // add more AVP as ANY values to aMBR
                        aPNConfiguration.setAMBR(aMBR);
                    }
                    {
                        SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                        specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string942735601"));
                        {
                            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "47.20.17.135")));
                            {
                                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-440973630.diameter.com"));
                                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id1680723671.diameter.com"));
                                // add more AVP as ANY values to mIPHomeAgentHost
                                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                            }
                            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-231568562"));
                            // add more AVP as ANY values to mIP6AgentInfo
                            specificAPNInfo.setMIP6AgentInfo(mIP6AgentInfo);
                        }
                        // add more AVP as ANY values to specificAPNInfo
                        aPNConfiguration.addSpecificAPNInfo(specificAPNInfo);
                    }
                    // add more AVP as ANY values to aPNConfiguration
                    aPNConfigurationProfile.addAPNConfiguration(aPNConfiguration);
                }
                // add more AVP as ANY values to aPNConfigurationProfile
                subscriptionData.setAPNConfigurationProfile(aPNConfigurationProfile);
            }
            subscriptionData.setRATFrequencySelectionPriorityID(new RATFrequencySelectionPriorityID(new Integer(-908291181)));
            {
                TraceData traceData = new TraceData();
                traceData.setTraceReference(new TraceReference("octetstring917873888"));
                traceData.setTraceDepth(new TraceDepth(TraceDepth.Value.Medium));
                traceData.setTraceNETypeList(new TraceNETypeList("octetstring-1841751913"));
                traceData.setTraceEventList(new TraceEventList("octetstring-1971750571"));
                traceData.setTraceCollectionEntity(new TraceCollectionEntity(new Address(Address.Family.IPV4, "162.227.3.51")));
                traceData.setTraceInterfaceList(new TraceInterfaceList("octetstring-723022176"));
                traceData.setOMCId(new OMCId("octetstring1485507299"));
                // add more AVP as ANY values to traceData
                subscriptionData.setTraceData(traceData);
            }
            {
                GPRSSubscriptionData gPRSSubscriptionData = new GPRSSubscriptionData();
                gPRSSubscriptionData.setCompleteDataListIncludedIndicator(new CompleteDataListIncludedIndicator(CompleteDataListIncludedIndicator.Value.MODIFIED_ADDED_PDP_CONTEXTS_INCLUDED));
                {
                    PDPContext pDPContext = new PDPContext();
                    pDPContext.setContextIdentifier(new ContextIdentifier(new Integer(737516968)));
                    pDPContext.setPDPType(new PDPType("octetstring-238841896"));
                    pDPContext.setQoSSubscribed(new QoSSubscribed("octetstring1047388420"));
                    pDPContext.setServiceSelection(new ServiceSelection("utf8string929982397"));
                    pDPContext.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.NOTALLOWED));
                    pDPContext.setPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "211.3.40.53")));
                    pDPContext.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string674016266"));
                    // add more AVP as ANY values to pDPContext
                    gPRSSubscriptionData.addPDPContext(pDPContext);
                }
                // add more AVP as ANY values to gPRSSubscriptionData
                subscriptionData.setGPRSSubscriptionData(gPRSSubscriptionData);
            }
            {
                CSGSubscriptionData cSGSubscriptionData = new CSGSubscriptionData();
                cSGSubscriptionData.setCSGId(new CSGId(new Integer(-477542514)));
                cSGSubscriptionData.setExpirationDate(new ExpirationDate(-35160397));
                // add more AVP as ANY values to cSGSubscriptionData
                subscriptionData.addCSGSubscriptionData(cSGSubscriptionData);
            }
            subscriptionData.setRoamingRestrictedDueToUnsupportedFeature(new RoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature.Value.Roaming_Restricted_Due_To_Unsupported_Feature));
            // add more AVP as ANY values to subscriptionData
            insertSubscriberDataRequest.setSubscriptionData(subscriptionData);
        }
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1620498555)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(453327896)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1072578747)));
            insertSubscriberDataRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        insertSubscriberDataRequest.setIDRFlags(new IDRFlags(new Integer(-1877209180)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-346629692)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1576970772)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-354451811)));
            // add more AVP as ANY values to supportedFeatures
            insertSubscriberDataRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-2092406088.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1689587741"));
            // add more AVP as ANY values to proxyInfo
            insertSubscriberDataRequest.addProxyInfo(proxyInfo);
        }
        insertSubscriberDataRequest.addRouteRecord(new diameter.base.RouteRecord("id-107448956.diameter.com"));
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
        insertSubscriberDataAnswer.setSessionId(new diameter.base.SessionId("utf8string-410305159"));
        insertSubscriberDataAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        insertSubscriberDataAnswer.setOriginHost(new diameter.base.OriginHost("id-1025225736.diameter.com"));
        insertSubscriberDataAnswer.setOriginRealm(new diameter.base.OriginRealm("id-993593061.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-429478599)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(485918851)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1539035457)));
            insertSubscriberDataAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-970698879)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1424630993)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1746979984)));
            // add more AVP as ANY values to supportedFeatures
            insertSubscriberDataAnswer.addSupportedFeatures(supportedFeatures);
        }
        insertSubscriberDataAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1760909177)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1596089389)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-2128863545)));
            insertSubscriberDataAnswer.setExperimentalResult(experimentalResult);
        }
        insertSubscriberDataAnswer.setIDAFlags(new IDAFlags(new Integer(-1347002710)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1521828336.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1808742552"));
            // add more AVP as ANY values to proxyInfo
            insertSubscriberDataAnswer.addProxyInfo(proxyInfo);
        }
        insertSubscriberDataAnswer.addRouteRecord(new diameter.base.RouteRecord("id1278278134.diameter.com"));
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
