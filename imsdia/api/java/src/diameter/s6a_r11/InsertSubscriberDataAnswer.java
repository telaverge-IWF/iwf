package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
   * The Insert-Subscriber-Data-Answer (IDA) command, indicated by the 
   * Command-Code field set to 319 and the 'R' bit cleared in the Command 
   * Flags field, is sent from MME or SGSN to HSS.
   */
public class InsertSubscriberDataAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new InsertSubscriberDataAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public InsertSubscriberDataAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 319, 16777251);
    }

    /**
     * Constructs a InsertSubscriberDataAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public InsertSubscriberDataAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a InsertSubscriberDataAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public InsertSubscriberDataAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    InsertSubscriberDataAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Tests whether there is any VendorSpecificApplicationId.
     */
    public boolean containsVendorSpecificApplicationId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.VendorSpecificApplicationId);
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
     * Returns number of SupportedFeatures instances.
     */
    public int countSupportedFeatures() {
        return _data.getContainer().count(S6a_r11AttributeName.SupportedFeatures);
    }

    /**
     * Gets one SupportedFeatures.
     *
     * @param index - the index of the attribute to return
     */
    public SupportedFeatures getSupportedFeatures(int index) throws NoSuchAttributeException {
        return (SupportedFeatures)_data.getContainer().get(S6a_r11AttributeName.SupportedFeatures, index);
    }

    /**
     * Adds one SupportedFeatures.
     *
     * @param avp - the attribute value
     */
    public void addSupportedFeatures(SupportedFeatures avp) {
        _data.getContainer().add(S6a_r11AttributeName.SupportedFeatures, avp.getData(), false);
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
     * Tests whether there is any IMSVoiceOverPSSessionsSupported.
     */
    public boolean containsIMSVoiceOverPSSessionsSupported() {
        return _data.getContainer().contains(S6a_r11AttributeName.IMSVoiceOverPSSessionsSupported);
    }

    /**
     * Gets the IMSVoiceOverPSSessionsSupported.
     */
    public IMSVoiceOverPSSessionsSupported getIMSVoiceOverPSSessionsSupported() throws NoSuchAttributeException {
        return (IMSVoiceOverPSSessionsSupported)_data.getContainer().get(S6a_r11AttributeName.IMSVoiceOverPSSessionsSupported, 0);
    }

    /**
     * Sets the IMSVoiceOverPSSessionsSupported.
     *
     * @param avp - the attribute value
     */
    public void setIMSVoiceOverPSSessionsSupported(IMSVoiceOverPSSessionsSupported avp) {
        _data.getContainer().add(S6a_r11AttributeName.IMSVoiceOverPSSessionsSupported, avp.getData(), true);
    }

    /**
     * Tests whether there is any LastUEActivityTime.
     */
    public boolean containsLastUEActivityTime() {
        return _data.getContainer().contains(S6a_r11AttributeName.LastUEActivityTime);
    }

    /**
     * Gets the LastUEActivityTime.
     */
    public LastUEActivityTime getLastUEActivityTime() throws NoSuchAttributeException {
        return (LastUEActivityTime)_data.getContainer().get(S6a_r11AttributeName.LastUEActivityTime, 0);
    }

    /**
     * Sets the LastUEActivityTime.
     *
     * @param avp - the attribute value
     */
    public void setLastUEActivityTime(LastUEActivityTime avp) {
        _data.getContainer().add(S6a_r11AttributeName.LastUEActivityTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any RATType.
     */
    public boolean containsRATType() {
        return _data.getContainer().contains(S6a_r11AttributeName.RATType);
    }

    /**
     * Gets the RATType.
     */
    public RATType getRATType() throws NoSuchAttributeException {
        return (RATType)_data.getContainer().get(S6a_r11AttributeName.RATType, 0);
    }

    /**
     * Sets the RATType.
     *
     * @param avp - the attribute value
     */
    public void setRATType(RATType avp) {
        _data.getContainer().add(S6a_r11AttributeName.RATType, avp.getData(), true);
    }

    /**
     * Tests whether there is any IDAFlags.
     */
    public boolean containsIDAFlags() {
        return _data.getContainer().contains(S6a_r11AttributeName.IDAFlags);
    }

    /**
     * Gets the IDAFlags.
     */
    public IDAFlags getIDAFlags() throws NoSuchAttributeException {
        return (IDAFlags)_data.getContainer().get(S6a_r11AttributeName.IDAFlags, 0);
    }

    /**
     * Sets the IDAFlags.
     *
     * @param avp - the attribute value
     */
    public void setIDAFlags(IDAFlags avp) {
        _data.getContainer().add(S6a_r11AttributeName.IDAFlags, avp.getData(), true);
    }

    /**
     * Tests whether there is any EPSUserState.
     */
    public boolean containsEPSUserState() {
        return _data.getContainer().contains(S6a_r11AttributeName.EPSUserState);
    }

    /**
     * Gets the EPSUserState.
     */
    public EPSUserState getEPSUserState() throws NoSuchAttributeException {
        return (EPSUserState)_data.getContainer().get(S6a_r11AttributeName.EPSUserState, 0);
    }

    /**
     * Sets the EPSUserState.
     *
     * @param avp - the attribute value
     */
    public void setEPSUserState(EPSUserState avp) {
        _data.getContainer().add(S6a_r11AttributeName.EPSUserState, avp.getData(), true);
    }

    /**
     * Tests whether there is any EPSLocationInformation.
     */
    public boolean containsEPSLocationInformation() {
        return _data.getContainer().contains(S6a_r11AttributeName.EPSLocationInformation);
    }

    /**
     * Gets the EPSLocationInformation.
     */
    public EPSLocationInformation getEPSLocationInformation() throws NoSuchAttributeException {
        return (EPSLocationInformation)_data.getContainer().get(S6a_r11AttributeName.EPSLocationInformation, 0);
    }

    /**
     * Sets the EPSLocationInformation.
     *
     * @param avp - the attribute value
     */
    public void setEPSLocationInformation(EPSLocationInformation avp) {
        _data.getContainer().add(S6a_r11AttributeName.EPSLocationInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any LocalTimeZone.
     */
    public boolean containsLocalTimeZone() {
        return _data.getContainer().contains(S6a_r11AttributeName.LocalTimeZone);
    }

    /**
     * Gets the LocalTimeZone.
     */
    public LocalTimeZone getLocalTimeZone() throws NoSuchAttributeException {
        return (LocalTimeZone)_data.getContainer().get(S6a_r11AttributeName.LocalTimeZone, 0);
    }

    /**
     * Sets the LocalTimeZone.
     *
     * @param avp - the attribute value
     */
    public void setLocalTimeZone(LocalTimeZone avp) {
        _data.getContainer().add(S6a_r11AttributeName.LocalTimeZone, avp.getData(), true);
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

    public String toString() {
        StringBuffer sb = headerToStringBuffer().append(" {\n");
        sb.append("    SessionId:");
            try {
                sb.append(getSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[fixed but missing]\n");
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
        if (containsVendorSpecificApplicationId()) {
            sb.append("    VendorSpecificApplicationId:");
            try {
                sb.append(getVendorSpecificApplicationId()).append('\n');
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
        if (containsIMSVoiceOverPSSessionsSupported()) {
            sb.append("    IMSVoiceOverPSSessionsSupported:");
            try {
                sb.append(getIMSVoiceOverPSSessionsSupported()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLastUEActivityTime()) {
            sb.append("    LastUEActivityTime:");
            try {
                sb.append(getLastUEActivityTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRATType()) {
            sb.append("    RATType:");
            try {
                sb.append(getRATType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIDAFlags()) {
            sb.append("    IDAFlags:");
            try {
                sb.append(getIDAFlags()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEPSUserState()) {
            sb.append("    EPSUserState:");
            try {
                sb.append(getEPSUserState()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEPSLocationInformation()) {
            sb.append("    EPSLocationInformation:");
            try {
                sb.append(getEPSLocationInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLocalTimeZone()) {
            sb.append("    LocalTimeZone:");
            try {
                sb.append(getLocalTimeZone()).append('\n');
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
        if (getCommandCode() != 319 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
