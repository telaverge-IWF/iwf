package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Alternate-Charged-Party-Address AVP (AVP code 1280) is of type 
 * UTF8String and  holds  the address of the alternate charged party 
 * determined by an AS at IMS session initiation.
 */
public class AlternateChargedPartyAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AlternateChargedPartyAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public AlternateChargedPartyAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    AlternateChargedPartyAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
