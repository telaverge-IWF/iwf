package diameter.s13;

import com.intellinet.diameter.*;


/**
 * The MSISDN AVP is of type OctetString. This AVP contains an MSISDN, in international 
 * number format as described in ITU-T Rec E.164, encoded as a TBCD-string, i.e. digits 
 * from 0 through 9 are encoded 0000 to 1001; 1111 is used as a filler when there is an 
 * odd number of digits; bits 8 to 5 of octet n encode digit 2n; bits 4 to 1 of octet n 
 * encode digit 2(n-1)+1.
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
