package diameter.dcca;

import com.intellinet.diameter.*;
import diameter.*;

public class CreditControlTest {

    public static void testCreditControlRequest() throws Exception {
        CreditControlRequest creditControlRequest = new CreditControlRequest(false, false);
        creditControlRequest.setSessionId(new diameter.base.SessionId("utf8string1842436288"));
        creditControlRequest.setOriginHost(new diameter.base.OriginHost("id1731084809.diameter.com"));
        creditControlRequest.setOriginRealm(new diameter.base.OriginRealm("id-1968186820.diameter.com"));
        creditControlRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-2010288296.diameter.com"));
        creditControlRequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(371092081)));
        creditControlRequest.setServiceContextId(new ServiceContextId("utf8string1577426714"));
        creditControlRequest.setCCRequestType(new CCRequestType(CCRequestType.Value.UPDATE_REQUEST));
        creditControlRequest.setCCRequestNumber(new CCRequestNumber(new Integer(1429850766)));
        creditControlRequest.setDestinationHost(new diameter.base.DestinationHost("id-2108225628.diameter.com"));
        creditControlRequest.setUserName(new diameter.base.UserName("utf8string-2039312122"));
        creditControlRequest.setCCSubSessionId(new CCSubSessionId(new Long(-5912245072262340413L)));
        creditControlRequest.setAcctMultiSessionId(new diameter.base.AcctMultiSessionId("utf8string721303964"));
        creditControlRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(2071721713)));
        creditControlRequest.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(-1567500606)));
        {
            SubscriptionId subscriptionId = new SubscriptionId();
            subscriptionId.setSubscriptionIdType(new SubscriptionIdType(SubscriptionIdType.Value.END_USER_NAI));
            subscriptionId.setSubscriptionIdData(new SubscriptionIdData("utf8string-1328150019"));
            creditControlRequest.addSubscriptionId(subscriptionId);
        }
        creditControlRequest.setServiceIdentifier(new ServiceIdentifier(new Integer(-2072364827)));
        creditControlRequest.setTerminationCause(new diameter.base.TerminationCause(diameter.base.TerminationCause.Value.DIAMETER_ADMINISTRATIVE));
        {
            RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
            requestedServiceUnit.setCCTime(new CCTime(new Integer(-1515914351)));
            {
                CCMoney cCMoney = new CCMoney();
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(-4077270999435246054L)));
                    unitValue.setExponent(new Exponent(new Integer(-1809046464)));
                    cCMoney.setUnitValue(unitValue);
                }
                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(1260724522)));
                requestedServiceUnit.setCCMoney(cCMoney);
            }
            requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-1697341755396967561L)));
            requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-1784727052237446712L)));
            requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-3655346357392277928L)));
            requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(147831739203026358L)));
            // add more AVP as ANY values to requestedServiceUnit
            creditControlRequest.setRequestedServiceUnit(requestedServiceUnit);
        }
        creditControlRequest.setRequestedAction(new RequestedAction(RequestedAction.Value.DIRECT_DEBITING));
        {
            UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
            usedServiceUnit.setTariffTimeChange(new TariffTimeChange(-1360971887));
            usedServiceUnit.setCCTime(new CCTime(new Integer(1577989648)));
            {
                CCMoney cCMoney = new CCMoney();
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(7609504554197637498L)));
                    unitValue.setExponent(new Exponent(new Integer(-1963189581)));
                    cCMoney.setUnitValue(unitValue);
                }
                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(1675136859)));
                usedServiceUnit.setCCMoney(cCMoney);
            }
            usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(5987577146268823025L)));
            usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(940361224440727663L)));
            usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-8605338485219726845L)));
            usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(8561347242835219198L)));
            // add more AVP as ANY values to usedServiceUnit
            creditControlRequest.addUsedServiceUnit(usedServiceUnit);
        }
        creditControlRequest.setMultipleServicesIndicator(new MultipleServicesIndicator(MultipleServicesIndicator.Value.MULTIPLE_SERVICES_SUPPORTED));
        {
            MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
            {
                GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(-570734288));
                grantedServiceUnit.setCCTime(new CCTime(new Integer(-1085430840)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(6298785147706317758L)));
                        unitValue.setExponent(new Exponent(new Integer(-625694772)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(1343964462)));
                    grantedServiceUnit.setCCMoney(cCMoney);
                }
                grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(4388488770361260051L)));
                grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(4077502669568768802L)));
                grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-845605230381703129L)));
                grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(78538669925814321L)));
                // add more AVP as ANY values to grantedServiceUnit
                multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
            }
            {
                RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                requestedServiceUnit.setCCTime(new CCTime(new Integer(-681796126)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(-1677254656618345888L)));
                        unitValue.setExponent(new Exponent(new Integer(367182721)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(2011558950)));
                    requestedServiceUnit.setCCMoney(cCMoney);
                }
                requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(1299587229647447970L)));
                requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(7503439067286799456L)));
                requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-9198718229420563216L)));
                requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-6050638542296928484L)));
                // add more AVP as ANY values to requestedServiceUnit
                multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
            }
            {
                UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                usedServiceUnit.setTariffTimeChange(new TariffTimeChange(-371819582));
                usedServiceUnit.setCCTime(new CCTime(new Integer(484884738)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(8966129971316790993L)));
                        unitValue.setExponent(new Exponent(new Integer(464878434)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(531783217)));
                    usedServiceUnit.setCCMoney(cCMoney);
                }
                usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(8571842084642195358L)));
                usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(6220235606916518730L)));
                usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(2097061347428640310L)));
                usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(873396433094325668L)));
                // add more AVP as ANY values to usedServiceUnit
                multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
            }
            multipleServicesCreditControl.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_BEFORE_TARIFF_CHANGE));
            multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(1235360279)));
            multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(2113185681)));
            {
                GSUPoolReference gSUPoolReference = new GSUPoolReference();
                gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(284340339)));
                gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.TOTAL_OCTETS));
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(-566847715801052660L)));
                    unitValue.setExponent(new Exponent(new Integer(1194589535)));
                    gSUPoolReference.setUnitValue(unitValue);
                }
                multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
            }
            multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(1464333983)));
            multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(1436740006)));
            {
                FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.TERMINATE));
                finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                finalUnitIndication.addFilterId(new FilterId("utf8string-1862577584"));
                {
                    RedirectServer redirectServer = new RedirectServer();
                    redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv4_Address));
                    redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string-1566168163"));
                    finalUnitIndication.setRedirectServer(redirectServer);
                }
                multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
            }
            creditControlRequest.addMultipleServicesCreditControl(multipleServicesCreditControl);
        }
        {
            ServiceParameterInfo serviceParameterInfo = new ServiceParameterInfo();
            serviceParameterInfo.setServiceParameterType(new ServiceParameterType(new Integer(1399842697)));
            serviceParameterInfo.setServiceParameterValue(new ServiceParameterValue("octetstring441440395"));
            creditControlRequest.addServiceParameterInfo(serviceParameterInfo);
        }
        creditControlRequest.setCCCorrelationId(new CCCorrelationId("octetstring997122831"));
        {
            UserEquipmentInfo userEquipmentInfo = new UserEquipmentInfo();
            userEquipmentInfo.setUserEquipmentInfoType(new UserEquipmentInfoType(UserEquipmentInfoType.Value.IMEISV));
            userEquipmentInfo.setUserEquipmentInfoValue(new UserEquipmentInfoValue("octetstring-536532907"));
            creditControlRequest.setUserEquipmentInfo(userEquipmentInfo);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1862598398.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-457119627"));
            // add more AVP as ANY values to proxyInfo
            creditControlRequest.addProxyInfo(proxyInfo);
        }
        creditControlRequest.addRouteRecord(new diameter.base.RouteRecord("id1161342694.diameter.com"));
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
        creditControlAnswer.setSessionId(new diameter.base.SessionId("utf8string786156949"));
        creditControlAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-204650009)));
        creditControlAnswer.setOriginHost(new diameter.base.OriginHost("id-259258569.diameter.com"));
        creditControlAnswer.setOriginRealm(new diameter.base.OriginRealm("id1440312578.diameter.com"));
        creditControlAnswer.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(792302172)));
        creditControlAnswer.setCCRequestType(new CCRequestType(CCRequestType.Value.TERMINATION_REQUEST));
        creditControlAnswer.setCCRequestNumber(new CCRequestNumber(new Integer(-33147805)));
        creditControlAnswer.setUserName(new diameter.base.UserName("utf8string1082666669"));
        creditControlAnswer.setCCSessionFailover(new CCSessionFailover(CCSessionFailover.Value.FAILOVER_NOT_SUPPORTED));
        creditControlAnswer.setCCSubSessionId(new CCSubSessionId(new Long(3090615324775043607L)));
        creditControlAnswer.setAcctMultiSessionId(new diameter.base.AcctMultiSessionId("utf8string-708743408"));
        creditControlAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(-1916898034)));
        creditControlAnswer.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(-1517861862)));
        {
            GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
            grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(-678361020));
            grantedServiceUnit.setCCTime(new CCTime(new Integer(767465013)));
            {
                CCMoney cCMoney = new CCMoney();
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(3813647343621922566L)));
                    unitValue.setExponent(new Exponent(new Integer(-1222253131)));
                    cCMoney.setUnitValue(unitValue);
                }
                cCMoney.setCurrencyCode(new CurrencyCode(new Integer(2102042551)));
                grantedServiceUnit.setCCMoney(cCMoney);
            }
            grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(5639623584716303084L)));
            grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(6734866402667002041L)));
            grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-6162956946591823703L)));
            grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-3257805014174414567L)));
            // add more AVP as ANY values to grantedServiceUnit
            creditControlAnswer.setGrantedServiceUnit(grantedServiceUnit);
        }
        {
            MultipleServicesCreditControl multipleServicesCreditControl = new MultipleServicesCreditControl();
            {
                GrantedServiceUnit grantedServiceUnit = new GrantedServiceUnit();
                grantedServiceUnit.setTariffTimeChange(new TariffTimeChange(735495935));
                grantedServiceUnit.setCCTime(new CCTime(new Integer(1300906090)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(2626707435467447268L)));
                        unitValue.setExponent(new Exponent(new Integer(698855880)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(267952442)));
                    grantedServiceUnit.setCCMoney(cCMoney);
                }
                grantedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(735680287958735627L)));
                grantedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(7374104384128681436L)));
                grantedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(-2137917812321496489L)));
                grantedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-7015471754344983846L)));
                // add more AVP as ANY values to grantedServiceUnit
                multipleServicesCreditControl.setGrantedServiceUnit(grantedServiceUnit);
            }
            {
                RequestedServiceUnit requestedServiceUnit = new RequestedServiceUnit();
                requestedServiceUnit.setCCTime(new CCTime(new Integer(-1747964687)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(-8278128924362724952L)));
                        unitValue.setExponent(new Exponent(new Integer(278512093)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(-1612422385)));
                    requestedServiceUnit.setCCMoney(cCMoney);
                }
                requestedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-359401602582765228L)));
                requestedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-1910777214733670006L)));
                requestedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(8099252800128975943L)));
                requestedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(-7400726051496753223L)));
                // add more AVP as ANY values to requestedServiceUnit
                multipleServicesCreditControl.setRequestedServiceUnit(requestedServiceUnit);
            }
            {
                UsedServiceUnit usedServiceUnit = new UsedServiceUnit();
                usedServiceUnit.setTariffTimeChange(new TariffTimeChange(-1070509221));
                usedServiceUnit.setCCTime(new CCTime(new Integer(753649756)));
                {
                    CCMoney cCMoney = new CCMoney();
                    {
                        UnitValue unitValue = new UnitValue();
                        unitValue.setValueDigits(new ValueDigits(new Long(751829779416574902L)));
                        unitValue.setExponent(new Exponent(new Integer(412138681)));
                        cCMoney.setUnitValue(unitValue);
                    }
                    cCMoney.setCurrencyCode(new CurrencyCode(new Integer(1897827017)));
                    usedServiceUnit.setCCMoney(cCMoney);
                }
                usedServiceUnit.setCCTotalOctets(new CCTotalOctets(new Long(-3550409209841095140L)));
                usedServiceUnit.setCCInputOctets(new CCInputOctets(new Long(-7486228938148052093L)));
                usedServiceUnit.setCCOutputOctets(new CCOutputOctets(new Long(7391969476812541458L)));
                usedServiceUnit.setCCServiceSpecificUnits(new CCServiceSpecificUnits(new Long(8132068132899244769L)));
                // add more AVP as ANY values to usedServiceUnit
                multipleServicesCreditControl.addUsedServiceUnit(usedServiceUnit);
            }
            multipleServicesCreditControl.setTariffChangeUsage(new TariffChangeUsage(TariffChangeUsage.Value.UNIT_INDETERMINATE));
            multipleServicesCreditControl.addServiceIdentifier(new ServiceIdentifier(new Integer(-1820186232)));
            multipleServicesCreditControl.setRatingGroup(new RatingGroup(new Integer(960082651)));
            {
                GSUPoolReference gSUPoolReference = new GSUPoolReference();
                gSUPoolReference.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-1092987521)));
                gSUPoolReference.setCCUnitType(new CCUnitType(CCUnitType.Value.TOTAL_OCTETS));
                {
                    UnitValue unitValue = new UnitValue();
                    unitValue.setValueDigits(new ValueDigits(new Long(5455747834558015963L)));
                    unitValue.setExponent(new Exponent(new Integer(315279972)));
                    gSUPoolReference.setUnitValue(unitValue);
                }
                multipleServicesCreditControl.addGSUPoolReference(gSUPoolReference);
            }
            multipleServicesCreditControl.setValidityTime(new ValidityTime(new Integer(1522499109)));
            multipleServicesCreditControl.setResultCode(new diameter.base.ResultCode(new Integer(-1662125040)));
            {
                FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
                finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.REDIRECT));
                finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
                finalUnitIndication.addFilterId(new FilterId("utf8string-193390745"));
                {
                    RedirectServer redirectServer = new RedirectServer();
                    redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.SIP_URI));
                    redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string1519148773"));
                    finalUnitIndication.setRedirectServer(redirectServer);
                }
                multipleServicesCreditControl.setFinalUnitIndication(finalUnitIndication);
            }
            creditControlAnswer.addMultipleServicesCreditControl(multipleServicesCreditControl);
        }
        {
            CostInformation costInformation = new CostInformation();
            {
                UnitValue unitValue = new UnitValue();
                unitValue.setValueDigits(new ValueDigits(new Long(6623939837034194894L)));
                unitValue.setExponent(new Exponent(new Integer(1825001359)));
                costInformation.setUnitValue(unitValue);
            }
            costInformation.setCurrencyCode(new CurrencyCode(new Integer(-1987581173)));
            costInformation.setCostUnit(new CostUnit("utf8string804525868"));
            creditControlAnswer.setCostInformation(costInformation);
        }
        {
            FinalUnitIndication finalUnitIndication = new FinalUnitIndication();
            finalUnitIndication.setFinalUnitAction(new FinalUnitAction(FinalUnitAction.Value.TERMINATE));
            finalUnitIndication.addRestrictionFilterRule(new RestrictionFilterRule(new IPFilterRule()));
            finalUnitIndication.addFilterId(new FilterId("utf8string2020327952"));
            {
                RedirectServer redirectServer = new RedirectServer();
                redirectServer.setRedirectAddressType(new RedirectAddressType(RedirectAddressType.Value.IPv6_Address));
                redirectServer.setRedirectServerAddress(new RedirectServerAddress("utf8string1098238884"));
                finalUnitIndication.setRedirectServer(redirectServer);
            }
            creditControlAnswer.setFinalUnitIndication(finalUnitIndication);
        }
        creditControlAnswer.setCheckBalanceResult(new CheckBalanceResult(CheckBalanceResult.Value.ENOUGH_CREDIT));
        creditControlAnswer.setCreditControlFailureHandling(new CreditControlFailureHandling(CreditControlFailureHandling.Value.RETRY_AND_TERMINATE));
        creditControlAnswer.setDirectDebitingFailureHandling(new DirectDebitingFailureHandling(DirectDebitingFailureHandling.Value.TERMINATE_OR_BUFFER));
        creditControlAnswer.setValidityTime(new ValidityTime(new Integer(566344505)));
        creditControlAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain-960101809.com", URI.Scheme.AAAS, (short)19033, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        creditControlAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_USER));
        creditControlAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(1594024367)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id2140988526.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1959435625"));
            // add more AVP as ANY values to proxyInfo
            creditControlAnswer.addProxyInfo(proxyInfo);
        }
        creditControlAnswer.addRouteRecord(new diameter.base.RouteRecord("id1040510729.diameter.com"));
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
