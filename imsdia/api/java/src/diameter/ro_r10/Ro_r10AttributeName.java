package diameter.ro_r10;

import com.intellinet.diameter.*;

/**
 * This class defines singleton AttributeName instances for all attributes in <i><b>ro_r10</b></i>.
 */
public abstract class Ro_r10AttributeName {

    private static class AdaptationsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Adaptations((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName Adaptations = new com.intellinet.diameter.EnumeratedName("Adaptations", new AdaptationsAVPBuilder());

    private static class FinalUnitIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FinalUnitIndication((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName FinalUnitIndication = new com.intellinet.diameter.GroupedName("Final-Unit-Indication", new FinalUnitIndicationAVPBuilder());

    private static class PDGChargingIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDGChargingId((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PDGChargingId = new com.intellinet.diameter.Unsigned32Name("PDG-Charging-Id", new PDGChargingIdAVPBuilder());

    private static class UnitCostAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UnitCost((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UnitCost = new com.intellinet.diameter.GroupedName("Unit-Cost", new UnitCostAVPBuilder());

    private static class GrantedServiceUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GrantedServiceUnit((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName GrantedServiceUnit = new com.intellinet.diameter.GroupedName("Granted-Service-Unit", new GrantedServiceUnitAVPBuilder());

    private static class TrafficDataVolumesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TrafficDataVolumes((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TrafficDataVolumes = new com.intellinet.diameter.GroupedName("Traffic-Data-Volumes", new TrafficDataVolumesAVPBuilder());

    private static class AccountExpirationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountExpiration((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName AccountExpiration = new com.intellinet.diameter.TimeName("Account-Expiration", new AccountExpirationAVPBuilder());

    private static class GSUPoolReferenceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GSUPoolReference((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName GSUPoolReference = new com.intellinet.diameter.GroupedName("G-S-U-Pool-Reference", new GSUPoolReferenceAVPBuilder());

    private static class SDPTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SDPType = new com.intellinet.diameter.EnumeratedName("SDP-Type", new SDPTypeAVPBuilder());

    private static class CCUnitTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCUnitType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CCUnitType = new com.intellinet.diameter.EnumeratedName("CC-Unit-Type", new CCUnitTypeAVPBuilder());

    private static class LCSClientIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSClientID((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName LCSClientID = new com.intellinet.diameter.GroupedName("LCS-Client-ID", new LCSClientIDAVPBuilder());

    private static class ReplyPathRequestedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReplyPathRequested((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ReplyPathRequested = new com.intellinet.diameter.EnumeratedName("Reply-Path-Requested", new ReplyPathRequestedAVPBuilder());

    private static class BearerIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new BearerIdentifier((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName BearerIdentifier = new com.intellinet.diameter.OctetStringName("Bearer-Identifier", new BearerIdentifierAVPBuilder());

    private static class DynamicAddressFlagExtensionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DynamicAddressFlagExtension((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName DynamicAddressFlagExtension = new com.intellinet.diameter.EnumeratedName("Dynamic-Address-Flag-Extension", new DynamicAddressFlagExtensionAVPBuilder());

    private static class OriginatorAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginatorAddress((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName OriginatorAddress = new com.intellinet.diameter.GroupedName("Originator-Address", new OriginatorAddressAVPBuilder());

    private static class InterfaceTextAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new InterfaceText((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName InterfaceText = new com.intellinet.diameter.UTF8StringName("Interface-Text", new InterfaceTextAVPBuilder());

    private static class OperatorNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OperatorName((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName OperatorName = new com.intellinet.diameter.OctetStringName("Operator-Name", new OperatorNameAVPBuilder());

    private static class MessageSizeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MessageSize((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MessageSize = new com.intellinet.diameter.Unsigned32Name("Message-Size", new MessageSizeAVPBuilder());

    private static class FinalUnitActionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FinalUnitAction((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName FinalUnitAction = new com.intellinet.diameter.EnumeratedName("Final-Unit-Action", new FinalUnitActionAVPBuilder());

    private static class AdditionalContentInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AdditionalContentInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AdditionalContentInformation = new com.intellinet.diameter.GroupedName("Additional-Content-Information", new AdditionalContentInformationAVPBuilder());

    private static class QoSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new QoSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName QoSInformation = new com.intellinet.diameter.GroupedName("QoS-Information", new QoSInformationAVPBuilder());

    private static class AoCServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCServiceType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AoCServiceType = new com.intellinet.diameter.EnumeratedName("AoC-Service-Type", new AoCServiceTypeAVPBuilder());

    private static class VASPIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VASPId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName VASPId = new com.intellinet.diameter.UTF8StringName("VASP-Id", new VASPIdAVPBuilder());

    private static class Ro3GPPSessionStopIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPSessionStopIndicator((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Ro3GPPSessionStopIndicator = new com.intellinet.diameter.OctetStringName("Ro-3GPP-Session-Stop-Indicator", new Ro3GPPSessionStopIndicatorAVPBuilder());

    private static class SMDischargeTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMDischargeTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName SMDischargeTime = new com.intellinet.diameter.TimeName("SM-Discharge-Time", new SMDischargeTimeAVPBuilder());

    private static class CCOutputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCOutputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCOutputOctets = new com.intellinet.diameter.Unsigned64Name("CC-Output-Octets", new CCOutputOctetsAVPBuilder());

    private static class Ro3GPPIMSIMCCMNCAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPIMSIMCCMNC((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPIMSIMCCMNC = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-IMSI-MCC-MNC", new Ro3GPPIMSIMCCMNCAVPBuilder());

    private static class ApplicationServerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ApplicationServer((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ApplicationServer = new com.intellinet.diameter.UTF8StringName("Application-Server", new ApplicationServerAVPBuilder());

    private static class InterfaceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new InterfaceType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName InterfaceType = new com.intellinet.diameter.EnumeratedName("Interface-Type", new InterfaceTypeAVPBuilder());

    private static class QuotaHoldingTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new QuotaHoldingTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName QuotaHoldingTime = new com.intellinet.diameter.Unsigned32Name("Quota-Holding-Time", new QuotaHoldingTimeAVPBuilder());

    private static class SIPMethodAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPMethod((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SIPMethod = new com.intellinet.diameter.UTF8StringName("SIP-Method", new SIPMethodAVPBuilder());

    private static class SMProtocolIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMProtocolID((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SMProtocolID = new com.intellinet.diameter.OctetStringName("SM-Protocol-ID", new SMProtocolIDAVPBuilder());

    private static class Ro3GPPPDPTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPPDPType((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName Ro3GPPPDPType = new com.intellinet.diameter.Unsigned32Name("Ro-3GPP-PDP-Type", new Ro3GPPPDPTypeAVPBuilder());

    private static class PDPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName PDPAddress = new com.intellinet.diameter.AddressName("PDP-Address", new PDPAddressAVPBuilder());

    private static class EarlyMediaDescriptionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EarlyMediaDescription((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName EarlyMediaDescription = new com.intellinet.diameter.GroupedName("Early-Media-Description", new EarlyMediaDescriptionAVPBuilder());

    private static class TimeQuotaTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TimeQuotaType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TimeQuotaType = new com.intellinet.diameter.EnumeratedName("Time-Quota-Type", new TimeQuotaTypeAVPBuilder());

    private static class PSAppendFreeFormatDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PSAppendFreeFormatData((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PSAppendFreeFormatData = new com.intellinet.diameter.EnumeratedName("PS-Append-Free-Format-Data", new PSAppendFreeFormatDataAVPBuilder());

    private static class AFChargingIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AFChargingIdentifier((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName AFChargingIdentifier = new com.intellinet.diameter.OctetStringName("AF-Charging-Identifier", new AFChargingIdentifierAVPBuilder());

    private static class RecipientAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RecipientAddress((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RecipientAddress = new com.intellinet.diameter.GroupedName("Recipient-Address", new RecipientAddressAVPBuilder());

    private static class FileRepairSupportedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FileRepairSupported((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName FileRepairSupported = new com.intellinet.diameter.EnumeratedName("File-Repair-Supported", new FileRepairSupportedAVPBuilder());

    private static class LocationInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LocationInformation((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LocationInformation = new com.intellinet.diameter.OctetStringName("Location-Information", new LocationInformationAVPBuilder());

    private static class IncomingTrunkGroupIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IncomingTrunkGroupID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IncomingTrunkGroupID = new com.intellinet.diameter.UTF8StringName("Incoming-Trunk-Group-ID", new IncomingTrunkGroupIDAVPBuilder());

    private static class MMTelInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MMTelInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MMTelInformation = new com.intellinet.diameter.GroupedName("MMTel-Information", new MMTelInformationAVPBuilder());

    private static class OptionalCapabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OptionalCapability((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName OptionalCapability = new com.intellinet.diameter.Unsigned32Name("Optional-Capability", new OptionalCapabilityAVPBuilder());

    private static class MBMSServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MBMSServiceType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MBMSServiceType = new com.intellinet.diameter.EnumeratedName("MBMS-Service-Type", new MBMSServiceTypeAVPBuilder());

    private static class PoCUserRoleAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCUserRole((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName PoCUserRole = new com.intellinet.diameter.GroupedName("PoC-User-Role", new PoCUserRoleAVPBuilder());

    private static class UserEquipmentInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserEquipmentInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UserEquipmentInfo = new com.intellinet.diameter.GroupedName("User-Equipment-Info", new UserEquipmentInfoAVPBuilder());

    private static class LowPriorityIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LowPriorityIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LowPriorityIndicator = new com.intellinet.diameter.EnumeratedName("Low-Priority-Indicator", new LowPriorityIndicatorAVPBuilder());

    private static class ExpiresAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Expires((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName Expires = new com.intellinet.diameter.Unsigned32Name("Expires", new ExpiresAVPBuilder());

    private static class WLANSessionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WLANSessionId((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName WLANSessionId = new com.intellinet.diameter.Unsigned32Name("WLAN-Session-Id", new WLANSessionIdAVPBuilder());

    private static class CCRequestNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCRequestNumber((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CCRequestNumber = new com.intellinet.diameter.Unsigned32Name("CC-Request-Number", new CCRequestNumberAVPBuilder());

    private static class UserParticipatingTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserParticipatingType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName UserParticipatingType = new com.intellinet.diameter.EnumeratedName("User-Participating-Type", new UserParticipatingTypeAVPBuilder());

    private static class AoCSubscriptionInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCSubscriptionInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AoCSubscriptionInformation = new com.intellinet.diameter.GroupedName("AoC-Subscription-Information", new AoCSubscriptionInformationAVPBuilder());

    private static class CreditControlFailureHandlingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CreditControlFailureHandling((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CreditControlFailureHandling = new com.intellinet.diameter.EnumeratedName("Credit-Control-Failure-Handling", new CreditControlFailureHandlingAVPBuilder());

    private static class PoCEventTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCEventType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PoCEventType = new com.intellinet.diameter.EnumeratedName("PoC-Event-Type", new PoCEventTypeAVPBuilder());

    private static class EnvelopeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Envelope((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName Envelope = new com.intellinet.diameter.GroupedName("Envelope", new EnvelopeAVPBuilder());

    private static class IMSChargingIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSChargingIdentifier((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IMSChargingIdentifier = new com.intellinet.diameter.UTF8StringName("IMS-Charging-Identifier", new IMSChargingIdentifierAVPBuilder());

    private static class NumberOfDiversionsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfDiversions((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfDiversions = new com.intellinet.diameter.Unsigned32Name("Number-Of-Diversions", new NumberOfDiversionsAVPBuilder());

    private static class LCSClientTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSClientType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LCSClientType = new com.intellinet.diameter.EnumeratedName("LCS-Client-Type", new LCSClientTypeAVPBuilder());

    private static class PDPAddressPrefixLengthAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDPAddressPrefixLength((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PDPAddressPrefixLength = new com.intellinet.diameter.Unsigned32Name("PDP-Address-Prefix-Length", new PDPAddressPrefixLengthAVPBuilder());

    private static class SIPRequestTimestampAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPRequestTimestamp((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName SIPRequestTimestamp = new com.intellinet.diameter.TimeName("SIP-Request-Timestamp", new SIPRequestTimestampAVPBuilder());

    private static class LCSDataCodingSchemeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSDataCodingScheme((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName LCSDataCodingScheme = new com.intellinet.diameter.UTF8StringName("LCS-Data-Coding-Scheme", new LCSDataCodingSchemeAVPBuilder());

    private static class LocalSequenceNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LocalSequenceNumber((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName LocalSequenceNumber = new com.intellinet.diameter.Unsigned32Name("Local-Sequence-Number", new LocalSequenceNumberAVPBuilder());

    private static class TerminalInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TerminalInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TerminalInformation = new com.intellinet.diameter.GroupedName("Terminal-Information", new TerminalInformationAVPBuilder());

    private static class RoleOfNodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RoleOfNode((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RoleOfNode = new com.intellinet.diameter.EnumeratedName("Role-Of-Node", new RoleOfNodeAVPBuilder());

    private static class VASIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VASId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName VASId = new com.intellinet.diameter.UTF8StringName("VAS-Id", new VASIdAVPBuilder());

    private static class TimeFirstUsageAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TimeFirstUsage((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName TimeFirstUsage = new com.intellinet.diameter.TimeName("Time-First-Usage", new TimeFirstUsageAVPBuilder());

    private static class ChangeConditionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ChangeCondition((com.intellinet.diameter.Integer32Data)impl);
        }
    }

    public static final AttributeName ChangeCondition = new com.intellinet.diameter.Integer32Name("Change-Condition", new ChangeConditionAVPBuilder());

    private static class CauseCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CauseCode((com.intellinet.diameter.Integer32Data)impl);
        }
    }

    public static final AttributeName CauseCode = new com.intellinet.diameter.Integer32Name("Cause-Code", new CauseCodeAVPBuilder());

    private static class EventTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EventType((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName EventType = new com.intellinet.diameter.GroupedName("Event-Type", new EventTypeAVPBuilder());

    private static class RealTimeTariffInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RealTimeTariffInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RealTimeTariffInformation = new com.intellinet.diameter.GroupedName("Real-Time-Tariff-Information", new RealTimeTariffInformationAVPBuilder());

    private static class PSFurnishChargingInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PSFurnishChargingInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName PSFurnishChargingInformation = new com.intellinet.diameter.GroupedName("PS-Furnish-Charging-Information", new PSFurnishChargingInformationAVPBuilder());

    private static class SubscriberRoleAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriberRole((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SubscriberRole = new com.intellinet.diameter.EnumeratedName("Subscriber-Role", new SubscriberRoleAVPBuilder());

    private static class SDPOfferTimestampAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPOfferTimestamp((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName SDPOfferTimestamp = new com.intellinet.diameter.TimeName("SDP-Offer-Timestamp", new SDPOfferTimestampAVPBuilder());

    private static class TimeLastUsageAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TimeLastUsage((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName TimeLastUsage = new com.intellinet.diameter.TimeName("Time-Last-Usage", new TimeLastUsageAVPBuilder());

    private static class QoSClassIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new QoSClassIdentifier((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName QoSClassIdentifier = new com.intellinet.diameter.EnumeratedName("QoS-Class-Identifier", new QoSClassIdentifierAVPBuilder());

    private static class ApplicationServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ApplicationServiceType((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ApplicationServiceType = new com.intellinet.diameter.UTF8StringName("Application-Service-Type", new ApplicationServiceTypeAVPBuilder());

    private static class IMSApplicationReferenceIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSApplicationReferenceIdentifier((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IMSApplicationReferenceIdentifier = new com.intellinet.diameter.UTF8StringName("IMS-Application-Reference-Identifier", new IMSApplicationReferenceIdentifierAVPBuilder());

    private static class WLANInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WLANInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName WLANInformation = new com.intellinet.diameter.GroupedName("WLAN-Information", new WLANInformationAVPBuilder());

    private static class SDPMediaDescriptionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPMediaDescription((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SDPMediaDescription = new com.intellinet.diameter.UTF8StringName("SDP-Media-Description", new SDPMediaDescriptionAVPBuilder());

    private static class MBMSGWAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MBMSGWAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName MBMSGWAddress = new com.intellinet.diameter.AddressName("MBMS-GW-Address", new MBMSGWAddressAVPBuilder());

    private static class SoftwareVersionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SoftwareVersion((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SoftwareVersion = new com.intellinet.diameter.UTF8StringName("Software-Version", new SoftwareVersionAVPBuilder());

    private static class TariffTimeChangeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TariffTimeChange((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName TariffTimeChange = new com.intellinet.diameter.TimeName("Tariff-Time-Change", new TariffTimeChangeAVPBuilder());

    private static class StopTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new StopTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName StopTime = new com.intellinet.diameter.TimeName("Stop-Time", new StopTimeAVPBuilder());

    private static class ScaleFactorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ScaleFactor((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ScaleFactor = new com.intellinet.diameter.GroupedName("Scale-Factor", new ScaleFactorAVPBuilder());

    private static class ContentproviderIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContentproviderID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ContentproviderID = new com.intellinet.diameter.UTF8StringName("Content-provider-ID", new ContentproviderIDAVPBuilder());

    private static class ServiceGenericInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceGenericInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServiceGenericInformation = new com.intellinet.diameter.GroupedName("Service-Generic-Information", new ServiceGenericInformationAVPBuilder());

    private static class WAGAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WAGAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName WAGAddress = new com.intellinet.diameter.AddressName("WAG-Address", new WAGAddressAVPBuilder());

    private static class ContentClassAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContentClass((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ContentClass = new com.intellinet.diameter.EnumeratedName("Content-Class", new ContentClassAVPBuilder());

    private static class MMBoxStorageRequestedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MMBoxStorageRequested((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MMBoxStorageRequested = new com.intellinet.diameter.EnumeratedName("MMBox-Storage-Requested", new MMBoxStorageRequestedAVPBuilder());

    private static class TypeNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TypeNumber((com.intellinet.diameter.Integer32Data)impl);
        }
    }

    public static final AttributeName TypeNumber = new com.intellinet.diameter.Integer32Name("Type-Number", new TypeNumberAVPBuilder());

    private static class GGSNAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GGSNAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName GGSNAddress = new com.intellinet.diameter.AddressName("GGSN-Address", new GGSNAddressAVPBuilder());

    private static class PoCGroupNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCGroupName((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName PoCGroupName = new com.intellinet.diameter.UTF8StringName("PoC-Group-Name", new PoCGroupNameAVPBuilder());

    private static class PSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName PSInformation = new com.intellinet.diameter.GroupedName("PS-Information", new PSInformationAVPBuilder());

    private static class UserEquipmentInfoTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserEquipmentInfoType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName UserEquipmentInfoType = new com.intellinet.diameter.EnumeratedName("User-Equipment-Info-Type", new UserEquipmentInfoTypeAVPBuilder());

    private static class Ro3GPPChargingIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPChargingId((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName Ro3GPPChargingId = new com.intellinet.diameter.Unsigned32Name("Ro-3GPP-Charging-Id", new Ro3GPPChargingIdAVPBuilder());

    private static class TimeQuotaThresholdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TimeQuotaThreshold((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName TimeQuotaThreshold = new com.intellinet.diameter.Unsigned32Name("Time-Quota-Threshold", new TimeQuotaThresholdAVPBuilder());

    private static class ParticipantAccessPriorityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ParticipantAccessPriority((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ParticipantAccessPriority = new com.intellinet.diameter.EnumeratedName("Participant-Access-Priority", new ParticipantAccessPriorityAVPBuilder());

    private static class MultipleServicesCreditControlAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MultipleServicesCreditControl((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MultipleServicesCreditControl = new com.intellinet.diameter.GroupedName("Multiple-Services-Credit-Control", new MultipleServicesCreditControlAVPBuilder());

    private static class UnitQuotaThresholdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UnitQuotaThreshold((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName UnitQuotaThreshold = new com.intellinet.diameter.Unsigned32Name("Unit-Quota-Threshold", new UnitQuotaThresholdAVPBuilder());

    private static class SDPMediaNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPMediaName((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SDPMediaName = new com.intellinet.diameter.UTF8StringName("SDP-Media-Name", new SDPMediaNameAVPBuilder());

    private static class CalledAssertedIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CalledAssertedIdentity((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CalledAssertedIdentity = new com.intellinet.diameter.UTF8StringName("Called-Asserted-Identity", new CalledAssertedIdentityAVPBuilder());

    private static class LCSFormatIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSFormatIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LCSFormatIndicator = new com.intellinet.diameter.EnumeratedName("LCS-Format-Indicator", new LCSFormatIndicatorAVPBuilder());

    private static class TotalNumberOfMessagesSentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TotalNumberOfMessagesSent((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName TotalNumberOfMessagesSent = new com.intellinet.diameter.Unsigned32Name("Total-Number-Of-Messages-Sent", new TotalNumberOfMessagesSentAVPBuilder());

    private static class AddressDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AddressData((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName AddressData = new com.intellinet.diameter.UTF8StringName("Address-Data", new AddressDataAVPBuilder());

    private static class AddressDomainAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AddressDomain((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AddressDomain = new com.intellinet.diameter.GroupedName("Address-Domain", new AddressDomainAVPBuilder());

    private static class IPRealmDefaultIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IPRealmDefaultIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName IPRealmDefaultIndication = new com.intellinet.diameter.EnumeratedName("IP-Realm-Default-Indication", new IPRealmDefaultIndicationAVPBuilder());

    private static class OriginatorInterfaceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginatorInterface((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName OriginatorInterface = new com.intellinet.diameter.GroupedName("Originator-Interface", new OriginatorInterfaceAVPBuilder());

    private static class WLANUELocalIPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WLANUELocalIPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName WLANUELocalIPAddress = new com.intellinet.diameter.AddressName("WLAN-UE-Local-IPAddress", new WLANUELocalIPAddressAVPBuilder());

    private static class SIPResponseTimestampAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPResponseTimestamp((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName SIPResponseTimestamp = new com.intellinet.diameter.TimeName("SIP-Response-Timestamp", new SIPResponseTimestampAVPBuilder());

    private static class PoCSessionTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCSessionType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PoCSessionType = new com.intellinet.diameter.EnumeratedName("PoC-Session-Type", new PoCSessionTypeAVPBuilder());

    private static class PoCUserRoleIdsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCUserRoleIds((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName PoCUserRoleIds = new com.intellinet.diameter.UTF8StringName("PoC-User-Role-Ids", new PoCUserRoleIdsAVPBuilder());

    private static class SDPSessionDescriptionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPSessionDescription((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SDPSessionDescription = new com.intellinet.diameter.UTF8StringName("SDP-Session-Description", new SDPSessionDescriptionAVPBuilder());

    private static class TalkBurstExchangeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TalkBurstExchange((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TalkBurstExchange = new com.intellinet.diameter.GroupedName("Talk-Burst-Exchange", new TalkBurstExchangeAVPBuilder());

    private static class EnvelopeStartTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EnvelopeStartTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName EnvelopeStartTime = new com.intellinet.diameter.TimeName("Envelope-Start-Time", new EnvelopeStartTimeAVPBuilder());

    private static class ClassIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ClassIdentifier((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ClassIdentifier = new com.intellinet.diameter.EnumeratedName("Class-Identifier", new ClassIdentifierAVPBuilder());

    private static class Ro3GPPGPRSNegotiatedQoSProfileAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPGPRSNegotiatedQoSProfile((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPGPRSNegotiatedQoSProfile = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-GPRS-Negotiated-QoS-Profile", new Ro3GPPGPRSNegotiatedQoSProfileAVPBuilder());

    private static class CCTotalOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCTotalOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCTotalOctets = new com.intellinet.diameter.Unsigned64Name("CC-Total-Octets", new CCTotalOctetsAVPBuilder());

    private static class LCSRequestorIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSRequestorID((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName LCSRequestorID = new com.intellinet.diameter.GroupedName("LCS-Requestor-ID", new LCSRequestorIDAVPBuilder());

    private static class MBMSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MBMSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MBMSInformation = new com.intellinet.diameter.GroupedName("MBMS-Information", new MBMSInformationAVPBuilder());

    private static class LCSClientDialedByMSAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSClientDialedByMS((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName LCSClientDialedByMS = new com.intellinet.diameter.UTF8StringName("LCS-Client-Dialed-By-MS", new LCSClientDialedByMSAVPBuilder());

    private static class WAGPLMNIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WAGPLMNId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName WAGPLMNId = new com.intellinet.diameter.OctetStringName("WAG-PLMN-Id", new WAGPLMNIdAVPBuilder());

    private static class TalkBurstVolumeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TalkBurstVolume((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName TalkBurstVolume = new com.intellinet.diameter.Unsigned32Name("Talk-Burst-Volume", new TalkBurstVolumeAVPBuilder());

    private static class AlternateChargedPartyAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AlternateChargedPartyAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName AlternateChargedPartyAddress = new com.intellinet.diameter.UTF8StringName("Alternate-Charged-Party-Address", new AlternateChargedPartyAddressAVPBuilder());

    private static class RATTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RATType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RATType = new com.intellinet.diameter.EnumeratedName("RAT-Type", new RATTypeAVPBuilder());

    private static class IMSIUnauthenticatedFlagAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSIUnauthenticatedFlag((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName IMSIUnauthenticatedFlag = new com.intellinet.diameter.EnumeratedName("IMSI-Unauthenticated-Flag", new IMSIUnauthenticatedFlagAVPBuilder());

    private static class MessageClassAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MessageClass((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MessageClass = new com.intellinet.diameter.GroupedName("Message-Class", new MessageClassAVPBuilder());

    private static class UserEquipmentInfoValueAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserEquipmentInfoValue((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName UserEquipmentInfoValue = new com.intellinet.diameter.OctetStringName("User-Equipment-Info-Value", new UserEquipmentInfoValueAVPBuilder());

    private static class SDPMediaComponentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPMediaComponent((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SDPMediaComponent = new com.intellinet.diameter.GroupedName("SDP-Media-Component", new SDPMediaComponentAVPBuilder());

    private static class ChargedPartyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ChargedParty((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ChargedParty = new com.intellinet.diameter.UTF8StringName("Charged-Party", new ChargedPartyAVPBuilder());

    private static class AoCServiceObligatoryTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCServiceObligatoryType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AoCServiceObligatoryType = new com.intellinet.diameter.EnumeratedName("AoC-Service-Obligatory-Type", new AoCServiceObligatoryTypeAVPBuilder());

    private static class Ro3GPPNSAPIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPNSAPI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPNSAPI = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-NSAPI", new Ro3GPPNSAPIAVPBuilder());

    private static class ContentDispositionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContentDisposition((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ContentDisposition = new com.intellinet.diameter.UTF8StringName("Content-Disposition", new ContentDispositionAVPBuilder());

    private static class TotalNumberOfMessagesExplodedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TotalNumberOfMessagesExploded((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName TotalNumberOfMessagesExploded = new com.intellinet.diameter.Unsigned32Name("Total-Number-Of-Messages-Exploded", new TotalNumberOfMessagesExplodedAVPBuilder());

    private static class CCInputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCInputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCInputOctets = new com.intellinet.diameter.Unsigned64Name("CC-Input-Octets", new CCInputOctetsAVPBuilder());

    private static class PoCChangeTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCChangeTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName PoCChangeTime = new com.intellinet.diameter.TimeName("PoC-Change-Time", new PoCChangeTimeAVPBuilder());

    private static class AllocationRetentionPriorityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AllocationRetentionPriority((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AllocationRetentionPriority = new com.intellinet.diameter.GroupedName("Allocation-Retention-Priority", new AllocationRetentionPriorityAVPBuilder());

    private static class Ro3GPPGGSNMCCMNCAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPGGSNMCCMNC((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPGGSNMCCMNC = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-GGSN-MCC-MNC", new Ro3GPPGGSNMCCMNCAVPBuilder());

    private static class BearerServiceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new BearerService((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName BearerService = new com.intellinet.diameter.OctetStringName("Bearer-Service", new BearerServiceAVPBuilder());

    private static class UnitValueAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UnitValue((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UnitValue = new com.intellinet.diameter.GroupedName("Unit-Value", new UnitValueAVPBuilder());

    private static class DiagnosticsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Diagnostics((com.intellinet.diameter.Integer32Data)impl);
        }
    }

    public static final AttributeName Diagnostics = new com.intellinet.diameter.Integer32Name("Diagnostics", new DiagnosticsAVPBuilder());

    private static class TimeQuotaMechanismAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TimeQuotaMechanism((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TimeQuotaMechanism = new com.intellinet.diameter.GroupedName("Time-Quota-Mechanism", new TimeQuotaMechanismAVPBuilder());

    private static class ParticipantActionTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ParticipantActionType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ParticipantActionType = new com.intellinet.diameter.EnumeratedName("Participant-Action-Type", new ParticipantActionTypeAVPBuilder());

    private static class ServiceInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServiceInformation = new com.intellinet.diameter.GroupedName("Service-Information", new ServiceInformationAVPBuilder());

    private static class MediaInitiatorFlagAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MediaInitiatorFlag((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MediaInitiatorFlag = new com.intellinet.diameter.EnumeratedName("Media-Initiator-Flag", new MediaInitiatorFlagAVPBuilder());

    private static class BaseTimeIntervalAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new BaseTimeInterval((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName BaseTimeInterval = new com.intellinet.diameter.Unsigned32Name("Base-Time-Interval", new BaseTimeIntervalAVPBuilder());

    private static class MessageIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MessageID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName MessageID = new com.intellinet.diameter.UTF8StringName("Message-ID", new MessageIDAVPBuilder());

    private static class RequiredMBMSBearerCapabilitiesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequiredMBMSBearerCapabilities((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName RequiredMBMSBearerCapabilities = new com.intellinet.diameter.UTF8StringName("Required-MBMS-Bearer-Capabilities", new RequiredMBMSBearerCapabilitiesAVPBuilder());

    private static class CurrencyCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CurrencyCode((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CurrencyCode = new com.intellinet.diameter.Unsigned32Name("Currency-Code", new CurrencyCodeAVPBuilder());

    private static class RefundInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RefundInformation((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName RefundInformation = new com.intellinet.diameter.OctetStringName("Refund-Information", new RefundInformationAVPBuilder());

    private static class EnvelopeReportingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EnvelopeReporting((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName EnvelopeReporting = new com.intellinet.diameter.EnumeratedName("Envelope-Reporting", new EnvelopeReportingAVPBuilder());

    private static class TokenTextAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TokenText((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName TokenText = new com.intellinet.diameter.UTF8StringName("Token-Text", new TokenTextAVPBuilder());

    private static class PoCSessionInitiationTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCSessionInitiationType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PoCSessionInitiationType = new com.intellinet.diameter.EnumeratedName("PoC-Session-Initiation-Type", new PoCSessionInitiationTypeAVPBuilder());

    private static class LocationEstimateTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LocationEstimateType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LocationEstimateType = new com.intellinet.diameter.EnumeratedName("Location-Estimate-Type", new LocationEstimateTypeAVPBuilder());

    private static class Ro3GPPRATTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPRATType((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Ro3GPPRATType = new com.intellinet.diameter.OctetStringName("Ro-3GPP-RAT-Type", new Ro3GPPRATTypeAVPBuilder());

    private static class Ro3GPPCAMELChargingInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPCAMELChargingInfo((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Ro3GPPCAMELChargingInfo = new com.intellinet.diameter.OctetStringName("Ro-3GPP-CAMEL-Charging-Info", new Ro3GPPCAMELChargingInfoAVPBuilder());

    private static class GSUPoolIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GSUPoolIdentifier((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName GSUPoolIdentifier = new com.intellinet.diameter.Unsigned32Name("G-S-U-Pool-Identifier", new GSUPoolIdentifierAVPBuilder());

    private static class LocationEstimateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LocationEstimate((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName LocationEstimate = new com.intellinet.diameter.UTF8StringName("Location-Estimate", new LocationEstimateAVPBuilder());

    private static class AuxApplicInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AuxApplicInfo((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName AuxApplicInfo = new com.intellinet.diameter.UTF8StringName("Aux-Applic-Info", new AuxApplicInfoAVPBuilder());

    private static class MMSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MMSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MMSInformation = new com.intellinet.diameter.GroupedName("MMS-Information", new MMSInformationAVPBuilder());

    private static class MultipleServicesIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MultipleServicesIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MultipleServicesIndicator = new com.intellinet.diameter.EnumeratedName("Multiple-Services-Indicator", new MultipleServicesIndicatorAVPBuilder());

    private static class ContentLengthAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContentLength((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ContentLength = new com.intellinet.diameter.Unsigned32Name("Content-Length", new ContentLengthAVPBuilder());

    private static class LocalGWInsertedIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LocalGWInsertedIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LocalGWInsertedIndication = new com.intellinet.diameter.EnumeratedName("Local-GW-Inserted-Indication", new LocalGWInsertedIndicationAVPBuilder());

    private static class CCSubSessionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCSubSessionId((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCSubSessionId = new com.intellinet.diameter.Unsigned64Name("CC-Sub-Session-Id", new CCSubSessionIdAVPBuilder());

    private static class ReceivedTalkBurstVolumeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReceivedTalkBurstVolume((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ReceivedTalkBurstVolume = new com.intellinet.diameter.Unsigned32Name("Received-Talk-Burst-Volume", new ReceivedTalkBurstVolumeAVPBuilder());

    private static class AccountingOutputPacketsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingOutputPackets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingOutputPackets = new com.intellinet.diameter.Unsigned64Name("Accounting-Output-Packets", new AccountingOutputPacketsAVPBuilder());

    private static class TimeStampsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TimeStamps((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TimeStamps = new com.intellinet.diameter.GroupedName("Time-Stamps", new TimeStampsAVPBuilder());

    private static class ContentTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContentType((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ContentType = new com.intellinet.diameter.UTF8StringName("Content-Type", new ContentTypeAVPBuilder());

    private static class IncrementalCostAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IncrementalCost((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName IncrementalCost = new com.intellinet.diameter.GroupedName("Incremental-Cost", new IncrementalCostAVPBuilder());

    private static class Ro3GPPIMSIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPIMSI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPIMSI = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-IMSI", new Ro3GPPIMSIAVPBuilder());

    private static class DirectDebitingFailureHandlingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DirectDebitingFailureHandling((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName DirectDebitingFailureHandling = new com.intellinet.diameter.EnumeratedName("Direct-Debiting-Failure-Handling", new DirectDebitingFailureHandlingAVPBuilder());

    private static class TerminatingIOIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TerminatingIOI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName TerminatingIOI = new com.intellinet.diameter.UTF8StringName("Terminating-IOI", new TerminatingIOIAVPBuilder());

    private static class OutgoingTrunkGroupIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OutgoingTrunkGroupID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName OutgoingTrunkGroupID = new com.intellinet.diameter.UTF8StringName("Outgoing-Trunk-Group-ID", new OutgoingTrunkGroupIDAVPBuilder());

    private static class FlowsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Flows((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName Flows = new com.intellinet.diameter.GroupedName("Flows", new FlowsAVPBuilder());

    private static class AccessNetworkChargingIdentifierValueAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccessNetworkChargingIdentifierValue((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName AccessNetworkChargingIdentifierValue = new com.intellinet.diameter.OctetStringName("Access-Network-Charging-Identifier-Value", new AccessNetworkChargingIdentifierValueAVPBuilder());

    private static class ServiceSpecificDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceSpecificData((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ServiceSpecificData = new com.intellinet.diameter.UTF8StringName("Service-Specific-Data", new ServiceSpecificDataAVPBuilder());

    private static class IMEIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMEI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IMEI = new com.intellinet.diameter.UTF8StringName("IMEI", new IMEIAVPBuilder());

    private static class DeferredLocationEventTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DeferredLocationEventType((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName DeferredLocationEventType = new com.intellinet.diameter.UTF8StringName("Deferred-Location-Event-Type", new DeferredLocationEventTypeAVPBuilder());

    private static class OfflineChargingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OfflineCharging((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName OfflineCharging = new com.intellinet.diameter.GroupedName("Offline-Charging", new OfflineChargingAVPBuilder());

    private static class CGAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CGAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName CGAddress = new com.intellinet.diameter.AddressName("CG-Address", new CGAddressAVPBuilder());

    private static class LCSClientExternalIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSClientExternalID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName LCSClientExternalID = new com.intellinet.diameter.UTF8StringName("LCS-Client-External-ID", new LCSClientExternalIDAVPBuilder());

    private static class PoCSessionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCSessionId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName PoCSessionId = new com.intellinet.diameter.UTF8StringName("PoC-Session-Id", new PoCSessionIdAVPBuilder());

    private static class IMSCommunicationServiceIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSCommunicationServiceIdentifier((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IMSCommunicationServiceIdentifier = new com.intellinet.diameter.UTF8StringName("IMS-Communication-Service-Identifier", new IMSCommunicationServiceIdentifierAVPBuilder());

    private static class SubmissionTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubmissionTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName SubmissionTime = new com.intellinet.diameter.TimeName("Submission-Time", new SubmissionTimeAVPBuilder());

    private static class NumberOfParticipantsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfParticipants((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfParticipants = new com.intellinet.diameter.Unsigned32Name("Number-Of-Participants", new NumberOfParticipantsAVPBuilder());

    private static class OnlineChargingFlagAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OnlineChargingFlag((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName OnlineChargingFlag = new com.intellinet.diameter.EnumeratedName("Online-Charging-Flag", new OnlineChargingFlagAVPBuilder());

    private static class UserCSGInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserCSGInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UserCSGInformation = new com.intellinet.diameter.GroupedName("User-CSG-Information", new UserCSGInformationAVPBuilder());

    private static class ValidityTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ValidityTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ValidityTime = new com.intellinet.diameter.Unsigned32Name("Validity-Time", new ValidityTimeAVPBuilder());

    private static class DynamicAddressFlagAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DynamicAddressFlag((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName DynamicAddressFlag = new com.intellinet.diameter.EnumeratedName("Dynamic-Address-Flag", new DynamicAddressFlagAVPBuilder());

    private static class AFCorrelationInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AFCorrelationInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AFCorrelationInformation = new com.intellinet.diameter.GroupedName("AF-Correlation-Information", new AFCorrelationInformationAVPBuilder());

    private static class AccumulatedCostAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccumulatedCost((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AccumulatedCost = new com.intellinet.diameter.GroupedName("Accumulated-Cost", new AccumulatedCostAVPBuilder());

    private static class CCTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CCTime = new com.intellinet.diameter.Unsigned32Name("CC-Time", new CCTimeAVPBuilder());

    private static class TalkBurstTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TalkBurstTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName TalkBurstTime = new com.intellinet.diameter.Unsigned32Name("Talk-Burst-Time", new TalkBurstTimeAVPBuilder());

    private static class ChargingRuleBaseNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ChargingRuleBaseName((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ChargingRuleBaseName = new com.intellinet.diameter.OctetStringName("Charging-Rule-Base-Name", new ChargingRuleBaseNameAVPBuilder());

    private static class CostUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CostUnit((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CostUnit = new com.intellinet.diameter.UTF8StringName("Cost-Unit", new CostUnitAVPBuilder());

    private static class AoCCostInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCCostInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AoCCostInformation = new com.intellinet.diameter.GroupedName("AoC-Cost-Information", new AoCCostInformationAVPBuilder());

    private static class DeliveryStatusAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DeliveryStatus((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName DeliveryStatus = new com.intellinet.diameter.UTF8StringName("Delivery-Status", new DeliveryStatusAVPBuilder());

    private static class ServiceContextIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceContextId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ServiceContextId = new com.intellinet.diameter.UTF8StringName("Service-Context-Id", new ServiceContextIdAVPBuilder());

    private static class MandatoryCapabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MandatoryCapability((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MandatoryCapability = new com.intellinet.diameter.Unsigned32Name("Mandatory-Capability", new MandatoryCapabilityAVPBuilder());

    private static class TriggerTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TriggerType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TriggerType = new com.intellinet.diameter.EnumeratedName("Trigger-Type", new TriggerTypeAVPBuilder());

    private static class OutgoingSessionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OutgoingSessionId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName OutgoingSessionId = new com.intellinet.diameter.UTF8StringName("Outgoing-Session-Id", new OutgoingSessionIdAVPBuilder());

    private static class LCSNameStringAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSNameString((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName LCSNameString = new com.intellinet.diameter.UTF8StringName("LCS-Name-String", new LCSNameStringAVPBuilder());

    private static class CSGMembershipIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CSGMembershipIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CSGMembershipIndication = new com.intellinet.diameter.EnumeratedName("CSG-Membership-Indication", new CSGMembershipIndicationAVPBuilder());

    private static class OriginatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Originator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName Originator = new com.intellinet.diameter.EnumeratedName("Originator", new OriginatorAVPBuilder());

    private static class AssociatedURIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AssociatedURI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName AssociatedURI = new com.intellinet.diameter.UTF8StringName("Associated-URI", new AssociatedURIAVPBuilder());

    private static class TariffChangeUsageAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TariffChangeUsage((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TariffChangeUsage = new com.intellinet.diameter.EnumeratedName("Tariff-Change-Usage", new TariffChangeUsageAVPBuilder());

    private static class MMContentTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MMContentType((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MMContentType = new com.intellinet.diameter.GroupedName("MM-Content-Type", new MMContentTypeAVPBuilder());

    private static class MBMSUserServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MBMSUserServiceType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MBMSUserServiceType = new com.intellinet.diameter.EnumeratedName("MBMS-User-Service-Type", new MBMSUserServiceTypeAVPBuilder());

    private static class SupplementaryServiceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SupplementaryService((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SupplementaryService = new com.intellinet.diameter.GroupedName("Supplementary-Service", new SupplementaryServiceAVPBuilder());

    private static class AccountingInputPacketsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingInputPackets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingInputPackets = new com.intellinet.diameter.Unsigned64Name("Accounting-Input-Packets", new AccountingInputPacketsAVPBuilder());

    private static class NextTariffAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NextTariff((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName NextTariff = new com.intellinet.diameter.GroupedName("Next-Tariff", new NextTariffAVPBuilder());

    private static class ReportingReasonAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReportingReason((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ReportingReason = new com.intellinet.diameter.EnumeratedName("Reporting-Reason", new ReportingReasonAVPBuilder());

    private static class AccessNetworkInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccessNetworkInformation((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName AccessNetworkInformation = new com.intellinet.diameter.OctetStringName("Access-Network-Information", new AccessNetworkInformationAVPBuilder());

    private static class PDNConnectionIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDNConnectionID((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PDNConnectionID = new com.intellinet.diameter.Unsigned32Name("PDN-Connection-ID", new PDNConnectionIDAVPBuilder());

    private static class SMMessageTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMMessageType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SMMessageType = new com.intellinet.diameter.EnumeratedName("SM-Message-Type", new SMMessageTypeAVPBuilder());

    private static class SIPResponseTimestampFractionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPResponseTimestampFraction((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName SIPResponseTimestampFraction = new com.intellinet.diameter.Unsigned32Name("SIP-Response-Timestamp-Fraction", new SIPResponseTimestampFractionAVPBuilder());

    private static class MBMS2G3GIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MBMS2G3GIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MBMS2G3GIndicator = new com.intellinet.diameter.EnumeratedName("MBMS-2G-3G-Indicator", new MBMS2G3GIndicatorAVPBuilder());

    private static class ServerCapabilitiesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServerCapabilities((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServerCapabilities = new com.intellinet.diameter.GroupedName("Server-Capabilities", new ServerCapabilitiesAVPBuilder());

    private static class AuthorizedQoSAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AuthorizedQoS((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName AuthorizedQoS = new com.intellinet.diameter.UTF8StringName("Authorized-QoS", new AuthorizedQoSAVPBuilder());

    private static class SDPAnswerTimestampAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPAnswerTimestamp((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName SDPAnswerTimestamp = new com.intellinet.diameter.TimeName("SDP-Answer-Timestamp", new SDPAnswerTimestampAVPBuilder());

    private static class TimeUsageAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TimeUsage((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName TimeUsage = new com.intellinet.diameter.TimeName("Time-Usage", new TimeUsageAVPBuilder());

    private static class ReplyApplicIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReplyApplicID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ReplyApplicID = new com.intellinet.diameter.UTF8StringName("Reply-Applic-ID", new ReplyApplicIDAVPBuilder());

    private static class OriginatorReceivedAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginatorReceivedAddress((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName OriginatorReceivedAddress = new com.intellinet.diameter.GroupedName("Originator-Received-Address", new OriginatorReceivedAddressAVPBuilder());

    private static class InterfaceIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new InterfaceId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName InterfaceId = new com.intellinet.diameter.UTF8StringName("Interface-Id", new InterfaceIdAVPBuilder());

    private static class LowBalanceIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LowBalanceIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LowBalanceIndication = new com.intellinet.diameter.EnumeratedName("Low-Balance-Indication", new LowBalanceIndicationAVPBuilder());

    private static class SubscriptionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionId((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SubscriptionId = new com.intellinet.diameter.GroupedName("Subscription-Id", new SubscriptionIdAVPBuilder());

    private static class TrunkGroupIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TrunkGroupID((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TrunkGroupID = new com.intellinet.diameter.GroupedName("Trunk-Group-ID", new TrunkGroupIDAVPBuilder());

    private static class CUGInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CUGInformation((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CUGInformation = new com.intellinet.diameter.OctetStringName("CUG-Information", new CUGInformationAVPBuilder());

    private static class ReadReplyReportRequestedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReadReplyReportRequested((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ReadReplyReportRequested = new com.intellinet.diameter.EnumeratedName("Read-Reply-Report-Requested", new ReadReplyReportRequestedAVPBuilder());

    private static class PoCControllingAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCControllingAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName PoCControllingAddress = new com.intellinet.diameter.UTF8StringName("PoC-Controlling-Address", new PoCControllingAddressAVPBuilder());

    private static class SMSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SMSInformation = new com.intellinet.diameter.GroupedName("SMS-Information", new SMSInformationAVPBuilder());

    private static class ChangeTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ChangeTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName ChangeTime = new com.intellinet.diameter.TimeName("Change-Time", new ChangeTimeAVPBuilder());

    private static class DomainNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DomainName((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName DomainName = new com.intellinet.diameter.UTF8StringName("Domain-Name", new DomainNameAVPBuilder());

    private static class LCSAPNAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSAPN((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName LCSAPN = new com.intellinet.diameter.UTF8StringName("LCS-APN", new LCSAPNAVPBuilder());

    private static class PoCChangeConditionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCChangeCondition((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PoCChangeCondition = new com.intellinet.diameter.EnumeratedName("PoC-Change-Condition", new PoCChangeConditionAVPBuilder());

    private static class Ro3GPPUserLocationInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPUserLocationInfo((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Ro3GPPUserLocationInfo = new com.intellinet.diameter.OctetStringName("Ro-3GPP-User-Location-Info", new Ro3GPPUserLocationInfoAVPBuilder());

    private static class TMGIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TMGI((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TMGI = new com.intellinet.diameter.OctetStringName("TMGI", new TMGIAVPBuilder());

    private static class MBMSSessionIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MBMSSessionIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName MBMSSessionIdentity = new com.intellinet.diameter.OctetStringName("MBMS-Session-Identity", new MBMSSessionIdentityAVPBuilder());

    private static class NumberOfMessagesSentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfMessagesSent((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfMessagesSent = new com.intellinet.diameter.Unsigned32Name("Number-Of-Messages-Sent", new NumberOfMessagesSentAVPBuilder());

    private static class RemainingBalanceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RemainingBalance((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RemainingBalance = new com.intellinet.diameter.GroupedName("Remaining-Balance", new RemainingBalanceAVPBuilder());

    private static class AssociatedPartyAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AssociatedPartyAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName AssociatedPartyAddress = new com.intellinet.diameter.UTF8StringName("Associated-Party-Address", new AssociatedPartyAddressAVPBuilder());

    private static class IMInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName IMInformation = new com.intellinet.diameter.GroupedName("IM-Information", new IMInformationAVPBuilder());

    private static class InterfacePortAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new InterfacePort((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName InterfacePort = new com.intellinet.diameter.UTF8StringName("Interface-Port", new InterfacePortAVPBuilder());

    private static class SMUserDataHeaderAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMUserDataHeader((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SMUserDataHeader = new com.intellinet.diameter.OctetStringName("SM-User-Data-Header", new SMUserDataHeaderAVPBuilder());

    private static class OriginatorSCCPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginatorSCCPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName OriginatorSCCPAddress = new com.intellinet.diameter.AddressName("Originator-SCCP-Address", new OriginatorSCCPAddressAVPBuilder());

    private static class UsedServiceUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UsedServiceUnit((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UsedServiceUnit = new com.intellinet.diameter.GroupedName("Used-Service-Unit", new UsedServiceUnitAVPBuilder());

    private static class ServedPartyIPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServedPartyIPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName ServedPartyIPAddress = new com.intellinet.diameter.AddressName("Served-Party-IP-Address", new ServedPartyIPAddressAVPBuilder());

    private static class IMSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName IMSInformation = new com.intellinet.diameter.GroupedName("IMS-Information", new IMSInformationAVPBuilder());

    private static class AoCFormatAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCFormat((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AoCFormat = new com.intellinet.diameter.EnumeratedName("AoC-Format", new AoCFormatAVPBuilder());

    private static class DRMContentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DRMContent((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName DRMContent = new com.intellinet.diameter.EnumeratedName("DRM-Content", new DRMContentAVPBuilder());

    private static class PositioningDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PositioningData((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName PositioningData = new com.intellinet.diameter.UTF8StringName("Positioning-Data", new PositioningDataAVPBuilder());

    private static class CNIPMulticastDistributionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CNIPMulticastDistribution((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CNIPMulticastDistribution = new com.intellinet.diameter.EnumeratedName("CN-IP-Multicast-Distribution", new CNIPMulticastDistributionAVPBuilder());

    private static class IMSAddressTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSAddressType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName IMSAddressType = new com.intellinet.diameter.EnumeratedName("IMS-Address-Type", new IMSAddressTypeAVPBuilder());

    private static class RedirectServerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RedirectServer((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RedirectServer = new com.intellinet.diameter.GroupedName("Redirect-Server", new RedirectServerAVPBuilder());

    private static class InterOperatorIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new InterOperatorIdentifier((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName InterOperatorIdentifier = new com.intellinet.diameter.GroupedName("Inter-Operator-Identifier", new InterOperatorIdentifierAVPBuilder());

    private static class NumberOfTalkBurstsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfTalkBursts((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfTalkBursts = new com.intellinet.diameter.Unsigned32Name("Number-Of-Talk-Bursts", new NumberOfTalkBurstsAVPBuilder());

    private static class GuaranteedBitrateULAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GuaranteedBitrateUL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName GuaranteedBitrateUL = new com.intellinet.diameter.Unsigned32Name("Guaranteed-Bitrate-UL", new GuaranteedBitrateULAVPBuilder());

    private static class NumberOfReceivedTalkBurstsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfReceivedTalkBursts((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfReceivedTalkBursts = new com.intellinet.diameter.Unsigned32Name("Number-Of-Received-Talk-Bursts", new NumberOfReceivedTalkBurstsAVPBuilder());

    private static class SGWChangeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SGWChange((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SGWChange = new com.intellinet.diameter.EnumeratedName("SGW-Change", new SGWChangeAVPBuilder());

    private static class RecipientReceivedAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RecipientReceivedAddress((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RecipientReceivedAddress = new com.intellinet.diameter.GroupedName("Recipient-Received-Address", new RecipientReceivedAddressAVPBuilder());

    private static class SIPRequestTimestampFractionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPRequestTimestampFraction((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName SIPRequestTimestampFraction = new com.intellinet.diameter.Unsigned32Name("SIP-Request-Timestamp-Fraction", new SIPRequestTimestampFractionAVPBuilder());

    private static class SubscriptionIdDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionIdData((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SubscriptionIdData = new com.intellinet.diameter.UTF8StringName("Subscription-Id-Data", new SubscriptionIdDataAVPBuilder());

    private static class NumberOfMessagesSuccessfullyExplodedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfMessagesSuccessfullyExploded((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfMessagesSuccessfullyExploded = new com.intellinet.diameter.Unsigned32Name("Number-Of-Messages-Successfully-Exploded", new NumberOfMessagesSuccessfullyExplodedAVPBuilder());

    private static class SessionPriorityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SessionPriority((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SessionPriority = new com.intellinet.diameter.EnumeratedName("Session-Priority", new SessionPriorityAVPBuilder());

    private static class CostInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CostInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CostInformation = new com.intellinet.diameter.GroupedName("Cost-Information", new CostInformationAVPBuilder());

    private static class PSFreeFormatDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PSFreeFormatData((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName PSFreeFormatData = new com.intellinet.diameter.OctetStringName("PS-Free-Format-Data", new PSFreeFormatDataAVPBuilder());

    private static class ApplicationServerInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ApplicationServerInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ApplicationServerInformation = new com.intellinet.diameter.GroupedName("Application-Server-Information", new ApplicationServerInformationAVPBuilder());

    private static class RedirectAddressTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RedirectAddressType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RedirectAddressType = new com.intellinet.diameter.EnumeratedName("Redirect-Address-Type", new RedirectAddressTypeAVPBuilder());

    private static class Ro3GPPChargingCharacteristicsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPChargingCharacteristics((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPChargingCharacteristics = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-Charging-Characteristics", new Ro3GPPChargingCharacteristicsAVPBuilder());

    private static class CCCorrelationIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCCorrelationId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CCCorrelationId = new com.intellinet.diameter.OctetStringName("CC-Correlation-Id", new CCCorrelationIdAVPBuilder());

    private static class IMSEventAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSEvent((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IMSEvent = new com.intellinet.diameter.UTF8StringName("IMS-Event", new IMSEventAVPBuilder());

    private static class PriorityLevelAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PriorityLevel((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PriorityLevel = new com.intellinet.diameter.Unsigned32Name("Priority-Level", new PriorityLevelAVPBuilder());

    private static class PreemptionCapabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PreemptionCapability((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PreemptionCapability = new com.intellinet.diameter.EnumeratedName("Pre-emption-Capability", new PreemptionCapabilityAVPBuilder());

    private static class CCRequestTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCRequestType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CCRequestType = new com.intellinet.diameter.EnumeratedName("CC-Request-Type", new CCRequestTypeAVPBuilder());

    private static class ServiceIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ServiceId = new com.intellinet.diameter.UTF8StringName("Service-Id", new ServiceIdAVPBuilder());

    private static class SMStatusAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMStatus((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SMStatus = new com.intellinet.diameter.OctetStringName("SM-Status", new SMStatusAVPBuilder());

    private static class ServiceSpecificTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceSpecificType((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ServiceSpecificType = new com.intellinet.diameter.Unsigned32Name("Service-Specific-Type", new ServiceSpecificTypeAVPBuilder());

    private static class ServingNodeTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServingNodeType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ServingNodeType = new com.intellinet.diameter.EnumeratedName("Serving-Node-Type", new ServingNodeTypeAVPBuilder());

    private static class DeliveryReportRequestedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DeliveryReportRequested((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName DeliveryReportRequested = new com.intellinet.diameter.EnumeratedName("Delivery-Report-Requested", new DeliveryReportRequestedAVPBuilder());

    private static class SMServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMServiceType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SMServiceType = new com.intellinet.diameter.EnumeratedName("SM-Service-Type", new SMServiceTypeAVPBuilder());

    private static class ParticipantsInvolvedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ParticipantsInvolved((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ParticipantsInvolved = new com.intellinet.diameter.UTF8StringName("Participants-Involved", new ParticipantsInvolvedAVPBuilder());

    private static class ApplicationServerIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ApplicationServerID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ApplicationServerID = new com.intellinet.diameter.UTF8StringName("Application-Server-ID", new ApplicationServerIDAVPBuilder());

    private static class AddresseeTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AddresseeType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AddresseeType = new com.intellinet.diameter.EnumeratedName("Addressee-Type", new AddresseeTypeAVPBuilder());

    private static class ApplicationSessionIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ApplicationSessionID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ApplicationSessionID = new com.intellinet.diameter.UTF8StringName("Application-Session-ID", new ApplicationSessionIDAVPBuilder());

    private static class MBMSServiceAreaAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MBMSServiceArea((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName MBMSServiceArea = new com.intellinet.diameter.OctetStringName("MBMS-Service-Area", new MBMSServiceAreaAVPBuilder());

    private static class RatingGroupAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RatingGroup((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName RatingGroup = new com.intellinet.diameter.Unsigned32Name("Rating-Group", new RatingGroupAVPBuilder());

    private static class Ro3GPPSelectionModeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPSelectionMode((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPSelectionMode = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-Selection-Mode", new Ro3GPPSelectionModeAVPBuilder());

    private static class DataCodingSchemeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DataCodingScheme((com.intellinet.diameter.Integer32Data)impl);
        }
    }

    public static final AttributeName DataCodingScheme = new com.intellinet.diameter.Integer32Name("Data-Coding-Scheme", new DataCodingSchemeAVPBuilder());

    private static class NodeFunctionalityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NodeFunctionality((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName NodeFunctionality = new com.intellinet.diameter.EnumeratedName("Node-Functionality", new NodeFunctionalityAVPBuilder());

    private static class CSGAccessModeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CSGAccessMode((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CSGAccessMode = new com.intellinet.diameter.EnumeratedName("CSG-Access-Mode", new CSGAccessModeAVPBuilder());

    private static class PDGAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDGAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName PDGAddress = new com.intellinet.diameter.AddressName("PDG-Address", new PDGAddressAVPBuilder());

    private static class WLANRadioContainerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WLANRadioContainer((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName WLANRadioContainer = new com.intellinet.diameter.GroupedName("WLAN-Radio-Container", new WLANRadioContainerAVPBuilder());

    private static class ContentSizeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContentSize((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ContentSize = new com.intellinet.diameter.Unsigned32Name("Content-Size", new ContentSizeAVPBuilder());

    private static class PreferredAoCCurrencyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PreferredAoCCurrency((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PreferredAoCCurrency = new com.intellinet.diameter.Unsigned32Name("Preferred-AoC-Currency", new PreferredAoCCurrencyAVPBuilder());

    private static class MediaComponentNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MediaComponentNumber((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MediaComponentNumber = new com.intellinet.diameter.Unsigned32Name("Media-Component-Number", new MediaComponentNumberAVPBuilder());

    private static class PreemptionVulnerabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PreemptionVulnerability((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PreemptionVulnerability = new com.intellinet.diameter.EnumeratedName("Pre-emption-Vulnerability", new PreemptionVulnerabilityAVPBuilder());

    private static class RateElementAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RateElement((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RateElement = new com.intellinet.diameter.GroupedName("Rate-Element", new RateElementAVPBuilder());

    private static class APNAggregateMaxBitrateDLAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new APNAggregateMaxBitrateDL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName APNAggregateMaxBitrateDL = new com.intellinet.diameter.Unsigned32Name("APN-Aggregate-Max-Bitrate-DL", new APNAggregateMaxBitrateDLAVPBuilder());

    private static class DestinationInterfaceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DestinationInterface((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName DestinationInterface = new com.intellinet.diameter.GroupedName("Destination-Interface", new DestinationInterfaceAVPBuilder());

    private static class TariffXMLAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TariffXML((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName TariffXML = new com.intellinet.diameter.UTF8StringName("Tariff-XML", new TariffXMLAVPBuilder());

    private static class TriggerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Trigger((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName Trigger = new com.intellinet.diameter.GroupedName("Trigger", new TriggerAVPBuilder());

    private static class ServiceModeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceMode((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ServiceMode = new com.intellinet.diameter.Unsigned32Name("Service-Mode", new ServiceModeAVPBuilder());

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

    private static class ContentIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContentID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ContentID = new com.intellinet.diameter.UTF8StringName("Content-ID", new ContentIDAVPBuilder());

    private static class AccountingOutputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingOutputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingOutputOctets = new com.intellinet.diameter.Unsigned64Name("Accounting-Output-Octets", new AccountingOutputOctetsAVPBuilder());

    private static class LCSClientNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSClientName((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName LCSClientName = new com.intellinet.diameter.GroupedName("LCS-Client-Name", new LCSClientNameAVPBuilder());

    private static class APNAggregateMaxBitrateULAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new APNAggregateMaxBitrateUL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName APNAggregateMaxBitrateUL = new com.intellinet.diameter.Unsigned32Name("APN-Aggregate-Max-Bitrate-UL", new APNAggregateMaxBitrateULAVPBuilder());

    private static class CurrentTariffAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CurrentTariff((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CurrentTariff = new com.intellinet.diameter.GroupedName("Current-Tariff", new CurrentTariffAVPBuilder());

    private static class AoCServiceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCService((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AoCService = new com.intellinet.diameter.GroupedName("AoC-Service", new AoCServiceAVPBuilder());

    private static class NumberOfMessagesSuccessfullySentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfMessagesSuccessfullySent((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfMessagesSuccessfullySent = new com.intellinet.diameter.Unsigned32Name("Number-Of-Messages-Successfully-Sent", new NumberOfMessagesSuccessfullySentAVPBuilder());

    private static class SGWAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SGWAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName SGWAddress = new com.intellinet.diameter.AddressName("SGW-Address", new SGWAddressAVPBuilder());

    private static class SGSNAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SGSNAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName SGSNAddress = new com.intellinet.diameter.AddressName("SGSN-Address", new SGSNAddressAVPBuilder());

    private static class Ro3GPPSGSNMCCMNCAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPSGSNMCCMNC((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPPSGSNMCCMNC = new com.intellinet.diameter.UTF8StringName("Ro-3GPP-SGSN-MCC-MNC", new Ro3GPPSGSNMCCMNCAVPBuilder());

    private static class VolumeQuotaThresholdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VolumeQuotaThreshold((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName VolumeQuotaThreshold = new com.intellinet.diameter.Unsigned32Name("Volume-Quota-Threshold", new VolumeQuotaThresholdAVPBuilder());

    private static class MessageBodyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MessageBody((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MessageBody = new com.intellinet.diameter.GroupedName("Message-Body", new MessageBodyAVPBuilder());

    private static class ReasonCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReasonCode((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ReasonCode = new com.intellinet.diameter.EnumeratedName("Reason-Code", new ReasonCodeAVPBuilder());

    private static class PriorityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Priority((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName Priority = new com.intellinet.diameter.EnumeratedName("Priority", new PriorityAVPBuilder());

    private static class EventChargingTimeStampAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EventChargingTimeStamp((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName EventChargingTimeStamp = new com.intellinet.diameter.TimeName("Event-Charging-TimeStamp", new EventChargingTimeStampAVPBuilder());

    private static class StartTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new StartTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName StartTime = new com.intellinet.diameter.TimeName("Start-Time", new StartTimeAVPBuilder());

    private static class EnvelopeEndTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EnvelopeEndTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName EnvelopeEndTime = new com.intellinet.diameter.TimeName("Envelope-End-Time", new EnvelopeEndTimeAVPBuilder());

    private static class GuaranteedBitrateDLAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GuaranteedBitrateDL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName GuaranteedBitrateDL = new com.intellinet.diameter.Unsigned32Name("Guaranteed-Bitrate-DL", new GuaranteedBitrateDLAVPBuilder());

    private static class WLANTechnologyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WLANTechnology((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName WLANTechnology = new com.intellinet.diameter.Unsigned32Name("WLAN-Technology", new WLANTechnologyAVPBuilder());

    private static class ClientAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ClientAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName ClientAddress = new com.intellinet.diameter.AddressName("Client-Address", new ClientAddressAVPBuilder());

    private static class UserSessionIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserSessionID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName UserSessionID = new com.intellinet.diameter.UTF8StringName("User-Session-ID", new UserSessionIDAVPBuilder());

    private static class ServiceIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceIdentifier((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ServiceIdentifier = new com.intellinet.diameter.Unsigned32Name("Service-Identifier", new ServiceIdentifierAVPBuilder());

    private static class SMSCAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMSCAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName SMSCAddress = new com.intellinet.diameter.AddressName("SMSC-Address", new SMSCAddressAVPBuilder());

    private static class SDPTimeStampsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SDPTimeStamps((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SDPTimeStamps = new com.intellinet.diameter.GroupedName("SDP-TimeStamps", new SDPTimeStampsAVPBuilder());

    private static class SMSNodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SMSNode((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SMSNode = new com.intellinet.diameter.EnumeratedName("SMS-Node", new SMSNodeAVPBuilder());

    private static class ServerNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServerName((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ServerName = new com.intellinet.diameter.UTF8StringName("Server-Name", new ServerNameAVPBuilder());

    private static class CCServiceSpecificUnitsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCServiceSpecificUnits((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName CCServiceSpecificUnits = new com.intellinet.diameter.Unsigned64Name("CC-Service-Specific-Units", new CCServiceSpecificUnitsAVPBuilder());

    private static class OriginatingIOIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginatingIOI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName OriginatingIOI = new com.intellinet.diameter.UTF8StringName("Originating-IOI", new OriginatingIOIAVPBuilder());

    private static class AdditionalTypeInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AdditionalTypeInformation((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName AdditionalTypeInformation = new com.intellinet.diameter.UTF8StringName("Additional-Type-Information", new AdditionalTypeInformationAVPBuilder());

    private static class ReceivedTalkBurstTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReceivedTalkBurstTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ReceivedTalkBurstTime = new com.intellinet.diameter.Unsigned32Name("Received-Talk-Burst-Time", new ReceivedTalkBurstTimeAVPBuilder());

    private static class TariffInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TariffInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TariffInformation = new com.intellinet.diameter.GroupedName("Tariff-Information", new TariffInformationAVPBuilder());

    private static class RequestedPartyAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequestedPartyAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName RequestedPartyAddress = new com.intellinet.diameter.UTF8StringName("Requested-Party-Address", new RequestedPartyAddressAVPBuilder());

    private static class QuotaConsumptionTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new QuotaConsumptionTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName QuotaConsumptionTime = new com.intellinet.diameter.Unsigned32Name("Quota-Consumption-Time", new QuotaConsumptionTimeAVPBuilder());

    private static class NumberPortabilityRoutingInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberPortabilityRoutingInformation((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName NumberPortabilityRoutingInformation = new com.intellinet.diameter.UTF8StringName("Number-Portability-Routing-Information", new NumberPortabilityRoutingInformationAVPBuilder());

    private static class Ro3GPP2BSIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPP2BSID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName Ro3GPP2BSID = new com.intellinet.diameter.UTF8StringName("Ro-3GPP2-BSID", new Ro3GPP2BSIDAVPBuilder());

    private static class MSISDNAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MSISDN((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName MSISDN = new com.intellinet.diameter.OctetStringName("MSISDN", new MSISDNAVPBuilder());

    private static class PoCInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName PoCInformation = new com.intellinet.diameter.GroupedName("PoC-Information", new PoCInformationAVPBuilder());

    private static class ExponentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Exponent((com.intellinet.diameter.Integer32Data)impl);
        }
    }

    public static final AttributeName Exponent = new com.intellinet.diameter.Integer32Name("Exponent", new ExponentAVPBuilder());

    private static class MaxRequestedBandwidthULAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MaxRequestedBandwidthUL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MaxRequestedBandwidthUL = new com.intellinet.diameter.Unsigned32Name("Max-Requested-Bandwidth-UL", new MaxRequestedBandwidthULAVPBuilder());

    private static class InitialIMSChargingIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new InitialIMSChargingIdentifier((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName InitialIMSChargingIdentifier = new com.intellinet.diameter.UTF8StringName("Initial-IMS-Charging-Identifier", new InitialIMSChargingIdentifierAVPBuilder());

    private static class TranscoderInsertedIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TranscoderInsertedIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TranscoderInsertedIndication = new com.intellinet.diameter.EnumeratedName("Transcoder-Inserted-Indication", new TranscoderInsertedIndicationAVPBuilder());

    private static class MaxRequestedBandwidthDLAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MaxRequestedBandwidthDL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MaxRequestedBandwidthDL = new com.intellinet.diameter.Unsigned32Name("Max-Requested-Bandwidth-DL", new MaxRequestedBandwidthDLAVPBuilder());

    private static class AoCInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AoCInformation = new com.intellinet.diameter.GroupedName("AoC-Information", new AoCInformationAVPBuilder());

    private static class ApplicationProvidedCalledPartyAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ApplicationProvidedCalledPartyAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ApplicationProvidedCalledPartyAddress = new com.intellinet.diameter.UTF8StringName("Application-Provided-Called-Party-Address", new ApplicationProvidedCalledPartyAddressAVPBuilder());

    private static class ServiceDataContainerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceDataContainer((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServiceDataContainer = new com.intellinet.diameter.GroupedName("Service-Data-Container", new ServiceDataContainerAVPBuilder());

    private static class MessageTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MessageType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MessageType = new com.intellinet.diameter.EnumeratedName("Message-Type", new MessageTypeAVPBuilder());

    private static class PoCServerRoleAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCServerRole((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PoCServerRole = new com.intellinet.diameter.EnumeratedName("PoC-Server-Role", new PoCServerRoleAVPBuilder());

    private static class Ro3GPPMSTimeZoneAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Ro3GPPMSTimeZone((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Ro3GPPMSTimeZone = new com.intellinet.diameter.OctetStringName("Ro-3GPP-MS-TimeZone", new Ro3GPPMSTimeZoneAVPBuilder());

    private static class RequestedServiceUnitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequestedServiceUnit((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RequestedServiceUnit = new com.intellinet.diameter.GroupedName("Requested-Service-Unit", new RequestedServiceUnitAVPBuilder());

    private static class FlowNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FlowNumber((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FlowNumber = new com.intellinet.diameter.Unsigned32Name("Flow-Number", new FlowNumberAVPBuilder());

    private static class RedirectServerAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RedirectServerAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName RedirectServerAddress = new com.intellinet.diameter.UTF8StringName("Redirect-Server-Address", new RedirectServerAddressAVPBuilder());

    private static class ApplicIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ApplicID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ApplicID = new com.intellinet.diameter.UTF8StringName("Applic-ID", new ApplicIDAVPBuilder());

    private static class LCSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName LCSInformation = new com.intellinet.diameter.GroupedName("LCS-Information", new LCSInformationAVPBuilder());

    private static class ServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceType((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ServiceType = new com.intellinet.diameter.Unsigned32Name("Service-Type", new ServiceTypeAVPBuilder());

    private static class RecipientInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RecipientInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RecipientInfo = new com.intellinet.diameter.GroupedName("Recipient-Info", new RecipientInfoAVPBuilder());

    private static class CallingPartyAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CallingPartyAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CallingPartyAddress = new com.intellinet.diameter.UTF8StringName("Calling-Party-Address", new CallingPartyAddressAVPBuilder());

    private static class CalledPartyAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CalledPartyAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CalledPartyAddress = new com.intellinet.diameter.UTF8StringName("Called-Party-Address", new CalledPartyAddressAVPBuilder());

    private static class LocationTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LocationType((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName LocationType = new com.intellinet.diameter.GroupedName("Location-Type", new LocationTypeAVPBuilder());

    private static class SubscriptionIdTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionIdType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SubscriptionIdType = new com.intellinet.diameter.EnumeratedName("Subscription-Id-Type", new SubscriptionIdTypeAVPBuilder());

    private static class AccountingInputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingInputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingInputOctets = new com.intellinet.diameter.Unsigned64Name("Accounting-Input-Octets", new AccountingInputOctetsAVPBuilder());

    private static class ValueDigitsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ValueDigits((com.intellinet.diameter.Integer64Data)impl);
        }
    }

    public static final AttributeName ValueDigits = new com.intellinet.diameter.Integer64Name("Value-Digits", new ValueDigitsAVPBuilder());

    private static class PDPContextTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDPContextType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PDPContextType = new com.intellinet.diameter.EnumeratedName("PDP-Context-Type", new PDPContextTypeAVPBuilder());

    private static class RecipientSCCPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RecipientSCCPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName RecipientSCCPAddress = new com.intellinet.diameter.AddressName("Recipient-SCCP-Address", new RecipientSCCPAddressAVPBuilder());

    private static class CarrierSelectRoutingInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CarrierSelectRoutingInformation((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CarrierSelectRoutingInformation = new com.intellinet.diameter.UTF8StringName("Carrier-Select-Routing-Information", new CarrierSelectRoutingInformationAVPBuilder());

    private static class CCSessionFailoverAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CCSessionFailover((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CCSessionFailover = new com.intellinet.diameter.EnumeratedName("CC-Session-Failover", new CCSessionFailoverAVPBuilder());

    private static class PoCUserRoleinfoUnitsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PoCUserRoleinfoUnits((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PoCUserRoleinfoUnits = new com.intellinet.diameter.EnumeratedName("PoC-User-Role-info-Units", new PoCUserRoleinfoUnitsAVPBuilder());

    private static class CSGIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CSGId((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CSGId = new com.intellinet.diameter.Unsigned32Name("CSG-Id", new CSGIdAVPBuilder());

    private static class MediaInitiatorPartyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MediaInitiatorParty((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName MediaInitiatorParty = new com.intellinet.diameter.UTF8StringName("Media-Initiator-Party", new MediaInitiatorPartyAVPBuilder());

    private static class NodeIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NodeId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName NodeId = new com.intellinet.diameter.UTF8StringName("Node-Id", new NodeIdAVPBuilder());

    private static class ServiceSpecificInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceSpecificInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServiceSpecificInfo = new com.intellinet.diameter.GroupedName("Service-Specific-Info", new ServiceSpecificInfoAVPBuilder());

    private static class RAIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RAI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName RAI = new com.intellinet.diameter.UTF8StringName("RAI", new RAIAVPBuilder());

    private static class AoCRequestTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AoCRequestType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AoCRequestType = new com.intellinet.diameter.EnumeratedName("AoC-Request-Type", new AoCRequestTypeAVPBuilder());

    private static class ParticipantGroupAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ParticipantGroup((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ParticipantGroup = new com.intellinet.diameter.GroupedName("Participant-Group", new ParticipantGroupAVPBuilder());

    private static class RestrictionFilterRuleAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RestrictionFilterRule((com.intellinet.diameter.IPFilterRuleData)impl);
        }
    }

    public static final AttributeName RestrictionFilterRule = new com.intellinet.diameter.IPFilterRuleName("Restriction-Filter-Rule", new RestrictionFilterRuleAVPBuilder());

    private static class LCSRequestorIDStringAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSRequestorIDString((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName LCSRequestorIDString = new com.intellinet.diameter.UTF8StringName("LCS-Requestor-ID-String", new LCSRequestorIDStringAVPBuilder());

    private static class DCDInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DCDInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName DCDInformation = new com.intellinet.diameter.GroupedName("DCD-Information", new DCDInformationAVPBuilder());
}

