package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Server-Assignment-Answer (SAA) command, indicated by the Command-Code field set to 301 and the <tt>R</tt> bit
 * cleared in the Command Flags field, is sent by a server in response to the Server-Assignment-Request command. The
 * Result-Code or Experimental-Result AVP may contain one of the values defined in section 6.2 in addition to the values
 * defined in IETF RFC 3588 [6]. If Result-Code or Experimental-Result does not inform about an error, the User-Data
 * AVP shall contain the information that the S-CSCF needs to give service to the user.
 */
public class ServerAssignmentAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new ServerAssignmentAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public ServerAssignmentAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 301, 16777216);
    }

    /**
     * Constructs a ServerAssignmentAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public ServerAssignmentAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a ServerAssignmentAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public ServerAssignmentAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    ServerAssignmentAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Tests whether there is any ResultCode.
     */
    public boolean containsResultCode() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.ResultCode);
    }

    /**
     * Gets the ResultCode.
     */
    public diameter.base.ResultCode getResultCode() throws NoSuchAttributeException {
        return (diameter.base.ResultCode)_data.getContainer().get(diameter.base.BaseAttributeName.ResultCode, 0);
    }

    /**
     * Sets the ResultCode.
     *
     * @param avp - the attribute value
     */
    public void setResultCode(diameter.base.ResultCode avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ResultCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any ExperimentalResult.
     */
    public boolean containsExperimentalResult() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.ExperimentalResult);
    }

    /**
     * Gets the ExperimentalResult.
     */
    public diameter.base.ExperimentalResult getExperimentalResult() throws NoSuchAttributeException {
        return (diameter.base.ExperimentalResult)_data.getContainer().get(diameter.base.BaseAttributeName.ExperimentalResult, 0);
    }

    /**
     * Sets the ExperimentalResult.
     *
     * @param avp - the attribute value
     */
    public void setExperimentalResult(diameter.base.ExperimentalResult avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ExperimentalResult, avp.getData(), true);
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
     * Tests whether there is any AssociatedIdentities.
     */
    public boolean containsAssociatedIdentities() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.AssociatedIdentities);
    }

    /**
     * Gets the AssociatedIdentities.
     */
    public AssociatedIdentities getAssociatedIdentities() throws NoSuchAttributeException {
        return (AssociatedIdentities)_data.getContainer().get(Cxdx_v12AttributeName.AssociatedIdentities, 0);
    }

    /**
     * Sets the AssociatedIdentities.
     *
     * @param avp - the attribute value
     */
    public void setAssociatedIdentities(AssociatedIdentities avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.AssociatedIdentities, avp.getData(), true);
    }

    /**
     * Tests whether there is any LooseRouteIndication.
     */
    public boolean containsLooseRouteIndication() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.LooseRouteIndication);
    }

    /**
     * Gets the LooseRouteIndication.
     */
    public LooseRouteIndication getLooseRouteIndication() throws NoSuchAttributeException {
        return (LooseRouteIndication)_data.getContainer().get(Cxdx_v12AttributeName.LooseRouteIndication, 0);
    }

    /**
     * Sets the LooseRouteIndication.
     *
     * @param avp - the attribute value
     */
    public void setLooseRouteIndication(LooseRouteIndication avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.LooseRouteIndication, avp.getData(), true);
    }

    /**
     * Returns number of SCSCFRestorationInfo instances.
     */
    public int countSCSCFRestorationInfo() {
        return _data.getContainer().count(Cxdx_v12AttributeName.SCSCFRestorationInfo);
    }

    /**
     * Gets one SCSCFRestorationInfo.
     *
     * @param index - the index of the attribute to return
     */
    public SCSCFRestorationInfo getSCSCFRestorationInfo(int index) throws NoSuchAttributeException {
        return (SCSCFRestorationInfo)_data.getContainer().get(Cxdx_v12AttributeName.SCSCFRestorationInfo, index);
    }

    /**
     * Adds one SCSCFRestorationInfo.
     *
     * @param avp - the attribute value
     */
    public void addSCSCFRestorationInfo(SCSCFRestorationInfo avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SCSCFRestorationInfo, avp.getData(), false);
    }

    /**
     * Tests whether there is any AssociatedRegisteredIdentities.
     */
    public boolean containsAssociatedRegisteredIdentities() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.AssociatedRegisteredIdentities);
    }

    /**
     * Gets the AssociatedRegisteredIdentities.
     */
    public AssociatedRegisteredIdentities getAssociatedRegisteredIdentities() throws NoSuchAttributeException {
        return (AssociatedRegisteredIdentities)_data.getContainer().get(Cxdx_v12AttributeName.AssociatedRegisteredIdentities, 0);
    }

    /**
     * Sets the AssociatedRegisteredIdentities.
     *
     * @param avp - the attribute value
     */
    public void setAssociatedRegisteredIdentities(AssociatedRegisteredIdentities avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.AssociatedRegisteredIdentities, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServerName.
     */
    public boolean containsServerName() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.ServerName);
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
     * Tests whether there is any PriviledgedSenderIndication.
     */
    public boolean containsPriviledgedSenderIndication() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.PriviledgedSenderIndication);
    }

    /**
     * Gets the PriviledgedSenderIndication.
     */
    public PriviledgedSenderIndication getPriviledgedSenderIndication() throws NoSuchAttributeException {
        return (PriviledgedSenderIndication)_data.getContainer().get(Cxdx_v12AttributeName.PriviledgedSenderIndication, 0);
    }

    /**
     * Sets the PriviledgedSenderIndication.
     *
     * @param avp - the attribute value
     */
    public void setPriviledgedSenderIndication(PriviledgedSenderIndication avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.PriviledgedSenderIndication, avp.getData(), true);
    }

    /**
     * Returns number of FailedAVP instances.
     */
    public int countFailedAVP() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.FailedAVP);
    }

    /**
     * Gets one FailedAVP.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.FailedAVP getFailedAVP(int index) throws NoSuchAttributeException {
        return (diameter.base.FailedAVP)_data.getContainer().get(diameter.base.BaseAttributeName.FailedAVP, index);
    }

    /**
     * Adds one FailedAVP.
     *
     * @param avp - the attribute value
     */
    public void addFailedAVP(diameter.base.FailedAVP avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.FailedAVP, avp.getData(), false);
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
        if (containsResultCode()) {
            sb.append("    ResultCode:");
            try {
                sb.append(getResultCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsExperimentalResult()) {
            sb.append("    ExperimentalResult:");
            try {
                sb.append(getExperimentalResult()).append('\n');
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
        if (containsAssociatedIdentities()) {
            sb.append("    AssociatedIdentities:");
            try {
                sb.append(getAssociatedIdentities()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLooseRouteIndication()) {
            sb.append("    LooseRouteIndication:");
            try {
                sb.append(getLooseRouteIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSCSCFRestorationInfo(); ++i) {
            sb.append("    SCSCFRestorationInfo:");
            try {
                sb.append(getSCSCFRestorationInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAssociatedRegisteredIdentities()) {
            sb.append("    AssociatedRegisteredIdentities:");
            try {
                sb.append(getAssociatedRegisteredIdentities()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServerName()) {
            sb.append("    ServerName:");
            try {
                sb.append(getServerName()).append('\n');
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
        if (containsPriviledgedSenderIndication()) {
            sb.append("    PriviledgedSenderIndication:");
            try {
                sb.append(getPriviledgedSenderIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFailedAVP(); ++i) {
            sb.append("    FailedAVP:");
            try {
                sb.append(getFailedAVP(i)).append('\n');
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
        if (getCommandCode() != 301 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
