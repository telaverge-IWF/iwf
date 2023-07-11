package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The NAS-IPv6-Address AVP (AVP Code 95) [RADIUSIPv6] is of type
 * OctetString and contains the IPv6 Address of the NAS providing
 * service to the user. This AVP SHOULD only be added by a
 * RADIUS/Diameter Translation Agent. When this AVP is present, the
 * Origin-Host AVP identifies the NAS providing service to the user.
 */
public class NASIPv6Address extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a NASIPv6Address with the given value.
     *
     * @param value - the value of the AVP
     */
    public NASIPv6Address(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    NASIPv6Address(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
