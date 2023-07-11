package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The STN-SR AVP is of type OctetString and contains the Session Transfer Number for SRVCC. 
 * See 3GPP TS 23.003 [3] for the structure of STN-SR.
 */
public class STNSR extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a STNSR with the given value.
     *
     * @param value - the value of the AVP
     */
    public STNSR(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    STNSR(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
