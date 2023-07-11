package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;
import diameter.*;

public class CreditControlTest {

    public static void testCreditControlRequest() throws Exception {
        CreditControlRequest creditControlRequest = new CreditControlRequest(false, false);
        creditControlRequest.setSessionId(new diameter.base.SessionId("utf8string547788717"));
        creditControlRequest.setOriginHost(new diameter.base.OriginHost("id2050076122.diameter.com"));
        creditControlRequest.setOriginRealm(new diameter.base.OriginRealm("id-1061559040.diameter.com"));
        creditControlRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-705020939.diameter.com"));
        creditControlRequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(816088621)));
        creditControlRequest.setServiceContextId(new ServiceContextId("utf8string-949182458"));
        creditControlRequest.setCCRequestType(new CCRequestType(CCRequestType.Value.INITIAL_REQUEST));
        creditControlRequest.setCCRequestNumber(new CCRequestNumber(new Integer(1457424856)));
        creditControlRequest.setDestinationHost(new diameter.base.DestinationHost("id-1758258184.diameter.com"));
        creditControlRequest.setUserName(new diameter.base.UserName("utf8string2105746108"));
        creditControlRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(-1164183455)));
        creditControlRequest.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(597113267)));
        {
            SubscriptionId subscriptionId = new SubscriptionId();
            subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_NAI));
            subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string-1809515632"));
            creditControlRequest.addSubscriptionId(subscriptionId);
        }
        creditControlRequest.setTerminationCause(new diameter.base.TerminationCause(diameter.base.TerminationCause.Value.DIAMETER_AUTH_EXPIRED));
        creditControlRequest.setRequestedAction(new RequestedAction(RequestedAction.Value.PRICE_ENQUIRY));
        creditControlRequest.setAoCRequestType(new AoCRequestType(AoCRequestType.Value.AoC_TARIFF_ONLY));
        creditControlRequest.setMultipleServicesIndicator(new MultipleServicesIndicator(MultipleServicesIndicator.Value.MULTIPLE_SERVICES_NOT_SUPPORTED));
        {
            MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
            {
                GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(2041915186));
                grantedServiceUnit.setCCTime(new CCTime(new Integer(2078166386)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(-6410974685590175602L)));
                        unitValue.setExponent(new Exponent(new Integer(-1176507650)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(565702865)));
                    grantedServiceUnit.setCCMoney(cCMoney);
                }
                grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(130894409623963751L)));
                grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(4849973948505634055L)));
                grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(5607824996410991584L)));
                grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(6445399307368615991L)));
                // add more AVP as ANY values to grantedServiceUnit
                multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
            }
            {
                RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                requestedServiceUnit.setCCTime(new CCTime(new Integer(-1189817901)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(2633378233155512491L)));
                        unitValue.setExponent(new Exponent(new Integer(1420506972)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(641677616)));
                    requestedServiceUnit.setCCMoney(cCMoney);
                }
                requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-5852327004852334699L)));
                requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-6598852488029497274L)));
                requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(2513635578901833422L)));
                requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(3476975644256922606L)));
                // add more AVP as ANY values to requestedServiceUnit
                multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
            }
            {
                UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.FINAL));
                usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                usedServiceUnit.setCCTime(new CCTime(new Integer(-476420924)));
                usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(9019363215870412811L)));
                usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(6065179208884419662L)));
                usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(3596246469513520522L)));
                usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(7738481283489244848L)));
                usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(1606954208));
                multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
            }
            multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(2108108280)));
            multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(-1877871608)));
            {
                GSUPoolReference gSUPoolReference = new GSUPoolReference();
                gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(194120867)));
                gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(1750000764597469280L)));
                    unitValue.setExponent(new Exponent(new Integer(1503523394)));
                    gSUPoolReference.setUnitValue(unitValue);
                }
                multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
            }
            multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(-375410767)));
            multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(700280062)));
            {
                FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.REDIRECT));
                finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string368410662"));
                {
                    RedirectServer redirectServer = new RedirectServer();
                    redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv4_Address));
                    redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string-1115113977"));
                    finalUnitIndication.setRedirectServer(redirectServer);
                }
                multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
            }
            multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(1758764718)));
            multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(690063791)));
            multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-179252931)));
            multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(677064842)));
            multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(-2105255012)));
            multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.QUOTA_EXHAUSTED));
            {
                Trigger trigger = new Trigger();
                trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_SDU_ERROR_RATIO));
                multipleServicesCreditControl.setTrigger(trigger);
            }
            {
                PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(59717617)));
                pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-236165240"));
                pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
            }
            multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring1179366276"));
            {
                AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-1547982597"));
                {
                    Flows flows = new Flows();
                    flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(2762086)));
                    flows.addFlowNumber(new FlowNumber(new Integer(-1208920064)));
                    aFCorrelationInformation.addFlows(flows);
                }
                multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
            }
            {
                Envelope envelope = new Envelope();
                envelope.setEnvelopeStartTime(new EnvelopeStartTime(-1145765049));
                envelope.setEnvelopeEndTime(new EnvelopeEndTime(-902146060));
                envelope.setCCTotalOctets(new CCTotalOctets(new Long(-6510945079163257461L)));
                envelope.setCCInputOctets(new CCInputOctets(new Long(1288536672457405991L)));
                envelope.setCCOutputOctets(new CCOutputOctets(new Long(-2859515177048082769L)));
                envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(2074246254200609425L)));
                // add more AVP as ANY values to envelope
                multipleServicesCreditControl.addEnvelope(envelope);
            }
            multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES));
            {
                TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(728383119)));
                multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
            }
            {
                ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string1241670102"));
                serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(639711203)));
                multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
            }
            {
                QoSInformation qoSInformation = new QoSInformation();
                qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_8));
                qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(944177271)));
                qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-435824264)));
                qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(2066624839)));
                qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-1412595345)));
                qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-68405977"));
                {
                    AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                    allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(877505094)));
                    allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                    allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                    qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                }
                qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1550865435)));
                qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(8173074)));
                // add more AVP as ANY values to qoSInformation
                multipleServicesCreditControl.setQoSInformation(qoSInformation);
            }
            creditControlRequest.addMultipleServicesCreditControl(multipleServicesCreditControl);
        }
        creditControlRequest.setCCCorrelationId(new CCCorrelationId("octetstring-164499598"));
        {
            UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
            userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.MAC));
            userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring1241604381"));
            creditControlRequest.setUserEquipmentInfo(userEquipmentInfo);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1075059878.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1342898907"));
            // add more AVP as ANY values to proxyInfo
            creditControlRequest.addProxyInfo(proxyInfo);
        }
        creditControlRequest.addRouteRecord(new diameter.base.RouteRecord("id194162290.diameter.com"));
        {
            ServiceInformation serviceInformation = new ServiceInformation();
            {
                SubscriptionId subscriptionId = new SubscriptionId();
                subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_E164));
                subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string2123684855"));
                serviceInformation.addSubscriptionId(subscriptionId);
            }
            {
                AoCInformation aoCInformation = new AoCInformation();
                {
                    AoCCostInformation aoCCostInformation = new AoCCostInformation();
                    {
                        AccumulatedCost accumulatedCost = new AccumulatedCost();
                        accumulatedCost.setValueDigits(new ValueDigits(new Long(6973888542185011658L)));
                        accumulatedCost.setExponent(new Exponent(new Integer(-85821115)));
                        aoCCostInformation.setAccumulatedCost(accumulatedCost);
                    }
                    {
                        IncrementalCost incrementalCost = new IncrementalCost();
                        incrementalCost.setValueDigits(new ValueDigits(new Long(4260052967954945367L)));
                        incrementalCost.setExponent(new Exponent(new Integer(-54487531)));
                        aoCCostInformation.addIncrementalCost(incrementalCost);
                    }
                    aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(-1667827873)));
                    aoCInformation.setAoCCostInformation(aoCCostInformation);
                }
                {
                    TariffInformation tariffInformation = new TariffInformation();
                    {
                        CurrentTariff currentTariff = new CurrentTariff();
                        currentTariff.setCurrencyCode(new CurrencyCode(new Integer(785011576)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(896990612341928549L)));
                            scaleFactor.setExponent(new Exponent(new Integer(1641009078)));
                            currentTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.SETUP_CHARGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-2793325222295516083L)));
                                unitValue.setExponent(new Exponent(new Integer(-1056955370)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(2938192378965803080L)));
                                unitCost.setExponent(new Exponent(new Integer(1732769355)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1789870053)));
                            currentTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setCurrentTariff(currentTariff);
                    }
                    tariffInformation.setTariffTimeChange(new TariffTimeChange(-1525585287));
                    {
                        NextTariff nextTariff = new NextTariff();
                        nextTariff.setCurrencyCode(new CurrencyCode(new Integer(1667066154)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(-475978591811303672L)));
                            scaleFactor.setExponent(new Exponent(new Integer(-178154171)));
                            nextTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.COMMUNICATION_ATTEMPT_CHARGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-7112827911934686909L)));
                                unitValue.setExponent(new Exponent(new Integer(-1051106933)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(-8529400548546385478L)));
                                unitCost.setExponent(new Exponent(new Integer(-1075857675)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(815723477)));
                            nextTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setNextTariff(nextTariff);
                    }
                    aoCInformation.setTariffInformation(tariffInformation);
                }
                {
                    AoCSubscriptionInformation aoCSubscriptionInformation = new AoCSubscriptionInformation();
                    {
                        AoCService aoCService = new AoCService();
                        aoCService.setAoCServiceObligatoryType(new AoCServiceObligatoryType(AoCServiceObligatoryType.Value.NON_BINDING));
                        aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.NONE));
                        aoCSubscriptionInformation.addAoCService(aoCService);
                    }
                    aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.NON_MONETARY));
                    aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(-645488195)));
                    aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                }
                serviceInformation.setAoCInformation(aoCInformation);
            }
            {
                PSInformation pSInformation = new PSInformation();
                pSInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-91602830)));
                pSInformation.setPDNConnectionID(new PDNConnectionID(new Integer(-1868775352)));
                pSInformation.setNodeId(new NodeId("utf8string-1204721599"));
                pSInformation.setRo3GPPPDPType(new Ro3GPPPDPType(new Integer(-1131579572)));
                pSInformation.addPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "108.91.213.231")));
                pSInformation.setPDPAddressPrefixLength(new PDPAddressPrefixLength(new Integer(1672732323)));
                pSInformation.setDynamicAddressFlag(new DynamicAddressFlag(DynamicAddressFlag.Value.Static));
                pSInformation.setDynamicAddressFlagExtension(new DynamicAddressFlagExtension(DynamicAddressFlagExtension.Value.Dynamic));
                {
                    QoSInformation qoSInformation = new QoSInformation();
                    qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_1));
                    qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(507251440)));
                    qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(385679024)));
                    qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-1092384872)));
                    qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-9786935)));
                    qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-1572916364"));
                    {
                        AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                        allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1216521731)));
                        allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                        allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                        qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                    }
                    qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(95969500)));
                    qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1705789131)));
                    // add more AVP as ANY values to qoSInformation
                    pSInformation.setQoSInformation(qoSInformation);
                }
                pSInformation.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "38.52.230.100")));
                pSInformation.setGGSNAddress(new GGSNAddress(new Address(Address.Family.IPV4, "208.21.34.240")));
                pSInformation.setSGWAddress(new SGWAddress(new Address(Address.Family.IPV4, "119.141.253.43")));
                pSInformation.setCGAddress(new CGAddress(new Address(Address.Family.IPV4, "194.161.251.88")));
                pSInformation.setServingNodeType(new ServingNodeType(ServingNodeType.Value.GTPSGW));
                pSInformation.setSGWChange(new SGWChange(SGWChange.Value.ACR_Start_NOT_due_to_SGW_Change));
                pSInformation.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string1641307459"));
                pSInformation.setIMSIUnauthenticatedFlag(new IMSIUnauthenticatedFlag(IMSIUnauthenticatedFlag.Value.Authenticated));
                pSInformation.setRo3GPPGGSNMCCMNC(new Ro3GPPGGSNMCCMNC("utf8string82737247"));
                pSInformation.setRo3GPPNSAPI(new Ro3GPPNSAPI("utf8string-778473247"));
                pSInformation.setCalledStationId(new diameter.nasreq.CalledStationId("utf8string595668320"));
                pSInformation.setRo3GPPSessionStopIndicator(new Ro3GPPSessionStopIndicator("octetstring62285487"));
                pSInformation.setRo3GPPSelectionMode(new Ro3GPPSelectionMode("utf8string1636053304"));
                pSInformation.setRo3GPPChargingCharacteristics(new Ro3GPPChargingCharacteristics("utf8string1091174022"));
                pSInformation.setRo3GPPSGSNMCCMNC(new Ro3GPPSGSNMCCMNC("utf8string-1899753147"));
                pSInformation.setRo3GPPMSTimeZone(new Ro3GPPMSTimeZone("octetstring428249623"));
                pSInformation.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring-151523639"));
                pSInformation.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring1288869149"));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(-1411783278)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.Hybrid_Mode));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.CSG_Member));
                    pSInformation.setUserCSGInformation(userCSGInformation);
                }
                pSInformation.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string-195966636"));
                pSInformation.setRo3GPPRATType(new Ro3GPPRATType("octetstring-56091883"));
                {
                    PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                    pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-413104354)));
                    pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-1409746362"));
                    pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                    pSInformation.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                }
                pSInformation.setPDPContextType(new PDPContextType(PDPContextType.Value.PRIMARY));
                {
                    OfflineCharging offlineCharging = new OfflineCharging();
                    offlineCharging.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(-1588960734)));
                    {
                        TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                        timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                        timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(-1735017105)));
                        offlineCharging.setTimeQuotaMechanism(timeQuotaMechanism);
                    }
                    offlineCharging.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.DO_NOT_REPORT_ENVELOPES));
                    {
                        MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
                        {
                            GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                            grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(-1620816313));
                            grantedServiceUnit.setCCTime(new CCTime(new Integer(-1195067712)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(8699162054480214441L)));
                                    unitValue.setExponent(new Exponent(new Integer(2089819227)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-2085852990)));
                                grantedServiceUnit.setCCMoney(cCMoney);
                            }
                            grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-7544591913337163276L)));
                            grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(8281742057683208006L)));
                            grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(7495365756627114978L)));
                            grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-3209258121224977695L)));
                            // add more AVP as ANY values to grantedServiceUnit
                            multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
                        }
                        {
                            RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                            requestedServiceUnit.setCCTime(new CCTime(new Integer(-82128825)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(2752737555831867008L)));
                                    unitValue.setExponent(new Exponent(new Integer(1013945993)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(928457339)));
                                requestedServiceUnit.setCCMoney(cCMoney);
                            }
                            requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-597570777523002436L)));
                            requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-3674827914808285741L)));
                            requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-6513876623789618416L)));
                            requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-7201212513197198126L)));
                            // add more AVP as ANY values to requestedServiceUnit
                            multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
                        }
                        {
                            UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                            usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.OTHER_QUOTA_TYPE));
                            usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                            usedServiceUnit.setCCTime(new CCTime(new Integer(424063146)));
                            usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(2960025257212158359L)));
                            usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-4365644153379392188L)));
                            usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(3638669038906233024L)));
                            usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-5092892723101667478L)));
                            usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(-1647255353));
                            multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
                        }
                        multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(-1121334659)));
                        multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(709053795)));
                        {
                            GSUPoolReference gSUPoolReference = new GSUPoolReference();
                            gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-694983468)));
                            gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(2770092819003865478L)));
                                unitValue.setExponent(new Exponent(new Integer(-1398539238)));
                                gSUPoolReference.setUnitValue(unitValue);
                            }
                            multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
                        }
                        multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(321592310)));
                        multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(219885337)));
                        {
                            FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                            finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.RESTRICT_ACCESS));
                            finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                            finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string137839698"));
                            {
                                RedirectServer redirectServer = new RedirectServer();
                                redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.SIP_URI));
                                redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string2004153617"));
                                finalUnitIndication.setRedirectServer(redirectServer);
                            }
                            multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
                        }
                        multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(-985589275)));
                        multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(616272638)));
                        multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-391696742)));
                        multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(-587452262)));
                        multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(-1830485662)));
                        multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.QUOTA_EXHAUSTED));
                        {
                            Trigger trigger = new Trigger();
                            trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINLOCATION_MCC));
                            multipleServicesCreditControl.setTrigger(trigger);
                        }
                        {
                            PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                            pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(636671196)));
                            pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-388830500"));
                            pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                            multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                        }
                        multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring1944883463"));
                        {
                            AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                            aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring1793554743"));
                            {
                                Flows flows = new Flows();
                                flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(1002257869)));
                                flows.addFlowNumber(new FlowNumber(new Integer(269291349)));
                                aFCorrelationInformation.addFlows(flows);
                            }
                            multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
                        }
                        {
                            Envelope envelope = new Envelope();
                            envelope.setEnvelopeStartTime(new EnvelopeStartTime(-1626467002));
                            envelope.setEnvelopeEndTime(new EnvelopeEndTime(-1982104441));
                            envelope.setCCTotalOctets(new CCTotalOctets(new Long(1691650410846573289L)));
                            envelope.setCCInputOctets(new CCInputOctets(new Long(6201197923172194472L)));
                            envelope.setCCOutputOctets(new CCOutputOctets(new Long(-9173836620747961326L)));
                            envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(7636685659758111292L)));
                            // add more AVP as ANY values to envelope
                            multipleServicesCreditControl.addEnvelope(envelope);
                        }
                        multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME));
                        {
                            TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                            timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.CONTINUOUS_TIME_PERIOD));
                            timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(-2142145926)));
                            multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
                        }
                        {
                            ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                            serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-2077839189"));
                            serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(-1527708454)));
                            multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
                        }
                        {
                            QoSInformation qoSInformation = new QoSInformation();
                            qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_9));
                            qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-669667083)));
                            qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(1238387307)));
                            qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-1955508040)));
                            qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-624967141)));
                            qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-1069864561"));
                            {
                                AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                                allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(562114944)));
                                allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                                allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                                qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                            }
                            qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-1075002561)));
                            qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1340898374)));
                            // add more AVP as ANY values to qoSInformation
                            multipleServicesCreditControl.setQoSInformation(qoSInformation);
                        }
                        offlineCharging.addMultipleServicesCreditControl(multipleServicesCreditControl);
                    }
                    // add more AVP as ANY values to offlineCharging
                    pSInformation.setOfflineCharging(offlineCharging);
                }
                {
                    TrafficDataVolumes trafficDataVolumes = new TrafficDataVolumes();
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_9));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1081729840)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(203140493)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1472964206)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(1728464775)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring654355196"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1232547739)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(797282758)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(307553580)));
                        // add more AVP as ANY values to qoSInformation
                        trafficDataVolumes.setQoSInformation(qoSInformation);
                    }
                    trafficDataVolumes.setAccountingInputOctets(new AccountingInputOctets(new Long(2873175875222260512L)));
                    trafficDataVolumes.setAccountingInputPackets(new AccountingInputPackets(new Long(-6278409270349230824L)));
                    trafficDataVolumes.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-5126896670764659231L)));
                    trafficDataVolumes.setAccountingOutputPackets(new AccountingOutputPackets(new Long(-4540095318489368388L)));
                    trafficDataVolumes.setChangeCondition(new ChangeCondition(new Integer(-1745658952)));
                    trafficDataVolumes.setChangeTime(new ChangeTime(-168050405));
                    trafficDataVolumes.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring1855039011"));
                    pSInformation.addTrafficDataVolumes(trafficDataVolumes);
                }
                {
                    ServiceDataContainer serviceDataContainer = new ServiceDataContainer();
                    {
                        AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                        aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring2131948770"));
                        {
                            Flows flows = new Flows();
                            flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(955960288)));
                            flows.addFlowNumber(new FlowNumber(new Integer(121062878)));
                            aFCorrelationInformation.addFlows(flows);
                        }
                        serviceDataContainer.setAFCorrelationInformation(aFCorrelationInformation);
                    }
                    serviceDataContainer.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring-1086578342"));
                    serviceDataContainer.setAccountingInputOctets(new AccountingInputOctets(new Long(-8865493528262129100L)));
                    serviceDataContainer.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-3970651200535251758L)));
                    serviceDataContainer.setAccountingInputPackets(new AccountingInputPackets(new Long(8048443382537556286L)));
                    serviceDataContainer.setAccountingOutputPackets(new AccountingOutputPackets(new Long(-7776911257157871227L)));
                    serviceDataContainer.setLocalSequenceNumber(new LocalSequenceNumber(new Integer(936223684)));
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_2));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(2117699611)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1591668159)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1864797433)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-580551868)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-764689971"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(49385098)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-840039344)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-430499907)));
                        // add more AVP as ANY values to qoSInformation
                        serviceDataContainer.setQoSInformation(qoSInformation);
                    }
                    serviceDataContainer.setRatingGroup(new RatingGroup(new Integer(937124091)));
                    serviceDataContainer.setChangeTime(new ChangeTime(418232382));
                    serviceDataContainer.setServiceIdentifier(new ServiceIdentifier(new Integer(-1948996924)));
                    {
                        ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                        serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-1468945288"));
                        serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(973170595)));
                        serviceDataContainer.setServiceSpecificInfo(serviceSpecificInfo);
                    }
                    serviceDataContainer.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "9.75.57.120")));
                    serviceDataContainer.setTimeFirstUsage(new TimeFirstUsage(915900602));
                    serviceDataContainer.setTimeLastUsage(new TimeLastUsage(555428607));
                    serviceDataContainer.setTimeUsage(new TimeUsage(-1481980603));
                    serviceDataContainer.addChangeCondition(new ChangeCondition(new Integer(-1482100311)));
                    serviceDataContainer.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring-1550567812"));
                    serviceDataContainer.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string-1468305370"));
                    pSInformation.addServiceDataContainer(serviceDataContainer);
                }
                {
                    UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
                    userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.MAC));
                    userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring1935095454"));
                    pSInformation.setUserEquipmentInfo(userEquipmentInfo);
                }
                {
                    TerminalInformation terminalInformation = new TerminalInformation();
                    terminalInformation.setIMEI(new IMEI("utf8string286508044"));
                    terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string-949936220"));
                    // add more AVP as ANY values to terminalInformation
                    pSInformation.setTerminalInformation(terminalInformation);
                }
                pSInformation.setStartTime(new StartTime(-851809977));
                pSInformation.setStopTime(new StopTime(1136146069));
                pSInformation.setChangeCondition(new ChangeCondition(new Integer(693741761)));
                pSInformation.setDiagnostics(new Diagnostics(new Integer(1216413872)));
                pSInformation.setLowPriorityIndicator(new LowPriorityIndicator(LowPriorityIndicator.Value.YES));
                serviceInformation.setPSInformation(pSInformation);
            }
            {
                WLANInformation wLANInformation = new WLANInformation();
                wLANInformation.setWLANSessionId(new WLANSessionId(new Integer(-1406315412)));
                wLANInformation.setPDGAddress(new PDGAddress(new Address(Address.Family.IPV4, "203.202.188.191")));
                wLANInformation.setPDGChargingId(new PDGChargingId(new Integer(-2027064641)));
                wLANInformation.setWAGAddress(new WAGAddress(new Address(Address.Family.IPV4, "236.58.53.82")));
                wLANInformation.setWAGPLMNId(new WAGPLMNId("octetstring-16877313"));
                {
                    WLANRadioContainer wLANRadioContainer = new WLANRadioContainer();
                    wLANRadioContainer.setOperatorName(new OperatorName("octetstring-282652861"));
                    wLANRadioContainer.setLocationInformation(new LocationInformation("octetstring671943703"));
                    {
                        LocationType locationType = new LocationType();
                        locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.CANCEL_DEFERRED_LOCATION));
                        locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string-1364887664"));
                        wLANRadioContainer.setLocationType(locationType);
                    }
                    wLANRadioContainer.setWLANTechnology(new WLANTechnology(new Integer(933454969)));
                    wLANInformation.setWLANRadioContainer(wLANRadioContainer);
                }
                wLANInformation.setWLANUELocalIPAddress(new WLANUELocalIPAddress(new Address(Address.Family.IPV4, "34.64.195.97")));
                serviceInformation.setWLANInformation(wLANInformation);
            }
            {
                IMSInformation iMSInformation = new IMSInformation();
                {
                    EventType eventType = new EventType();
                    eventType.setSIPMethod(new SIPMethod("utf8string1374793373"));
                    eventType.setIMSEvent(new IMSEvent("utf8string-1047316958"));
                    eventType.setExpires(new Expires(new Integer(678302087)));
                    iMSInformation.setEventType(eventType);
                }
                iMSInformation.setRoleOfNode(new RoleOfNode(RoleOfNode.Value.TERMINATING_ROLE));
                iMSInformation.setNodeFunctionality(new NodeFunctionality(NodeFunctionality.Value.AS));
                iMSInformation.setUserSessionID(new UserSessionID("utf8string-1445164808"));
                iMSInformation.setOutgoingSessionId(new OutgoingSessionId("utf8string2080529419"));
                iMSInformation.addCallingPartyAddress(new CallingPartyAddress("utf8string2096665598"));
                iMSInformation.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY_4));
                iMSInformation.setCalledPartyAddress(new CalledPartyAddress("utf8string-190686355"));
                iMSInformation.addCalledAssertedIdentity(new CalledAssertedIdentity("utf8string203843184"));
                iMSInformation.setNumberPortabilityRoutingInformation(new NumberPortabilityRoutingInformation("utf8string1985060803"));
                iMSInformation.setCarrierSelectRoutingInformation(new CarrierSelectRoutingInformation("utf8string837551141"));
                iMSInformation.setAlternateChargedPartyAddress(new AlternateChargedPartyAddress("utf8string-614059998"));
                iMSInformation.setRequestedPartyAddress(new RequestedPartyAddress("utf8string-423291457"));
                iMSInformation.addAssociatedURI(new AssociatedURI("utf8string-1910390811"));
                {
                    TimeStamps timeStamps = new TimeStamps();
                    timeStamps.setSIPRequestTimestamp(new SIPRequestTimestamp(1573899678));
                    timeStamps.setSIPResponseTimestamp(new SIPResponseTimestamp(2064931134));
                    timeStamps.setSIPRequestTimestampFraction(new SIPRequestTimestampFraction(new Integer(-1502879204)));
                    timeStamps.setSIPResponseTimestampFraction(new SIPResponseTimestampFraction(new Integer(-686976378)));
                    iMSInformation.setTimeStamps(timeStamps);
                }
                {
                    ApplicationServerInformation applicationServerInformation = new ApplicationServerInformation();
                    applicationServerInformation.setApplicationServer(new ApplicationServer("utf8string-67417552"));
                    applicationServerInformation.addApplicationProvidedCalledPartyAddress(new ApplicationProvidedCalledPartyAddress("utf8string-1250129880"));
                    iMSInformation.addApplicationServerInformation(applicationServerInformation);
                }
                {
                    InterOperatorIdentifier interOperatorIdentifier = new InterOperatorIdentifier();
                    interOperatorIdentifier.setOriginatingIOI(new OriginatingIOI("utf8string1148855611"));
                    interOperatorIdentifier.setTerminatingIOI(new TerminatingIOI("utf8string-1119063225"));
                    iMSInformation.addInterOperatorIdentifier(interOperatorIdentifier);
                }
                iMSInformation.setIMSChargingIdentifier(new IMSChargingIdentifier("utf8string1592182528"));
                iMSInformation.addSDPSessionDescription(new SDPSessionDescription("utf8string-1185081965"));
                {
                    SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                    sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string72506387"));
                    sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string362360042"));
                    sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                    sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                    sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_Realm_Not_used));
                    sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.called_party));
                    sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string-94192288"));
                    sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string314248428"));
                    sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-333817328)));
                    sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring-765555931"));
                    sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Answer));
                    iMSInformation.addSDPMediaComponent(sDPMediaComponent);
                }
                iMSInformation.setServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "75.70.49.162")));
                {
                    ServerCapabilities serverCapabilities = new ServerCapabilities();
                    serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(1394220752)));
                    serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(1014833793)));
                    serverCapabilities.addServerName(new ServerName("utf8string1413713424"));
                    // add more AVP as ANY values to serverCapabilities
                    iMSInformation.setServerCapabilities(serverCapabilities);
                }
                {
                    TrunkGroupID trunkGroupID = new TrunkGroupID();
                    trunkGroupID.setIncomingTrunkGroupID(new IncomingTrunkGroupID("utf8string515132813"));
                    trunkGroupID.setOutgoingTrunkGroupID(new OutgoingTrunkGroupID("utf8string758693521"));
                    iMSInformation.setTrunkGroupID(trunkGroupID);
                }
                iMSInformation.setBearerService(new BearerService("octetstring-1945101998"));
                iMSInformation.setServiceId(new ServiceId("utf8string-1830670963"));
                {
                    ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                    serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string1298153407"));
                    serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1087597126)));
                    iMSInformation.addServiceSpecificInfo(serviceSpecificInfo);
                }
                {
                    MessageBody messageBody = new MessageBody();
                    messageBody.setContentType(new ContentType("utf8string-1585930488"));
                    messageBody.setContentLength(new ContentLength(new Integer(2130201514)));
                    messageBody.setContentDisposition(new ContentDisposition("utf8string-1039796140"));
                    messageBody.setOriginator(new Originator(Originator.Value.Calling_Party));
                    iMSInformation.addMessageBody(messageBody);
                }
                iMSInformation.setCauseCode(new CauseCode(new Integer(-177254368)));
                iMSInformation.setAccessNetworkInformation(new AccessNetworkInformation("octetstring-1376243700"));
                {
                    EarlyMediaDescription earlyMediaDescription = new EarlyMediaDescription();
                    {
                        SDPTimeStamps sDPTimeStamps = new SDPTimeStamps();
                        sDPTimeStamps.setSDPOfferTimestamp(new SDPOfferTimestamp(-1693053625));
                        sDPTimeStamps.setSDPAnswerTimestamp(new SDPAnswerTimestamp(-287557028));
                        earlyMediaDescription.setSDPTimeStamps(sDPTimeStamps);
                    }
                    {
                        SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                        sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string-1060827396"));
                        sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string225644437"));
                        sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                        sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                        sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_Realm_Not_used));
                        sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.unknown));
                        sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string227952602"));
                        sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string674628260"));
                        sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(1532922345)));
                        sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring-1296307304"));
                        sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Offer));
                        earlyMediaDescription.addSDPMediaComponent(sDPMediaComponent);
                    }
                    earlyMediaDescription.addSDPSessionDescription(new SDPSessionDescription("utf8string-715952565"));
                    iMSInformation.addEarlyMediaDescription(earlyMediaDescription);
                }
                iMSInformation.setIMSCommunicationServiceIdentifier(new IMSCommunicationServiceIdentifier("utf8string-1772040449"));
                iMSInformation.setOnlineChargingFlag(new OnlineChargingFlag(OnlineChargingFlag.Value.ECF_address_provided));
                {
                    RealTimeTariffInformation realTimeTariffInformation = new RealTimeTariffInformation();
                    {
                        TariffInformation tariffInformation = new TariffInformation();
                        {
                            CurrentTariff currentTariff = new CurrentTariff();
                            currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-1403591762)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(-3048537058813652469L)));
                                scaleFactor.setExponent(new Exponent(new Integer(627693595)));
                                currentTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.COMMUNICATION_ATTEMPT_CHARGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(4923767190838889275L)));
                                    unitValue.setExponent(new Exponent(new Integer(1247398412)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(-8118178550738061609L)));
                                    unitCost.setExponent(new Exponent(new Integer(-2072812370)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(631575560)));
                                currentTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setCurrentTariff(currentTariff);
                        }
                        tariffInformation.setTariffTimeChange(new TariffTimeChange(-1749558213));
                        {
                            NextTariff nextTariff = new NextTariff();
                            nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-1561653674)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(-59952964281374765L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-1560050039)));
                                nextTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.SETUP_CHARGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(405015669204339626L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1710203792)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(725864828275100660L)));
                                    unitCost.setExponent(new Exponent(new Integer(-1172970735)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(524555577)));
                                nextTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setNextTariff(nextTariff);
                        }
                        realTimeTariffInformation.setTariffInformation(tariffInformation);
                    }
                    realTimeTariffInformation.setTariffXML(new TariffXML("utf8string-590437650"));
                    iMSInformation.setRealTimeTariffInformation(realTimeTariffInformation);
                }
                iMSInformation.setAccountExpiration(new AccountExpiration(290822448));
                iMSInformation.setInitialIMSChargingIdentifier(new InitialIMSChargingIdentifier("utf8string-587117759"));
                serviceInformation.setIMSInformation(iMSInformation);
            }
            {
                MMSInformation mMSInformation = new MMSInformation();
                {
                    OriginatorAddress originatorAddress = new OriginatorAddress();
                    originatorAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv4_Address));
                    originatorAddress.setAddressData(new AddressData("utf8string-723279571"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-1203038732"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-265503013"));
                        originatorAddress.setAddressDomain(addressDomain);
                    }
                    mMSInformation.setOriginatorAddress(originatorAddress);
                }
                {
                    RecipientAddress recipientAddress = new RecipientAddress();
                    recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.Other));
                    recipientAddress.setAddressData(new AddressData("utf8string2101050347"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-510486777"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string1254585815"));
                        recipientAddress.setAddressDomain(addressDomain);
                    }
                    recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.TO));
                    mMSInformation.addRecipientAddress(recipientAddress);
                }
                mMSInformation.setSubmissionTime(new SubmissionTime(-435327113));
                {
                    MMContentType mMContentType = new MMContentType();
                    mMContentType.setTypeNumber(new TypeNumber(new Integer(-1402669971)));
                    mMContentType.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string-1655064815"));
                    mMContentType.setContentSize(new ContentSize(new Integer(-1767852109)));
                    {
                        AdditionalContentInformation additionalContentInformation = new AdditionalContentInformation();
                        additionalContentInformation.setTypeNumber(new TypeNumber(new Integer(-2134600551)));
                        additionalContentInformation.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string-1218921548"));
                        additionalContentInformation.setContentSize(new ContentSize(new Integer(539360775)));
                        mMContentType.addAdditionalContentInformation(additionalContentInformation);
                    }
                    mMSInformation.setMMContentType(mMContentType);
                }
                mMSInformation.setPriority(new Priority(Priority.Value.Low));
                mMSInformation.setMessageID(new MessageID("utf8string-355334666"));
                mMSInformation.setMessageType(new MessageType(MessageType.Value.m_mbox_store_conf));
                mMSInformation.setMessageSize(new MessageSize(new Integer(1313880289)));
                {
                    MessageClass messageClass = new MessageClass();
                    messageClass.setClassIdentifier(new ClassIdentifier(ClassIdentifier.Value.Auto));
                    messageClass.setTokenText(new TokenText("utf8string1253144504"));
                    mMSInformation.setMessageClass(messageClass);
                }
                mMSInformation.setDeliveryReportRequested(new DeliveryReportRequested(DeliveryReportRequested.Value.No));
                mMSInformation.setReadReplyReportRequested(new ReadReplyReportRequested(ReadReplyReportRequested.Value.No));
                mMSInformation.setMMBoxStorageRequested(new MMBoxStorageRequested(MMBoxStorageRequested.Value.Yes));
                mMSInformation.setApplicID(new ApplicID("utf8string2108499310"));
                mMSInformation.setReplyApplicID(new ReplyApplicID("utf8string2121718677"));
                mMSInformation.setAuxApplicInfo(new AuxApplicInfo("utf8string1701182970"));
                mMSInformation.setContentClass(new ContentClass(ContentClass.Value.image_basic));
                mMSInformation.setDRMContent(new DRMContent(DRMContent.Value.Yes));
                mMSInformation.setAdaptations(new Adaptations(Adaptations.Value.No));
                mMSInformation.setVASPId(new VASPId("utf8string449196918"));
                mMSInformation.setVASId(new VASId("utf8string787798662"));
                serviceInformation.setMMSInformation(mMSInformation);
            }
            {
                LCSInformation lCSInformation = new LCSInformation();
                {
                    LCSClientID lCSClientID = new LCSClientID();
                    lCSClientID.setLCSClientType(new LCSClientType(LCSClientType.Value.EMERGENCY_SERVICES));
                    lCSClientID.setLCSClientExternalID(new LCSClientExternalID("utf8string1768054619"));
                    lCSClientID.setLCSClientDialedByMS(new LCSClientDialedByMS("utf8string-1485399789"));
                    {
                        LCSClientName lCSClientName = new LCSClientName();
                        lCSClientName.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string1856963631"));
                        lCSClientName.setLCSNameString(new LCSNameString("utf8string1945049993"));
                        lCSClientName.setLCSFormatIndicator(new LCSFormatIndicator(LCSFormatIndicator.Value.LOCATION_NAME));
                        lCSClientID.setLCSClientName(lCSClientName);
                    }
                    lCSClientID.setLCSAPN(new LCSAPN("utf8string-1896159937"));
                    {
                        LCSRequestorID lCSRequestorID = new LCSRequestorID();
                        lCSRequestorID.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string-1298611628"));
                        lCSRequestorID.setLCSRequestorIDString(new LCSRequestorIDString("utf8string-64629557"));
                        lCSClientID.setLCSRequestorID(lCSRequestorID);
                    }
                    lCSInformation.setLCSClientID(lCSClientID);
                }
                {
                    LocationType locationType = new LocationType();
                    locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.CANCEL_DEFERRED_LOCATION));
                    locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string-2013523355"));
                    lCSInformation.setLocationType(locationType);
                }
                lCSInformation.setLocationEstimate(new LocationEstimate("utf8string472114114"));
                lCSInformation.setPositioningData(new PositioningData("utf8string-457066893"));
                lCSInformation.setRo3GPPIMSI(new Ro3GPPIMSI("utf8string-2141691456"));
                lCSInformation.setMSISDN(new MSISDN("octetstring279164598"));
                serviceInformation.setLCSInformation(lCSInformation);
            }
            {
                PoCInformation poCInformation = new PoCInformation();
                poCInformation.setPoCServerRole(new PoCServerRole(PoCServerRole.Value.Participating_PoC_Server));
                poCInformation.setPoCSessionType(new PoCSessionType(PoCSessionType.Value.pre_arranged_PoC_group_session));
                {
                    PoCUserRole poCUserRole = new PoCUserRole();
                    poCUserRole.setPoCUserRoleIds(new PoCUserRoleIds("utf8string61890907"));
                    poCUserRole.setPoCUserRoleinfoUnits(new PoCUserRoleinfoUnits(PoCUserRoleinfoUnits.Value.Dispatcher));
                    poCInformation.setPoCUserRole(poCUserRole);
                }
                poCInformation.setPoCSessionInitiationType(new PoCSessionInitiationType(PoCSessionInitiationType.Value.On_demand));
                poCInformation.setPoCEventType(new PoCEventType(PoCEventType.Value.Instant_Ppersonal_Aalert_event));
                poCInformation.setNumberOfParticipants(new NumberOfParticipants(new Integer(1724009914)));
                poCInformation.addParticipantsInvolved(new ParticipantsInvolved("utf8string-1404459829"));
                {
                    ParticipantGroup participantGroup = new ParticipantGroup();
                    participantGroup.setCalledPartyAddress(new CalledPartyAddress("utf8string-1550569959"));
                    participantGroup.setParticipantAccessPriority(new ParticipantAccessPriority(ParticipantAccessPriority.Value.Normal_priority));
                    participantGroup.setUserParticipatingType(new UserParticipatingType(UserParticipatingType.Value.UE_PoC_Box));
                    poCInformation.addParticipantGroup(participantGroup);
                }
                {
                    TalkBurstExchange talkBurstExchange = new TalkBurstExchange();
                    talkBurstExchange.setPoCChangeTime(new PoCChangeTime(-616749271));
                    talkBurstExchange.setNumberOfTalkBursts(new NumberOfTalkBursts(new Integer(1173164769)));
                    talkBurstExchange.setTalkBurstVolume(new TalkBurstVolume(new Integer(-788832667)));
                    talkBurstExchange.setTalkBurstTime(new TalkBurstTime(new Integer(1866608355)));
                    talkBurstExchange.setNumberOfReceivedTalkBursts(new NumberOfReceivedTalkBursts(new Integer(673017648)));
                    talkBurstExchange.setReceivedTalkBurstVolume(new ReceivedTalkBurstVolume(new Integer(-2104637275)));
                    talkBurstExchange.setReceivedTalkBurstTime(new ReceivedTalkBurstTime(new Integer(-1108079749)));
                    talkBurstExchange.setNumberOfParticipants(new NumberOfParticipants(new Integer(-1578239285)));
                    talkBurstExchange.setPoCChangeCondition(new PoCChangeCondition(PoCChangeCondition.Value.tariffTime));
                    poCInformation.addTalkBurstExchange(talkBurstExchange);
                }
                poCInformation.setPoCControllingAddress(new PoCControllingAddress("utf8string1993164055"));
                poCInformation.setPoCGroupName(new PoCGroupName("utf8string-753074947"));
                poCInformation.setPoCSessionId(new PoCSessionId("utf8string-1616229349"));
                poCInformation.setChargedParty(new ChargedParty("utf8string1295756510"));
                serviceInformation.setPoCInformation(poCInformation);
            }
            {
                MBMSInformation mBMSInformation = new MBMSInformation();
                mBMSInformation.setTMGI(new TMGI("octetstring1512995058"));
                mBMSInformation.setMBMSServiceType(new MBMSServiceType(MBMSServiceType.Value.MULTICAST));
                mBMSInformation.setMBMSUserServiceType(new MBMSUserServiceType(MBMSUserServiceType.Value.STREAMING));
                mBMSInformation.setFileRepairSupported(new FileRepairSupported(FileRepairSupported.Value.SUPPORTED));
                mBMSInformation.setRequiredMBMSBearerCapabilities(new RequiredMBMSBearerCapabilities("utf8string-1220103891"));
                mBMSInformation.setMBMS2G3GIndicator(new MBMS2G3GIndicator(MBMS2G3GIndicator.Value.ONLY_3G));
                mBMSInformation.setRAI(new RAI("utf8string1959578773"));
                mBMSInformation.addMBMSServiceArea(new MBMSServiceArea("octetstring414118030"));
                mBMSInformation.setMBMSSessionIdentity(new MBMSSessionIdentity("octetstring-1844684947"));
                mBMSInformation.setCNIPMulticastDistribution(new CNIPMulticastDistribution(CNIPMulticastDistribution.Value.IP_MULTICAST));
                mBMSInformation.setMBMSGWAddress(new MBMSGWAddress(new Address(Address.Family.IPV4, "39.49.186.33")));
                serviceInformation.setMBMSInformation(mBMSInformation);
            }
            {
                SMSInformation sMSInformation = new SMSInformation();
                sMSInformation.setSMSNode(new SMSNode(SMSNode.Value.IP_SM_GW));
                sMSInformation.setClientAddress(new ClientAddress(new Address(Address.Family.IPV4, "65.117.243.13")));
                sMSInformation.setOriginatorSCCPAddress(new OriginatorSCCPAddress(new Address(Address.Family.IPV4, "101.137.150.195")));
                sMSInformation.setSMSCAddress(new SMSCAddress(new Address(Address.Family.IPV4, "185.225.21.45")));
                sMSInformation.setDataCodingScheme(new DataCodingScheme(new Integer(1657403857)));
                sMSInformation.setSMDischargeTime(new SMDischargeTime(1154315801));
                sMSInformation.setSMMessageType(new SMMessageType(SMMessageType.Value.SM_Service_Request));
                {
                    OriginatorInterface originatorInterface = new OriginatorInterface();
                    originatorInterface.setInterfaceId(new InterfaceId("utf8string791344898"));
                    originatorInterface.setInterfaceText(new InterfaceText("utf8string-543090179"));
                    originatorInterface.setInterfacePort(new InterfacePort("utf8string838759799"));
                    originatorInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.Unknown));
                    sMSInformation.setOriginatorInterface(originatorInterface);
                }
                sMSInformation.setSMProtocolID(new SMProtocolID("octetstring-333926638"));
                sMSInformation.setReplyPathRequested(new ReplyPathRequested(ReplyPathRequested.Value.Reply_path_Set));
                sMSInformation.setSMStatus(new SMStatus("octetstring1687456284"));
                sMSInformation.setSMUserDataHeader(new SMUserDataHeader("octetstring791932951"));
                sMSInformation.setNumberOfMessagesSent(new NumberOfMessagesSent(new Integer(-1962273126)));
                {
                    RecipientInfo recipientInfo = new RecipientInfo();
                    {
                        DestinationInterface destinationInterface = new DestinationInterface();
                        destinationInterface.setInterfaceId(new InterfaceId("utf8string833640921"));
                        destinationInterface.setInterfaceText(new InterfaceText("utf8string800080246"));
                        destinationInterface.setInterfacePort(new InterfacePort("utf8string466051778"));
                        destinationInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.APPLICATION_ORIGINATING));
                        recipientInfo.setDestinationInterface(destinationInterface);
                    }
                    {
                        RecipientAddress recipientAddress = new RecipientAddress();
                        recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IMSI));
                        recipientAddress.setAddressData(new AddressData("utf8string-955560968"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string631617380"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string139257314"));
                            recipientAddress.setAddressDomain(addressDomain);
                        }
                        recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.CC));
                        recipientInfo.addRecipientAddress(recipientAddress);
                    }
                    {
                        RecipientReceivedAddress recipientReceivedAddress = new RecipientReceivedAddress();
                        recipientReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv6_Address));
                        recipientReceivedAddress.setAddressData(new AddressData("utf8string1831146578"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string1129868980"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-2138994826"));
                            recipientReceivedAddress.setAddressDomain(addressDomain);
                        }
                        recipientInfo.addRecipientReceivedAddress(recipientReceivedAddress);
                    }
                    recipientInfo.setRecipientSCCPAddress(new RecipientSCCPAddress(new Address(Address.Family.IPV4, "73.202.135.88")));
                    recipientInfo.setSMProtocolID(new SMProtocolID("octetstring-304477471"));
                    sMSInformation.addRecipientInfo(recipientInfo);
                }
                {
                    OriginatorReceivedAddress originatorReceivedAddress = new OriginatorReceivedAddress();
                    originatorReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.MSISDN));
                    originatorReceivedAddress.setAddressData(new AddressData("utf8string-1342245016"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string1430820326"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-160483235"));
                        originatorReceivedAddress.setAddressDomain(addressDomain);
                    }
                    sMSInformation.setOriginatorReceivedAddress(originatorReceivedAddress);
                }
                sMSInformation.setSMServiceType(new SMServiceType(SMServiceType.Value.VAS4SMS_Forwarding_Multiple_Subscriptions));
                serviceInformation.setSMSInformation(sMSInformation);
            }
            {
                MMTelInformation mMTelInformation = new MMTelInformation();
                {
                    SupplementaryService supplementaryService = new SupplementaryService();
                    supplementaryService.setServiceType(new ServiceType(new Integer(713738247)));
                    supplementaryService.setServiceMode(new ServiceMode(new Integer(-644170267)));
                    supplementaryService.setNumberOfDiversions(new NumberOfDiversions(new Integer(-1687141493)));
                    supplementaryService.setAssociatedPartyAddress(new AssociatedPartyAddress("utf8string331427996"));
                    supplementaryService.setServiceId(new ServiceId("utf8string1632581839"));
                    supplementaryService.setChangeTime(new ChangeTime(-594441867));
                    supplementaryService.setNumberOfParticipants(new NumberOfParticipants(new Integer(564202678)));
                    supplementaryService.setParticipantActionType(new ParticipantActionType(ParticipantActionType.Value.INVITE_INTO_CONF));
                    supplementaryService.setCUGInformation(new CUGInformation("octetstring-137777609"));
                    {
                        AoCInformation aoCInformation = new AoCInformation();
                        {
                            AoCCostInformation aoCCostInformation = new AoCCostInformation();
                            {
                                AccumulatedCost accumulatedCost = new AccumulatedCost();
                                accumulatedCost.setValueDigits(new ValueDigits(new Long(6894277507360223768L)));
                                accumulatedCost.setExponent(new Exponent(new Integer(-2042609102)));
                                aoCCostInformation.setAccumulatedCost(accumulatedCost);
                            }
                            {
                                IncrementalCost incrementalCost = new IncrementalCost();
                                incrementalCost.setValueDigits(new ValueDigits(new Long(3036706352197628814L)));
                                incrementalCost.setExponent(new Exponent(new Integer(-1868269684)));
                                aoCCostInformation.addIncrementalCost(incrementalCost);
                            }
                            aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(319881232)));
                            aoCInformation.setAoCCostInformation(aoCCostInformation);
                        }
                        {
                            TariffInformation tariffInformation = new TariffInformation();
                            {
                                CurrentTariff currentTariff = new CurrentTariff();
                                currentTariff.setCurrencyCode(new CurrencyCode(new Integer(794494910)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(2452757976602129799L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(-42946013)));
                                    currentTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.INPUT_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.ADD_ON_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(-289563770893371637L)));
                                        unitValue.setExponent(new Exponent(new Integer(1893663895)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(-7802373844270018482L)));
                                        unitCost.setExponent(new Exponent(new Integer(-1622846505)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1854714468)));
                                    currentTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setCurrentTariff(currentTariff);
                            }
                            tariffInformation.setTariffTimeChange(new TariffTimeChange(-1792809941));
                            {
                                NextTariff nextTariff = new NextTariff();
                                nextTariff.setCurrencyCode(new CurrencyCode(new Integer(1138876683)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(-8252418980702634861L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(-1922929188)));
                                    nextTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.MONEY));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.SETUP_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(-3827718662416189924L)));
                                        unitValue.setExponent(new Exponent(new Integer(959580965)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(5208335835994543573L)));
                                        unitCost.setExponent(new Exponent(new Integer(-1292220444)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-847301126)));
                                    nextTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setNextTariff(nextTariff);
                            }
                            aoCInformation.setTariffInformation(tariffInformation);
                        }
                        {
                            AoCSubscriptionInformation aoCSubscriptionInformation = new AoCSubscriptionInformation();
                            {
                                AoCService aoCService = new AoCService();
                                aoCService.setAoCServiceObligatoryType(new AoCServiceObligatoryType(AoCServiceObligatoryType.Value.BINDING));
                                aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.AOC_E));
                                aoCSubscriptionInformation.addAoCService(aoCService);
                            }
                            aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.MONETARY));
                            aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(1107769246)));
                            aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                        }
                        supplementaryService.setAoCInformation(aoCInformation);
                    }
                    mMTelInformation.addSupplementaryService(supplementaryService);
                }
                mMTelInformation.setSubscriberRole(new SubscriberRole(SubscriberRole.Value.TERMINATING));
                serviceInformation.setMMTelInformation(mMTelInformation);
            }
            {
                ServiceGenericInformation serviceGenericInformation = new ServiceGenericInformation();
                serviceGenericInformation.setApplicationServerID(new ApplicationServerID("utf8string1834089300"));
                serviceGenericInformation.setApplicationServiceType(new ApplicationServiceType("utf8string-1129727588"));
                serviceGenericInformation.setApplicationSessionID(new ApplicationSessionID("utf8string-1766468212"));
                serviceGenericInformation.setDeliveryStatus(new DeliveryStatus("utf8string1061314031"));
                serviceInformation.setServiceGenericInformation(serviceGenericInformation);
            }
            {
                IMInformation iMInformation = new IMInformation();
                iMInformation.setTotalNumberOfMessagesSent(new TotalNumberOfMessagesSent(new Integer(-1338457761)));
                iMInformation.setTotalNumberOfMessagesExploded(new TotalNumberOfMessagesExploded(new Integer(-1892945353)));
                iMInformation.setNumberOfMessagesSuccessfullySent(new NumberOfMessagesSuccessfullySent(new Integer(-1030825296)));
                iMInformation.setNumberOfMessagesSuccessfullyExploded(new NumberOfMessagesSuccessfullyExploded(new Integer(-529211042)));
                serviceInformation.setIMInformation(iMInformation);
            }
            {
                DCDInformation dCDInformation = new DCDInformation();
                dCDInformation.setContentID(new ContentID("utf8string-889511076"));
                dCDInformation.setContentproviderID(new ContentproviderID("utf8string502993655"));
                serviceInformation.setDCDInformation(dCDInformation);
            }
            {
                diameter.transatel_custom_avps.CSInformation cSInformation = new diameter.transatel_custom_avps.CSInformation();
                cSInformation.setCallType(new diameter.transatel_custom_avps.CallType(diameter.transatel_custom_avps.CallType.Value.MO_VOICE));
                {
                    diameter.transatel_custom_avps.CAPInformation cAPInformation = new diameter.transatel_custom_avps.CAPInformation();
                    cAPInformation.setCAPCellIDAreaIDLAI(new diameter.transatel_custom_avps.CAPCellIDAreaIDLAI("octetstring1590077966"));
                    cAPInformation.setCAPIsFollowingOn(new diameter.transatel_custom_avps.CAPIsFollowingOn(diameter.transatel_custom_avps.CAPIsFollowingOn.Value.False));
                    cAPInformation.setCAPControlMode(new diameter.transatel_custom_avps.CAPControlMode(diameter.transatel_custom_avps.CAPControlMode.Value.NO_CONTROL));
                    cAPInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(363755850)));
                    cAPInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(-599131709)));
                    cAPInformation.setCAPServiceKey(new diameter.transatel_custom_avps.CAPServiceKey(new Integer(162571789)));
                    cAPInformation.setCAPDialedDigits(new diameter.transatel_custom_avps.CAPDialedDigits("utf8string846086956"));
                    cAPInformation.setCAPCalledTON(new diameter.transatel_custom_avps.CAPCalledTON(new Integer(-1384888576)));
                    cAPInformation.setCAPCLI(new diameter.transatel_custom_avps.CAPCLI("utf8string762902613"));
                    cAPInformation.setCAPCallingCategory(new diameter.transatel_custom_avps.CAPCallingCategory(new Integer(-277240060)));
                    cAPInformation.setCAPLocationNumber(new diameter.transatel_custom_avps.CAPLocationNumber("utf8string-1300444275"));
                    cAPInformation.setCAPRedirectingNumber(new diameter.transatel_custom_avps.CAPRedirectingNumber("utf8string-328627313"));
                    cAPInformation.setCAPRedirectingIndicator(new diameter.transatel_custom_avps.CAPRedirectingIndicator(new Integer(833181402)));
                    cAPInformation.setCAPOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPOriginalRedirectingReason(new Integer(1275864027)));
                    cAPInformation.setCAPRedirectionCounter(new diameter.transatel_custom_avps.CAPRedirectionCounter(new Integer(183237941)));
                    cAPInformation.setCAPRedirectingReason(new diameter.transatel_custom_avps.CAPRedirectingReason(new Integer(2132102598)));
                    cAPInformation.setCAPIMSI(new diameter.transatel_custom_avps.CAPIMSI("utf8string1651802371"));
                    cAPInformation.setCAPVLRNumber(new diameter.transatel_custom_avps.CAPVLRNumber("utf8string-1414959779"));
                    cAPInformation.setCAPCallReference(new diameter.transatel_custom_avps.CAPCallReference("octetstring1796439095"));
                    cAPInformation.setCAPMSCAddress(new diameter.transatel_custom_avps.CAPMSCAddress("utf8string506539861"));
                    cAPInformation.setCAPCalledNPI(new diameter.transatel_custom_avps.CAPCalledNPI(new Integer(-47775546)));
                    cAPInformation.setCAPCLINPI(new diameter.transatel_custom_avps.CAPCLINPI(new Integer(1939422220)));
                    cAPInformation.setCAPCLINOA(new diameter.transatel_custom_avps.CAPCLINOA(new Integer(868805715)));
                    cAPInformation.setCAPCLIR(new diameter.transatel_custom_avps.CAPCLIR(new Integer(454848452)));
                    cAPInformation.setCAPVersion(new diameter.transatel_custom_avps.CAPVersion(new Integer(1968175165)));
                    cAPInformation.setCAPBearerCapabilityTransfer(new diameter.transatel_custom_avps.CAPBearerCapabilityTransfer("utf8string-1493995980"));
                    cAPInformation.setCAPBearerCapabilityTransferRate(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferRate("utf8string-1803823241"));
                    cAPInformation.setCAPGMSCAddress(new diameter.transatel_custom_avps.CAPGMSCAddress("utf8string1334291111"));
                    cAPInformation.setCAPExtBasicServiceCode(new diameter.transatel_custom_avps.CAPExtBasicServiceCode("utf8string1035195853"));
                    cAPInformation.setCAPBearerCapability(new diameter.transatel_custom_avps.CAPBearerCapability("octetstring-855698627"));
                    cAPInformation.setCAPSMSCAddress(new diameter.transatel_custom_avps.CAPSMSCAddress("utf8string1330313352"));
                    cAPInformation.setCAPSGSNAddress(new diameter.transatel_custom_avps.CAPSGSNAddress("utf8string-1604205296"));
                    cAPInformation.setCAPIMEI(new diameter.transatel_custom_avps.CAPIMEI("utf8string-478959990"));
                    cAPInformation.setCAPSMStatusReportRequest(new diameter.transatel_custom_avps.CAPSMStatusReportRequest("utf8string-2128193471"));
                    cAPInformation.setCAPSMUserDataHeaderIndicator(new diameter.transatel_custom_avps.CAPSMUserDataHeaderIndicator("utf8string-1696797087"));
                    cAPInformation.setCAPSMReplyPath(new diameter.transatel_custom_avps.CAPSMReplyPath("utf8string1470217796"));
                    cAPInformation.setCAPSMVPFormat(new diameter.transatel_custom_avps.CAPSMVPFormat("utf8string409774810"));
                    cAPInformation.setCAPSMMessageTypeIndicator(new diameter.transatel_custom_avps.CAPSMMessageTypeIndicator("utf8string-60544546"));
                    cAPInformation.setCAPSMProtocolID(new diameter.transatel_custom_avps.CAPSMProtocolID("utf8string753048347"));
                    cAPInformation.setCAPSMDCS(new diameter.transatel_custom_avps.CAPSMDCS("utf8string-1978640464"));
                    cAPInformation.setCAPSMValidityPeriod(new diameter.transatel_custom_avps.CAPSMValidityPeriod("utf8string-1544941224"));
                    cAPInformation.setCAPSMRejectDuplicate(new diameter.transatel_custom_avps.CAPSMRejectDuplicate("utf8string1091149644"));
                    cAPInformation.setCAPSCCPCallingGT(new diameter.transatel_custom_avps.CAPSCCPCallingGT("utf8string1237955470"));
                    cAPInformation.setCAPSCCPCalledGT(new diameter.transatel_custom_avps.CAPSCCPCalledGT("utf8string-118503395"));
                    cAPInformation.setCAPBearerCapabilityTransferMode(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferMode("utf8string1845296122"));
                    cAPInformation.setCAPGSMForwardingPending(new diameter.transatel_custom_avps.CAPGSMForwardingPending(new Integer(-117013839)));
                    cAPInformation.setCAPTCAPRemoteTransactionId(new diameter.transatel_custom_avps.CAPTCAPRemoteTransactionId("octetstring428491544"));
                    cAPInformation.setCAPTCAPLocalTransactionId(new diameter.transatel_custom_avps.CAPTCAPLocalTransactionId("octetstring1116663330"));
                    {
                        diameter.transatel_custom_avps.CAPERBSInformation cAPERBSInformation = new diameter.transatel_custom_avps.CAPERBSInformation();
                        cAPERBSInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(-2006109323)));
                        cAPERBSInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(-1648260429)));
                        cAPERBSInformation.setCAPERBSEventSpecificInformation(new diameter.transatel_custom_avps.CAPERBSEventSpecificInformation("octetstring1323444124"));
                        cAPERBSInformation.setCAPERBSLegId(new diameter.transatel_custom_avps.CAPERBSLegId(new Integer(1404614106)));
                        cAPERBSInformation.setCAPERBSMessageType(new diameter.transatel_custom_avps.CAPERBSMessageType(new Integer(1786195167)));
                        cAPInformation.setCAPERBSInformation(cAPERBSInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPACHInformation cAPACHInformation = new diameter.transatel_custom_avps.CAPACHInformation();
                        cAPACHInformation.setCAPACHBeepTone(new diameter.transatel_custom_avps.CAPACHBeepTone(diameter.transatel_custom_avps.CAPACHBeepTone.Value.False));
                        cAPInformation.setCAPACHInformation(cAPACHInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPConnectInformation cAPConnectInformation = new diameter.transatel_custom_avps.CAPConnectInformation();
                        cAPConnectInformation.setCAPAnnouncementAccessNumber(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumber("utf8string-2114074163"));
                        cAPConnectInformation.setCAPAnnouncementAccessNumberNOA(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumberNOA(new Integer(1841800663)));
                        cAPConnectInformation.setCAPConnectDestinationNumber(new diameter.transatel_custom_avps.CAPConnectDestinationNumber("utf8string-1598929514"));
                        cAPConnectInformation.setCAPConnectDestinationNumberNature(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNature(new Integer(842437608)));
                        cAPConnectInformation.setCAPConnectDestinationNumberNPI(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNPI(new Integer(431855020)));
                        cAPConnectInformation.setCAPConnectGenericNumber(new diameter.transatel_custom_avps.CAPConnectGenericNumber("utf8string1966131030"));
                        cAPConnectInformation.setCAPConnectCallingCategory(new diameter.transatel_custom_avps.CAPConnectCallingCategory(new Integer(851728736)));
                        cAPConnectInformation.setCAPConnectRedirectingNumber(new diameter.transatel_custom_avps.CAPConnectRedirectingNumber("utf8string1434429603"));
                        cAPConnectInformation.setCAPConnectRedirectingIndicator(new diameter.transatel_custom_avps.CAPConnectRedirectingIndicator(new Integer(-1547962545)));
                        cAPConnectInformation.setCAPConnectOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPConnectOriginalRedirectingReason(new Integer(-908567117)));
                        cAPConnectInformation.setCAPConnectRedirectingCounter(new diameter.transatel_custom_avps.CAPConnectRedirectingCounter(new Integer(-1825171757)));
                        cAPConnectInformation.setCAPConnectRedirectingReason(new diameter.transatel_custom_avps.CAPConnectRedirectingReason(new Integer(2040141041)));
                        cAPConnectInformation.setCAPConnectoCSIApplicable(new diameter.transatel_custom_avps.CAPConnectoCSIApplicable(new Integer(1932517347)));
                        cAPConnectInformation.setCAPConnectSuppressionOfAnnouncement(new diameter.transatel_custom_avps.CAPConnectSuppressionOfAnnouncement(new Integer(-2001329889)));
                        cAPConnectInformation.setCAPConnectGenericNumberNOA(new diameter.transatel_custom_avps.CAPConnectGenericNumberNOA(new Integer(1426961911)));
                        cAPConnectInformation.setCAPConnectGenericNumberNPI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNPI(new Integer(1237696876)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumber(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumber("utf8string-167504141"));
                        cAPConnectInformation.setCAPConnectDestinationNumberINN(new diameter.transatel_custom_avps.CAPConnectDestinationNumberINN(new Integer(-1669992305)));
                        cAPConnectInformation.setCAPConnectGenericNumberNQI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNQI(new Integer(1158411561)));
                        cAPConnectInformation.setCAPConnectGenericNumberNII(new diameter.transatel_custom_avps.CAPConnectGenericNumberNII(new Integer(2103592679)));
                        cAPConnectInformation.setCAPConnectGenericNumberARI(new diameter.transatel_custom_avps.CAPConnectGenericNumberARI(new Integer(-1774461975)));
                        cAPConnectInformation.setCAPConnectGenericNumberSCI(new diameter.transatel_custom_avps.CAPConnectGenericNumberSCI(new Integer(2082287351)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberNOA(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNOA(new Integer(734101569)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberNPI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNPI(new Integer(48640191)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberARI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberARI(new Integer(675388373)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberNOA(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNOA(new Integer(1653358519)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberNPI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNPI(new Integer(410068471)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberARI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberARI(new Integer(240619639)));
                        cAPConnectInformation.setCAPConnectMaxDuration(new diameter.transatel_custom_avps.CAPConnectMaxDuration(new Integer(-851132563)));
                        cAPInformation.setCAPConnectInformation(cAPConnectInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPRRBSInformation cAPRRBSInformation = new diameter.transatel_custom_avps.CAPRRBSInformation();
                        cAPRRBSInformation.setCAPRRBSNoAnswerTimeout(new diameter.transatel_custom_avps.CAPRRBSNoAnswerTimeout(new Integer(1530320469)));
                        cAPInformation.setCAPRRBSInformation(cAPRRBSInformation);
                    }
                    cAPInformation.setCAPReleaseCause(new diameter.transatel_custom_avps.CAPReleaseCause(new Integer(-183140478)));
                    cAPInformation.setCAPSMSpecificInfo(new diameter.transatel_custom_avps.CAPSMSpecificInfo("octetstring-142494076"));
                    cAPInformation.setCAPTCAPErrorCause(new diameter.transatel_custom_avps.CAPTCAPErrorCause(new Integer(261608788)));
                    cSInformation.setCAPInformation(cAPInformation);
                }
                serviceInformation.setCSInformation(cSInformation);
            }
            creditControlRequest.setServiceInformation(serviceInformation);
        }
        // add more AVP as ANY values to creditControlRequest

        byte[] buffer = creditControlRequest.encode();
        CreditControlRequest creditControlRequest2 = new CreditControlRequest(buffer);
        String s1 = creditControlRequest.toString();
        String s2 = creditControlRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("creditControlRequest1 = " + s1);
            System.err.println("creditControlRequest2 = " + s2);
            throw new VerificationException("CreditControlRequest encoding/decoding failure");
        }
    }

    public static void testCreditControlAnswer() throws Exception {
        CreditControlAnswer creditControlAnswer = new CreditControlAnswer(false, false);
        creditControlAnswer.setSessionId(new diameter.base.SessionId("utf8string-555414163"));
        creditControlAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-2144932223)));
        creditControlAnswer.setOriginHost(new diameter.base.OriginHost("id999105636.diameter.com"));
        creditControlAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1773101922.diameter.com"));
        creditControlAnswer.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1106933989)));
        creditControlAnswer.setCCRequestType(new CCRequestType(CCRequestType.Value.EVENT_REQUEST));
        creditControlAnswer.setCCRequestNumber(new CCRequestNumber(new Integer(-497284108)));
        creditControlAnswer.setCCSessionFailover(new CCSessionFailover(CCSessionFailover.Value.FAILOVER_SUPPORTED));
        creditControlAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(-1277188252)));
        {
            MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
            {
                GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(-1546310543));
                grantedServiceUnit.setCCTime(new CCTime(new Integer(2069819395)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(1832383073962804996L)));
                        unitValue.setExponent(new Exponent(new Integer(-886514399)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(884619809)));
                    grantedServiceUnit.setCCMoney(cCMoney);
                }
                grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(2713871750315336005L)));
                grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(6338673885357988285L)));
                grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(5516406399705571909L)));
                grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(2600229243556544622L)));
                // add more AVP as ANY values to grantedServiceUnit
                multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
            }
            {
                RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                requestedServiceUnit.setCCTime(new CCTime(new Integer(496324020)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(3492223944266021905L)));
                        unitValue.setExponent(new Exponent(new Integer(1624985488)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(2020058736)));
                    requestedServiceUnit.setCCMoney(cCMoney);
                }
                requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-3264740371379106634L)));
                requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(1020921916704282159L)));
                requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-9104536625369415801L)));
                requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(5812218089977143318L)));
                // add more AVP as ANY values to requestedServiceUnit
                multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
            }
            {
                UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.QHT));
                usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                usedServiceUnit.setCCTime(new CCTime(new Integer(-931677798)));
                usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-5830026683119191863L)));
                usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-1623691794860817315L)));
                usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-4160833907760264934L)));
                usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-3590628528676063899L)));
                usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(481186682));
                multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
            }
            multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(-1711280774)));
            multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(1093495639)));
            {
                GSUPoolReference gSUPoolReference = new GSUPoolReference();
                gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-1079072842)));
                gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.INPUT_OCTETS));
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(1746332524685768295L)));
                    unitValue.setExponent(new Exponent(new Integer(-360769498)));
                    gSUPoolReference.setUnitValue(unitValue);
                }
                multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
            }
            multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(1137795837)));
            multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(-1974739668)));
            {
                FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.REDIRECT));
                finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string-474010393"));
                {
                    RedirectServer redirectServer = new RedirectServer();
                    redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.URLocation));
                    redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string1443141069"));
                    finalUnitIndication.setRedirectServer(redirectServer);
                }
                multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
            }
            multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(-1197437820)));
            multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(690545252)));
            multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1266931622)));
            multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(-515208256)));
            multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(84044080)));
            multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.POOL_EXHAUSTED));
            {
                Trigger trigger = new Trigger();
                trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_MAXIMUM_BIT_RATE_FOR_DOWNLINK));
                multipleServicesCreditControl.setTrigger(trigger);
            }
            {
                PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-1939423422)));
                pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring1712426302"));
                pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
            }
            multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring-360265288"));
            {
                AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring513875083"));
                {
                    Flows flows = new Flows();
                    flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(237306313)));
                    flows.addFlowNumber(new FlowNumber(new Integer(2084765930)));
                    aFCorrelationInformation.addFlows(flows);
                }
                multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
            }
            {
                Envelope envelope = new Envelope();
                envelope.setEnvelopeStartTime(new EnvelopeStartTime(-1179649182));
                envelope.setEnvelopeEndTime(new EnvelopeEndTime(-966658933));
                envelope.setCCTotalOctets(new CCTotalOctets(new Long(-5073661499502810978L)));
                envelope.setCCInputOctets(new CCInputOctets(new Long(-3430710775517950762L)));
                envelope.setCCOutputOctets(new CCOutputOctets(new Long(7518863773936850107L)));
                envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-5555228759150708005L)));
                // add more AVP as ANY values to envelope
                multipleServicesCreditControl.addEnvelope(envelope);
            }
            multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME_AND_EVENTS));
            {
                TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(1354541560)));
                multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
            }
            {
                ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string224771676"));
                serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1168561456)));
                multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
            }
            {
                QoSInformation qoSInformation = new QoSInformation();
                qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_8));
                qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1137115440)));
                qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-733098214)));
                qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(3660531)));
                qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(1308089312)));
                qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring1838491904"));
                {
                    AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                    allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(53055951)));
                    allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                    allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                    qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                }
                qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(2083815348)));
                qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-123869088)));
                // add more AVP as ANY values to qoSInformation
                multipleServicesCreditControl.setQoSInformation(qoSInformation);
            }
            creditControlAnswer.addMultipleServicesCreditControl(multipleServicesCreditControl);
        }
        {
            CostInformation costInformation = new CostInformation();
            {
                UnitValue unitValue = new UnitValue();
                unitValue.setValueDigits(new ValueDigits(new Long(3807881096778779011L)));
                unitValue.setExponent(new Exponent(new Integer(-2122039257)));
                costInformation.setUnitValue(unitValue);
            }
            costInformation.setCurrencyCode(new CurrencyCode(new Integer(1208144210)));
            costInformation.setCostUnit(new CostUnit("utf8string-1303832428"));
            creditControlAnswer.setCostInformation(costInformation);
        }
        creditControlAnswer.setLowBalanceIndication(new LowBalanceIndication(LowBalanceIndication.Value.YES));
        {
            RemainingBalance remainingBalance = new RemainingBalance();
            {
                UnitValue unitValue = new UnitValue();
                unitValue.setValueDigits(new ValueDigits(new Long(-6599657122897376643L)));
                unitValue.setExponent(new Exponent(new Integer(1470180162)));
                remainingBalance.setUnitValue(unitValue);
            }
            remainingBalance.setCurrencyCode(new CurrencyCode(new Integer(1422351670)));
            creditControlAnswer.setRemainingBalance(remainingBalance);
        }
        creditControlAnswer.setCreditControlFailureHandling(new CreditControlFailureHandling(CreditControlFailureHandling.Value.CONTINUE));
        creditControlAnswer.setDirectDebitingFailureHandling(new DirectDebitingFailureHandling(DirectDebitingFailureHandling.Value.CONTINUE));
        creditControlAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain655286047.com", URI.Scheme.AAAS, (short)6323, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        creditControlAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_APPLICATION));
        creditControlAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(-1064687499)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id647233931.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring85155149"));
            // add more AVP as ANY values to proxyInfo
            creditControlAnswer.addProxyInfo(proxyInfo);
        }
        creditControlAnswer.addRouteRecord(new diameter.base.RouteRecord("id776647917.diameter.com"));
        {
            ServiceInformation serviceInformation = new ServiceInformation();
            {
                SubscriptionId subscriptionId = new SubscriptionId();
                subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_NAI));
                subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string1892160325"));
                serviceInformation.addSubscriptionId(subscriptionId);
            }
            {
                AoCInformation aoCInformation = new AoCInformation();
                {
                    AoCCostInformation aoCCostInformation = new AoCCostInformation();
                    {
                        AccumulatedCost accumulatedCost = new AccumulatedCost();
                        accumulatedCost.setValueDigits(new ValueDigits(new Long(1556479568187575932L)));
                        accumulatedCost.setExponent(new Exponent(new Integer(-497756420)));
                        aoCCostInformation.setAccumulatedCost(accumulatedCost);
                    }
                    {
                        IncrementalCost incrementalCost = new IncrementalCost();
                        incrementalCost.setValueDigits(new ValueDigits(new Long(8049753375297792750L)));
                        incrementalCost.setExponent(new Exponent(new Integer(-1351721593)));
                        aoCCostInformation.addIncrementalCost(incrementalCost);
                    }
                    aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(901556223)));
                    aoCInformation.setAoCCostInformation(aoCCostInformation);
                }
                {
                    TariffInformation tariffInformation = new TariffInformation();
                    {
                        CurrentTariff currentTariff = new CurrentTariff();
                        currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-1518502775)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(2017107112374261610L)));
                            scaleFactor.setExponent(new Exponent(new Integer(930270974)));
                            currentTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.MONEY));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(769180074734275014L)));
                                unitValue.setExponent(new Exponent(new Integer(-164330797)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(6329899668723231405L)));
                                unitCost.setExponent(new Exponent(new Integer(-84574182)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1087973107)));
                            currentTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setCurrentTariff(currentTariff);
                    }
                    tariffInformation.setTariffTimeChange(new TariffTimeChange(-1053429611));
                    {
                        NextTariff nextTariff = new NextTariff();
                        nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-719240806)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(-5921908461488744719L)));
                            scaleFactor.setExponent(new Exponent(new Integer(-443957369)));
                            nextTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.INPUT_OCTETS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-664730576850961523L)));
                                unitValue.setExponent(new Exponent(new Integer(72210980)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(-5953335475350689007L)));
                                unitCost.setExponent(new Exponent(new Integer(1093408618)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-42230244)));
                            nextTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setNextTariff(nextTariff);
                    }
                    aoCInformation.setTariffInformation(tariffInformation);
                }
                {
                    AoCSubscriptionInformation aoCSubscriptionInformation = new AoCSubscriptionInformation();
                    {
                        AoCService aoCService = new AoCService();
                        aoCService.setAoCServiceObligatoryType(new AoCServiceObligatoryType(AoCServiceObligatoryType.Value.BINDING));
                        aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.NONE));
                        aoCSubscriptionInformation.addAoCService(aoCService);
                    }
                    aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.CAI));
                    aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(120278146)));
                    aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                }
                serviceInformation.setAoCInformation(aoCInformation);
            }
            {
                PSInformation pSInformation = new PSInformation();
                pSInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(749283323)));
                pSInformation.setPDNConnectionID(new PDNConnectionID(new Integer(-570295479)));
                pSInformation.setNodeId(new NodeId("utf8string130007859"));
                pSInformation.setRo3GPPPDPType(new Ro3GPPPDPType(new Integer(-1082826042)));
                pSInformation.addPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "68.123.158.39")));
                pSInformation.setPDPAddressPrefixLength(new PDPAddressPrefixLength(new Integer(392785039)));
                pSInformation.setDynamicAddressFlag(new DynamicAddressFlag(DynamicAddressFlag.Value.Dynamic));
                pSInformation.setDynamicAddressFlagExtension(new DynamicAddressFlagExtension(DynamicAddressFlagExtension.Value.Dynamic));
                {
                    QoSInformation qoSInformation = new QoSInformation();
                    qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_1));
                    qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1149714056)));
                    qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1262050087)));
                    qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-1674980319)));
                    qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-333598774)));
                    qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-1998334367"));
                    {
                        AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                        allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1654658242)));
                        allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                        allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                        qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                    }
                    qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1112391946)));
                    qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-93607443)));
                    // add more AVP as ANY values to qoSInformation
                    pSInformation.setQoSInformation(qoSInformation);
                }
                pSInformation.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "117.230.159.31")));
                pSInformation.setGGSNAddress(new GGSNAddress(new Address(Address.Family.IPV4, "198.214.34.91")));
                pSInformation.setSGWAddress(new SGWAddress(new Address(Address.Family.IPV4, "97.57.106.204")));
                pSInformation.setCGAddress(new CGAddress(new Address(Address.Family.IPV4, "98.142.90.231")));
                pSInformation.setServingNodeType(new ServingNodeType(ServingNodeType.Value.hSGW));
                pSInformation.setSGWChange(new SGWChange(SGWChange.Value.ACR_Start_NOT_due_to_SGW_Change));
                pSInformation.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-377580460"));
                pSInformation.setIMSIUnauthenticatedFlag(new IMSIUnauthenticatedFlag(IMSIUnauthenticatedFlag.Value.Authenticated));
                pSInformation.setRo3GPPGGSNMCCMNC(new Ro3GPPGGSNMCCMNC("utf8string1381886760"));
                pSInformation.setRo3GPPNSAPI(new Ro3GPPNSAPI("utf8string822923988"));
                pSInformation.setCalledStationId(new diameter.nasreq.CalledStationId("utf8string1373299440"));
                pSInformation.setRo3GPPSessionStopIndicator(new Ro3GPPSessionStopIndicator("octetstring1804418813"));
                pSInformation.setRo3GPPSelectionMode(new Ro3GPPSelectionMode("utf8string948882756"));
                pSInformation.setRo3GPPChargingCharacteristics(new Ro3GPPChargingCharacteristics("utf8string-912844070"));
                pSInformation.setRo3GPPSGSNMCCMNC(new Ro3GPPSGSNMCCMNC("utf8string-288473368"));
                pSInformation.setRo3GPPMSTimeZone(new Ro3GPPMSTimeZone("octetstring789924633"));
                pSInformation.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring-98596513"));
                pSInformation.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring-1948627518"));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(-838964137)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.Closed_mode));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.CSG_Member));
                    pSInformation.setUserCSGInformation(userCSGInformation);
                }
                pSInformation.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string1870831737"));
                pSInformation.setRo3GPPRATType(new Ro3GPPRATType("octetstring193420322"));
                {
                    PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                    pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-765285899)));
                    pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-1552381721"));
                    pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                    pSInformation.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                }
                pSInformation.setPDPContextType(new PDPContextType(PDPContextType.Value.PRIMARY));
                {
                    OfflineCharging offlineCharging = new OfflineCharging();
                    offlineCharging.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(-1558559840)));
                    {
                        TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                        timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                        timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(-1700001036)));
                        offlineCharging.setTimeQuotaMechanism(timeQuotaMechanism);
                    }
                    offlineCharging.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES));
                    {
                        MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
                        {
                            GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                            grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(-1695292007));
                            grantedServiceUnit.setCCTime(new CCTime(new Integer(1346932145)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-5056214670189858457L)));
                                    unitValue.setExponent(new Exponent(new Integer(-632857930)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(105607977)));
                                grantedServiceUnit.setCCMoney(cCMoney);
                            }
                            grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-4046692208623317057L)));
                            grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(424782701967633474L)));
                            grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-3783141686650044807L)));
                            grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-2265817051020429979L)));
                            // add more AVP as ANY values to grantedServiceUnit
                            multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
                        }
                        {
                            RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                            requestedServiceUnit.setCCTime(new CCTime(new Integer(-1210301422)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-2080842392947191682L)));
                                    unitValue.setExponent(new Exponent(new Integer(-843798475)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-1256732411)));
                                requestedServiceUnit.setCCMoney(cCMoney);
                            }
                            requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-8245805941979334706L)));
                            requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(7785120527897903654L)));
                            requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-4014309128132596709L)));
                            requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-5630692824260128067L)));
                            // add more AVP as ANY values to requestedServiceUnit
                            multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
                        }
                        {
                            UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                            usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.OTHER_QUOTA_TYPE));
                            usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                            usedServiceUnit.setCCTime(new CCTime(new Integer(121208574)));
                            usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-7103903960861118657L)));
                            usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-5330575062361057017L)));
                            usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-7059501787255681132L)));
                            usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-6982130896950045571L)));
                            usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(-1751915211));
                            multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
                        }
                        multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(999596406)));
                        multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(-825804545)));
                        {
                            GSUPoolReference gSUPoolReference = new GSUPoolReference();
                            gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(462164734)));
                            gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.TOTAL_OCTETS));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-4003745919285959651L)));
                                unitValue.setExponent(new Exponent(new Integer(-699975187)));
                                gSUPoolReference.setUnitValue(unitValue);
                            }
                            multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
                        }
                        multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(257831098)));
                        multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(-418045973)));
                        {
                            FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                            finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.REDIRECT));
                            finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                            finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string1829921157"));
                            {
                                RedirectServer redirectServer = new RedirectServer();
                                redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.SIP_URI));
                                redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string1525794747"));
                                finalUnitIndication.setRedirectServer(redirectServer);
                            }
                            multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
                        }
                        multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(588748002)));
                        multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(1774346545)));
                        multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(364969782)));
                        multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(1397474618)));
                        multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(1287863835)));
                        multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.QHT));
                        {
                            Trigger trigger = new Trigger();
                            trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_MEAN_THROUGHPUT));
                            multipleServicesCreditControl.setTrigger(trigger);
                        }
                        {
                            PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                            pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(1388529575)));
                            pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-2064859504"));
                            pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Append));
                            multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                        }
                        multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring-2031915369"));
                        {
                            AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                            aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-134830346"));
                            {
                                Flows flows = new Flows();
                                flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(-1134857420)));
                                flows.addFlowNumber(new FlowNumber(new Integer(999265356)));
                                aFCorrelationInformation.addFlows(flows);
                            }
                            multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
                        }
                        {
                            Envelope envelope = new Envelope();
                            envelope.setEnvelopeStartTime(new EnvelopeStartTime(-240325562));
                            envelope.setEnvelopeEndTime(new EnvelopeEndTime(-54530039));
                            envelope.setCCTotalOctets(new CCTotalOctets(new Long(3111174390698619750L)));
                            envelope.setCCInputOctets(new CCInputOctets(new Long(-1740782469046435806L)));
                            envelope.setCCOutputOctets(new CCOutputOctets(new Long(-2721502942569702844L)));
                            envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-2021562252499197038L)));
                            // add more AVP as ANY values to envelope
                            multipleServicesCreditControl.addEnvelope(envelope);
                        }
                        multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME));
                        {
                            TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                            timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.CONTINUOUS_TIME_PERIOD));
                            timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(-383636965)));
                            multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
                        }
                        {
                            ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                            serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string1613130678"));
                            serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(-37218667)));
                            multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
                        }
                        {
                            QoSInformation qoSInformation = new QoSInformation();
                            qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_9));
                            qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1883588215)));
                            qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(1247883299)));
                            qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-1792937107)));
                            qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-225427510)));
                            qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring897679855"));
                            {
                                AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                                allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-678662368)));
                                allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                                allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                                qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                            }
                            qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(916592751)));
                            qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-853180076)));
                            // add more AVP as ANY values to qoSInformation
                            multipleServicesCreditControl.setQoSInformation(qoSInformation);
                        }
                        offlineCharging.addMultipleServicesCreditControl(multipleServicesCreditControl);
                    }
                    // add more AVP as ANY values to offlineCharging
                    pSInformation.setOfflineCharging(offlineCharging);
                }
                {
                    TrafficDataVolumes trafficDataVolumes = new TrafficDataVolumes();
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_3));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(254845188)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-257758450)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-1324297024)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-397355759)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-1520600727"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(358694547)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-156991413)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1304124986)));
                        // add more AVP as ANY values to qoSInformation
                        trafficDataVolumes.setQoSInformation(qoSInformation);
                    }
                    trafficDataVolumes.setAccountingInputOctets(new AccountingInputOctets(new Long(8890763625629509281L)));
                    trafficDataVolumes.setAccountingInputPackets(new AccountingInputPackets(new Long(708280075820279479L)));
                    trafficDataVolumes.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-392565846328592748L)));
                    trafficDataVolumes.setAccountingOutputPackets(new AccountingOutputPackets(new Long(8654214030098152827L)));
                    trafficDataVolumes.setChangeCondition(new ChangeCondition(new Integer(193796072)));
                    trafficDataVolumes.setChangeTime(new ChangeTime(676395095));
                    trafficDataVolumes.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring843413305"));
                    pSInformation.addTrafficDataVolumes(trafficDataVolumes);
                }
                {
                    ServiceDataContainer serviceDataContainer = new ServiceDataContainer();
                    {
                        AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                        aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring968030261"));
                        {
                            Flows flows = new Flows();
                            flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(-1935808881)));
                            flows.addFlowNumber(new FlowNumber(new Integer(110212727)));
                            aFCorrelationInformation.addFlows(flows);
                        }
                        serviceDataContainer.setAFCorrelationInformation(aFCorrelationInformation);
                    }
                    serviceDataContainer.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring1716339732"));
                    serviceDataContainer.setAccountingInputOctets(new AccountingInputOctets(new Long(7843925415067021686L)));
                    serviceDataContainer.setAccountingOutputOctets(new AccountingOutputOctets(new Long(3743357437278976833L)));
                    serviceDataContainer.setAccountingInputPackets(new AccountingInputPackets(new Long(5872342519667242927L)));
                    serviceDataContainer.setAccountingOutputPackets(new AccountingOutputPackets(new Long(1726260631623857778L)));
                    serviceDataContainer.setLocalSequenceNumber(new LocalSequenceNumber(new Integer(-430849622)));
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_1));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-71460776)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-442345915)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1209052981)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(555904107)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-2022294409"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1548681108)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-189197328)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-1858004470)));
                        // add more AVP as ANY values to qoSInformation
                        serviceDataContainer.setQoSInformation(qoSInformation);
                    }
                    serviceDataContainer.setRatingGroup(new RatingGroup(new Integer(-1694407810)));
                    serviceDataContainer.setChangeTime(new ChangeTime(-2127853806));
                    serviceDataContainer.setServiceIdentifier(new ServiceIdentifier(new Integer(2135937123)));
                    {
                        ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                        serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-1840126982"));
                        serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(-535380957)));
                        serviceDataContainer.setServiceSpecificInfo(serviceSpecificInfo);
                    }
                    serviceDataContainer.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "41.71.107.173")));
                    serviceDataContainer.setTimeFirstUsage(new TimeFirstUsage(-1374762713));
                    serviceDataContainer.setTimeLastUsage(new TimeLastUsage(665543946));
                    serviceDataContainer.setTimeUsage(new TimeUsage(-824697737));
                    serviceDataContainer.addChangeCondition(new ChangeCondition(new Integer(-131082879)));
                    serviceDataContainer.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring-1879350043"));
                    serviceDataContainer.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string996774523"));
                    pSInformation.addServiceDataContainer(serviceDataContainer);
                }
                {
                    UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
                    userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.IMEISV));
                    userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring1524563502"));
                    pSInformation.setUserEquipmentInfo(userEquipmentInfo);
                }
                {
                    TerminalInformation terminalInformation = new TerminalInformation();
                    terminalInformation.setIMEI(new IMEI("utf8string-1326914080"));
                    terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string-538977172"));
                    // add more AVP as ANY values to terminalInformation
                    pSInformation.setTerminalInformation(terminalInformation);
                }
                pSInformation.setStartTime(new StartTime(-1969009485));
                pSInformation.setStopTime(new StopTime(1521132977));
                pSInformation.setChangeCondition(new ChangeCondition(new Integer(-582759124)));
                pSInformation.setDiagnostics(new Diagnostics(new Integer(-1422518894)));
                pSInformation.setLowPriorityIndicator(new LowPriorityIndicator(LowPriorityIndicator.Value.YES));
                serviceInformation.setPSInformation(pSInformation);
            }
            {
                WLANInformation wLANInformation = new WLANInformation();
                wLANInformation.setWLANSessionId(new WLANSessionId(new Integer(956882420)));
                wLANInformation.setPDGAddress(new PDGAddress(new Address(Address.Family.IPV4, "167.176.169.152")));
                wLANInformation.setPDGChargingId(new PDGChargingId(new Integer(-1648961422)));
                wLANInformation.setWAGAddress(new WAGAddress(new Address(Address.Family.IPV4, "244.92.243.157")));
                wLANInformation.setWAGPLMNId(new WAGPLMNId("octetstring-1914661215"));
                {
                    WLANRadioContainer wLANRadioContainer = new WLANRadioContainer();
                    wLANRadioContainer.setOperatorName(new OperatorName("octetstring-1139871702"));
                    wLANRadioContainer.setLocationInformation(new LocationInformation("octetstring104414044"));
                    {
                        LocationType locationType = new LocationType();
                        locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.INITIAL_LOCATION));
                        locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string1752283629"));
                        wLANRadioContainer.setLocationType(locationType);
                    }
                    wLANRadioContainer.setWLANTechnology(new WLANTechnology(new Integer(-1384302151)));
                    wLANInformation.setWLANRadioContainer(wLANRadioContainer);
                }
                wLANInformation.setWLANUELocalIPAddress(new WLANUELocalIPAddress(new Address(Address.Family.IPV4, "165.18.44.89")));
                serviceInformation.setWLANInformation(wLANInformation);
            }
            {
                IMSInformation iMSInformation = new IMSInformation();
                {
                    EventType eventType = new EventType();
                    eventType.setSIPMethod(new SIPMethod("utf8string-1018179864"));
                    eventType.setIMSEvent(new IMSEvent("utf8string917919252"));
                    eventType.setExpires(new Expires(new Integer(-2098456787)));
                    iMSInformation.setEventType(eventType);
                }
                iMSInformation.setRoleOfNode(new RoleOfNode(RoleOfNode.Value.TERMINATING_ROLE));
                iMSInformation.setNodeFunctionality(new NodeFunctionality(NodeFunctionality.Value.HSGW));
                iMSInformation.setUserSessionID(new UserSessionID("utf8string-2135311602"));
                iMSInformation.setOutgoingSessionId(new OutgoingSessionId("utf8string544682723"));
                iMSInformation.addCallingPartyAddress(new CallingPartyAddress("utf8string-546043090"));
                iMSInformation.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY_0));
                iMSInformation.setCalledPartyAddress(new CalledPartyAddress("utf8string62560030"));
                iMSInformation.addCalledAssertedIdentity(new CalledAssertedIdentity("utf8string-766670521"));
                iMSInformation.setNumberPortabilityRoutingInformation(new NumberPortabilityRoutingInformation("utf8string-1790995749"));
                iMSInformation.setCarrierSelectRoutingInformation(new CarrierSelectRoutingInformation("utf8string185265816"));
                iMSInformation.setAlternateChargedPartyAddress(new AlternateChargedPartyAddress("utf8string-2146215988"));
                iMSInformation.setRequestedPartyAddress(new RequestedPartyAddress("utf8string-1225985411"));
                iMSInformation.addAssociatedURI(new AssociatedURI("utf8string2117421811"));
                {
                    TimeStamps timeStamps = new TimeStamps();
                    timeStamps.setSIPRequestTimestamp(new SIPRequestTimestamp(-79033637));
                    timeStamps.setSIPResponseTimestamp(new SIPResponseTimestamp(-1590944383));
                    timeStamps.setSIPRequestTimestampFraction(new SIPRequestTimestampFraction(new Integer(262931253)));
                    timeStamps.setSIPResponseTimestampFraction(new SIPResponseTimestampFraction(new Integer(302650070)));
                    iMSInformation.setTimeStamps(timeStamps);
                }
                {
                    ApplicationServerInformation applicationServerInformation = new ApplicationServerInformation();
                    applicationServerInformation.setApplicationServer(new ApplicationServer("utf8string-112177696"));
                    applicationServerInformation.addApplicationProvidedCalledPartyAddress(new ApplicationProvidedCalledPartyAddress("utf8string148226617"));
                    iMSInformation.addApplicationServerInformation(applicationServerInformation);
                }
                {
                    InterOperatorIdentifier interOperatorIdentifier = new InterOperatorIdentifier();
                    interOperatorIdentifier.setOriginatingIOI(new OriginatingIOI("utf8string611426131"));
                    interOperatorIdentifier.setTerminatingIOI(new TerminatingIOI("utf8string283027401"));
                    iMSInformation.addInterOperatorIdentifier(interOperatorIdentifier);
                }
                iMSInformation.setIMSChargingIdentifier(new IMSChargingIdentifier("utf8string-1939499924"));
                iMSInformation.addSDPSessionDescription(new SDPSessionDescription("utf8string-1430120585"));
                {
                    SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                    sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string-226454830"));
                    sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string-2055432694"));
                    sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                    sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Inserted));
                    sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_realm_used));
                    sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.unknown));
                    sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string1009540890"));
                    sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string-765606483"));
                    sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(162683231)));
                    sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring1388142980"));
                    sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Answer));
                    iMSInformation.addSDPMediaComponent(sDPMediaComponent);
                }
                iMSInformation.setServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "99.83.75.36")));
                {
                    ServerCapabilities serverCapabilities = new ServerCapabilities();
                    serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(2105988547)));
                    serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(-254274561)));
                    serverCapabilities.addServerName(new ServerName("utf8string2012672613"));
                    // add more AVP as ANY values to serverCapabilities
                    iMSInformation.setServerCapabilities(serverCapabilities);
                }
                {
                    TrunkGroupID trunkGroupID = new TrunkGroupID();
                    trunkGroupID.setIncomingTrunkGroupID(new IncomingTrunkGroupID("utf8string1214089449"));
                    trunkGroupID.setOutgoingTrunkGroupID(new OutgoingTrunkGroupID("utf8string-24345088"));
                    iMSInformation.setTrunkGroupID(trunkGroupID);
                }
                iMSInformation.setBearerService(new BearerService("octetstring45798629"));
                iMSInformation.setServiceId(new ServiceId("utf8string-865188903"));
                {
                    ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                    serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-337295987"));
                    serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(-483881779)));
                    iMSInformation.addServiceSpecificInfo(serviceSpecificInfo);
                }
                {
                    MessageBody messageBody = new MessageBody();
                    messageBody.setContentType(new ContentType("utf8string468857914"));
                    messageBody.setContentLength(new ContentLength(new Integer(345468002)));
                    messageBody.setContentDisposition(new ContentDisposition("utf8string-1365333748"));
                    messageBody.setOriginator(new Originator(Originator.Value.Called_Party));
                    iMSInformation.addMessageBody(messageBody);
                }
                iMSInformation.setCauseCode(new CauseCode(new Integer(-221535100)));
                iMSInformation.setAccessNetworkInformation(new AccessNetworkInformation("octetstring800813119"));
                {
                    EarlyMediaDescription earlyMediaDescription = new EarlyMediaDescription();
                    {
                        SDPTimeStamps sDPTimeStamps = new SDPTimeStamps();
                        sDPTimeStamps.setSDPOfferTimestamp(new SDPOfferTimestamp(-969644899));
                        sDPTimeStamps.setSDPAnswerTimestamp(new SDPAnswerTimestamp(47825365));
                        earlyMediaDescription.setSDPTimeStamps(sDPTimeStamps);
                    }
                    {
                        SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                        sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string-1172338562"));
                        sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string-1784719289"));
                        sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Not_Inserted));
                        sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Inserted));
                        sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_realm_used));
                        sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.called_party));
                        sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string1720288350"));
                        sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string-298211242"));
                        sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-32607079)));
                        sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring1553576559"));
                        sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Offer));
                        earlyMediaDescription.addSDPMediaComponent(sDPMediaComponent);
                    }
                    earlyMediaDescription.addSDPSessionDescription(new SDPSessionDescription("utf8string1958746885"));
                    iMSInformation.addEarlyMediaDescription(earlyMediaDescription);
                }
                iMSInformation.setIMSCommunicationServiceIdentifier(new IMSCommunicationServiceIdentifier("utf8string-1270723386"));
                iMSInformation.setOnlineChargingFlag(new OnlineChargingFlag(OnlineChargingFlag.Value.ECF_address_not_provided));
                {
                    RealTimeTariffInformation realTimeTariffInformation = new RealTimeTariffInformation();
                    {
                        TariffInformation tariffInformation = new TariffInformation();
                        {
                            CurrentTariff currentTariff = new CurrentTariff();
                            currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-388391136)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(-6617077839840888256L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-283686578)));
                                currentTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TOTAL_OCTETS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(2444811319673473220L)));
                                    unitValue.setExponent(new Exponent(new Integer(1635761653)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(3241066699765043596L)));
                                    unitCost.setExponent(new Exponent(new Integer(-574133272)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-578720450)));
                                currentTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setCurrentTariff(currentTariff);
                        }
                        tariffInformation.setTariffTimeChange(new TariffTimeChange(-1518981560));
                        {
                            NextTariff nextTariff = new NextTariff();
                            nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-989526982)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(-5330429128028025547L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-1112387871)));
                                nextTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.ADD_ON_CHARGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(5725498327170319451L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1639527618)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(-3036020904364605188L)));
                                    unitCost.setExponent(new Exponent(new Integer(1748068025)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-294721436)));
                                nextTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setNextTariff(nextTariff);
                        }
                        realTimeTariffInformation.setTariffInformation(tariffInformation);
                    }
                    realTimeTariffInformation.setTariffXML(new TariffXML("utf8string1845910088"));
                    iMSInformation.setRealTimeTariffInformation(realTimeTariffInformation);
                }
                iMSInformation.setAccountExpiration(new AccountExpiration(2001896145));
                iMSInformation.setInitialIMSChargingIdentifier(new InitialIMSChargingIdentifier("utf8string1652262941"));
                serviceInformation.setIMSInformation(iMSInformation);
            }
            {
                MMSInformation mMSInformation = new MMSInformation();
                {
                    OriginatorAddress originatorAddress = new OriginatorAddress();
                    originatorAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.MSISDN));
                    originatorAddress.setAddressData(new AddressData("utf8string-267899380"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string362088871"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string1153772485"));
                        originatorAddress.setAddressDomain(addressDomain);
                    }
                    mMSInformation.setOriginatorAddress(originatorAddress);
                }
                {
                    RecipientAddress recipientAddress = new RecipientAddress();
                    recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.MSISDN));
                    recipientAddress.setAddressData(new AddressData("utf8string2060241278"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-2095673933"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string1622276152"));
                        recipientAddress.setAddressDomain(addressDomain);
                    }
                    recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.TO));
                    mMSInformation.addRecipientAddress(recipientAddress);
                }
                mMSInformation.setSubmissionTime(new SubmissionTime(-231194086));
                {
                    MMContentType mMContentType = new MMContentType();
                    mMContentType.setTypeNumber(new TypeNumber(new Integer(-155756453)));
                    mMContentType.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string290789563"));
                    mMContentType.setContentSize(new ContentSize(new Integer(185224370)));
                    {
                        AdditionalContentInformation additionalContentInformation = new AdditionalContentInformation();
                        additionalContentInformation.setTypeNumber(new TypeNumber(new Integer(-1261201330)));
                        additionalContentInformation.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string378239808"));
                        additionalContentInformation.setContentSize(new ContentSize(new Integer(738951690)));
                        mMContentType.addAdditionalContentInformation(additionalContentInformation);
                    }
                    mMSInformation.setMMContentType(mMContentType);
                }
                mMSInformation.setPriority(new Priority(Priority.Value.Normal));
                mMSInformation.setMessageID(new MessageID("utf8string-1082004147"));
                mMSInformation.setMessageType(new MessageType(MessageType.Value.m_send_conf));
                mMSInformation.setMessageSize(new MessageSize(new Integer(-110539196)));
                {
                    MessageClass messageClass = new MessageClass();
                    messageClass.setClassIdentifier(new ClassIdentifier(ClassIdentifier.Value.Informational));
                    messageClass.setTokenText(new TokenText("utf8string401785378"));
                    mMSInformation.setMessageClass(messageClass);
                }
                mMSInformation.setDeliveryReportRequested(new DeliveryReportRequested(DeliveryReportRequested.Value.Yes));
                mMSInformation.setReadReplyReportRequested(new ReadReplyReportRequested(ReadReplyReportRequested.Value.No));
                mMSInformation.setMMBoxStorageRequested(new MMBoxStorageRequested(MMBoxStorageRequested.Value.Yes));
                mMSInformation.setApplicID(new ApplicID("utf8string1729139719"));
                mMSInformation.setReplyApplicID(new ReplyApplicID("utf8string153049916"));
                mMSInformation.setAuxApplicInfo(new AuxApplicInfo("utf8string-1718231685"));
                mMSInformation.setContentClass(new ContentClass(ContentClass.Value.megapixel));
                mMSInformation.setDRMContent(new DRMContent(DRMContent.Value.No));
                mMSInformation.setAdaptations(new Adaptations(Adaptations.Value.Yes));
                mMSInformation.setVASPId(new VASPId("utf8string2016338131"));
                mMSInformation.setVASId(new VASId("utf8string1861166798"));
                serviceInformation.setMMSInformation(mMSInformation);
            }
            {
                LCSInformation lCSInformation = new LCSInformation();
                {
                    LCSClientID lCSClientID = new LCSClientID();
                    lCSClientID.setLCSClientType(new LCSClientType(LCSClientType.Value.EMERGENCY_SERVICES));
                    lCSClientID.setLCSClientExternalID(new LCSClientExternalID("utf8string-1950810621"));
                    lCSClientID.setLCSClientDialedByMS(new LCSClientDialedByMS("utf8string1477763699"));
                    {
                        LCSClientName lCSClientName = new LCSClientName();
                        lCSClientName.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string-106242172"));
                        lCSClientName.setLCSNameString(new LCSNameString("utf8string1762310366"));
                        lCSClientName.setLCSFormatIndicator(new LCSFormatIndicator(LCSFormatIndicator.Value.MSISDN));
                        lCSClientID.setLCSClientName(lCSClientName);
                    }
                    lCSClientID.setLCSAPN(new LCSAPN("utf8string938770571"));
                    {
                        LCSRequestorID lCSRequestorID = new LCSRequestorID();
                        lCSRequestorID.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string1302807059"));
                        lCSRequestorID.setLCSRequestorIDString(new LCSRequestorIDString("utf8string1863740485"));
                        lCSClientID.setLCSRequestorID(lCSRequestorID);
                    }
                    lCSInformation.setLCSClientID(lCSClientID);
                }
                {
                    LocationType locationType = new LocationType();
                    locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.CURRENT_LOCATION));
                    locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string-610701650"));
                    lCSInformation.setLocationType(locationType);
                }
                lCSInformation.setLocationEstimate(new LocationEstimate("utf8string-575243467"));
                lCSInformation.setPositioningData(new PositioningData("utf8string-250934146"));
                lCSInformation.setRo3GPPIMSI(new Ro3GPPIMSI("utf8string-1770539047"));
                lCSInformation.setMSISDN(new MSISDN("octetstring1508713598"));
                serviceInformation.setLCSInformation(lCSInformation);
            }
            {
                PoCInformation poCInformation = new PoCInformation();
                poCInformation.setPoCServerRole(new PoCServerRole(PoCServerRole.Value.Controlling_PoC_Server));
                poCInformation.setPoCSessionType(new PoCSessionType(PoCSessionType.Value.ad_hoc_PoC_group_session));
                {
                    PoCUserRole poCUserRole = new PoCUserRole();
                    poCUserRole.setPoCUserRoleIds(new PoCUserRoleIds("utf8string1188413631"));
                    poCUserRole.setPoCUserRoleinfoUnits(new PoCUserRoleinfoUnits(PoCUserRoleinfoUnits.Value.Session_Participant));
                    poCInformation.setPoCUserRole(poCUserRole);
                }
                poCInformation.setPoCSessionInitiationType(new PoCSessionInitiationType(PoCSessionInitiationType.Value.On_demand));
                poCInformation.setPoCEventType(new PoCEventType(PoCEventType.Value.Early_Ssession_Setting_up_event));
                poCInformation.setNumberOfParticipants(new NumberOfParticipants(new Integer(1253544040)));
                poCInformation.addParticipantsInvolved(new ParticipantsInvolved("utf8string-1667372787"));
                {
                    ParticipantGroup participantGroup = new ParticipantGroup();
                    participantGroup.setCalledPartyAddress(new CalledPartyAddress("utf8string-485420970"));
                    participantGroup.setParticipantAccessPriority(new ParticipantAccessPriority(ParticipantAccessPriority.Value.Low_priority));
                    participantGroup.setUserParticipatingType(new UserParticipatingType(UserParticipatingType.Value.Normal));
                    poCInformation.addParticipantGroup(participantGroup);
                }
                {
                    TalkBurstExchange talkBurstExchange = new TalkBurstExchange();
                    talkBurstExchange.setPoCChangeTime(new PoCChangeTime(-1393861305));
                    talkBurstExchange.setNumberOfTalkBursts(new NumberOfTalkBursts(new Integer(579914700)));
                    talkBurstExchange.setTalkBurstVolume(new TalkBurstVolume(new Integer(-1621653918)));
                    talkBurstExchange.setTalkBurstTime(new TalkBurstTime(new Integer(869461556)));
                    talkBurstExchange.setNumberOfReceivedTalkBursts(new NumberOfReceivedTalkBursts(new Integer(-1754146737)));
                    talkBurstExchange.setReceivedTalkBurstVolume(new ReceivedTalkBurstVolume(new Integer(-790948747)));
                    talkBurstExchange.setReceivedTalkBurstTime(new ReceivedTalkBurstTime(new Integer(-1615201737)));
                    talkBurstExchange.setNumberOfParticipants(new NumberOfParticipants(new Integer(2017576827)));
                    talkBurstExchange.setPoCChangeCondition(new PoCChangeCondition(PoCChangeCondition.Value.numberofTalkBurstLimit));
                    poCInformation.addTalkBurstExchange(talkBurstExchange);
                }
                poCInformation.setPoCControllingAddress(new PoCControllingAddress("utf8string-513614955"));
                poCInformation.setPoCGroupName(new PoCGroupName("utf8string-895127211"));
                poCInformation.setPoCSessionId(new PoCSessionId("utf8string-612140400"));
                poCInformation.setChargedParty(new ChargedParty("utf8string-853644145"));
                serviceInformation.setPoCInformation(poCInformation);
            }
            {
                MBMSInformation mBMSInformation = new MBMSInformation();
                mBMSInformation.setTMGI(new TMGI("octetstring30222649"));
                mBMSInformation.setMBMSServiceType(new MBMSServiceType(MBMSServiceType.Value.BROADCAST));
                mBMSInformation.setMBMSUserServiceType(new MBMSUserServiceType(MBMSUserServiceType.Value.STREAMING));
                mBMSInformation.setFileRepairSupported(new FileRepairSupported(FileRepairSupported.Value.NOT_SUPPORTED));
                mBMSInformation.setRequiredMBMSBearerCapabilities(new RequiredMBMSBearerCapabilities("utf8string-2113235299"));
                mBMSInformation.setMBMS2G3GIndicator(new MBMS2G3GIndicator(MBMS2G3GIndicator.Value.ONLY_2G));
                mBMSInformation.setRAI(new RAI("utf8string779815889"));
                mBMSInformation.addMBMSServiceArea(new MBMSServiceArea("octetstring-735714613"));
                mBMSInformation.setMBMSSessionIdentity(new MBMSSessionIdentity("octetstring-1214018867"));
                mBMSInformation.setCNIPMulticastDistribution(new CNIPMulticastDistribution(CNIPMulticastDistribution.Value.NO_IP_MULTICAST));
                mBMSInformation.setMBMSGWAddress(new MBMSGWAddress(new Address(Address.Family.IPV4, "64.174.142.138")));
                serviceInformation.setMBMSInformation(mBMSInformation);
            }
            {
                SMSInformation sMSInformation = new SMSInformation();
                sMSInformation.setSMSNode(new SMSNode(SMSNode.Value.SMS_SC));
                sMSInformation.setClientAddress(new ClientAddress(new Address(Address.Family.IPV4, "55.125.239.194")));
                sMSInformation.setOriginatorSCCPAddress(new OriginatorSCCPAddress(new Address(Address.Family.IPV4, "196.121.115.103")));
                sMSInformation.setSMSCAddress(new SMSCAddress(new Address(Address.Family.IPV4, "184.62.152.87")));
                sMSInformation.setDataCodingScheme(new DataCodingScheme(new Integer(-11986066)));
                sMSInformation.setSMDischargeTime(new SMDischargeTime(-175772334));
                sMSInformation.setSMMessageType(new SMMessageType(SMMessageType.Value.SM_Service_Request));
                {
                    OriginatorInterface originatorInterface = new OriginatorInterface();
                    originatorInterface.setInterfaceId(new InterfaceId("utf8string-843471365"));
                    originatorInterface.setInterfaceText(new InterfaceText("utf8string193912938"));
                    originatorInterface.setInterfacePort(new InterfacePort("utf8string-1738896349"));
                    originatorInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.APPLICATION_TERMINATION));
                    sMSInformation.setOriginatorInterface(originatorInterface);
                }
                sMSInformation.setSMProtocolID(new SMProtocolID("octetstring1441815121"));
                sMSInformation.setReplyPathRequested(new ReplyPathRequested(ReplyPathRequested.Value.No_Reply_Path_Set));
                sMSInformation.setSMStatus(new SMStatus("octetstring-206029711"));
                sMSInformation.setSMUserDataHeader(new SMUserDataHeader("octetstring-239068198"));
                sMSInformation.setNumberOfMessagesSent(new NumberOfMessagesSent(new Integer(-1114217488)));
                {
                    RecipientInfo recipientInfo = new RecipientInfo();
                    {
                        DestinationInterface destinationInterface = new DestinationInterface();
                        destinationInterface.setInterfaceId(new InterfaceId("utf8string456539675"));
                        destinationInterface.setInterfaceText(new InterfaceText("utf8string-865021719"));
                        destinationInterface.setInterfacePort(new InterfacePort("utf8string2010721361"));
                        destinationInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.APPLICATION_ORIGINATING));
                        recipientInfo.setDestinationInterface(destinationInterface);
                    }
                    {
                        RecipientAddress recipientAddress = new RecipientAddress();
                        recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv6_Address));
                        recipientAddress.setAddressData(new AddressData("utf8string2031002898"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string-876147465"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-797962450"));
                            recipientAddress.setAddressDomain(addressDomain);
                        }
                        recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.CC));
                        recipientInfo.addRecipientAddress(recipientAddress);
                    }
                    {
                        RecipientReceivedAddress recipientReceivedAddress = new RecipientReceivedAddress();
                        recipientReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv4_Address));
                        recipientReceivedAddress.setAddressData(new AddressData("utf8string584104884"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string535647896"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string2000158361"));
                            recipientReceivedAddress.setAddressDomain(addressDomain);
                        }
                        recipientInfo.addRecipientReceivedAddress(recipientReceivedAddress);
                    }
                    recipientInfo.setRecipientSCCPAddress(new RecipientSCCPAddress(new Address(Address.Family.IPV4, "214.17.164.56")));
                    recipientInfo.setSMProtocolID(new SMProtocolID("octetstring-1608958672"));
                    sMSInformation.addRecipientInfo(recipientInfo);
                }
                {
                    OriginatorReceivedAddress originatorReceivedAddress = new OriginatorReceivedAddress();
                    originatorReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv4_Address));
                    originatorReceivedAddress.setAddressData(new AddressData("utf8string1909545695"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string222098700"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-841511616"));
                        originatorReceivedAddress.setAddressDomain(addressDomain);
                    }
                    sMSInformation.setOriginatorReceivedAddress(originatorReceivedAddress);
                }
                sMSInformation.setSMServiceType(new SMServiceType(SMServiceType.Value.VAS4SMS_Deferred_Delivery));
                serviceInformation.setSMSInformation(sMSInformation);
            }
            {
                MMTelInformation mMTelInformation = new MMTelInformation();
                {
                    SupplementaryService supplementaryService = new SupplementaryService();
                    supplementaryService.setServiceType(new ServiceType(new Integer(-389276222)));
                    supplementaryService.setServiceMode(new ServiceMode(new Integer(101856325)));
                    supplementaryService.setNumberOfDiversions(new NumberOfDiversions(new Integer(-1637555239)));
                    supplementaryService.setAssociatedPartyAddress(new AssociatedPartyAddress("utf8string723605456"));
                    supplementaryService.setServiceId(new ServiceId("utf8string1785771903"));
                    supplementaryService.setChangeTime(new ChangeTime(-285635502));
                    supplementaryService.setNumberOfParticipants(new NumberOfParticipants(new Integer(242642489)));
                    supplementaryService.setParticipantActionType(new ParticipantActionType(ParticipantActionType.Value.QUIT_CONF));
                    supplementaryService.setCUGInformation(new CUGInformation("octetstring-1159155458"));
                    {
                        AoCInformation aoCInformation = new AoCInformation();
                        {
                            AoCCostInformation aoCCostInformation = new AoCCostInformation();
                            {
                                AccumulatedCost accumulatedCost = new AccumulatedCost();
                                accumulatedCost.setValueDigits(new ValueDigits(new Long(2017167967250277299L)));
                                accumulatedCost.setExponent(new Exponent(new Integer(443091796)));
                                aoCCostInformation.setAccumulatedCost(accumulatedCost);
                            }
                            {
                                IncrementalCost incrementalCost = new IncrementalCost();
                                incrementalCost.setValueDigits(new ValueDigits(new Long(6377355603606526036L)));
                                incrementalCost.setExponent(new Exponent(new Integer(461106317)));
                                aoCCostInformation.addIncrementalCost(incrementalCost);
                            }
                            aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(-2085653313)));
                            aoCInformation.setAoCCostInformation(aoCCostInformation);
                        }
                        {
                            TariffInformation tariffInformation = new TariffInformation();
                            {
                                CurrentTariff currentTariff = new CurrentTariff();
                                currentTariff.setCurrencyCode(new CurrencyCode(new Integer(1554037327)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(-3827426402628955349L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(525456697)));
                                    currentTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(-1842777726294670044L)));
                                        unitValue.setExponent(new Exponent(new Integer(422068661)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(6209341239100513363L)));
                                        unitCost.setExponent(new Exponent(new Integer(1816553464)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1174073509)));
                                    currentTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setCurrentTariff(currentTariff);
                            }
                            tariffInformation.setTariffTimeChange(new TariffTimeChange(219771636));
                            {
                                NextTariff nextTariff = new NextTariff();
                                nextTariff.setCurrencyCode(new CurrencyCode(new Integer(254416873)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(2179742590383957423L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(1502344264)));
                                    nextTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.INPUT_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(3321448792614608295L)));
                                        unitValue.setExponent(new Exponent(new Integer(-1870425730)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(5362381135588419523L)));
                                        unitCost.setExponent(new Exponent(new Integer(2108183647)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1279457586)));
                                    nextTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setNextTariff(nextTariff);
                            }
                            aoCInformation.setTariffInformation(tariffInformation);
                        }
                        {
                            AoCSubscriptionInformation aoCSubscriptionInformation = new AoCSubscriptionInformation();
                            {
                                AoCService aoCService = new AoCService();
                                aoCService.setAoCServiceObligatoryType(new AoCServiceObligatoryType(AoCServiceObligatoryType.Value.NON_BINDING));
                                aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.AOC_S));
                                aoCSubscriptionInformation.addAoCService(aoCService);
                            }
                            aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.MONETARY));
                            aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(-612138361)));
                            aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                        }
                        supplementaryService.setAoCInformation(aoCInformation);
                    }
                    mMTelInformation.addSupplementaryService(supplementaryService);
                }
                mMTelInformation.setSubscriberRole(new SubscriberRole(SubscriberRole.Value.ORIGINATING));
                serviceInformation.setMMTelInformation(mMTelInformation);
            }
            {
                ServiceGenericInformation serviceGenericInformation = new ServiceGenericInformation();
                serviceGenericInformation.setApplicationServerID(new ApplicationServerID("utf8string-2132637446"));
                serviceGenericInformation.setApplicationServiceType(new ApplicationServiceType("utf8string-950974755"));
                serviceGenericInformation.setApplicationSessionID(new ApplicationSessionID("utf8string-1358141503"));
                serviceGenericInformation.setDeliveryStatus(new DeliveryStatus("utf8string-749691161"));
                serviceInformation.setServiceGenericInformation(serviceGenericInformation);
            }
            {
                IMInformation iMInformation = new IMInformation();
                iMInformation.setTotalNumberOfMessagesSent(new TotalNumberOfMessagesSent(new Integer(1133907667)));
                iMInformation.setTotalNumberOfMessagesExploded(new TotalNumberOfMessagesExploded(new Integer(1111154671)));
                iMInformation.setNumberOfMessagesSuccessfullySent(new NumberOfMessagesSuccessfullySent(new Integer(-282459966)));
                iMInformation.setNumberOfMessagesSuccessfullyExploded(new NumberOfMessagesSuccessfullyExploded(new Integer(1636406677)));
                serviceInformation.setIMInformation(iMInformation);
            }
            {
                DCDInformation dCDInformation = new DCDInformation();
                dCDInformation.setContentID(new ContentID("utf8string-1212975520"));
                dCDInformation.setContentproviderID(new ContentproviderID("utf8string1130267928"));
                serviceInformation.setDCDInformation(dCDInformation);
            }
            {
                diameter.transatel_custom_avps.CSInformation cSInformation = new diameter.transatel_custom_avps.CSInformation();
                cSInformation.setCallType(new diameter.transatel_custom_avps.CallType(diameter.transatel_custom_avps.CallType.Value.MT_VOICE));
                {
                    diameter.transatel_custom_avps.CAPInformation cAPInformation = new diameter.transatel_custom_avps.CAPInformation();
                    cAPInformation.setCAPCellIDAreaIDLAI(new diameter.transatel_custom_avps.CAPCellIDAreaIDLAI("octetstring1120313800"));
                    cAPInformation.setCAPIsFollowingOn(new diameter.transatel_custom_avps.CAPIsFollowingOn(diameter.transatel_custom_avps.CAPIsFollowingOn.Value.True));
                    cAPInformation.setCAPControlMode(new diameter.transatel_custom_avps.CAPControlMode(diameter.transatel_custom_avps.CAPControlMode.Value.LOCAL_CONTROL));
                    cAPInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(815844821)));
                    cAPInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(1237119035)));
                    cAPInformation.setCAPServiceKey(new diameter.transatel_custom_avps.CAPServiceKey(new Integer(422610312)));
                    cAPInformation.setCAPDialedDigits(new diameter.transatel_custom_avps.CAPDialedDigits("utf8string748740762"));
                    cAPInformation.setCAPCalledTON(new diameter.transatel_custom_avps.CAPCalledTON(new Integer(-1415181881)));
                    cAPInformation.setCAPCLI(new diameter.transatel_custom_avps.CAPCLI("utf8string-1300146747"));
                    cAPInformation.setCAPCallingCategory(new diameter.transatel_custom_avps.CAPCallingCategory(new Integer(537995350)));
                    cAPInformation.setCAPLocationNumber(new diameter.transatel_custom_avps.CAPLocationNumber("utf8string1175518842"));
                    cAPInformation.setCAPRedirectingNumber(new diameter.transatel_custom_avps.CAPRedirectingNumber("utf8string-2044235832"));
                    cAPInformation.setCAPRedirectingIndicator(new diameter.transatel_custom_avps.CAPRedirectingIndicator(new Integer(1974250481)));
                    cAPInformation.setCAPOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPOriginalRedirectingReason(new Integer(-1976565497)));
                    cAPInformation.setCAPRedirectionCounter(new diameter.transatel_custom_avps.CAPRedirectionCounter(new Integer(747738532)));
                    cAPInformation.setCAPRedirectingReason(new diameter.transatel_custom_avps.CAPRedirectingReason(new Integer(2087185263)));
                    cAPInformation.setCAPIMSI(new diameter.transatel_custom_avps.CAPIMSI("utf8string26272461"));
                    cAPInformation.setCAPVLRNumber(new diameter.transatel_custom_avps.CAPVLRNumber("utf8string1000409188"));
                    cAPInformation.setCAPCallReference(new diameter.transatel_custom_avps.CAPCallReference("octetstring1170092149"));
                    cAPInformation.setCAPMSCAddress(new diameter.transatel_custom_avps.CAPMSCAddress("utf8string2100943239"));
                    cAPInformation.setCAPCalledNPI(new diameter.transatel_custom_avps.CAPCalledNPI(new Integer(-724771838)));
                    cAPInformation.setCAPCLINPI(new diameter.transatel_custom_avps.CAPCLINPI(new Integer(152159477)));
                    cAPInformation.setCAPCLINOA(new diameter.transatel_custom_avps.CAPCLINOA(new Integer(44658086)));
                    cAPInformation.setCAPCLIR(new diameter.transatel_custom_avps.CAPCLIR(new Integer(2064399670)));
                    cAPInformation.setCAPVersion(new diameter.transatel_custom_avps.CAPVersion(new Integer(-1814404315)));
                    cAPInformation.setCAPBearerCapabilityTransfer(new diameter.transatel_custom_avps.CAPBearerCapabilityTransfer("utf8string935820999"));
                    cAPInformation.setCAPBearerCapabilityTransferRate(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferRate("utf8string1917526718"));
                    cAPInformation.setCAPGMSCAddress(new diameter.transatel_custom_avps.CAPGMSCAddress("utf8string313762657"));
                    cAPInformation.setCAPExtBasicServiceCode(new diameter.transatel_custom_avps.CAPExtBasicServiceCode("utf8string-518858933"));
                    cAPInformation.setCAPBearerCapability(new diameter.transatel_custom_avps.CAPBearerCapability("octetstring1415998319"));
                    cAPInformation.setCAPSMSCAddress(new diameter.transatel_custom_avps.CAPSMSCAddress("utf8string-1316376120"));
                    cAPInformation.setCAPSGSNAddress(new diameter.transatel_custom_avps.CAPSGSNAddress("utf8string-1135388593"));
                    cAPInformation.setCAPIMEI(new diameter.transatel_custom_avps.CAPIMEI("utf8string1633442274"));
                    cAPInformation.setCAPSMStatusReportRequest(new diameter.transatel_custom_avps.CAPSMStatusReportRequest("utf8string-869198257"));
                    cAPInformation.setCAPSMUserDataHeaderIndicator(new diameter.transatel_custom_avps.CAPSMUserDataHeaderIndicator("utf8string966166086"));
                    cAPInformation.setCAPSMReplyPath(new diameter.transatel_custom_avps.CAPSMReplyPath("utf8string166843276"));
                    cAPInformation.setCAPSMVPFormat(new diameter.transatel_custom_avps.CAPSMVPFormat("utf8string-394619202"));
                    cAPInformation.setCAPSMMessageTypeIndicator(new diameter.transatel_custom_avps.CAPSMMessageTypeIndicator("utf8string698321175"));
                    cAPInformation.setCAPSMProtocolID(new diameter.transatel_custom_avps.CAPSMProtocolID("utf8string1281420645"));
                    cAPInformation.setCAPSMDCS(new diameter.transatel_custom_avps.CAPSMDCS("utf8string1787657743"));
                    cAPInformation.setCAPSMValidityPeriod(new diameter.transatel_custom_avps.CAPSMValidityPeriod("utf8string337344882"));
                    cAPInformation.setCAPSMRejectDuplicate(new diameter.transatel_custom_avps.CAPSMRejectDuplicate("utf8string-2061371250"));
                    cAPInformation.setCAPSCCPCallingGT(new diameter.transatel_custom_avps.CAPSCCPCallingGT("utf8string459390321"));
                    cAPInformation.setCAPSCCPCalledGT(new diameter.transatel_custom_avps.CAPSCCPCalledGT("utf8string-1640679778"));
                    cAPInformation.setCAPBearerCapabilityTransferMode(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferMode("utf8string-2056690719"));
                    cAPInformation.setCAPGSMForwardingPending(new diameter.transatel_custom_avps.CAPGSMForwardingPending(new Integer(232454546)));
                    cAPInformation.setCAPTCAPRemoteTransactionId(new diameter.transatel_custom_avps.CAPTCAPRemoteTransactionId("octetstring-1573551990"));
                    cAPInformation.setCAPTCAPLocalTransactionId(new diameter.transatel_custom_avps.CAPTCAPLocalTransactionId("octetstring-1040566159"));
                    {
                        diameter.transatel_custom_avps.CAPERBSInformation cAPERBSInformation = new diameter.transatel_custom_avps.CAPERBSInformation();
                        cAPERBSInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(594655764)));
                        cAPERBSInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(811172445)));
                        cAPERBSInformation.setCAPERBSEventSpecificInformation(new diameter.transatel_custom_avps.CAPERBSEventSpecificInformation("octetstring1671567000"));
                        cAPERBSInformation.setCAPERBSLegId(new diameter.transatel_custom_avps.CAPERBSLegId(new Integer(-1077458923)));
                        cAPERBSInformation.setCAPERBSMessageType(new diameter.transatel_custom_avps.CAPERBSMessageType(new Integer(642242380)));
                        cAPInformation.setCAPERBSInformation(cAPERBSInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPACHInformation cAPACHInformation = new diameter.transatel_custom_avps.CAPACHInformation();
                        cAPACHInformation.setCAPACHBeepTone(new diameter.transatel_custom_avps.CAPACHBeepTone(diameter.transatel_custom_avps.CAPACHBeepTone.Value.False));
                        cAPInformation.setCAPACHInformation(cAPACHInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPConnectInformation cAPConnectInformation = new diameter.transatel_custom_avps.CAPConnectInformation();
                        cAPConnectInformation.setCAPAnnouncementAccessNumber(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumber("utf8string1342177916"));
                        cAPConnectInformation.setCAPAnnouncementAccessNumberNOA(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumberNOA(new Integer(1216563859)));
                        cAPConnectInformation.setCAPConnectDestinationNumber(new diameter.transatel_custom_avps.CAPConnectDestinationNumber("utf8string951697499"));
                        cAPConnectInformation.setCAPConnectDestinationNumberNature(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNature(new Integer(908322901)));
                        cAPConnectInformation.setCAPConnectDestinationNumberNPI(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNPI(new Integer(-1764829561)));
                        cAPConnectInformation.setCAPConnectGenericNumber(new diameter.transatel_custom_avps.CAPConnectGenericNumber("utf8string-56382767"));
                        cAPConnectInformation.setCAPConnectCallingCategory(new diameter.transatel_custom_avps.CAPConnectCallingCategory(new Integer(1978476335)));
                        cAPConnectInformation.setCAPConnectRedirectingNumber(new diameter.transatel_custom_avps.CAPConnectRedirectingNumber("utf8string-998318167"));
                        cAPConnectInformation.setCAPConnectRedirectingIndicator(new diameter.transatel_custom_avps.CAPConnectRedirectingIndicator(new Integer(901739567)));
                        cAPConnectInformation.setCAPConnectOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPConnectOriginalRedirectingReason(new Integer(1521824055)));
                        cAPConnectInformation.setCAPConnectRedirectingCounter(new diameter.transatel_custom_avps.CAPConnectRedirectingCounter(new Integer(-292514897)));
                        cAPConnectInformation.setCAPConnectRedirectingReason(new diameter.transatel_custom_avps.CAPConnectRedirectingReason(new Integer(1347152727)));
                        cAPConnectInformation.setCAPConnectoCSIApplicable(new diameter.transatel_custom_avps.CAPConnectoCSIApplicable(new Integer(-453635329)));
                        cAPConnectInformation.setCAPConnectSuppressionOfAnnouncement(new diameter.transatel_custom_avps.CAPConnectSuppressionOfAnnouncement(new Integer(-1431817835)));
                        cAPConnectInformation.setCAPConnectGenericNumberNOA(new diameter.transatel_custom_avps.CAPConnectGenericNumberNOA(new Integer(1337312713)));
                        cAPConnectInformation.setCAPConnectGenericNumberNPI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNPI(new Integer(608763939)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumber(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumber("utf8string-437173553"));
                        cAPConnectInformation.setCAPConnectDestinationNumberINN(new diameter.transatel_custom_avps.CAPConnectDestinationNumberINN(new Integer(-1038666941)));
                        cAPConnectInformation.setCAPConnectGenericNumberNQI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNQI(new Integer(690463947)));
                        cAPConnectInformation.setCAPConnectGenericNumberNII(new diameter.transatel_custom_avps.CAPConnectGenericNumberNII(new Integer(-723608315)));
                        cAPConnectInformation.setCAPConnectGenericNumberARI(new diameter.transatel_custom_avps.CAPConnectGenericNumberARI(new Integer(128081205)));
                        cAPConnectInformation.setCAPConnectGenericNumberSCI(new diameter.transatel_custom_avps.CAPConnectGenericNumberSCI(new Integer(-410159223)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberNOA(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNOA(new Integer(-1419816974)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberNPI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNPI(new Integer(-288566740)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberARI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberARI(new Integer(1779898939)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberNOA(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNOA(new Integer(-1421540799)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberNPI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNPI(new Integer(-614390720)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberARI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberARI(new Integer(-688704442)));
                        cAPConnectInformation.setCAPConnectMaxDuration(new diameter.transatel_custom_avps.CAPConnectMaxDuration(new Integer(-1512358831)));
                        cAPInformation.setCAPConnectInformation(cAPConnectInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPRRBSInformation cAPRRBSInformation = new diameter.transatel_custom_avps.CAPRRBSInformation();
                        cAPRRBSInformation.setCAPRRBSNoAnswerTimeout(new diameter.transatel_custom_avps.CAPRRBSNoAnswerTimeout(new Integer(-1993733957)));
                        cAPInformation.setCAPRRBSInformation(cAPRRBSInformation);
                    }
                    cAPInformation.setCAPReleaseCause(new diameter.transatel_custom_avps.CAPReleaseCause(new Integer(-1778136174)));
                    cAPInformation.setCAPSMSpecificInfo(new diameter.transatel_custom_avps.CAPSMSpecificInfo("octetstring1166950398"));
                    cAPInformation.setCAPTCAPErrorCause(new diameter.transatel_custom_avps.CAPTCAPErrorCause(new Integer(-1573615739)));
                    cSInformation.setCAPInformation(cAPInformation);
                }
                serviceInformation.setCSInformation(cSInformation);
            }
            creditControlAnswer.setServiceInformation(serviceInformation);
        }
        {
            diameter.transatel_custom_avps.ServiceControl serviceControl = new diameter.transatel_custom_avps.ServiceControl();
            serviceControl.setSCPAction(new diameter.transatel_custom_avps.SCPAction(diameter.transatel_custom_avps.SCPAction.Value.CONNECT));
            {
                diameter.transatel_custom_avps.CAPInformation cAPInformation = new diameter.transatel_custom_avps.CAPInformation();
                cAPInformation.setCAPCellIDAreaIDLAI(new diameter.transatel_custom_avps.CAPCellIDAreaIDLAI("octetstring162572529"));
                cAPInformation.setCAPIsFollowingOn(new diameter.transatel_custom_avps.CAPIsFollowingOn(diameter.transatel_custom_avps.CAPIsFollowingOn.Value.True));
                cAPInformation.setCAPControlMode(new diameter.transatel_custom_avps.CAPControlMode(diameter.transatel_custom_avps.CAPControlMode.Value.REMOTE_CONTROL));
                cAPInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(650255001)));
                cAPInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(-556911065)));
                cAPInformation.setCAPServiceKey(new diameter.transatel_custom_avps.CAPServiceKey(new Integer(-1104570922)));
                cAPInformation.setCAPDialedDigits(new diameter.transatel_custom_avps.CAPDialedDigits("utf8string-1737593997"));
                cAPInformation.setCAPCalledTON(new diameter.transatel_custom_avps.CAPCalledTON(new Integer(-1089628815)));
                cAPInformation.setCAPCLI(new diameter.transatel_custom_avps.CAPCLI("utf8string1090135701"));
                cAPInformation.setCAPCallingCategory(new diameter.transatel_custom_avps.CAPCallingCategory(new Integer(1070404723)));
                cAPInformation.setCAPLocationNumber(new diameter.transatel_custom_avps.CAPLocationNumber("utf8string1926247075"));
                cAPInformation.setCAPRedirectingNumber(new diameter.transatel_custom_avps.CAPRedirectingNumber("utf8string-93989768"));
                cAPInformation.setCAPRedirectingIndicator(new diameter.transatel_custom_avps.CAPRedirectingIndicator(new Integer(-1757256892)));
                cAPInformation.setCAPOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPOriginalRedirectingReason(new Integer(-1328267660)));
                cAPInformation.setCAPRedirectionCounter(new diameter.transatel_custom_avps.CAPRedirectionCounter(new Integer(1563835649)));
                cAPInformation.setCAPRedirectingReason(new diameter.transatel_custom_avps.CAPRedirectingReason(new Integer(170546794)));
                cAPInformation.setCAPIMSI(new diameter.transatel_custom_avps.CAPIMSI("utf8string-2065091527"));
                cAPInformation.setCAPVLRNumber(new diameter.transatel_custom_avps.CAPVLRNumber("utf8string-1478828543"));
                cAPInformation.setCAPCallReference(new diameter.transatel_custom_avps.CAPCallReference("octetstring-636496786"));
                cAPInformation.setCAPMSCAddress(new diameter.transatel_custom_avps.CAPMSCAddress("utf8string2006984721"));
                cAPInformation.setCAPCalledNPI(new diameter.transatel_custom_avps.CAPCalledNPI(new Integer(-399365364)));
                cAPInformation.setCAPCLINPI(new diameter.transatel_custom_avps.CAPCLINPI(new Integer(176721822)));
                cAPInformation.setCAPCLINOA(new diameter.transatel_custom_avps.CAPCLINOA(new Integer(1672158173)));
                cAPInformation.setCAPCLIR(new diameter.transatel_custom_avps.CAPCLIR(new Integer(-1674244377)));
                cAPInformation.setCAPVersion(new diameter.transatel_custom_avps.CAPVersion(new Integer(-293952837)));
                cAPInformation.setCAPBearerCapabilityTransfer(new diameter.transatel_custom_avps.CAPBearerCapabilityTransfer("utf8string1313318759"));
                cAPInformation.setCAPBearerCapabilityTransferRate(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferRate("utf8string-1631599286"));
                cAPInformation.setCAPGMSCAddress(new diameter.transatel_custom_avps.CAPGMSCAddress("utf8string452475390"));
                cAPInformation.setCAPExtBasicServiceCode(new diameter.transatel_custom_avps.CAPExtBasicServiceCode("utf8string96069819"));
                cAPInformation.setCAPBearerCapability(new diameter.transatel_custom_avps.CAPBearerCapability("octetstring-1490114915"));
                cAPInformation.setCAPSMSCAddress(new diameter.transatel_custom_avps.CAPSMSCAddress("utf8string-518343958"));
                cAPInformation.setCAPSGSNAddress(new diameter.transatel_custom_avps.CAPSGSNAddress("utf8string510827812"));
                cAPInformation.setCAPIMEI(new diameter.transatel_custom_avps.CAPIMEI("utf8string-793615536"));
                cAPInformation.setCAPSMStatusReportRequest(new diameter.transatel_custom_avps.CAPSMStatusReportRequest("utf8string1456276832"));
                cAPInformation.setCAPSMUserDataHeaderIndicator(new diameter.transatel_custom_avps.CAPSMUserDataHeaderIndicator("utf8string-1262094429"));
                cAPInformation.setCAPSMReplyPath(new diameter.transatel_custom_avps.CAPSMReplyPath("utf8string604461633"));
                cAPInformation.setCAPSMVPFormat(new diameter.transatel_custom_avps.CAPSMVPFormat("utf8string1037977886"));
                cAPInformation.setCAPSMMessageTypeIndicator(new diameter.transatel_custom_avps.CAPSMMessageTypeIndicator("utf8string-1336650563"));
                cAPInformation.setCAPSMProtocolID(new diameter.transatel_custom_avps.CAPSMProtocolID("utf8string1707862718"));
                cAPInformation.setCAPSMDCS(new diameter.transatel_custom_avps.CAPSMDCS("utf8string-576267004"));
                cAPInformation.setCAPSMValidityPeriod(new diameter.transatel_custom_avps.CAPSMValidityPeriod("utf8string1052229118"));
                cAPInformation.setCAPSMRejectDuplicate(new diameter.transatel_custom_avps.CAPSMRejectDuplicate("utf8string1470299371"));
                cAPInformation.setCAPSCCPCallingGT(new diameter.transatel_custom_avps.CAPSCCPCallingGT("utf8string-546618662"));
                cAPInformation.setCAPSCCPCalledGT(new diameter.transatel_custom_avps.CAPSCCPCalledGT("utf8string-1574597442"));
                cAPInformation.setCAPBearerCapabilityTransferMode(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferMode("utf8string916810005"));
                cAPInformation.setCAPGSMForwardingPending(new diameter.transatel_custom_avps.CAPGSMForwardingPending(new Integer(-1119478830)));
                cAPInformation.setCAPTCAPRemoteTransactionId(new diameter.transatel_custom_avps.CAPTCAPRemoteTransactionId("octetstring-1065522141"));
                cAPInformation.setCAPTCAPLocalTransactionId(new diameter.transatel_custom_avps.CAPTCAPLocalTransactionId("octetstring-1640941427"));
                {
                    diameter.transatel_custom_avps.CAPERBSInformation cAPERBSInformation = new diameter.transatel_custom_avps.CAPERBSInformation();
                    cAPERBSInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(1003608099)));
                    cAPERBSInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(-1495513140)));
                    cAPERBSInformation.setCAPERBSEventSpecificInformation(new diameter.transatel_custom_avps.CAPERBSEventSpecificInformation("octetstring-1389392444"));
                    cAPERBSInformation.setCAPERBSLegId(new diameter.transatel_custom_avps.CAPERBSLegId(new Integer(2045682109)));
                    cAPERBSInformation.setCAPERBSMessageType(new diameter.transatel_custom_avps.CAPERBSMessageType(new Integer(1908753432)));
                    cAPInformation.setCAPERBSInformation(cAPERBSInformation);
                }
                {
                    diameter.transatel_custom_avps.CAPACHInformation cAPACHInformation = new diameter.transatel_custom_avps.CAPACHInformation();
                    cAPACHInformation.setCAPACHBeepTone(new diameter.transatel_custom_avps.CAPACHBeepTone(diameter.transatel_custom_avps.CAPACHBeepTone.Value.False));
                    cAPInformation.setCAPACHInformation(cAPACHInformation);
                }
                {
                    diameter.transatel_custom_avps.CAPConnectInformation cAPConnectInformation = new diameter.transatel_custom_avps.CAPConnectInformation();
                    cAPConnectInformation.setCAPAnnouncementAccessNumber(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumber("utf8string1094840985"));
                    cAPConnectInformation.setCAPAnnouncementAccessNumberNOA(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumberNOA(new Integer(335202410)));
                    cAPConnectInformation.setCAPConnectDestinationNumber(new diameter.transatel_custom_avps.CAPConnectDestinationNumber("utf8string-1291941140"));
                    cAPConnectInformation.setCAPConnectDestinationNumberNature(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNature(new Integer(139897097)));
                    cAPConnectInformation.setCAPConnectDestinationNumberNPI(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNPI(new Integer(1493748009)));
                    cAPConnectInformation.setCAPConnectGenericNumber(new diameter.transatel_custom_avps.CAPConnectGenericNumber("utf8string-803086743"));
                    cAPConnectInformation.setCAPConnectCallingCategory(new diameter.transatel_custom_avps.CAPConnectCallingCategory(new Integer(356610735)));
                    cAPConnectInformation.setCAPConnectRedirectingNumber(new diameter.transatel_custom_avps.CAPConnectRedirectingNumber("utf8string1736886700"));
                    cAPConnectInformation.setCAPConnectRedirectingIndicator(new diameter.transatel_custom_avps.CAPConnectRedirectingIndicator(new Integer(-1683722541)));
                    cAPConnectInformation.setCAPConnectOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPConnectOriginalRedirectingReason(new Integer(1893205096)));
                    cAPConnectInformation.setCAPConnectRedirectingCounter(new diameter.transatel_custom_avps.CAPConnectRedirectingCounter(new Integer(-1860335137)));
                    cAPConnectInformation.setCAPConnectRedirectingReason(new diameter.transatel_custom_avps.CAPConnectRedirectingReason(new Integer(347165037)));
                    cAPConnectInformation.setCAPConnectoCSIApplicable(new diameter.transatel_custom_avps.CAPConnectoCSIApplicable(new Integer(-1516848570)));
                    cAPConnectInformation.setCAPConnectSuppressionOfAnnouncement(new diameter.transatel_custom_avps.CAPConnectSuppressionOfAnnouncement(new Integer(-1801570989)));
                    cAPConnectInformation.setCAPConnectGenericNumberNOA(new diameter.transatel_custom_avps.CAPConnectGenericNumberNOA(new Integer(-913164039)));
                    cAPConnectInformation.setCAPConnectGenericNumberNPI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNPI(new Integer(-343939288)));
                    cAPConnectInformation.setCAPConnectOriginalCalledNumber(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumber("utf8string-79824586"));
                    cAPConnectInformation.setCAPConnectDestinationNumberINN(new diameter.transatel_custom_avps.CAPConnectDestinationNumberINN(new Integer(1849689081)));
                    cAPConnectInformation.setCAPConnectGenericNumberNQI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNQI(new Integer(32102738)));
                    cAPConnectInformation.setCAPConnectGenericNumberNII(new diameter.transatel_custom_avps.CAPConnectGenericNumberNII(new Integer(-1912908792)));
                    cAPConnectInformation.setCAPConnectGenericNumberARI(new diameter.transatel_custom_avps.CAPConnectGenericNumberARI(new Integer(236295499)));
                    cAPConnectInformation.setCAPConnectGenericNumberSCI(new diameter.transatel_custom_avps.CAPConnectGenericNumberSCI(new Integer(-1099100433)));
                    cAPConnectInformation.setCAPConnectRedirectingNumberNOA(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNOA(new Integer(925820198)));
                    cAPConnectInformation.setCAPConnectRedirectingNumberNPI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNPI(new Integer(789771268)));
                    cAPConnectInformation.setCAPConnectRedirectingNumberARI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberARI(new Integer(1495766109)));
                    cAPConnectInformation.setCAPConnectOriginalCalledNumberNOA(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNOA(new Integer(830164660)));
                    cAPConnectInformation.setCAPConnectOriginalCalledNumberNPI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNPI(new Integer(-583297807)));
                    cAPConnectInformation.setCAPConnectOriginalCalledNumberARI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberARI(new Integer(-83088724)));
                    cAPConnectInformation.setCAPConnectMaxDuration(new diameter.transatel_custom_avps.CAPConnectMaxDuration(new Integer(-1743165474)));
                    cAPInformation.setCAPConnectInformation(cAPConnectInformation);
                }
                {
                    diameter.transatel_custom_avps.CAPRRBSInformation cAPRRBSInformation = new diameter.transatel_custom_avps.CAPRRBSInformation();
                    cAPRRBSInformation.setCAPRRBSNoAnswerTimeout(new diameter.transatel_custom_avps.CAPRRBSNoAnswerTimeout(new Integer(680370709)));
                    cAPInformation.setCAPRRBSInformation(cAPRRBSInformation);
                }
                cAPInformation.setCAPReleaseCause(new diameter.transatel_custom_avps.CAPReleaseCause(new Integer(1318419965)));
                cAPInformation.setCAPSMSpecificInfo(new diameter.transatel_custom_avps.CAPSMSpecificInfo("octetstring-1863458779"));
                cAPInformation.setCAPTCAPErrorCause(new diameter.transatel_custom_avps.CAPTCAPErrorCause(new Integer(-1007566953)));
                serviceControl.setCAPInformation(cAPInformation);
            }
            creditControlAnswer.setServiceControl(serviceControl);
        }
        // add more AVP as ANY values to creditControlAnswer

        byte[] buffer = creditControlAnswer.encode();
        CreditControlAnswer creditControlAnswer2 = new CreditControlAnswer(buffer);
        String s1 = creditControlAnswer.toString();
        String s2 = creditControlAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("creditControlAnswer1 = " + s1);
            System.err.println("creditControlAnswer2 = " + s2);
            throw new VerificationException("CreditControlAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testCreditControlRequest();
        testCreditControlAnswer();
    }
}
