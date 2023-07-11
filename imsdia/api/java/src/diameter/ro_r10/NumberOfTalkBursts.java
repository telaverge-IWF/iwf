package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Number-Of-Talk-Bursts AVP (AVP code 1283) is of type Unsigned32 and holds the number of the sent talk bursts.
 */
public class NumberOfTalkBursts extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfTalkBursts with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfTalkBursts(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfTalkBursts(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
