package diameter.s6a;

import com.intellinet.diameter.*;


public class TraceNETypeList extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TraceNETypeList with the given value.
     *
     * @param value - the value of the AVP
     */
    public TraceNETypeList(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TraceNETypeList(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
