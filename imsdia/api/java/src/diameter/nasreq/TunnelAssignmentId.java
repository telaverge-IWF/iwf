package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Assignment-Id AVP (AVP Code 82) is of type OctetString and
 * is used to indicate to the tunnel initiator the particular tunnel to
 * which a session is to be assigned. Some tunneling protocols, such as
 * [PPTP] and [L2TP], allow for sessions between the same two tunnel
 * endpoints to be multiplexed over the same tunnel and also for a given
 * session to use its own dedicated tunnel. This attribute provides a
 * mechanism for Diameter to inform the tunnel initiator (e.g., PAC,
 * LAC) whether to assign the session to a multiplexed tunnel or to a
 * separate tunnel. Furthermore, it allows for sessions sharing
 * multiplexed tunnels to be assigned to different multiplexed tunnels.
 */
public class TunnelAssignmentId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TunnelAssignmentId with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelAssignmentId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TunnelAssignmentId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
