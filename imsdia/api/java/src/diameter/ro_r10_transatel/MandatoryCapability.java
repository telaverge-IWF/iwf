package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Mandatory-Capability AVP is of type Unsigned32. The value included in this AVP can be used to represent a
 * single determined mandatory capability of an S-CSCF. Each mandatory capability available in an individual operator¡¯s
 * network shall be allocated a unique value. The allocation of these values to individual capabilities is an operator issue. */
public class MandatoryCapability extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a MandatoryCapability with the given value.
     *
     * @param value - the value of the AVP
     */
    public MandatoryCapability(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    MandatoryCapability(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
