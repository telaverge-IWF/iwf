package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Push-Profile-Request (PPR) command, indicated by the Command-Code field set to 305 and the <tt>R</tt> bit set in the
 * Command Flags field, is sent by a Diameter Multimedia server to a Diameter Multimedia client in order to update the subscription data and for SIP Digest 
 * authentication the authentication data of a multimedia user in the Diameter Multimedia client whenever a modification has occurred in the
 * subscription data that constitutes the data used by the client.
 */
public class PushProfileRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new PushProfileRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public PushProfileRequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 305, 16777216);
    }

    /**
     * Constructs a PushProfileRequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public PushProfileRequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a PushProfileRequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public PushProfileRequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    PushProfileRequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Tests whether there is any UserData.
     */
    public boolean containsUserData() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.UserData);
    }

    /**
     * Gets the UserData.
     */
    public UserData getUserData() throws NoSuchAttributeException {
        return (UserData)_data.getContainer().get(Cxdx_v12AttributeName.UserData, 0);
    }

    /**
     * Sets the UserData.
     *
     * @param avp - the attribute value
     */
    public void setUserData(UserData avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.UserData, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChargingInformation.
     */
    public boolean containsChargingInformation() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.ChargingInformation);
    }

    /**
     * Gets the ChargingInformation.
     */
    public ChargingInformation getChargingInformation() throws NoSuchAttributeException {
        return (ChargingInformation)_data.getContainer().get(Cxdx_v12AttributeName.ChargingInformation, 0);
    }

    /**
     * Sets the ChargingInformation.
     *
     * @param avp - the attribute value
     */
    public void setChargingInformation(ChargingInformation avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.ChargingInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPAuthDataItem.
     */
    public boolean containsSIPAuthDataItem() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SIPAuthDataItem);
    }

    /**
     * Gets the SIPAuthDataItem.
     */
    public SIPAuthDataItem getSIPAuthDataItem() throws NoSuchAttributeException {
        return (SIPAuthDataItem)_data.getContainer().get(Cxdx_v12AttributeName.SIPAuthDataItem, 0);
    }

    /**
     * Sets the SIPAuthDataItem.
     *
     * @param avp - the attribute value
     */
    public void setSIPAuthDataItem(SIPAuthDataItem avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SIPAuthDataItem, avp.getData(), true);
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
        sb.append("    DestinationHost:");
            try {
                sb.append(getDestinationHost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    DestinationRealm:");
            try {
                sb.append(getDestinationRealm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    UserName:");
            try {
                sb.append(getUserName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        for (int i = 0; i < countSupportedFeatures(); ++i) {
            sb.append("    SupportedFeatures:");
            try {
                sb.append(getSupportedFeatures(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserData()) {
            sb.append("    UserData:");
            try {
                sb.append(getUserData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsChargingInformation()) {
            sb.append("    ChargingInformation:");
            try {
                sb.append(getChargingInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPAuthDataItem()) {
            sb.append("    SIPAuthDataItem:");
            try {
                sb.append(getSIPAuthDataItem()).append('\n');
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
        if (getCommandCode() != 305 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}