package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The NAS-IP-Address AVP (AVP Code 4) [RADIUS] is of type OctetString
 * and contains the IP Address of the NAS providing service to the user.
 * This AVP SHOULD only be added by a RADIUS/Diameter Translation Agent.
 * When this AVP is present, the Origin-Host AVP identifies the NAS
 * providing service to the user.
 * Diameter agents and servers MUST check whether the NAS-IP-Address AVP
 * corresponds to an entry in the Route-Record AVP. This is done by
 * doing a reverse lookup (PTR RR) for the NAS-IP-Address to retrieve
 * the corresponding FQDN, and by checking for a match with the Route-
 * Record AVP. If no match is found, then an error is logged, but no
 * other action is taken.
 */
public class NASIPAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a NASIPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public NASIPAddress(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    NASIPAddress(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
