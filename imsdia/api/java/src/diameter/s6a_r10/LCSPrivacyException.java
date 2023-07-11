package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class LCSPrivacyException extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LCSPrivacyException.
     */
    public LCSPrivacyException() {}

    LCSPrivacyException(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the SSCode.
     */
    public SSCode getSSCode() throws NoSuchAttributeException {
        return (SSCode)_data.getContainer().get(S6a_r10AttributeName.SSCode, 0);
    }

    /**
     * Sets the SSCode.
     *
     * @param avp - the attribute value
     */
    public void setSSCode(SSCode avp) {
        _data.getContainer().add(S6a_r10AttributeName.SSCode, avp.getData(), true);
    }

    /**
     * Gets the SSStatus.
     */
    public SSStatus getSSStatus() throws NoSuchAttributeException {
        return (SSStatus)_data.getContainer().get(S6a_r10AttributeName.SSStatus, 0);
    }

    /**
     * Sets the SSStatus.
     *
     * @param avp - the attribute value
     */
    public void setSSStatus(SSStatus avp) {
        _data.getContainer().add(S6a_r10AttributeName.SSStatus, avp.getData(), true);
    }

    /**
     * Tests whether there is any NotificationToUEUser.
     */
    public boolean containsNotificationToUEUser() {
        return _data.getContainer().contains(S6a_r10AttributeName.NotificationToUEUser);
    }

    /**
     * Gets the NotificationToUEUser.
     */
    public NotificationToUEUser getNotificationToUEUser() throws NoSuchAttributeException {
        return (NotificationToUEUser)_data.getContainer().get(S6a_r10AttributeName.NotificationToUEUser, 0);
    }

    /**
     * Sets the NotificationToUEUser.
     *
     * @param avp - the attribute value
     */
    public void setNotificationToUEUser(NotificationToUEUser avp) {
        _data.getContainer().add(S6a_r10AttributeName.NotificationToUEUser, avp.getData(), true);
    }

    /**
     * Returns number of ExternalClient instances.
     */
    public int countExternalClient() {
        return _data.getContainer().count(S6a_r10AttributeName.ExternalClient);
    }

    /**
     * Gets one ExternalClient.
     *
     * @param index - the index of the attribute to return
     */
    public ExternalClient getExternalClient(int index) throws NoSuchAttributeException {
        return (ExternalClient)_data.getContainer().get(S6a_r10AttributeName.ExternalClient, index);
    }

    /**
     * Adds one ExternalClient.
     *
     * @param avp - the attribute value
     */
    public void addExternalClient(ExternalClient avp) {
        _data.getContainer().add(S6a_r10AttributeName.ExternalClient, avp.getData(), false);
    }

    /**
     * Returns number of PLMNClient instances.
     */
    public int countPLMNClient() {
        return _data.getContainer().count(S6a_r10AttributeName.PLMNClient);
    }

    /**
     * Gets one PLMNClient.
     *
     * @param index - the index of the attribute to return
     */
    public PLMNClient getPLMNClient(int index) throws NoSuchAttributeException {
        return (PLMNClient)_data.getContainer().get(S6a_r10AttributeName.PLMNClient, index);
    }

    /**
     * Adds one PLMNClient.
     *
     * @param avp - the attribute value
     */
    public void addPLMNClient(PLMNClient avp) {
        _data.getContainer().add(S6a_r10AttributeName.PLMNClient, avp.getData(), false);
    }

    /**
     * Returns number of ServiceType instances.
     */
    public int countServiceType() {
        return _data.getContainer().count(S6a_r10AttributeName.ServiceType);
    }

    /**
     * Gets one ServiceType.
     *
     * @param index - the index of the attribute to return
     */
    public ServiceType getServiceType(int index) throws NoSuchAttributeException {
        return (ServiceType)_data.getContainer().get(S6a_r10AttributeName.ServiceType, index);
    }

    /**
     * Adds one ServiceType.
     *
     * @param avp - the attribute value
     */
    public void addServiceType(ServiceType avp) {
        _data.getContainer().add(S6a_r10AttributeName.ServiceType, avp.getData(), false);
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
        sb.append("    SSCode:");
            try {
                sb.append(getSSCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    SSStatus:");
            try {
                sb.append(getSSStatus()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsNotificationToUEUser()) {
            sb.append("    NotificationToUEUser:");
            try {
                sb.append(getNotificationToUEUser()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countExternalClient(); ++i) {
            sb.append("    ExternalClient:");
            try {
                sb.append(getExternalClient(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countPLMNClient(); ++i) {
            sb.append("    PLMNClient:");
            try {
                sb.append(getPLMNClient(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServiceType(); ++i) {
            sb.append("    ServiceType:");
            try {
                sb.append(getServiceType(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
