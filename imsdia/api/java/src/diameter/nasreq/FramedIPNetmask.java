package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-IP-Netmask AVP (AVP Code 9) is of type OctetString and
 * contains the four octets of the IPv4 netmask to be configured for the
 * user when the user is a router to a network. It MAY be used in an
 * authorization request as a hint to the server that a specific netmask
 * is desired, but the server is not required to honor the hint in the
 * corresponding response. This AVP MUST be present in a response if
 * the request included this AVP with a value of 0xFFFFFFFF.
 */
public class FramedIPNetmask extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPNetmask with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPNetmask(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedIPNetmask(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
