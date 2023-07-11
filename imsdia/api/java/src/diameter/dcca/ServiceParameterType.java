package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Service-Parameter-Type AVP is of type Unsigned32 (AVP Code 441) and 
 * defines the type of the service event specific parameter (e.g.,it can be the
 * end-user location or service name). The different parameters and their types
 * are service specific,and the meanings of these parameters are not defined in
 * this document. Whoever allocates the Service-Context-Id (i.e., unique 
 * identifier of a service-specific document) is also responsible for assigning
 * Service-Parameter-Type values for the service and ensuring their uniqueness 
 * within the given service. 
 */
public class ServiceParameterType extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ServiceParameterType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceParameterType(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ServiceParameterType(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
