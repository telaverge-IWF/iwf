package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * User-Session-ID AVP is of type UTF8String and holds the session identifier. For a SIP session the 
 * User-Session-ID contains the SIP Call ID
 */
public class UserSessionID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a UserSessionID with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserSessionID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    UserSessionID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
