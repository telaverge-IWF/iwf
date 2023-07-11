package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SM-Protocol-ID AVP (AVP code 2013) is of type Octet String and holds an indication of the protocol used for the SM.
 */
public class SMProtocolID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SMProtocolID with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMProtocolID(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SMProtocolID(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
