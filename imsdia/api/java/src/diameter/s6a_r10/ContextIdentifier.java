package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The Context-Identifier AVP is of type Unsigned32.
 */
public class ContextIdentifier extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ContextIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContextIdentifier(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ContextIdentifier(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
