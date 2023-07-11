package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-APN AVP is of type UTF8String and contains the APN of the LCS Client.
 */
public class LCSAPN extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LCSAPN with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSAPN(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    LCSAPN(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
