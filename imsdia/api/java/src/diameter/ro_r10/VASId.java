package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * VAS-Id AVP is of type UTF8String. It contains the identification of a Value Added Service.
 */
public class VASId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a VASId with the given value.
     *
     * @param value - the value of the AVP
     */
    public VASId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    VASId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
