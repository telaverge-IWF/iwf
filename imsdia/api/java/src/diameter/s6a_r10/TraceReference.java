package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
  *  See 3GPP 29272 section 7.3.64 for details.
  */
public class TraceReference extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TraceReference with the given value.
     *
     * @param value - the value of the AVP
     */
    public TraceReference(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TraceReference(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
