package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The Guaranteed-Bitrate-DL AVP (AVP code 1025) is of type Unsigned32,
  * and it indicates the guaranteed bitrate in bits per second for a downlink
  * service data flow. The bandwidth contains all the overhead coming from the
  * IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload.
 */
public class GuaranteedBitrateDL extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a GuaranteedBitrateDL with the given value.
     *
     * @param value - the value of the AVP
     */
    public GuaranteedBitrateDL(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    GuaranteedBitrateDL(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
