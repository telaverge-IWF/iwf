package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Refund-Information AVP (AVP code 1292) is of type OctetString and 
 * it conveys relevant information for the OCS application relative to 
 * refund mechanism. When refund mechanism is implemented in the OCS this 
 * AVP is included in the CCA of the previous IEC. This AVP must be used 
 * by the CTF in case of a refund scenario and thus must be included in 
 * the CCR for refund.
 */
public class RefundInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RefundInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public RefundInformation(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    RefundInformation(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
