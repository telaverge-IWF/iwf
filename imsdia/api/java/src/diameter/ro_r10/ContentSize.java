package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Content-size AVP is of type Unsigned32 and indicates the size in bytes of the specified content type.
 */
public class ContentSize extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ContentSize with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContentSize(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ContentSize(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
