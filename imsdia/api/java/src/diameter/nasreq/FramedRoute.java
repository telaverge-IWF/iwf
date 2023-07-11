package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-Route AVP (AVP Code 22) is of type UTF8String and contains
 * the ASCII routing information to be configured for the user on the
 * NAS. Zero or more of these AVPs MAY be present in an authorization
 * response.
 * The string MUST contain a destination prefix in dotted quad form
 * optionally followed by a slash and a decimal length specifier stating
 * how many high-order bits of the prefix should be used. This is
 * followed by a space, a gateway address in dotted quad form, a space,
 * and one or more metrics separated by spaces; for example,
 * "192.168.1.0/24 192.168.1.1 1".
 */
public class FramedRoute extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedRoute with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedRoute(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    FramedRoute(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
