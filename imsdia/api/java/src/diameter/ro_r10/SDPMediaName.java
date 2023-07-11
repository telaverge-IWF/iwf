package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * SDP-Media-Name AVP is of type UTF8String and holds the content of a "m=" line in the SDP data.
 */
public class SDPMediaName extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SDPMediaName with the given value.
     *
     * @param value - the value of the AVP
     */
    public SDPMediaName(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    SDPMediaName(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
