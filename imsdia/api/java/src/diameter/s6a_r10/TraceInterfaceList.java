package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class TraceInterfaceList extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TraceInterfaceList with the given value.
     *
     * @param value - the value of the AVP
     */
    public TraceInterfaceList(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TraceInterfaceList(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
