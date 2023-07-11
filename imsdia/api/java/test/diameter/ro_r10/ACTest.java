package diameter.ro_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class ACTest {

    public static void testACRequest() throws Exception {
        ACRequest aCRequest = new ACRequest(false, false);
        aCRequest.setSessionId(new diameter.base.SessionId("utf8string-371226215"));
        aCRequest.setOriginHost(new diameter.base.OriginHost("id2044602346.diameter.com"));
        aCRequest.setOriginRealm(new diameter.base.OriginRealm("id-1972942055.diameter.com"));
        aCRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1507396110.diameter.com"));
        aCRequest.setAccountingRecordType(new diameter.base.AccountingRecordType(diameter.base.AccountingRecordType.Value.START_RECORD));
        aCRequest.setAccountingRecordNumber(new diameter.base.AccountingRecordNumber(new Integer(-1106575538)));
        aCRequest.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1353507222)));
        aCRequest.setUserName(new diameter.base.UserName("utf8string-580704739"));
        aCRequest.setAcctInterimInterval(new diameter.base.AcctInterimInterval(new Integer(-1679346320)));
        aCRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(1987964369)));
        aCRequest.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(1975232641)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-477868771.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-2095072344"));
            // add more AVP as ANY values to proxyInfo
            aCRequest.addProxyInfo(proxyInfo);
        }
        aCRequest.addRouteRecord(new diameter.base.RouteRecord("id-1621760866.diameter.com"));
        aCRequest.setServiceContextId(new ServiceContextId("utf8string2145432773"));
        {
            ServiceInformation serviceInformation = new ServiceInformation();
            {
                SubscriptionId subscriptionId = new SubscriptionId();
                subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_PRIVATE));
                subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string376779252"));
                serviceInformation.addSubscriptionId(subscriptionId);
            }
            {
                AoCInformation aoCInformation = new AoCInformation();
                {
                    AoCCostInformation aoCCostInformation = new AoCCostInformation();
                    {
                        AccumulatedCost accumulatedCost = new AccumulatedCost();
                        accumulatedCost.setValueDigits(new ValueDigits(new Long(-4982026302660887350L)));
                        accumulatedCost.setExponent(new Exponent(new Integer(2080631118)));
                        aoCCostInformation.setAccumulatedCost(accumulatedCost);
                    }
                    {
                        IncrementalCost incrementalCost = new IncrementalCost();
                        incrementalCost.setValueDigits(new ValueDigits(new Long(2637953767387103708L)));
                        incrementalCost.setExponent(new Exponent(new Integer(-1532285245)));
                        aoCCostInformation.addIncrementalCost(incrementalCost);
                    }
                    aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(478652222)));
                    aoCInformation.setAoCCostInformation(aoCCostInformation);
                }
                {
                    TariffInformation tariffInformation = new TariffInformation();
                    {
                        CurrentTariff currentTariff = new CurrentTariff();
                        currentTariff.setCurrencyCode(new CurrencyCode(new Integer(2059110672)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(-2948296030303168444L)));
                            scaleFactor.setExponent(new Exponent(new Integer(11554156)));
                            currentTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TOTAL_OCTETS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.SETUP_CHARGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-5185064743034602691L)));
                                unitValue.setExponent(new Exponent(new Integer(-1964336728)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(5824117423846501198L)));
                                unitCost.setExponent(new Exponent(new Integer(1363593417)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(2125426387)));
                            currentTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setCurrentTariff(currentTariff);
                    }
                    tariffInformation.setTariffTimeChange(new TariffTimeChange(-885065782));
                    {
                        NextTariff nextTariff = new NextTariff();
                        nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-648121700)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(-6750269546814029299L)));
                            scaleFactor.setExponent(new Exponent(new Integer(838343150)));
                            nextTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-8851364773665925589L)));
                                unitValue.setExponent(new Exponent(new Integer(1946731010)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(-4189549536721249654L)));
                                unitCost.setExponent(new Exponent(new Integer(-1151079163)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1712979710)));
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
                        aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.AOC_E));
                        aoCSubscriptionInformation.addAoCService(aoCService);
                    }
                    aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.NON_MONETARY));
                    aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(-76890035)));
                    aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                }
                serviceInformation.setAoCInformation(aoCInformation);
            }
            {
                PSInformation pSInformation = new PSInformation();
                pSInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-313166495)));
                pSInformation.setPDNConnectionID(new PDNConnectionID(new Integer(1420427227)));
                pSInformation.setNodeId(new NodeId("utf8string244816197"));
                pSInformation.setRo3GPPPDPType(new Ro3GPPPDPType(new Integer(1003632466)));
                pSInformation.addPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "196.135.199.85")));
                pSInformation.setPDPAddressPrefixLength(new PDPAddressPrefixLength(new Integer(1407070623)));
                pSInformation.setDynamicAddressFlag(new DynamicAddressFlag(DynamicAddressFlag.Value.Dynamic));
                pSInformation.setDynamicAddressFlagExtension(new DynamicAddressFlagExtension(DynamicAddressFlagExtension.Value.Static));
                {
                    QoSInformation qoSInformation = new QoSInformation();
                    qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_6));
                    qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1143668506)));
                    qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-452121956)));
                    qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1138478858)));
                    qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(419647557)));
                    qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-1735504141"));
                    {
                        AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                        allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1556490543)));
                        allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                        allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                        qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                    }
                    qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-560385664)));
                    qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-1998383711)));
                    // add more AVP as ANY values to qoSInformation
                    pSInformation.setQoSInformation(qoSInformation);
                }
                pSInformation.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "93.29.244.112")));
                pSInformation.setGGSNAddress(new GGSNAddress(new Address(Address.Family.IPV4, "255.173.224.150")));
                pSInformation.setSGWAddress(new SGWAddress(new Address(Address.Family.IPV4, "158.48.253.255")));
                pSInformation.setCGAddress(new CGAddress(new Address(Address.Family.IPV4, "216.239.40.53")));
                pSInformation.setServingNodeType(new ServingNodeType(ServingNodeType.Value.ePDG));
                pSInformation.setSGWChange(new SGWChange(SGWChange.Value.ACR_Start_due_to_SGW_Change));
                pSInformation.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string330373805"));
                pSInformation.setIMSIUnauthenticatedFlag(new IMSIUnauthenticatedFlag(IMSIUnauthenticatedFlag.Value.Authenticated));
                pSInformation.setRo3GPPGGSNMCCMNC(new Ro3GPPGGSNMCCMNC("utf8string1415300744"));
                pSInformation.setRo3GPPNSAPI(new Ro3GPPNSAPI("utf8string-505792610"));
                pSInformation.setCalledStationId(new diameter.nasreq.CalledStationId("utf8string-491197241"));
                pSInformation.setRo3GPPSessionStopIndicator(new Ro3GPPSessionStopIndicator("octetstring-350857883"));
                pSInformation.setRo3GPPSelectionMode(new Ro3GPPSelectionMode("utf8string-127631850"));
                pSInformation.setRo3GPPChargingCharacteristics(new Ro3GPPChargingCharacteristics("utf8string108835579"));
                pSInformation.setRo3GPPSGSNMCCMNC(new Ro3GPPSGSNMCCMNC("utf8string1720310375"));
                pSInformation.setRo3GPPMSTimeZone(new Ro3GPPMSTimeZone("octetstring1271143806"));
                pSInformation.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring-336376841"));
                pSInformation.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring-218524078"));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(1632471860)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.Closed_mode));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.CSG_Member));
                    pSInformation.setUserCSGInformation(userCSGInformation);
                }
                pSInformation.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string-895142274"));
                pSInformation.setRo3GPPRATType(new Ro3GPPRATType("octetstring-1011078445"));
                {
                    PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                    pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(440415308)));
                    pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring1554413552"));
                    pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Append));
                    pSInformation.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                }
                pSInformation.setPDPContextType(new PDPContextType(PDPContextType.Value.PRIMARY));
                {
                    OfflineCharging offlineCharging = new OfflineCharging();
                    offlineCharging.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(577313326)));
                    {
                        TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                        timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                        timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(-1574567725)));
                        offlineCharging.setTimeQuotaMechanism(timeQuotaMechanism);
                    }
                    offlineCharging.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_EVENTS));
                    {
                        MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
                        {
                            GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                            grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(242182691));
                            grantedServiceUnit.setCCTime(new CCTime(new Integer(-1019192412)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(4913166610340054622L)));
                                    unitValue.setExponent(new Exponent(new Integer(1075807776)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-529210360)));
                                grantedServiceUnit.setCCMoney(cCMoney);
                            }
                            grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-3632889282381247057L)));
                            grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-3568702124542938584L)));
                            grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-3597958799691393638L)));
                            grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(5197711792061882869L)));
                            // add more AVP as ANY values to grantedServiceUnit
                            multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
                        }
                        {
                            RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                            requestedServiceUnit.setCCTime(new CCTime(new Integer(-369613019)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(6030060693500708258L)));
                                    unitValue.setExponent(new Exponent(new Integer(246724850)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(2092412213)));
                                requestedServiceUnit.setCCMoney(cCMoney);
                            }
                            requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-8612824640311711679L)));
                            requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-1361625501326758770L)));
                            requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-4668213243633690425L)));
                            requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(9151763455394257917L)));
                            // add more AVP as ANY values to requestedServiceUnit
                            multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
                        }
                        {
                            UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                            usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.RATING_CONDITION_CHANGE));
                            usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_INDETERMINATE));
                            usedServiceUnit.setCCTime(new CCTime(new Integer(-26642786)));
                            usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(4659898089227833795L)));
                            usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(1346060547448069169L)));
                            usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-2276598822413219792L)));
                            usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(7995654540343738107L)));
                            usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(1142325280));
                            multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
                        }
                        multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(1659921901)));
                        multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(390938173)));
                        {
                            GSUPoolReference gSUPoolReference = new GSUPoolReference();
                            gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(313097225)));
                            gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-7961658972035326825L)));
                                unitValue.setExponent(new Exponent(new Integer(224721840)));
                                gSUPoolReference.setUnitValue(unitValue);
                            }
                            multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
                        }
                        multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(-1112961748)));
                        multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(-1819150134)));
                        {
                            FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                            finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.RESTRICT_ACCESS));
                            finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                            finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string-294521870"));
                            {
                                RedirectServer redirectServer = new RedirectServer();
                                redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv6_Address));
                                redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string2146325897"));
                                finalUnitIndication.setRedirectServer(redirectServer);
                            }
                            multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
                        }
                        multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(-328446412)));
                        multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(-1684132571)));
                        multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(816494004)));
                        multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(2034211617)));
                        multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(681914505)));
                        multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.OTHER_QUOTA_TYPE));
                        {
                            Trigger trigger = new Trigger();
                            trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_TRAFFIC_CLASS));
                            multipleServicesCreditControl.setTrigger(trigger);
                        }
                        {
                            PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                            pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-2063251751)));
                            pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-1865412166"));
                            pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Append));
                            multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                        }
                        multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring513470970"));
                        {
                            AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                            aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-1173929090"));
                            {
                                Flows flows = new Flows();
                                flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(1337758478)));
                                flows.addFlowNumber(new FlowNumber(new Integer(-1308953338)));
                                aFCorrelationInformation.addFlows(flows);
                            }
                            multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
                        }
                        {
                            Envelope envelope = new Envelope();
                            envelope.setEnvelopeStartTime(new EnvelopeStartTime(1994620963));
                            envelope.setEnvelopeEndTime(new EnvelopeEndTime(1107023205));
                            envelope.setCCTotalOctets(new CCTotalOctets(new Long(-5385779249267874768L)));
                            envelope.setCCInputOctets(new CCInputOctets(new Long(3851249588045464239L)));
                            envelope.setCCOutputOctets(new CCOutputOctets(new Long(-8381512536900187978L)));
                            envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(165454980939922382L)));
                            // add more AVP as ANY values to envelope
                            multipleServicesCreditControl.addEnvelope(envelope);
                        }
                        multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME));
                        {
                            TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                            timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                            timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(1938102647)));
                            multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
                        }
                        {
                            ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                            serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string304236616"));
                            serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1249316871)));
                            multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
                        }
                        {
                            QoSInformation qoSInformation = new QoSInformation();
                            qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_8));
                            qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-991387176)));
                            qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(1867758522)));
                            qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-939782968)));
                            qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(791670589)));
                            qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring264907608"));
                            {
                                AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                                allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-963512544)));
                                allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                                allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                                qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                            }
                            qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1555270395)));
                            qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(523172435)));
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
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_4));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1739831837)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(1384061775)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(477727186)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-261018844)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-2050865749"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1509326852)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-1982291026)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1331793602)));
                        // add more AVP as ANY values to qoSInformation
                        trafficDataVolumes.setQoSInformation(qoSInformation);
                    }
                    trafficDataVolumes.setAccountingInputOctets(new AccountingInputOctets(new Long(6231582468113059720L)));
                    trafficDataVolumes.setAccountingInputPackets(new AccountingInputPackets(new Long(-2859186852104343241L)));
                    trafficDataVolumes.setAccountingOutputOctets(new AccountingOutputOctets(new Long(3947357521295463848L)));
                    trafficDataVolumes.setAccountingOutputPackets(new AccountingOutputPackets(new Long(-2507650845320326034L)));
                    trafficDataVolumes.setChangeCondition(new ChangeCondition(new Integer(1088259844)));
                    trafficDataVolumes.setChangeTime(new ChangeTime(-733854823));
                    trafficDataVolumes.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring756018719"));
                    pSInformation.addTrafficDataVolumes(trafficDataVolumes);
                }
                {
                    ServiceDataContainer serviceDataContainer = new ServiceDataContainer();
                    {
                        AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                        aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring935016807"));
                        {
                            Flows flows = new Flows();
                            flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(-1468674821)));
                            flows.addFlowNumber(new FlowNumber(new Integer(-1672287961)));
                            aFCorrelationInformation.addFlows(flows);
                        }
                        serviceDataContainer.setAFCorrelationInformation(aFCorrelationInformation);
                    }
                    serviceDataContainer.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring481849635"));
                    serviceDataContainer.setAccountingInputOctets(new AccountingInputOctets(new Long(-3338087739333736945L)));
                    serviceDataContainer.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-4300695197862105098L)));
                    serviceDataContainer.setAccountingInputPackets(new AccountingInputPackets(new Long(-3559290121808878162L)));
                    serviceDataContainer.setAccountingOutputPackets(new AccountingOutputPackets(new Long(-7273821972762149057L)));
                    serviceDataContainer.setLocalSequenceNumber(new LocalSequenceNumber(new Integer(949565187)));
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_7));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1629220828)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1173171799)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-179431941)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(437244183)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring178912598"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(658829694)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(235892282)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(903409806)));
                        // add more AVP as ANY values to qoSInformation
                        serviceDataContainer.setQoSInformation(qoSInformation);
                    }
                    serviceDataContainer.setRatingGroup(new RatingGroup(new Integer(-1858324625)));
                    serviceDataContainer.setChangeTime(new ChangeTime(450371575));
                    serviceDataContainer.setServiceIdentifier(new ServiceIdentifier(new Integer(114454984)));
                    {
                        ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                        serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-879136171"));
                        serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(162077306)));
                        serviceDataContainer.setServiceSpecificInfo(serviceSpecificInfo);
                    }
                    serviceDataContainer.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "71.160.92.255")));
                    serviceDataContainer.setTimeFirstUsage(new TimeFirstUsage(1721306642));
                    serviceDataContainer.setTimeLastUsage(new TimeLastUsage(222895223));
                    serviceDataContainer.setTimeUsage(new TimeUsage(-880674593));
                    serviceDataContainer.addChangeCondition(new ChangeCondition(new Integer(-1422039621)));
                    serviceDataContainer.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring-2004627146"));
                    serviceDataContainer.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string-2028846073"));
                    pSInformation.addServiceDataContainer(serviceDataContainer);
                }
                {
                    UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
                    userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.IMEISV));
                    userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring-136720923"));
                    pSInformation.setUserEquipmentInfo(userEquipmentInfo);
                }
                {
                    TerminalInformation terminalInformation = new TerminalInformation();
                    terminalInformation.setIMEI(new IMEI("utf8string-1178542414"));
                    terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string2057164359"));
                    // add more AVP as ANY values to terminalInformation
                    pSInformation.setTerminalInformation(terminalInformation);
                }
                pSInformation.setStartTime(new StartTime(1690630490));
                pSInformation.setStopTime(new StopTime(1696336768));
                pSInformation.setChangeCondition(new ChangeCondition(new Integer(1305178473)));
                pSInformation.setDiagnostics(new Diagnostics(new Integer(-313503268)));
                pSInformation.setLowPriorityIndicator(new LowPriorityIndicator(LowPriorityIndicator.Value.NO));
                serviceInformation.setPSInformation(pSInformation);
            }
            {
                WLANInformation wLANInformation = new WLANInformation();
                wLANInformation.setWLANSessionId(new WLANSessionId(new Integer(1774847727)));
                wLANInformation.setPDGAddress(new PDGAddress(new Address(Address.Family.IPV4, "37.207.167.206")));
                wLANInformation.setPDGChargingId(new PDGChargingId(new Integer(-1818416930)));
                wLANInformation.setWAGAddress(new WAGAddress(new Address(Address.Family.IPV4, "127.202.254.58")));
                wLANInformation.setWAGPLMNId(new WAGPLMNId("octetstring-840150568"));
                {
                    WLANRadioContainer wLANRadioContainer = new WLANRadioContainer();
                    wLANRadioContainer.setOperatorName(new OperatorName("octetstring-1431077426"));
                    wLANRadioContainer.setLocationInformation(new LocationInformation("octetstring-1641702398"));
                    {
                        LocationType locationType = new LocationType();
                        locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.ACTIVATE_DEFERRED_LOCATION));
                        locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string-311158588"));
                        wLANRadioContainer.setLocationType(locationType);
                    }
                    wLANRadioContainer.setWLANTechnology(new WLANTechnology(new Integer(-264284482)));
                    wLANInformation.setWLANRadioContainer(wLANRadioContainer);
                }
                wLANInformation.setWLANUELocalIPAddress(new WLANUELocalIPAddress(new Address(Address.Family.IPV4, "137.200.225.120")));
                serviceInformation.setWLANInformation(wLANInformation);
            }
            {
                IMSInformation iMSInformation = new IMSInformation();
                {
                    EventType eventType = new EventType();
                    eventType.setSIPMethod(new SIPMethod("utf8string4981067"));
                    eventType.setIMSEvent(new IMSEvent("utf8string1232053726"));
                    eventType.setExpires(new Expires(new Integer(1350600053)));
                    iMSInformation.setEventType(eventType);
                }
                iMSInformation.setRoleOfNode(new RoleOfNode(RoleOfNode.Value.TERMINATING_ROLE));
                iMSInformation.setNodeFunctionality(new NodeFunctionality(NodeFunctionality.Value.S_GW));
                iMSInformation.setUserSessionID(new UserSessionID("utf8string-266715352"));
                iMSInformation.setOutgoingSessionId(new OutgoingSessionId("utf8string-1629463906"));
                iMSInformation.addCallingPartyAddress(new CallingPartyAddress("utf8string-397243533"));
                iMSInformation.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY_4));
                iMSInformation.setCalledPartyAddress(new CalledPartyAddress("utf8string1326820156"));
                iMSInformation.addCalledAssertedIdentity(new CalledAssertedIdentity("utf8string179254733"));
                iMSInformation.setNumberPortabilityRoutingInformation(new NumberPortabilityRoutingInformation("utf8string-239493681"));
                iMSInformation.setCarrierSelectRoutingInformation(new CarrierSelectRoutingInformation("utf8string508996552"));
                iMSInformation.setAlternateChargedPartyAddress(new AlternateChargedPartyAddress("utf8string1861689270"));
                iMSInformation.setRequestedPartyAddress(new RequestedPartyAddress("utf8string-203969419"));
                iMSInformation.addAssociatedURI(new AssociatedURI("utf8string659831858"));
                {
                    TimeStamps timeStamps = new TimeStamps();
                    timeStamps.setSIPRequestTimestamp(new SIPRequestTimestamp(-87862273));
                    timeStamps.setSIPResponseTimestamp(new SIPResponseTimestamp(543498368));
                    timeStamps.setSIPRequestTimestampFraction(new SIPRequestTimestampFraction(new Integer(63319038)));
                    timeStamps.setSIPResponseTimestampFraction(new SIPResponseTimestampFraction(new Integer(-1713431055)));
                    iMSInformation.setTimeStamps(timeStamps);
                }
                {
                    ApplicationServerInformation applicationServerInformation = new ApplicationServerInformation();
                    applicationServerInformation.setApplicationServer(new ApplicationServer("utf8string-1850331187"));
                    applicationServerInformation.addApplicationProvidedCalledPartyAddress(new ApplicationProvidedCalledPartyAddress("utf8string-1877626797"));
                    iMSInformation.addApplicationServerInformation(applicationServerInformation);
                }
                {
                    InterOperatorIdentifier interOperatorIdentifier = new InterOperatorIdentifier();
                    interOperatorIdentifier.setOriginatingIOI(new OriginatingIOI("utf8string-1041614337"));
                    interOperatorIdentifier.setTerminatingIOI(new TerminatingIOI("utf8string-1300357045"));
                    iMSInformation.addInterOperatorIdentifier(interOperatorIdentifier);
                }
                iMSInformation.setIMSChargingIdentifier(new IMSChargingIdentifier("utf8string1269325166"));
                iMSInformation.addSDPSessionDescription(new SDPSessionDescription("utf8string559973758"));
                {
                    SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                    sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string-1676737620"));
                    sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string675517133"));
                    sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Not_Inserted));
                    sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                    sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_realm_used));
                    sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.calling_party));
                    sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string-91801864"));
                    sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string1579291981"));
                    sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-1294128015)));
                    sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring86253599"));
                    sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Answer));
                    iMSInformation.addSDPMediaComponent(sDPMediaComponent);
                }
                iMSInformation.setServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "214.161.149.114")));
                {
                    ServerCapabilities serverCapabilities = new ServerCapabilities();
                    serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(-1745458488)));
                    serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(-793709481)));
                    serverCapabilities.addServerName(new ServerName("utf8string-1683695353"));
                    // add more AVP as ANY values to serverCapabilities
                    iMSInformation.setServerCapabilities(serverCapabilities);
                }
                {
                    TrunkGroupID trunkGroupID = new TrunkGroupID();
                    trunkGroupID.setIncomingTrunkGroupID(new IncomingTrunkGroupID("utf8string-976817809"));
                    trunkGroupID.setOutgoingTrunkGroupID(new OutgoingTrunkGroupID("utf8string-1523211374"));
                    iMSInformation.setTrunkGroupID(trunkGroupID);
                }
                iMSInformation.setBearerService(new BearerService("octetstring1700846704"));
                iMSInformation.setServiceId(new ServiceId("utf8string2043073831"));
                {
                    ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                    serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string711939203"));
                    serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(-931711730)));
                    iMSInformation.addServiceSpecificInfo(serviceSpecificInfo);
                }
                {
                    MessageBody messageBody = new MessageBody();
                    messageBody.setContentType(new ContentType("utf8string1572954721"));
                    messageBody.setContentLength(new ContentLength(new Integer(-623785846)));
                    messageBody.setContentDisposition(new ContentDisposition("utf8string1273139652"));
                    messageBody.setOriginator(new Originator(Originator.Value.Called_Party));
                    iMSInformation.addMessageBody(messageBody);
                }
                iMSInformation.setCauseCode(new CauseCode(new Integer(1302176359)));
                iMSInformation.setAccessNetworkInformation(new AccessNetworkInformation("octetstring83718867"));
                {
                    EarlyMediaDescription earlyMediaDescription = new EarlyMediaDescription();
                    {
                        SDPTimeStamps sDPTimeStamps = new SDPTimeStamps();
                        sDPTimeStamps.setSDPOfferTimestamp(new SDPOfferTimestamp(1070413606));
                        sDPTimeStamps.setSDPAnswerTimestamp(new SDPAnswerTimestamp(882375683));
                        earlyMediaDescription.setSDPTimeStamps(sDPTimeStamps);
                    }
                    {
                        SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                        sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string1559683330"));
                        sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string898140688"));
                        sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                        sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                        sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_realm_used));
                        sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.calling_party));
                        sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string628524076"));
                        sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string-1244203827"));
                        sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(1520482467)));
                        sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring1070363108"));
                        sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Answer));
                        earlyMediaDescription.addSDPMediaComponent(sDPMediaComponent);
                    }
                    earlyMediaDescription.addSDPSessionDescription(new SDPSessionDescription("utf8string1017491846"));
                    iMSInformation.addEarlyMediaDescription(earlyMediaDescription);
                }
                iMSInformation.setIMSCommunicationServiceIdentifier(new IMSCommunicationServiceIdentifier("utf8string1340518007"));
                iMSInformation.setOnlineChargingFlag(new OnlineChargingFlag(OnlineChargingFlag.Value.ECF_address_provided));
                {
                    RealTimeTariffInformation realTimeTariffInformation = new RealTimeTariffInformation();
                    {
                        TariffInformation tariffInformation = new TariffInformation();
                        {
                            CurrentTariff currentTariff = new CurrentTariff();
                            currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-1929737800)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(-5475279460122011102L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-1773713993)));
                                currentTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.SETUP_CHARGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-7253622339497610099L)));
                                    unitValue.setExponent(new Exponent(new Integer(-958358847)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(7372143899310913870L)));
                                    unitCost.setExponent(new Exponent(new Integer(-755464930)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(2067691721)));
                                currentTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setCurrentTariff(currentTariff);
                        }
                        tariffInformation.setTariffTimeChange(new TariffTimeChange(189782820));
                        {
                            NextTariff nextTariff = new NextTariff();
                            nextTariff.setCurrencyCode(new CurrencyCode(new Integer(1862219574)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(-7737550924070234733L)));
                                scaleFactor.setExponent(new Exponent(new Integer(1452438318)));
                                nextTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-8109329411382911882L)));
                                    unitValue.setExponent(new Exponent(new Integer(1690001994)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(-4627106924298225074L)));
                                    unitCost.setExponent(new Exponent(new Integer(-838443612)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1493474741)));
                                nextTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setNextTariff(nextTariff);
                        }
                        realTimeTariffInformation.setTariffInformation(tariffInformation);
                    }
                    realTimeTariffInformation.setTariffXML(new TariffXML("utf8string-1571124888"));
                    iMSInformation.setRealTimeTariffInformation(realTimeTariffInformation);
                }
                iMSInformation.setAccountExpiration(new AccountExpiration(-246526846));
                iMSInformation.setInitialIMSChargingIdentifier(new InitialIMSChargingIdentifier("utf8string1091701502"));
                serviceInformation.setIMSInformation(iMSInformation);
            }
            {
                MMSInformation mMSInformation = new MMSInformation();
                {
                    OriginatorAddress originatorAddress = new OriginatorAddress();
                    originatorAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.Numeric_Shortcode));
                    originatorAddress.setAddressData(new AddressData("utf8string623954958"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string837063013"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-959113168"));
                        originatorAddress.setAddressDomain(addressDomain);
                    }
                    mMSInformation.setOriginatorAddress(originatorAddress);
                }
                {
                    RecipientAddress recipientAddress = new RecipientAddress();
                    recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IMSI));
                    recipientAddress.setAddressData(new AddressData("utf8string-615228568"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-1975847228"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1299054005"));
                        recipientAddress.setAddressDomain(addressDomain);
                    }
                    recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.BCC));
                    mMSInformation.addRecipientAddress(recipientAddress);
                }
                mMSInformation.setSubmissionTime(new SubmissionTime(1239335532));
                {
                    MMContentType mMContentType = new MMContentType();
                    mMContentType.setTypeNumber(new TypeNumber(new Integer(214475297)));
                    mMContentType.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string977131023"));
                    mMContentType.setContentSize(new ContentSize(new Integer(-1281876370)));
                    {
                        AdditionalContentInformation additionalContentInformation = new AdditionalContentInformation();
                        additionalContentInformation.setTypeNumber(new TypeNumber(new Integer(-396676044)));
                        additionalContentInformation.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string-1841385786"));
                        additionalContentInformation.setContentSize(new ContentSize(new Integer(1750406765)));
                        mMContentType.addAdditionalContentInformation(additionalContentInformation);
                    }
                    mMSInformation.setMMContentType(mMContentType);
                }
                mMSInformation.setPriority(new Priority(Priority.Value.High));
                mMSInformation.setMessageID(new MessageID("utf8string-476430299"));
                mMSInformation.setMessageType(new MessageType(MessageType.Value.m_mbox_store_conf));
                mMSInformation.setMessageSize(new MessageSize(new Integer(658114374)));
                {
                    MessageClass messageClass = new MessageClass();
                    messageClass.setClassIdentifier(new ClassIdentifier(ClassIdentifier.Value.Personal));
                    messageClass.setTokenText(new TokenText("utf8string1338647636"));
                    mMSInformation.setMessageClass(messageClass);
                }
                mMSInformation.setDeliveryReportRequested(new DeliveryReportRequested(DeliveryReportRequested.Value.Yes));
                mMSInformation.setReadReplyReportRequested(new ReadReplyReportRequested(ReadReplyReportRequested.Value.Yes));
                mMSInformation.setMMBoxStorageRequested(new MMBoxStorageRequested(MMBoxStorageRequested.Value.No));
                mMSInformation.setApplicID(new ApplicID("utf8string668426788"));
                mMSInformation.setReplyApplicID(new ReplyApplicID("utf8string-274235706"));
                mMSInformation.setAuxApplicInfo(new AuxApplicInfo("utf8string2044112156"));
                mMSInformation.setContentClass(new ContentClass(ContentClass.Value.video_basic));
                mMSInformation.setDRMContent(new DRMContent(DRMContent.Value.Yes));
                mMSInformation.setAdaptations(new Adaptations(Adaptations.Value.Yes));
                mMSInformation.setVASPId(new VASPId("utf8string-2085233912"));
                mMSInformation.setVASId(new VASId("utf8string1826917951"));
                serviceInformation.setMMSInformation(mMSInformation);
            }
            {
                LCSInformation lCSInformation = new LCSInformation();
                {
                    LCSClientID lCSClientID = new LCSClientID();
                    lCSClientID.setLCSClientType(new LCSClientType(LCSClientType.Value.PLMN_OPERATOR_SERVICES));
                    lCSClientID.setLCSClientExternalID(new LCSClientExternalID("utf8string-2058936860"));
                    lCSClientID.setLCSClientDialedByMS(new LCSClientDialedByMS("utf8string263437978"));
                    {
                        LCSClientName lCSClientName = new LCSClientName();
                        lCSClientName.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string1013748250"));
                        lCSClientName.setLCSNameString(new LCSNameString("utf8string1014625698"));
                        lCSClientName.setLCSFormatIndicator(new LCSFormatIndicator(LCSFormatIndicator.Value.EMAIL_ADDRESS));
                        lCSClientID.setLCSClientName(lCSClientName);
                    }
                    lCSClientID.setLCSAPN(new LCSAPN("utf8string668569272"));
                    {
                        LCSRequestorID lCSRequestorID = new LCSRequestorID();
                        lCSRequestorID.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string-1074061321"));
                        lCSRequestorID.setLCSRequestorIDString(new LCSRequestorIDString("utf8string495815373"));
                        lCSClientID.setLCSRequestorID(lCSRequestorID);
                    }
                    lCSInformation.setLCSClientID(lCSClientID);
                }
                {
                    LocationType locationType = new LocationType();
                    locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.ACTIVATE_DEFERRED_LOCATION));
                    locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string1918606610"));
                    lCSInformation.setLocationType(locationType);
                }
                lCSInformation.setLocationEstimate(new LocationEstimate("utf8string429847401"));
                lCSInformation.setPositioningData(new PositioningData("utf8string1348770389"));
                lCSInformation.setRo3GPPIMSI(new Ro3GPPIMSI("utf8string1498091938"));
                lCSInformation.setMSISDN(new MSISDN("octetstring1075302058"));
                serviceInformation.setLCSInformation(lCSInformation);
            }
            {
                PoCInformation poCInformation = new PoCInformation();
                poCInformation.setPoCServerRole(new PoCServerRole(PoCServerRole.Value.Participating_PoC_Server));
                poCInformation.setPoCSessionType(new PoCSessionType(PoCSessionType.Value.One_to_one_PoC_session));
                {
                    PoCUserRole poCUserRole = new PoCUserRole();
                    poCUserRole.setPoCUserRoleIds(new PoCUserRoleIds("utf8string1948497449"));
                    poCUserRole.setPoCUserRoleinfoUnits(new PoCUserRoleinfoUnits(PoCUserRoleinfoUnits.Value.Session_Owner));
                    poCInformation.setPoCUserRole(poCUserRole);
                }
                poCInformation.setPoCSessionInitiationType(new PoCSessionInitiationType(PoCSessionInitiationType.Value.On_demand));
                poCInformation.setPoCEventType(new PoCEventType(PoCEventType.Value.PoC_Group_Advertisement_event));
                poCInformation.setNumberOfParticipants(new NumberOfParticipants(new Integer(1365230101)));
                poCInformation.addParticipantsInvolved(new ParticipantsInvolved("utf8string-1488157438"));
                {
                    ParticipantGroup participantGroup = new ParticipantGroup();
                    participantGroup.setCalledPartyAddress(new CalledPartyAddress("utf8string-583300369"));
                    participantGroup.setParticipantAccessPriority(new ParticipantAccessPriority(ParticipantAccessPriority.Value.Low_priority));
                    participantGroup.setUserParticipatingType(new UserParticipatingType(UserParticipatingType.Value.Normal));
                    poCInformation.addParticipantGroup(participantGroup);
                }
                {
                    TalkBurstExchange talkBurstExchange = new TalkBurstExchange();
                    talkBurstExchange.setPoCChangeTime(new PoCChangeTime(1250854011));
                    talkBurstExchange.setNumberOfTalkBursts(new NumberOfTalkBursts(new Integer(815006996)));
                    talkBurstExchange.setTalkBurstVolume(new TalkBurstVolume(new Integer(1922054092)));
                    talkBurstExchange.setTalkBurstTime(new TalkBurstTime(new Integer(-658250059)));
                    talkBurstExchange.setNumberOfReceivedTalkBursts(new NumberOfReceivedTalkBursts(new Integer(276533099)));
                    talkBurstExchange.setReceivedTalkBurstVolume(new ReceivedTalkBurstVolume(new Integer(1792263297)));
                    talkBurstExchange.setReceivedTalkBurstTime(new ReceivedTalkBurstTime(new Integer(918237189)));
                    talkBurstExchange.setNumberOfParticipants(new NumberOfParticipants(new Integer(1639902618)));
                    talkBurstExchange.setPoCChangeCondition(new PoCChangeCondition(PoCChangeCondition.Value.volumeLimit));
                    poCInformation.addTalkBurstExchange(talkBurstExchange);
                }
                poCInformation.setPoCControllingAddress(new PoCControllingAddress("utf8string1830830487"));
                poCInformation.setPoCGroupName(new PoCGroupName("utf8string-2073930772"));
                poCInformation.setPoCSessionId(new PoCSessionId("utf8string-451080657"));
                poCInformation.setChargedParty(new ChargedParty("utf8string170011536"));
                serviceInformation.setPoCInformation(poCInformation);
            }
            {
                MBMSInformation mBMSInformation = new MBMSInformation();
                mBMSInformation.setTMGI(new TMGI("octetstring-1941007142"));
                mBMSInformation.setMBMSServiceType(new MBMSServiceType(MBMSServiceType.Value.MULTICAST));
                mBMSInformation.setMBMSUserServiceType(new MBMSUserServiceType(MBMSUserServiceType.Value.STREAMING));
                mBMSInformation.setFileRepairSupported(new FileRepairSupported(FileRepairSupported.Value.NOT_SUPPORTED));
                mBMSInformation.setRequiredMBMSBearerCapabilities(new RequiredMBMSBearerCapabilities("utf8string-1592160794"));
                mBMSInformation.setMBMS2G3GIndicator(new MBMS2G3GIndicator(MBMS2G3GIndicator.Value.BOTH_2G_AND_3G));
                mBMSInformation.setRAI(new RAI("utf8string1775801158"));
                mBMSInformation.addMBMSServiceArea(new MBMSServiceArea("octetstring748254116"));
                mBMSInformation.setMBMSSessionIdentity(new MBMSSessionIdentity("octetstring-1943157341"));
                mBMSInformation.setCNIPMulticastDistribution(new CNIPMulticastDistribution(CNIPMulticastDistribution.Value.NO_IP_MULTICAST));
                mBMSInformation.setMBMSGWAddress(new MBMSGWAddress(new Address(Address.Family.IPV4, "35.98.183.202")));
                serviceInformation.setMBMSInformation(mBMSInformation);
            }
            {
                SMSInformation sMSInformation = new SMSInformation();
                sMSInformation.setSMSNode(new SMSNode(SMSNode.Value.SMS_Router));
                sMSInformation.setClientAddress(new ClientAddress(new Address(Address.Family.IPV4, "219.60.251.90")));
                sMSInformation.setOriginatorSCCPAddress(new OriginatorSCCPAddress(new Address(Address.Family.IPV4, "11.178.188.179")));
                sMSInformation.setSMSCAddress(new SMSCAddress(new Address(Address.Family.IPV4, "239.55.197.241")));
                sMSInformation.setDataCodingScheme(new DataCodingScheme(new Integer(-1469434298)));
                sMSInformation.setSMDischargeTime(new SMDischargeTime(-435268875));
                sMSInformation.setSMMessageType(new SMMessageType(SMMessageType.Value.SUBMISSION));
                {
                    OriginatorInterface originatorInterface = new OriginatorInterface();
                    originatorInterface.setInterfaceId(new InterfaceId("utf8string1434293616"));
                    originatorInterface.setInterfaceText(new InterfaceText("utf8string-50709604"));
                    originatorInterface.setInterfacePort(new InterfacePort("utf8string304658139"));
                    originatorInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.MOBILE_ORIGINATING));
                    sMSInformation.setOriginatorInterface(originatorInterface);
                }
                sMSInformation.setSMProtocolID(new SMProtocolID("octetstring-2130215648"));
                sMSInformation.setReplyPathRequested(new ReplyPathRequested(ReplyPathRequested.Value.No_Reply_Path_Set));
                sMSInformation.setSMStatus(new SMStatus("octetstring26441615"));
                sMSInformation.setSMUserDataHeader(new SMUserDataHeader("octetstring-1081011754"));
                sMSInformation.setNumberOfMessagesSent(new NumberOfMessagesSent(new Integer(1048787352)));
                {
                    RecipientInfo recipientInfo = new RecipientInfo();
                    {
                        DestinationInterface destinationInterface = new DestinationInterface();
                        destinationInterface.setInterfaceId(new InterfaceId("utf8string829880611"));
                        destinationInterface.setInterfaceText(new InterfaceText("utf8string-1672686174"));
                        destinationInterface.setInterfacePort(new InterfacePort("utf8string1053795392"));
                        destinationInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.MOBILE_TERMINATING));
                        recipientInfo.setDestinationInterface(destinationInterface);
                    }
                    {
                        RecipientAddress recipientAddress = new RecipientAddress();
                        recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.e_mail_address));
                        recipientAddress.setAddressData(new AddressData("utf8string-129110779"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string-708525045"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-406552111"));
                            recipientAddress.setAddressDomain(addressDomain);
                        }
                        recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.CC));
                        recipientInfo.addRecipientAddress(recipientAddress);
                    }
                    {
                        RecipientReceivedAddress recipientReceivedAddress = new RecipientReceivedAddress();
                        recipientReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.e_mail_address));
                        recipientReceivedAddress.setAddressData(new AddressData("utf8string1959871619"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string-1970502586"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string807183379"));
                            recipientReceivedAddress.setAddressDomain(addressDomain);
                        }
                        recipientInfo.addRecipientReceivedAddress(recipientReceivedAddress);
                    }
                    recipientInfo.setRecipientSCCPAddress(new RecipientSCCPAddress(new Address(Address.Family.IPV4, "207.138.212.91")));
                    recipientInfo.setSMProtocolID(new SMProtocolID("octetstring136046728"));
                    sMSInformation.addRecipientInfo(recipientInfo);
                }
                {
                    OriginatorReceivedAddress originatorReceivedAddress = new OriginatorReceivedAddress();
                    originatorReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv4_Address));
                    originatorReceivedAddress.setAddressData(new AddressData("utf8string-1405094832"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string815093783"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string894293724"));
                        originatorReceivedAddress.setAddressDomain(addressDomain);
                    }
                    sMSInformation.setOriginatorReceivedAddress(originatorReceivedAddress);
                }
                sMSInformation.setSMServiceType(new SMServiceType(SMServiceType.Value.VAS4SMS_Forwarding));
                serviceInformation.setSMSInformation(sMSInformation);
            }
            {
                MMTelInformation mMTelInformation = new MMTelInformation();
                {
                    SupplementaryService supplementaryService = new SupplementaryService();
                    supplementaryService.setServiceType(new ServiceType(new Integer(21851887)));
                    supplementaryService.setServiceMode(new ServiceMode(new Integer(-838785630)));
                    supplementaryService.setNumberOfDiversions(new NumberOfDiversions(new Integer(1159723297)));
                    supplementaryService.setAssociatedPartyAddress(new AssociatedPartyAddress("utf8string1637963594"));
                    supplementaryService.setServiceId(new ServiceId("utf8string-719066343"));
                    supplementaryService.setChangeTime(new ChangeTime(-230113406));
                    supplementaryService.setNumberOfParticipants(new NumberOfParticipants(new Integer(-1616499190)));
                    supplementaryService.setParticipantActionType(new ParticipantActionType(ParticipantActionType.Value.CREATE_CONF));
                    supplementaryService.setCUGInformation(new CUGInformation("octetstring1479024259"));
                    {
                        AoCInformation aoCInformation = new AoCInformation();
                        {
                            AoCCostInformation aoCCostInformation = new AoCCostInformation();
                            {
                                AccumulatedCost accumulatedCost = new AccumulatedCost();
                                accumulatedCost.setValueDigits(new ValueDigits(new Long(-2019065158344672560L)));
                                accumulatedCost.setExponent(new Exponent(new Integer(2142045366)));
                                aoCCostInformation.setAccumulatedCost(accumulatedCost);
                            }
                            {
                                IncrementalCost incrementalCost = new IncrementalCost();
                                incrementalCost.setValueDigits(new ValueDigits(new Long(-753510180339352938L)));
                                incrementalCost.setExponent(new Exponent(new Integer(260382895)));
                                aoCCostInformation.addIncrementalCost(incrementalCost);
                            }
                            aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(2061516466)));
                            aoCInformation.setAoCCostInformation(aoCCostInformation);
                        }
                        {
                            TariffInformation tariffInformation = new TariffInformation();
                            {
                                CurrentTariff currentTariff = new CurrentTariff();
                                currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-1821371259)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(6450018444234528147L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(-333511639)));
                                    currentTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.INPUT_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(-6492268635712697921L)));
                                        unitValue.setExponent(new Exponent(new Integer(532771329)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(-6889930765606013282L)));
                                        unitCost.setExponent(new Exponent(new Integer(1613123569)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1326402592)));
                                    currentTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setCurrentTariff(currentTariff);
                            }
                            tariffInformation.setTariffTimeChange(new TariffTimeChange(769167258));
                            {
                                NextTariff nextTariff = new NextTariff();
                                nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-1118613005)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(8594660828614333331L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(-2051451797)));
                                    nextTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.INPUT_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.SETUP_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(3434539235745237605L)));
                                        unitValue.setExponent(new Exponent(new Integer(251863808)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(-8909844226154467348L)));
                                        unitCost.setExponent(new Exponent(new Integer(70191313)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-811886250)));
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
                                aoCService.setAoCServiceType(new AoCServiceType(AoCServiceType.Value.AOC_S));
                                aoCSubscriptionInformation.addAoCService(aoCService);
                            }
                            aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.MONETARY));
                            aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(218937694)));
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
                serviceGenericInformation.setApplicationServerID(new ApplicationServerID("utf8string504710739"));
                serviceGenericInformation.setApplicationServiceType(new ApplicationServiceType("utf8string1955866640"));
                serviceGenericInformation.setApplicationSessionID(new ApplicationSessionID("utf8string-2059819538"));
                serviceGenericInformation.setDeliveryStatus(new DeliveryStatus("utf8string-1899576844"));
                serviceInformation.setServiceGenericInformation(serviceGenericInformation);
            }
            {
                IMInformation iMInformation = new IMInformation();
                iMInformation.setTotalNumberOfMessagesSent(new TotalNumberOfMessagesSent(new Integer(993214823)));
                iMInformation.setTotalNumberOfMessagesExploded(new TotalNumberOfMessagesExploded(new Integer(56039082)));
                iMInformation.setNumberOfMessagesSuccessfullySent(new NumberOfMessagesSuccessfullySent(new Integer(-1679512795)));
                iMInformation.setNumberOfMessagesSuccessfullyExploded(new NumberOfMessagesSuccessfullyExploded(new Integer(528790754)));
                serviceInformation.setIMInformation(iMInformation);
            }
            {
                DCDInformation dCDInformation = new DCDInformation();
                dCDInformation.setContentID(new ContentID("utf8string70360353"));
                dCDInformation.setContentproviderID(new ContentproviderID("utf8string-1420301296"));
                serviceInformation.setDCDInformation(dCDInformation);
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
        aCAnswer.setSessionId(new diameter.base.SessionId("utf8string2146583455"));
        aCAnswer.setResultCode(new diameter.base.ResultCode(new Integer(2058442351)));
        aCAnswer.setOriginHost(new diameter.base.OriginHost("id-2014041912.diameter.com"));
        aCAnswer.setOriginRealm(new diameter.base.OriginRealm("id74018584.diameter.com"));
        aCAnswer.setAccountingRecordType(new diameter.base.AccountingRecordType(diameter.base.AccountingRecordType.Value.INTERIM_RECORD));
        aCAnswer.setAccountingRecordNumber(new diameter.base.AccountingRecordNumber(new Integer(870193242)));
        aCAnswer.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(836079684)));
        aCAnswer.setUserName(new diameter.base.UserName("utf8string1230649024"));
        aCAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id-328388832.diameter.com"));
        aCAnswer.setAcctInterimInterval(new diameter.base.AcctInterimInterval(new Integer(-367108254)));
        aCAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(1298922739)));
        aCAnswer.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(916167796)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1635630105.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-914912976"));
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
