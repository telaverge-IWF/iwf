package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The MMTel-Information AVP (AVP code 2030) is of type Grouped. Its purpose 
 * is to allow the transmission of additional MMtel  service specific 
 * information elements. It holds MMTel supplementary services invoked during 
 * MMTel service.
 */
public class MMTelInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MMTelInformation.
     */
    public MMTelInformation() {}

    MMTelInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of SupplementaryService instances.
     */
    public int countSupplementaryService() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.SupplementaryService);
    }

    /**
     * Gets one SupplementaryService.
     *
     * @param index - the index of the attribute to return
     */
    public SupplementaryService getSupplementaryService(int index) throws NoSuchAttributeException {
        return (SupplementaryService)_data.getContainer().get(Ro_r10_transatelAttributeName.SupplementaryService, index);
    }

    /**
     * Adds one SupplementaryService.
     *
     * @param avp - the attribute value
     */
    public void addSupplementaryService(SupplementaryService avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SupplementaryService, avp.getData(), false);
    }

    /**
     * Tests whether there is any SubscriberRole.
     */
    public boolean containsSubscriberRole() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SubscriberRole);
    }

    /**
     * Gets the SubscriberRole.
     */
    public SubscriberRole getSubscriberRole() throws NoSuchAttributeException {
        return (SubscriberRole)_data.getContainer().get(Ro_r10_transatelAttributeName.SubscriberRole, 0);
    }

    /**
     * Sets the SubscriberRole.
     *
     * @param avp - the attribute value
     */
    public void setSubscriberRole(SubscriberRole avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SubscriberRole, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        for (int i = 0; i < countSupplementaryService(); ++i) {
            sb.append("    SupplementaryService:");
            try {
                sb.append(getSupplementaryService(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSubscriberRole()) {
            sb.append("    SubscriberRole:");
            try {
                sb.append(getSubscriberRole()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
