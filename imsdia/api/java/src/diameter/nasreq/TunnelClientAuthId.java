package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Client-Auth-Id AVP (AVP Code 90) is of type UTF8String and
 * specifies the name used by the tunnel initiator during the
 * authentication phase of tunnel establishment. It MAY be used in an
 * authorization request as a hint to the server that a specific
 * preference is desired, but the server is not required to honor the
 * hint in the corresponding response. This AVP MUST be present in the
 * authorization response if an authentication name other than the
 * default is desired. This AVP SHOULD be included in the Accounting-
 * Request messages pertaining to the tunneled session.
 */
public class TunnelClientAuthId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TunnelClientAuthId with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelClientAuthId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    TunnelClientAuthId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
