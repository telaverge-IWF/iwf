package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class GeodeticInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a GeodeticInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public GeodeticInformation(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    GeodeticInformation(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
