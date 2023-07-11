package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The CHAP-Ident AVP (AVP Code 404) is of type OctetString and contains the 1
 * octet CHAP Identifier used in the computation of the CHAP response [PPPCHAP].
 */
public class CHAPIdent extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CHAPIdent with the given value.
     *
     * @param value - the value of the AVP
     */
    public CHAPIdent(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CHAPIdent(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
