package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-IPX-Network AVP (AVP Code 23) is of type Unsigned32 and
 * contains the IPX Network number to be configured for the user. It
 * MAY be used in an authorization request as a hint to the server that
 * a specific address is desired, but the server is not required to
 * honor the hint in the corresponding response.
 */
public class FramedIPXNetwork extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPXNetwork with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPXNetwork(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    FramedIPXNetwork(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
