package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Max -Bandwidth-UL AVP (AVP code 516) is of type Unsigned32, and it indicates 
 * the maximum requested bandwidth in bits per second for an uplink IP flow. 
 * The bandwidth contains all the overhead coming from the IP-layer and the layers above,
 * e.g. IP, UDP, RTP and RTP payload.
 */
public class MaxRequestedBandwidthUL extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a MaxRequestedBandwidthUL with the given value.
     *
     * @param value - the value of the AVP
     */
    public MaxRequestedBandwidthUL(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    MaxRequestedBandwidthUL(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
