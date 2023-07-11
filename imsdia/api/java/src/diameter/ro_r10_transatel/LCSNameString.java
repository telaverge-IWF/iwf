package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-Name-String AVP is of type UTF8String and contains the LCS Client name.
 */
public class LCSNameString extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LCSNameString with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSNameString(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    LCSNameString(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
