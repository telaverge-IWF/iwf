package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class UpdateLocationTest {

    public static void testUpdateLocationRequest() throws Exception {
        UpdateLocationRequest updateLocationRequest = new UpdateLocationRequest(false, false);
        updateLocationRequest.setSessionId(new diameter.base.SessionId("utf8string1420146641"));
        updateLocationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        updateLocationRequest.setOriginHost(new diameter.base.OriginHost("id448341783.diameter.com"));
        updateLocationRequest.setOriginRealm(new diameter.base.OriginRealm("id-1984055878.diameter.com"));
        updateLocationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1157722093.diameter.com"));
        updateLocationRequest.setUserName(new diameter.base.UserName("utf8string119474622"));
        updateLocationRequest.setULRFlags(new ULRFlags(new Integer(1925014875)));
        updateLocationRequest.setVisitedPLMNId(new VisitedPLMNId("octetstring-1370875675"));
        updateLocationRequest.setRATType(new RATType(RATType.Value.CDMA2000_1X));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1854957704)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1481365015)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-486015235)));
            updateLocationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        updateLocationRequest.setSGSNNumber(new SGSNNumber("octetstring-368927372"));
        updateLocationRequest.setDestinationHost(new diameter.base.DestinationHost("id479170356.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1376052229)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1199088532)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-157058734)));
            // add more AVP as ANY values to supportedFeatures
            updateLocationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string9671177"));
            terminalInformation.setS6a3GPP2MEID(new S6a3GPP2MEID("octetstring-2032099301"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string-1964472060"));
            // add more AVP as ANY values to terminalInformation
            updateLocationRequest.setTerminalInformation(terminalInformation);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1007339387.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1926486502"));
            // add more AVP as ANY values to proxyInfo
            updateLocationRequest.addProxyInfo(proxyInfo);
        }
        updateLocationRequest.addRouteRecord(new diameter.base.RouteRecord("id8391646.diameter.com"));
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
        updateLocationAnswer.setSessionId(new diameter.base.SessionId("utf8string-809528378"));
        updateLocationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        updateLocationAnswer.setOriginHost(new diameter.base.OriginHost("id-1240321014.diameter.com"));
        updateLocationAnswer.setOriginRealm(new diameter.base.OriginRealm("id1073420468.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1013384963)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(911359155)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1153001391)));
            updateLocationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        updateLocationAnswer.setULAFlags(new ULAFlags(new Integer(923656272)));
        updateLocationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(683292267)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-3667645)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1577359355)));
            updateLocationAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(657764256)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(284164422)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(862017305)));
            // add more AVP as ANY values to supportedFeatures
            updateLocationAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            SubscriptionData subscriptionData = new SubscriptionData();
            subscriptionData.setSubscriberStatus(new SubscriberStatus(SubscriberStatus.Value.OPERATORDETERMINEDBARRING));
            subscriptionData.setMSISDN(new MSISDN("octetstring-1245488150"));
            subscriptionData.setSTNSR(new STNSR("octetstring-818386232"));
            subscriptionData.setNetworkAccessMode(new NetworkAccessMode(NetworkAccessMode.Value.ONLY_CIRCUIT));
            subscriptionData.setOperatorDeterminedBarring(new OperatorDeterminedBarring(new Integer(1512465653)));
            subscriptionData.setHPLMNODB(new HPLMNODB(new Integer(1211778609)));
            subscriptionData.addRegionalSubscriptionZoneCode(new RegionalSubscriptionZoneCode("octetstring623567784"));
            subscriptionData.setAccessRestrictionData(new AccessRestrictionData(new Integer(442766036)));
            subscriptionData.setAPNOIReplacement(new APNOIReplacement("utf8string-1141103518"));
            {
                LCSInfo lCSInfo = new LCSInfo();
                lCSInfo.addGMLCNumber(new GMLCNumber("octetstring-1017270051"));
                {
                    LCSPrivacyException lCSPrivacyException = new LCSPrivacyException();
                    lCSPrivacyException.setSSCode(new SSCode("octetstring987175155"));
                    lCSPrivacyException.setSSStatus(new SSStatus("octetstring2082059759"));
                    lCSPrivacyException.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFYANDVERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE));
                    {
                        ExternalClient externalClient = new ExternalClient();
                        externalClient.setClientIdentity(new ClientIdentity("octetstring-658879590"));
                        externalClient.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.GMLC_LIST));
                        externalClient.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFY_LOCATION_ALLOWED));
                        // add more AVP as ANY values to externalClient
                        lCSPrivacyException.addExternalClient(externalClient);
                    }
                    lCSPrivacyException.addPLMNClient(new PLMNClient(PLMNClient.Value.BROADCAST_SERVICE));
                    {
                        ServiceType serviceType = new ServiceType();
                        serviceType.setServiceTypeIdentity(new ServiceTypeIdentity(new Integer(1670125951)));
                        serviceType.setGMLCRestriction(new GMLCRestriction(GMLCRestriction.Value.HOME_COUNTRY));
                        serviceType.setNotificationToUEUser(new NotificationToUEUser(NotificationToUEUser.Value.NOTIFY_LOCATION_ALLOWED));
                        // add more AVP as ANY values to serviceType
                        lCSPrivacyException.addServiceType(serviceType);
                    }
                    // add more AVP as ANY values to lCSPrivacyException
                    lCSInfo.addLCSPrivacyException(lCSPrivacyException);
                }
                {
                    MOLR mOLR = new MOLR();
                    mOLR.setSSCode(new SSCode("octetstring1361412846"));
                    mOLR.setSSStatus(new SSStatus("octetstring-1918167693"));
                    // add more AVP as ANY values to mOLR
                    lCSInfo.addMOLR(mOLR);
                }
                // add more AVP as ANY values to lCSInfo
                subscriptionData.setLCSInfo(lCSInfo);
            }
            {
                TeleserviceList teleserviceList = new TeleserviceList();
                teleserviceList.addTSCode(new TSCode("octetstring-1620047576"));
                // add more AVP as ANY values to teleserviceList
                subscriptionData.setTeleserviceList(teleserviceList);
            }
            {
                CallBarringInforList callBarringInforList = new CallBarringInforList();
                callBarringInforList.addSSCode(new SSCode("octetstring453012431"));
                // add more AVP as ANY values to callBarringInforList
                subscriptionData.setCallBarringInforList(callBarringInforList);
            }
            subscriptionData.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string-143797166"));
            {
                AMBR aMBR = new AMBR();
                aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-780977972)));
                aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-2041469385)));
                // add more AVP as ANY values to aMBR
                subscriptionData.setAMBR(aMBR);
            }
            {
                APNConfigurationProfile aPNConfigurationProfile = new APNConfigurationProfile();
                aPNConfigurationProfile.setContextIdentifier(new ContextIdentifier(new Integer(1591931357)));
                aPNConfigurationProfile.setAllAPNConfigurationsIncludedIndicator(new AllAPNConfigurationsIncludedIndicator(AllAPNConfigurationsIncludedIndicator.Value.All_APN_CONFIGURATIONS_INCLUDED));
                {
                    APNConfiguration aPNConfiguration = new APNConfiguration();
                    aPNConfiguration.setContextIdentifier(new ContextIdentifier(new Integer(-1798059976)));
                    aPNConfiguration.setPDNType(new PDNType(PDNType.Value.IPv4));
                    aPNConfiguration.setServiceSelection(new ServiceSelection("utf8string-1615993378"));
                    aPNConfiguration.addServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "151.224.35.178")));
                    {
                        EPSSubscribedQoSProfile ePSSubscribedQoSProfile = new EPSSubscribedQoSProfile();
                        ePSSubscribedQoSProfile.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.TRAFFIC_CLASS_D));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-497430582)));
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
                        mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "126.132.216.82")));
                        {
                            MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                            mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-128653332.diameter.com"));
                            mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1682004420.diameter.com"));
                            // add more AVP as ANY values to mIPHomeAgentHost
                            mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                        }
                        mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-1168117119"));
                        // add more AVP as ANY values to mIP6AgentInfo
                        aPNConfiguration.setMIP6AgentInfo(mIP6AgentInfo);
                    }
                    aPNConfiguration.setPDNGWAllocationType(new PDNGWAllocationType(PDNGWAllocationType.Value.DYNAMIC));
                    aPNConfiguration.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string2129070220"));
                    {
                        AMBR aMBR = new AMBR();
                        aMBR.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1944566550)));
                        aMBR.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(954119666)));
                        // add more AVP as ANY values to aMBR
                        aPNConfiguration.setAMBR(aMBR);
                    }
                    {
                        SpecificAPNInfo specificAPNInfo = new SpecificAPNInfo();
                        specificAPNInfo.setServiceSelection(new ServiceSelection("utf8string1477979423"));
                        {
                            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
                            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "199.238.123.64")));
                            {
                                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id251739797.diameter.com"));
                                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1102098584.diameter.com"));
                                // add more AVP as ANY values to mIPHomeAgentHost
                                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
                            }
                            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring-959973657"));
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
            subscriptionData.setRATFrequencySelectionPriorityID(new RATFrequencySelectionPriorityID(new Integer(-1845477509)));
            {
                TraceData traceData = new TraceData();
                traceData.setTraceReference(new TraceReference("octetstring-138744986"));
                traceData.setTraceDepth(new TraceDepth(TraceDepth.Value.MediumWithoutVendorSpecificExtension));
                traceData.setTraceNETypeList(new TraceNETypeList("octetstring1285991941"));
                traceData.setTraceEventList(new TraceEventList("octetstring-1793073283"));
                traceData.setTraceCollectionEntity(new TraceCollectionEntity(new Address(Address.Family.IPV4, "70.94.99.1")));
                traceData.setTraceInterfaceList(new TraceInterfaceList("octetstring1686702651"));
                traceData.setOMCId(new OMCId("octetstring1491313646"));
                // add more AVP as ANY values to traceData
                subscriptionData.setTraceData(traceData);
            }
            {
                GPRSSubscriptionData gPRSSubscriptionData = new GPRSSubscriptionData();
                gPRSSubscriptionData.setCompleteDataListIncludedIndicator(new CompleteDataListIncludedIndicator(CompleteDataListIncludedIndicator.Value.MODIFIED_ADDED_PDP_CONTEXTS_INCLUDED));
                {
                    PDPContext pDPContext = new PDPContext();
                    pDPContext.setContextIdentifier(new ContextIdentifier(new Integer(-1118046585)));
                    pDPContext.setPDPType(new PDPType("octetstring16184817"));
                    pDPContext.setQoSSubscribed(new QoSSubscribed("octetstring-1146702928"));
                    pDPContext.setServiceSelection(new ServiceSelection("utf8string-297833899"));
                    pDPContext.setVPLMNDynamicAddressAllowed(new VPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed.Value.NOTALLOWED));
                    pDPContext.setPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "152.76.67.88")));
                    pDPContext.setS6a3GPPChargingCharacteristics(new S6a3GPPChargingCharacteristics("utf8string-1814936051"));
                    // add more AVP as ANY values to pDPContext
                    gPRSSubscriptionData.addPDPContext(pDPContext);
                }
                // add more AVP as ANY values to gPRSSubscriptionData
                subscriptionData.setGPRSSubscriptionData(gPRSSubscriptionData);
            }
            {
                CSGSubscriptionData cSGSubscriptionData = new CSGSubscriptionData();
                cSGSubscriptionData.setCSGId(new CSGId(new Integer(-1486587799)));
                cSGSubscriptionData.setExpirationDate(new ExpirationDate(-152748177));
                // add more AVP as ANY values to cSGSubscriptionData
                subscriptionData.addCSGSubscriptionData(cSGSubscriptionData);
            }
            subscriptionData.setRoamingRestrictedDueToUnsupportedFeature(new RoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature.Value.Roaming_Restricted_Due_To_Unsupported_Feature));
            // add more AVP as ANY values to subscriptionData
            updateLocationAnswer.setSubscriptionData(subscriptionData);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1892996041.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1772527554"));
            // add more AVP as ANY values to proxyInfo
            updateLocationAnswer.addProxyInfo(proxyInfo);
        }
        updateLocationAnswer.addRouteRecord(new diameter.base.RouteRecord("id42959997.diameter.com"));
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
