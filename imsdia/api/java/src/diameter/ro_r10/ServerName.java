package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Server-Name 3 is of type UTF8String. This AVP contains a SIP-URL (as defined in IETF RFC 3261 and IETF
 * RFC 2396), used to identify a SIP server (e.g. S-CSCF name).
 */
public class ServerName extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ServerName with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServerName(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ServerName(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
