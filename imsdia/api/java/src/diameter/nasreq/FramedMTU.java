package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-MTU AVP (AVP Code 12) is of type Unsigned32 and contains
 * the Maximum Transmission Unit to be configured for the user, when it
 * is not negotiated by some other means (such as PPP). This AVP SHOULD
 * only be present in authorization responses. The MTU value MUST be in
 * the range from 64 to 65535.
 */
public class FramedMTU extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a FramedMTU with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedMTU(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    FramedMTU(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
