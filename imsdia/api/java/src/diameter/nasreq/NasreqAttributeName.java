package diameter.nasreq;

import com.intellinet.diameter.*;

/**
 * This class defines singleton AttributeName instances for all attributes in <i><b>nasreq</b></i>.
 */
public abstract class NasreqAttributeName {

    private static class CHAPIdentAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CHAPIdent((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CHAPIdent = new com.intellinet.diameter.OctetStringName("CHAP-Ident", new CHAPIdentAVPBuilder());

    private static class OriginatingLineInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginatingLineInfo((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName OriginatingLineInfo = new com.intellinet.diameter.OctetStringName("Originating-Line-Info", new OriginatingLineInfoAVPBuilder());

    private static class ARAPChallengeResponseAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ARAPChallengeResponse((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ARAPChallengeResponse = new com.intellinet.diameter.OctetStringName("ARAP-Challenge-Response", new ARAPChallengeResponseAVPBuilder());

    private static class FramedIPv6PrefixAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPv6Prefix((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedIPv6Prefix = new com.intellinet.diameter.OctetStringName("Framed-IPv6-Prefix", new FramedIPv6PrefixAVPBuilder());

    private static class CallbackNumberAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CallbackNumber((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CallbackNumber = new com.intellinet.diameter.UTF8StringName("Callback-Number", new CallbackNumberAVPBuilder());

    private static class TunnelClientAuthIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelClientAuthId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName TunnelClientAuthId = new com.intellinet.diameter.UTF8StringName("Tunnel-Client-Auth-Id", new TunnelClientAuthIdAVPBuilder());

    private static class NASFilterRuleAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NASFilterRule((com.intellinet.diameter.IPFilterRuleData)impl);
        }
    }

    public static final AttributeName NASFilterRule = new com.intellinet.diameter.IPFilterRuleName("NAS-Filter-Rule", new NASFilterRuleAVPBuilder());

    private static class FramedAppletalkZoneAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedAppletalkZone((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedAppletalkZone = new com.intellinet.diameter.OctetStringName("Framed-Appletalk-Zone", new FramedAppletalkZoneAVPBuilder());

    private static class PortLimitAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PortLimit((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PortLimit = new com.intellinet.diameter.Unsigned32Name("Port-Limit", new PortLimitAVPBuilder());

    private static class LoginLATGroupAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginLATGroup((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LoginLATGroup = new com.intellinet.diameter.OctetStringName("Login-LAT-Group", new LoginLATGroupAVPBuilder());

    private static class TunnelAssignmentIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelAssignmentId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TunnelAssignmentId = new com.intellinet.diameter.OctetStringName("Tunnel-Assignment-Id", new TunnelAssignmentIdAVPBuilder());

    private static class TunnelingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Tunneling((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName Tunneling = new com.intellinet.diameter.GroupedName("Tunneling", new TunnelingAVPBuilder());

    private static class AccountingInputPacketsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingInputPackets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingInputPackets = new com.intellinet.diameter.Unsigned64Name("Accounting-Input-Packets", new AccountingInputPacketsAVPBuilder());

    private static class LoginServiceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginService((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName LoginService = new com.intellinet.diameter.EnumeratedName("Login-Service", new LoginServiceAVPBuilder());

    private static class AccountingOutputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingOutputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingOutputOctets = new com.intellinet.diameter.Unsigned64Name("Accounting-Output-Octets", new AccountingOutputOctetsAVPBuilder());

    private static class NASPortAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NASPort((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName NASPort = new com.intellinet.diameter.Unsigned32Name("NAS-Port", new NASPortAVPBuilder());

    private static class IdleTimeoutAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IdleTimeout((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName IdleTimeout = new com.intellinet.diameter.Unsigned32Name("Idle-Timeout", new IdleTimeoutAVPBuilder());

    private static class ARAPZoneAccessAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ARAPZoneAccess((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ARAPZoneAccess = new com.intellinet.diameter.EnumeratedName("ARAP-Zone-Access", new ARAPZoneAccessAVPBuilder());

    private static class FramedMTUAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedMTU((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FramedMTU = new com.intellinet.diameter.Unsigned32Name("Framed-MTU", new FramedMTUAVPBuilder());

    private static class AcctLinkCountAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AcctLinkCount((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName AcctLinkCount = new com.intellinet.diameter.Unsigned32Name("Acct-Link-Count", new AcctLinkCountAVPBuilder());

    private static class StateAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new State((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName State = new com.intellinet.diameter.OctetStringName("State", new StateAVPBuilder());

    private static class AcctTunnelPacketsLostAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AcctTunnelPacketsLost((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName AcctTunnelPacketsLost = new com.intellinet.diameter.Unsigned32Name("Acct-Tunnel-Packets-Lost", new AcctTunnelPacketsLostAVPBuilder());

    private static class FramedPoolAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedPool((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedPool = new com.intellinet.diameter.OctetStringName("Framed-Pool", new FramedPoolAVPBuilder());

    private static class LoginIPv6HostAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginIPv6Host((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LoginIPv6Host = new com.intellinet.diameter.OctetStringName("Login-IPv6-Host", new LoginIPv6HostAVPBuilder());

    private static class FramedRouteAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedRoute((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName FramedRoute = new com.intellinet.diameter.UTF8StringName("Framed-Route", new FramedRouteAVPBuilder());

    private static class AcctTunnelConnectionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AcctTunnelConnection((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName AcctTunnelConnection = new com.intellinet.diameter.OctetStringName("Acct-Tunnel-Connection", new AcctTunnelConnectionAVPBuilder());

    private static class FramedIPXNetworkAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPXNetwork((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName FramedIPXNetwork = new com.intellinet.diameter.UTF8StringName("Framed-IPX-Network", new FramedIPXNetworkAVPBuilder());

    private static class AcctSessionTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AcctSessionTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName AcctSessionTime = new com.intellinet.diameter.Unsigned32Name("Acct-Session-Time", new AcctSessionTimeAVPBuilder());

    private static class LoginLATServiceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginLATService((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LoginLATService = new com.intellinet.diameter.OctetStringName("Login-LAT-Service", new LoginLATServiceAVPBuilder());

    private static class TunnelPreferenceAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelPreference((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName TunnelPreference = new com.intellinet.diameter.Unsigned32Name("Tunnel-Preference", new TunnelPreferenceAVPBuilder());

    private static class AcctDelayTimeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AcctDelayTime((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName AcctDelayTime = new com.intellinet.diameter.Unsigned32Name("Acct-Delay-Time", new AcctDelayTimeAVPBuilder());

    private static class NASIPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NASIPAddress((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName NASIPAddress = new com.intellinet.diameter.OctetStringName("NAS-IP-Address", new NASIPAddressAVPBuilder());

    private static class TunnelServerEndpointAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelServerEndpoint((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName TunnelServerEndpoint = new com.intellinet.diameter.UTF8StringName("Tunnel-Server-Endpoint", new TunnelServerEndpointAVPBuilder());

    private static class NASIdentifierAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NASIdentifier((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName NASIdentifier = new com.intellinet.diameter.UTF8StringName("NAS-Identifier", new NASIdentifierAVPBuilder());

    private static class ARAPSecurityAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ARAPSecurity((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName ARAPSecurity = new com.intellinet.diameter.Unsigned32Name("ARAP-Security", new ARAPSecurityAVPBuilder());

    private static class FramedIPv6PoolAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPv6Pool((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedIPv6Pool = new com.intellinet.diameter.OctetStringName("Framed-IPv6-Pool", new FramedIPv6PoolAVPBuilder());

    private static class NASPortTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NASPortType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName NASPortType = new com.intellinet.diameter.EnumeratedName("NAS-Port-Type", new NASPortTypeAVPBuilder());

    private static class ReplyMessageAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ReplyMessage((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ReplyMessage = new com.intellinet.diameter.UTF8StringName("Reply-Message", new ReplyMessageAVPBuilder());

    private static class TunnelPrivateGroupIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelPrivateGroupId((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TunnelPrivateGroupId = new com.intellinet.diameter.OctetStringName("Tunnel-Private-Group-Id", new TunnelPrivateGroupIdAVPBuilder());

    private static class CHAPAlgorithmAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CHAPAlgorithm((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName CHAPAlgorithm = new com.intellinet.diameter.EnumeratedName("CHAP-Algorithm", new CHAPAlgorithmAVPBuilder());

    private static class ARAPPasswordAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ARAPPassword((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ARAPPassword = new com.intellinet.diameter.OctetStringName("ARAP-Password", new ARAPPasswordAVPBuilder());

    private static class CallingStationIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CallingStationId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CallingStationId = new com.intellinet.diameter.UTF8StringName("Calling-Station-Id", new CallingStationIdAVPBuilder());

    private static class ARAPFeaturesAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ARAPFeatures((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ARAPFeatures = new com.intellinet.diameter.OctetStringName("ARAP-Features", new ARAPFeaturesAVPBuilder());

    private static class FramedCompressionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedCompression((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName FramedCompression = new com.intellinet.diameter.EnumeratedName("Framed-Compression", new FramedCompressionAVPBuilder());

    private static class FramedRoutingAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedRouting((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName FramedRouting = new com.intellinet.diameter.EnumeratedName("Framed-Routing", new FramedRoutingAVPBuilder());

    private static class FramedIPNetmaskAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPNetmask((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedIPNetmask = new com.intellinet.diameter.OctetStringName("Framed-IP-Netmask", new FramedIPNetmaskAVPBuilder());

    private static class TunnelServerAuthIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelServerAuthId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName TunnelServerAuthId = new com.intellinet.diameter.UTF8StringName("Tunnel-Server-Auth-Id", new TunnelServerAuthIdAVPBuilder());

    private static class FramedInterfaceIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedInterfaceId((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName FramedInterfaceId = new com.intellinet.diameter.Unsigned64Name("Framed-Interface-Id", new FramedInterfaceIdAVPBuilder());

    private static class CalledStationIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CalledStationId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CalledStationId = new com.intellinet.diameter.UTF8StringName("Called-Station-Id", new CalledStationIdAVPBuilder());

    private static class AccountingAuthMethodAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingAuthMethod((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AccountingAuthMethod = new com.intellinet.diameter.EnumeratedName("Accounting-Auth-Method", new AccountingAuthMethodAVPBuilder());

    private static class AccountingOutputPacketsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingOutputPackets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingOutputPackets = new com.intellinet.diameter.Unsigned64Name("Accounting-Output-Packets", new AccountingOutputPacketsAVPBuilder());

    private static class ServiceTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ServiceType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName ServiceType = new com.intellinet.diameter.EnumeratedName("Service-Type", new ServiceTypeAVPBuilder());

    private static class TunnelMediumTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelMediumType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TunnelMediumType = new com.intellinet.diameter.EnumeratedName("Tunnel-Medium-Type", new TunnelMediumTypeAVPBuilder());

    private static class QoSFilterRuleAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new QoSFilterRule((com.intellinet.diameter.IPFilterRuleData)impl);
        }
    }

    public static final AttributeName QoSFilterRule = new com.intellinet.diameter.IPFilterRuleName("QoS-Filter-Rule", new QoSFilterRuleAVPBuilder());

    private static class CHAPResponseAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CHAPResponse((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CHAPResponse = new com.intellinet.diameter.OctetStringName("CHAP-Response", new CHAPResponseAVPBuilder());

    private static class CHAPChallengeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CHAPChallenge((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName CHAPChallenge = new com.intellinet.diameter.OctetStringName("CHAP-Challenge", new CHAPChallengeAVPBuilder());

    private static class AccountingInputOctetsAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AccountingInputOctets((com.intellinet.diameter.Unsigned64Data)impl);
        }
    }

    public static final AttributeName AccountingInputOctets = new com.intellinet.diameter.Unsigned64Name("Accounting-Input-Octets", new AccountingInputOctetsAVPBuilder());

    private static class FramedAppletalkNetworkAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedAppletalkNetwork((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FramedAppletalkNetwork = new com.intellinet.diameter.Unsigned32Name("Framed-Appletalk-Network", new FramedAppletalkNetworkAVPBuilder());

    private static class FramedAppletalkLinkAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedAppletalkLink((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName FramedAppletalkLink = new com.intellinet.diameter.Unsigned32Name("Framed-Appletalk-Link", new FramedAppletalkLinkAVPBuilder());

    private static class NASPortIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NASPortId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName NASPortId = new com.intellinet.diameter.UTF8StringName("NAS-Port-Id", new NASPortIdAVPBuilder());

    private static class FramedProtocolAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedProtocol((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName FramedProtocol = new com.intellinet.diameter.EnumeratedName("Framed-Protocol", new FramedProtocolAVPBuilder());

    private static class FramedIPv6RouteAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPv6Route((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName FramedIPv6Route = new com.intellinet.diameter.UTF8StringName("Framed-IPv6-Route", new FramedIPv6RouteAVPBuilder());

    private static class CHAPAuthAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CHAPAuth((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName CHAPAuth = new com.intellinet.diameter.GroupedName("CHAP-Auth", new CHAPAuthAVPBuilder());

    private static class ARAPSecurityDataAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ARAPSecurityData((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ARAPSecurityData = new com.intellinet.diameter.OctetStringName("ARAP-Security-Data", new ARAPSecurityDataAVPBuilder());

    private static class OriginAAAProtocolAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new OriginAAAProtocol((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName OriginAAAProtocol = new com.intellinet.diameter.EnumeratedName("Origin-AAA-Protocol", new OriginAAAProtocolAVPBuilder());

    private static class AcctAuthenticAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new AcctAuthentic((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName AcctAuthentic = new com.intellinet.diameter.EnumeratedName("Acct-Authentic", new AcctAuthenticAVPBuilder());

    private static class UserPasswordAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new UserPassword((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName UserPassword = new com.intellinet.diameter.OctetStringName("User-Password", new UserPasswordAVPBuilder());

    private static class PasswordRetryAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new PasswordRetry((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName PasswordRetry = new com.intellinet.diameter.Unsigned32Name("Password-Retry", new PasswordRetryAVPBuilder());

    private static class FilterIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FilterId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName FilterId = new com.intellinet.diameter.UTF8StringName("Filter-Id", new FilterIdAVPBuilder());

    private static class FramedIPAddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new FramedIPAddress((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName FramedIPAddress = new com.intellinet.diameter.OctetStringName("Framed-IP-Address", new FramedIPAddressAVPBuilder());

    private static class TunnelTypeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelType((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName TunnelType = new com.intellinet.diameter.EnumeratedName("Tunnel-Type", new TunnelTypeAVPBuilder());

    private static class ConfigurationTokenAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ConfigurationToken((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName ConfigurationToken = new com.intellinet.diameter.OctetStringName("Configuration-Token", new ConfigurationTokenAVPBuilder());

    private static class LoginIPHostAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginIPHost((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LoginIPHost = new com.intellinet.diameter.OctetStringName("Login-IP-Host", new LoginIPHostAVPBuilder());

    private static class LoginLATPortAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginLATPort((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LoginLATPort = new com.intellinet.diameter.OctetStringName("Login-LAT-Port", new LoginLATPortAVPBuilder());

    private static class CallbackIdAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new CallbackId((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName CallbackId = new com.intellinet.diameter.UTF8StringName("Callback-Id", new CallbackIdAVPBuilder());

    private static class PromptAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new Prompt((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName Prompt = new com.intellinet.diameter.EnumeratedName("Prompt", new PromptAVPBuilder());

    private static class ConnectInfoAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new ConnectInfo((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName ConnectInfo = new com.intellinet.diameter.UTF8StringName("Connect-Info", new ConnectInfoAVPBuilder());

    private static class NASIPv6AddressAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new NASIPv6Address((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName NASIPv6Address = new com.intellinet.diameter.OctetStringName("NAS-IPv6-Address", new NASIPv6AddressAVPBuilder());

    private static class LoginTCPPortAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginTCPPort((com.intellinet.diameter.Unsigned32Data)impl);
        }
    }

    public static final AttributeName LoginTCPPort = new com.intellinet.diameter.Unsigned32Name("Login-TCP-Port", new LoginTCPPortAVPBuilder());

    private static class LoginLATNodeAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new LoginLATNode((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName LoginLATNode = new com.intellinet.diameter.OctetStringName("Login-LAT-Node", new LoginLATNodeAVPBuilder());

    private static class TunnelClientEndpointAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelClientEndpoint((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName TunnelClientEndpoint = new com.intellinet.diameter.UTF8StringName("Tunnel-Client-Endpoint", new TunnelClientEndpointAVPBuilder());

    private static class TunnelPasswordAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TunnelPassword((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName TunnelPassword = new com.intellinet.diameter.OctetStringName("Tunnel-Password", new TunnelPasswordAVPBuilder());
}

