package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class LocationInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LocationInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public LocationInformation(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LocationInformation(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
