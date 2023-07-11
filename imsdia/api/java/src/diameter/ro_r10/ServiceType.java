package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
  * The Service-Type AVP (AVP Code 2031) is of type Unsigned32 and identifies 
  * the type of MMTel supplementary service. 
  */
public class ServiceType extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ServiceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceType(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ServiceType(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
