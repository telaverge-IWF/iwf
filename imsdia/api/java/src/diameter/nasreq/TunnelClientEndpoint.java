package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Client-Endpoint AVP (AVP Code 66) is of type UTF8String
 * and contains the address of the initiator end of the tunnel. It MAY
 * be used in an authorization request as a hint to the server that a
 * specific endpoint is desired, but the server is not required to honor
 * the hint in the corresponding response.
 * This AVP SHOULD be included in the corresponding Accounting-Request
 * messages, in which case it indicates the address from which the
 * tunnel was initiated. This AVP, along with the Tunnel-Server-
 * Endpoint and Session-Id AVP [BASE], MAY be used to provide a globally
 * unique means to identify a tunnel for accounting and auditing
 * purposes.
 */
public class TunnelClientEndpoint extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TunnelClientEndpoint with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelClientEndpoint(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    TunnelClientEndpoint(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
