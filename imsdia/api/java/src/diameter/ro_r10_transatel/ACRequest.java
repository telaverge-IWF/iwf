package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class ACRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new ACRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public ACRequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 271, 4);
    }

    /**
     * Constructs a ACRequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public ACRequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a ACRequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public ACRequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    ACRequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Gets the AccountingRecordType.
     */
    public diameter.base.AccountingRecordType getAccountingRecordType() throws NoSuchAttributeException {
        return (diameter.base.AccountingRecordType)_data.getContainer().get(diameter.base.BaseAttributeName.AccountingRecordType, 0);
    }

    /**
     * Sets the AccountingRecordType.
     *
     * @param avp - the attribute value
     */
    public void setAccountingRecordType(diameter.base.AccountingRecordType avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AccountingRecordType, avp.getData(), true);
    }

    /**
     * Gets the AccountingRecordNumber.
     */
    public diameter.base.AccountingRecordNumber getAccountingRecordNumber() throws NoSuchAttributeException {
        return (diameter.base.AccountingRecordNumber)_data.getContainer().get(diameter.base.BaseAttributeName.AccountingRecordNumber, 0);
    }

    /**
     * Sets the AccountingRecordNumber.
     *
     * @param avp - the attribute value
     */
    public void setAccountingRecordNumber(diameter.base.AccountingRecordNumber avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AccountingRecordNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctApplicationId.
     */
    public boolean containsAcctApplicationId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AcctApplicationId);
    }

    /**
     * Gets the AcctApplicationId.
     */
    public diameter.base.AcctApplicationId getAcctApplicationId() throws NoSuchAttributeException {
        return (diameter.base.AcctApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.AcctApplicationId, 0);
    }

    /**
     * Sets the AcctApplicationId.
     *
     * @param avp - the attribute value
     */
    public void setAcctApplicationId(diameter.base.AcctApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AcctApplicationId, avp.getData(), true);
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
     * Tests whether there is any AcctInterimInterval.
     */
    public boolean containsAcctInterimInterval() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AcctInterimInterval);
    }

    /**
     * Gets the AcctInterimInterval.
     */
    public diameter.base.AcctInterimInterval getAcctInterimInterval() throws NoSuchAttributeException {
        return (diameter.base.AcctInterimInterval)_data.getContainer().get(diameter.base.BaseAttributeName.AcctInterimInterval, 0);
    }

    /**
     * Sets the AcctInterimInterval.
     *
     * @param avp - the attribute value
     */
    public void setAcctInterimInterval(diameter.base.AcctInterimInterval avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AcctInterimInterval, avp.getData(), true);
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
     * Tests whether there is any ServiceContextId.
     */
    public boolean containsServiceContextId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ServiceContextId);
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
        sb.append("    AccountingRecordType:");
            try {
                sb.append(getAccountingRecordType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AccountingRecordNumber:");
            try {
                sb.append(getAccountingRecordNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsAcctApplicationId()) {
            sb.append("    AcctApplicationId:");
            try {
                sb.append(getAcctApplicationId()).append('\n');
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
        if (containsAcctInterimInterval()) {
            sb.append("    AcctInterimInterval:");
            try {
                sb.append(getAcctInterimInterval()).append('\n');
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
        if (containsServiceContextId()) {
            sb.append("    ServiceContextId:");
            try {
                sb.append(getServiceContextId()).append('\n');
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
        if (getCommandCode() != 271 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
