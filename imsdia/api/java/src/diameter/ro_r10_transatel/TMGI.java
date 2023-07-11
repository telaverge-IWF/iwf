package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * TMGI AVP is of type OctetString and contains the Temporary Mobile Group Identity allocated to a 
 * particular MBMS bearer service. TMGI use and structure is specified in 3GPP TS 23.003.
 */
public class TMGI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TMGI with the given value.
     *
     * @param value - the value of the AVP
     */
    public TMGI(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TMGI(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
