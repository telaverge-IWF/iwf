package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class VisitedNetworkIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a VisitedNetworkIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public VisitedNetworkIdentifier(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    VisitedNetworkIdentifier(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
