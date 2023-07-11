package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Message-Size AVP is of type Unsigned32 and holds the total size in bytes of the MM calculated according
 * to TS 23.140.
 */
public class MessageSize extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a MessageSize with the given value.
     *
     * @param value - the value of the AVP
     */
    public MessageSize(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    MessageSize(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
