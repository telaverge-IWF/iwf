package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Location-Estimate AVP is of type UTF8String and contains an estimate of the location of an MS in the 
 * universal coordinates and the accuracy of the estimate.
 */
public class LocationEstimate extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LocationEstimate with the given value.
     *
     * @param value - the value of the AVP
     */
    public LocationEstimate(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    LocationEstimate(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
