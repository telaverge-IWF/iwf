package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * 3GPP-GGSN-MCC-MNC AVP is of type UTF8String. It contains the MCC and MNC of the 
 *  network the GGSN belongs to.
 */
public class Ro3GPPGGSNMCCMNC extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPGGSNMCCMNC with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPGGSNMCCMNC(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPGGSNMCCMNC(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
