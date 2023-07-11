package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * SDP-Media-Description AVP is of type UTF8String and holds the content of a "attribute-line" 
 * (i=,c=,b=,k=,a=,etc.) related to a media component. The attributes are specifying the media
 * described in the SDP-Media-Name AVP.
 */
public class SDPMediaDescription extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SDPMediaDescription with the given value.
     *
     * @param value - the value of the AVP
     */
    public SDPMediaDescription(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    SDPMediaDescription(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
