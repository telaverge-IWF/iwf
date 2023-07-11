package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Re-Auth-Request (RAR), indicated by the Command-Code set to 258
 * and the message flags' 'R' bit set, may be sent by any server to the
 * access device that is providing session service, to request that the
 * user be re-authenticated and/or re-authorized.
 */
public class RARequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new RARequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public RARequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 258, 4);
    }

    /**
     * Constructs a RARequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public RARequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a RARequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public RARequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    RARequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
        super(data);
        validate();
    }

    /**
     * Gets the SessionId.
     */
    public diameter.base.SessionId getSessionId() throws NoSuchAttributeException {
        return (diameter.base.SessionId)_data.getContainer().get(diameter.base.BaseAttributeName.SessionId, 0);
    }

    /**
     * Sets the SessionId.
     *
     * @param avp - the attribute value
     */
    public void setSessionId(diameter.base.SessionId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.SessionId, avp.getData(), true);
    }

    /**
     * Gets the OriginHost.
     */
    public diameter.base.OriginHost getOriginHost() throws NoSuchAttributeException {
        return (diameter.base.OriginHost)_data.getContainer().get(diameter.base.BaseAttributeName.OriginHost, 0);
    }

    /**
     * Sets the OriginHost.
     *
     * @param avp - the attribute value
     */
    public void setOriginHost(diameter.base.OriginHost avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.OriginHost, avp.getData(), true);
    }

    /**
     * Gets the OriginRealm.
     */
    public diameter.base.OriginRealm getOriginRealm() throws NoSuchAttributeException {
        return (diameter.base.OriginRealm)_data.getContainer().get(diameter.base.BaseAttributeName.OriginRealm, 0);
    }

    /**
     * Sets the OriginRealm.
     *
     * @param avp - the attribute value
     */
    public void setOriginRealm(diameter.base.OriginRealm avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.OriginRealm, avp.getData(), true);
    }

    /**
     * Gets the DestinationRealm.
     */
    public diameter.base.DestinationRealm getDestinationRealm() throws NoSuchAttributeException {
        return (diameter.base.DestinationRealm)_data.getContainer().get(diameter.base.BaseAttributeName.DestinationRealm, 0);
    }

    /**
     * Sets the DestinationRealm.
     *
     * @param avp - the attribute value
     */
    public void setDestinationRealm(diameter.base.DestinationRealm avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.DestinationRealm, avp.getData(), true);
    }

    /**
     * Gets the DestinationHost.
     */
    public diameter.base.DestinationHost getDestinationHost() throws NoSuchAttributeException {
        return (diameter.base.DestinationHost)_data.getContainer().get(diameter.base.BaseAttributeName.DestinationHost, 0);
    }

    /**
     * Sets the DestinationHost.
     *
     * @param avp - the attribute value
     */
    public void setDestinationHost(diameter.base.DestinationHost avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.DestinationHost, avp.getData(), true);
    }

    /**
     * Gets the AuthApplicationId.
     */
    public diameter.base.AuthApplicationId getAuthApplicationId() throws NoSuchAttributeException {
        return (diameter.base.AuthApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.AuthApplicationId, 0);
    }

    /**
     * Sets the AuthApplicationId.
     *
     * @param avp - the attribute value
     */
    public void setAuthApplicationId(diameter.base.AuthApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthApplicationId, avp.getData(), true);
    }

    /**
     * Gets the ReAuthRequestType.
     */
    public diameter.base.ReAuthRequestType getReAuthRequestType() throws NoSuchAttributeException {
        return (diameter.base.ReAuthRequestType)_data.getContainer().get(diameter.base.BaseAttributeName.ReAuthRequestType, 0);
    }

    /**
     * Sets the ReAuthRequestType.
     *
     * @param avp - the attribute value
     */
    public void setReAuthRequestType(diameter.base.ReAuthRequestType avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ReAuthRequestType, avp.getData(), true);
    }

    /**
     * Tests whether there is any UserName.
     */
    public boolean containsUserName() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.UserName);
    }

    /**
     * Gets the UserName.
     */
    public diameter.base.UserName getUserName() throws NoSuchAttributeException {
        return (diameter.base.UserName)_data.getContainer().get(diameter.base.BaseAttributeName.UserName, 0);
    }

    /**
     * Sets the UserName.
     *
     * @param avp - the attribute value
     */
    public void setUserName(diameter.base.UserName avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.UserName, avp.getData(), true);
    }

    /**
     * Tests whether there is any OriginStateId.
     */
    public boolean containsOriginStateId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.OriginStateId);
    }

    /**
     * Gets the OriginStateId.
     */
    public diameter.base.OriginStateId getOriginStateId() throws NoSuchAttributeException {
        return (diameter.base.OriginStateId)_data.getContainer().get(diameter.base.BaseAttributeName.OriginStateId, 0);
    }

    /**
     * Sets the OriginStateId.
     *
     * @param avp - the attribute value
     */
    public void setOriginStateId(diameter.base.OriginStateId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.OriginStateId, avp.getData(), true);
    }

    /**
     * Returns number of ProxyInfo instances.
     */
    public int countProxyInfo() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.ProxyInfo);
    }

    /**
     * Gets one ProxyInfo.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.ProxyInfo getProxyInfo(int index) throws NoSuchAttributeException {
        return (diameter.base.ProxyInfo)_data.getContainer().get(diameter.base.BaseAttributeName.ProxyInfo, index);
    }

    /**
     * Adds one ProxyInfo.
     *
     * @param avp - the attribute value
     */
    public void addProxyInfo(diameter.base.ProxyInfo avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ProxyInfo, avp.getData(), false);
    }

    /**
     * Returns number of RouteRecord instances.
     */
    public int countRouteRecord() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.RouteRecord);
    }

    /**
     * Gets one RouteRecord.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.RouteRecord getRouteRecord(int index) throws NoSuchAttributeException {
        return (diameter.base.RouteRecord)_data.getContainer().get(diameter.base.BaseAttributeName.RouteRecord, index);
    }

    /**
     * Adds one RouteRecord.
     *
     * @param avp - the attribute value
     */
    public void addRouteRecord(diameter.base.RouteRecord avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RouteRecord, avp.getData(), false);
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

    /**
     * Tests whether there is any CCSubSessionId.
     */
    public boolean containsCCSubSessionId() {
        return _data.getContainer().contains(DccaAttributeName.CCSubSessionId);
    }

    /**
     * Gets the CCSubSessionId.
     */
    public CCSubSessionId getCCSubSessionId() throws NoSuchAttributeException {
        return (CCSubSessionId)_data.getContainer().get(DccaAttributeName.CCSubSessionId, 0);
    }

    /**
     * Sets the CCSubSessionId.
     *
     * @param avp - the attribute value
     */
    public void setCCSubSessionId(CCSubSessionId avp) {
        _data.getContainer().add(DccaAttributeName.CCSubSessionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any GSUPoolIdentifier.
     */
    public boolean containsGSUPoolIdentifier() {
        return _data.getContainer().contains(DccaAttributeName.GSUPoolIdentifier);
    }

    /**
     * Gets the GSUPoolIdentifier.
     */
    public GSUPoolIdentifier getGSUPoolIdentifier() throws NoSuchAttributeException {
        return (GSUPoolIdentifier)_data.getContainer().get(DccaAttributeName.GSUPoolIdentifier, 0);
    }

    /**
     * Sets the GSUPoolIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setGSUPoolIdentifier(GSUPoolIdentifier avp) {
        _data.getContainer().add(DccaAttributeName.GSUPoolIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceIdentifier.
     */
    public boolean containsServiceIdentifier() {
        return _data.getContainer().contains(DccaAttributeName.ServiceIdentifier);
    }

    /**
     * Gets the ServiceIdentifier.
     */
    public ServiceIdentifier getServiceIdentifier() throws NoSuchAttributeException {
        return (ServiceIdentifier)_data.getContainer().get(DccaAttributeName.ServiceIdentifier, 0);
    }

    /**
     * Sets the ServiceIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setServiceIdentifier(ServiceIdentifier avp) {
        _data.getContainer().add(DccaAttributeName.ServiceIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any RatingGroup.
     */
    public boolean containsRatingGroup() {
        return _data.getContainer().contains(DccaAttributeName.RatingGroup);
    }

    /**
     * Gets the RatingGroup.
     */
    public RatingGroup getRatingGroup() throws NoSuchAttributeException {
        return (RatingGroup)_data.getContainer().get(DccaAttributeName.RatingGroup, 0);
    }

    /**
     * Sets the RatingGroup.
     *
     * @param avp - the attribute value
     */
    public void setRatingGroup(RatingGroup avp) {
        _data.getContainer().add(DccaAttributeName.RatingGroup, avp.getData(), true);
    }

    public String toString() {
        StringBuffer sb = headerToStringBuffer().append(" {\n");
        sb.append("    SessionId:");
            try {
                sb.append(getSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[fixed but missing]\n");
            }
        sb.append("    OriginHost:");
            try {
                sb.append(getOriginHost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    OriginRealm:");
            try {
                sb.append(getOriginRealm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    DestinationRealm:");
            try {
                sb.append(getDestinationRealm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    DestinationHost:");
            try {
                sb.append(getDestinationHost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AuthApplicationId:");
            try {
                sb.append(getAuthApplicationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ReAuthRequestType:");
            try {
                sb.append(getReAuthRequestType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsUserName()) {
            sb.append("    UserName:");
            try {
                sb.append(getUserName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOriginStateId()) {
            sb.append("    OriginStateId:");
            try {
                sb.append(getOriginStateId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countProxyInfo(); ++i) {
            sb.append("    ProxyInfo:");
            try {
                sb.append(getProxyInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRouteRecord(); ++i) {
            sb.append("    RouteRecord:");
            try {
                sb.append(getRouteRecord(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCSubSessionId()) {
            sb.append("    CCSubSessionId:");
            try {
                sb.append(getCCSubSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGSUPoolIdentifier()) {
            sb.append("    GSUPoolIdentifier:");
            try {
                sb.append(getGSUPoolIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceIdentifier()) {
            sb.append("    ServiceIdentifier:");
            try {
                sb.append(getServiceIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRatingGroup()) {
            sb.append("    RatingGroup:");
            try {
                sb.append(getRatingGroup()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }

    private void validate() throws WrongCommandTypeException {
        if (getCommandCode() != 258 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
