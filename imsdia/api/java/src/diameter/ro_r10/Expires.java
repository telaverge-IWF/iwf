package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Expires AVP is of type Unsigned32 and holds the content of the "Expires" header.
 */
public class Expires extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a Expires with the given value.
     *
     * @param value - the value of the AVP
     */
    public Expires(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    Expires(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
