package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-Client-External-ID AVP is of type UTF8String and holds identification of the external LCS Client.
 */
public class LCSClientExternalID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LCSClientExternalID with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSClientExternalID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    LCSClientExternalID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
