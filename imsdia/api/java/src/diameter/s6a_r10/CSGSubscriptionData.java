package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The PDN-GW-Address AVP is of type Address. This AVP contains an IP address of the 
 * PDN GW and this IP address shall be used as the PDN GW IP address
 */
public class CSGSubscriptionData extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CSGSubscriptionData.
     */
    public CSGSubscriptionData() {}

    CSGSubscriptionData(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the CSGId.
     */
    public CSGId getCSGId() throws NoSuchAttributeException {
        return (CSGId)_data.getContainer().get(S6a_r10AttributeName.CSGId, 0);
    }

    /**
     * Sets the CSGId.
     *
     * @param avp - the attribute value
     */
    public void setCSGId(CSGId avp) {
        _data.getContainer().add(S6a_r10AttributeName.CSGId, avp.getData(), true);
    }

    /**
     * Tests whether there is any ExpirationDate.
     */
    public boolean containsExpirationDate() {
        return _data.getContainer().contains(S6a_r10AttributeName.ExpirationDate);
    }

    /**
     * Gets the ExpirationDate.
     */
    public ExpirationDate getExpirationDate() throws NoSuchAttributeException {
        return (ExpirationDate)_data.getContainer().get(S6a_r10AttributeName.ExpirationDate, 0);
    }

    /**
     * Sets the ExpirationDate.
     *
     * @param avp - the attribute value
     */
    public void setExpirationDate(ExpirationDate avp) {
        _data.getContainer().add(S6a_r10AttributeName.ExpirationDate, avp.getData(), true);
    }

    /**
     * Returns number of ServiceSelection instances.
     */
    public int countServiceSelection() {
        return _data.getContainer().count(S6a_r10AttributeName.ServiceSelection);
    }

    /**
     * Gets one ServiceSelection.
     *
     * @param index - the index of the attribute to return
     */
    public ServiceSelection getServiceSelection(int index) throws NoSuchAttributeException {
        return (ServiceSelection)_data.getContainer().get(S6a_r10AttributeName.ServiceSelection, index);
    }

    /**
     * Adds one ServiceSelection.
     *
     * @param avp - the attribute value
     */
    public void addServiceSelection(ServiceSelection avp) {
        _data.getContainer().add(S6a_r10AttributeName.ServiceSelection, avp.getData(), false);
    }

    /**
     * Returns number of extra AVP instances.
     */
    public int countExtra() {
        return _data.getContainer().count(AttributeName.AVP);
    }

    /**
     * Returns number of extra AVP instances that match the given attribute name.
     *
     * @param name - the attribute to count
     */
    public int countExtra(AttributeName name) {
        return _data.getContainer().countExtra(name);
    }

    /**
     * Gets an extra AVP that matches the given attribute name.
     *
     * @param name - the attribute to return
     * @param index - the index of the attribute to return
     */
    public AVP getExtra(AttributeName name, int index) throws NoSuchAttributeException {
        return _data.getContainer().getExtra(name, index);
    }

    /**
     * Adds one extra AVP.
     *
     * @param avp - the attribute value
     */
    public void addExtra(AVP avp) {
        _data.getContainer().add(AttributeName.AVP, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    CSGId:");
            try {
                sb.append(getCSGId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsExpirationDate()) {
            sb.append("    ExpirationDate:");
            try {
                sb.append(getExpirationDate()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServiceSelection(); ++i) {
            sb.append("    ServiceSelection:");
            try {
                sb.append(getServiceSelection(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
