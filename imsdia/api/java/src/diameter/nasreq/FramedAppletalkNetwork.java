package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-AppleTalk-Network AVP (AVP Code 38) is of type Unsigned32
 * and contains the AppleTalk Network number that the NAS should probe
 * to allocate an AppleTalk node for the user. This AVP MUST only be
 * present in an authorization response and is never used when the user
 * is not another router. Multiple instances of this AVP indicate that
 * the NAS may probe, using any of the network numbers specified.
 */
public class FramedAppletalkNetwork extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a FramedAppletalkNetwork with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedAppletalkNetwork(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    FramedAppletalkNetwork(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
