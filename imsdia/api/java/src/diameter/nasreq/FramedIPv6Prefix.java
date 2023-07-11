package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-IPv6-Prefix AVP (AVP Code 97) is of type OctetString and 
 * contains the IPv6 prefix to be configured for the user. One or more AVPs
 * MAY be used in authorization requests as hint to the server that 
 * specific IPv6 prefixes are desired, but the server is not required to 
 * honor the hint in the corresponding response.
 */
public class FramedIPv6Prefix extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPv6Prefix with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPv6Prefix(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedIPv6Prefix(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
