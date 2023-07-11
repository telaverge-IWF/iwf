package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The SGSN-Number AVP is of type OctetString and it shall contain the ISDN
 * number of the SGSN. For further details on the encoding of this AVP, see
 * 3GPP TS 23.003[3].
 */
public class SGSNNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SGSNNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public SGSNNumber(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SGSNNumber(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
