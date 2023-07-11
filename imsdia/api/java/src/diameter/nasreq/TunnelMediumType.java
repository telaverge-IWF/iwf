package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Medium-Type AVP (AVP Code 65) is of type Enumerated and
 * contains the transport medium to use when creating a tunnel for
 * protocols (such as L2TP) that can operate over multiple transports.
 * It MAY be used in an authorization request as a hint to the server
 * that a specific medium is desired, but the server is not required to
 * honor the hint in the corresponding response.
 */
public class TunnelMediumType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        IPv4(1),
        IPv6(2),
        NSAP(3),
        HDLC(4),
        BBN(5),
        CANON_802(6),
        E_163_POTS(7),
        E_164(8),
        F_69(9),
        X_121(10),
        IPX(11),
        APPLETALK(12),
        DECNET_IV(13),
        BANYAN_VINES(14),
        E_164_NSAP(15);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a TunnelMediumType with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelMediumType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    TunnelMediumType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
