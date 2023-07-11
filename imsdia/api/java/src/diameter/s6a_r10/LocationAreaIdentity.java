package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class LocationAreaIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LocationAreaIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public LocationAreaIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LocationAreaIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
