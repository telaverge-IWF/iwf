package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Service-Identifier AVP is of type Unsigned32 (AVP Code 439) and contains
 * the identifier of a service. The specific service the request relates to is
 * uniquely identified by the combination of Service-Context-Id and 
 * Service-Identifier AVPs.
 */
public class ServiceIdentifier extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ServiceIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceIdentifier(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ServiceIdentifier(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
