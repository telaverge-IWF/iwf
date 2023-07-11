package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPTCAPRemoteTransactionId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPTCAPRemoteTransactionId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPTCAPRemoteTransactionId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CAPTCAPRemoteTransactionId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
