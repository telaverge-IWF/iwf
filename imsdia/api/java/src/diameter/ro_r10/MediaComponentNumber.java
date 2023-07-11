package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Media-Component-Number AVP (AVP code 518) is of type Unsigned32, and it
 * contains the ordinal number of the media component, assigned according to
 * the rules in annex A of 3GPP2 X.S0013-013-0.
 */
public class MediaComponentNumber extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a MediaComponentNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public MediaComponentNumber(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    MediaComponentNumber(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
