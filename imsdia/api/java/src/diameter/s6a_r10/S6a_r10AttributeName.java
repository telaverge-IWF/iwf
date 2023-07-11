package diameter.s6a_r10;

import com.intellinet.diameter.*;

/**
 * This class defines singleton AttributeName instances for all attributes in <i><b>s6a_r10</b></i>.
 */
public abstract class S6a_r10AttributeName {

    private static class PDPTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDPType((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName PDPType = new com.intellinet.diameter.OctetStringName("PDP-Type", new PDPTypeAVPBuilder());

    private static class UserStateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserState((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName UserState = new com.intellinet.diameter.EnumeratedName("User-State", new UserStateAVPBuilder());

    private static class XRESAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new XRES((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName XRES = new com.intellinet.diameter.OctetStringName("XRES", new XRESAVPBuilder());

    private static class MDTConfigurationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MDTConfiguration((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MDTConfiguration = new com.intellinet.diameter.GroupedName("MDT-Configuration", new MDTConfigurationAVPBuilder());

    private static class RANDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RAND((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName RAND = new com.intellinet.diameter.OctetStringName("RAND", new RANDAVPBuilder());

    private static class TraceInterfaceListAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TraceInterfaceList((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TraceInterfaceList = new com.intellinet.diameter.OctetStringName("Trace-Interface-List", new TraceInterfaceListAVPBuilder());

    private static class GPRSSubscriptionDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GPRSSubscriptionData((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName GPRSSubscriptionData = new com.intellinet.diameter.GroupedName("GPRS-Subscription-Data", new GPRSSubscriptionDataAVPBuilder());

    private static class UESRVCCCapabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UESRVCCCapability((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName UESRVCCCapability = new com.intellinet.diameter.EnumeratedName("UE-SRVCC-Capability", new UESRVCCCapabilityAVPBuilder());

    private static class TraceReferenceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TraceReference((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TraceReference = new com.intellinet.diameter.OctetStringName("Trace-Reference", new TraceReferenceAVPBuilder());

    private static class TraceNETypeListAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TraceNETypeList((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TraceNETypeList = new com.intellinet.diameter.OctetStringName("Trace-NE-Type-List", new TraceNETypeListAVPBuilder());

    private static class FeatureListIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FeatureListID((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FeatureListID = new com.intellinet.diameter.Unsigned32Name("Feature-List-ID", new FeatureListIDAVPBuilder());

    private static class EPSSubscribedQoSProfileAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EPSSubscribedQoSProfile((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName EPSSubscribedQoSProfile = new com.intellinet.diameter.GroupedName("EPS-Subscribed-QoS-Profile", new EPSSubscribedQoSProfileAVPBuilder());

    private static class LCSPrivacyExceptionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSPrivacyException((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName LCSPrivacyException = new com.intellinet.diameter.GroupedName("LCS-PrivacyException", new LCSPrivacyExceptionAVPBuilder());

    private static class EUTRANVectorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EUTRANVector((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName EUTRANVector = new com.intellinet.diameter.GroupedName("E-UTRAN-Vector", new EUTRANVectorAVPBuilder());

    private static class DSAFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DSAFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName DSAFlags = new com.intellinet.diameter.Unsigned32Name("DSA-Flags", new DSAFlagsAVPBuilder());

    private static class CompleteDataListIncludedIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CompleteDataListIncludedIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CompleteDataListIncludedIndicator = new com.intellinet.diameter.EnumeratedName("Complete-Data-List-Included-Indicator", new CompleteDataListIncludedIndicatorAVPBuilder());

    private static class PDNGWAllocationTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDNGWAllocationType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PDNGWAllocationType = new com.intellinet.diameter.EnumeratedName("PDN-GW-Allocation-Type", new PDNGWAllocationTypeAVPBuilder());

    private static class NetworkAccessModeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NetworkAccessMode((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName NetworkAccessMode = new com.intellinet.diameter.EnumeratedName("Network-Access-Mode", new NetworkAccessModeAVPBuilder());

    private static class ReportIntervalAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReportInterval((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ReportInterval = new com.intellinet.diameter.EnumeratedName("Report-Interval", new ReportIntervalAVPBuilder());

    private static class ReportAmountAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReportAmount((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ReportAmount = new com.intellinet.diameter.EnumeratedName("Report-Amount", new ReportAmountAVPBuilder());

    private static class CSGSubscriptionDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CSGSubscriptionData((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CSGSubscriptionData = new com.intellinet.diameter.GroupedName("CSG-Subscription-Data", new CSGSubscriptionDataAVPBuilder());

    private static class ContextIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ContextIdentifier((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ContextIdentifier = new com.intellinet.diameter.Unsigned32Name("Context-Identifier", new ContextIdentifierAVPBuilder());

    private static class AlertReasonAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AlertReason((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AlertReason = new com.intellinet.diameter.EnumeratedName("Alert-Reason", new AlertReasonAVPBuilder());

    private static class SIPTOPermissionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SIPTOPermission((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SIPTOPermission = new com.intellinet.diameter.EnumeratedName("SIPTO-Permission", new SIPTOPermissionAVPBuilder());

    private static class IKAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IK((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName IK = new com.intellinet.diameter.OctetStringName("IK", new IKAVPBuilder());

    private static class PDPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName PDPAddress = new com.intellinet.diameter.AddressName("PDP-Address", new PDPAddressAVPBuilder());

    private static class EquipmentStatusAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EquipmentStatus((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName EquipmentStatus = new com.intellinet.diameter.EnumeratedName("Equipment-Status", new EquipmentStatusAVPBuilder());

    private static class ServiceTypeIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceTypeIdentity((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ServiceTypeIdentity = new com.intellinet.diameter.Unsigned32Name("ServiceTypeIdentity", new ServiceTypeIdentityAVPBuilder());

    private static class SpecificAPNInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SpecificAPNInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SpecificAPNInfo = new com.intellinet.diameter.GroupedName("Specific-APN-Info", new SpecificAPNInfoAVPBuilder());

    private static class KASMEAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new KASME((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName KASME = new com.intellinet.diameter.OctetStringName("KASME", new KASMEAVPBuilder());

    private static class PDNTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDNType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PDNType = new com.intellinet.diameter.EnumeratedName("PDN-Type", new PDNTypeAVPBuilder());

    private static class AgeOfLocationInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AgeOfLocationInformation((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName AgeOfLocationInformation = new com.intellinet.diameter.Unsigned32Name("Age-Of-Location-Information", new AgeOfLocationInformationAVPBuilder());

    private static class GERANVectorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GERANVector((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName GERANVector = new com.intellinet.diameter.GroupedName("GERAN-Vector", new GERANVectorAVPBuilder());

    private static class AccessRestrictionDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccessRestrictionData((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName AccessRestrictionData = new com.intellinet.diameter.Unsigned32Name("Access-Restriction-Data", new AccessRestrictionDataAVPBuilder());

    private static class UserIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName UserId = new com.intellinet.diameter.OctetStringName("User-Id", new UserIdAVPBuilder());

    private static class GeographicalInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GeographicalInformation((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName GeographicalInformation = new com.intellinet.diameter.OctetStringName("Geographical-Information", new GeographicalInformationAVPBuilder());

    private static class PURFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PURFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PURFlags = new com.intellinet.diameter.Unsigned32Name("PUR-Flags", new PURFlagsAVPBuilder());

    private static class ListOfMeasurementsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ListOfMeasurements((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ListOfMeasurements = new com.intellinet.diameter.Unsigned32Name("List-Of-Measurements", new ListOfMeasurementsAVPBuilder());

    private static class RegionalSubscriptionZoneCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RegionalSubscriptionZoneCode((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName RegionalSubscriptionZoneCode = new com.intellinet.diameter.OctetStringName("Regional-Subscription-Zone-Code", new RegionalSubscriptionZoneCodeAVPBuilder());

    private static class VPLMNLIPAAllowedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VPLMNLIPAAllowed((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName VPLMNLIPAAllowed = new com.intellinet.diameter.EnumeratedName("VPLMN-LIPA-Allowed", new VPLMNLIPAAllowedAVPBuilder());

    private static class PUAFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PUAFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PUAFlags = new com.intellinet.diameter.Unsigned32Name("PUA-Flags", new PUAFlagsAVPBuilder());

    private static class OperatorDeterminedBarringAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OperatorDeterminedBarring((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName OperatorDeterminedBarring = new com.intellinet.diameter.Unsigned32Name("Operator-Determined-Barring", new OperatorDeterminedBarringAVPBuilder());

    private static class LoggingIntervalAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoggingInterval((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LoggingInterval = new com.intellinet.diameter.EnumeratedName("Logging-Interval", new LoggingIntervalAVPBuilder());

    private static class APNOIReplacementAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new APNOIReplacement((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName APNOIReplacement = new com.intellinet.diameter.UTF8StringName("APN-OI-Replacement", new APNOIReplacementAVPBuilder());

    private static class CellGlobalIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CellGlobalIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CellGlobalIdentity = new com.intellinet.diameter.OctetStringName("Cell-Global-Identity", new CellGlobalIdentityAVPBuilder());

    private static class ActiveAPNAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ActiveAPN((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ActiveAPN = new com.intellinet.diameter.GroupedName("Active-APN", new ActiveAPNAVPBuilder());

    private static class JobTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new JobType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName JobType = new com.intellinet.diameter.EnumeratedName("Job-Type", new JobTypeAVPBuilder());

    private static class ServedPartyIPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServedPartyIPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName ServedPartyIPAddress = new com.intellinet.diameter.AddressName("Served-Party-IP-Address", new ServedPartyIPAddressAVPBuilder());

    private static class LastUEActivityTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LastUEActivityTime((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName LastUEActivityTime = new com.intellinet.diameter.TimeName("Last-UE-Activity-Time", new LastUEActivityTimeAVPBuilder());

    private static class AllAPNConfigurationsIncludedIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AllAPNConfigurationsIncludedIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AllAPNConfigurationsIncludedIndicator = new com.intellinet.diameter.EnumeratedName("All-APN-Configurations-Included-Indicator", new AllAPNConfigurationsIncludedIndicatorAVPBuilder());

    private static class VisitedNetworkIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VisitedNetworkIdentifier((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName VisitedNetworkIdentifier = new com.intellinet.diameter.OctetStringName("Visited-Network-Identifier", new VisitedNetworkIdentifierAVPBuilder());

    private static class TraceCollectionEntityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TraceCollectionEntity((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName TraceCollectionEntity = new com.intellinet.diameter.AddressName("Trace-Collection-Entity", new TraceCollectionEntityAVPBuilder());

    private static class TerminalInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TerminalInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TerminalInformation = new com.intellinet.diameter.GroupedName("Terminal-Information", new TerminalInformationAVPBuilder());

    private static class IDRFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IDRFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName IDRFlags = new com.intellinet.diameter.Unsigned32Name("IDR-Flags", new IDRFlagsAVPBuilder());

    private static class TSCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TSCode((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TSCode = new com.intellinet.diameter.OctetStringName("TS-Code", new TSCodeAVPBuilder());

    private static class IMSVoiceOverPSSessionsSupportedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMSVoiceOverPSSessionsSupported((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName IMSVoiceOverPSSessionsSupported = new com.intellinet.diameter.EnumeratedName("IMS-Voice-Over-PS-Sessions-Supported", new IMSVoiceOverPSSessionsSupportedAVPBuilder());

    private static class FeatureListAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FeatureList((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FeatureList = new com.intellinet.diameter.Unsigned32Name("Feature-List", new FeatureListAVPBuilder());

    private static class EPSUserStateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EPSUserState((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName EPSUserState = new com.intellinet.diameter.GroupedName("EPS-User-State", new EPSUserStateAVPBuilder());

    private static class AMBRAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AMBR((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AMBR = new com.intellinet.diameter.GroupedName("AMBR", new AMBRAVPBuilder());

    private static class ExtPDPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ExtPDPAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName ExtPDPAddress = new com.intellinet.diameter.AddressName("Ext-PDP-Address", new ExtPDPAddressAVPBuilder());

    private static class LCSInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LCSInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName LCSInfo = new com.intellinet.diameter.GroupedName("LCS-Info", new LCSInfoAVPBuilder());

    private static class RequestedEUTRANAuthenticationInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequestedEUTRANAuthenticationInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RequestedEUTRANAuthenticationInfo = new com.intellinet.diameter.GroupedName("Requested-EUTRAN-Authentication-Info", new RequestedEUTRANAuthenticationInfoAVPBuilder());

    private static class CKAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CK((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CK = new com.intellinet.diameter.OctetStringName("CK", new CKAVPBuilder());

    private static class SGSNUserStateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SGSNUserState((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SGSNUserState = new com.intellinet.diameter.GroupedName("SGSN-User-State", new SGSNUserStateAVPBuilder());

    private static class QoSClassIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new QoSClassIdentifier((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName QoSClassIdentifier = new com.intellinet.diameter.EnumeratedName("QoS-Class-Identifier", new QoSClassIdentifierAVPBuilder());

    private static class MIP6HomeLinkPrefixAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MIP6HomeLinkPrefix((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName MIP6HomeLinkPrefix = new com.intellinet.diameter.OctetStringName("MIP6-Home-Link-Prefix", new MIP6HomeLinkPrefixAVPBuilder());

    private static class SRESAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SRES((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SRES = new com.intellinet.diameter.OctetStringName("SRES", new SRESAVPBuilder());

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

    private static class SoftwareVersionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SoftwareVersion((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SoftwareVersion = new com.intellinet.diameter.UTF8StringName("Software-Version", new SoftwareVersionAVPBuilder());

    private static class ICSIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ICSIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ICSIndicator = new com.intellinet.diameter.EnumeratedName("ICS-Indicator", new ICSIndicatorAVPBuilder());

    private static class LIPAPermissionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LIPAPermission((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LIPAPermission = new com.intellinet.diameter.EnumeratedName("LIPA-Permission", new LIPAPermissionAVPBuilder());

    private static class MIPHomeAgentAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MIPHomeAgentAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName MIPHomeAgentAddress = new com.intellinet.diameter.AddressName("MIP-Home-Agent-Address", new MIPHomeAgentAddressAVPBuilder());

    private static class MMEUserStateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MMEUserState((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MMEUserState = new com.intellinet.diameter.GroupedName("MME-User-State", new MMEUserStateAVPBuilder());

    private static class DSRFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new DSRFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName DSRFlags = new com.intellinet.diameter.Unsigned32Name("DSR-Flags", new DSRFlagsAVPBuilder());

    private static class KcAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Kc((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName Kc = new com.intellinet.diameter.OctetStringName("Kc", new KcAVPBuilder());

    private static class SGSNLocationInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SGSNLocationInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SGSNLocationInformation = new com.intellinet.diameter.GroupedName("SGSN-Location-Information", new SGSNLocationInformationAVPBuilder());

    private static class STNSRAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new STNSR((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName STNSR = new com.intellinet.diameter.OctetStringName("STN-SR", new STNSRAVPBuilder());

    private static class ExpirationDateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ExpirationDate((com.intellinet.diameter.TimeData)impl);
        }
    }

    public static final AttributeName ExpirationDate = new com.intellinet.diameter.TimeName("Expiration-Date", new ExpirationDateAVPBuilder());

    private static class ServiceSelectionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceSelection((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ServiceSelection = new com.intellinet.diameter.UTF8StringName("Service-Selection", new ServiceSelectionAVPBuilder());

    private static class S6a3GPP2MEIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new S6a3GPP2MEID((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName S6a3GPP2MEID = new com.intellinet.diameter.OctetStringName("S6a-3GPP2-MEID", new S6a3GPP2MEIDAVPBuilder());

    private static class PLMNClientAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PLMNClient((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PLMNClient = new com.intellinet.diameter.EnumeratedName("PLMN-Client", new PLMNClientAVPBuilder());

    private static class PDPContextAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PDPContext((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName PDPContext = new com.intellinet.diameter.GroupedName("PDP-Context", new PDPContextAVPBuilder());

    private static class SupportedFeaturesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SupportedFeatures((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SupportedFeatures = new com.intellinet.diameter.GroupedName("Supported-Features", new SupportedFeaturesAVPBuilder());

    private static class CancellationTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CancellationType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CancellationType = new com.intellinet.diameter.EnumeratedName("Cancellation-Type", new CancellationTypeAVPBuilder());

    private static class RelayNodeIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RelayNodeIndicator((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RelayNodeIndicator = new com.intellinet.diameter.EnumeratedName("Relay-Node-Indicator", new RelayNodeIndicatorAVPBuilder());

    private static class PreemptionVulnerabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PreemptionVulnerability((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName PreemptionVulnerability = new com.intellinet.diameter.EnumeratedName("Pre-emption-Vulnerability", new PreemptionVulnerabilityAVPBuilder());

    private static class TrackingAreaIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TrackingAreaIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TrackingAreaIdentity = new com.intellinet.diameter.OctetStringName("Tracking-Area-Identity", new TrackingAreaIdentityAVPBuilder());

    private static class CurrentLocationRetrievedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CurrentLocationRetrieved((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CurrentLocationRetrieved = new com.intellinet.diameter.EnumeratedName("Current-Location-Retrieved", new CurrentLocationRetrievedAVPBuilder());

    private static class GMLCRestrictionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GMLCRestriction((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName GMLCRestriction = new com.intellinet.diameter.EnumeratedName("GMLC-Restriction", new GMLCRestrictionAVPBuilder());

    private static class TraceDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TraceData((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TraceData = new com.intellinet.diameter.GroupedName("Trace-Data", new TraceDataAVPBuilder());

    private static class QoSSubscribedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new QoSSubscribed((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName QoSSubscribed = new com.intellinet.diameter.OctetStringName("QoS-Subscribed", new QoSSubscribedAVPBuilder());

    private static class HPLMNODBAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new HPLMNODB((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName HPLMNODB = new com.intellinet.diameter.Unsigned32Name("HPLMN-ODB", new HPLMNODBAVPBuilder());

    private static class APNConfigurationProfileAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new APNConfigurationProfile((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName APNConfigurationProfile = new com.intellinet.diameter.GroupedName("APN-Configuration-Profile", new APNConfigurationProfileAVPBuilder());

    private static class ULRFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ULRFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ULRFlags = new com.intellinet.diameter.Unsigned32Name("ULR-Flags", new ULRFlagsAVPBuilder());

    private static class MIPHomeAgentHostAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MIPHomeAgentHost((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MIPHomeAgentHost = new com.intellinet.diameter.GroupedName("MIP-Home-Agent-Host", new MIPHomeAgentHostAVPBuilder());

    private static class ReportingTriggerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReportingTrigger((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ReportingTrigger = new com.intellinet.diameter.Unsigned32Name("Reporting-Trigger", new ReportingTriggerAVPBuilder());

    private static class GMLCNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GMLCNumber((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName GMLCNumber = new com.intellinet.diameter.OctetStringName("GMLC-Number", new GMLCNumberAVPBuilder());

    private static class NORFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NORFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NORFlags = new com.intellinet.diameter.Unsigned32Name("NOR-Flags", new NORFlagsAVPBuilder());

    private static class ClientIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ClientIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ClientIdentity = new com.intellinet.diameter.OctetStringName("Client-Identity", new ClientIdentityAVPBuilder());

    private static class CallBarringInforListAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CallBarringInforList((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CallBarringInforList = new com.intellinet.diameter.GroupedName("Call-Barring-Infor-List", new CallBarringInforListAVPBuilder());

    private static class AreaScopeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AreaScope((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AreaScope = new com.intellinet.diameter.GroupedName("Area-Scope", new AreaScopeAVPBuilder());

    private static class LocationAreaIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LocationAreaIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LocationAreaIdentity = new com.intellinet.diameter.OctetStringName("Location-Area-Identity", new LocationAreaIdentityAVPBuilder());

    private static class RATTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RATType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RATType = new com.intellinet.diameter.EnumeratedName("RAT-Type", new RATTypeAVPBuilder());

    private static class ServiceAreaIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceAreaIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ServiceAreaIdentity = new com.intellinet.diameter.OctetStringName("Service-Area-Identity", new ServiceAreaIdentityAVPBuilder());

    private static class UTRANVectorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UTRANVector((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName UTRANVector = new com.intellinet.diameter.GroupedName("UTRAN-Vector", new UTRANVectorAVPBuilder());

    private static class AUTNAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AUTN((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName AUTN = new com.intellinet.diameter.OctetStringName("AUTN", new AUTNAVPBuilder());

    private static class MMELocationInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MMELocationInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MMELocationInformation = new com.intellinet.diameter.GroupedName("MME-Location-Information", new MMELocationInformationAVPBuilder());

    private static class TraceDepthAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TraceDepth((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TraceDepth = new com.intellinet.diameter.EnumeratedName("Trace-Depth", new TraceDepthAVPBuilder());

    private static class NotificationToUEUserAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NotificationToUEUser((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName NotificationToUEUser = new com.intellinet.diameter.EnumeratedName("Notification-To-UE-User", new NotificationToUEUserAVPBuilder());

    private static class HomogeneousSupportofIMSVoiceOverPSSessionsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new HomogeneousSupportofIMSVoiceOverPSSessions((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName HomogeneousSupportofIMSVoiceOverPSSessions = new com.intellinet.diameter.EnumeratedName("Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions", new HomogeneousSupportofIMSVoiceOverPSSessionsAVPBuilder());

    private static class ULAFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ULAFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ULAFlags = new com.intellinet.diameter.Unsigned32Name("ULA-Flags", new ULAFlagsAVPBuilder());

    private static class SSCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SSCode((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SSCode = new com.intellinet.diameter.OctetStringName("SS-Code", new SSCodeAVPBuilder());

    private static class S6a3GPPChargingCharacteristicsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new S6a3GPPChargingCharacteristics((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName S6a3GPPChargingCharacteristics = new com.intellinet.diameter.UTF8StringName("S6a-3GPP-Charging-Characteristics", new S6a3GPPChargingCharacteristicsAVPBuilder());

    private static class ErrorDiagnosticAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ErrorDiagnostic((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ErrorDiagnostic = new com.intellinet.diameter.EnumeratedName("Error-Diagnostic", new ErrorDiagnosticAVPBuilder());

    private static class LoggingDurationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoggingDuration((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LoggingDuration = new com.intellinet.diameter.EnumeratedName("Logging-Duration", new LoggingDurationAVPBuilder());

    private static class MIP6AgentInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MIP6AgentInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MIP6AgentInfo = new com.intellinet.diameter.GroupedName("MIP6-Agent-Info", new MIP6AgentInfoAVPBuilder());

    private static class EventThresholdRSRPAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EventThresholdRSRP((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName EventThresholdRSRP = new com.intellinet.diameter.Unsigned32Name("Event-Threshold-RSRP", new EventThresholdRSRPAVPBuilder());

    private static class EventThresholdRSRQAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EventThresholdRSRQ((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName EventThresholdRSRQ = new com.intellinet.diameter.Unsigned32Name("Event-Threshold-RSRQ", new EventThresholdRSRQAVPBuilder());

    private static class SGSNNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SGSNNumber((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SGSNNumber = new com.intellinet.diameter.OctetStringName("SGSN-Number", new SGSNNumberAVPBuilder());

    private static class AllocationRetentionPriorityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AllocationRetentionPriority((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AllocationRetentionPriority = new com.intellinet.diameter.GroupedName("Allocation-Retention-Priority", new AllocationRetentionPriorityAVPBuilder());

    private static class MPSPriorityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MPSPriority((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MPSPriority = new com.intellinet.diameter.Unsigned32Name("MPS-Priority", new MPSPriorityAVPBuilder());

    private static class MSISDNAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MSISDN((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName MSISDN = new com.intellinet.diameter.OctetStringName("MSISDN", new MSISDNAVPBuilder());

    private static class SSStatusAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SSStatus((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName SSStatus = new com.intellinet.diameter.OctetStringName("SS-Status", new SSStatusAVPBuilder());

    private static class RequestedUTRANGERANAuthenticationInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequestedUTRANGERANAuthenticationInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName RequestedUTRANGERANAuthenticationInfo = new com.intellinet.diameter.GroupedName("Requested-UTRAN-GERAN-Authentication-Info", new RequestedUTRANGERANAuthenticationInfoAVPBuilder());

    private static class MaxRequestedBandwidthULAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MaxRequestedBandwidthUL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MaxRequestedBandwidthUL = new com.intellinet.diameter.Unsigned32Name("Max-Requested-Bandwidth-UL", new MaxRequestedBandwidthULAVPBuilder());

    private static class OMCIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OMCId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName OMCId = new com.intellinet.diameter.OctetStringName("OMC-Id", new OMCIdAVPBuilder());

    private static class VPLMNDynamicAddressAllowedAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VPLMNDynamicAddressAllowed((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName VPLMNDynamicAddressAllowed = new com.intellinet.diameter.EnumeratedName("VPLMN-Dynamic-Address-Allowed", new VPLMNDynamicAddressAllowedAVPBuilder());

    private static class SubscribedPeriodicRAUTAUTimerAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscribedPeriodicRAUTAUTimer((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName SubscribedPeriodicRAUTAUTimer = new com.intellinet.diameter.Unsigned32Name("Subscribed-Periodic-RAU-TAU-Timer", new SubscribedPeriodicRAUTAUTimerAVPBuilder());

    private static class SubscriptionDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriptionData((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName SubscriptionData = new com.intellinet.diameter.GroupedName("Subscription-Data", new SubscriptionDataAVPBuilder());

    private static class GMLCAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GMLCAddress((com.intellinet.diameter.AddressData)impl);
        }
    }

    public static final AttributeName GMLCAddress = new com.intellinet.diameter.AddressName("GMLC-Address", new GMLCAddressAVPBuilder());

    private static class MaxRequestedBandwidthDLAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MaxRequestedBandwidthDL((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName MaxRequestedBandwidthDL = new com.intellinet.diameter.Unsigned32Name("Max-Requested-Bandwidth-DL", new MaxRequestedBandwidthDLAVPBuilder());

    private static class RoamingRestrictedDueToUnsupportedFeatureAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RoamingRestrictedDueToUnsupportedFeature((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RoamingRestrictedDueToUnsupportedFeature = new com.intellinet.diameter.EnumeratedName("Roaming-Restricted-Due-To-Unsupported-Feature", new RoamingRestrictedDueToUnsupportedFeatureAVPBuilder());

    private static class ItemNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ItemNumber((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ItemNumber = new com.intellinet.diameter.Unsigned32Name("Item-Number", new ItemNumberAVPBuilder());

    private static class GeodeticInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new GeodeticInformation((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName GeodeticInformation = new com.intellinet.diameter.OctetStringName("Geodetic-Information", new GeodeticInformationAVPBuilder());

    private static class ImmediateResponsePreferredAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ImmediateResponsePreferred((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ImmediateResponsePreferred = new com.intellinet.diameter.Unsigned32Name("Immediate-Response-Preferred", new ImmediateResponsePreferredAVPBuilder());

    private static class ExternalClientAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ExternalClient((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ExternalClient = new com.intellinet.diameter.GroupedName("External-Client", new ExternalClientAVPBuilder());

    private static class EPSLocationInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EPSLocationInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName EPSLocationInformation = new com.intellinet.diameter.GroupedName("EPS-Location-Information", new EPSLocationInformationAVPBuilder());

    private static class ServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceType((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServiceType = new com.intellinet.diameter.GroupedName("Service-Type", new ServiceTypeAVPBuilder());

    private static class TraceEventListAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TraceEventList((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TraceEventList = new com.intellinet.diameter.OctetStringName("Trace-Event-List", new TraceEventListAVPBuilder());

    private static class NumberOfRequestedVectorsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NumberOfRequestedVectors((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NumberOfRequestedVectors = new com.intellinet.diameter.Unsigned32Name("Number-Of-Requested-Vectors", new NumberOfRequestedVectorsAVPBuilder());

    private static class AuthenticationInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AuthenticationInfo((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName AuthenticationInfo = new com.intellinet.diameter.GroupedName("Authentication-Info", new AuthenticationInfoAVPBuilder());

    private static class APNConfigurationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new APNConfiguration((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName APNConfiguration = new com.intellinet.diameter.GroupedName("APN-Configuration", new APNConfigurationAVPBuilder());

    private static class IMEIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMEI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IMEI = new com.intellinet.diameter.UTF8StringName("IMEI", new IMEIAVPBuilder());

    private static class RoutingAreaIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RoutingAreaIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName RoutingAreaIdentity = new com.intellinet.diameter.OctetStringName("Routing-Area-Identity", new RoutingAreaIdentityAVPBuilder());

    private static class MDTUserConsentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MDTUserConsent((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName MDTUserConsent = new com.intellinet.diameter.EnumeratedName("MDT-User-Consent", new MDTUserConsentAVPBuilder());

    private static class MOLRAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new MOLR((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName MOLR = new com.intellinet.diameter.GroupedName("MO-LR", new MOLRAVPBuilder());

    private static class RATFrequencySelectionPriorityIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RATFrequencySelectionPriorityID((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName RATFrequencySelectionPriorityID = new com.intellinet.diameter.Unsigned32Name("RAT-Frequency-Selection-Priority-ID", new RATFrequencySelectionPriorityIDAVPBuilder());

    private static class RequestingNodeTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new RequestingNodeType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName RequestingNodeType = new com.intellinet.diameter.EnumeratedName("Requesting-Node-Type", new RequestingNodeTypeAVPBuilder());

    private static class TeleserviceListAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TeleserviceList((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TeleserviceList = new com.intellinet.diameter.GroupedName("Teleservice-List", new TeleserviceListAVPBuilder());

    private static class CSGIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CSGId((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CSGId = new com.intellinet.diameter.Unsigned32Name("CSG-Id", new CSGIdAVPBuilder());

    private static class SubscriberStatusAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SubscriberStatus((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SubscriberStatus = new com.intellinet.diameter.EnumeratedName("Subscriber-Status", new SubscriberStatusAVPBuilder());

    private static class ExtPDPTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ExtPDPType((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ExtPDPType = new com.intellinet.diameter.OctetStringName("Ext-PDP-Type", new ExtPDPTypeAVPBuilder());

    private static class CLRFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CLRFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CLRFlags = new com.intellinet.diameter.Unsigned32Name("CLR-Flags", new CLRFlagsAVPBuilder());

    private static class EUTRANCellGlobalIdentityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EUTRANCellGlobalIdentity((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName EUTRANCellGlobalIdentity = new com.intellinet.diameter.OctetStringName("E-UTRAN-Cell-Global-Identity", new EUTRANCellGlobalIdentityAVPBuilder());

    private static class ReSynchronizationInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReSynchronizationInfo((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ReSynchronizationInfo = new com.intellinet.diameter.OctetStringName("Re-Synchronization-Info", new ReSynchronizationInfoAVPBuilder());

    private static class VisitedPLMNIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new VisitedPLMNId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName VisitedPLMNId = new com.intellinet.diameter.OctetStringName("Visited-PLMN-Id", new VisitedPLMNIdAVPBuilder());

    private static class IDAFlagsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IDAFlags((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName IDAFlags = new com.intellinet.diameter.Unsigned32Name("IDA-Flags", new IDAFlagsAVPBuilder());
}

