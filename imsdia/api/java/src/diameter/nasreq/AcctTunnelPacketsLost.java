package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Acct-Tunnel-Packets-Lost AVP (AVP Code 86) is of type Unsigned32
 * and contains the number of packets lost on a given link.
 */
public class AcctTunnelPacketsLost extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a AcctTunnelPacketsLost with the given value.
     *
     * @param value - the value of the AVP
     */
    public AcctTunnelPacketsLost(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    AcctTunnelPacketsLost(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
