package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;

/**
 * This class defines singleton AttributeName instances for all attributes in <i><b>transatel_custom_avps</b></i>.
 */
public abstract class Transatel_custom_avpsAttributeName {

    private static class CallTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CallType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CallType = new com.intellinet.diameter.EnumeratedName("Call-Type", new CallTypeAVPBuilder());

    private static class CAPIMEIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPIMEI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPIMEI = new com.intellinet.diameter.UTF8StringName("CAP-IMEI", new CAPIMEIAVPBuilder());

    private static class CAPConnectGenericNumberARIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectGenericNumberARI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectGenericNumberARI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Generic-Number-ARI", new CAPConnectGenericNumberARIAVPBuilder());

    private static class CAPRedirectingReasonAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPRedirectingReason((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPRedirectingReason = new com.intellinet.diameter.Unsigned32Name("CAP-Redirecting-Reason", new CAPRedirectingReasonAVPBuilder());

    private static class CAPERBSMessageTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPERBSMessageType((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPERBSMessageType = new com.intellinet.diameter.Unsigned32Name("CAP-ERBS-MessageType", new CAPERBSMessageTypeAVPBuilder());

    private static class CAPConnectOriginalCalledNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectOriginalCalledNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPConnectOriginalCalledNumber = new com.intellinet.diameter.UTF8StringName("CAP-Connect-Original-Called-Number", new CAPConnectOriginalCalledNumberAVPBuilder());

    private static class CAPTCAPErrorCauseAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPTCAPErrorCause((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPTCAPErrorCause = new com.intellinet.diameter.Unsigned32Name("CAP-TCAP-Error-Cause", new CAPTCAPErrorCauseAVPBuilder());

    private static class CAPConnectRedirectingCounterAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectRedirectingCounter((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectRedirectingCounter = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Redirecting-Counter", new CAPConnectRedirectingCounterAVPBuilder());

    private static class CAPCLIRAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCLIR((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPCLIR = new com.intellinet.diameter.Unsigned32Name("CAP-CLIR", new CAPCLIRAVPBuilder());

    private static class CAPSMStatusReportRequestAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMStatusReportRequest((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMStatusReportRequest = new com.intellinet.diameter.UTF8StringName("CAP-SM-StatusReportRequest", new CAPSMStatusReportRequestAVPBuilder());

    private static class CAPSMReplyPathAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMReplyPath((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMReplyPath = new com.intellinet.diameter.UTF8StringName("CAP-SM-ReplyPath", new CAPSMReplyPathAVPBuilder());

    private static class CAPSCCPCalledGTAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSCCPCalledGT((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSCCPCalledGT = new com.intellinet.diameter.UTF8StringName("CAP-SCCP-CalledGT", new CAPSCCPCalledGTAVPBuilder());

    private static class CAPConnectInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CAPConnectInformation = new com.intellinet.diameter.GroupedName("CAP-Connect-Information", new CAPConnectInformationAVPBuilder());

    private static class CAPConnectoCSIApplicableAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectoCSIApplicable((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectoCSIApplicable = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-oCSI-Applicable", new CAPConnectoCSIApplicableAVPBuilder());

    private static class ServiceControlAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceControl((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName ServiceControl = new com.intellinet.diameter.GroupedName("Service-Control", new ServiceControlAVPBuilder());

    private static class CAPBearerCapabilityTransferModeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPBearerCapabilityTransferMode((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPBearerCapabilityTransferMode = new com.intellinet.diameter.UTF8StringName("CAP-Bearer-Capability-Transfer-Mode", new CAPBearerCapabilityTransferModeAVPBuilder());

    private static class CAPMSCAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPMSCAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPMSCAddress = new com.intellinet.diameter.UTF8StringName("CAP-MSC-Address", new CAPMSCAddressAVPBuilder());

    private static class CAPTCAPRemoteTransactionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPTCAPRemoteTransactionId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CAPTCAPRemoteTransactionId = new com.intellinet.diameter.OctetStringName("CAP-TCAP-Remote-Transaction-Id", new CAPTCAPRemoteTransactionIdAVPBuilder());

    private static class CAPEventTypeBCSMAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPEventTypeBCSM((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPEventTypeBCSM = new com.intellinet.diameter.Unsigned32Name("CAP-Event-Type-BCSM", new CAPEventTypeBCSMAVPBuilder());

    private static class CAPOriginalRedirectingReasonAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPOriginalRedirectingReason((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPOriginalRedirectingReason = new com.intellinet.diameter.Unsigned32Name("CAP-Original-Redirecting-Reason", new CAPOriginalRedirectingReasonAVPBuilder());

    private static class CAPConnectGenericNumberNPIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectGenericNumberNPI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectGenericNumberNPI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Generic-Number-NPI", new CAPConnectGenericNumberNPIAVPBuilder());

    private static class CAPGMSCAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPGMSCAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPGMSCAddress = new com.intellinet.diameter.UTF8StringName("CAP-GMSC-Address", new CAPGMSCAddressAVPBuilder());

    private static class CAPRedirectingNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPRedirectingNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPRedirectingNumber = new com.intellinet.diameter.UTF8StringName("CAP-Redirecting-Number", new CAPRedirectingNumberAVPBuilder());

    private static class CAPServiceKeyAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPServiceKey((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPServiceKey = new com.intellinet.diameter.Unsigned32Name("CAP-Service-Key", new CAPServiceKeyAVPBuilder());

    private static class CAPConnectOriginalCalledNumberNOAAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectOriginalCalledNumberNOA((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectOriginalCalledNumberNOA = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Original-Called-Number-NOA", new CAPConnectOriginalCalledNumberNOAAVPBuilder());

    private static class CAPCallingCategoryAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCallingCategory((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPCallingCategory = new com.intellinet.diameter.Unsigned32Name("CAP-Calling-Category", new CAPCallingCategoryAVPBuilder());

    private static class CAPSMUserDataHeaderIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMUserDataHeaderIndicator((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMUserDataHeaderIndicator = new com.intellinet.diameter.UTF8StringName("CAP-SM-UserDataHeaderIndicator", new CAPSMUserDataHeaderIndicatorAVPBuilder());

    private static class CAPConnectRedirectingNumberARIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectRedirectingNumberARI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectRedirectingNumberARI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Redirecting-Number-ARI", new CAPConnectRedirectingNumberARIAVPBuilder());

    private static class CAPConnectOriginalRedirectingReasonAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectOriginalRedirectingReason((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectOriginalRedirectingReason = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Original-Redirecting-Reason", new CAPConnectOriginalRedirectingReasonAVPBuilder());

    private static class CAPReleaseCauseAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPReleaseCause((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPReleaseCause = new com.intellinet.diameter.Unsigned32Name("CAP-Release-Cause", new CAPReleaseCauseAVPBuilder());

    private static class CAPConnectMaxDurationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectMaxDuration((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectMaxDuration = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-MaxDuration", new CAPConnectMaxDurationAVPBuilder());

    private static class CAPCalledNPIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCalledNPI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPCalledNPI = new com.intellinet.diameter.Unsigned32Name("CAP-Called-NPI", new CAPCalledNPIAVPBuilder());

    private static class CSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CSInformation = new com.intellinet.diameter.GroupedName("CS-Information", new CSInformationAVPBuilder());

    private static class CAPVLRNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPVLRNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPVLRNumber = new com.intellinet.diameter.UTF8StringName("CAP-VLR-Number", new CAPVLRNumberAVPBuilder());

    private static class CAPConnectRedirectingNumberNOAAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectRedirectingNumberNOA((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectRedirectingNumberNOA = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Redirecting-Number-NOA", new CAPConnectRedirectingNumberNOAAVPBuilder());

    private static class CAPConnectGenericNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectGenericNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPConnectGenericNumber = new com.intellinet.diameter.UTF8StringName("CAP-Connect-Generic-Number", new CAPConnectGenericNumberAVPBuilder());

    private static class CAPConnectGenericNumberNIIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectGenericNumberNII((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectGenericNumberNII = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Generic-Number-NII", new CAPConnectGenericNumberNIIAVPBuilder());

    private static class CAPSMSpecificInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMSpecificInfo((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CAPSMSpecificInfo = new com.intellinet.diameter.OctetStringName("CAP-SM-SpecificInfo", new CAPSMSpecificInfoAVPBuilder());

    private static class CAPIMSIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPIMSI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPIMSI = new com.intellinet.diameter.UTF8StringName("CAP-IMSI", new CAPIMSIAVPBuilder());

    private static class CAPVersionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPVersion((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPVersion = new com.intellinet.diameter.Unsigned32Name("CAP-Version", new CAPVersionAVPBuilder());

    private static class CAPCLINOAAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCLINOA((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPCLINOA = new com.intellinet.diameter.Unsigned32Name("CAP-CLI-NOA", new CAPCLINOAAVPBuilder());

    private static class CAPConnectDestinationNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectDestinationNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPConnectDestinationNumber = new com.intellinet.diameter.UTF8StringName("CAP-Connect-Destination-Number", new CAPConnectDestinationNumberAVPBuilder());

    private static class CAPConnectGenericNumberNQIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectGenericNumberNQI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectGenericNumberNQI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Generic-Number-NQI", new CAPConnectGenericNumberNQIAVPBuilder());

    private static class CAPRedirectingIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPRedirectingIndicator((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPRedirectingIndicator = new com.intellinet.diameter.Unsigned32Name("CAP-Redirecting-Indicator", new CAPRedirectingIndicatorAVPBuilder());

    private static class CAPSGSNAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSGSNAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSGSNAddress = new com.intellinet.diameter.UTF8StringName("CAP-SGSN-Address", new CAPSGSNAddressAVPBuilder());

    private static class CAPConnectCallingCategoryAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectCallingCategory((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectCallingCategory = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Calling-Category", new CAPConnectCallingCategoryAVPBuilder());

    private static class CAPRRBSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPRRBSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CAPRRBSInformation = new com.intellinet.diameter.GroupedName("CAP-RRBS-Information", new CAPRRBSInformationAVPBuilder());

    private static class CAPDialedDigitsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPDialedDigits((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPDialedDigits = new com.intellinet.diameter.UTF8StringName("CAP-Dialed-Digits", new CAPDialedDigitsAVPBuilder());

    private static class CAPCalledTONAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCalledTON((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPCalledTON = new com.intellinet.diameter.Unsigned32Name("CAP-Called-TON", new CAPCalledTONAVPBuilder());

    private static class CAPIsFollowingOnAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPIsFollowingOn((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CAPIsFollowingOn = new com.intellinet.diameter.EnumeratedName("CAP-Is-FollowingOn", new CAPIsFollowingOnAVPBuilder());

    private static class CAPGSMForwardingPendingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPGSMForwardingPending((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPGSMForwardingPending = new com.intellinet.diameter.Unsigned32Name("CAP-GSM-Forwarding-Pending", new CAPGSMForwardingPendingAVPBuilder());

    private static class CAPConnectGenericNumberSCIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectGenericNumberSCI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectGenericNumberSCI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Generic-Number-SCI", new CAPConnectGenericNumberSCIAVPBuilder());

    private static class CAPSMVPFormatAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMVPFormat((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMVPFormat = new com.intellinet.diameter.UTF8StringName("CAP-SM-VPFormat", new CAPSMVPFormatAVPBuilder());

    private static class CAPCLIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCLI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPCLI = new com.intellinet.diameter.UTF8StringName("CAP-CLI", new CAPCLIAVPBuilder());

    private static class CAPERBSLegIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPERBSLegId((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPERBSLegId = new com.intellinet.diameter.Unsigned32Name("CAP-ERBS-LegId", new CAPERBSLegIdAVPBuilder());

    private static class CAPConnectOriginalCalledNumberARIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectOriginalCalledNumberARI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectOriginalCalledNumberARI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Original-Called-Number-ARI", new CAPConnectOriginalCalledNumberARIAVPBuilder());

    private static class CAPLocationNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPLocationNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPLocationNumber = new com.intellinet.diameter.UTF8StringName("CAP-Location-Number", new CAPLocationNumberAVPBuilder());

    private static class CAPConnectDestinationNumberNatureAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectDestinationNumberNature((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectDestinationNumberNature = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Destination-Number-Nature", new CAPConnectDestinationNumberNatureAVPBuilder());

    private static class CAPACHBeepToneAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPACHBeepTone((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CAPACHBeepTone = new com.intellinet.diameter.EnumeratedName("CAP-ACH-BeepTone", new CAPACHBeepToneAVPBuilder());

    private static class CAPRedirectionCounterAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPRedirectionCounter((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPRedirectionCounter = new com.intellinet.diameter.Unsigned32Name("CAP-Redirection-Counter", new CAPRedirectionCounterAVPBuilder());

    private static class CAPSMSCAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMSCAddress((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMSCAddress = new com.intellinet.diameter.UTF8StringName("CAP-SMSC-Address", new CAPSMSCAddressAVPBuilder());

    private static class CAPSMProtocolIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMProtocolID((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMProtocolID = new com.intellinet.diameter.UTF8StringName("CAP-SM-ProtocolID", new CAPSMProtocolIDAVPBuilder());

    private static class CAPSCCPCallingGTAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSCCPCallingGT((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSCCPCallingGT = new com.intellinet.diameter.UTF8StringName("CAP-SCCP-CallingGT", new CAPSCCPCallingGTAVPBuilder());

    private static class CAPConnectRedirectingIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectRedirectingIndicator((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectRedirectingIndicator = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Redirecting-Indicator", new CAPConnectRedirectingIndicatorAVPBuilder());

    private static class CAPInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CAPInformation = new com.intellinet.diameter.GroupedName("CAP-Information", new CAPInformationAVPBuilder());

    private static class CAPSMDCSAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMDCS((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMDCS = new com.intellinet.diameter.UTF8StringName("CAP-SM-DCS", new CAPSMDCSAVPBuilder());

    private static class CAPConnectRedirectingReasonAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectRedirectingReason((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectRedirectingReason = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Redirecting-Reason", new CAPConnectRedirectingReasonAVPBuilder());

    private static class CAPSMRejectDuplicateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMRejectDuplicate((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMRejectDuplicate = new com.intellinet.diameter.UTF8StringName("CAP-SM-RejectDuplicate", new CAPSMRejectDuplicateAVPBuilder());

    private static class CAPCLINPIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCLINPI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPCLINPI = new com.intellinet.diameter.Unsigned32Name("CAP-CLI-NPI", new CAPCLINPIAVPBuilder());

    private static class CAPConnectRedirectingNumberNPIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectRedirectingNumberNPI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectRedirectingNumberNPI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Redirecting-Number-NPI", new CAPConnectRedirectingNumberNPIAVPBuilder());

    private static class CAPCallReferenceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCallReference((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CAPCallReference = new com.intellinet.diameter.OctetStringName("CAP-Call-Reference", new CAPCallReferenceAVPBuilder());

    private static class CAPConnectSuppressionOfAnnouncementAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectSuppressionOfAnnouncement((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectSuppressionOfAnnouncement = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Suppression-Of-Announcement", new CAPConnectSuppressionOfAnnouncementAVPBuilder());

    private static class CAPConnectOriginalCalledNumberNPIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectOriginalCalledNumberNPI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectOriginalCalledNumberNPI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Original-Called-Number-NPI", new CAPConnectOriginalCalledNumberNPIAVPBuilder());

    private static class SCPActionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SCPAction((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName SCPAction = new com.intellinet.diameter.EnumeratedName("SCP-Action", new SCPActionAVPBuilder());

    private static class CAPConnectDestinationNumberINNAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectDestinationNumberINN((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectDestinationNumberINN = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Destination-Number-INN", new CAPConnectDestinationNumberINNAVPBuilder());

    private static class CAPConnectDestinationNumberNPIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectDestinationNumberNPI((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectDestinationNumberNPI = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Destination-Number-NPI", new CAPConnectDestinationNumberNPIAVPBuilder());

    private static class CAPERBSEventSpecificInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPERBSEventSpecificInformation((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CAPERBSEventSpecificInformation = new com.intellinet.diameter.OctetStringName("CAP-ERBS-Event-Specific-Information", new CAPERBSEventSpecificInformationAVPBuilder());

    private static class CAPAnnouncementAccessNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPAnnouncementAccessNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPAnnouncementAccessNumber = new com.intellinet.diameter.UTF8StringName("CAP-Announcement-Access-Number", new CAPAnnouncementAccessNumberAVPBuilder());

    private static class CAPBearerCapabilityTransferRateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPBearerCapabilityTransferRate((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPBearerCapabilityTransferRate = new com.intellinet.diameter.UTF8StringName("CAP-Bearer-Capability-Transfer-Rate", new CAPBearerCapabilityTransferRateAVPBuilder());

    private static class CAPSCCPErrorCauseAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSCCPErrorCause((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPSCCPErrorCause = new com.intellinet.diameter.Unsigned32Name("CAP-SCCP-Error-Cause", new CAPSCCPErrorCauseAVPBuilder());

    private static class CAPBearerCapabilityTransferAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPBearerCapabilityTransfer((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPBearerCapabilityTransfer = new com.intellinet.diameter.UTF8StringName("CAP-Bearer-Capability-Transfer", new CAPBearerCapabilityTransferAVPBuilder());

    private static class CAPConnectRedirectingNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectRedirectingNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPConnectRedirectingNumber = new com.intellinet.diameter.UTF8StringName("CAP-Connect-Redirecting-Number", new CAPConnectRedirectingNumberAVPBuilder());

    private static class CAPEventTypeSMSAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPEventTypeSMS((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPEventTypeSMS = new com.intellinet.diameter.Unsigned32Name("CAP-Event-Type-SMS", new CAPEventTypeSMSAVPBuilder());

    private static class CAPERBSInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPERBSInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CAPERBSInformation = new com.intellinet.diameter.GroupedName("CAP-ERBS-Information", new CAPERBSInformationAVPBuilder());

    private static class CAPRRBSNoAnswerTimeoutAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPRRBSNoAnswerTimeout((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPRRBSNoAnswerTimeout = new com.intellinet.diameter.Unsigned32Name("CAP-RRBS-NoAnswerTimeout", new CAPRRBSNoAnswerTimeoutAVPBuilder());

    private static class CAPBearerCapabilityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPBearerCapability((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CAPBearerCapability = new com.intellinet.diameter.OctetStringName("CAP-Bearer-Capability", new CAPBearerCapabilityAVPBuilder());

    private static class CAPControlModeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPControlMode((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CAPControlMode = new com.intellinet.diameter.EnumeratedName("CAP-Control-Mode", new CAPControlModeAVPBuilder());

    private static class CAPSMMessageTypeIndicatorAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMMessageTypeIndicator((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMMessageTypeIndicator = new com.intellinet.diameter.UTF8StringName("CAP-SM-MessageTypeIndicator", new CAPSMMessageTypeIndicatorAVPBuilder());

    private static class CAPSMValidityPeriodAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPSMValidityPeriod((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPSMValidityPeriod = new com.intellinet.diameter.UTF8StringName("CAP-SM-ValidityPeriod", new CAPSMValidityPeriodAVPBuilder());

    private static class CAPCellIDAreaIDLAIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPCellIDAreaIDLAI((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CAPCellIDAreaIDLAI = new com.intellinet.diameter.OctetStringName("CAP-CellID-AreaID-LAI", new CAPCellIDAreaIDLAIAVPBuilder());

    private static class CAPConnectGenericNumberNOAAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPConnectGenericNumberNOA((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPConnectGenericNumberNOA = new com.intellinet.diameter.Unsigned32Name("CAP-Connect-Generic-Number-NOA", new CAPConnectGenericNumberNOAAVPBuilder());

    private static class CAPACHInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPACHInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CAPACHInformation = new com.intellinet.diameter.GroupedName("CAP-ACH-Information", new CAPACHInformationAVPBuilder());

    private static class CAPTCAPLocalTransactionIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPTCAPLocalTransactionId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CAPTCAPLocalTransactionId = new com.intellinet.diameter.OctetStringName("CAP-TCAP-Local-Transaction-Id", new CAPTCAPLocalTransactionIdAVPBuilder());

    private static class CAPAnnouncementAccessNumberNOAAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPAnnouncementAccessNumberNOA((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName CAPAnnouncementAccessNumberNOA = new com.intellinet.diameter.Unsigned32Name("CAP-Announcement-Access-Number-NOA", new CAPAnnouncementAccessNumberNOAAVPBuilder());

    private static class CAPExtBasicServiceCodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CAPExtBasicServiceCode((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CAPExtBasicServiceCode = new com.intellinet.diameter.UTF8StringName("CAP-Ext-Basic-Service-Code", new CAPExtBasicServiceCodeAVPBuilder());
}

