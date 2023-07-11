package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Received-Talk-Burst-Time AVP (AVP code 1284) is of  type Unsigned32 and holds the duration in seconds of  the received talk bursts.
 */
public class ReceivedTalkBurstTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ReceivedTalkBurstTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReceivedTalkBurstTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ReceivedTalkBurstTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
