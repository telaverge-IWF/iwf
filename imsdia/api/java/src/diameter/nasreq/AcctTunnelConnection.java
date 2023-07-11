package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Acct-Tunnel-Connection AVP (AVP Code 68) is of type OctetString
 * and contains the identifier assigned to the tunnel session. This
 * AVP, along with the Tunnel-Client-Endpoint and Tunnel-Server-Endpoint
 * AVPs, may be used to provide a means to uniquely identify a tunnel
 * session for auditing purposes.
 */
public class AcctTunnelConnection extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AcctTunnelConnection with the given value.
     *
     * @param value - the value of the AVP
     */
    public AcctTunnelConnection(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    AcctTunnelConnection(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
