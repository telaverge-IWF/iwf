package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The IK is of type OctetString, and contains the Integrity Key (IK).
 */
public class IK extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a IK with the given value.
     *
     * @param value - the value of the AVP
     */
    public IK(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    IK(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
