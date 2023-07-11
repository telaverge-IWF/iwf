package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-IPv6-Route AVP (AVP Code 99) is of type UTF8String and
 * contains the ASCII routing information to be configured for the user
 * on the NAS. Zero or more of these AVPs MAY be present in an
 * authorization response.
 * The string MUST contain an IPv6 address prefix followed by a slash
 * and a decimal length specifier stating how many high order bits of
 * the prefix should be used. This is followed by a space, a gateway
 * address in hexadecimal notation, a space, and one or more metrics
 * separated by spaces;
 */
public class FramedIPv6Route extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPv6Route with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPv6Route(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    FramedIPv6Route(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
