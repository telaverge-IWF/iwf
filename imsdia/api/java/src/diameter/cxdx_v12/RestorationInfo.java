package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class RestorationInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RestorationInfo.
     */
    public RestorationInfo() {}

    RestorationInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the Path.
     */
    public Path getPath() throws NoSuchAttributeException {
        return (Path)_data.getContainer().get(Cxdx_v12AttributeName.Path, 0);
    }

    /**
     * Sets the Path.
     *
     * @param avp - the attribute value
     */
    public void setPath(Path avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.Path, avp.getData(), true);
    }

    /**
     * Gets the Contact.
     */
    public Contact getContact() throws NoSuchAttributeException {
        return (Contact)_data.getContainer().get(Cxdx_v12AttributeName.Contact, 0);
    }

    /**
     * Sets the Contact.
     *
     * @param avp - the attribute value
     */
    public void setContact(Contact avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.Contact, avp.getData(), true);
    }

    /**
     * Tests whether there is any SubscriptionInfo.
     */
    public boolean containsSubscriptionInfo() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SubscriptionInfo);
    }

    /**
     * Gets the SubscriptionInfo.
     */
    public SubscriptionInfo getSubscriptionInfo() throws NoSuchAttributeException {
        return (SubscriptionInfo)_data.getContainer().get(Cxdx_v12AttributeName.SubscriptionInfo, 0);
    }

    /**
     * Sets the SubscriptionInfo.
     *
     * @param avp - the attribute value
     */
    public void setSubscriptionInfo(SubscriptionInfo avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SubscriptionInfo, avp.getData(), true);
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
        sb.append("    Path:");
            try {
                sb.append(getPath()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    Contact:");
            try {
                sb.append(getContact()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsSubscriptionInfo()) {
            sb.append("    SubscriptionInfo:");
            try {
                sb.append(getSubscriptionInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
