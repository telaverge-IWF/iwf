package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class TrackingAreaIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TrackingAreaIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public TrackingAreaIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TrackingAreaIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
