package diameter.s6a;

import com.intellinet.diameter.*;


public class TraceEventList extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TraceEventList with the given value.
     *
     * @param value - the value of the AVP
     */
    public TraceEventList(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TraceEventList(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
