package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * SDP-Session-Description AVP is of type UTF8String and holds the content of a "attribute-line" 
 * (i=,c=,b=,k=,a=,etc.) related to a session.
 */
public class SDPSessionDescription extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SDPSessionDescription with the given value.
     *
     * @param value - the value of the AVP
     */
    public SDPSessionDescription(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    SDPSessionDescription(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
