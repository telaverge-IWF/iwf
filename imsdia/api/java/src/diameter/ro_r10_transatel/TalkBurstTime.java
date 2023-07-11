package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Talk-Burst-Time AVP (AVP code 1286) is of  type Unsigned32 and holds the duration in seconds of the sent talk bursts.
 */
public class TalkBurstTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TalkBurstTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public TalkBurstTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    TalkBurstTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
