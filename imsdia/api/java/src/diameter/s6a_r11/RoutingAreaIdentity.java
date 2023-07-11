package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class RoutingAreaIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RoutingAreaIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public RoutingAreaIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    RoutingAreaIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
