package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Calling-Party-Address is of type UTF8String and holds the address (Public User ID,SIP URL,E.164 etc.)
 * of the party initiating a session.In IMS charging the address is obtained from P-Asserted-Identity header.
 */
public class CallingPartyAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CallingPartyAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public CallingPartyAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CallingPartyAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
