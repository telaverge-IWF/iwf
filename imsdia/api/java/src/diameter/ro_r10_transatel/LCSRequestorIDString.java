package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-Requestor-ID-String AVP is of type UTF8String and contains the identification of the Requestor
 * and can be e.g MSISDN or logical name.
 */
public class LCSRequestorIDString extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LCSRequestorIDString with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSRequestorIDString(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    LCSRequestorIDString(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
