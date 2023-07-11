package diameter.dcca;

import com.intellinet.diameter.*;

/**
 * This class defines singleton AttributeName instances for all attributes in <i><b>dcca</b></i>.
 */
public abstract class DccaAttributeName {

    private static class FinalUnitIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FinalUnitIndication((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName FinalUnitIndication = new com.intellinet.diameter.GroupedName("Final-Unit-Indication", new FinalUnitIndicationAVPBuilder());

    private static class CCTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CCTime = new com.intellinet.diameter.Unsigned32Name("CC-Time", new CCTimeAVPBuilder());

    private static class GrantedServiceUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GrantedServiceUnit((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName GrantedServiceUnit = new com.intellinet.diameter.GroupedName("Granted-Service-Unit", new GrantedServiceUnitAVPBuilder());

    private static class GSUPoolReferenceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GSUPoolReference((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName GSUPoolReference = new com.intellinet.diameter.GroupedName("G-S-U-Pool-Reference", new GSUPoolReferenceAVPBuilder());

    private static class CostUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CostUnit((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CostUnit = new com.intellinet.diameter.UTF8StringName("Cost-Unit", new CostUnitAVPBuilder());

    private static class UserEquipmentInfoTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserEquipmentInfoType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName UserEquipmentInfoType = new com.intellinet.diameter.EnumeratedName("User-Equipment-Info-Type", new UserEquipmentInfoTypeAVPBuilder());

    private static class CCUnitTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCUnitType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CCUnitType = new com.intellinet.diameter.EnumeratedName("CC-Unit-Type", new CCUnitTypeAVPBuilder());

    private static class ServiceContextIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceContextId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ServiceContextId = new com.intellinet.diameter.UTF8StringName("Service-Context-Id", new ServiceContextIdAVPBuilder());

    private static class MultipleServicesCreditControlAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MultipleServicesCreditControl((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MultipleServicesCreditControl = new com.intellinet.diameter.GroupedName("Multiple-Services-Credit-Control", new MultipleServicesCreditControlAVPBuilder());

    private static class FinalUnitActionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FinalUnitAction((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName FinalUnitAction = new com.intellinet.diameter.EnumeratedName("Final-Unit-Action", new FinalUnitActionAVPBuilder());

    private static class TariffChangeUsageAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TariffChangeUsage((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TariffChangeUsage = new com.intellinet.diameter.EnumeratedName("Tariff-Change-Usage", new TariffChangeUsageAVPBuilder());

    private static class RequestedActionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequestedAction((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RequestedAction = new com.intellinet.diameter.EnumeratedName("Requested-Action", new RequestedActionAVPBuilder());

    private static class CCMoneyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCMoney((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CCMoney = new com.intellinet.diameter.GroupedName("CC-Money", new CCMoneyAVPBuilder());

    private static class CCOutputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCOutputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCOutputOctets = new com.intellinet.diameter.Unsigned64Name("CC-Output-Octets", new CCOutputOctetsAVPBuilder());

    private static class CCTotalOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCTotalOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCTotalOctets = new com.intellinet.diameter.Unsigned64Name("CC-Total-Octets", new CCTotalOctetsAVPBuilder());

    private static class ServiceParameterTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceParameterType((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ServiceParameterType = new com.intellinet.diameter.Unsigned32Name("Service-Parameter-Type", new ServiceParameterTypeAVPBuilder());

    private static class ServiceIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceIdentifier((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ServiceIdentifier = new com.intellinet.diameter.Unsigned32Name("Service-Identifier", new ServiceIdentifierAVPBuilder());

    private static class UserEquipmentInfoValueAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserEquipmentInfoValue((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName UserEquipmentInfoValue = new com.intellinet.diameter.OctetStringName("User-Equipment-Info-Value", new UserEquipmentInfoValueAVPBuilder());

    private static class SubscriptionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionId((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SubscriptionId = new com.intellinet.diameter.GroupedName("Subscription-Id", new SubscriptionIdAVPBuilder());

    private static class UserEquipmentInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserEquipmentInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UserEquipmentInfo = new com.intellinet.diameter.GroupedName("User-Equipment-Info", new UserEquipmentInfoAVPBuilder());

    private static class CCServiceSpecificUnitsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCServiceSpecificUnits((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCServiceSpecificUnits = new com.intellinet.diameter.Unsigned64Name("CC-Service-Specific-Units", new CCServiceSpecificUnitsAVPBuilder());

    private static class ServiceParameterInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceParameterInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServiceParameterInfo = new com.intellinet.diameter.GroupedName("Service-Parameter-Info", new ServiceParameterInfoAVPBuilder());

    private static class CCInputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCInputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCInputOctets = new com.intellinet.diameter.Unsigned64Name("CC-Input-Octets", new CCInputOctetsAVPBuilder());

    private static class CheckBalanceResultAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CheckBalanceResult((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CheckBalanceResult = new com.intellinet.diameter.EnumeratedName("Check-Balance-Result", new CheckBalanceResultAVPBuilder());

    private static class CCRequestNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCRequestNumber((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CCRequestNumber = new com.intellinet.diameter.Unsigned32Name("CC-Request-Number", new CCRequestNumberAVPBuilder());

    private static class ExponentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Exponent((com.intellinet.diameter.Integer32Data)impl);
        }
    }

    public static final AttributeName Exponent = new com.intellinet.diameter.Integer32Name("Exponent", new ExponentAVPBuilder());

    private static class UnitValueAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UnitValue((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UnitValue = new com.intellinet.diameter.GroupedName("Unit-Value", new UnitValueAVPBuilder());

    private static class CreditControlFailureHandlingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CreditControlFailureHandling((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CreditControlFailureHandling = new com.intellinet.diameter.EnumeratedName("Credit-Control-Failure-Handling", new CreditControlFailureHandlingAVPBuilder());

    private static class CurrencyCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CurrencyCode((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CurrencyCode = new com.intellinet.diameter.Unsigned32Name("Currency-Code", new CurrencyCodeAVPBuilder());

    private static class UsedServiceUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UsedServiceUnit((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UsedServiceUnit = new com.intellinet.diameter.GroupedName("Used-Service-Unit", new UsedServiceUnitAVPBuilder());

    private static class GSUPoolIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GSUPoolIdentifier((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName GSUPoolIdentifier = new com.intellinet.diameter.Unsigned32Name("G-S-U-Pool-Identifier", new GSUPoolIdentifierAVPBuilder());

    private static class RedirectServerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RedirectServer((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RedirectServer = new com.intellinet.diameter.GroupedName("Redirect-Server", new RedirectServerAVPBuilder());

    private static class RequestedServiceUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequestedServiceUnit((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RequestedServiceUnit = new com.intellinet.diameter.GroupedName("Requested-Service-Unit", new RequestedServiceUnitAVPBuilder());

    private static class MultipleServicesIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MultipleServicesIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MultipleServicesIndicator = new com.intellinet.diameter.EnumeratedName("Multiple-Services-Indicator", new MultipleServicesIndicatorAVPBuilder());

    private static class RedirectServerAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RedirectServerAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName RedirectServerAddress = new com.intellinet.diameter.UTF8StringName("Redirect-Server-Address", new RedirectServerAddressAVPBuilder());

    private static class CCSubSessionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCSubSessionId((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCSubSessionId = new com.intellinet.diameter.Unsigned64Name("CC-Sub-Session-Id", new CCSubSessionIdAVPBuilder());

    private static class SubscriptionIdDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionIdData((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SubscriptionIdData = new com.intellinet.diameter.UTF8StringName("Subscription-Id-Data", new SubscriptionIdDataAVPBuilder());

    private static class CostInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CostInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CostInformation = new com.intellinet.diameter.GroupedName("Cost-Information", new CostInformationAVPBuilder());

    private static class DirectDebitingFailureHandlingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DirectDebitingFailureHandling((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName DirectDebitingFailureHandling = new com.intellinet.diameter.EnumeratedName("Direct-Debiting-Failure-Handling", new DirectDebitingFailureHandlingAVPBuilder());

    private static class ServiceParameterValueAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceParameterValue((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ServiceParameterValue = new com.intellinet.diameter.OctetStringName("Service-Parameter-Value", new ServiceParameterValueAVPBuilder());

    private static class RedirectAddressTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RedirectAddressType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RedirectAddressType = new com.intellinet.diameter.EnumeratedName("Redirect-Address-Type", new RedirectAddressTypeAVPBuilder());

    private static class CCCorrelationIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCCorrelationId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CCCorrelationId = new com.intellinet.diameter.OctetStringName("CC-Correlation-Id", new CCCorrelationIdAVPBuilder());

    private static class SubscriptionIdTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionIdType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SubscriptionIdType = new com.intellinet.diameter.EnumeratedName("Subscription-Id-Type", new SubscriptionIdTypeAVPBuilder());

    private static class ValueDigitsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ValueDigits((com.intellinet.diameter.Integer64Data)impl);
        }
    }

    public static final AttributeName ValueDigits = new com.intellinet.diameter.Integer64Name("Value-Digits", new ValueDigitsAVPBuilder());

    private static class CCRequestTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCRequestType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CCRequestType = new com.intellinet.diameter.EnumeratedName("CC-Request-Type", new CCRequestTypeAVPBuilder());

    private static class CCSessionFailoverAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCSessionFailover((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CCSessionFailover = new com.intellinet.diameter.EnumeratedName("CC-Session-Failover", new CCSessionFailoverAVPBuilder());

    private static class TariffTimeChangeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TariffTimeChange((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName TariffTimeChange = new com.intellinet.diameter.TimeName("Tariff-Time-Change", new TariffTimeChangeAVPBuilder());

    private static class FilterIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FilterId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName FilterId = new com.intellinet.diameter.UTF8StringName("Filter-Id", new FilterIdAVPBuilder());

    private static class ValidityTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ValidityTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ValidityTime = new com.intellinet.diameter.Unsigned32Name("Validity-Time", new ValidityTimeAVPBuilder());

    private static class RatingGroupAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RatingGroup((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName RatingGroup = new com.intellinet.diameter.Unsigned32Name("Rating-Group", new RatingGroupAVPBuilder());

    private static class RestrictionFilterRuleAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RestrictionFilterRule((com.intellinet.diameter.IPFilterRuleData)impl);
        }
    }

    public static final AttributeName RestrictionFilterRule = new com.intellinet.diameter.IPFilterRuleName("Restriction-Filter-Rule", new RestrictionFilterRuleAVPBuilder());

    private static class CreditControlAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CreditControl((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CreditControl = new com.intellinet.diameter.EnumeratedName("Credit-Control", new CreditControlAVPBuilder());
}

