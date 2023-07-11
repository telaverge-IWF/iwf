package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Content-Length AVP is of type Unsigned32 and holds the size of the message-body.
 */
public class ContentLength extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ContentLength with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContentLength(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ContentLength(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
