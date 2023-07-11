package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class RecordRoute extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RecordRoute with the given value.
     *
     * @param value - the value of the AVP
     */
    public RecordRoute(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    RecordRoute(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
