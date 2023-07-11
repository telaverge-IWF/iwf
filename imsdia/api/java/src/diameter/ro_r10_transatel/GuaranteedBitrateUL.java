package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Guaranteed -Bitrate-UL AVP (AVP code 1026) is of type Unsigned32, and
 * it indicates the guaranteed bitrate in bits per second for an uplink service data flow.
 * The bandwidth contains all the overhead coming from the IP-layer and the layers above,
 * e.g. IP, UDP, RTP and RTP payload.
 */
public class GuaranteedBitrateUL extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a GuaranteedBitrateUL with the given value.
     *
     * @param value - the value of the AVP
     */
    public GuaranteedBitrateUL(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    GuaranteedBitrateUL(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
