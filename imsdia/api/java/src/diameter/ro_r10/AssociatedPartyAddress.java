package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Associated-Party-Address AVP (AVP code 2035) is of type UTF8String and 
 * is used for MMTel supplementary service. It holds the address (SIP URI or 
 * TEL URI) of the user, the MMTel supplementary service is provided to :   
 * the "forwarding party" for CDIV, the "transferor" for ECT.
 */
public class AssociatedPartyAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AssociatedPartyAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public AssociatedPartyAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    AssociatedPartyAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
