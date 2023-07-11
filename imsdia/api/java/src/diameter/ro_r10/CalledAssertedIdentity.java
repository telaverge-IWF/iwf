package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Called-Asserted-Identity AVP (AVP code 1250) is of type UTF8String and 
 * holds the address (Public User ID: SIP URI, E.164, etc.) of the finally 
 * asserted called party
 */
public class CalledAssertedIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CalledAssertedIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public CalledAssertedIdentity(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CalledAssertedIdentity(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
