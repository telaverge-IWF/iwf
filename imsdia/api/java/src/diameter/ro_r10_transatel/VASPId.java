package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * VASP-Id AVP is of type UTF8String. It contains the identification of a Value Added Service Provider.
 */
public class VASPId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a VASPId with the given value.
     *
     * @param value - the value of the AVP
     */
    public VASPId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    VASPId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
