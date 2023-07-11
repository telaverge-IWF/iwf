package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Registration-Termination-Answer (RTA) command, indicated by the Command-Code field set to 304 and the <tt>R</tt>
 * bit cleared in the Command Flags field, is sent by a client in response to the Registration-Termination-Request
 * command. The Result-Code or Experimental-Result AVP may contain one of the values defined in section 6.2 in
 * addition to the values defined in IETF RFC 3588 [6].
 */
public class RegistrationTerminationAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new RegistrationTerminationAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public RegistrationTerminationAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 304, 16777216);
    }

    /**
     * Constructs a RegistrationTerminationAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public RegistrationTerminationAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a RegistrationTerminationAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public RegistrationTerminationAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    RegistrationTerminationAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Returns number of IdentitywithEmergencyRegistration instances.
     */
    public int countIdentitywithEmergencyRegistration() {
        return _data.getContainer().count(Cxdx_v12AttributeName.IdentitywithEmergencyRegistration);
    }

    /**
     * Gets one IdentitywithEmergencyRegistration.
     *
     * @param index - the index of the attribute to return
     */
    public IdentitywithEmergencyRegistration getIdentitywithEmergencyRegistration(int index) throws NoSuchAttributeException {
        return (IdentitywithEmergencyRegistration)_data.getContainer().get(Cxdx_v12AttributeName.IdentitywithEmergencyRegistration, index);
    }

    /**
     * Adds one IdentitywithEmergencyRegistration.
     *
     * @param avp - the attribute value
     */
    public void addIdentitywithEmergencyRegistration(IdentitywithEmergencyRegistration avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.IdentitywithEmergencyRegistration, avp.getData(), false);
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
        if (containsAssociatedIdentities()) {
            sb.append("    AssociatedIdentities:");
            try {
                sb.append(getAssociatedIdentities()).append('\n');
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
        for (int i = 0; i < countIdentitywithEmergencyRegistration(); ++i) {
            sb.append("    IdentitywithEmergencyRegistration:");
            try {
                sb.append(getIdentitywithEmergencyRegistration(i)).append('\n');
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
        if (getCommandCode() != 304 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
