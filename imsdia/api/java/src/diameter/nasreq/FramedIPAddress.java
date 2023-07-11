package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-IP-Address AVP (AVP Code 8) is of type OctetString and contains
 * an IPv4 address of the type specified in attribute value to be configured
 * for the user. It MAY be used in an authorization request as a hint to server
 * that a specific address is desired, but the server is not required to honor
 * the hint in the corresponding response.
 * Two values have special significance: 0xFFFFFFFF and 0xFFFFFFFE. The 
 * value 0xFFFFFFFF indicates that the NAS should allow the user to select
 * an address (i.e:negotiated). The value 0xFFFFFFFE indicates that NAS
 * should select an address for the user (e.g:assigned from a pool of
 * addresses kept by NAS).
 */
public class FramedIPAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPAddress(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedIPAddress(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
