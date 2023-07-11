package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
   * The Notify-Request (NOR) command, indicated by the Command-Code field set to 323 
   *  and the 'R' bit set in the Command Flags field, is sent from MME or SGSN to HSS.
   */
public class NotifyRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new NotifyRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public NotifyRequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 323, 16777251);
    }

    /**
     * Constructs a NotifyRequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public NotifyRequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a NotifyRequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public NotifyRequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    NotifyRequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
        return _data.getContainer().count(S6a_r10AttributeName.SupportedFeatures);
    }

    /**
     * Gets one SupportedFeatures.
     *
     * @param index - the index of the attribute to return
     */
    public SupportedFeatures getSupportedFeatures(int index) throws NoSuchAttributeException {
        return (SupportedFeatures)_data.getContainer().get(S6a_r10AttributeName.SupportedFeatures, index);
    }

    /**
     * Adds one SupportedFeatures.
     *
     * @param avp - the attribute value
     */
    public void addSupportedFeatures(SupportedFeatures avp) {
        _data.getContainer().add(S6a_r10AttributeName.SupportedFeatures, avp.getData(), false);
    }

    /**
     * Tests whether there is any TerminalInformation.
     */
    public boolean containsTerminalInformation() {
        return _data.getContainer().contains(S6a_r10AttributeName.TerminalInformation);
    }

    /**
     * Gets the TerminalInformation.
     */
    public TerminalInformation getTerminalInformation() throws NoSuchAttributeException {
        return (TerminalInformation)_data.getContainer().get(S6a_r10AttributeName.TerminalInformation, 0);
    }

    /**
     * Sets the TerminalInformation.
     *
     * @param avp - the attribute value
     */
    public void setTerminalInformation(TerminalInformation avp) {
        _data.getContainer().add(S6a_r10AttributeName.TerminalInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any NORFlags.
     */
    public boolean containsNORFlags() {
        return _data.getContainer().contains(S6a_r10AttributeName.NORFlags);
    }

    /**
     * Gets the NORFlags.
     */
    public NORFlags getNORFlags() throws NoSuchAttributeException {
        return (NORFlags)_data.getContainer().get(S6a_r10AttributeName.NORFlags, 0);
    }

    /**
     * Sets the NORFlags.
     *
     * @param avp - the attribute value
     */
    public void setNORFlags(NORFlags avp) {
        _data.getContainer().add(S6a_r10AttributeName.NORFlags, avp.getData(), true);
    }

    /**
     * Tests whether there is any MIP6AgentInfo.
     */
    public boolean containsMIP6AgentInfo() {
        return _data.getContainer().contains(S6a_r10AttributeName.MIP6AgentInfo);
    }

    /**
     * Gets the MIP6AgentInfo.
     */
    public MIP6AgentInfo getMIP6AgentInfo() throws NoSuchAttributeException {
        return (MIP6AgentInfo)_data.getContainer().get(S6a_r10AttributeName.MIP6AgentInfo, 0);
    }

    /**
     * Sets the MIP6AgentInfo.
     *
     * @param avp - the attribute value
     */
    public void setMIP6AgentInfo(MIP6AgentInfo avp) {
        _data.getContainer().add(S6a_r10AttributeName.MIP6AgentInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any VisitedNetworkIdentifier.
     */
    public boolean containsVisitedNetworkIdentifier() {
        return _data.getContainer().contains(S6a_r10AttributeName.VisitedNetworkIdentifier);
    }

    /**
     * Gets the VisitedNetworkIdentifier.
     */
    public VisitedNetworkIdentifier getVisitedNetworkIdentifier() throws NoSuchAttributeException {
        return (VisitedNetworkIdentifier)_data.getContainer().get(S6a_r10AttributeName.VisitedNetworkIdentifier, 0);
    }

    /**
     * Sets the VisitedNetworkIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setVisitedNetworkIdentifier(VisitedNetworkIdentifier avp) {
        _data.getContainer().add(S6a_r10AttributeName.VisitedNetworkIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any ContextIdentifier.
     */
    public boolean containsContextIdentifier() {
        return _data.getContainer().contains(S6a_r10AttributeName.ContextIdentifier);
    }

    /**
     * Gets the ContextIdentifier.
     */
    public ContextIdentifier getContextIdentifier() throws NoSuchAttributeException {
        return (ContextIdentifier)_data.getContainer().get(S6a_r10AttributeName.ContextIdentifier, 0);
    }

    /**
     * Sets the ContextIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setContextIdentifier(ContextIdentifier avp) {
        _data.getContainer().add(S6a_r10AttributeName.ContextIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceSelection.
     */
    public boolean containsServiceSelection() {
        return _data.getContainer().contains(S6a_r10AttributeName.ServiceSelection);
    }

    /**
     * Gets the ServiceSelection.
     */
    public ServiceSelection getServiceSelection() throws NoSuchAttributeException {
        return (ServiceSelection)_data.getContainer().get(S6a_r10AttributeName.ServiceSelection, 0);
    }

    /**
     * Sets the ServiceSelection.
     *
     * @param avp - the attribute value
     */
    public void setServiceSelection(ServiceSelection avp) {
        _data.getContainer().add(S6a_r10AttributeName.ServiceSelection, avp.getData(), true);
    }

    /**
     * Tests whether there is any AlertReason.
     */
    public boolean containsAlertReason() {
        return _data.getContainer().contains(S6a_r10AttributeName.AlertReason);
    }

    /**
     * Gets the AlertReason.
     */
    public AlertReason getAlertReason() throws NoSuchAttributeException {
        return (AlertReason)_data.getContainer().get(S6a_r10AttributeName.AlertReason, 0);
    }

    /**
     * Sets the AlertReason.
     *
     * @param avp - the attribute value
     */
    public void setAlertReason(AlertReason avp) {
        _data.getContainer().add(S6a_r10AttributeName.AlertReason, avp.getData(), true);
    }

    /**
     * Tests whether there is any UESRVCCCapability.
     */
    public boolean containsUESRVCCCapability() {
        return _data.getContainer().contains(S6a_r10AttributeName.UESRVCCCapability);
    }

    /**
     * Gets the UESRVCCCapability.
     */
    public UESRVCCCapability getUESRVCCCapability() throws NoSuchAttributeException {
        return (UESRVCCCapability)_data.getContainer().get(S6a_r10AttributeName.UESRVCCCapability, 0);
    }

    /**
     * Sets the UESRVCCCapability.
     *
     * @param avp - the attribute value
     */
    public void setUESRVCCCapability(UESRVCCCapability avp) {
        _data.getContainer().add(S6a_r10AttributeName.UESRVCCCapability, avp.getData(), true);
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
        if (containsVendorSpecificApplicationId()) {
            sb.append("    VendorSpecificApplicationId:");
            try {
                sb.append(getVendorSpecificApplicationId()).append('\n');
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
        if (containsNORFlags()) {
            sb.append("    NORFlags:");
            try {
                sb.append(getNORFlags()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMIP6AgentInfo()) {
            sb.append("    MIP6AgentInfo:");
            try {
                sb.append(getMIP6AgentInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVisitedNetworkIdentifier()) {
            sb.append("    VisitedNetworkIdentifier:");
            try {
                sb.append(getVisitedNetworkIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsContextIdentifier()) {
            sb.append("    ContextIdentifier:");
            try {
                sb.append(getContextIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceSelection()) {
            sb.append("    ServiceSelection:");
            try {
                sb.append(getServiceSelection()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAlertReason()) {
            sb.append("    AlertReason:");
            try {
                sb.append(getAlertReason()).append('\n');
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
        if (getCommandCode() != 323 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
