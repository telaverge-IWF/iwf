package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;
import diameter.*;

public class ACTest {

    public static void testACRequest() throws Exception {
        ACRequest aCRequest = new ACRequest(false, false);
        aCRequest.setSessionId(new diameter.base.SessionId("utf8string-2014504669"));
        aCRequest.setOriginHost(new diameter.base.OriginHost("id1109977807.diameter.com"));
        aCRequest.setOriginRealm(new diameter.base.OriginRealm("id-1111920578.diameter.com"));
        aCRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-824986031.diameter.com"));
        aCRequest.setAccountingRecordType(new diameter.base.AccountingRecordType(diameter.base.AccountingRecordType.Value.EVENT_RECORD));
        aCRequest.setAccountingRecordNumber(new diameter.base.AccountingRecordNumber(new Integer(-447260723)));
        aCRequest.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1755595690)));
        aCRequest.setUserName(new diameter.base.UserName("utf8string2049705746"));
        aCRequest.setAcctInterimInterval(new diameter.base.AcctInterimInterval(new Integer(-573896131)));
        aCRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(1581854450)));
        aCRequest.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(-364906623)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-319964282.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring454462252"));
            // add more AVP as ANY values to proxyInfo
            aCRequest.addProxyInfo(proxyInfo);
        }
        aCRequest.addRouteRecord(new diameter.base.RouteRecord("id684914536.diameter.com"));
        aCRequest.setServiceContextId(new ServiceContextId("utf8string-1502082183"));
        {
            ServiceInformation serviceInformation = new ServiceInformation();
            {
                SubscriptionId subscriptionId = new SubscriptionId();
                subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_NAI));
                subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string-1220230148"));
                serviceInformation.addSubscriptionId(subscriptionId);
            }
            {
                AoCInformation aoCInformation = new AoCInformation();
                {
                    AoCCostInformation aoCCostInformation = new AoCCostInformation();
                    {
                        AccumulatedCost accumulatedCost = new AccumulatedCost();
                        accumulatedCost.setValueDigits(new ValueDigits(new Long(-5665284881937656868L)));
                        accumulatedCost.setExponent(new Exponent(new Integer(560795971)));
                        aoCCostInformation.setAccumulatedCost(accumulatedCost);
                    }
                    {
                        IncrementalCost incrementalCost = new IncrementalCost();
                        incrementalCost.setValueDigits(new ValueDigits(new Long(-6503530114638918429L)));
                        incrementalCost.setExponent(new Exponent(new Integer(-835655340)));
                        aoCCostInformation.addIncrementalCost(incrementalCost);
                    }
                    aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(-134050804)));
                    aoCInformation.setAoCCostInformation(aoCCostInformation);
                }
                {
                    TariffInformation tariffInformation = new TariffInformation();
                    {
                        CurrentTariff currentTariff = new CurrentTariff();
                        currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-383855657)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(-8057482530577743351L)));
                            scaleFactor.setExponent(new Exponent(new Integer(-328181680)));
                            currentTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.MONEY));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.COMMUNICATION_ATTEMPT_CHARGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-5977464257699373022L)));
                                unitValue.setExponent(new Exponent(new Integer(1381794235)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(-9036326215316864938L)));
                                unitCost.setExponent(new Exponent(new Integer(-4663940)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-171089624)));
                            currentTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setCurrentTariff(currentTariff);
                    }
                    tariffInformation.setTariffTimeChange(new TariffTimeChange(-1787511280));
                    {
                        NextTariff nextTariff = new NextTariff();
                        nextTariff.setCurrencyCode(new CurrencyCode(new Integer(167680204)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(5923747013931379338L)));
                            scaleFactor.setExponent(new Exponent(new Integer(299635039)));
                            nextTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TOTAL_OCTETS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(6195763669046808235L)));
                                unitValue.setExponent(new Exponent(new Integer(1891293901)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(410428429694036631L)));
                                unitCost.setExponent(new Exponent(new Integer(21745326)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1106954903)));
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
                        aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.AOC_D));
                        aoCSubscriptionInformation.addAoCService(aoCService);
                    }
                    aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.NON_MONETARY));
                    aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(-552963937)));
                    aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                }
                serviceInformation.setAoCInformation(aoCInformation);
            }
            {
                PSInformation pSInformation = new PSInformation();
                pSInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(1744385161)));
                pSInformation.setPDNConnectionID(new PDNConnectionID(new Integer(-498264021)));
                pSInformation.setNodeId(new NodeId("utf8string-701515322"));
                pSInformation.setRo3GPPPDPType(new Ro3GPPPDPType(new Integer(-954002641)));
                pSInformation.addPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "115.169.61.70")));
                pSInformation.setPDPAddressPrefixLength(new PDPAddressPrefixLength(new Integer(-103234822)));
                pSInformation.setDynamicAddressFlag(new DynamicAddressFlag(DynamicAddressFlag.Value.Static));
                pSInformation.setDynamicAddressFlagExtension(new DynamicAddressFlagExtension(DynamicAddressFlagExtension.Value.Dynamic));
                {
                    QoSInformation qoSInformation = new QoSInformation();
                    qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_9));
                    qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-942559253)));
                    qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1489748450)));
                    qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-1350528652)));
                    qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-2118497127)));
                    qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring1931660382"));
                    {
                        AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                        allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1330103761)));
                        allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                        allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                        qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                    }
                    qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(948976446)));
                    qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1612185378)));
                    // add more AVP as ANY values to qoSInformation
                    pSInformation.setQoSInformation(qoSInformation);
                }
                pSInformation.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "177.196.7.183")));
                pSInformation.setGGSNAddress(new GGSNAddress(new Address(Address.Family.IPV4, "94.143.209.134")));
                pSInformation.setSGWAddress(new SGWAddress(new Address(Address.Family.IPV4, "173.200.142.207")));
                pSInformation.setCGAddress(new CGAddress(new Address(Address.Family.IPV4, "166.200.143.75")));
                pSInformation.setServingNodeType(new ServingNodeType(ServingNodeType.Value.GTPSGW));
                pSInformation.setSGWChange(new SGWChange(SGWChange.Value.ACR_Start_NOT_due_to_SGW_Change));
                pSInformation.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-276014004"));
                pSInformation.setIMSIUnauthenticatedFlag(new IMSIUnauthenticatedFlag(IMSIUnauthenticatedFlag.Value.Authenticated));
                pSInformation.setRo3GPPGGSNMCCMNC(new Ro3GPPGGSNMCCMNC("utf8string846672113"));
                pSInformation.setRo3GPPNSAPI(new Ro3GPPNSAPI("utf8string-1193045923"));
                pSInformation.setCalledStationId(new diameter.nasreq.CalledStationId("utf8string1934816356"));
                pSInformation.setRo3GPPSessionStopIndicator(new Ro3GPPSessionStopIndicator("octetstring-1519848919"));
                pSInformation.setRo3GPPSelectionMode(new Ro3GPPSelectionMode("utf8string-1360375294"));
                pSInformation.setRo3GPPChargingCharacteristics(new Ro3GPPChargingCharacteristics("utf8string-2101865864"));
                pSInformation.setRo3GPPSGSNMCCMNC(new Ro3GPPSGSNMCCMNC("utf8string2075139554"));
                pSInformation.setRo3GPPMSTimeZone(new Ro3GPPMSTimeZone("octetstring231899579"));
                pSInformation.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring-228021822"));
                pSInformation.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring294293840"));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(-1500847423)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.Closed_mode));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.CSG_Member));
                    pSInformation.setUserCSGInformation(userCSGInformation);
                }
                pSInformation.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string1637930184"));
                pSInformation.setRo3GPPRATType(new Ro3GPPRATType("octetstring-91884878"));
                {
                    PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                    pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-1844543740)));
                    pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring2108730370"));
                    pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                    pSInformation.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                }
                pSInformation.setPDPContextType(new PDPContextType(PDPContextType.Value.PRIMARY));
                {
                    OfflineCharging offlineCharging = new OfflineCharging();
                    offlineCharging.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(1617668235)));
                    {
                        TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                        timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.CONTINUOUS_TIME_PERIOD));
                        timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(909751863)));
                        offlineCharging.setTimeQuotaMechanism(timeQuotaMechanism);
                    }
                    offlineCharging.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_EVENTS));
                    {
                        MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
                        {
                            GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                            grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(1352420969));
                            grantedServiceUnit.setCCTime(new CCTime(new Integer(510758269)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-4385041778554299284L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1522764927)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(1508438050)));
                                grantedServiceUnit.setCCMoney(cCMoney);
                            }
                            grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-3596862727362674080L)));
                            grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-63076478576573085L)));
                            grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(7848294328745612721L)));
                            grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-6812173332427168830L)));
                            // add more AVP as ANY values to grantedServiceUnit
                            multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
                        }
                        {
                            RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                            requestedServiceUnit.setCCTime(new CCTime(new Integer(-444698158)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(9127789679846946799L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1803143993)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-1709680727)));
                                requestedServiceUnit.setCCMoney(cCMoney);
                            }
                            requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-8996599505595269352L)));
                            requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(855040888008197185L)));
                            requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(3393674259267765797L)));
                            requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-4580724718920628408L)));
                            // add more AVP as ANY values to requestedServiceUnit
                            multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
                        }
                        {
                            UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                            usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.POOL_EXHAUSTED));
                            usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                            usedServiceUnit.setCCTime(new CCTime(new Integer(-1457055442)));
                            usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(6231578172190784592L)));
                            usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(2949562681770963667L)));
                            usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(4856972716595056594L)));
                            usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-3796668134411751980L)));
                            usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(-212495615));
                            multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
                        }
                        multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(2044694399)));
                        multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(2020934546)));
                        {
                            GSUPoolReference gSUPoolReference = new GSUPoolReference();
                            gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(1783333269)));
                            gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(3239929367413248033L)));
                                unitValue.setExponent(new Exponent(new Integer(981651131)));
                                gSUPoolReference.setUnitValue(unitValue);
                            }
                            multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
                        }
                        multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(-1280063987)));
                        multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(-2115235058)));
                        {
                            FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                            finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.REDIRECT));
                            finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                            finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string1165707535"));
                            {
                                RedirectServer redirectServer = new RedirectServer();
                                redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv4_Address));
                                redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string666522623"));
                                finalUnitIndication.setRedirectServer(redirectServer);
                            }
                            multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
                        }
                        multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(231608951)));
                        multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(-366912600)));
                        multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1920885909)));
                        multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(-825914240)));
                        multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(-967232828)));
                        multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.QUOTA_EXHAUSTED));
                        {
                            Trigger trigger = new Trigger();
                            trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_MEAN_THROUGHPUT));
                            multipleServicesCreditControl.setTrigger(trigger);
                        }
                        {
                            PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                            pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(1419768477)));
                            pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring350066099"));
                            pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                            multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                        }
                        multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring274629257"));
                        {
                            AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                            aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring1039811229"));
                            {
                                Flows flows = new Flows();
                                flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(-749010142)));
                                flows.addFlowNumber(new FlowNumber(new Integer(15595311)));
                                aFCorrelationInformation.addFlows(flows);
                            }
                            multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
                        }
                        {
                            Envelope envelope = new Envelope();
                            envelope.setEnvelopeStartTime(new EnvelopeStartTime(-1827994281));
                            envelope.setEnvelopeEndTime(new EnvelopeEndTime(1350008457));
                            envelope.setCCTotalOctets(new CCTotalOctets(new Long(8241217095768615525L)));
                            envelope.setCCInputOctets(new CCInputOctets(new Long(4360511566303371759L)));
                            envelope.setCCOutputOctets(new CCOutputOctets(new Long(-6377416831469772528L)));
                            envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(5072088485096934883L)));
                            // add more AVP as ANY values to envelope
                            multipleServicesCreditControl.addEnvelope(envelope);
                        }
                        multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME_AND_EVENTS));
                        {
                            TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                            timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.CONTINUOUS_TIME_PERIOD));
                            timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(2023243411)));
                            multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
                        }
                        {
                            ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                            serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string1580904774"));
                            serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1600077273)));
                            multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
                        }
                        {
                            QoSInformation qoSInformation = new QoSInformation();
                            qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_4));
                            qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1441439337)));
                            qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(1649029450)));
                            qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1652145229)));
                            qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(260273677)));
                            qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring291400238"));
                            {
                                AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                                allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(18978357)));
                                allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                                allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                                qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                            }
                            qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(95243590)));
                            qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-370229148)));
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
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-807406170)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1162932933)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-1257952878)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(2089924753)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-32771815"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1914044109)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1925291231)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-623560627)));
                        // add more AVP as ANY values to qoSInformation
                        trafficDataVolumes.setQoSInformation(qoSInformation);
                    }
                    trafficDataVolumes.setAccountingInputOctets(new AccountingInputOctets(new Long(-1902880822274589245L)));
                    trafficDataVolumes.setAccountingInputPackets(new AccountingInputPackets(new Long(5553434613718127914L)));
                    trafficDataVolumes.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-497262546749299632L)));
                    trafficDataVolumes.setAccountingOutputPackets(new AccountingOutputPackets(new Long(453461106669641420L)));
                    trafficDataVolumes.setChangeCondition(new ChangeCondition(new Integer(-2142426550)));
                    trafficDataVolumes.setChangeTime(new ChangeTime(2127824094));
                    trafficDataVolumes.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring104170375"));
                    pSInformation.addTrafficDataVolumes(trafficDataVolumes);
                }
                {
                    ServiceDataContainer serviceDataContainer = new ServiceDataContainer();
                    {
                        AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                        aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring2057416352"));
                        {
                            Flows flows = new Flows();
                            flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(328208402)));
                            flows.addFlowNumber(new FlowNumber(new Integer(-349887292)));
                            aFCorrelationInformation.addFlows(flows);
                        }
                        serviceDataContainer.setAFCorrelationInformation(aFCorrelationInformation);
                    }
                    serviceDataContainer.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring2143358812"));
                    serviceDataContainer.setAccountingInputOctets(new AccountingInputOctets(new Long(-2610999874227805657L)));
                    serviceDataContainer.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-3182590182345201470L)));
                    serviceDataContainer.setAccountingInputPackets(new AccountingInputPackets(new Long(7552980795978398778L)));
                    serviceDataContainer.setAccountingOutputPackets(new AccountingOutputPackets(new Long(8797418354610834194L)));
                    serviceDataContainer.setLocalSequenceNumber(new LocalSequenceNumber(new Integer(1072189651)));
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_3));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1293108118)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1319888101)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(2113435455)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-1041987317)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring266121023"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1328586681)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-1566416392)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(2021583872)));
                        // add more AVP as ANY values to qoSInformation
                        serviceDataContainer.setQoSInformation(qoSInformation);
                    }
                    serviceDataContainer.setRatingGroup(new RatingGroup(new Integer(2119336399)));
                    serviceDataContainer.setChangeTime(new ChangeTime(-1849262399));
                    serviceDataContainer.setServiceIdentifier(new ServiceIdentifier(new Integer(1717501729)));
                    {
                        ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                        serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-1052290225"));
                        serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1632402974)));
                        serviceDataContainer.setServiceSpecificInfo(serviceSpecificInfo);
                    }
                    serviceDataContainer.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "98.206.198.70")));
                    serviceDataContainer.setTimeFirstUsage(new TimeFirstUsage(1041384478));
                    serviceDataContainer.setTimeLastUsage(new TimeLastUsage(380086274));
                    serviceDataContainer.setTimeUsage(new TimeUsage(-1908910944));
                    serviceDataContainer.addChangeCondition(new ChangeCondition(new Integer(1620908749)));
                    serviceDataContainer.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring1240676511"));
                    serviceDataContainer.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string-1773916132"));
                    pSInformation.addServiceDataContainer(serviceDataContainer);
                }
                {
                    UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
                    userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.IMEISV));
                    userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring-1034842166"));
                    pSInformation.setUserEquipmentInfo(userEquipmentInfo);
                }
                {
                    TerminalInformation terminalInformation = new TerminalInformation();
                    terminalInformation.setIMEI(new IMEI("utf8string1593895655"));
                    terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string712234385"));
                    // add more AVP as ANY values to terminalInformation
                    pSInformation.setTerminalInformation(terminalInformation);
                }
                pSInformation.setStartTime(new StartTime(103309651));
                pSInformation.setStopTime(new StopTime(187748026));
                pSInformation.setChangeCondition(new ChangeCondition(new Integer(1901703828)));
                pSInformation.setDiagnostics(new Diagnostics(new Integer(1605945307)));
                pSInformation.setLowPriorityIndicator(new LowPriorityIndicator(LowPriorityIndicator.Value.NO));
                serviceInformation.setPSInformation(pSInformation);
            }
            {
                WLANInformation wLANInformation = new WLANInformation();
                wLANInformation.setWLANSessionId(new WLANSessionId(new Integer(-1272537452)));
                wLANInformation.setPDGAddress(new PDGAddress(new Address(Address.Family.IPV4, "101.176.167.26")));
                wLANInformation.setPDGChargingId(new PDGChargingId(new Integer(-2073910276)));
                wLANInformation.setWAGAddress(new WAGAddress(new Address(Address.Family.IPV4, "119.132.113.229")));
                wLANInformation.setWAGPLMNId(new WAGPLMNId("octetstring-2038802441"));
                {
                    WLANRadioContainer wLANRadioContainer = new WLANRadioContainer();
                    wLANRadioContainer.setOperatorName(new OperatorName("octetstring-1590033538"));
                    wLANRadioContainer.setLocationInformation(new LocationInformation("octetstring-1108883469"));
                    {
                        LocationType locationType = new LocationType();
                        locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.INITIAL_LOCATION));
                        locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string-78910639"));
                        wLANRadioContainer.setLocationType(locationType);
                    }
                    wLANRadioContainer.setWLANTechnology(new WLANTechnology(new Integer(-318296728)));
                    wLANInformation.setWLANRadioContainer(wLANRadioContainer);
                }
                wLANInformation.setWLANUELocalIPAddress(new WLANUELocalIPAddress(new Address(Address.Family.IPV4, "68.56.48.223")));
                serviceInformation.setWLANInformation(wLANInformation);
            }
            {
                IMSInformation iMSInformation = new IMSInformation();
                {
                    EventType eventType = new EventType();
                    eventType.setSIPMethod(new SIPMethod("utf8string-511257949"));
                    eventType.setIMSEvent(new IMSEvent("utf8string1222649318"));
                    eventType.setExpires(new Expires(new Integer(-1222881986)));
                    iMSInformation.setEventType(eventType);
                }
                iMSInformation.setRoleOfNode(new RoleOfNode(RoleOfNode.Value.TERMINATING_ROLE));
                iMSInformation.setNodeFunctionality(new NodeFunctionality(NodeFunctionality.Value.I_CSCF));
                iMSInformation.setUserSessionID(new UserSessionID("utf8string1876055348"));
                iMSInformation.setOutgoingSessionId(new OutgoingSessionId("utf8string-1721630503"));
                iMSInformation.addCallingPartyAddress(new CallingPartyAddress("utf8string790815346"));
                iMSInformation.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY_2));
                iMSInformation.setCalledPartyAddress(new CalledPartyAddress("utf8string1952099122"));
                iMSInformation.addCalledAssertedIdentity(new CalledAssertedIdentity("utf8string-985768698"));
                iMSInformation.setNumberPortabilityRoutingInformation(new NumberPortabilityRoutingInformation("utf8string280059265"));
                iMSInformation.setCarrierSelectRoutingInformation(new CarrierSelectRoutingInformation("utf8string1236449460"));
                iMSInformation.setAlternateChargedPartyAddress(new AlternateChargedPartyAddress("utf8string11917873"));
                iMSInformation.setRequestedPartyAddress(new RequestedPartyAddress("utf8string124736677"));
                iMSInformation.addAssociatedURI(new AssociatedURI("utf8string-1628440057"));
                {
                    TimeStamps timeStamps = new TimeStamps();
                    timeStamps.setSIPRequestTimestamp(new SIPRequestTimestamp(-921631595));
                    timeStamps.setSIPResponseTimestamp(new SIPResponseTimestamp(675957381));
                    timeStamps.setSIPRequestTimestampFraction(new SIPRequestTimestampFraction(new Integer(677915622)));
                    timeStamps.setSIPResponseTimestampFraction(new SIPResponseTimestampFraction(new Integer(143413874)));
                    iMSInformation.setTimeStamps(timeStamps);
                }
                {
                    ApplicationServerInformation applicationServerInformation = new ApplicationServerInformation();
                    applicationServerInformation.setApplicationServer(new ApplicationServer("utf8string-1615130120"));
                    applicationServerInformation.addApplicationProvidedCalledPartyAddress(new ApplicationProvidedCalledPartyAddress("utf8string2001342092"));
                    iMSInformation.addApplicationServerInformation(applicationServerInformation);
                }
                {
                    InterOperatorIdentifier interOperatorIdentifier = new InterOperatorIdentifier();
                    interOperatorIdentifier.setOriginatingIOI(new OriginatingIOI("utf8string-2127432197"));
                    interOperatorIdentifier.setTerminatingIOI(new TerminatingIOI("utf8string-1938222833"));
                    iMSInformation.addInterOperatorIdentifier(interOperatorIdentifier);
                }
                iMSInformation.setIMSChargingIdentifier(new IMSChargingIdentifier("utf8string113064883"));
                iMSInformation.addSDPSessionDescription(new SDPSessionDescription("utf8string-491678993"));
                {
                    SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                    sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string1944697358"));
                    sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string-976821259"));
                    sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Not_Inserted));
                    sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                    sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_Realm_Not_used));
                    sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.called_party));
                    sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string210110813"));
                    sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string-1966147005"));
                    sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-1885839068)));
                    sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring860202210"));
                    sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Offer));
                    iMSInformation.addSDPMediaComponent(sDPMediaComponent);
                }
                iMSInformation.setServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "231.99.119.19")));
                {
                    ServerCapabilities serverCapabilities = new ServerCapabilities();
                    serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(-482250345)));
                    serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(348982976)));
                    serverCapabilities.addServerName(new ServerName("utf8string80764662"));
                    // add more AVP as ANY values to serverCapabilities
                    iMSInformation.setServerCapabilities(serverCapabilities);
                }
                {
                    TrunkGroupID trunkGroupID = new TrunkGroupID();
                    trunkGroupID.setIncomingTrunkGroupID(new IncomingTrunkGroupID("utf8string1474764168"));
                    trunkGroupID.setOutgoingTrunkGroupID(new OutgoingTrunkGroupID("utf8string2055835701"));
                    iMSInformation.setTrunkGroupID(trunkGroupID);
                }
                iMSInformation.setBearerService(new BearerService("octetstring258576198"));
                iMSInformation.setServiceId(new ServiceId("utf8string1139292782"));
                {
                    ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                    serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string1958826664"));
                    serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(-277149240)));
                    iMSInformation.addServiceSpecificInfo(serviceSpecificInfo);
                }
                {
                    MessageBody messageBody = new MessageBody();
                    messageBody.setContentType(new ContentType("utf8string637488878"));
                    messageBody.setContentLength(new ContentLength(new Integer(2105838415)));
                    messageBody.setContentDisposition(new ContentDisposition("utf8string815692621"));
                    messageBody.setOriginator(new Originator(Originator.Value.Calling_Party));
                    iMSInformation.addMessageBody(messageBody);
                }
                iMSInformation.setCauseCode(new CauseCode(new Integer(-342256555)));
                iMSInformation.setAccessNetworkInformation(new AccessNetworkInformation("octetstring-277799926"));
                {
                    EarlyMediaDescription earlyMediaDescription = new EarlyMediaDescription();
                    {
                        SDPTimeStamps sDPTimeStamps = new SDPTimeStamps();
                        sDPTimeStamps.setSDPOfferTimestamp(new SDPOfferTimestamp(1966353604));
                        sDPTimeStamps.setSDPAnswerTimestamp(new SDPAnswerTimestamp(-2110543885));
                        earlyMediaDescription.setSDPTimeStamps(sDPTimeStamps);
                    }
                    {
                        SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                        sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string-1983437137"));
                        sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string133061364"));
                        sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                        sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                        sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_Realm_Not_used));
                        sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.unknown));
                        sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string448927587"));
                        sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string1858980349"));
                        sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(1632616055)));
                        sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring403328843"));
                        sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Offer));
                        earlyMediaDescription.addSDPMediaComponent(sDPMediaComponent);
                    }
                    earlyMediaDescription.addSDPSessionDescription(new SDPSessionDescription("utf8string-2103438390"));
                    iMSInformation.addEarlyMediaDescription(earlyMediaDescription);
                }
                iMSInformation.setIMSCommunicationServiceIdentifier(new IMSCommunicationServiceIdentifier("utf8string-372919978"));
                iMSInformation.setOnlineChargingFlag(new OnlineChargingFlag(OnlineChargingFlag.Value.ECF_address_provided));
                {
                    RealTimeTariffInformation realTimeTariffInformation = new RealTimeTariffInformation();
                    {
                        TariffInformation tariffInformation = new TariffInformation();
                        {
                            CurrentTariff currentTariff = new CurrentTariff();
                            currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-949280683)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(7196570841113746608L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-709795167)));
                                currentTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.INPUT_OCTETS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-7731905703016292379L)));
                                    unitValue.setExponent(new Exponent(new Integer(421995452)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(5282889538426187830L)));
                                    unitCost.setExponent(new Exponent(new Integer(-1674461018)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1167428265)));
                                currentTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setCurrentTariff(currentTariff);
                        }
                        tariffInformation.setTariffTimeChange(new TariffTimeChange(1145987971));
                        {
                            NextTariff nextTariff = new NextTariff();
                            nextTariff.setCurrencyCode(new CurrencyCode(new Integer(1128899116)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(6973657405366846096L)));
                                scaleFactor.setExponent(new Exponent(new Integer(415433772)));
                                nextTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.MONEY));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.ADD_ON_CHARGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-4974080271353118556L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1883238424)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(1596967868979652894L)));
                                    unitCost.setExponent(new Exponent(new Integer(-1959629474)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(562047968)));
                                nextTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setNextTariff(nextTariff);
                        }
                        realTimeTariffInformation.setTariffInformation(tariffInformation);
                    }
                    realTimeTariffInformation.setTariffXML(new TariffXML("utf8string979191153"));
                    iMSInformation.setRealTimeTariffInformation(realTimeTariffInformation);
                }
                iMSInformation.setAccountExpiration(new AccountExpiration(-44013727));
                iMSInformation.setInitialIMSChargingIdentifier(new InitialIMSChargingIdentifier("utf8string2110295459"));
                serviceInformation.setIMSInformation(iMSInformation);
            }
            {
                MMSInformation mMSInformation = new MMSInformation();
                {
                    OriginatorAddress originatorAddress = new OriginatorAddress();
                    originatorAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.e_mail_address));
                    originatorAddress.setAddressData(new AddressData("utf8string-1518000303"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string1710761349"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1560149798"));
                        originatorAddress.setAddressDomain(addressDomain);
                    }
                    mMSInformation.setOriginatorAddress(originatorAddress);
                }
                {
                    RecipientAddress recipientAddress = new RecipientAddress();
                    recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.Alphanumeric_Shortcode));
                    recipientAddress.setAddressData(new AddressData("utf8string-2036001013"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-1759081751"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-130613239"));
                        recipientAddress.setAddressDomain(addressDomain);
                    }
                    recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.CC));
                    mMSInformation.addRecipientAddress(recipientAddress);
                }
                mMSInformation.setSubmissionTime(new SubmissionTime(-1335346828));
                {
                    MMContentType mMContentType = new MMContentType();
                    mMContentType.setTypeNumber(new TypeNumber(new Integer(-1515581896)));
                    mMContentType.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string233271195"));
                    mMContentType.setContentSize(new ContentSize(new Integer(995528808)));
                    {
                        AdditionalContentInformation additionalContentInformation = new AdditionalContentInformation();
                        additionalContentInformation.setTypeNumber(new TypeNumber(new Integer(-1610028547)));
                        additionalContentInformation.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string-978283266"));
                        additionalContentInformation.setContentSize(new ContentSize(new Integer(-1043674781)));
                        mMContentType.addAdditionalContentInformation(additionalContentInformation);
                    }
                    mMSInformation.setMMContentType(mMContentType);
                }
                mMSInformation.setPriority(new Priority(Priority.Value.High));
                mMSInformation.setMessageID(new MessageID("utf8string-25436581"));
                mMSInformation.setMessageType(new MessageType(MessageType.Value.m_read_orig_ind));
                mMSInformation.setMessageSize(new MessageSize(new Integer(-1771691296)));
                {
                    MessageClass messageClass = new MessageClass();
                    messageClass.setClassIdentifier(new ClassIdentifier(ClassIdentifier.Value.Advertisement));
                    messageClass.setTokenText(new TokenText("utf8string-1833475990"));
                    mMSInformation.setMessageClass(messageClass);
                }
                mMSInformation.setDeliveryReportRequested(new DeliveryReportRequested(DeliveryReportRequested.Value.No));
                mMSInformation.setReadReplyReportRequested(new ReadReplyReportRequested(ReadReplyReportRequested.Value.Yes));
                mMSInformation.setMMBoxStorageRequested(new MMBoxStorageRequested(MMBoxStorageRequested.Value.No));
                mMSInformation.setApplicID(new ApplicID("utf8string-1239825842"));
                mMSInformation.setReplyApplicID(new ReplyApplicID("utf8string-124403979"));
                mMSInformation.setAuxApplicInfo(new AuxApplicInfo("utf8string1624015021"));
                mMSInformation.setContentClass(new ContentClass(ContentClass.Value.megapixel));
                mMSInformation.setDRMContent(new DRMContent(DRMContent.Value.Yes));
                mMSInformation.setAdaptations(new Adaptations(Adaptations.Value.Yes));
                mMSInformation.setVASPId(new VASPId("utf8string811699772"));
                mMSInformation.setVASId(new VASId("utf8string-1656537061"));
                serviceInformation.setMMSInformation(mMSInformation);
            }
            {
                LCSInformation lCSInformation = new LCSInformation();
                {
                    LCSClientID lCSClientID = new LCSClientID();
                    lCSClientID.setLCSClientType(new LCSClientType(LCSClientType.Value.LAWFUL_INTERCEPT_SERVICES));
                    lCSClientID.setLCSClientExternalID(new LCSClientExternalID("utf8string-1333438453"));
                    lCSClientID.setLCSClientDialedByMS(new LCSClientDialedByMS("utf8string2078621768"));
                    {
                        LCSClientName lCSClientName = new LCSClientName();
                        lCSClientName.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string-1895919658"));
                        lCSClientName.setLCSNameString(new LCSNameString("utf8string-186773828"));
                        lCSClientName.setLCSFormatIndicator(new LCSFormatIndicator(LCSFormatIndicator.Value.SIP_URL));
                        lCSClientID.setLCSClientName(lCSClientName);
                    }
                    lCSClientID.setLCSAPN(new LCSAPN("utf8string-663680663"));
                    {
                        LCSRequestorID lCSRequestorID = new LCSRequestorID();
                        lCSRequestorID.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string1516655806"));
                        lCSRequestorID.setLCSRequestorIDString(new LCSRequestorIDString("utf8string-1265878494"));
                        lCSClientID.setLCSRequestorID(lCSRequestorID);
                    }
                    lCSInformation.setLCSClientID(lCSClientID);
                }
                {
                    LocationType locationType = new LocationType();
                    locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.ACTIVATE_DEFERRED_LOCATION));
                    locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string1640943292"));
                    lCSInformation.setLocationType(locationType);
                }
                lCSInformation.setLocationEstimate(new LocationEstimate("utf8string885367850"));
                lCSInformation.setPositioningData(new PositioningData("utf8string456745692"));
                lCSInformation.setRo3GPPIMSI(new Ro3GPPIMSI("utf8string1849099051"));
                lCSInformation.setMSISDN(new MSISDN("octetstring-2005261338"));
                serviceInformation.setLCSInformation(lCSInformation);
            }
            {
                PoCInformation poCInformation = new PoCInformation();
                poCInformation.setPoCServerRole(new PoCServerRole(PoCServerRole.Value.Participating_PoC_Server));
                poCInformation.setPoCSessionType(new PoCSessionType(PoCSessionType.Value.One_to_one_PoC_session));
                {
                    PoCUserRole poCUserRole = new PoCUserRole();
                    poCUserRole.setPoCUserRoleIds(new PoCUserRoleIds("utf8string607034871"));
                    poCUserRole.setPoCUserRoleinfoUnits(new PoCUserRoleinfoUnits(PoCUserRoleinfoUnits.Value.Dispatcher));
                    poCInformation.setPoCUserRole(poCUserRole);
                }
                poCInformation.setPoCSessionInitiationType(new PoCSessionInitiationType(PoCSessionInitiationType.Value.Pre_established));
                poCInformation.setPoCEventType(new PoCEventType(PoCEventType.Value.Early_Ssession_Setting_up_event));
                poCInformation.setNumberOfParticipants(new NumberOfParticipants(new Integer(942800654)));
                poCInformation.addParticipantsInvolved(new ParticipantsInvolved("utf8string576177878"));
                {
                    ParticipantGroup participantGroup = new ParticipantGroup();
                    participantGroup.setCalledPartyAddress(new CalledPartyAddress("utf8string-1561612646"));
                    participantGroup.setParticipantAccessPriority(new ParticipantAccessPriority(ParticipantAccessPriority.Value.Low_priority));
                    participantGroup.setUserParticipatingType(new UserParticipatingType(UserParticipatingType.Value.Normal));
                    poCInformation.addParticipantGroup(participantGroup);
                }
                {
                    TalkBurstExchange talkBurstExchange = new TalkBurstExchange();
                    talkBurstExchange.setPoCChangeTime(new PoCChangeTime(-1894292430));
                    talkBurstExchange.setNumberOfTalkBursts(new NumberOfTalkBursts(new Integer(54498702)));
                    talkBurstExchange.setTalkBurstVolume(new TalkBurstVolume(new Integer(-1294917870)));
                    talkBurstExchange.setTalkBurstTime(new TalkBurstTime(new Integer(1831275252)));
                    talkBurstExchange.setNumberOfReceivedTalkBursts(new NumberOfReceivedTalkBursts(new Integer(-21548452)));
                    talkBurstExchange.setReceivedTalkBurstVolume(new ReceivedTalkBurstVolume(new Integer(-1482709956)));
                    talkBurstExchange.setReceivedTalkBurstTime(new ReceivedTalkBurstTime(new Integer(1086964257)));
                    talkBurstExchange.setNumberOfParticipants(new NumberOfParticipants(new Integer(-1631833776)));
                    talkBurstExchange.setPoCChangeCondition(new PoCChangeCondition(PoCChangeCondition.Value.timeLimit));
                    poCInformation.addTalkBurstExchange(talkBurstExchange);
                }
                poCInformation.setPoCControllingAddress(new PoCControllingAddress("utf8string-1985136548"));
                poCInformation.setPoCGroupName(new PoCGroupName("utf8string-2110603205"));
                poCInformation.setPoCSessionId(new PoCSessionId("utf8string443889143"));
                poCInformation.setChargedParty(new ChargedParty("utf8string2063751714"));
                serviceInformation.setPoCInformation(poCInformation);
            }
            {
                MBMSInformation mBMSInformation = new MBMSInformation();
                mBMSInformation.setTMGI(new TMGI("octetstring1103388574"));
                mBMSInformation.setMBMSServiceType(new MBMSServiceType(MBMSServiceType.Value.MULTICAST));
                mBMSInformation.setMBMSUserServiceType(new MBMSUserServiceType(MBMSUserServiceType.Value.STREAMING));
                mBMSInformation.setFileRepairSupported(new FileRepairSupported(FileRepairSupported.Value.SUPPORTED));
                mBMSInformation.setRequiredMBMSBearerCapabilities(new RequiredMBMSBearerCapabilities("utf8string65279013"));
                mBMSInformation.setMBMS2G3GIndicator(new MBMS2G3GIndicator(MBMS2G3GIndicator.Value.ONLY_3G));
                mBMSInformation.setRAI(new RAI("utf8string483556549"));
                mBMSInformation.addMBMSServiceArea(new MBMSServiceArea("octetstring-1299623467"));
                mBMSInformation.setMBMSSessionIdentity(new MBMSSessionIdentity("octetstring-377926602"));
                mBMSInformation.setCNIPMulticastDistribution(new CNIPMulticastDistribution(CNIPMulticastDistribution.Value.NO_IP_MULTICAST));
                mBMSInformation.setMBMSGWAddress(new MBMSGWAddress(new Address(Address.Family.IPV4, "98.222.44.10")));
                serviceInformation.setMBMSInformation(mBMSInformation);
            }
            {
                SMSInformation sMSInformation = new SMSInformation();
                sMSInformation.setSMSNode(new SMSNode(SMSNode.Value.IP_SM_GW));
                sMSInformation.setClientAddress(new ClientAddress(new Address(Address.Family.IPV4, "166.175.187.152")));
                sMSInformation.setOriginatorSCCPAddress(new OriginatorSCCPAddress(new Address(Address.Family.IPV4, "53.37.157.91")));
                sMSInformation.setSMSCAddress(new SMSCAddress(new Address(Address.Family.IPV4, "202.103.26.187")));
                sMSInformation.setDataCodingScheme(new DataCodingScheme(new Integer(598758691)));
                sMSInformation.setSMDischargeTime(new SMDischargeTime(-1821211720));
                sMSInformation.setSMMessageType(new SMMessageType(SMMessageType.Value.SM_Service_Request));
                {
                    OriginatorInterface originatorInterface = new OriginatorInterface();
                    originatorInterface.setInterfaceId(new InterfaceId("utf8string991228643"));
                    originatorInterface.setInterfaceText(new InterfaceText("utf8string-1858771973"));
                    originatorInterface.setInterfacePort(new InterfacePort("utf8string1470935538"));
                    originatorInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.APPLICATION_TERMINATION));
                    sMSInformation.setOriginatorInterface(originatorInterface);
                }
                sMSInformation.setSMProtocolID(new SMProtocolID("octetstring1605055021"));
                sMSInformation.setReplyPathRequested(new ReplyPathRequested(ReplyPathRequested.Value.Reply_path_Set));
                sMSInformation.setSMStatus(new SMStatus("octetstring1213005057"));
                sMSInformation.setSMUserDataHeader(new SMUserDataHeader("octetstring554935637"));
                sMSInformation.setNumberOfMessagesSent(new NumberOfMessagesSent(new Integer(910185140)));
                {
                    RecipientInfo recipientInfo = new RecipientInfo();
                    {
                        DestinationInterface destinationInterface = new DestinationInterface();
                        destinationInterface.setInterfaceId(new InterfaceId("utf8string19150326"));
                        destinationInterface.setInterfaceText(new InterfaceText("utf8string605781909"));
                        destinationInterface.setInterfacePort(new InterfacePort("utf8string-605625035"));
                        destinationInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.APPLICATION_ORIGINATING));
                        recipientInfo.setDestinationInterface(destinationInterface);
                    }
                    {
                        RecipientAddress recipientAddress = new RecipientAddress();
                        recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IMSI));
                        recipientAddress.setAddressData(new AddressData("utf8string-537148397"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string-859166914"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1618852640"));
                            recipientAddress.setAddressDomain(addressDomain);
                        }
                        recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.BCC));
                        recipientInfo.addRecipientAddress(recipientAddress);
                    }
                    {
                        RecipientReceivedAddress recipientReceivedAddress = new RecipientReceivedAddress();
                        recipientReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv4_Address));
                        recipientReceivedAddress.setAddressData(new AddressData("utf8string-283365189"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string-2016474828"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-852233986"));
                            recipientReceivedAddress.setAddressDomain(addressDomain);
                        }
                        recipientInfo.addRecipientReceivedAddress(recipientReceivedAddress);
                    }
                    recipientInfo.setRecipientSCCPAddress(new RecipientSCCPAddress(new Address(Address.Family.IPV4, "112.5.12.80")));
                    recipientInfo.setSMProtocolID(new SMProtocolID("octetstring250077124"));
                    sMSInformation.addRecipientInfo(recipientInfo);
                }
                {
                    OriginatorReceivedAddress originatorReceivedAddress = new OriginatorReceivedAddress();
                    originatorReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.Numeric_Shortcode));
                    originatorReceivedAddress.setAddressData(new AddressData("utf8string-11869772"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-1036437215"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string492254610"));
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
                    supplementaryService.setServiceType(new ServiceType(new Integer(-1134252557)));
                    supplementaryService.setServiceMode(new ServiceMode(new Integer(1754864830)));
                    supplementaryService.setNumberOfDiversions(new NumberOfDiversions(new Integer(388997601)));
                    supplementaryService.setAssociatedPartyAddress(new AssociatedPartyAddress("utf8string-1383415495"));
                    supplementaryService.setServiceId(new ServiceId("utf8string479654491"));
                    supplementaryService.setChangeTime(new ChangeTime(1800668251));
                    supplementaryService.setNumberOfParticipants(new NumberOfParticipants(new Integer(-1527845018)));
                    supplementaryService.setParticipantActionType(new ParticipantActionType(ParticipantActionType.Value.QUIT_CONF));
                    supplementaryService.setCUGInformation(new CUGInformation("octetstring1056991713"));
                    {
                        AoCInformation aoCInformation = new AoCInformation();
                        {
                            AoCCostInformation aoCCostInformation = new AoCCostInformation();
                            {
                                AccumulatedCost accumulatedCost = new AccumulatedCost();
                                accumulatedCost.setValueDigits(new ValueDigits(new Long(-268044363504494022L)));
                                accumulatedCost.setExponent(new Exponent(new Integer(500031825)));
                                aoCCostInformation.setAccumulatedCost(accumulatedCost);
                            }
                            {
                                IncrementalCost incrementalCost = new IncrementalCost();
                                incrementalCost.setValueDigits(new ValueDigits(new Long(5395789194474955819L)));
                                incrementalCost.setExponent(new Exponent(new Integer(-1802175796)));
                                aoCCostInformation.addIncrementalCost(incrementalCost);
                            }
                            aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(-1649966059)));
                            aoCInformation.setAoCCostInformation(aoCCostInformation);
                        }
                        {
                            TariffInformation tariffInformation = new TariffInformation();
                            {
                                CurrentTariff currentTariff = new CurrentTariff();
                                currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-426496200)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(-3181984878627918824L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(847421431)));
                                    currentTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.SETUP_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(-365881081641165359L)));
                                        unitValue.setExponent(new Exponent(new Integer(268296174)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(4752229671351491963L)));
                                        unitCost.setExponent(new Exponent(new Integer(-1606283693)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1600245668)));
                                    currentTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setCurrentTariff(currentTariff);
                            }
                            tariffInformation.setTariffTimeChange(new TariffTimeChange(-811019297));
                            {
                                NextTariff nextTariff = new NextTariff();
                                nextTariff.setCurrencyCode(new CurrencyCode(new Integer(2123826580)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(8843993107659705101L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(-1684865486)));
                                    nextTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.ADD_ON_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(7030022225808015508L)));
                                        unitValue.setExponent(new Exponent(new Integer(1389752316)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(-5974248862679876813L)));
                                        unitCost.setExponent(new Exponent(new Integer(1670627314)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1789131956)));
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
                                aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.AOC_D));
                                aoCSubscriptionInformation.addAoCService(aoCService);
                            }
                            aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.MONETARY));
                            aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(-2061277440)));
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
                serviceGenericInformation.setApplicationServerID(new ApplicationServerID("utf8string-1046620912"));
                serviceGenericInformation.setApplicationServiceType(new ApplicationServiceType("utf8string-1715713451"));
                serviceGenericInformation.setApplicationSessionID(new ApplicationSessionID("utf8string302315452"));
                serviceGenericInformation.setDeliveryStatus(new DeliveryStatus("utf8string-1868088970"));
                serviceInformation.setServiceGenericInformation(serviceGenericInformation);
            }
            {
                IMInformation iMInformation = new IMInformation();
                iMInformation.setTotalNumberOfMessagesSent(new TotalNumberOfMessagesSent(new Integer(1003221001)));
                iMInformation.setTotalNumberOfMessagesExploded(new TotalNumberOfMessagesExploded(new Integer(624584194)));
                iMInformation.setNumberOfMessagesSuccessfullySent(new NumberOfMessagesSuccessfullySent(new Integer(383359685)));
                iMInformation.setNumberOfMessagesSuccessfullyExploded(new NumberOfMessagesSuccessfullyExploded(new Integer(-1219252598)));
                serviceInformation.setIMInformation(iMInformation);
            }
            {
                DCDInformation dCDInformation = new DCDInformation();
                dCDInformation.setContentID(new ContentID("utf8string74860010"));
                dCDInformation.setContentproviderID(new ContentproviderID("utf8string725283265"));
                serviceInformation.setDCDInformation(dCDInformation);
            }
            {
                diameter.transatel_custom_avps.CSInformation cSInformation = new diameter.transatel_custom_avps.CSInformation();
                cSInformation.setCallType(new diameter.transatel_custom_avps.CallType(diameter.transatel_custom_avps.CallType.Value.MO_MMS));
                {
                    diameter.transatel_custom_avps.CAPInformation cAPInformation = new diameter.transatel_custom_avps.CAPInformation();
                    cAPInformation.setCAPCellIDAreaIDLAI(new diameter.transatel_custom_avps.CAPCellIDAreaIDLAI("octetstring-922949468"));
                    cAPInformation.setCAPIsFollowingOn(new diameter.transatel_custom_avps.CAPIsFollowingOn(diameter.transatel_custom_avps.CAPIsFollowingOn.Value.True));
                    cAPInformation.setCAPControlMode(new diameter.transatel_custom_avps.CAPControlMode(diameter.transatel_custom_avps.CAPControlMode.Value.NO_CONTROL));
                    cAPInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(-315973787)));
                    cAPInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(70530793)));
                    cAPInformation.setCAPServiceKey(new diameter.transatel_custom_avps.CAPServiceKey(new Integer(-1933065701)));
                    cAPInformation.setCAPDialedDigits(new diameter.transatel_custom_avps.CAPDialedDigits("utf8string1928398367"));
                    cAPInformation.setCAPCalledTON(new diameter.transatel_custom_avps.CAPCalledTON(new Integer(-535316684)));
                    cAPInformation.setCAPCLI(new diameter.transatel_custom_avps.CAPCLI("utf8string8264313"));
                    cAPInformation.setCAPCallingCategory(new diameter.transatel_custom_avps.CAPCallingCategory(new Integer(-262741650)));
                    cAPInformation.setCAPLocationNumber(new diameter.transatel_custom_avps.CAPLocationNumber("utf8string-1247889465"));
                    cAPInformation.setCAPRedirectingNumber(new diameter.transatel_custom_avps.CAPRedirectingNumber("utf8string-520784022"));
                    cAPInformation.setCAPRedirectingIndicator(new diameter.transatel_custom_avps.CAPRedirectingIndicator(new Integer(668222418)));
                    cAPInformation.setCAPOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPOriginalRedirectingReason(new Integer(-648031342)));
                    cAPInformation.setCAPRedirectionCounter(new diameter.transatel_custom_avps.CAPRedirectionCounter(new Integer(1880964956)));
                    cAPInformation.setCAPRedirectingReason(new diameter.transatel_custom_avps.CAPRedirectingReason(new Integer(-1657645579)));
                    cAPInformation.setCAPIMSI(new diameter.transatel_custom_avps.CAPIMSI("utf8string243237493"));
                    cAPInformation.setCAPVLRNumber(new diameter.transatel_custom_avps.CAPVLRNumber("utf8string-501238363"));
                    cAPInformation.setCAPCallReference(new diameter.transatel_custom_avps.CAPCallReference("octetstring267534089"));
                    cAPInformation.setCAPMSCAddress(new diameter.transatel_custom_avps.CAPMSCAddress("utf8string524414551"));
                    cAPInformation.setCAPCalledNPI(new diameter.transatel_custom_avps.CAPCalledNPI(new Integer(-1800500534)));
                    cAPInformation.setCAPCLINPI(new diameter.transatel_custom_avps.CAPCLINPI(new Integer(1897920590)));
                    cAPInformation.setCAPCLINOA(new diameter.transatel_custom_avps.CAPCLINOA(new Integer(-633914903)));
                    cAPInformation.setCAPCLIR(new diameter.transatel_custom_avps.CAPCLIR(new Integer(211909600)));
                    cAPInformation.setCAPVersion(new diameter.transatel_custom_avps.CAPVersion(new Integer(337163840)));
                    cAPInformation.setCAPBearerCapabilityTransfer(new diameter.transatel_custom_avps.CAPBearerCapabilityTransfer("utf8string-1185773806"));
                    cAPInformation.setCAPBearerCapabilityTransferRate(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferRate("utf8string1549519565"));
                    cAPInformation.setCAPGMSCAddress(new diameter.transatel_custom_avps.CAPGMSCAddress("utf8string-1704115425"));
                    cAPInformation.setCAPExtBasicServiceCode(new diameter.transatel_custom_avps.CAPExtBasicServiceCode("utf8string-1890967112"));
                    cAPInformation.setCAPBearerCapability(new diameter.transatel_custom_avps.CAPBearerCapability("octetstring-50818841"));
                    cAPInformation.setCAPSMSCAddress(new diameter.transatel_custom_avps.CAPSMSCAddress("utf8string-2129788100"));
                    cAPInformation.setCAPSGSNAddress(new diameter.transatel_custom_avps.CAPSGSNAddress("utf8string1230937749"));
                    cAPInformation.setCAPIMEI(new diameter.transatel_custom_avps.CAPIMEI("utf8string-903295453"));
                    cAPInformation.setCAPSMStatusReportRequest(new diameter.transatel_custom_avps.CAPSMStatusReportRequest("utf8string-388708858"));
                    cAPInformation.setCAPSMUserDataHeaderIndicator(new diameter.transatel_custom_avps.CAPSMUserDataHeaderIndicator("utf8string1604007610"));
                    cAPInformation.setCAPSMReplyPath(new diameter.transatel_custom_avps.CAPSMReplyPath("utf8string-2091801940"));
                    cAPInformation.setCAPSMVPFormat(new diameter.transatel_custom_avps.CAPSMVPFormat("utf8string706258793"));
                    cAPInformation.setCAPSMMessageTypeIndicator(new diameter.transatel_custom_avps.CAPSMMessageTypeIndicator("utf8string1944264453"));
                    cAPInformation.setCAPSMProtocolID(new diameter.transatel_custom_avps.CAPSMProtocolID("utf8string2021373517"));
                    cAPInformation.setCAPSMDCS(new diameter.transatel_custom_avps.CAPSMDCS("utf8string1122798823"));
                    cAPInformation.setCAPSMValidityPeriod(new diameter.transatel_custom_avps.CAPSMValidityPeriod("utf8string572429708"));
                    cAPInformation.setCAPSMRejectDuplicate(new diameter.transatel_custom_avps.CAPSMRejectDuplicate("utf8string1893564708"));
                    cAPInformation.setCAPSCCPCallingGT(new diameter.transatel_custom_avps.CAPSCCPCallingGT("utf8string736116796"));
                    cAPInformation.setCAPSCCPCalledGT(new diameter.transatel_custom_avps.CAPSCCPCalledGT("utf8string-1594723751"));
                    cAPInformation.setCAPBearerCapabilityTransferMode(new diameter.transatel_custom_avps.CAPBearerCapabilityTransferMode("utf8string314637325"));
                    cAPInformation.setCAPGSMForwardingPending(new diameter.transatel_custom_avps.CAPGSMForwardingPending(new Integer(-1149905946)));
                    cAPInformation.setCAPTCAPRemoteTransactionId(new diameter.transatel_custom_avps.CAPTCAPRemoteTransactionId("octetstring1732257818"));
                    cAPInformation.setCAPTCAPLocalTransactionId(new diameter.transatel_custom_avps.CAPTCAPLocalTransactionId("octetstring-848436901"));
                    {
                        diameter.transatel_custom_avps.CAPERBSInformation cAPERBSInformation = new diameter.transatel_custom_avps.CAPERBSInformation();
                        cAPERBSInformation.setCAPEventTypeBCSM(new diameter.transatel_custom_avps.CAPEventTypeBCSM(new Integer(-664384626)));
                        cAPERBSInformation.setCAPEventTypeSMS(new diameter.transatel_custom_avps.CAPEventTypeSMS(new Integer(1218665443)));
                        cAPERBSInformation.setCAPERBSEventSpecificInformation(new diameter.transatel_custom_avps.CAPERBSEventSpecificInformation("octetstring-1454146814"));
                        cAPERBSInformation.setCAPERBSLegId(new diameter.transatel_custom_avps.CAPERBSLegId(new Integer(-461936008)));
                        cAPERBSInformation.setCAPERBSMessageType(new diameter.transatel_custom_avps.CAPERBSMessageType(new Integer(-1680307784)));
                        cAPInformation.setCAPERBSInformation(cAPERBSInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPACHInformation cAPACHInformation = new diameter.transatel_custom_avps.CAPACHInformation();
                        cAPACHInformation.setCAPACHBeepTone(new diameter.transatel_custom_avps.CAPACHBeepTone(diameter.transatel_custom_avps.CAPACHBeepTone.Value.False));
                        cAPInformation.setCAPACHInformation(cAPACHInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPConnectInformation cAPConnectInformation = new diameter.transatel_custom_avps.CAPConnectInformation();
                        cAPConnectInformation.setCAPAnnouncementAccessNumber(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumber("utf8string-254499805"));
                        cAPConnectInformation.setCAPAnnouncementAccessNumberNOA(new diameter.transatel_custom_avps.CAPAnnouncementAccessNumberNOA(new Integer(-1306049364)));
                        cAPConnectInformation.setCAPConnectDestinationNumber(new diameter.transatel_custom_avps.CAPConnectDestinationNumber("utf8string-778112162"));
                        cAPConnectInformation.setCAPConnectDestinationNumberNature(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNature(new Integer(711120144)));
                        cAPConnectInformation.setCAPConnectDestinationNumberNPI(new diameter.transatel_custom_avps.CAPConnectDestinationNumberNPI(new Integer(370759038)));
                        cAPConnectInformation.setCAPConnectGenericNumber(new diameter.transatel_custom_avps.CAPConnectGenericNumber("utf8string-964656946"));
                        cAPConnectInformation.setCAPConnectCallingCategory(new diameter.transatel_custom_avps.CAPConnectCallingCategory(new Integer(206380258)));
                        cAPConnectInformation.setCAPConnectRedirectingNumber(new diameter.transatel_custom_avps.CAPConnectRedirectingNumber("utf8string-1347261491"));
                        cAPConnectInformation.setCAPConnectRedirectingIndicator(new diameter.transatel_custom_avps.CAPConnectRedirectingIndicator(new Integer(-1706379026)));
                        cAPConnectInformation.setCAPConnectOriginalRedirectingReason(new diameter.transatel_custom_avps.CAPConnectOriginalRedirectingReason(new Integer(-736657335)));
                        cAPConnectInformation.setCAPConnectRedirectingCounter(new diameter.transatel_custom_avps.CAPConnectRedirectingCounter(new Integer(1576613079)));
                        cAPConnectInformation.setCAPConnectRedirectingReason(new diameter.transatel_custom_avps.CAPConnectRedirectingReason(new Integer(1987501385)));
                        cAPConnectInformation.setCAPConnectoCSIApplicable(new diameter.transatel_custom_avps.CAPConnectoCSIApplicable(new Integer(-1929302680)));
                        cAPConnectInformation.setCAPConnectSuppressionOfAnnouncement(new diameter.transatel_custom_avps.CAPConnectSuppressionOfAnnouncement(new Integer(-769875182)));
                        cAPConnectInformation.setCAPConnectGenericNumberNOA(new diameter.transatel_custom_avps.CAPConnectGenericNumberNOA(new Integer(1677806824)));
                        cAPConnectInformation.setCAPConnectGenericNumberNPI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNPI(new Integer(334660018)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumber(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumber("utf8string-1165486972"));
                        cAPConnectInformation.setCAPConnectDestinationNumberINN(new diameter.transatel_custom_avps.CAPConnectDestinationNumberINN(new Integer(-2020646699)));
                        cAPConnectInformation.setCAPConnectGenericNumberNQI(new diameter.transatel_custom_avps.CAPConnectGenericNumberNQI(new Integer(-933114633)));
                        cAPConnectInformation.setCAPConnectGenericNumberNII(new diameter.transatel_custom_avps.CAPConnectGenericNumberNII(new Integer(-8536702)));
                        cAPConnectInformation.setCAPConnectGenericNumberARI(new diameter.transatel_custom_avps.CAPConnectGenericNumberARI(new Integer(-1772981188)));
                        cAPConnectInformation.setCAPConnectGenericNumberSCI(new diameter.transatel_custom_avps.CAPConnectGenericNumberSCI(new Integer(1089290609)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberNOA(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNOA(new Integer(1935504520)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberNPI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberNPI(new Integer(-1468042984)));
                        cAPConnectInformation.setCAPConnectRedirectingNumberARI(new diameter.transatel_custom_avps.CAPConnectRedirectingNumberARI(new Integer(-26119950)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberNOA(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNOA(new Integer(1861445799)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberNPI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberNPI(new Integer(-380006816)));
                        cAPConnectInformation.setCAPConnectOriginalCalledNumberARI(new diameter.transatel_custom_avps.CAPConnectOriginalCalledNumberARI(new Integer(381963652)));
                        cAPConnectInformation.setCAPConnectMaxDuration(new diameter.transatel_custom_avps.CAPConnectMaxDuration(new Integer(40494007)));
                        cAPInformation.setCAPConnectInformation(cAPConnectInformation);
                    }
                    {
                        diameter.transatel_custom_avps.CAPRRBSInformation cAPRRBSInformation = new diameter.transatel_custom_avps.CAPRRBSInformation();
                        cAPRRBSInformation.setCAPRRBSNoAnswerTimeout(new diameter.transatel_custom_avps.CAPRRBSNoAnswerTimeout(new Integer(-1287608051)));
                        cAPInformation.setCAPRRBSInformation(cAPRRBSInformation);
                    }
                    cAPInformation.setCAPReleaseCause(new diameter.transatel_custom_avps.CAPReleaseCause(new Integer(1507277417)));
                    cAPInformation.setCAPSMSpecificInfo(new diameter.transatel_custom_avps.CAPSMSpecificInfo("octetstring422978210"));
                    cAPInformation.setCAPTCAPErrorCause(new diameter.transatel_custom_avps.CAPTCAPErrorCause(new Integer(-908685110)));
                    cSInformation.setCAPInformation(cAPInformation);
                }
                serviceInformation.setCSInformation(cSInformation);
            }
            aCRequest.setServiceInformation(serviceInformation);
        }
        // add more AVP as ANY values to aCRequest

        byte[] buffer = aCRequest.encode();
        ACRequest aCRequest2 = new ACRequest(buffer);
        String s1 = aCRequest.toString();
        String s2 = aCRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aCRequest1 = " + s1);
            System.err.println("aCRequest2 = " + s2);
            throw new VerificationException("ACRequest encoding/decoding failure");
        }
    }

    public static void testACAnswer() throws Exception {
        ACAnswer aCAnswer = new ACAnswer(false, false);
        aCAnswer.setSessionId(new diameter.base.SessionId("utf8string-1978576312"));
        aCAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-811798056)));
        aCAnswer.setOriginHost(new diameter.base.OriginHost("id493976169.diameter.com"));
        aCAnswer.setOriginRealm(new diameter.base.OriginRealm("id-770129314.diameter.com"));
        aCAnswer.setAccountingRecordType(new diameter.base.AccountingRecordType(diameter.base.AccountingRecordType.Value.STOP_RECORD));
        aCAnswer.setAccountingRecordNumber(new diameter.base.AccountingRecordNumber(new Integer(1035053457)));
        aCAnswer.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1010231932)));
        aCAnswer.setUserName(new diameter.base.UserName("utf8string1177635743"));
        aCAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id-1464638729.diameter.com"));
        aCAnswer.setAcctInterimInterval(new diameter.base.AcctInterimInterval(new Integer(-218286391)));
        aCAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(875306274)));
        aCAnswer.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(-1124583433)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-2131285953.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1433917933"));
            // add more AVP as ANY values to proxyInfo
            aCAnswer.addProxyInfo(proxyInfo);
        }
        // add more AVP as ANY values to aCAnswer

        byte[] buffer = aCAnswer.encode();
        ACAnswer aCAnswer2 = new ACAnswer(buffer);
        String s1 = aCAnswer.toString();
        String s2 = aCAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aCAnswer1 = " + s1);
            System.err.println("aCAnswer2 = " + s2);
            throw new VerificationException("ACAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testACRequest();
        testACAnswer();
    }
}
