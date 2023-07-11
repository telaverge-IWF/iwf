package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Service-Specific-Type AVP (AVP Code 1257) is of type Unsigned32 and holds the type of the Service-Specific-Data.
 */
public class ServiceSpecificType extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ServiceSpecificType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceSpecificType(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ServiceSpecificType(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
