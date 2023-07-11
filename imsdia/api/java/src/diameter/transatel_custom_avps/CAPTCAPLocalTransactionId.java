package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPTCAPLocalTransactionId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPTCAPLocalTransactionId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPTCAPLocalTransactionId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CAPTCAPLocalTransactionId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
