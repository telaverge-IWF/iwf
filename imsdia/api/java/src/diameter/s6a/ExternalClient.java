package diameter.s6a;

import com.intellinet.diameter.*;


public class ExternalClient extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ExternalClient.
     */
    public ExternalClient() {}

    ExternalClient(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ClientIdentity.
     */
    public ClientIdentity getClientIdentity() throws NoSuchAttributeException {
        return (ClientIdentity)_data.getContainer().get(S6aAttributeName.ClientIdentity, 0);
    }

    /**
     * Sets the ClientIdentity.
     *
     * @param avp - the attribute value
     */
    public void setClientIdentity(ClientIdentity avp) {
        _data.getContainer().add(S6aAttributeName.ClientIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any GMLCRestriction.
     */
    public boolean containsGMLCRestriction() {
        return _data.getContainer().contains(S6aAttributeName.GMLCRestriction);
    }

    /**
     * Gets the GMLCRestriction.
     */
    public GMLCRestriction getGMLCRestriction() throws NoSuchAttributeException {
        return (GMLCRestriction)_data.getContainer().get(S6aAttributeName.GMLCRestriction, 0);
    }

    /**
     * Sets the GMLCRestriction.
     *
     * @param avp - the attribute value
     */
    public void setGMLCRestriction(GMLCRestriction avp) {
        _data.getContainer().add(S6aAttributeName.GMLCRestriction, avp.getData(), true);
    }

    /**
     * Tests whether there is any NotificationToUEUser.
     */
    public boolean containsNotificationToUEUser() {
        return _data.getContainer().contains(S6aAttributeName.NotificationToUEUser);
    }

    /**
     * Gets the NotificationToUEUser.
     */
    public NotificationToUEUser getNotificationToUEUser() throws NoSuchAttributeException {
        return (NotificationToUEUser)_data.getContainer().get(S6aAttributeName.NotificationToUEUser, 0);
    }

    /**
     * Sets the NotificationToUEUser.
     *
     * @param avp - the attribute value
     */
    public void setNotificationToUEUser(NotificationToUEUser avp) {
        _data.getContainer().add(S6aAttributeName.NotificationToUEUser, avp.getData(), true);
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
        sb.append("    ClientIdentity:");
            try {
                sb.append(getClientIdentity()).append('\n');
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
