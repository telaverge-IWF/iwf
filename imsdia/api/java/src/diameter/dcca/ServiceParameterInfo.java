package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Service-Parameter-Info AVP (AVP Code 440)is of type Grouped and contains
 * service-specific information used for price calculation or rating. The 
 * Service-Parameter-Type AVP defines the service parameter type, and the i
 * Service-Parameter-Value AVP contains the parameter value.
 */
public class ServiceParameterInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServiceParameterInfo.
     */
    public ServiceParameterInfo() {}

    ServiceParameterInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ServiceParameterType.
     */
    public ServiceParameterType getServiceParameterType() throws NoSuchAttributeException {
        return (ServiceParameterType)_data.getContainer().get(DccaAttributeName.ServiceParameterType, 0);
    }

    /**
     * Sets the ServiceParameterType.
     *
     * @param avp - the attribute value
     */
    public void setServiceParameterType(ServiceParameterType avp) {
        _data.getContainer().add(DccaAttributeName.ServiceParameterType, avp.getData(), true);
    }

    /**
     * Gets the ServiceParameterValue.
     */
    public ServiceParameterValue getServiceParameterValue() throws NoSuchAttributeException {
        return (ServiceParameterValue)_data.getContainer().get(DccaAttributeName.ServiceParameterValue, 0);
    }

    /**
     * Sets the ServiceParameterValue.
     *
     * @param avp - the attribute value
     */
    public void setServiceParameterValue(ServiceParameterValue avp) {
        _data.getContainer().add(DccaAttributeName.ServiceParameterValue, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    ServiceParameterType:");
            try {
                sb.append(getServiceParameterType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ServiceParameterValue:");
            try {
                sb.append(getServiceParameterValue()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        return sb.append('}').toString();
    }
}
