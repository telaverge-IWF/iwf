package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 *The Number-Of-Received-Talk-Bursts AVP (AVP code 1282) is of type Unsigned32 and holds the number of the received talk bursts
 */
public class NumberOfReceivedTalkBursts extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfReceivedTalkBursts with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfReceivedTalkBursts(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfReceivedTalkBursts(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
