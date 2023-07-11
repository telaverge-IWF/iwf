package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class CreditControlRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new CreditControlRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public CreditControlRequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 272, 4);
    }

    /**
     * Constructs a CreditControlRequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public CreditControlRequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a CreditControlRequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public CreditControlRequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    CreditControlRequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Gets the ServiceContextId.
     */
    public ServiceContextId getServiceContextId() throws NoSuchAttributeException {
        return (ServiceContextId)_data.getContainer().get(Ro_r10_transatelAttributeName.ServiceContextId, 0);
    }

    /**
     * Sets the ServiceContextId.
     *
     * @param avp - the attribute value
     */
    public void setServiceContextId(ServiceContextId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ServiceContextId, avp.getData(), true);
    }

    /**
     * Gets the CCRequestType.
     */
    public CCRequestType getCCRequestType() throws NoSuchAttributeException {
        return (CCRequestType)_data.getContainer().get(Ro_r10_transatelAttributeName.CCRequestType, 0);
    }

    /**
     * Sets the CCRequestType.
     *
     * @param avp - the attribute value
     */
    public void setCCRequestType(CCRequestType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCRequestType, avp.getData(), true);
    }

    /**
     * Gets the CCRequestNumber.
     */
    public CCRequestNumber getCCRequestNumber() throws NoSuchAttributeException {
        return (CCRequestNumber)_data.getContainer().get(Ro_r10_transatelAttributeName.CCRequestNumber, 0);
    }

    /**
     * Sets the CCRequestNumber.
     *
     * @param avp - the attribute value
     */
    public void setCCRequestNumber(CCRequestNumber avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCRequestNumber, avp.getData(), true);
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
     * Tests whether there is any EventTimestamp.
     */
    public boolean containsEventTimestamp() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.EventTimestamp);
    }

    /**
     * Gets the EventTimestamp.
     */
    public diameter.base.EventTimestamp getEventTimestamp() throws NoSuchAttributeException {
        return (diameter.base.EventTimestamp)_data.getContainer().get(diameter.base.BaseAttributeName.EventTimestamp, 0);
    }

    /**
     * Sets the EventTimestamp.
     *
     * @param avp - the attribute value
     */
    public void setEventTimestamp(diameter.base.EventTimestamp avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.EventTimestamp, avp.getData(), true);
    }

    /**
     * Returns number of SubscriptionId instances.
     */
    public int countSubscriptionId() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.SubscriptionId);
    }

    /**
     * Gets one SubscriptionId.
     *
     * @param index - the index of the attribute to return
     */
    public SubscriptionId getSubscriptionId(int index) throws NoSuchAttributeException {
        return (SubscriptionId)_data.getContainer().get(Ro_r10_transatelAttributeName.SubscriptionId, index);
    }

    /**
     * Adds one SubscriptionId.
     *
     * @param avp - the attribute value
     */
    public void addSubscriptionId(SubscriptionId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SubscriptionId, avp.getData(), false);
    }

    /**
     * Tests whether there is any TerminationCause.
     */
    public boolean containsTerminationCause() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.TerminationCause);
    }

    /**
     * Gets the TerminationCause.
     */
    public diameter.base.TerminationCause getTerminationCause() throws NoSuchAttributeException {
        return (diameter.base.TerminationCause)_data.getContainer().get(diameter.base.BaseAttributeName.TerminationCause, 0);
    }

    /**
     * Sets the TerminationCause.
     *
     * @param avp - the attribute value
     */
    public void setTerminationCause(diameter.base.TerminationCause avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.TerminationCause, avp.getData(), true);
    }

    /**
     * Tests whether there is any RequestedAction.
     */
    public boolean containsRequestedAction() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.RequestedAction);
    }

    /**
     * Gets the RequestedAction.
     */
    public RequestedAction getRequestedAction() throws NoSuchAttributeException {
        return (RequestedAction)_data.getContainer().get(Ro_r10_transatelAttributeName.RequestedAction, 0);
    }

    /**
     * Sets the RequestedAction.
     *
     * @param avp - the attribute value
     */
    public void setRequestedAction(RequestedAction avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.RequestedAction, avp.getData(), true);
    }

    /**
     * Tests whether there is any AoCRequestType.
     */
    public boolean containsAoCRequestType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AoCRequestType);
    }

    /**
     * Gets the AoCRequestType.
     */
    public AoCRequestType getAoCRequestType() throws NoSuchAttributeException {
        return (AoCRequestType)_data.getContainer().get(Ro_r10_transatelAttributeName.AoCRequestType, 0);
    }

    /**
     * Sets the AoCRequestType.
     *
     * @param avp - the attribute value
     */
    public void setAoCRequestType(AoCRequestType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AoCRequestType, avp.getData(), true);
    }

    /**
     * Tests whether there is any MultipleServicesIndicator.
     */
    public boolean containsMultipleServicesIndicator() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MultipleServicesIndicator);
    }

    /**
     * Gets the MultipleServicesIndicator.
     */
    public MultipleServicesIndicator getMultipleServicesIndicator() throws NoSuchAttributeException {
        return (MultipleServicesIndicator)_data.getContainer().get(Ro_r10_transatelAttributeName.MultipleServicesIndicator, 0);
    }

    /**
     * Sets the MultipleServicesIndicator.
     *
     * @param avp - the attribute value
     */
    public void setMultipleServicesIndicator(MultipleServicesIndicator avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MultipleServicesIndicator, avp.getData(), true);
    }

    /**
     * Returns number of MultipleServicesCreditControl instances.
     */
    public int countMultipleServicesCreditControl() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.MultipleServicesCreditControl);
    }

    /**
     * Gets one MultipleServicesCreditControl.
     *
     * @param index - the index of the attribute to return
     */
    public MultipleServicesCreditControl getMultipleServicesCreditControl(int index) throws NoSuchAttributeException {
        return (MultipleServicesCreditControl)_data.getContainer().get(Ro_r10_transatelAttributeName.MultipleServicesCreditControl, index);
    }

    /**
     * Adds one MultipleServicesCreditControl.
     *
     * @param avp - the attribute value
     */
    public void addMultipleServicesCreditControl(MultipleServicesCreditControl avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MultipleServicesCreditControl, avp.getData(), false);
    }

    /**
     * Tests whether there is any CCCorrelationId.
     */
    public boolean containsCCCorrelationId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCCorrelationId);
    }

    /**
     * Gets the CCCorrelationId.
     */
    public CCCorrelationId getCCCorrelationId() throws NoSuchAttributeException {
        return (CCCorrelationId)_data.getContainer().get(Ro_r10_transatelAttributeName.CCCorrelationId, 0);
    }

    /**
     * Sets the CCCorrelationId.
     *
     * @param avp - the attribute value
     */
    public void setCCCorrelationId(CCCorrelationId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCCorrelationId, avp.getData(), true);
    }

    /**
     * Tests whether there is any UserEquipmentInfo.
     */
    public boolean containsUserEquipmentInfo() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.UserEquipmentInfo);
    }

    /**
     * Gets the UserEquipmentInfo.
     */
    public UserEquipmentInfo getUserEquipmentInfo() throws NoSuchAttributeException {
        return (UserEquipmentInfo)_data.getContainer().get(Ro_r10_transatelAttributeName.UserEquipmentInfo, 0);
    }

    /**
     * Sets the UserEquipmentInfo.
     *
     * @param avp - the attribute value
     */
    public void setUserEquipmentInfo(UserEquipmentInfo avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.UserEquipmentInfo, avp.getData(), true);
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
     * Tests whether there is any ServiceInformation.
     */
    public boolean containsServiceInformation() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ServiceInformation);
    }

    /**
     * Gets the ServiceInformation.
     */
    public ServiceInformation getServiceInformation() throws NoSuchAttributeException {
        return (ServiceInformation)_data.getContainer().get(Ro_r10_transatelAttributeName.ServiceInformation, 0);
    }

    /**
     * Sets the ServiceInformation.
     *
     * @param avp - the attribute value
     */
    public void setServiceInformation(ServiceInformation avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ServiceInformation, avp.getData(), true);
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
        sb.append("    AuthApplicationId:");
            try {
                sb.append(getAuthApplicationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ServiceContextId:");
            try {
                sb.append(getServiceContextId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CCRequestType:");
            try {
                sb.append(getCCRequestType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CCRequestNumber:");
            try {
                sb.append(getCCRequestNumber()).append('\n');
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
        if (containsOriginStateId()) {
            sb.append("    OriginStateId:");
            try {
                sb.append(getOriginStateId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEventTimestamp()) {
            sb.append("    EventTimestamp:");
            try {
                sb.append(getEventTimestamp()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSubscriptionId(); ++i) {
            sb.append("    SubscriptionId:");
            try {
                sb.append(getSubscriptionId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTerminationCause()) {
            sb.append("    TerminationCause:");
            try {
                sb.append(getTerminationCause()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRequestedAction()) {
            sb.append("    RequestedAction:");
            try {
                sb.append(getRequestedAction()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAoCRequestType()) {
            sb.append("    AoCRequestType:");
            try {
                sb.append(getAoCRequestType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMultipleServicesIndicator()) {
            sb.append("    MultipleServicesIndicator:");
            try {
                sb.append(getMultipleServicesIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countMultipleServicesCreditControl(); ++i) {
            sb.append("    MultipleServicesCreditControl:");
            try {
                sb.append(getMultipleServicesCreditControl(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCCorrelationId()) {
            sb.append("    CCCorrelationId:");
            try {
                sb.append(getCCCorrelationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserEquipmentInfo()) {
            sb.append("    UserEquipmentInfo:");
            try {
                sb.append(getUserEquipmentInfo()).append('\n');
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
        if (containsServiceInformation()) {
            sb.append("    ServiceInformation:");
            try {
                sb.append(getServiceInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }

    private void validate() throws WrongCommandTypeException {
        if (getCommandCode() != 272 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
