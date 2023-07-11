package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class ServiceType extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServiceType.
     */
    public ServiceType() {}

    ServiceType(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ServiceTypeIdentity.
     */
    public ServiceTypeIdentity getServiceTypeIdentity() throws NoSuchAttributeException {
        return (ServiceTypeIdentity)_data.getContainer().get(S6a_r11AttributeName.ServiceTypeIdentity, 0);
    }

    /**
     * Sets the ServiceTypeIdentity.
     *
     * @param avp - the attribute value
     */
    public void setServiceTypeIdentity(ServiceTypeIdentity avp) {
        _data.getContainer().add(S6a_r11AttributeName.ServiceTypeIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any GMLCRestriction.
     */
    public boolean containsGMLCRestriction() {
        return _data.getContainer().contains(S6a_r11AttributeName.GMLCRestriction);
    }

    /**
     * Gets the GMLCRestriction.
     */
    public GMLCRestriction getGMLCRestriction() throws NoSuchAttributeException {
        return (GMLCRestriction)_data.getContainer().get(S6a_r11AttributeName.GMLCRestriction, 0);
    }

    /**
     * Sets the GMLCRestriction.
     *
     * @param avp - the attribute value
     */
    public void setGMLCRestriction(GMLCRestriction avp) {
        _data.getContainer().add(S6a_r11AttributeName.GMLCRestriction, avp.getData(), true);
    }

    /**
     * Tests whether there is any NotificationToUEUser.
     */
    public boolean containsNotificationToUEUser() {
        return _data.getContainer().contains(S6a_r11AttributeName.NotificationToUEUser);
    }

    /**
     * Gets the NotificationToUEUser.
     */
    public NotificationToUEUser getNotificationToUEUser() throws NoSuchAttributeException {
        return (NotificationToUEUser)_data.getContainer().get(S6a_r11AttributeName.NotificationToUEUser, 0);
    }

    /**
     * Sets the NotificationToUEUser.
     *
     * @param avp - the attribute value
     */
    public void setNotificationToUEUser(NotificationToUEUser avp) {
        _data.getContainer().add(S6a_r11AttributeName.NotificationToUEUser, avp.getData(), true);
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
        sb.append("    ServiceTypeIdentity:");
            try {
                sb.append(getServiceTypeIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsGMLCRestriction()) {
            sb.append("    GMLCRestriction:");
            try {
                sb.append(getGMLCRestriction()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNotificationToUEUser()) {
            sb.append("    NotificationToUEUser:");
            try {
                sb.append(getNotificationToUEUser()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
