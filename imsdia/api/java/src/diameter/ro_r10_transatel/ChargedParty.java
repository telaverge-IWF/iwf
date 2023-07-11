package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Charged-Party AVP (AVP code 857) is of type UTF8String and holds the address (Public User ID: SIP URI, TEL URI, etc.) of the party to be charged. 
 */
public class ChargedParty extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ChargedParty with the given value.
     *
     * @param value - the value of the AVP
     */
    public ChargedParty(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ChargedParty(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
