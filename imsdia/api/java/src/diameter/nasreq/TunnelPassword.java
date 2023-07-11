package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Password AVP (AVP Code 69) is of type OctetString and may
 * contain a password to be used to authenticate to a remote server.
 * The Tunnel-Password AVP contains sensitive information. This value
 * is not protected in the same manner as RADIUS [RADTunnels].
 * As required in [BASE], Diameter messages are encrypted by using IPsec
 * or TLS. The Tunnel-Password AVP SHOULD NOT be used in untrusted
 * proxy environments without encrypting it by using end-to-end security
 * techniques, such as CMS Security [DiamCMS].
 */
public class TunnelPassword extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TunnelPassword with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelPassword(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TunnelPassword(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
