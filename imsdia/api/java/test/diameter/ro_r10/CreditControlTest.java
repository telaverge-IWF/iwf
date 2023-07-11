package diameter.ro_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class CreditControlTest {

    public static void testCreditControlRequest() throws Exception {
        CreditControlRequest creditControlRequest = new CreditControlRequest(false, false);
        creditControlRequest.setSessionId(new diameter.base.SessionId("utf8string-125580041"));
        creditControlRequest.setOriginHost(new diameter.base.OriginHost("id-1022012676.diameter.com"));
        creditControlRequest.setOriginRealm(new diameter.base.OriginRealm("id1900624056.diameter.com"));
        creditControlRequest.setDestinationRealm(new diameter.base.DestinationRealm("id9008093.diameter.com"));
        creditControlRequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(284814323)));
        creditControlRequest.setServiceContextId(new ServiceContextId("utf8string-1517037814"));
        creditControlRequest.setCCRequestType(new CCRequestType(CCRequestType.Value.UPDATE_REQUEST));
        creditControlRequest.setCCRequestNumber(new CCRequestNumber(new Integer(-734000364)));
        creditControlRequest.setDestinationHost(new diameter.base.DestinationHost("id-366064226.diameter.com"));
        creditControlRequest.setUserName(new diameter.base.UserName("utf8string837900394"));
        creditControlRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(-2081186735)));
        creditControlRequest.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(2052880090)));
        {
            SubscriptionId subscriptionId = new SubscriptionId();
            subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_NAI));
            subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string1677069000"));
            creditControlRequest.addSubscriptionId(subscriptionId);
        }
        creditControlRequest.setTerminationCause(new diameter.base.TerminationCause(diameter.base.TerminationCause.Value.DIAMETER_BAD_ANSWER));
        creditControlRequest.setRequestedAction(new RequestedAction(RequestedAction.Value.CHECK_BALANCE));
        creditControlRequest.setAoCRequestType(new AoCRequestType(AoCRequestType.Value.AoC_TARIFF_ONLY));
        creditControlRequest.setMultipleServicesIndicator(new MultipleServicesIndicator(MultipleServicesIndicator.Value.MULTIPLE_SERVICES_NOT_SUPPORTED));
        {
            MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
            {
                GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(-226178027));
                grantedServiceUnit.setCCTime(new CCTime(new Integer(-1625778213)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(3775846938766579461L)));
                        unitValue.setExponent(new Exponent(new Integer(928672097)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-1497543104)));
                    grantedServiceUnit.setCCMoney(cCMoney);
                }
                grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-4947693337871087377L)));
                grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(9168691967958722926L)));
                grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(1921037210605051926L)));
                grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-1867333303476607306L)));
                // add more AVP as ANY values to grantedServiceUnit
                multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
            }
            {
                RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                requestedServiceUnit.setCCTime(new CCTime(new Integer(-1871169738)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(-2089893070401835261L)));
                        unitValue.setExponent(new Exponent(new Integer(1583212084)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-486266684)));
                    requestedServiceUnit.setCCMoney(cCMoney);
                }
                requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(5820271984254356863L)));
                requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(6571743751426974535L)));
                requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(3283863104264570841L)));
                requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-4284507217422725844L)));
                // add more AVP as ANY values to requestedServiceUnit
                multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
            }
            {
                UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.RATING_CONDITION_CHANGE));
                usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_INDETERMINATE));
                usedServiceUnit.setCCTime(new CCTime(new Integer(77363053)));
                usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(4920456481534157254L)));
                usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(3615820076522978117L)));
                usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(1814041882726817209L)));
                usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-3151402747234723871L)));
                usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(1916743739));
                multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
            }
            multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(-1355407526)));
            multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(93141602)));
            {
                GSUPoolReference gSUPoolReference = new GSUPoolReference();
                gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-1295727689)));
                gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(-3811137022329547826L)));
                    unitValue.setExponent(new Exponent(new Integer(453397907)));
                    gSUPoolReference.setUnitValue(unitValue);
                }
                multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
            }
            multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(819149433)));
            multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(-1448041276)));
            {
                FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.TERMINATE));
                finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string-1277410133"));
                {
                    RedirectServer redirectServer = new RedirectServer();
                    redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv4_Address));
                    redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string-1008680963"));
                    finalUnitIndication.setRedirectServer(redirectServer);
                }
                multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
            }
            multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(1847663767)));
            multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(-157217296)));
            multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(755009638)));
            multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(631295850)));
            multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(-801118353)));
            multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.QHT));
            {
                Trigger trigger = new Trigger();
                trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_TRANSFER_DELAY));
                multipleServicesCreditControl.setTrigger(trigger);
            }
            {
                PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(886901642)));
                pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-564352200"));
                pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Append));
                multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
            }
            multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring-2076205605"));
            {
                AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-1378121565"));
                {
                    Flows flows = new Flows();
                    flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(-1249461919)));
                    flows.addFlowNumber(new FlowNumber(new Integer(1960202562)));
                    aFCorrelationInformation.addFlows(flows);
                }
                multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
            }
            {
                Envelope envelope = new Envelope();
                envelope.setEnvelopeStartTime(new EnvelopeStartTime(-9769785));
                envelope.setEnvelopeEndTime(new EnvelopeEndTime(-2040011783));
                envelope.setCCTotalOctets(new CCTotalOctets(new Long(5969927929643296762L)));
                envelope.setCCInputOctets(new CCInputOctets(new Long(-8650369862097432515L)));
                envelope.setCCOutputOctets(new CCOutputOctets(new Long(2188617819634086317L)));
                envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-7063624297792867004L)));
                // add more AVP as ANY values to envelope
                multipleServicesCreditControl.addEnvelope(envelope);
            }
            multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.DO_NOT_REPORT_ENVELOPES));
            {
                TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(1312324104)));
                multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
            }
            {
                ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-1142368520"));
                serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(115140096)));
                multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
            }
            {
                QoSInformation qoSInformation = new QoSInformation();
                qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_4));
                qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(220230604)));
                qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(895530899)));
                qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-871792615)));
                qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(90991340)));
                qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-1241398972"));
                {
                    AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                    allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(844966153)));
                    allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                    allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                    qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                }
                qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(140562047)));
                qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-846052923)));
                // add more AVP as ANY values to qoSInformation
                multipleServicesCreditControl.setQoSInformation(qoSInformation);
            }
            creditControlRequest.addMultipleServicesCreditControl(multipleServicesCreditControl);
        }
        creditControlRequest.setCCCorrelationId(new CCCorrelationId("octetstring-1433797065"));
        {
            UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
            userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.IMEISV));
            userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring-1866503669"));
            creditControlRequest.setUserEquipmentInfo(userEquipmentInfo);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-635590504.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring233899814"));
            // add more AVP as ANY values to proxyInfo
            creditControlRequest.addProxyInfo(proxyInfo);
        }
        creditControlRequest.addRouteRecord(new diameter.base.RouteRecord("id-1910032965.diameter.com"));
        {
            ServiceInformation serviceInformation = new ServiceInformation();
            {
                SubscriptionId subscriptionId = new SubscriptionId();
                subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_IMSI));
                subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string657779694"));
                serviceInformation.addSubscriptionId(subscriptionId);
            }
            {
                AoCInformation aoCInformation = new AoCInformation();
                {
                    AoCCostInformation aoCCostInformation = new AoCCostInformation();
                    {
                        AccumulatedCost accumulatedCost = new AccumulatedCost();
                        accumulatedCost.setValueDigits(new ValueDigits(new Long(-147226609423470349L)));
                        accumulatedCost.setExponent(new Exponent(new Integer(-134792184)));
                        aoCCostInformation.setAccumulatedCost(accumulatedCost);
                    }
                    {
                        IncrementalCost incrementalCost = new IncrementalCost();
                        incrementalCost.setValueDigits(new ValueDigits(new Long(-2736613789060797928L)));
                        incrementalCost.setExponent(new Exponent(new Integer(-754719687)));
                        aoCCostInformation.addIncrementalCost(incrementalCost);
                    }
                    aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(1435526372)));
                    aoCInformation.setAoCCostInformation(aoCCostInformation);
                }
                {
                    TariffInformation tariffInformation = new TariffInformation();
                    {
                        CurrentTariff currentTariff = new CurrentTariff();
                        currentTariff.setCurrencyCode(new CurrencyCode(new Integer(1440465363)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(8238864161128878156L)));
                            scaleFactor.setExponent(new Exponent(new Integer(1904663851)));
                            currentTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-4475415199741303404L)));
                                unitValue.setExponent(new Exponent(new Integer(1155581296)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(7247317712371562877L)));
                                unitCost.setExponent(new Exponent(new Integer(1769985575)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-345545827)));
                            currentTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setCurrentTariff(currentTariff);
                    }
                    tariffInformation.setTariffTimeChange(new TariffTimeChange(-245453601));
                    {
                        NextTariff nextTariff = new NextTariff();
                        nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-982124296)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(509565675211194738L)));
                            scaleFactor.setExponent(new Exponent(new Integer(-1193551988)));
                            nextTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-6074259360408223480L)));
                                unitValue.setExponent(new Exponent(new Integer(-1310369641)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(-6320891929664001090L)));
                                unitCost.setExponent(new Exponent(new Integer(-301811711)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1455441611)));
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
                    aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(1652940866)));
                    aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                }
                serviceInformation.setAoCInformation(aoCInformation);
            }
            {
                PSInformation pSInformation = new PSInformation();
                pSInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-1759087901)));
                pSInformation.setPDNConnectionID(new PDNConnectionID(new Integer(942446568)));
                pSInformation.setNodeId(new NodeId("utf8string699003217"));
                pSInformation.setRo3GPPPDPType(new Ro3GPPPDPType(new Integer(-69685512)));
                pSInformation.addPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "43.73.104.219")));
                pSInformation.setPDPAddressPrefixLength(new PDPAddressPrefixLength(new Integer(331513321)));
                pSInformation.setDynamicAddressFlag(new DynamicAddressFlag(DynamicAddressFlag.Value.Static));
                pSInformation.setDynamicAddressFlagExtension(new DynamicAddressFlagExtension(DynamicAddressFlagExtension.Value.Dynamic));
                {
                    QoSInformation qoSInformation = new QoSInformation();
                    qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_6));
                    qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(559289177)));
                    qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-603477554)));
                    qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-975576630)));
                    qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(1013147094)));
                    qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-311540433"));
                    {
                        AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                        allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1363445831)));
                        allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                        allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                        qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                    }
                    qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-125967909)));
                    qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1806833253)));
                    // add more AVP as ANY values to qoSInformation
                    pSInformation.setQoSInformation(qoSInformation);
                }
                pSInformation.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "146.190.15.145")));
                pSInformation.setGGSNAddress(new GGSNAddress(new Address(Address.Family.IPV4, "83.39.125.77")));
                pSInformation.setSGWAddress(new SGWAddress(new Address(Address.Family.IPV4, "80.177.229.171")));
                pSInformation.setCGAddress(new CGAddress(new Address(Address.Family.IPV4, "53.15.78.181")));
                pSInformation.setServingNodeType(new ServingNodeType(ServingNodeType.Value.PMIPSGW));
                pSInformation.setSGWChange(new SGWChange(SGWChange.Value.ACR_Start_due_to_SGW_Change));
                pSInformation.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1780836205"));
                pSInformation.setIMSIUnauthenticatedFlag(new IMSIUnauthenticatedFlag(IMSIUnauthenticatedFlag.Value.Unauthenticated));
                pSInformation.setRo3GPPGGSNMCCMNC(new Ro3GPPGGSNMCCMNC("utf8string-1631937673"));
                pSInformation.setRo3GPPNSAPI(new Ro3GPPNSAPI("utf8string-1548467973"));
                pSInformation.setCalledStationId(new diameter.nasreq.CalledStationId("utf8string899909921"));
                pSInformation.setRo3GPPSessionStopIndicator(new Ro3GPPSessionStopIndicator("octetstring-461858237"));
                pSInformation.setRo3GPPSelectionMode(new Ro3GPPSelectionMode("utf8string-352900895"));
                pSInformation.setRo3GPPChargingCharacteristics(new Ro3GPPChargingCharacteristics("utf8string-627353330"));
                pSInformation.setRo3GPPSGSNMCCMNC(new Ro3GPPSGSNMCCMNC("utf8string1626301693"));
                pSInformation.setRo3GPPMSTimeZone(new Ro3GPPMSTimeZone("octetstring1834190274"));
                pSInformation.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring991127894"));
                pSInformation.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring2030714218"));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(357559308)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.Hybrid_Mode));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.CSG_Member));
                    pSInformation.setUserCSGInformation(userCSGInformation);
                }
                pSInformation.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string1224834329"));
                pSInformation.setRo3GPPRATType(new Ro3GPPRATType("octetstring-735607922"));
                {
                    PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                    pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-946753647)));
                    pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-892550098"));
                    pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                    pSInformation.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                }
                pSInformation.setPDPContextType(new PDPContextType(PDPContextType.Value.PRIMARY));
                {
                    OfflineCharging offlineCharging = new OfflineCharging();
                    offlineCharging.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(1252255140)));
                    {
                        TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                        timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                        timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(801418348)));
                        offlineCharging.setTimeQuotaMechanism(timeQuotaMechanism);
                    }
                    offlineCharging.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME_AND_EVENTS));
                    {
                        MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
                        {
                            GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                            grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(485634372));
                            grantedServiceUnit.setCCTime(new CCTime(new Integer(1198183938)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(379186338935660766L)));
                                    unitValue.setExponent(new Exponent(new Integer(-2092316539)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(1967790202)));
                                grantedServiceUnit.setCCMoney(cCMoney);
                            }
                            grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(1618377257087210842L)));
                            grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-4308086366664852744L)));
                            grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-3577733079118312506L)));
                            grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(590331798950273965L)));
                            // add more AVP as ANY values to grantedServiceUnit
                            multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
                        }
                        {
                            RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                            requestedServiceUnit.setCCTime(new CCTime(new Integer(-777057912)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-4495006415312731979L)));
                                    unitValue.setExponent(new Exponent(new Integer(1813799387)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(394355267)));
                                requestedServiceUnit.setCCMoney(cCMoney);
                            }
                            requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-8379550962292852626L)));
                            requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-702697089739406705L)));
                            requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-1045553580587654171L)));
                            requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(3471778987736496572L)));
                            // add more AVP as ANY values to requestedServiceUnit
                            multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
                        }
                        {
                            UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                            usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.VALIDITY_TIME));
                            usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                            usedServiceUnit.setCCTime(new CCTime(new Integer(-1984910774)));
                            usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-8936713562053353966L)));
                            usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(9100260660516454593L)));
                            usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-7087129682183705823L)));
                            usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(3400298389309938934L)));
                            usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(-969261884));
                            multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
                        }
                        multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(-1873209338)));
                        multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(2138319570)));
                        {
                            GSUPoolReference gSUPoolReference = new GSUPoolReference();
                            gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(66074637)));
                            gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(1413905510866827420L)));
                                unitValue.setExponent(new Exponent(new Integer(-1648714)));
                                gSUPoolReference.setUnitValue(unitValue);
                            }
                            multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
                        }
                        multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(1490895402)));
                        multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(1029996912)));
                        {
                            FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                            finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.TERMINATE));
                            finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                            finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string567566550"));
                            {
                                RedirectServer redirectServer = new RedirectServer();
                                redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv4_Address));
                                redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string1501300581"));
                                finalUnitIndication.setRedirectServer(redirectServer);
                            }
                            multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
                        }
                        multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(-2103370579)));
                        multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(-743870363)));
                        multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(912772616)));
                        multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(1404922584)));
                        multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(-964333388)));
                        multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.QUOTA_EXHAUSTED));
                        {
                            Trigger trigger = new Trigger();
                            trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_SDU_ERROR_RATIO));
                            multipleServicesCreditControl.setTrigger(trigger);
                        }
                        {
                            PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                            pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(483811989)));
                            pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-2017583556"));
                            pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Append));
                            multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                        }
                        multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring1958038892"));
                        {
                            AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                            aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-1088749363"));
                            {
                                Flows flows = new Flows();
                                flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(-856659305)));
                                flows.addFlowNumber(new FlowNumber(new Integer(-311494023)));
                                aFCorrelationInformation.addFlows(flows);
                            }
                            multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
                        }
                        {
                            Envelope envelope = new Envelope();
                            envelope.setEnvelopeStartTime(new EnvelopeStartTime(1960762848));
                            envelope.setEnvelopeEndTime(new EnvelopeEndTime(-1602086559));
                            envelope.setCCTotalOctets(new CCTotalOctets(new Long(385571154617089142L)));
                            envelope.setCCInputOctets(new CCInputOctets(new Long(7431613891488729183L)));
                            envelope.setCCOutputOctets(new CCOutputOctets(new Long(8560052535376671677L)));
                            envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-3691750787418923828L)));
                            // add more AVP as ANY values to envelope
                            multipleServicesCreditControl.addEnvelope(envelope);
                        }
                        multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME_AND_EVENTS));
                        {
                            TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                            timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.CONTINUOUS_TIME_PERIOD));
                            timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(392978910)));
                            multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
                        }
                        {
                            ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                            serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-195286109"));
                            serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1078695416)));
                            multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
                        }
                        {
                            QoSInformation qoSInformation = new QoSInformation();
                            qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_3));
                            qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(368078760)));
                            qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-784527587)));
                            qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-98657294)));
                            qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-322143015)));
                            qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring413135725"));
                            {
                                AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                                allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(1474926131)));
                                allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                                allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                                qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                            }
                            qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-975343630)));
                            qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(848439392)));
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
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_5));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1379390278)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(145833599)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1499636139)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-1710281823)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring223514420"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1732776529)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(-1472021633)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1318533512)));
                        // add more AVP as ANY values to qoSInformation
                        trafficDataVolumes.setQoSInformation(qoSInformation);
                    }
                    trafficDataVolumes.setAccountingInputOctets(new AccountingInputOctets(new Long(-8442047885154669246L)));
                    trafficDataVolumes.setAccountingInputPackets(new AccountingInputPackets(new Long(3179808591653761226L)));
                    trafficDataVolumes.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-6331313699658316823L)));
                    trafficDataVolumes.setAccountingOutputPackets(new AccountingOutputPackets(new Long(8251005308483427211L)));
                    trafficDataVolumes.setChangeCondition(new ChangeCondition(new Integer(-1373347106)));
                    trafficDataVolumes.setChangeTime(new ChangeTime(-2122391912));
                    trafficDataVolumes.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring42597964"));
                    pSInformation.addTrafficDataVolumes(trafficDataVolumes);
                }
                {
                    ServiceDataContainer serviceDataContainer = new ServiceDataContainer();
                    {
                        AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                        aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-489163005"));
                        {
                            Flows flows = new Flows();
                            flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(315872062)));
                            flows.addFlowNumber(new FlowNumber(new Integer(-1498312218)));
                            aFCorrelationInformation.addFlows(flows);
                        }
                        serviceDataContainer.setAFCorrelationInformation(aFCorrelationInformation);
                    }
                    serviceDataContainer.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring-96739173"));
                    serviceDataContainer.setAccountingInputOctets(new AccountingInputOctets(new Long(222535258711827047L)));
                    serviceDataContainer.setAccountingOutputOctets(new AccountingOutputOctets(new Long(6989780573816917891L)));
                    serviceDataContainer.setAccountingInputPackets(new AccountingInputPackets(new Long(7751357338926852486L)));
                    serviceDataContainer.setAccountingOutputPackets(new AccountingOutputPackets(new Long(8659831749431587545L)));
                    serviceDataContainer.setLocalSequenceNumber(new LocalSequenceNumber(new Integer(26786432)));
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_3));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-193647327)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-9294089)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(2042431473)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-1901518092)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring1753447102"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-73874788)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1185774454)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1071456016)));
                        // add more AVP as ANY values to qoSInformation
                        serviceDataContainer.setQoSInformation(qoSInformation);
                    }
                    serviceDataContainer.setRatingGroup(new RatingGroup(new Integer(555713993)));
                    serviceDataContainer.setChangeTime(new ChangeTime(-1014630230));
                    serviceDataContainer.setServiceIdentifier(new ServiceIdentifier(new Integer(-1566396529)));
                    {
                        ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                        serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string2026053259"));
                        serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(2030614042)));
                        serviceDataContainer.setServiceSpecificInfo(serviceSpecificInfo);
                    }
                    serviceDataContainer.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "232.194.215.5")));
                    serviceDataContainer.setTimeFirstUsage(new TimeFirstUsage(-1530038001));
                    serviceDataContainer.setTimeLastUsage(new TimeLastUsage(1884393009));
                    serviceDataContainer.setTimeUsage(new TimeUsage(1246803508));
                    serviceDataContainer.addChangeCondition(new ChangeCondition(new Integer(-990756968)));
                    serviceDataContainer.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring220447035"));
                    serviceDataContainer.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string-567577704"));
                    pSInformation.addServiceDataContainer(serviceDataContainer);
                }
                {
                    UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
                    userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.IMEISV));
                    userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring-142188278"));
                    pSInformation.setUserEquipmentInfo(userEquipmentInfo);
                }
                {
                    TerminalInformation terminalInformation = new TerminalInformation();
                    terminalInformation.setIMEI(new IMEI("utf8string-529535922"));
                    terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string1329008579"));
                    // add more AVP as ANY values to terminalInformation
                    pSInformation.setTerminalInformation(terminalInformation);
                }
                pSInformation.setStartTime(new StartTime(-1924345211));
                pSInformation.setStopTime(new StopTime(-86060458));
                pSInformation.setChangeCondition(new ChangeCondition(new Integer(-188490511)));
                pSInformation.setDiagnostics(new Diagnostics(new Integer(-1812107713)));
                pSInformation.setLowPriorityIndicator(new LowPriorityIndicator(LowPriorityIndicator.Value.YES));
                serviceInformation.setPSInformation(pSInformation);
            }
            {
                WLANInformation wLANInformation = new WLANInformation();
                wLANInformation.setWLANSessionId(new WLANSessionId(new Integer(-575118323)));
                wLANInformation.setPDGAddress(new PDGAddress(new Address(Address.Family.IPV4, "216.84.83.104")));
                wLANInformation.setPDGChargingId(new PDGChargingId(new Integer(-1792920247)));
                wLANInformation.setWAGAddress(new WAGAddress(new Address(Address.Family.IPV4, "50.195.156.222")));
                wLANInformation.setWAGPLMNId(new WAGPLMNId("octetstring1648099689"));
                {
                    WLANRadioContainer wLANRadioContainer = new WLANRadioContainer();
                    wLANRadioContainer.setOperatorName(new OperatorName("octetstring-2066678058"));
                    wLANRadioContainer.setLocationInformation(new LocationInformation("octetstring1039305842"));
                    {
                        LocationType locationType = new LocationType();
                        locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.ACTIVATE_DEFERRED_LOCATION));
                        locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string1502487966"));
                        wLANRadioContainer.setLocationType(locationType);
                    }
                    wLANRadioContainer.setWLANTechnology(new WLANTechnology(new Integer(259637752)));
                    wLANInformation.setWLANRadioContainer(wLANRadioContainer);
                }
                wLANInformation.setWLANUELocalIPAddress(new WLANUELocalIPAddress(new Address(Address.Family.IPV4, "22.215.123.43")));
                serviceInformation.setWLANInformation(wLANInformation);
            }
            {
                IMSInformation iMSInformation = new IMSInformation();
                {
                    EventType eventType = new EventType();
                    eventType.setSIPMethod(new SIPMethod("utf8string-2012384722"));
                    eventType.setIMSEvent(new IMSEvent("utf8string-134174599"));
                    eventType.setExpires(new Expires(new Integer(1265479655)));
                    iMSInformation.setEventType(eventType);
                }
                iMSInformation.setRoleOfNode(new RoleOfNode(RoleOfNode.Value.ORIGINATING_ROLE));
                iMSInformation.setNodeFunctionality(new NodeFunctionality(NodeFunctionality.Value.S_GW));
                iMSInformation.setUserSessionID(new UserSessionID("utf8string-738346240"));
                iMSInformation.setOutgoingSessionId(new OutgoingSessionId("utf8string2084066679"));
                iMSInformation.addCallingPartyAddress(new CallingPartyAddress("utf8string-263276079"));
                iMSInformation.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY_1));
                iMSInformation.setCalledPartyAddress(new CalledPartyAddress("utf8string-752107288"));
                iMSInformation.addCalledAssertedIdentity(new CalledAssertedIdentity("utf8string33137187"));
                iMSInformation.setNumberPortabilityRoutingInformation(new NumberPortabilityRoutingInformation("utf8string-384138309"));
                iMSInformation.setCarrierSelectRoutingInformation(new CarrierSelectRoutingInformation("utf8string-1758720660"));
                iMSInformation.setAlternateChargedPartyAddress(new AlternateChargedPartyAddress("utf8string-500881449"));
                iMSInformation.setRequestedPartyAddress(new RequestedPartyAddress("utf8string-803128004"));
                iMSInformation.addAssociatedURI(new AssociatedURI("utf8string1767833388"));
                {
                    TimeStamps timeStamps = new TimeStamps();
                    timeStamps.setSIPRequestTimestamp(new SIPRequestTimestamp(1478299911));
                    timeStamps.setSIPResponseTimestamp(new SIPResponseTimestamp(188217894));
                    timeStamps.setSIPRequestTimestampFraction(new SIPRequestTimestampFraction(new Integer(1750720157)));
                    timeStamps.setSIPResponseTimestampFraction(new SIPResponseTimestampFraction(new Integer(-1591257807)));
                    iMSInformation.setTimeStamps(timeStamps);
                }
                {
                    ApplicationServerInformation applicationServerInformation = new ApplicationServerInformation();
                    applicationServerInformation.setApplicationServer(new ApplicationServer("utf8string-1385976148"));
                    applicationServerInformation.addApplicationProvidedCalledPartyAddress(new ApplicationProvidedCalledPartyAddress("utf8string-1798303328"));
                    iMSInformation.addApplicationServerInformation(applicationServerInformation);
                }
                {
                    InterOperatorIdentifier interOperatorIdentifier = new InterOperatorIdentifier();
                    interOperatorIdentifier.setOriginatingIOI(new OriginatingIOI("utf8string-66255840"));
                    interOperatorIdentifier.setTerminatingIOI(new TerminatingIOI("utf8string460017670"));
                    iMSInformation.addInterOperatorIdentifier(interOperatorIdentifier);
                }
                iMSInformation.setIMSChargingIdentifier(new IMSChargingIdentifier("utf8string1168805243"));
                iMSInformation.addSDPSessionDescription(new SDPSessionDescription("utf8string1158361736"));
                {
                    SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                    sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string-1570239916"));
                    sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string811374519"));
                    sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Not_Inserted));
                    sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                    sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_realm_used));
                    sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.unknown));
                    sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string-1064249776"));
                    sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string-2004119064"));
                    sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(2061086585)));
                    sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring1838882458"));
                    sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Answer));
                    iMSInformation.addSDPMediaComponent(sDPMediaComponent);
                }
                iMSInformation.setServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "228.219.70.35")));
                {
                    ServerCapabilities serverCapabilities = new ServerCapabilities();
                    serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(1785050658)));
                    serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(1050423285)));
                    serverCapabilities.addServerName(new ServerName("utf8string-1085911860"));
                    // add more AVP as ANY values to serverCapabilities
                    iMSInformation.setServerCapabilities(serverCapabilities);
                }
                {
                    TrunkGroupID trunkGroupID = new TrunkGroupID();
                    trunkGroupID.setIncomingTrunkGroupID(new IncomingTrunkGroupID("utf8string-2117344395"));
                    trunkGroupID.setOutgoingTrunkGroupID(new OutgoingTrunkGroupID("utf8string2085031739"));
                    iMSInformation.setTrunkGroupID(trunkGroupID);
                }
                iMSInformation.setBearerService(new BearerService("octetstring371735327"));
                iMSInformation.setServiceId(new ServiceId("utf8string-1277855311"));
                {
                    ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                    serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-1528083035"));
                    serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1924919192)));
                    iMSInformation.addServiceSpecificInfo(serviceSpecificInfo);
                }
                {
                    MessageBody messageBody = new MessageBody();
                    messageBody.setContentType(new ContentType("utf8string-1412659232"));
                    messageBody.setContentLength(new ContentLength(new Integer(-1048517277)));
                    messageBody.setContentDisposition(new ContentDisposition("utf8string1101313887"));
                    messageBody.setOriginator(new Originator(Originator.Value.Calling_Party));
                    iMSInformation.addMessageBody(messageBody);
                }
                iMSInformation.setCauseCode(new CauseCode(new Integer(-1102317988)));
                iMSInformation.setAccessNetworkInformation(new AccessNetworkInformation("octetstring-1193955422"));
                {
                    EarlyMediaDescription earlyMediaDescription = new EarlyMediaDescription();
                    {
                        SDPTimeStamps sDPTimeStamps = new SDPTimeStamps();
                        sDPTimeStamps.setSDPOfferTimestamp(new SDPOfferTimestamp(1642265630));
                        sDPTimeStamps.setSDPAnswerTimestamp(new SDPAnswerTimestamp(1859161519));
                        earlyMediaDescription.setSDPTimeStamps(sDPTimeStamps);
                    }
                    {
                        SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                        sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string1039458315"));
                        sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string469986331"));
                        sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                        sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Inserted));
                        sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_Realm_Not_used));
                        sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.calling_party));
                        sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string-242408475"));
                        sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string1274886992"));
                        sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-327552905)));
                        sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring-1423043120"));
                        sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Answer));
                        earlyMediaDescription.addSDPMediaComponent(sDPMediaComponent);
                    }
                    earlyMediaDescription.addSDPSessionDescription(new SDPSessionDescription("utf8string392329539"));
                    iMSInformation.addEarlyMediaDescription(earlyMediaDescription);
                }
                iMSInformation.setIMSCommunicationServiceIdentifier(new IMSCommunicationServiceIdentifier("utf8string-1084637543"));
                iMSInformation.setOnlineChargingFlag(new OnlineChargingFlag(OnlineChargingFlag.Value.ECF_address_provided));
                {
                    RealTimeTariffInformation realTimeTariffInformation = new RealTimeTariffInformation();
                    {
                        TariffInformation tariffInformation = new TariffInformation();
                        {
                            CurrentTariff currentTariff = new CurrentTariff();
                            currentTariff.setCurrencyCode(new CurrencyCode(new Integer(302650857)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(-3275969157847174436L)));
                                scaleFactor.setExponent(new Exponent(new Integer(842549510)));
                                currentTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(2480594599543211623L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1602226389)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(1671351578744907043L)));
                                    unitCost.setExponent(new Exponent(new Integer(-425742751)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1049718241)));
                                currentTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setCurrentTariff(currentTariff);
                        }
                        tariffInformation.setTariffTimeChange(new TariffTimeChange(-188933650));
                        {
                            NextTariff nextTariff = new NextTariff();
                            nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-524580155)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(7663190541285306177L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-1032650299)));
                                nextTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(5920142981954213586L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1950985247)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(-8894963754440775979L)));
                                    unitCost.setExponent(new Exponent(new Integer(1558767225)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1383802121)));
                                nextTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setNextTariff(nextTariff);
                        }
                        realTimeTariffInformation.setTariffInformation(tariffInformation);
                    }
                    realTimeTariffInformation.setTariffXML(new TariffXML("utf8string-612151337"));
                    iMSInformation.setRealTimeTariffInformation(realTimeTariffInformation);
                }
                iMSInformation.setAccountExpiration(new AccountExpiration(2098757852));
                iMSInformation.setInitialIMSChargingIdentifier(new InitialIMSChargingIdentifier("utf8string475779427"));
                serviceInformation.setIMSInformation(iMSInformation);
            }
            {
                MMSInformation mMSInformation = new MMSInformation();
                {
                    OriginatorAddress originatorAddress = new OriginatorAddress();
                    originatorAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.MSISDN));
                    originatorAddress.setAddressData(new AddressData("utf8string-1220983607"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-222112220"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1470786688"));
                        originatorAddress.setAddressDomain(addressDomain);
                    }
                    mMSInformation.setOriginatorAddress(originatorAddress);
                }
                {
                    RecipientAddress recipientAddress = new RecipientAddress();
                    recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.Other));
                    recipientAddress.setAddressData(new AddressData("utf8string-1440506767"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string1429518117"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-330381233"));
                        recipientAddress.setAddressDomain(addressDomain);
                    }
                    recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.TO));
                    mMSInformation.addRecipientAddress(recipientAddress);
                }
                mMSInformation.setSubmissionTime(new SubmissionTime(-510230055));
                {
                    MMContentType mMContentType = new MMContentType();
                    mMContentType.setTypeNumber(new TypeNumber(new Integer(1708696448)));
                    mMContentType.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string-1390350500"));
                    mMContentType.setContentSize(new ContentSize(new Integer(1131709070)));
                    {
                        AdditionalContentInformation additionalContentInformation = new AdditionalContentInformation();
                        additionalContentInformation.setTypeNumber(new TypeNumber(new Integer(1873038642)));
                        additionalContentInformation.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string-1374074029"));
                        additionalContentInformation.setContentSize(new ContentSize(new Integer(-1807633142)));
                        mMContentType.addAdditionalContentInformation(additionalContentInformation);
                    }
                    mMSInformation.setMMContentType(mMContentType);
                }
                mMSInformation.setPriority(new Priority(Priority.Value.Low));
                mMSInformation.setMessageID(new MessageID("utf8string1355154495"));
                mMSInformation.setMessageType(new MessageType(MessageType.Value.m_retrive_conf));
                mMSInformation.setMessageSize(new MessageSize(new Integer(-1939635310)));
                {
                    MessageClass messageClass = new MessageClass();
                    messageClass.setClassIdentifier(new ClassIdentifier(ClassIdentifier.Value.Auto));
                    messageClass.setTokenText(new TokenText("utf8string-522126092"));
                    mMSInformation.setMessageClass(messageClass);
                }
                mMSInformation.setDeliveryReportRequested(new DeliveryReportRequested(DeliveryReportRequested.Value.No));
                mMSInformation.setReadReplyReportRequested(new ReadReplyReportRequested(ReadReplyReportRequested.Value.No));
                mMSInformation.setMMBoxStorageRequested(new MMBoxStorageRequested(MMBoxStorageRequested.Value.Yes));
                mMSInformation.setApplicID(new ApplicID("utf8string-399407526"));
                mMSInformation.setReplyApplicID(new ReplyApplicID("utf8string39304969"));
                mMSInformation.setAuxApplicInfo(new AuxApplicInfo("utf8string1456363819"));
                mMSInformation.setContentClass(new ContentClass(ContentClass.Value.video_basic));
                mMSInformation.setDRMContent(new DRMContent(DRMContent.Value.Yes));
                mMSInformation.setAdaptations(new Adaptations(Adaptations.Value.No));
                mMSInformation.setVASPId(new VASPId("utf8string-50985331"));
                mMSInformation.setVASId(new VASId("utf8string1636153278"));
                serviceInformation.setMMSInformation(mMSInformation);
            }
            {
                LCSInformation lCSInformation = new LCSInformation();
                {
                    LCSClientID lCSClientID = new LCSClientID();
                    lCSClientID.setLCSClientType(new LCSClientType(LCSClientType.Value.LAWFUL_INTERCEPT_SERVICES));
                    lCSClientID.setLCSClientExternalID(new LCSClientExternalID("utf8string-710397251"));
                    lCSClientID.setLCSClientDialedByMS(new LCSClientDialedByMS("utf8string553772340"));
                    {
                        LCSClientName lCSClientName = new LCSClientName();
                        lCSClientName.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string54429836"));
                        lCSClientName.setLCSNameString(new LCSNameString("utf8string1392906006"));
                        lCSClientName.setLCSFormatIndicator(new LCSFormatIndicator(LCSFormatIndicator.Value.URL));
                        lCSClientID.setLCSClientName(lCSClientName);
                    }
                    lCSClientID.setLCSAPN(new LCSAPN("utf8string964562063"));
                    {
                        LCSRequestorID lCSRequestorID = new LCSRequestorID();
                        lCSRequestorID.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string431966009"));
                        lCSRequestorID.setLCSRequestorIDString(new LCSRequestorIDString("utf8string-965038964"));
                        lCSClientID.setLCSRequestorID(lCSRequestorID);
                    }
                    lCSInformation.setLCSClientID(lCSClientID);
                }
                {
                    LocationType locationType = new LocationType();
                    locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.CURRENT_LOCATION));
                    locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string1311114558"));
                    lCSInformation.setLocationType(locationType);
                }
                lCSInformation.setLocationEstimate(new LocationEstimate("utf8string1210458185"));
                lCSInformation.setPositioningData(new PositioningData("utf8string-2002091297"));
                lCSInformation.setRo3GPPIMSI(new Ro3GPPIMSI("utf8string-1572650140"));
                lCSInformation.setMSISDN(new MSISDN("octetstring1206371284"));
                serviceInformation.setLCSInformation(lCSInformation);
            }
            {
                PoCInformation poCInformation = new PoCInformation();
                poCInformation.setPoCServerRole(new PoCServerRole(PoCServerRole.Value.Controlling_PoC_Server));
                poCInformation.setPoCSessionType(new PoCSessionType(PoCSessionType.Value.pre_arranged_PoC_group_session));
                {
                    PoCUserRole poCUserRole = new PoCUserRole();
                    poCUserRole.setPoCUserRoleIds(new PoCUserRoleIds("utf8string-222879059"));
                    poCUserRole.setPoCUserRoleinfoUnits(new PoCUserRoleinfoUnits(PoCUserRoleinfoUnits.Value.Session_Owner));
                    poCInformation.setPoCUserRole(poCUserRole);
                }
                poCInformation.setPoCSessionInitiationType(new PoCSessionInitiationType(PoCSessionInitiationType.Value.Pre_established));
                poCInformation.setPoCEventType(new PoCEventType(PoCEventType.Value.Normal));
                poCInformation.setNumberOfParticipants(new NumberOfParticipants(new Integer(-683001994)));
                poCInformation.addParticipantsInvolved(new ParticipantsInvolved("utf8string1033469732"));
                {
                    ParticipantGroup participantGroup = new ParticipantGroup();
                    participantGroup.setCalledPartyAddress(new CalledPartyAddress("utf8string-1650556462"));
                    participantGroup.setParticipantAccessPriority(new ParticipantAccessPriority(ParticipantAccessPriority.Value.Low_priority));
                    participantGroup.setUserParticipatingType(new UserParticipatingType(UserParticipatingType.Value.Normal));
                    poCInformation.addParticipantGroup(participantGroup);
                }
                {
                    TalkBurstExchange talkBurstExchange = new TalkBurstExchange();
                    talkBurstExchange.setPoCChangeTime(new PoCChangeTime(2058083630));
                    talkBurstExchange.setNumberOfTalkBursts(new NumberOfTalkBursts(new Integer(-486918775)));
                    talkBurstExchange.setTalkBurstVolume(new TalkBurstVolume(new Integer(-1492620174)));
                    talkBurstExchange.setTalkBurstTime(new TalkBurstTime(new Integer(-773245417)));
                    talkBurstExchange.setNumberOfReceivedTalkBursts(new NumberOfReceivedTalkBursts(new Integer(232077065)));
                    talkBurstExchange.setReceivedTalkBurstVolume(new ReceivedTalkBurstVolume(new Integer(1340810358)));
                    talkBurstExchange.setReceivedTalkBurstTime(new ReceivedTalkBurstTime(new Integer(1304219726)));
                    talkBurstExchange.setNumberOfParticipants(new NumberOfParticipants(new Integer(-1866287973)));
                    talkBurstExchange.setPoCChangeCondition(new PoCChangeCondition(PoCChangeCondition.Value.tariffTime));
                    poCInformation.addTalkBurstExchange(talkBurstExchange);
                }
                poCInformation.setPoCControllingAddress(new PoCControllingAddress("utf8string-1149332059"));
                poCInformation.setPoCGroupName(new PoCGroupName("utf8string-1429598979"));
                poCInformation.setPoCSessionId(new PoCSessionId("utf8string1653762655"));
                poCInformation.setChargedParty(new ChargedParty("utf8string1651899987"));
                serviceInformation.setPoCInformation(poCInformation);
            }
            {
                MBMSInformation mBMSInformation = new MBMSInformation();
                mBMSInformation.setTMGI(new TMGI("octetstring-965334633"));
                mBMSInformation.setMBMSServiceType(new MBMSServiceType(MBMSServiceType.Value.BROADCAST));
                mBMSInformation.setMBMSUserServiceType(new MBMSUserServiceType(MBMSUserServiceType.Value.STREAMING));
                mBMSInformation.setFileRepairSupported(new FileRepairSupported(FileRepairSupported.Value.NOT_SUPPORTED));
                mBMSInformation.setRequiredMBMSBearerCapabilities(new RequiredMBMSBearerCapabilities("utf8string-218123653"));
                mBMSInformation.setMBMS2G3GIndicator(new MBMS2G3GIndicator(MBMS2G3GIndicator.Value.ONLY_2G));
                mBMSInformation.setRAI(new RAI("utf8string931868345"));
                mBMSInformation.addMBMSServiceArea(new MBMSServiceArea("octetstring-1908963691"));
                mBMSInformation.setMBMSSessionIdentity(new MBMSSessionIdentity("octetstring-971646052"));
                mBMSInformation.setCNIPMulticastDistribution(new CNIPMulticastDistribution(CNIPMulticastDistribution.Value.NO_IP_MULTICAST));
                mBMSInformation.setMBMSGWAddress(new MBMSGWAddress(new Address(Address.Family.IPV4, "197.114.27.195")));
                serviceInformation.setMBMSInformation(mBMSInformation);
            }
            {
                SMSInformation sMSInformation = new SMSInformation();
                sMSInformation.setSMSNode(new SMSNode(SMSNode.Value.SMS_SC));
                sMSInformation.setClientAddress(new ClientAddress(new Address(Address.Family.IPV4, "165.221.120.218")));
                sMSInformation.setOriginatorSCCPAddress(new OriginatorSCCPAddress(new Address(Address.Family.IPV4, "74.198.23.245")));
                sMSInformation.setSMSCAddress(new SMSCAddress(new Address(Address.Family.IPV4, "32.38.134.167")));
                sMSInformation.setDataCodingScheme(new DataCodingScheme(new Integer(-131926900)));
                sMSInformation.setSMDischargeTime(new SMDischargeTime(101289075));
                sMSInformation.setSMMessageType(new SMMessageType(SMMessageType.Value.SM_Service_Request));
                {
                    OriginatorInterface originatorInterface = new OriginatorInterface();
                    originatorInterface.setInterfaceId(new InterfaceId("utf8string1673867987"));
                    originatorInterface.setInterfaceText(new InterfaceText("utf8string821985507"));
                    originatorInterface.setInterfacePort(new InterfacePort("utf8string-1781479111"));
                    originatorInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.MOBILE_TERMINATING));
                    sMSInformation.setOriginatorInterface(originatorInterface);
                }
                sMSInformation.setSMProtocolID(new SMProtocolID("octetstring105300075"));
                sMSInformation.setReplyPathRequested(new ReplyPathRequested(ReplyPathRequested.Value.Reply_path_Set));
                sMSInformation.setSMStatus(new SMStatus("octetstring874537293"));
                sMSInformation.setSMUserDataHeader(new SMUserDataHeader("octetstring-1755419925"));
                sMSInformation.setNumberOfMessagesSent(new NumberOfMessagesSent(new Integer(1363809722)));
                {
                    RecipientInfo recipientInfo = new RecipientInfo();
                    {
                        DestinationInterface destinationInterface = new DestinationInterface();
                        destinationInterface.setInterfaceId(new InterfaceId("utf8string562495891"));
                        destinationInterface.setInterfaceText(new InterfaceText("utf8string435815240"));
                        destinationInterface.setInterfacePort(new InterfacePort("utf8string-549304414"));
                        destinationInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.APPLICATION_TERMINATION));
                        recipientInfo.setDestinationInterface(destinationInterface);
                    }
                    {
                        RecipientAddress recipientAddress = new RecipientAddress();
                        recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv4_Address));
                        recipientAddress.setAddressData(new AddressData("utf8string504106035"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string1379852507"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1851124167"));
                            recipientAddress.setAddressDomain(addressDomain);
                        }
                        recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.CC));
                        recipientInfo.addRecipientAddress(recipientAddress);
                    }
                    {
                        RecipientReceivedAddress recipientReceivedAddress = new RecipientReceivedAddress();
                        recipientReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IMSI));
                        recipientReceivedAddress.setAddressData(new AddressData("utf8string-381174554"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string-233115064"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1305684920"));
                            recipientReceivedAddress.setAddressDomain(addressDomain);
                        }
                        recipientInfo.addRecipientReceivedAddress(recipientReceivedAddress);
                    }
                    recipientInfo.setRecipientSCCPAddress(new RecipientSCCPAddress(new Address(Address.Family.IPV4, "55.172.52.24")));
                    recipientInfo.setSMProtocolID(new SMProtocolID("octetstring790104440"));
                    sMSInformation.addRecipientInfo(recipientInfo);
                }
                {
                    OriginatorReceivedAddress originatorReceivedAddress = new OriginatorReceivedAddress();
                    originatorReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv4_Address));
                    originatorReceivedAddress.setAddressData(new AddressData("utf8string592195527"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-607767615"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1777857504"));
                        originatorReceivedAddress.setAddressDomain(addressDomain);
                    }
                    sMSInformation.setOriginatorReceivedAddress(originatorReceivedAddress);
                }
                sMSInformation.setSMServiceType(new SMServiceType(SMServiceType.Value.VAS4SMS_Filtering));
                serviceInformation.setSMSInformation(sMSInformation);
            }
            {
                MMTelInformation mMTelInformation = new MMTelInformation();
                {
                    SupplementaryService supplementaryService = new SupplementaryService();
                    supplementaryService.setServiceType(new ServiceType(new Integer(-1373517726)));
                    supplementaryService.setServiceMode(new ServiceMode(new Integer(708492168)));
                    supplementaryService.setNumberOfDiversions(new NumberOfDiversions(new Integer(1936822212)));
                    supplementaryService.setAssociatedPartyAddress(new AssociatedPartyAddress("utf8string-2032391801"));
                    supplementaryService.setServiceId(new ServiceId("utf8string2144527118"));
                    supplementaryService.setChangeTime(new ChangeTime(1771419713));
                    supplementaryService.setNumberOfParticipants(new NumberOfParticipants(new Integer(929466600)));
                    supplementaryService.setParticipantActionType(new ParticipantActionType(ParticipantActionType.Value.INVITE_INTO_CONF));
                    supplementaryService.setCUGInformation(new CUGInformation("octetstring1280136400"));
                    {
                        AoCInformation aoCInformation = new AoCInformation();
                        {
                            AoCCostInformation aoCCostInformation = new AoCCostInformation();
                            {
                                AccumulatedCost accumulatedCost = new AccumulatedCost();
                                accumulatedCost.setValueDigits(new ValueDigits(new Long(7362256294552868457L)));
                                accumulatedCost.setExponent(new Exponent(new Integer(936561138)));
                                aoCCostInformation.setAccumulatedCost(accumulatedCost);
                            }
                            {
                                IncrementalCost incrementalCost = new IncrementalCost();
                                incrementalCost.setValueDigits(new ValueDigits(new Long(-969386351625126003L)));
                                incrementalCost.setExponent(new Exponent(new Integer(117604414)));
                                aoCCostInformation.addIncrementalCost(incrementalCost);
                            }
                            aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(1254298569)));
                            aoCInformation.setAoCCostInformation(aoCCostInformation);
                        }
                        {
                            TariffInformation tariffInformation = new TariffInformation();
                            {
                                CurrentTariff currentTariff = new CurrentTariff();
                                currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-1281584804)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(4232957865386241375L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(42021105)));
                                    currentTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.ADD_ON_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(743662405093291576L)));
                                        unitValue.setExponent(new Exponent(new Integer(733353787)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(-586216466636869870L)));
                                        unitCost.setExponent(new Exponent(new Integer(908162695)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1410523419)));
                                    currentTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setCurrentTariff(currentTariff);
                            }
                            tariffInformation.setTariffTimeChange(new TariffTimeChange(1263181745));
                            {
                                NextTariff nextTariff = new NextTariff();
                                nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-949393454)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(7507252680277939827L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(1369119112)));
                                    nextTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(2118699564423109543L)));
                                        unitValue.setExponent(new Exponent(new Integer(1478080881)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(6252191196707331169L)));
                                        unitCost.setExponent(new Exponent(new Integer(-642906774)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-538542169)));
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
                            aoCSubscriptionInformation.setAoCFormat(new AoCFormat(AoCFormat.Value.CAI));
                            aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(812457314)));
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
                serviceGenericInformation.setApplicationServerID(new ApplicationServerID("utf8string1589439029"));
                serviceGenericInformation.setApplicationServiceType(new ApplicationServiceType("utf8string1031824873"));
                serviceGenericInformation.setApplicationSessionID(new ApplicationSessionID("utf8string660911654"));
                serviceGenericInformation.setDeliveryStatus(new DeliveryStatus("utf8string-115925980"));
                serviceInformation.setServiceGenericInformation(serviceGenericInformation);
            }
            {
                IMInformation iMInformation = new IMInformation();
                iMInformation.setTotalNumberOfMessagesSent(new TotalNumberOfMessagesSent(new Integer(1265994677)));
                iMInformation.setTotalNumberOfMessagesExploded(new TotalNumberOfMessagesExploded(new Integer(1978427909)));
                iMInformation.setNumberOfMessagesSuccessfullySent(new NumberOfMessagesSuccessfullySent(new Integer(1483402325)));
                iMInformation.setNumberOfMessagesSuccessfullyExploded(new NumberOfMessagesSuccessfullyExploded(new Integer(1805666500)));
                serviceInformation.setIMInformation(iMInformation);
            }
            {
                DCDInformation dCDInformation = new DCDInformation();
                dCDInformation.setContentID(new ContentID("utf8string1888230258"));
                dCDInformation.setContentproviderID(new ContentproviderID("utf8string558298063"));
                serviceInformation.setDCDInformation(dCDInformation);
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
        creditControlAnswer.setSessionId(new diameter.base.SessionId("utf8string1827548061"));
        creditControlAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-930371232)));
        creditControlAnswer.setOriginHost(new diameter.base.OriginHost("id-606396695.diameter.com"));
        creditControlAnswer.setOriginRealm(new diameter.base.OriginRealm("id848495396.diameter.com"));
        creditControlAnswer.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(743286450)));
        creditControlAnswer.setCCRequestType(new CCRequestType(CCRequestType.Value.TERMINATION_REQUEST));
        creditControlAnswer.setCCRequestNumber(new CCRequestNumber(new Integer(888986735)));
        creditControlAnswer.setCCSessionFailover(new CCSessionFailover(CCSessionFailover.Value.FAILOVER_NOT_SUPPORTED));
        {
            MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
            {
                GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(739179581));
                grantedServiceUnit.setCCTime(new CCTime(new Integer(1308651918)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(-8701645798003794462L)));
                        unitValue.setExponent(new Exponent(new Integer(831829779)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(244621876)));
                    grantedServiceUnit.setCCMoney(cCMoney);
                }
                grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(1871228980749167315L)));
                grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-7079625999072398458L)));
                grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(4867827701353624101L)));
                grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(3646795054267161156L)));
                // add more AVP as ANY values to grantedServiceUnit
                multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
            }
            {
                RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                requestedServiceUnit.setCCTime(new CCTime(new Integer(-1137423827)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(-3961106244636927620L)));
                        unitValue.setExponent(new Exponent(new Integer(-790141691)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(299917701)));
                    requestedServiceUnit.setCCMoney(cCMoney);
                }
                requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-522237968662702511L)));
                requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(8317967466451398209L)));
                requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-7545324747487602751L)));
                requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(1825694157601742009L)));
                // add more AVP as ANY values to requestedServiceUnit
                multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
            }
            {
                UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.THRESHOLD));
                usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                usedServiceUnit.setCCTime(new CCTime(new Integer(-179124115)));
                usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-518989569820442435L)));
                usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-185147344438041863L)));
                usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-327284340236165446L)));
                usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(5543783759944816302L)));
                usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(956934810));
                multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
            }
            multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(1670136218)));
            multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(1179665177)));
            {
                GSUPoolReference gSUPoolReference = new GSUPoolReference();
                gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-1286178341)));
                gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(8462309691724073879L)));
                    unitValue.setExponent(new Exponent(new Integer(-984732189)));
                    gSUPoolReference.setUnitValue(unitValue);
                }
                multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
            }
            multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(642035370)));
            multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(1626839260)));
            {
                FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.REDIRECT));
                finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string-1901210084"));
                {
                    RedirectServer redirectServer = new RedirectServer();
                    redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv4_Address));
                    redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string-590119769"));
                    finalUnitIndication.setRedirectServer(redirectServer);
                }
                multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
            }
            multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(1260492066)));
            multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(-1881925382)));
            multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(38097424)));
            multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(1853099887)));
            multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(1373274150)));
            multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.POOL_EXHAUSTED));
            {
                Trigger trigger = new Trigger();
                trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGE_IN_USER_PARTICIPATING_TYPE));
                multipleServicesCreditControl.setTrigger(trigger);
            }
            {
                PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-389681229)));
                pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring-1550946661"));
                pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
            }
            multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring744157636"));
            {
                AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-10865535"));
                {
                    Flows flows = new Flows();
                    flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(619498560)));
                    flows.addFlowNumber(new FlowNumber(new Integer(266155871)));
                    aFCorrelationInformation.addFlows(flows);
                }
                multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
            }
            {
                Envelope envelope = new Envelope();
                envelope.setEnvelopeStartTime(new EnvelopeStartTime(-1439926256));
                envelope.setEnvelopeEndTime(new EnvelopeEndTime(54854135));
                envelope.setCCTotalOctets(new CCTotalOctets(new Long(-1465589359809046213L)));
                envelope.setCCInputOctets(new CCInputOctets(new Long(8406098519499366918L)));
                envelope.setCCOutputOctets(new CCOutputOctets(new Long(-7832966341028466195L)));
                envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-2543208021813009031L)));
                // add more AVP as ANY values to envelope
                multipleServicesCreditControl.addEnvelope(envelope);
            }
            multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES));
            {
                TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.CONTINUOUS_TIME_PERIOD));
                timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(-381490922)));
                multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
            }
            {
                ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-177090251"));
                serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1046061684)));
                multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
            }
            {
                QoSInformation qoSInformation = new QoSInformation();
                qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_8));
                qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1329871582)));
                qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-40838206)));
                qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(44576494)));
                qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-1039560524)));
                qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-2028184248"));
                {
                    AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                    allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1181368566)));
                    allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                    allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                    qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                }
                qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1845930339)));
                qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-1850269089)));
                // add more AVP as ANY values to qoSInformation
                multipleServicesCreditControl.setQoSInformation(qoSInformation);
            }
            creditControlAnswer.addMultipleServicesCreditControl(multipleServicesCreditControl);
        }
        {
            CostInformation costInformation = new CostInformation();
            {
                UnitValue unitValue = new UnitValue();
                unitValue.setValueDigits(new ValueDigits(new Long(-5199254084636953577L)));
                unitValue.setExponent(new Exponent(new Integer(-1108007954)));
                costInformation.setUnitValue(unitValue);
            }
            costInformation.setCurrencyCode(new CurrencyCode(new Integer(-1093754686)));
            costInformation.setCostUnit(new CostUnit("utf8string-1098456518"));
            creditControlAnswer.setCostInformation(costInformation);
        }
        creditControlAnswer.setLowBalanceIndication(new LowBalanceIndication(LowBalanceIndication.Value.YES));
        {
            RemainingBalance remainingBalance = new RemainingBalance();
            {
                UnitValue unitValue = new UnitValue();
                unitValue.setValueDigits(new ValueDigits(new Long(2781671468743782241L)));
                unitValue.setExponent(new Exponent(new Integer(1867658263)));
                remainingBalance.setUnitValue(unitValue);
            }
            remainingBalance.setCurrencyCode(new CurrencyCode(new Integer(1694780133)));
            creditControlAnswer.setRemainingBalance(remainingBalance);
        }
        creditControlAnswer.setCreditControlFailureHandling(new CreditControlFailureHandling(CreditControlFailureHandling.Value.TERMINATE));
        creditControlAnswer.setDirectDebitingFailureHandling(new DirectDebitingFailureHandling(DirectDebitingFailureHandling.Value.TERMINATE_OR_BUFFER));
        creditControlAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain-1311264034.com", URI.Scheme.AAAS, (short)1347, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        creditControlAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_HOST));
        creditControlAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(1194589662)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-542420972.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring739271688"));
            // add more AVP as ANY values to proxyInfo
            creditControlAnswer.addProxyInfo(proxyInfo);
        }
        creditControlAnswer.addRouteRecord(new diameter.base.RouteRecord("id160472793.diameter.com"));
        {
            ServiceInformation serviceInformation = new ServiceInformation();
            {
                SubscriptionId subscriptionId = new SubscriptionId();
                subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_IMSI));
                subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string-1209556121"));
                serviceInformation.addSubscriptionId(subscriptionId);
            }
            {
                AoCInformation aoCInformation = new AoCInformation();
                {
                    AoCCostInformation aoCCostInformation = new AoCCostInformation();
                    {
                        AccumulatedCost accumulatedCost = new AccumulatedCost();
                        accumulatedCost.setValueDigits(new ValueDigits(new Long(8137387764861784631L)));
                        accumulatedCost.setExponent(new Exponent(new Integer(-462214546)));
                        aoCCostInformation.setAccumulatedCost(accumulatedCost);
                    }
                    {
                        IncrementalCost incrementalCost = new IncrementalCost();
                        incrementalCost.setValueDigits(new ValueDigits(new Long(4377461306239153550L)));
                        incrementalCost.setExponent(new Exponent(new Integer(1609988689)));
                        aoCCostInformation.addIncrementalCost(incrementalCost);
                    }
                    aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(762375222)));
                    aoCInformation.setAoCCostInformation(aoCCostInformation);
                }
                {
                    TariffInformation tariffInformation = new TariffInformation();
                    {
                        CurrentTariff currentTariff = new CurrentTariff();
                        currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-1939784622)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(693344860956456459L)));
                            scaleFactor.setExponent(new Exponent(new Integer(-283271250)));
                            currentTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.UNKNOWN));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-9164662912047495994L)));
                                unitValue.setExponent(new Exponent(new Integer(1818795279)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(8977344466451540157L)));
                                unitCost.setExponent(new Exponent(new Integer(-1437199680)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-566878296)));
                            currentTariff.addRateElement(rateElement);
                        }
                        tariffInformation.setCurrentTariff(currentTariff);
                    }
                    tariffInformation.setTariffTimeChange(new TariffTimeChange(307622065));
                    {
                        NextTariff nextTariff = new NextTariff();
                        nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-29255749)));
                        {
                            ScaleFactor scaleFactor = new ScaleFactor();
                            scaleFactor.setValueDigits(new ValueDigits(new Long(8352968886032000644L)));
                            scaleFactor.setExponent(new Exponent(new Integer(1594802534)));
                            nextTariff.setScaleFactor(scaleFactor);
                        }
                        {
                            RateElement rateElement = new RateElement();
                            rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.SERVICE_SPECIFIC_UNITS));
                            rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.ADD_ON_CHARGE));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(5511486823412194975L)));
                                unitValue.setExponent(new Exponent(new Integer(-1902753446)));
                                rateElement.setUnitValue(unitValue);
                            }
                            {
                                UnitCost unitCost = new UnitCost();
                                unitCost.setValueDigits(new ValueDigits(new Long(44985492962702728L)));
                                unitCost.setExponent(new Exponent(new Integer(1862688762)));
                                rateElement.setUnitCost(unitCost);
                            }
                            rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-2062546460)));
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
                    aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(-2001016943)));
                    aoCInformation.setAoCSubscriptionInformation(aoCSubscriptionInformation);
                }
                serviceInformation.setAoCInformation(aoCInformation);
            }
            {
                PSInformation pSInformation = new PSInformation();
                pSInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-2056480451)));
                pSInformation.setPDNConnectionID(new PDNConnectionID(new Integer(577301865)));
                pSInformation.setNodeId(new NodeId("utf8string-172709290"));
                pSInformation.setRo3GPPPDPType(new Ro3GPPPDPType(new Integer(-1149682655)));
                pSInformation.addPDPAddress(new PDPAddress(new Address(Address.Family.IPV4, "104.57.199.74")));
                pSInformation.setPDPAddressPrefixLength(new PDPAddressPrefixLength(new Integer(-441769001)));
                pSInformation.setDynamicAddressFlag(new DynamicAddressFlag(DynamicAddressFlag.Value.Static));
                pSInformation.setDynamicAddressFlagExtension(new DynamicAddressFlagExtension(DynamicAddressFlagExtension.Value.Static));
                {
                    QoSInformation qoSInformation = new QoSInformation();
                    qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_4));
                    qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1370053597)));
                    qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(84261145)));
                    qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1038840746)));
                    qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-1889998145)));
                    qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-2043057151"));
                    {
                        AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                        allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(639923254)));
                        allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                        allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                        qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                    }
                    qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1156561924)));
                    qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1932960792)));
                    // add more AVP as ANY values to qoSInformation
                    pSInformation.setQoSInformation(qoSInformation);
                }
                pSInformation.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "67.1.34.128")));
                pSInformation.setGGSNAddress(new GGSNAddress(new Address(Address.Family.IPV4, "60.204.152.202")));
                pSInformation.setSGWAddress(new SGWAddress(new Address(Address.Family.IPV4, "193.114.102.97")));
                pSInformation.setCGAddress(new CGAddress(new Address(Address.Family.IPV4, "203.140.86.116")));
                pSInformation.setServingNodeType(new ServingNodeType(ServingNodeType.Value.hSGW));
                pSInformation.setSGWChange(new SGWChange(SGWChange.Value.ACR_Start_due_to_SGW_Change));
                pSInformation.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string439518524"));
                pSInformation.setIMSIUnauthenticatedFlag(new IMSIUnauthenticatedFlag(IMSIUnauthenticatedFlag.Value.Unauthenticated));
                pSInformation.setRo3GPPGGSNMCCMNC(new Ro3GPPGGSNMCCMNC("utf8string108809567"));
                pSInformation.setRo3GPPNSAPI(new Ro3GPPNSAPI("utf8string-1880073081"));
                pSInformation.setCalledStationId(new diameter.nasreq.CalledStationId("utf8string-1569243522"));
                pSInformation.setRo3GPPSessionStopIndicator(new Ro3GPPSessionStopIndicator("octetstring-1249837934"));
                pSInformation.setRo3GPPSelectionMode(new Ro3GPPSelectionMode("utf8string-672194346"));
                pSInformation.setRo3GPPChargingCharacteristics(new Ro3GPPChargingCharacteristics("utf8string-1918154473"));
                pSInformation.setRo3GPPSGSNMCCMNC(new Ro3GPPSGSNMCCMNC("utf8string1173517782"));
                pSInformation.setRo3GPPMSTimeZone(new Ro3GPPMSTimeZone("octetstring-939789666"));
                pSInformation.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring-396681679"));
                pSInformation.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring500451426"));
                {
                    UserCSGInformation userCSGInformation = new UserCSGInformation();
                    userCSGInformation.setCSGId(new CSGId(new Integer(-797759658)));
                    userCSGInformation.setCSGAccessMode(new CSGAccessMode(CSGAccessMode.Value.Hybrid_Mode));
                    userCSGInformation.setCSGMembershipIndication(new CSGMembershipIndication(CSGMembershipIndication.Value.CSG_Member));
                    pSInformation.setUserCSGInformation(userCSGInformation);
                }
                pSInformation.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string1483310646"));
                pSInformation.setRo3GPPRATType(new Ro3GPPRATType("octetstring-113807444"));
                {
                    PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                    pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-1017462793)));
                    pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring1120890716"));
                    pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Overwrite));
                    pSInformation.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                }
                pSInformation.setPDPContextType(new PDPContextType(PDPContextType.Value.PRIMARY));
                {
                    OfflineCharging offlineCharging = new OfflineCharging();
                    offlineCharging.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(315865877)));
                    {
                        TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                        timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                        timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(-1178709925)));
                        offlineCharging.setTimeQuotaMechanism(timeQuotaMechanism);
                    }
                    offlineCharging.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_EVENTS));
                    {
                        MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
                        {
                            GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                            grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(1701151970));
                            grantedServiceUnit.setCCTime(new CCTime(new Integer(-1937814176)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(-5753475839262154946L)));
                                    unitValue.setExponent(new Exponent(new Integer(1486764277)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-647769667)));
                                grantedServiceUnit.setCCMoney(cCMoney);
                            }
                            grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-3982912638434741187L)));
                            grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(1519480254102145186L)));
                            grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-3466079721767652756L)));
                            grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-6764096329659553475L)));
                            // add more AVP as ANY values to grantedServiceUnit
                            multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
                        }
                        {
                            RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                            requestedServiceUnit.setCCTime(new CCTime(new Integer(399442731)));
                            {
                                CCMoney cCMoney = new CCMoney();
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(1527985505531423842L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1097740823)));
                                    cCMoney.setUnitValue(unitValue);
                                }
                                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-1403281471)));
                                requestedServiceUnit.setCCMoney(cCMoney);
                            }
                            requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(5372929074452824292L)));
                            requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-1804306463989682334L)));
                            requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-1984492088810359915L)));
                            requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(1569591207648210415L)));
                            // add more AVP as ANY values to requestedServiceUnit
                            multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
                        }
                        {
                            UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                            usedServiceUnit.setReportingReason(new ReportingReason(ReportingReason.Value.FORCED_REAUTHORISATION));
                            usedServiceUnit.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_AFTER_TARIFF_CHANGE));
                            usedServiceUnit.setCCTime(new CCTime(new Integer(-2105232174)));
                            usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-8243719593350516162L)));
                            usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(3621739155775683230L)));
                            usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-7800810687593766167L)));
                            usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(5733912330906530086L)));
                            usedServiceUnit.addEventChargingTimeStamp(new EventChargingTimeStamp(1135012348));
                            multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
                        }
                        multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(684867617)));
                        multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(1223489038)));
                        {
                            GSUPoolReference gSUPoolReference = new GSUPoolReference();
                            gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(1515210255)));
                            gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.MONEY));
                            {
                                UnitValue unitValue = new UnitValue();
                                unitValue.setValueDigits(new ValueDigits(new Long(-2454968189285403078L)));
                                unitValue.setExponent(new Exponent(new Integer(-970202648)));
                                gSUPoolReference.setUnitValue(unitValue);
                            }
                            multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
                        }
                        multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(-703414940)));
                        multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(84997874)));
                        {
                            FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                            finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.TERMINATE));
                            finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                            finalUnitIndication.addFilterId(new diameter.nasreq.FilterId("utf8string1073710222"));
                            {
                                RedirectServer redirectServer = new RedirectServer();
                                redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.SIP_URI));
                                redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string310043231"));
                                finalUnitIndication.setRedirectServer(redirectServer);
                            }
                            multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
                        }
                        multipleServicesCreditControl.setTimeQuotaThreshold(new TimeQuotaThreshold(new Integer(570901496)));
                        multipleServicesCreditControl.setVolumeQuotaThreshold(new VolumeQuotaThreshold(new Integer(1487782866)));
                        multipleServicesCreditControl.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1700463892)));
                        multipleServicesCreditControl.setQuotaHoldingTime(new QuotaHoldingTime(new Integer(-98368440)));
                        multipleServicesCreditControl.setQuotaConsumptionTime(new QuotaConsumptionTime(new Integer(1711566593)));
                        multipleServicesCreditControl.addReportingReason(new ReportingReason(ReportingReason.Value.POOL_EXHAUSTED));
                        {
                            Trigger trigger = new Trigger();
                            trigger.addTriggerType(new TriggerType(TriggerType.Value.CHANGEINQOS_PEAK_THROUGHPUT));
                            multipleServicesCreditControl.setTrigger(trigger);
                        }
                        {
                            PSFurnishChargingInformation pSFurnishChargingInformation = new PSFurnishChargingInformation();
                            pSFurnishChargingInformation.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-2003219552)));
                            pSFurnishChargingInformation.setPSFreeFormatData(new PSFreeFormatData("octetstring1296445728"));
                            pSFurnishChargingInformation.setPSAppendFreeFormatData(new PSAppendFreeFormatData(PSAppendFreeFormatData.Value.Append));
                            multipleServicesCreditControl.setPSFurnishChargingInformation(pSFurnishChargingInformation);
                        }
                        multipleServicesCreditControl.setRefundInformation(new RefundInformation("octetstring738663143"));
                        {
                            AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                            aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring-1239202434"));
                            {
                                Flows flows = new Flows();
                                flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(-1390362338)));
                                flows.addFlowNumber(new FlowNumber(new Integer(-436436212)));
                                aFCorrelationInformation.addFlows(flows);
                            }
                            multipleServicesCreditControl.addAFCorrelationInformation(aFCorrelationInformation);
                        }
                        {
                            Envelope envelope = new Envelope();
                            envelope.setEnvelopeStartTime(new EnvelopeStartTime(464457950));
                            envelope.setEnvelopeEndTime(new EnvelopeEndTime(-1883213024));
                            envelope.setCCTotalOctets(new CCTotalOctets(new Long(8938647348398416953L)));
                            envelope.setCCInputOctets(new CCInputOctets(new Long(1171974378713218098L)));
                            envelope.setCCOutputOctets(new CCOutputOctets(new Long(3608858850682289711L)));
                            envelope.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(2825250005069971792L)));
                            // add more AVP as ANY values to envelope
                            multipleServicesCreditControl.addEnvelope(envelope);
                        }
                        multipleServicesCreditControl.setEnvelopeReporting(new EnvelopeReporting(EnvelopeReporting.Value.REPORT_ENVELOPES_WITH_VOLUME_AND_EVENTS));
                        {
                            TimeQuotaMechanism timeQuotaMechanism = new TimeQuotaMechanism();
                            timeQuotaMechanism.setTimeQuotaType(new TimeQuotaType(TimeQuotaType.Value.DISCRETE_TIME_PERIOD));
                            timeQuotaMechanism.setBaseTimeInterval(new BaseTimeInterval(new Integer(20410409)));
                            multipleServicesCreditControl.setTimeQuotaMechanism(timeQuotaMechanism);
                        }
                        {
                            ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                            serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string-826338615"));
                            serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1783677089)));
                            multipleServicesCreditControl.addServiceSpecificInfo(serviceSpecificInfo);
                        }
                        {
                            QoSInformation qoSInformation = new QoSInformation();
                            qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_8));
                            qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(1025186225)));
                            qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(1705217958)));
                            qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(1813356470)));
                            qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(1988921341)));
                            qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-424901060"));
                            {
                                AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                                allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1438781206)));
                                allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                                allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                                qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                            }
                            qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1229877726)));
                            qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(-1704147686)));
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
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(222472193)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(253377881)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(-318939137)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(-1940212951)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-105801165"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1980922962)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_DISABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_DISABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(1690636030)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(423818487)));
                        // add more AVP as ANY values to qoSInformation
                        trafficDataVolumes.setQoSInformation(qoSInformation);
                    }
                    trafficDataVolumes.setAccountingInputOctets(new AccountingInputOctets(new Long(-5724919865007081281L)));
                    trafficDataVolumes.setAccountingInputPackets(new AccountingInputPackets(new Long(1693368340061194868L)));
                    trafficDataVolumes.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-6415131558345802270L)));
                    trafficDataVolumes.setAccountingOutputPackets(new AccountingOutputPackets(new Long(1423537881886648290L)));
                    trafficDataVolumes.setChangeCondition(new ChangeCondition(new Integer(1305332359)));
                    trafficDataVolumes.setChangeTime(new ChangeTime(2004677739));
                    trafficDataVolumes.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring-1293651778"));
                    pSInformation.addTrafficDataVolumes(trafficDataVolumes);
                }
                {
                    ServiceDataContainer serviceDataContainer = new ServiceDataContainer();
                    {
                        AFCorrelationInformation aFCorrelationInformation = new AFCorrelationInformation();
                        aFCorrelationInformation.setAFChargingIdentifier(new AFChargingIdentifier("octetstring925826579"));
                        {
                            Flows flows = new Flows();
                            flows.setMediaComponentNumber(new MediaComponentNumber(new Integer(185317156)));
                            flows.addFlowNumber(new FlowNumber(new Integer(2107325766)));
                            aFCorrelationInformation.addFlows(flows);
                        }
                        serviceDataContainer.setAFCorrelationInformation(aFCorrelationInformation);
                    }
                    serviceDataContainer.setChargingRuleBaseName(new ChargingRuleBaseName("octetstring1461752669"));
                    serviceDataContainer.setAccountingInputOctets(new AccountingInputOctets(new Long(-2297325390448743900L)));
                    serviceDataContainer.setAccountingOutputOctets(new AccountingOutputOctets(new Long(-5638313329273321681L)));
                    serviceDataContainer.setAccountingInputPackets(new AccountingInputPackets(new Long(7694700710129861277L)));
                    serviceDataContainer.setAccountingOutputPackets(new AccountingOutputPackets(new Long(7098714768812338584L)));
                    serviceDataContainer.setLocalSequenceNumber(new LocalSequenceNumber(new Integer(-1597306253)));
                    {
                        QoSInformation qoSInformation = new QoSInformation();
                        qoSInformation.setQoSClassIdentifier(new QoSClassIdentifier(QoSClassIdentifier.Value.QCI_1));
                        qoSInformation.setMaxRequestedBandwidthUL(new MaxRequestedBandwidthUL(new Integer(-1974978723)));
                        qoSInformation.setMaxRequestedBandwidthDL(new MaxRequestedBandwidthDL(new Integer(-1490266214)));
                        qoSInformation.setGuaranteedBitrateUL(new GuaranteedBitrateUL(new Integer(353796444)));
                        qoSInformation.setGuaranteedBitrateDL(new GuaranteedBitrateDL(new Integer(852772942)));
                        qoSInformation.setBearerIdentifier(new BearerIdentifier("octetstring-259997998"));
                        {
                            AllocationRetentionPriority allocationRetentionPriority = new AllocationRetentionPriority();
                            allocationRetentionPriority.setPriorityLevel(new PriorityLevel(new Integer(-1734444676)));
                            allocationRetentionPriority.setPreemptionCapability(new PreemptionCapability(PreemptionCapability.Value.PRE_EMPTION_CAPABILITY_ENABLED));
                            allocationRetentionPriority.setPreemptionVulnerability(new PreemptionVulnerability(PreemptionVulnerability.Value.PRE_EMPTION_VULNERABILITY_ENABLED));
                            qoSInformation.setAllocationRetentionPriority(allocationRetentionPriority);
                        }
                        qoSInformation.setAPNAggregateMaxBitrateUL(new APNAggregateMaxBitrateUL(new Integer(826799087)));
                        qoSInformation.setAPNAggregateMaxBitrateDL(new APNAggregateMaxBitrateDL(new Integer(1427125414)));
                        // add more AVP as ANY values to qoSInformation
                        serviceDataContainer.setQoSInformation(qoSInformation);
                    }
                    serviceDataContainer.setRatingGroup(new RatingGroup(new Integer(1684910645)));
                    serviceDataContainer.setChangeTime(new ChangeTime(-641427768));
                    serviceDataContainer.setServiceIdentifier(new ServiceIdentifier(new Integer(-368314918)));
                    {
                        ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                        serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string334126031"));
                        serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1052722424)));
                        serviceDataContainer.setServiceSpecificInfo(serviceSpecificInfo);
                    }
                    serviceDataContainer.setSGSNAddress(new SGSNAddress(new Address(Address.Family.IPV4, "114.51.89.71")));
                    serviceDataContainer.setTimeFirstUsage(new TimeFirstUsage(261525921));
                    serviceDataContainer.setTimeLastUsage(new TimeLastUsage(-1061488176));
                    serviceDataContainer.setTimeUsage(new TimeUsage(248774651));
                    serviceDataContainer.addChangeCondition(new ChangeCondition(new Integer(2062185935)));
                    serviceDataContainer.setRo3GPPUserLocationInfo(new Ro3GPPUserLocationInfo("octetstring-580539074"));
                    serviceDataContainer.setRo3GPP2BSID(new Ro3GPP2BSID("utf8string1527074991"));
                    pSInformation.addServiceDataContainer(serviceDataContainer);
                }
                {
                    UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
                    userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.IMEISV));
                    userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring-2041767717"));
                    pSInformation.setUserEquipmentInfo(userEquipmentInfo);
                }
                {
                    TerminalInformation terminalInformation = new TerminalInformation();
                    terminalInformation.setIMEI(new IMEI("utf8string545197553"));
                    terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string996841768"));
                    // add more AVP as ANY values to terminalInformation
                    pSInformation.setTerminalInformation(terminalInformation);
                }
                pSInformation.setStartTime(new StartTime(1866844302));
                pSInformation.setStopTime(new StopTime(775294110));
                pSInformation.setChangeCondition(new ChangeCondition(new Integer(655218663)));
                pSInformation.setDiagnostics(new Diagnostics(new Integer(1812341346)));
                pSInformation.setLowPriorityIndicator(new LowPriorityIndicator(LowPriorityIndicator.Value.NO));
                serviceInformation.setPSInformation(pSInformation);
            }
            {
                WLANInformation wLANInformation = new WLANInformation();
                wLANInformation.setWLANSessionId(new WLANSessionId(new Integer(-1790192945)));
                wLANInformation.setPDGAddress(new PDGAddress(new Address(Address.Family.IPV4, "214.7.187.123")));
                wLANInformation.setPDGChargingId(new PDGChargingId(new Integer(-133263811)));
                wLANInformation.setWAGAddress(new WAGAddress(new Address(Address.Family.IPV4, "59.13.22.240")));
                wLANInformation.setWAGPLMNId(new WAGPLMNId("octetstring-2008267575"));
                {
                    WLANRadioContainer wLANRadioContainer = new WLANRadioContainer();
                    wLANRadioContainer.setOperatorName(new OperatorName("octetstring-84461608"));
                    wLANRadioContainer.setLocationInformation(new LocationInformation("octetstring1466563538"));
                    {
                        LocationType locationType = new LocationType();
                        locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.ACTIVATE_DEFERRED_LOCATION));
                        locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string1168159903"));
                        wLANRadioContainer.setLocationType(locationType);
                    }
                    wLANRadioContainer.setWLANTechnology(new WLANTechnology(new Integer(275291904)));
                    wLANInformation.setWLANRadioContainer(wLANRadioContainer);
                }
                wLANInformation.setWLANUELocalIPAddress(new WLANUELocalIPAddress(new Address(Address.Family.IPV4, "51.229.124.222")));
                serviceInformation.setWLANInformation(wLANInformation);
            }
            {
                IMSInformation iMSInformation = new IMSInformation();
                {
                    EventType eventType = new EventType();
                    eventType.setSIPMethod(new SIPMethod("utf8string-1177011997"));
                    eventType.setIMSEvent(new IMSEvent("utf8string-210453632"));
                    eventType.setExpires(new Expires(new Integer(1967910887)));
                    iMSInformation.setEventType(eventType);
                }
                iMSInformation.setRoleOfNode(new RoleOfNode(RoleOfNode.Value.ORIGINATING_ROLE));
                iMSInformation.setNodeFunctionality(new NodeFunctionality(NodeFunctionality.Value.P_GW));
                iMSInformation.setUserSessionID(new UserSessionID("utf8string-572820258"));
                iMSInformation.setOutgoingSessionId(new OutgoingSessionId("utf8string-2137373854"));
                iMSInformation.addCallingPartyAddress(new CallingPartyAddress("utf8string478130156"));
                iMSInformation.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY_3));
                iMSInformation.setCalledPartyAddress(new CalledPartyAddress("utf8string-46549537"));
                iMSInformation.addCalledAssertedIdentity(new CalledAssertedIdentity("utf8string893435103"));
                iMSInformation.setNumberPortabilityRoutingInformation(new NumberPortabilityRoutingInformation("utf8string-2120935605"));
                iMSInformation.setCarrierSelectRoutingInformation(new CarrierSelectRoutingInformation("utf8string-1509042960"));
                iMSInformation.setAlternateChargedPartyAddress(new AlternateChargedPartyAddress("utf8string-1454906104"));
                iMSInformation.setRequestedPartyAddress(new RequestedPartyAddress("utf8string1188036979"));
                iMSInformation.addAssociatedURI(new AssociatedURI("utf8string-1927093820"));
                {
                    TimeStamps timeStamps = new TimeStamps();
                    timeStamps.setSIPRequestTimestamp(new SIPRequestTimestamp(-1725633452));
                    timeStamps.setSIPResponseTimestamp(new SIPResponseTimestamp(828480463));
                    timeStamps.setSIPRequestTimestampFraction(new SIPRequestTimestampFraction(new Integer(-1973377463)));
                    timeStamps.setSIPResponseTimestampFraction(new SIPResponseTimestampFraction(new Integer(1992491079)));
                    iMSInformation.setTimeStamps(timeStamps);
                }
                {
                    ApplicationServerInformation applicationServerInformation = new ApplicationServerInformation();
                    applicationServerInformation.setApplicationServer(new ApplicationServer("utf8string-1911632130"));
                    applicationServerInformation.addApplicationProvidedCalledPartyAddress(new ApplicationProvidedCalledPartyAddress("utf8string955875605"));
                    iMSInformation.addApplicationServerInformation(applicationServerInformation);
                }
                {
                    InterOperatorIdentifier interOperatorIdentifier = new InterOperatorIdentifier();
                    interOperatorIdentifier.setOriginatingIOI(new OriginatingIOI("utf8string1407832792"));
                    interOperatorIdentifier.setTerminatingIOI(new TerminatingIOI("utf8string-786282163"));
                    iMSInformation.addInterOperatorIdentifier(interOperatorIdentifier);
                }
                iMSInformation.setIMSChargingIdentifier(new IMSChargingIdentifier("utf8string-1174874920"));
                iMSInformation.addSDPSessionDescription(new SDPSessionDescription("utf8string-1005467661"));
                {
                    SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                    sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string-601664936"));
                    sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string-1243603140"));
                    sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                    sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Inserted));
                    sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_realm_used));
                    sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.calling_party));
                    sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string645888348"));
                    sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string198826546"));
                    sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-2044003019)));
                    sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring-717221578"));
                    sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Answer));
                    iMSInformation.addSDPMediaComponent(sDPMediaComponent);
                }
                iMSInformation.setServedPartyIPAddress(new ServedPartyIPAddress(new Address(Address.Family.IPV4, "45.80.186.196")));
                {
                    ServerCapabilities serverCapabilities = new ServerCapabilities();
                    serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(248880184)));
                    serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(150848382)));
                    serverCapabilities.addServerName(new ServerName("utf8string1591032996"));
                    // add more AVP as ANY values to serverCapabilities
                    iMSInformation.setServerCapabilities(serverCapabilities);
                }
                {
                    TrunkGroupID trunkGroupID = new TrunkGroupID();
                    trunkGroupID.setIncomingTrunkGroupID(new IncomingTrunkGroupID("utf8string-1122666331"));
                    trunkGroupID.setOutgoingTrunkGroupID(new OutgoingTrunkGroupID("utf8string2000534958"));
                    iMSInformation.setTrunkGroupID(trunkGroupID);
                }
                iMSInformation.setBearerService(new BearerService("octetstring1140939836"));
                iMSInformation.setServiceId(new ServiceId("utf8string-184212577"));
                {
                    ServiceSpecificInfo serviceSpecificInfo = new ServiceSpecificInfo();
                    serviceSpecificInfo.setServiceSpecificData(new ServiceSpecificData("utf8string952926920"));
                    serviceSpecificInfo.setServiceSpecificType(new ServiceSpecificType(new Integer(1198978548)));
                    iMSInformation.addServiceSpecificInfo(serviceSpecificInfo);
                }
                {
                    MessageBody messageBody = new MessageBody();
                    messageBody.setContentType(new ContentType("utf8string-1414677310"));
                    messageBody.setContentLength(new ContentLength(new Integer(445848028)));
                    messageBody.setContentDisposition(new ContentDisposition("utf8string558300117"));
                    messageBody.setOriginator(new Originator(Originator.Value.Called_Party));
                    iMSInformation.addMessageBody(messageBody);
                }
                iMSInformation.setCauseCode(new CauseCode(new Integer(-1358545873)));
                iMSInformation.setAccessNetworkInformation(new AccessNetworkInformation("octetstring904330549"));
                {
                    EarlyMediaDescription earlyMediaDescription = new EarlyMediaDescription();
                    {
                        SDPTimeStamps sDPTimeStamps = new SDPTimeStamps();
                        sDPTimeStamps.setSDPOfferTimestamp(new SDPOfferTimestamp(-1521587085));
                        sDPTimeStamps.setSDPAnswerTimestamp(new SDPAnswerTimestamp(1206514200));
                        earlyMediaDescription.setSDPTimeStamps(sDPTimeStamps);
                    }
                    {
                        SDPMediaComponent sDPMediaComponent = new SDPMediaComponent();
                        sDPMediaComponent.setSDPMediaName(new SDPMediaName("utf8string259646982"));
                        sDPMediaComponent.addSDPMediaDescription(new SDPMediaDescription("utf8string-1432286316"));
                        sDPMediaComponent.setLocalGWInsertedIndication(new LocalGWInsertedIndication(LocalGWInsertedIndication.Value.Local_GW_Inserted));
                        sDPMediaComponent.setTranscoderInsertedIndication(new TranscoderInsertedIndication(TranscoderInsertedIndication.Value.Transcoder_Not_Inserted));
                        sDPMediaComponent.setIPRealmDefaultIndication(new IPRealmDefaultIndication(IPRealmDefaultIndication.Value.Default_IP_Realm_Not_used));
                        sDPMediaComponent.setMediaInitiatorFlag(new MediaInitiatorFlag(MediaInitiatorFlag.Value.unknown));
                        sDPMediaComponent.setMediaInitiatorParty(new MediaInitiatorParty("utf8string-834471772"));
                        sDPMediaComponent.setAuthorizedQoS(new AuthorizedQoS("utf8string256168604"));
                        sDPMediaComponent.setRo3GPPChargingId(new Ro3GPPChargingId(new Integer(-1917723581)));
                        sDPMediaComponent.setAccessNetworkChargingIdentifierValue(new AccessNetworkChargingIdentifierValue("octetstring215992170"));
                        sDPMediaComponent.setSDPType(new SDPType(SDPType.Value.SDP_Offer));
                        earlyMediaDescription.addSDPMediaComponent(sDPMediaComponent);
                    }
                    earlyMediaDescription.addSDPSessionDescription(new SDPSessionDescription("utf8string802988196"));
                    iMSInformation.addEarlyMediaDescription(earlyMediaDescription);
                }
                iMSInformation.setIMSCommunicationServiceIdentifier(new IMSCommunicationServiceIdentifier("utf8string832250394"));
                iMSInformation.setOnlineChargingFlag(new OnlineChargingFlag(OnlineChargingFlag.Value.ECF_address_not_provided));
                {
                    RealTimeTariffInformation realTimeTariffInformation = new RealTimeTariffInformation();
                    {
                        TariffInformation tariffInformation = new TariffInformation();
                        {
                            CurrentTariff currentTariff = new CurrentTariff();
                            currentTariff.setCurrencyCode(new CurrencyCode(new Integer(247834000)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(6338312058314319589L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-1014804898)));
                                currentTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TIME));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.USAGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(3529244909321366867L)));
                                    unitValue.setExponent(new Exponent(new Integer(-2036733890)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(-2079739485495438770L)));
                                    unitCost.setExponent(new Exponent(new Integer(482571603)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1684636547)));
                                currentTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setCurrentTariff(currentTariff);
                        }
                        tariffInformation.setTariffTimeChange(new TariffTimeChange(561974901));
                        {
                            NextTariff nextTariff = new NextTariff();
                            nextTariff.setCurrencyCode(new CurrencyCode(new Integer(-842247946)));
                            {
                                ScaleFactor scaleFactor = new ScaleFactor();
                                scaleFactor.setValueDigits(new ValueDigits(new Long(7738279932045538057L)));
                                scaleFactor.setExponent(new Exponent(new Integer(-924316276)));
                                nextTariff.setScaleFactor(scaleFactor);
                            }
                            {
                                RateElement rateElement = new RateElement();
                                rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                                rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.COMMUNICATION_ATTEMPT_CHARGE));
                                {
                                    UnitValue unitValue = new UnitValue();
                                    unitValue.setValueDigits(new ValueDigits(new Long(3636984770962126124L)));
                                    unitValue.setExponent(new Exponent(new Integer(-1944451878)));
                                    rateElement.setUnitValue(unitValue);
                                }
                                {
                                    UnitCost unitCost = new UnitCost();
                                    unitCost.setValueDigits(new ValueDigits(new Long(3574999910682610722L)));
                                    unitCost.setExponent(new Exponent(new Integer(564900359)));
                                    rateElement.setUnitCost(unitCost);
                                }
                                rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(-1712134985)));
                                nextTariff.addRateElement(rateElement);
                            }
                            tariffInformation.setNextTariff(nextTariff);
                        }
                        realTimeTariffInformation.setTariffInformation(tariffInformation);
                    }
                    realTimeTariffInformation.setTariffXML(new TariffXML("utf8string-333628090"));
                    iMSInformation.setRealTimeTariffInformation(realTimeTariffInformation);
                }
                iMSInformation.setAccountExpiration(new AccountExpiration(1508642044));
                iMSInformation.setInitialIMSChargingIdentifier(new InitialIMSChargingIdentifier("utf8string-152824564"));
                serviceInformation.setIMSInformation(iMSInformation);
            }
            {
                MMSInformation mMSInformation = new MMSInformation();
                {
                    OriginatorAddress originatorAddress = new OriginatorAddress();
                    originatorAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IPv6_Address));
                    originatorAddress.setAddressData(new AddressData("utf8string739930820"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-1511558132"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-251990223"));
                        originatorAddress.setAddressDomain(addressDomain);
                    }
                    mMSInformation.setOriginatorAddress(originatorAddress);
                }
                {
                    RecipientAddress recipientAddress = new RecipientAddress();
                    recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.IMSI));
                    recipientAddress.setAddressData(new AddressData("utf8string1678923776"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string1410354289"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1440504461"));
                        recipientAddress.setAddressDomain(addressDomain);
                    }
                    recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.CC));
                    mMSInformation.addRecipientAddress(recipientAddress);
                }
                mMSInformation.setSubmissionTime(new SubmissionTime(448576233));
                {
                    MMContentType mMContentType = new MMContentType();
                    mMContentType.setTypeNumber(new TypeNumber(new Integer(-505095138)));
                    mMContentType.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string379224346"));
                    mMContentType.setContentSize(new ContentSize(new Integer(-673089388)));
                    {
                        AdditionalContentInformation additionalContentInformation = new AdditionalContentInformation();
                        additionalContentInformation.setTypeNumber(new TypeNumber(new Integer(1459226420)));
                        additionalContentInformation.setAdditionalTypeInformation(new AdditionalTypeInformation("utf8string2050077681"));
                        additionalContentInformation.setContentSize(new ContentSize(new Integer(-523878335)));
                        mMContentType.addAdditionalContentInformation(additionalContentInformation);
                    }
                    mMSInformation.setMMContentType(mMContentType);
                }
                mMSInformation.setPriority(new Priority(Priority.Value.Low));
                mMSInformation.setMessageID(new MessageID("utf8string-1162038144"));
                mMSInformation.setMessageType(new MessageType(MessageType.Value.m_mbox_store_conf));
                mMSInformation.setMessageSize(new MessageSize(new Integer(784575125)));
                {
                    MessageClass messageClass = new MessageClass();
                    messageClass.setClassIdentifier(new ClassIdentifier(ClassIdentifier.Value.Advertisement));
                    messageClass.setTokenText(new TokenText("utf8string-1768361285"));
                    mMSInformation.setMessageClass(messageClass);
                }
                mMSInformation.setDeliveryReportRequested(new DeliveryReportRequested(DeliveryReportRequested.Value.Yes));
                mMSInformation.setReadReplyReportRequested(new ReadReplyReportRequested(ReadReplyReportRequested.Value.No));
                mMSInformation.setMMBoxStorageRequested(new MMBoxStorageRequested(MMBoxStorageRequested.Value.No));
                mMSInformation.setApplicID(new ApplicID("utf8string-1535625021"));
                mMSInformation.setReplyApplicID(new ReplyApplicID("utf8string679206207"));
                mMSInformation.setAuxApplicInfo(new AuxApplicInfo("utf8string-1229141575"));
                mMSInformation.setContentClass(new ContentClass(ContentClass.Value.content_rich));
                mMSInformation.setDRMContent(new DRMContent(DRMContent.Value.Yes));
                mMSInformation.setAdaptations(new Adaptations(Adaptations.Value.No));
                mMSInformation.setVASPId(new VASPId("utf8string1911473198"));
                mMSInformation.setVASId(new VASId("utf8string819646690"));
                serviceInformation.setMMSInformation(mMSInformation);
            }
            {
                LCSInformation lCSInformation = new LCSInformation();
                {
                    LCSClientID lCSClientID = new LCSClientID();
                    lCSClientID.setLCSClientType(new LCSClientType(LCSClientType.Value.VALUE_ADDED_SERVICES));
                    lCSClientID.setLCSClientExternalID(new LCSClientExternalID("utf8string1750210464"));
                    lCSClientID.setLCSClientDialedByMS(new LCSClientDialedByMS("utf8string2134899809"));
                    {
                        LCSClientName lCSClientName = new LCSClientName();
                        lCSClientName.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string1414302382"));
                        lCSClientName.setLCSNameString(new LCSNameString("utf8string675924243"));
                        lCSClientName.setLCSFormatIndicator(new LCSFormatIndicator(LCSFormatIndicator.Value.MSISDN));
                        lCSClientID.setLCSClientName(lCSClientName);
                    }
                    lCSClientID.setLCSAPN(new LCSAPN("utf8string-773927390"));
                    {
                        LCSRequestorID lCSRequestorID = new LCSRequestorID();
                        lCSRequestorID.setLCSDataCodingScheme(new LCSDataCodingScheme("utf8string-1083485093"));
                        lCSRequestorID.setLCSRequestorIDString(new LCSRequestorIDString("utf8string-2099303319"));
                        lCSClientID.setLCSRequestorID(lCSRequestorID);
                    }
                    lCSInformation.setLCSClientID(lCSClientID);
                }
                {
                    LocationType locationType = new LocationType();
                    locationType.setLocationEstimateType(new LocationEstimateType(LocationEstimateType.Value.CURRENT_LAST_KNOWN_LOCATION));
                    locationType.setDeferredLocationEventType(new DeferredLocationEventType("utf8string1919014060"));
                    lCSInformation.setLocationType(locationType);
                }
                lCSInformation.setLocationEstimate(new LocationEstimate("utf8string1030305085"));
                lCSInformation.setPositioningData(new PositioningData("utf8string517580809"));
                lCSInformation.setRo3GPPIMSI(new Ro3GPPIMSI("utf8string-1260392697"));
                lCSInformation.setMSISDN(new MSISDN("octetstring2100301098"));
                serviceInformation.setLCSInformation(lCSInformation);
            }
            {
                PoCInformation poCInformation = new PoCInformation();
                poCInformation.setPoCServerRole(new PoCServerRole(PoCServerRole.Value.Participating_PoC_Server));
                poCInformation.setPoCSessionType(new PoCSessionType(PoCSessionType.Value.pre_arranged_PoC_group_session));
                {
                    PoCUserRole poCUserRole = new PoCUserRole();
                    poCUserRole.setPoCUserRoleIds(new PoCUserRoleIds("utf8string1262793420"));
                    poCUserRole.setPoCUserRoleinfoUnits(new PoCUserRoleinfoUnits(PoCUserRoleinfoUnits.Value.Session_Participant));
                    poCInformation.setPoCUserRole(poCUserRole);
                }
                poCInformation.setPoCSessionInitiationType(new PoCSessionInitiationType(PoCSessionInitiationType.Value.On_demand));
                poCInformation.setPoCEventType(new PoCEventType(PoCEventType.Value.PoC_Talk_Burst));
                poCInformation.setNumberOfParticipants(new NumberOfParticipants(new Integer(-1974108569)));
                poCInformation.addParticipantsInvolved(new ParticipantsInvolved("utf8string1046135612"));
                {
                    ParticipantGroup participantGroup = new ParticipantGroup();
                    participantGroup.setCalledPartyAddress(new CalledPartyAddress("utf8string-1723275191"));
                    participantGroup.setParticipantAccessPriority(new ParticipantAccessPriority(ParticipantAccessPriority.Value.Normal_priority));
                    participantGroup.setUserParticipatingType(new UserParticipatingType(UserParticipatingType.Value.UE_PoC_Box));
                    poCInformation.addParticipantGroup(participantGroup);
                }
                {
                    TalkBurstExchange talkBurstExchange = new TalkBurstExchange();
                    talkBurstExchange.setPoCChangeTime(new PoCChangeTime(-951013636));
                    talkBurstExchange.setNumberOfTalkBursts(new NumberOfTalkBursts(new Integer(255300724)));
                    talkBurstExchange.setTalkBurstVolume(new TalkBurstVolume(new Integer(-652220912)));
                    talkBurstExchange.setTalkBurstTime(new TalkBurstTime(new Integer(-1560545119)));
                    talkBurstExchange.setNumberOfReceivedTalkBursts(new NumberOfReceivedTalkBursts(new Integer(-1490792496)));
                    talkBurstExchange.setReceivedTalkBurstVolume(new ReceivedTalkBurstVolume(new Integer(922731055)));
                    talkBurstExchange.setReceivedTalkBurstTime(new ReceivedTalkBurstTime(new Integer(-701428500)));
                    talkBurstExchange.setNumberOfParticipants(new NumberOfParticipants(new Integer(28840629)));
                    talkBurstExchange.setPoCChangeCondition(new PoCChangeCondition(PoCChangeCondition.Value.volumeLimit));
                    poCInformation.addTalkBurstExchange(talkBurstExchange);
                }
                poCInformation.setPoCControllingAddress(new PoCControllingAddress("utf8string-1226330016"));
                poCInformation.setPoCGroupName(new PoCGroupName("utf8string21460254"));
                poCInformation.setPoCSessionId(new PoCSessionId("utf8string-1010080399"));
                poCInformation.setChargedParty(new ChargedParty("utf8string531356772"));
                serviceInformation.setPoCInformation(poCInformation);
            }
            {
                MBMSInformation mBMSInformation = new MBMSInformation();
                mBMSInformation.setTMGI(new TMGI("octetstring-1326193620"));
                mBMSInformation.setMBMSServiceType(new MBMSServiceType(MBMSServiceType.Value.BROADCAST));
                mBMSInformation.setMBMSUserServiceType(new MBMSUserServiceType(MBMSUserServiceType.Value.STREAMING));
                mBMSInformation.setFileRepairSupported(new FileRepairSupported(FileRepairSupported.Value.SUPPORTED));
                mBMSInformation.setRequiredMBMSBearerCapabilities(new RequiredMBMSBearerCapabilities("utf8string825065970"));
                mBMSInformation.setMBMS2G3GIndicator(new MBMS2G3GIndicator(MBMS2G3GIndicator.Value.ONLY_3G));
                mBMSInformation.setRAI(new RAI("utf8string1112779435"));
                mBMSInformation.addMBMSServiceArea(new MBMSServiceArea("octetstring615520504"));
                mBMSInformation.setMBMSSessionIdentity(new MBMSSessionIdentity("octetstring1363198330"));
                mBMSInformation.setCNIPMulticastDistribution(new CNIPMulticastDistribution(CNIPMulticastDistribution.Value.IP_MULTICAST));
                mBMSInformation.setMBMSGWAddress(new MBMSGWAddress(new Address(Address.Family.IPV4, "200.139.110.180")));
                serviceInformation.setMBMSInformation(mBMSInformation);
            }
            {
                SMSInformation sMSInformation = new SMSInformation();
                sMSInformation.setSMSNode(new SMSNode(SMSNode.Value.SMS_SC));
                sMSInformation.setClientAddress(new ClientAddress(new Address(Address.Family.IPV4, "147.8.167.243")));
                sMSInformation.setOriginatorSCCPAddress(new OriginatorSCCPAddress(new Address(Address.Family.IPV4, "22.12.15.4")));
                sMSInformation.setSMSCAddress(new SMSCAddress(new Address(Address.Family.IPV4, "188.249.95.178")));
                sMSInformation.setDataCodingScheme(new DataCodingScheme(new Integer(-1122521714)));
                sMSInformation.setSMDischargeTime(new SMDischargeTime(-1291993734));
                sMSInformation.setSMMessageType(new SMMessageType(SMMessageType.Value.SUBMISSION));
                {
                    OriginatorInterface originatorInterface = new OriginatorInterface();
                    originatorInterface.setInterfaceId(new InterfaceId("utf8string-1956803926"));
                    originatorInterface.setInterfaceText(new InterfaceText("utf8string-164436223"));
                    originatorInterface.setInterfacePort(new InterfacePort("utf8string-566659294"));
                    originatorInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.MOBILE_ORIGINATING));
                    sMSInformation.setOriginatorInterface(originatorInterface);
                }
                sMSInformation.setSMProtocolID(new SMProtocolID("octetstring-1851657139"));
                sMSInformation.setReplyPathRequested(new ReplyPathRequested(ReplyPathRequested.Value.No_Reply_Path_Set));
                sMSInformation.setSMStatus(new SMStatus("octetstring1322896473"));
                sMSInformation.setSMUserDataHeader(new SMUserDataHeader("octetstring1553722537"));
                sMSInformation.setNumberOfMessagesSent(new NumberOfMessagesSent(new Integer(-316313401)));
                {
                    RecipientInfo recipientInfo = new RecipientInfo();
                    {
                        DestinationInterface destinationInterface = new DestinationInterface();
                        destinationInterface.setInterfaceId(new InterfaceId("utf8string2013236084"));
                        destinationInterface.setInterfaceText(new InterfaceText("utf8string156218768"));
                        destinationInterface.setInterfacePort(new InterfacePort("utf8string-2136291940"));
                        destinationInterface.setInterfaceType(new InterfaceType(InterfaceType.Value.APPLICATION_ORIGINATING));
                        recipientInfo.setDestinationInterface(destinationInterface);
                    }
                    {
                        RecipientAddress recipientAddress = new RecipientAddress();
                        recipientAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.Numeric_Shortcode));
                        recipientAddress.setAddressData(new AddressData("utf8string1111974587"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string918792339"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1538393327"));
                            recipientAddress.setAddressDomain(addressDomain);
                        }
                        recipientAddress.setAddresseeType(new AddresseeType(AddresseeType.Value.CC));
                        recipientInfo.addRecipientAddress(recipientAddress);
                    }
                    {
                        RecipientReceivedAddress recipientReceivedAddress = new RecipientReceivedAddress();
                        recipientReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.Other));
                        recipientReceivedAddress.setAddressData(new AddressData("utf8string2095492434"));
                        {
                            AddressDomain addressDomain = new AddressDomain();
                            addressDomain.setDomainName(new DomainName("utf8string113151066"));
                            addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string-1930415"));
                            recipientReceivedAddress.setAddressDomain(addressDomain);
                        }
                        recipientInfo.addRecipientReceivedAddress(recipientReceivedAddress);
                    }
                    recipientInfo.setRecipientSCCPAddress(new RecipientSCCPAddress(new Address(Address.Family.IPV4, "172.213.82.184")));
                    recipientInfo.setSMProtocolID(new SMProtocolID("octetstring-1481984154"));
                    sMSInformation.addRecipientInfo(recipientInfo);
                }
                {
                    OriginatorReceivedAddress originatorReceivedAddress = new OriginatorReceivedAddress();
                    originatorReceivedAddress.setIMSAddressType(new IMSAddressType(IMSAddressType.Value.e_mail_address));
                    originatorReceivedAddress.setAddressData(new AddressData("utf8string1880669439"));
                    {
                        AddressDomain addressDomain = new AddressDomain();
                        addressDomain.setDomainName(new DomainName("utf8string-57374180"));
                        addressDomain.setRo3GPPIMSIMCCMNC(new Ro3GPPIMSIMCCMNC("utf8string1883186854"));
                        originatorReceivedAddress.setAddressDomain(addressDomain);
                    }
                    sMSInformation.setOriginatorReceivedAddress(originatorReceivedAddress);
                }
                sMSInformation.setSMServiceType(new SMServiceType(SMServiceType.Value.VAS4SMS_content_processing));
                serviceInformation.setSMSInformation(sMSInformation);
            }
            {
                MMTelInformation mMTelInformation = new MMTelInformation();
                {
                    SupplementaryService supplementaryService = new SupplementaryService();
                    supplementaryService.setServiceType(new ServiceType(new Integer(-1746986265)));
                    supplementaryService.setServiceMode(new ServiceMode(new Integer(353831105)));
                    supplementaryService.setNumberOfDiversions(new NumberOfDiversions(new Integer(-1977736089)));
                    supplementaryService.setAssociatedPartyAddress(new AssociatedPartyAddress("utf8string-806013776"));
                    supplementaryService.setServiceId(new ServiceId("utf8string765668327"));
                    supplementaryService.setChangeTime(new ChangeTime(-680957255));
                    supplementaryService.setNumberOfParticipants(new NumberOfParticipants(new Integer(-2132183526)));
                    supplementaryService.setParticipantActionType(new ParticipantActionType(ParticipantActionType.Value.JOIN_CONF));
                    supplementaryService.setCUGInformation(new CUGInformation("octetstring1925242690"));
                    {
                        AoCInformation aoCInformation = new AoCInformation();
                        {
                            AoCCostInformation aoCCostInformation = new AoCCostInformation();
                            {
                                AccumulatedCost accumulatedCost = new AccumulatedCost();
                                accumulatedCost.setValueDigits(new ValueDigits(new Long(-8093231985714630178L)));
                                accumulatedCost.setExponent(new Exponent(new Integer(-794486302)));
                                aoCCostInformation.setAccumulatedCost(accumulatedCost);
                            }
                            {
                                IncrementalCost incrementalCost = new IncrementalCost();
                                incrementalCost.setValueDigits(new ValueDigits(new Long(8379275845635948601L)));
                                incrementalCost.setExponent(new Exponent(new Integer(81106414)));
                                aoCCostInformation.addIncrementalCost(incrementalCost);
                            }
                            aoCCostInformation.setCurrencyCode(new CurrencyCode(new Integer(-935108161)));
                            aoCInformation.setAoCCostInformation(aoCCostInformation);
                        }
                        {
                            TariffInformation tariffInformation = new TariffInformation();
                            {
                                CurrentTariff currentTariff = new CurrentTariff();
                                currentTariff.setCurrencyCode(new CurrencyCode(new Integer(-719736215)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(813194148254819162L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(19516546)));
                                    currentTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.TOTAL_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.ADD_ON_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(2836476089150748137L)));
                                        unitValue.setExponent(new Exponent(new Integer(151958644)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(7271672436108092319L)));
                                        unitCost.setExponent(new Exponent(new Integer(1719065901)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(452924677)));
                                    currentTariff.addRateElement(rateElement);
                                }
                                tariffInformation.setCurrentTariff(currentTariff);
                            }
                            tariffInformation.setTariffTimeChange(new TariffTimeChange(2039098116));
                            {
                                NextTariff nextTariff = new NextTariff();
                                nextTariff.setCurrencyCode(new CurrencyCode(new Integer(1195103370)));
                                {
                                    ScaleFactor scaleFactor = new ScaleFactor();
                                    scaleFactor.setValueDigits(new ValueDigits(new Long(741398922063057682L)));
                                    scaleFactor.setExponent(new Exponent(new Integer(1724407916)));
                                    nextTariff.setScaleFactor(scaleFactor);
                                }
                                {
                                    RateElement rateElement = new RateElement();
                                    rateElement.setCCUnitType(new CCUnitType(CCUnitType.Value.OUTPUT_OCTETS));
                                    rateElement.setReasonCode(new ReasonCode(ReasonCode.Value.COMMUNICATION_ATTEMPT_CHARGE));
                                    {
                                        UnitValue unitValue = new UnitValue();
                                        unitValue.setValueDigits(new ValueDigits(new Long(-575868169540568886L)));
                                        unitValue.setExponent(new Exponent(new Integer(-1951279905)));
                                        rateElement.setUnitValue(unitValue);
                                    }
                                    {
                                        UnitCost unitCost = new UnitCost();
                                        unitCost.setValueDigits(new ValueDigits(new Long(-3049263009055725563L)));
                                        unitCost.setExponent(new Exponent(new Integer(-231155823)));
                                        rateElement.setUnitCost(unitCost);
                                    }
                                    rateElement.setUnitQuotaThreshold(new UnitQuotaThreshold(new Integer(1318649484)));
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
                            aoCSubscriptionInformation.setPreferredAoCCurrency(new PreferredAoCCurrency(new Integer(-667423314)));
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
                serviceGenericInformation.setApplicationServerID(new ApplicationServerID("utf8string-312219743"));
                serviceGenericInformation.setApplicationServiceType(new ApplicationServiceType("utf8string88180529"));
                serviceGenericInformation.setApplicationSessionID(new ApplicationSessionID("utf8string-1605973698"));
                serviceGenericInformation.setDeliveryStatus(new DeliveryStatus("utf8string-853963457"));
                serviceInformation.setServiceGenericInformation(serviceGenericInformation);
            }
            {
                IMInformation iMInformation = new IMInformation();
                iMInformation.setTotalNumberOfMessagesSent(new TotalNumberOfMessagesSent(new Integer(-207114164)));
                iMInformation.setTotalNumberOfMessagesExploded(new TotalNumberOfMessagesExploded(new Integer(123683142)));
                iMInformation.setNumberOfMessagesSuccessfullySent(new NumberOfMessagesSuccessfullySent(new Integer(-233979489)));
                iMInformation.setNumberOfMessagesSuccessfullyExploded(new NumberOfMessagesSuccessfullyExploded(new Integer(-251429164)));
                serviceInformation.setIMInformation(iMInformation);
            }
            {
                DCDInformation dCDInformation = new DCDInformation();
                dCDInformation.setContentID(new ContentID("utf8string709697361"));
                dCDInformation.setContentproviderID(new ContentproviderID("utf8string-1491088635"));
                serviceInformation.setDCDInformation(dCDInformation);
            }
            creditControlAnswer.setServiceInformation(serviceInformation);
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
