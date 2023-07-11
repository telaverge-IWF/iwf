package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * 3GPP-PDP-Type AVP is of type Unsigned32 and it denotes the type of PDP
 * context e.g IP or PPP.
 */
public class Ro3GPPPDPType extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a Ro3GPPPDPType with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPPDPType(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    Ro3GPPPDPType(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
