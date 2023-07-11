package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Server-Endpoint AVP (AVP Code 67) is of type UTF8String
 * and contains the address of the server end of the tunnel. It MAY be
 * used in an authorization request as a hint to the server that a
 * specific endpoint is desired, but the server is not required to honor
 * the hint in the corresponding response.
 */
public class TunnelServerEndpoint extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TunnelServerEndpoint with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelServerEndpoint(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    TunnelServerEndpoint(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
