package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Aux-Applic-Info AVP is of type UTF8String and holds additional application/implementation specific
 * control information.
 */
public class AuxApplicInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AuxApplicInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public AuxApplicInfo(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    AuxApplicInfo(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
