package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The MSISDN AVP is of type OctetString and contains the user's MSISDN.
 * See 3GPP TS 23.003 [3] for the structure of MSISDN.
 */
public class MSISDN extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a MSISDN with the given value.
     *
     * @param value - the value of the AVP
     */
    public MSISDN(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    MSISDN(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
