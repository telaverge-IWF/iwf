package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The G-S-U-Pool-Identifier AVP (AVP Code 453) is of type Unsigned32 and 
 * identifies a credit pool within the session.
 */
public class GSUPoolIdentifier extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a GSUPoolIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public GSUPoolIdentifier(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    GSUPoolIdentifier(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
