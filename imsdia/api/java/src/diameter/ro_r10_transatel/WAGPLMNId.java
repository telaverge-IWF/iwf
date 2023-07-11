package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * WAG-PLMN-Id is of type OctetString and contains the WAG PLMN Id( MCC and MNC). Coding of
 * this AVP is same as 3GPP-MCC-MNC coding described in 3GPP TS 29.061.
 */
public class WAGPLMNId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a WAGPLMNId with the given value.
     *
     * @param value - the value of the AVP
     */
    public WAGPLMNId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    WAGPLMNId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
