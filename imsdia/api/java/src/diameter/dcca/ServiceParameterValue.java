package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Service-Parameter-Value AVP is of type OctetString (AVP Code 442) and 
 * contains the value of the service parameter type.
 */
public class ServiceParameterValue extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ServiceParameterValue with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceParameterValue(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ServiceParameterValue(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
