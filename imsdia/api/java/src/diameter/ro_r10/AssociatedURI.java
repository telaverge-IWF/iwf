package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Associated-URI AVP (AVP code 856) is of type UTF8String and holds a 
 * non-barred public user identity (SIP URI or TEL URI) associated to the the 
 * public user identity under registration. This identity is obtained from 
 * the P-Associated-URI header of a 200 OK SIP response to a REGISTER request.
 * This AVP may appear several times when the P-Associated-URI header 
 * contains more than one public user identity.
 */
public class AssociatedURI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AssociatedURI with the given value.
     *
     * @param value - the value of the AVP
     */
    public AssociatedURI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    AssociatedURI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
