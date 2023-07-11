package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Local-Sequence-Number  AVP (AVP code 2063) is of type Unsigned32 and 
 * holds the service data container sequence number : increased by 1 for each 
 * service data container closed.
 */
public class LocalSequenceNumber extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a LocalSequenceNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public LocalSequenceNumber(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    LocalSequenceNumber(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
