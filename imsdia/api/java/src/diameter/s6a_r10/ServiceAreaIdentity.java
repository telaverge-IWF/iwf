package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class ServiceAreaIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ServiceAreaIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceAreaIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ServiceAreaIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
