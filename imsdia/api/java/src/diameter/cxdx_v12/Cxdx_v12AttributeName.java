package diameter.cxdx_v12;

import com.intellinet.diameter.*;

/**
 * This class defines singleton AttributeName instances for all attributes in <i><b>cxdx_v12</b></i>.
 */
public abstract class Cxdx_v12AttributeName {

    private static class PrimaryChargingCollectionFunctionNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PrimaryChargingCollectionFunctionName((com.intellinet.diameter.URIData)impl);
        }
    }

    public static final AttributeName PrimaryChargingCollectionFunctionName = new com.intellinet.diameter.URIName("Primary-Charging-Collection-Function-Name", new PrimaryChargingCollectionFunctionNameAVPBuilder());

    private static class SupportedFeaturesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SupportedFeatures((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SupportedFeatures = new com.intellinet.diameter.GroupedName("Supported-Features", new SupportedFeaturesAVPBuilder());

    private static class FramedIPv6PrefixAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPv6Prefix((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedIPv6Prefix = new com.intellinet.diameter.OctetStringName("Framed-IPv6-Prefix", new FramedIPv6PrefixAVPBuilder());

    private static class MandatoryCapabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MandatoryCapability((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MandatoryCapability = new com.intellinet.diameter.Unsigned32Name("Mandatory-Capability", new MandatoryCapabilityAVPBuilder());

    private static class SIPNumberAuthItemsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPNumberAuthItems((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName SIPNumberAuthItems = new com.intellinet.diameter.Unsigned32Name("SIP-Number-Auth-Items", new SIPNumberAuthItemsAVPBuilder());

    private static class ConfidentialityKeyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ConfidentialityKey((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ConfidentialityKey = new com.intellinet.diameter.OctetStringName("Confidentiality-Key", new ConfidentialityKeyAVPBuilder());

    private static class FeatureListIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FeatureListID((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FeatureListID = new com.intellinet.diameter.Unsigned32Name("Feature-List-ID", new FeatureListIDAVPBuilder());

    private static class SIPItemNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPItemNumber((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName SIPItemNumber = new com.intellinet.diameter.Unsigned32Name("SIP-Item-Number", new SIPItemNumberAVPBuilder());

    private static class ServerAssignmentTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServerAssignmentType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ServerAssignmentType = new com.intellinet.diameter.EnumeratedName("Server-Assignment-Type", new ServerAssignmentTypeAVPBuilder());

    private static class UserDataAlreadyAvailableAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserDataAlreadyAvailable((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName UserDataAlreadyAvailable = new com.intellinet.diameter.EnumeratedName("User-Data-Already-Available", new UserDataAlreadyAvailableAVPBuilder());

    private static class SIPAuthenticationSchemeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPAuthenticationScheme((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SIPAuthenticationScheme = new com.intellinet.diameter.UTF8StringName("SIP-Authentication-Scheme", new SIPAuthenticationSchemeAVPBuilder());

    private static class PublicIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PublicIdentity((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName PublicIdentity = new com.intellinet.diameter.UTF8StringName("Public-Identity", new PublicIdentityAVPBuilder());

    private static class ReasonCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReasonCode((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ReasonCode = new com.intellinet.diameter.EnumeratedName("Reason-Code", new ReasonCodeAVPBuilder());

    private static class IntegrityKeyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IntegrityKey((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName IntegrityKey = new com.intellinet.diameter.OctetStringName("Integrity-Key", new IntegrityKeyAVPBuilder());

    private static class AssociatedIdentitiesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AssociatedIdentities((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AssociatedIdentities = new com.intellinet.diameter.GroupedName("Associated-Identities", new AssociatedIdentitiesAVPBuilder());

    private static class CallIDSIPHeaderAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CallIDSIPHeader((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CallIDSIPHeader = new com.intellinet.diameter.OctetStringName("Call-ID-SIP-Header", new CallIDSIPHeaderAVPBuilder());

    private static class RecordRouteAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RecordRoute((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName RecordRoute = new com.intellinet.diameter.OctetStringName("Record-Route", new RecordRouteAVPBuilder());

    private static class DeregistrationReasonAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DeregistrationReason((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName DeregistrationReason = new com.intellinet.diameter.GroupedName("Deregistration-Reason", new DeregistrationReasonAVPBuilder());

    private static class ServerCapabilitiesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServerCapabilities((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServerCapabilities = new com.intellinet.diameter.GroupedName("Server-Capabilities", new ServerCapabilitiesAVPBuilder());

    private static class FromSIPHeaderAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FromSIPHeader((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FromSIPHeader = new com.intellinet.diameter.OctetStringName("From-SIP-Header", new FromSIPHeaderAVPBuilder());

    private static class LineIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LineIdentifier((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LineIdentifier = new com.intellinet.diameter.OctetStringName("Line-Identifier", new LineIdentifierAVPBuilder());

    private static class OptionalCapabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OptionalCapability((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName OptionalCapability = new com.intellinet.diameter.Unsigned32Name("Optional-Capability", new OptionalCapabilityAVPBuilder());

    private static class UserDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserData((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName UserData = new com.intellinet.diameter.OctetStringName("User-Data", new UserDataAVPBuilder());

    private static class ServerNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServerName((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ServerName = new com.intellinet.diameter.UTF8StringName("Server-Name", new ServerNameAVPBuilder());

    private static class SCSCFRestorationInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SCSCFRestorationInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SCSCFRestorationInfo = new com.intellinet.diameter.GroupedName("SCSCF-Restoration-Info", new SCSCFRestorationInfoAVPBuilder());

    private static class SIPAuthenticationContextAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPAuthenticationContext((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SIPAuthenticationContext = new com.intellinet.diameter.OctetStringName("SIP-Authentication-Context", new SIPAuthenticationContextAVPBuilder());

    private static class SIPAuthenticateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPAuthenticate((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SIPAuthenticate = new com.intellinet.diameter.OctetStringName("SIP-Authenticate", new SIPAuthenticateAVPBuilder());

    private static class OriginatingRequestAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginatingRequest((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName OriginatingRequest = new com.intellinet.diameter.EnumeratedName("Originating-Request", new OriginatingRequestAVPBuilder());

    private static class RestorationInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RestorationInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RestorationInfo = new com.intellinet.diameter.GroupedName("Restoration-Info", new RestorationInfoAVPBuilder());

    private static class DigestAlgorithmAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DigestAlgorithm((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName DigestAlgorithm = new com.intellinet.diameter.UTF8StringName("Digest-Algorithm", new DigestAlgorithmAVPBuilder());

    private static class DigestRealmAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DigestRealm((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName DigestRealm = new com.intellinet.diameter.UTF8StringName("Digest-Realm", new DigestRealmAVPBuilder());

    private static class SIPAuthorizationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPAuthorization((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SIPAuthorization = new com.intellinet.diameter.OctetStringName("SIP-Authorization", new SIPAuthorizationAVPBuilder());

    private static class SIPDigestAuthenticateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPDigestAuthenticate((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SIPDigestAuthenticate = new com.intellinet.diameter.GroupedName("SIP-Digest-Authenticate", new SIPDigestAuthenticateAVPBuilder());

    private static class SubscriptionInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SubscriptionInfo = new com.intellinet.diameter.GroupedName("Subscription-Info", new SubscriptionInfoAVPBuilder());

    private static class IdentitywithEmergencyRegistrationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IdentitywithEmergencyRegistration((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName IdentitywithEmergencyRegistration = new com.intellinet.diameter.GroupedName("Identity-with-Emergency-Registration", new IdentitywithEmergencyRegistrationAVPBuilder());

    private static class LooseRouteIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LooseRouteIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LooseRouteIndication = new com.intellinet.diameter.EnumeratedName("Loose-Route-Indication", new LooseRouteIndicationAVPBuilder());

    private static class VisitedNetworkIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VisitedNetworkIdentifier((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName VisitedNetworkIdentifier = new com.intellinet.diameter.OctetStringName("Visited-Network-Identifier", new VisitedNetworkIdentifierAVPBuilder());

    private static class DigestHA1AVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DigestHA1((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName DigestHA1 = new com.intellinet.diameter.UTF8StringName("Digest-HA1", new DigestHA1AVPBuilder());

    private static class AssociatedRegisteredIdentitiesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AssociatedRegisteredIdentities((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AssociatedRegisteredIdentities = new com.intellinet.diameter.GroupedName("Associated-Registered-Identities", new AssociatedRegisteredIdentitiesAVPBuilder());

    private static class FramedInterfaceIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedInterfaceId((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName FramedInterfaceId = new com.intellinet.diameter.Unsigned64Name("Framed-Interface-Id", new FramedInterfaceIdAVPBuilder());

    private static class UARFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UARFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName UARFlags = new com.intellinet.diameter.Unsigned32Name("UAR-Flags", new UARFlagsAVPBuilder());

    private static class SupportedApplicationsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SupportedApplications((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SupportedApplications = new com.intellinet.diameter.GroupedName("Supported-Applications", new SupportedApplicationsAVPBuilder());

    private static class SecondaryEventChargingFunctionNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SecondaryEventChargingFunctionName((com.intellinet.diameter.URIData)impl);
        }
    }

    public static final AttributeName SecondaryEventChargingFunctionName = new com.intellinet.diameter.URIName("Secondary-Event-Charging-Function-Name", new SecondaryEventChargingFunctionNameAVPBuilder());

    private static class FeatureListAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FeatureList((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FeatureList = new com.intellinet.diameter.Unsigned32Name("Feature-List", new FeatureListAVPBuilder());

    private static class DigestQoPAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DigestQoP((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName DigestQoP = new com.intellinet.diameter.UTF8StringName("Digest-QoP", new DigestQoPAVPBuilder());

    private static class SIPAuthDataItemAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPAuthDataItem((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SIPAuthDataItem = new com.intellinet.diameter.GroupedName("SIP-Auth-Data-Item", new SIPAuthDataItemAVPBuilder());

    private static class PrimaryEventChargingFunctionNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PrimaryEventChargingFunctionName((com.intellinet.diameter.URIData)impl);
        }
    }

    public static final AttributeName PrimaryEventChargingFunctionName = new com.intellinet.diameter.URIName("Primary-Event-Charging-Function-Name", new PrimaryEventChargingFunctionNameAVPBuilder());

    private static class PathAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Path((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Path = new com.intellinet.diameter.OctetStringName("Path", new PathAVPBuilder());

    private static class ReasonInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReasonInfo((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ReasonInfo = new com.intellinet.diameter.UTF8StringName("Reason-Info", new ReasonInfoAVPBuilder());

    private static class SessionPriorityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SessionPriority((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SessionPriority = new com.intellinet.diameter.EnumeratedName("Session-Priority", new SessionPriorityAVPBuilder());

    private static class PriviledgedSenderIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PriviledgedSenderIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PriviledgedSenderIndication = new com.intellinet.diameter.EnumeratedName("Priviledged-Sender-Indication", new PriviledgedSenderIndicationAVPBuilder());

    private static class ToSIPHeaderAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ToSIPHeader((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ToSIPHeader = new com.intellinet.diameter.OctetStringName("To-SIP-Header", new ToSIPHeaderAVPBuilder());

    private static class MultipleRegistrationIndicationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MultipleRegistrationIndication((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MultipleRegistrationIndication = new com.intellinet.diameter.EnumeratedName("Multiple-Registration-Indication", new MultipleRegistrationIndicationAVPBuilder());

    private static class LIAFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LIAFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName LIAFlags = new com.intellinet.diameter.Unsigned32Name("LIA-Flags", new LIAFlagsAVPBuilder());

    private static class ContactAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Contact((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Contact = new com.intellinet.diameter.OctetStringName("Contact", new ContactAVPBuilder());

    private static class SecondaryChargingCollectionFunctionNameAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SecondaryChargingCollectionFunctionName((com.intellinet.diameter.URIData)impl);
        }
    }

    public static final AttributeName SecondaryChargingCollectionFunctionName = new com.intellinet.diameter.URIName("Secondary-Charging-Collection-Function-Name", new SecondaryChargingCollectionFunctionNameAVPBuilder());

    private static class FramedIPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPAddress((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedIPAddress = new com.intellinet.diameter.OctetStringName("Framed-IP-Address", new FramedIPAddressAVPBuilder());

    private static class UserAuthorizationTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserAuthorizationType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName UserAuthorizationType = new com.intellinet.diameter.EnumeratedName("User-Authorization-Type", new UserAuthorizationTypeAVPBuilder());

    private static class ChargingInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ChargingInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ChargingInformation = new com.intellinet.diameter.GroupedName("Charging-Information", new ChargingInformationAVPBuilder());

    private static class WildcardedPublicIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new WildcardedPublicIdentity((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName WildcardedPublicIdentity = new com.intellinet.diameter.UTF8StringName("Wildcarded-Public-Identity", new WildcardedPublicIdentityAVPBuilder());
}

