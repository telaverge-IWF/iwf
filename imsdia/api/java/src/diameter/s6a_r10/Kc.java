package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The Kc is of type OctetString, and contains the Ciphering Key (Kc).
 */
public class Kc extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Kc with the given value.
     *
     * @param value - the value of the AVP
     */
    public Kc(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Kc(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
