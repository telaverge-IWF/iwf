package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * 3GPP-SGSN-MCC-MNC AVP is of type UTF8String. It contains the MCC and MNC extracted from 
 * the RAI within the Create PDP Context Request or Update PDP Context Request message.
 */
public class Ro3GPPSGSNMCCMNC extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPSGSNMCCMNC with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPSGSNMCCMNC(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPSGSNMCCMNC(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
