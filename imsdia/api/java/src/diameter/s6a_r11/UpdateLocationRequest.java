package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
   * The Update-Location-Request (ULR) command, indicated by the Command-Code 
   * field set to  316 and the 'R' bit set in the Command Flags field, is sent 
   * from MME or SGSN to HSS.
   */
public class UpdateLocationRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new UpdateLocationRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public UpdateLocationRequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 316, 16777251);
    }

    /**
     * Constructs a UpdateLocationRequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public UpdateLocationRequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a UpdateLocationRequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public UpdateLocationRequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    UpdateLocationRequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Gets the ULRFlags.
     */
    public ULRFlags getULRFlags() throws NoSuchAttributeException {
        return (ULRFlags)_data.getContainer().get(S6a_r11AttributeName.ULRFlags, 0);
    }

    /**
     * Sets the ULRFlags.
     *
     * @param avp - the attribute value
     */
    public void setULRFlags(ULRFlags avp) {
        _data.getContainer().add(S6a_r11AttributeName.ULRFlags, avp.getData(), true);
    }

    /**
     * Gets the VisitedPLMNId.
     */
    public VisitedPLMNId getVisitedPLMNId() throws NoSuchAttributeException {
        return (VisitedPLMNId)_data.getContainer().get(S6a_r11AttributeName.VisitedPLMNId, 0);
    }

    /**
     * Sets the VisitedPLMNId.
     *
     * @param avp - the attribute value
     */
    public void setVisitedPLMNId(VisitedPLMNId avp) {
        _data.getContainer().add(S6a_r11AttributeName.VisitedPLMNId, avp.getData(), true);
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
     * Tests whether there is any SGSNNumber.
     */
    public boolean containsSGSNNumber() {
        return _data.getContainer().contains(S6a_r11AttributeName.SGSNNumber);
    }

    /**
     * Gets the SGSNNumber.
     */
    public SGSNNumber getSGSNNumber() throws NoSuchAttributeException {
        return (SGSNNumber)_data.getContainer().get(S6a_r11AttributeName.SGSNNumber, 0);
    }

    /**
     * Sets the SGSNNumber.
     *
     * @param avp - the attribute value
     */
    public void setSGSNNumber(SGSNNumber avp) {
        _data.getContainer().add(S6a_r11AttributeName.SGSNNumber, avp.getData(), true);
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
     * Tests whether there is any TerminalInformation.
     */
    public boolean containsTerminalInformation() {
        return _data.getContainer().contains(S6a_r11AttributeName.TerminalInformation);
    }

    /**
     * Gets the TerminalInformation.
     */
    public TerminalInformation getTerminalInformation() throws NoSuchAttributeException {
        return (TerminalInformation)_data.getContainer().get(S6a_r11AttributeName.TerminalInformation, 0);
    }

    /**
     * Sets the TerminalInformation.
     *
     * @param avp - the attribute value
     */
    public void setTerminalInformation(TerminalInformation avp) {
        _data.getContainer().add(S6a_r11AttributeName.TerminalInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any UESRVCCCapability.
     */
    public boolean containsUESRVCCCapability() {
        return _data.getContainer().contains(S6a_r11AttributeName.UESRVCCCapability);
    }

    /**
     * Gets the UESRVCCCapability.
     */
    public UESRVCCCapability getUESRVCCCapability() throws NoSuchAttributeException {
        return (UESRVCCCapability)_data.getContainer().get(S6a_r11AttributeName.UESRVCCCapability, 0);
    }

    /**
     * Sets the UESRVCCCapability.
     *
     * @param avp - the attribute value
     */
    public void setUESRVCCCapability(UESRVCCCapability avp) {
        _data.getContainer().add(S6a_r11AttributeName.UESRVCCCapability, avp.getData(), true);
    }

    /**
     * Tests whether there is any HomogeneousSupportofIMSVoiceOverPSSessions.
     */
    public boolean containsHomogeneousSupportofIMSVoiceOverPSSessions() {
        return _data.getContainer().contains(S6a_r11AttributeName.HomogeneousSupportofIMSVoiceOverPSSessions);
    }

    /**
     * Gets the HomogeneousSupportofIMSVoiceOverPSSessions.
     */
    public HomogeneousSupportofIMSVoiceOverPSSessions getHomogeneousSupportofIMSVoiceOverPSSessions() throws NoSuchAttributeException {
        return (HomogeneousSupportofIMSVoiceOverPSSessions)_data.getContainer().get(S6a_r11AttributeName.HomogeneousSupportofIMSVoiceOverPSSessions, 0);
    }

    /**
     * Sets the HomogeneousSupportofIMSVoiceOverPSSessions.
     *
     * @param avp - the attribute value
     */
    public void setHomogeneousSupportofIMSVoiceOverPSSessions(HomogeneousSupportofIMSVoiceOverPSSessions avp) {
        _data.getContainer().add(S6a_r11AttributeName.HomogeneousSupportofIMSVoiceOverPSSessions, avp.getData(), true);
    }

    /**
     * Tests whether there is any GMLCAddress.
     */
    public boolean containsGMLCAddress() {
        return _data.getContainer().contains(S6a_r11AttributeName.GMLCAddress);
    }

    /**
     * Gets the GMLCAddress.
     */
    public GMLCAddress getGMLCAddress() throws NoSuchAttributeException {
        return (GMLCAddress)_data.getContainer().get(S6a_r11AttributeName.GMLCAddress, 0);
    }

    /**
     * Sets the GMLCAddress.
     *
     * @param avp - the attribute value
     */
    public void setGMLCAddress(GMLCAddress avp) {
        _data.getContainer().add(S6a_r11AttributeName.GMLCAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any EquivalentPLMNList.
     */
    public boolean containsEquivalentPLMNList() {
        return _data.getContainer().contains(S6a_r11AttributeName.EquivalentPLMNList);
    }

    /**
     * Gets the EquivalentPLMNList.
     */
    public EquivalentPLMNList getEquivalentPLMNList() throws NoSuchAttributeException {
        return (EquivalentPLMNList)_data.getContainer().get(S6a_r11AttributeName.EquivalentPLMNList, 0);
    }

    /**
     * Sets the EquivalentPLMNList.
     *
     * @param avp - the attribute value
     */
    public void setEquivalentPLMNList(EquivalentPLMNList avp) {
        _data.getContainer().add(S6a_r11AttributeName.EquivalentPLMNList, avp.getData(), true);
    }

    /**
     * Tests whether there is any MMENumberforMTSMS.
     */
    public boolean containsMMENumberforMTSMS() {
        return _data.getContainer().contains(S6a_r11AttributeName.MMENumberforMTSMS);
    }

    /**
     * Gets the MMENumberforMTSMS.
     */
    public MMENumberforMTSMS getMMENumberforMTSMS() throws NoSuchAttributeException {
        return (MMENumberforMTSMS)_data.getContainer().get(S6a_r11AttributeName.MMENumberforMTSMS, 0);
    }

    /**
     * Sets the MMENumberforMTSMS.
     *
     * @param avp - the attribute value
     */
    public void setMMENumberforMTSMS(MMENumberforMTSMS avp) {
        _data.getContainer().add(S6a_r11AttributeName.MMENumberforMTSMS, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMSReqisterRequest.
     */
    public boolean containsSMSReqisterRequest() {
        return _data.getContainer().contains(S6a_r11AttributeName.SMSReqisterRequest);
    }

    /**
     * Gets the SMSReqisterRequest.
     */
    public SMSReqisterRequest getSMSReqisterRequest() throws NoSuchAttributeException {
        return (SMSReqisterRequest)_data.getContainer().get(S6a_r11AttributeName.SMSReqisterRequest, 0);
    }

    /**
     * Sets the SMSReqisterRequest.
     *
     * @param avp - the attribute value
     */
    public void setSMSReqisterRequest(SMSReqisterRequest avp) {
        _data.getContainer().add(S6a_r11AttributeName.SMSReqisterRequest, avp.getData(), true);
    }

    /**
     * Returns number of ActiveAPN instances.
     */
    public int countActiveAPN() {
        return _data.getContainer().count(S6a_r11AttributeName.ActiveAPN);
    }

    /**
     * Gets one ActiveAPN.
     *
     * @param index - the index of the attribute to return
     */
    public ActiveAPN getActiveAPN(int index) throws NoSuchAttributeException {
        return (ActiveAPN)_data.getContainer().get(S6a_r11AttributeName.ActiveAPN, index);
    }

    /**
     * Adds one ActiveAPN.
     *
     * @param avp - the attribute value
     */
    public void addActiveAPN(ActiveAPN avp) {
        _data.getContainer().add(S6a_r11AttributeName.ActiveAPN, avp.getData(), false);
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
        sb.append("    ULRFlags:");
            try {
                sb.append(getULRFlags()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    VisitedPLMNId:");
            try {
                sb.append(getVisitedPLMNId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    RATType:");
            try {
                sb.append(getRATType()).append('\n');
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
        if (containsSGSNNumber()) {
            sb.append("    SGSNNumber:");
            try {
                sb.append(getSGSNNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDestinationHost()) {
            sb.append("    DestinationHost:");
            try {
                sb.append(getDestinationHost()).append('\n');
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
        if (containsTerminalInformation()) {
            sb.append("    TerminalInformation:");
            try {
                sb.append(getTerminalInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUESRVCCCapability()) {
            sb.append("    UESRVCCCapability:");
            try {
                sb.append(getUESRVCCCapability()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsHomogeneousSupportofIMSVoiceOverPSSessions()) {
            sb.append("    HomogeneousSupportofIMSVoiceOverPSSessions:");
            try {
                sb.append(getHomogeneousSupportofIMSVoiceOverPSSessions()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGMLCAddress()) {
            sb.append("    GMLCAddress:");
            try {
                sb.append(getGMLCAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEquivalentPLMNList()) {
            sb.append("    EquivalentPLMNList:");
            try {
                sb.append(getEquivalentPLMNList()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMMENumberforMTSMS()) {
            sb.append("    MMENumberforMTSMS:");
            try {
                sb.append(getMMENumberforMTSMS()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMSReqisterRequest()) {
            sb.append("    SMSReqisterRequest:");
            try {
                sb.append(getSMSReqisterRequest()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countActiveAPN(); ++i) {
            sb.append("    ActiveAPN:");
            try {
                sb.append(getActiveAPN(i)).append('\n');
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
        if (getCommandCode() != 316 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
