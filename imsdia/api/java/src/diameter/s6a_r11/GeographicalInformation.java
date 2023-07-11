package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class GeographicalInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a GeographicalInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public GeographicalInformation(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    GeographicalInformation(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
