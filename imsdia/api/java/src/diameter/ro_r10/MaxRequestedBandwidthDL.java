package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Max-Requested-Bandwidth-DL AVP (AVP code 515) is of type Unsigned32, and
 * it indicates the maximum requested bandwidth in bits per second for a
 * downlink IP flow. The bandwidth contains all the overhead coming from the
 * IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload.
 */
public class MaxRequestedBandwidthDL extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a MaxRequestedBandwidthDL with the given value.
     *
     * @param value - the value of the AVP
     */
    public MaxRequestedBandwidthDL(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    MaxRequestedBandwidthDL(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
