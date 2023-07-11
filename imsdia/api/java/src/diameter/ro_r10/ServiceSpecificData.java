package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Service-Specific-Data AVP (AVP Code 863) is of type UTF8String and 
 * holds the value of the Service-Specific-Data.
 */
public class ServiceSpecificData extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ServiceSpecificData with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceSpecificData(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ServiceSpecificData(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
