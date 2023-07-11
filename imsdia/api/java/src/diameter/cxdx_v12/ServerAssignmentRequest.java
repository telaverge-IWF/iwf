package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Server-Assignment-Request (SAR) command, indicated by the Command-Code field set to 301 and the <tt>R</tt> bit set
 * in the Command Flags field, is sent by a Diameter Multimedia client to a Diameter Multimedia server in order to
 * request it to store the name of the server that is currently serving the user.
 */
public class ServerAssignmentRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new ServerAssignmentRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public ServerAssignmentRequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 301, 16777216);
    }

    /**
     * Constructs a ServerAssignmentRequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public ServerAssignmentRequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a ServerAssignmentRequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public ServerAssignmentRequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    ServerAssignmentRequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Gets the VendorSpecificApplicationId.
     */
    public diameter.base.VendorSpecificApplicationId getVendorSpecificApplicationId() throws NoSuchAttributeException {
        return (diameter.base.VendorSpecificApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.VendorSpecificApplicationId, 0);
    }

    /**
     * Sets the VendorSpecificApplicationId.
     *
     * @param avp - the attribute value
     */
    public void setVendorSpecificApplicationId(diameter.base.VendorSpecificApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.VendorSpecificApplicationId, avp.getData(), true);
    }

    /**
     * Gets the AuthSessionState.
     */
    public diameter.base.AuthSessionState getAuthSessionState() throws NoSuchAttributeException {
        return (diameter.base.AuthSessionState)_data.getContainer().get(diameter.base.BaseAttributeName.AuthSessionState, 0);
    }

    /**
     * Sets the AuthSessionState.
     *
     * @param avp - the attribute value
     */
    public void setAuthSessionState(diameter.base.AuthSessionState avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthSessionState, avp.getData(), true);
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
     * Gets the ServerName.
     */
    public ServerName getServerName() throws NoSuchAttributeException {
        return (ServerName)_data.getContainer().get(Cxdx_v12AttributeName.ServerName, 0);
    }

    /**
     * Sets the ServerName.
     *
     * @param avp - the attribute value
     */
    public void setServerName(ServerName avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.ServerName, avp.getData(), true);
    }

    /**
     * Gets the ServerAssignmentType.
     */
    public ServerAssignmentType getServerAssignmentType() throws NoSuchAttributeException {
        return (ServerAssignmentType)_data.getContainer().get(Cxdx_v12AttributeName.ServerAssignmentType, 0);
    }

    /**
     * Sets the ServerAssignmentType.
     *
     * @param avp - the attribute value
     */
    public void setServerAssignmentType(ServerAssignmentType avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.ServerAssignmentType, avp.getData(), true);
    }

    /**
     * Gets the UserDataAlreadyAvailable.
     */
    public UserDataAlreadyAvailable getUserDataAlreadyAvailable() throws NoSuchAttributeException {
        return (UserDataAlreadyAvailable)_data.getContainer().get(Cxdx_v12AttributeName.UserDataAlreadyAvailable, 0);
    }

    /**
     * Sets the UserDataAlreadyAvailable.
     *
     * @param avp - the attribute value
     */
    public void setUserDataAlreadyAvailable(UserDataAlreadyAvailable avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.UserDataAlreadyAvailable, avp.getData(), true);
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
     * Tests whether there is any DestinationHost.
     */
    public boolean containsDestinationHost() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.DestinationHost);
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
     * Tests whether there is any WildcardedPublicIdentity.
     */
    public boolean containsWildcardedPublicIdentity() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.WildcardedPublicIdentity);
    }

    /**
     * Gets the WildcardedPublicIdentity.
     */
    public WildcardedPublicIdentity getWildcardedPublicIdentity() throws NoSuchAttributeException {
        return (WildcardedPublicIdentity)_data.getContainer().get(Cxdx_v12AttributeName.WildcardedPublicIdentity, 0);
    }

    /**
     * Sets the WildcardedPublicIdentity.
     *
     * @param avp - the attribute value
     */
    public void setWildcardedPublicIdentity(WildcardedPublicIdentity avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.WildcardedPublicIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any SCSCFRestorationInfo.
     */
    public boolean containsSCSCFRestorationInfo() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SCSCFRestorationInfo);
    }

    /**
     * Gets the SCSCFRestorationInfo.
     */
    public SCSCFRestorationInfo getSCSCFRestorationInfo() throws NoSuchAttributeException {
        return (SCSCFRestorationInfo)_data.getContainer().get(Cxdx_v12AttributeName.SCSCFRestorationInfo, 0);
    }

    /**
     * Sets the SCSCFRestorationInfo.
     *
     * @param avp - the attribute value
     */
    public void setSCSCFRestorationInfo(SCSCFRestorationInfo avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SCSCFRestorationInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any MultipleRegistrationIndication.
     */
    public boolean containsMultipleRegistrationIndication() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.MultipleRegistrationIndication);
    }

    /**
     * Gets the MultipleRegistrationIndication.
     */
    public MultipleRegistrationIndication getMultipleRegistrationIndication() throws NoSuchAttributeException {
        return (MultipleRegistrationIndication)_data.getContainer().get(Cxdx_v12AttributeName.MultipleRegistrationIndication, 0);
    }

    /**
     * Sets the MultipleRegistrationIndication.
     *
     * @param avp - the attribute value
     */
    public void setMultipleRegistrationIndication(MultipleRegistrationIndication avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.MultipleRegistrationIndication, avp.getData(), true);
    }

    /**
     * Tests whether there is any SessionPriority.
     */
    public boolean containsSessionPriority() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SessionPriority);
    }

    /**
     * Gets the SessionPriority.
     */
    public SessionPriority getSessionPriority() throws NoSuchAttributeException {
        return (SessionPriority)_data.getContainer().get(Cxdx_v12AttributeName.SessionPriority, 0);
    }

    /**
     * Sets the SessionPriority.
     *
     * @param avp - the attribute value
     */
    public void setSessionPriority(SessionPriority avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SessionPriority, avp.getData(), true);
    }

    /**
     * Returns number of SupportedFeatures instances.
     */
    public int countSupportedFeatures() {
        return _data.getContainer().count(Cxdx_v12AttributeName.SupportedFeatures);
    }

    /**
     * Gets one SupportedFeatures.
     *
     * @param index - the index of the attribute to return
     */
    public SupportedFeatures getSupportedFeatures(int index) throws NoSuchAttributeException {
        return (SupportedFeatures)_data.getContainer().get(Cxdx_v12AttributeName.SupportedFeatures, index);
    }

    /**
     * Adds one SupportedFeatures.
     *
     * @param avp - the attribute value
     */
    public void addSupportedFeatures(SupportedFeatures avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SupportedFeatures, avp.getData(), false);
    }

    /**
     * Returns number of PublicIdentity instances.
     */
    public int countPublicIdentity() {
        return _data.getContainer().count(Cxdx_v12AttributeName.PublicIdentity);
    }

    /**
     * Gets one PublicIdentity.
     *
     * @param index - the index of the attribute to return
     */
    public PublicIdentity getPublicIdentity(int index) throws NoSuchAttributeException {
        return (PublicIdentity)_data.getContainer().get(Cxdx_v12AttributeName.PublicIdentity, index);
    }

    /**
     * Adds one PublicIdentity.
     *
     * @param avp - the attribute value
     */
    public void addPublicIdentity(PublicIdentity avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.PublicIdentity, avp.getData(), false);
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

    public String toString() {
        StringBuffer sb = headerToStringBuffer().append(" {\n");
        sb.append("    SessionId:");
            try {
                sb.append(getSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[fixed but missing]\n");
            }
        sb.append("    VendorSpecificApplicationId:");
            try {
                sb.append(getVendorSpecificApplicationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AuthSessionState:");
            try {
                sb.append(getAuthSessionState()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
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
        sb.append("    ServerName:");
            try {
                sb.append(getServerName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ServerAssignmentType:");
            try {
                sb.append(getServerAssignmentType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    UserDataAlreadyAvailable:");
            try {
                sb.append(getUserDataAlreadyAvailable()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    DestinationRealm:");
            try {
                sb.append(getDestinationRealm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsDestinationHost()) {
            sb.append("    DestinationHost:");
            try {
                sb.append(getDestinationHost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserName()) {
            sb.append("    UserName:");
            try {
                sb.append(getUserName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsWildcardedPublicIdentity()) {
            sb.append("    WildcardedPublicIdentity:");
            try {
                sb.append(getWildcardedPublicIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSCSCFRestorationInfo()) {
            sb.append("    SCSCFRestorationInfo:");
            try {
                sb.append(getSCSCFRestorationInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMultipleRegistrationIndication()) {
            sb.append("    MultipleRegistrationIndication:");
            try {
                sb.append(getMultipleRegistrationIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSessionPriority()) {
            sb.append("    SessionPriority:");
            try {
                sb.append(getSessionPriority()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSupportedFeatures(); ++i) {
            sb.append("    SupportedFeatures:");
            try {
                sb.append(getSupportedFeatures(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countPublicIdentity(); ++i) {
            sb.append("    PublicIdentity:");
            try {
                sb.append(getPublicIdentity(i)).append('\n');
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
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }

    private void validate() throws WrongCommandTypeException {
        if (getCommandCode() != 301 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
