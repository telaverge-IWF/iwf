package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Received-Talk-Burst-Volume AVP (AVP code 1285) is of type Unsigned32 and holds the volume in bytes of  the received talk bursts.
 */
public class ReceivedTalkBurstVolume extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ReceivedTalkBurstVolume with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReceivedTalkBurstVolume(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ReceivedTalkBurstVolume(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
