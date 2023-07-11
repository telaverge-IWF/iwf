package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Token-Text AVP is of type UTF8String and contains extension information for the Message-Class AVP.
 */
public class TokenText extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TokenText with the given value.
     *
     * @param value - the value of the AVP
     */
    public TokenText(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    TokenText(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
