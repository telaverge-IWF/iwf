package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Port-Limit AVP (AVP Code 62) is of type Unsigned32 and sets the
 * maximum number of ports the NAS provides to the user. It MAY be used
 * in an authentication and/or authorization request as a hint to the
 * server that multilink PPP [PPPMP] service is desired, but the server
 * is not required to honor the hint in the corresponding response.
 */
public class PortLimit extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PortLimit with the given value.
     *
     * @param value - the value of the AVP
     */
    public PortLimit(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PortLimit(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
