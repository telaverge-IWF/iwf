package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Service-Specific-Info AVP (AVP Code 1249) is of type Grouped and 
 * holds service specific data if and as provided by an Application Server
 * or a PCEF only for pre-defined PCC rules.
 */
public class ServiceSpecificInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServiceSpecificInfo.
     */
    public ServiceSpecificInfo() {}

    ServiceSpecificInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any ServiceSpecificData.
     */
    public boolean containsServiceSpecificData() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServiceSpecificData);
    }

    /**
     * Gets the ServiceSpecificData.
     */
    public ServiceSpecificData getServiceSpecificData() throws NoSuchAttributeException {
        return (ServiceSpecificData)_data.getContainer().get(Ro_r10AttributeName.ServiceSpecificData, 0);
    }

    /**
     * Sets the ServiceSpecificData.
     *
     * @param avp - the attribute value
     */
    public void setServiceSpecificData(ServiceSpecificData avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceSpecificData, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceSpecificType.
     */
    public boolean containsServiceSpecificType() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServiceSpecificType);
    }

    /**
     * Gets the ServiceSpecificType.
     */
    public ServiceSpecificType getServiceSpecificType() throws NoSuchAttributeException {
        return (ServiceSpecificType)_data.getContainer().get(Ro_r10AttributeName.ServiceSpecificType, 0);
    }

    /**
     * Sets the ServiceSpecificType.
     *
     * @param avp - the attribute value
     */
    public void setServiceSpecificType(ServiceSpecificType avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceSpecificType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsServiceSpecificData()) {
            sb.append("    ServiceSpecificData:");
            try {
                sb.append(getServiceSpecificData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceSpecificType()) {
            sb.append("    ServiceSpecificType:");
            try {
                sb.append(getServiceSpecificType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
