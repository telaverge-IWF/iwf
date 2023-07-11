package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class ServiceTypeIdentity extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ServiceTypeIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceTypeIdentity(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ServiceTypeIdentity(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
