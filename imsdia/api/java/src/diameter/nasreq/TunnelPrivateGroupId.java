package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Private-Group-Id AVP (AVP Code 81) is of type OctetString
 * and contains the group Id for a particular tunneled session. The
 * Tunnel-Private-Group-Id AVP MAY be included in an authorization
 * request if the tunnel initiator can predetermine the group resulting
 * from a particular connection. It SHOULD be included in the
 * authorization response if this tunnel session is to be treated as
 * belonging to a particular private group. Private groups may be used
 * to associate a tunneled session with a particular group of users.
 * For example, it MAY be used to facilitate routing of unregistered IP
 * addresses through a particular interface. This AVP SHOULD be
 * included in the Accounting-Request messages that pertain to the
 * tunneled session.
 */
public class TunnelPrivateGroupId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TunnelPrivateGroupId with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelPrivateGroupId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TunnelPrivateGroupId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
