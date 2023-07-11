package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Service-Generic-Information AVP (AVP code 1256) is of type Grouped 
 * refer [TS32.299]. Its purpose is to allow the transmission of additional 
 * OMA service/enabler specific information elements which are common to 
 * different service/enablers.
 */
public class ServiceGenericInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServiceGenericInformation.
     */
    public ServiceGenericInformation() {}

    ServiceGenericInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any ApplicationServerID.
     */
    public boolean containsApplicationServerID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ApplicationServerID);
    }

    /**
     * Gets the ApplicationServerID.
     */
    public ApplicationServerID getApplicationServerID() throws NoSuchAttributeException {
        return (ApplicationServerID)_data.getContainer().get(Ro_r10_transatelAttributeName.ApplicationServerID, 0);
    }

    /**
     * Sets the ApplicationServerID.
     *
     * @param avp - the attribute value
     */
    public void setApplicationServerID(ApplicationServerID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ApplicationServerID, avp.getData(), true);
    }

    /**
     * Tests whether there is any ApplicationServiceType.
     */
    public boolean containsApplicationServiceType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ApplicationServiceType);
    }

    /**
     * Gets the ApplicationServiceType.
     */
    public ApplicationServiceType getApplicationServiceType() throws NoSuchAttributeException {
        return (ApplicationServiceType)_data.getContainer().get(Ro_r10_transatelAttributeName.ApplicationServiceType, 0);
    }

    /**
     * Sets the ApplicationServiceType.
     *
     * @param avp - the attribute value
     */
    public void setApplicationServiceType(ApplicationServiceType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ApplicationServiceType, avp.getData(), true);
    }

    /**
     * Tests whether there is any ApplicationSessionID.
     */
    public boolean containsApplicationSessionID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ApplicationSessionID);
    }

    /**
     * Gets the ApplicationSessionID.
     */
    public ApplicationSessionID getApplicationSessionID() throws NoSuchAttributeException {
        return (ApplicationSessionID)_data.getContainer().get(Ro_r10_transatelAttributeName.ApplicationSessionID, 0);
    }

    /**
     * Sets the ApplicationSessionID.
     *
     * @param avp - the attribute value
     */
    public void setApplicationSessionID(ApplicationSessionID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ApplicationSessionID, avp.getData(), true);
    }

    /**
     * Tests whether there is any DeliveryStatus.
     */
    public boolean containsDeliveryStatus() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.DeliveryStatus);
    }

    /**
     * Gets the DeliveryStatus.
     */
    public DeliveryStatus getDeliveryStatus() throws NoSuchAttributeException {
        return (DeliveryStatus)_data.getContainer().get(Ro_r10_transatelAttributeName.DeliveryStatus, 0);
    }

    /**
     * Sets the DeliveryStatus.
     *
     * @param avp - the attribute value
     */
    public void setDeliveryStatus(DeliveryStatus avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.DeliveryStatus, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsApplicationServerID()) {
            sb.append("    ApplicationServerID:");
            try {
                sb.append(getApplicationServerID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsApplicationServiceType()) {
            sb.append("    ApplicationServiceType:");
            try {
                sb.append(getApplicationServiceType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsApplicationSessionID()) {
            sb.append("    ApplicationSessionID:");
            try {
                sb.append(getApplicationSessionID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDeliveryStatus()) {
            sb.append("    DeliveryStatus:");
            try {
                sb.append(getDeliveryStatus()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
