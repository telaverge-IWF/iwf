package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * 3GPP-IMSI-MCC-MNC AVP is of type UTF8String. It contains MCC and MNC extracted from the user's
 * IMSI (first 5 or 6 digits, as applicable from the presented IMSI).
 */
public class Ro3GPPIMSIMCCMNC extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPIMSIMCCMNC with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPIMSIMCCMNC(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPIMSIMCCMNC(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
