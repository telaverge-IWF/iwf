package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Called-Party-Address is of type UTF8String and holds the address (Public User ID,SIP URL,E.164 etc.)
 * of the party to whom a session is established.
 */
public class CalledPartyAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CalledPartyAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public CalledPartyAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CalledPartyAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
