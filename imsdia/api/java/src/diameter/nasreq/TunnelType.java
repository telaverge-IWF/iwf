package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Type AVP (AVP Code 64) is of type Enumerated and contains
 * the tunneling protocol(s) to be used (in the case of a tunnel
 * initiator) or in use (in the case of a tunnel terminator). It MAY be
 * used in an authorization request as a hint to the server that a
 * specific tunnel type is desired, but the server is not required to
 * honor the hint in the corresponding response. The Tunnel-Type AVP SHOULD
 * also be included in Accounting-Request messages.
 */
public class TunnelType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PPTP(1),
        L2F(2),
        L2TP(3),
        ATMP(4),
        VTP(5),
        AH(6),
        IP_IP(7),
        MIN_IP_IP(8),
        N_ESP(9),
        GRE(10),
        DVS(11),
        IP_in_IP(12),
        VLAN(13);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a TunnelType with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    TunnelType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
