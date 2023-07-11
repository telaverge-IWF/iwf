package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The Talk-Burst-Volume AVP (AVP code 1287) is of type Unsigned32 and holds 
  * the volume in bytes of  the sent talk bursts.
  */
public class TalkBurstVolume extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TalkBurstVolume with the given value.
     *
     * @param value - the value of the AVP
     */
    public TalkBurstVolume(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    TalkBurstVolume(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
