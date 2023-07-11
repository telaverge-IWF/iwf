package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ACA message [BASE] is used to acknowledge an Accounting-Request command.
 * The Accounting-Answer command contains the same Session-Id as the Request.
 * If the Accounting-Request was protected by end-toend security, then the
 * corresponding ACA message MUST be protected as well.
 * Only the target Diameter Server or home Diameter Server SHOULD respond with
 * the Accounting-Answer command. Either Acct-Application-Id or
 * Vendor-Specific-Application-Id AVPs MUST be present as it was in the request.
 */
public class ACAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new ACAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public ACAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 271, 1);
    }

    /**
     * Constructs a ACAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public ACAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a ACAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public ACAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    ACAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Tests whether there is any AccountingSubSessionId.
     */
    public boolean containsAccountingSubSessionId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AccountingSubSessionId);
    }

    /**
     * Gets the AccountingSubSessionId.
     */
    public diameter.base.AccountingSubSessionId getAccountingSubSessionId() throws NoSuchAttributeException {
        return (diameter.base.AccountingSubSessionId)_data.getContainer().get(diameter.base.BaseAttributeName.AccountingSubSessionId, 0);
    }

    /**
     * Sets the AccountingSubSessionId.
     *
     * @param avp - the attribute value
     */
    public void setAccountingSubSessionId(diameter.base.AccountingSubSessionId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AccountingSubSessionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctSessionId.
     */
    public boolean containsAcctSessionId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AcctSessionId);
    }

    /**
     * Gets the AcctSessionId.
     */
    public diameter.base.AcctSessionId getAcctSessionId() throws NoSuchAttributeException {
        return (diameter.base.AcctSessionId)_data.getContainer().get(diameter.base.BaseAttributeName.AcctSessionId, 0);
    }

    /**
     * Sets the AcctSessionId.
     *
     * @param avp - the attribute value
     */
    public void setAcctSessionId(diameter.base.AcctSessionId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AcctSessionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctMultiSessionId.
     */
    public boolean containsAcctMultiSessionId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AcctMultiSessionId);
    }

    /**
     * Gets the AcctMultiSessionId.
     */
    public diameter.base.AcctMultiSessionId getAcctMultiSessionId() throws NoSuchAttributeException {
        return (diameter.base.AcctMultiSessionId)_data.getContainer().get(diameter.base.BaseAttributeName.AcctMultiSessionId, 0);
    }

    /**
     * Sets the AcctMultiSessionId.
     *
     * @param avp - the attribute value
     */
    public void setAcctMultiSessionId(diameter.base.AcctMultiSessionId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AcctMultiSessionId, avp.getData(), true);
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
     * Tests whether there is any ErrorMessage.
     */
    public boolean containsErrorMessage() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.ErrorMessage);
    }

    /**
     * Gets the ErrorMessage.
     */
    public diameter.base.ErrorMessage getErrorMessage() throws NoSuchAttributeException {
        return (diameter.base.ErrorMessage)_data.getContainer().get(diameter.base.BaseAttributeName.ErrorMessage, 0);
    }

    /**
     * Sets the ErrorMessage.
     *
     * @param avp - the attribute value
     */
    public void setErrorMessage(diameter.base.ErrorMessage avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ErrorMessage, avp.getData(), true);
    }

    /**
     * Tests whether there is any ErrorReportingHost.
     */
    public boolean containsErrorReportingHost() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.ErrorReportingHost);
    }

    /**
     * Gets the ErrorReportingHost.
     */
    public diameter.base.ErrorReportingHost getErrorReportingHost() throws NoSuchAttributeException {
        return (diameter.base.ErrorReportingHost)_data.getContainer().get(diameter.base.BaseAttributeName.ErrorReportingHost, 0);
    }

    /**
     * Sets the ErrorReportingHost.
     *
     * @param avp - the attribute value
     */
    public void setErrorReportingHost(diameter.base.ErrorReportingHost avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ErrorReportingHost, avp.getData(), true);
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
     * Tests whether there is any OriginAAAProtocol.
     */
    public boolean containsOriginAAAProtocol() {
        return _data.getContainer().contains(NasreqAttributeName.OriginAAAProtocol);
    }

    /**
     * Gets the OriginAAAProtocol.
     */
    public OriginAAAProtocol getOriginAAAProtocol() throws NoSuchAttributeException {
        return (OriginAAAProtocol)_data.getContainer().get(NasreqAttributeName.OriginAAAProtocol, 0);
    }

    /**
     * Sets the OriginAAAProtocol.
     *
     * @param avp - the attribute value
     */
    public void setOriginAAAProtocol(OriginAAAProtocol avp) {
        _data.getContainer().add(NasreqAttributeName.OriginAAAProtocol, avp.getData(), true);
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
     * Tests whether there is any NASIdentifier.
     */
    public boolean containsNASIdentifier() {
        return _data.getContainer().contains(NasreqAttributeName.NASIdentifier);
    }

    /**
     * Gets the NASIdentifier.
     */
    public NASIdentifier getNASIdentifier() throws NoSuchAttributeException {
        return (NASIdentifier)_data.getContainer().get(NasreqAttributeName.NASIdentifier, 0);
    }

    /**
     * Sets the NASIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setNASIdentifier(NASIdentifier avp) {
        _data.getContainer().add(NasreqAttributeName.NASIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any NASIPAddress.
     */
    public boolean containsNASIPAddress() {
        return _data.getContainer().contains(NasreqAttributeName.NASIPAddress);
    }

    /**
     * Gets the NASIPAddress.
     */
    public NASIPAddress getNASIPAddress() throws NoSuchAttributeException {
        return (NASIPAddress)_data.getContainer().get(NasreqAttributeName.NASIPAddress, 0);
    }

    /**
     * Sets the NASIPAddress.
     *
     * @param avp - the attribute value
     */
    public void setNASIPAddress(NASIPAddress avp) {
        _data.getContainer().add(NasreqAttributeName.NASIPAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any NASIPv6Address.
     */
    public boolean containsNASIPv6Address() {
        return _data.getContainer().contains(NasreqAttributeName.NASIPv6Address);
    }

    /**
     * Gets the NASIPv6Address.
     */
    public NASIPv6Address getNASIPv6Address() throws NoSuchAttributeException {
        return (NASIPv6Address)_data.getContainer().get(NasreqAttributeName.NASIPv6Address, 0);
    }

    /**
     * Sets the NASIPv6Address.
     *
     * @param avp - the attribute value
     */
    public void setNASIPv6Address(NASIPv6Address avp) {
        _data.getContainer().add(NasreqAttributeName.NASIPv6Address, avp.getData(), true);
    }

    /**
     * Tests whether there is any NASPort.
     */
    public boolean containsNASPort() {
        return _data.getContainer().contains(NasreqAttributeName.NASPort);
    }

    /**
     * Gets the NASPort.
     */
    public NASPort getNASPort() throws NoSuchAttributeException {
        return (NASPort)_data.getContainer().get(NasreqAttributeName.NASPort, 0);
    }

    /**
     * Sets the NASPort.
     *
     * @param avp - the attribute value
     */
    public void setNASPort(NASPort avp) {
        _data.getContainer().add(NasreqAttributeName.NASPort, avp.getData(), true);
    }

    /**
     * Tests whether there is any NASPortId.
     */
    public boolean containsNASPortId() {
        return _data.getContainer().contains(NasreqAttributeName.NASPortId);
    }

    /**
     * Gets the NASPortId.
     */
    public NASPortId getNASPortId() throws NoSuchAttributeException {
        return (NASPortId)_data.getContainer().get(NasreqAttributeName.NASPortId, 0);
    }

    /**
     * Sets the NASPortId.
     *
     * @param avp - the attribute value
     */
    public void setNASPortId(NASPortId avp) {
        _data.getContainer().add(NasreqAttributeName.NASPortId, avp.getData(), true);
    }

    /**
     * Tests whether there is any NASPortType.
     */
    public boolean containsNASPortType() {
        return _data.getContainer().contains(NasreqAttributeName.NASPortType);
    }

    /**
     * Gets the NASPortType.
     */
    public NASPortType getNASPortType() throws NoSuchAttributeException {
        return (NASPortType)_data.getContainer().get(NasreqAttributeName.NASPortType, 0);
    }

    /**
     * Sets the NASPortType.
     *
     * @param avp - the attribute value
     */
    public void setNASPortType(NASPortType avp) {
        _data.getContainer().add(NasreqAttributeName.NASPortType, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceType.
     */
    public boolean containsServiceType() {
        return _data.getContainer().contains(NasreqAttributeName.ServiceType);
    }

    /**
     * Gets the ServiceType.
     */
    public ServiceType getServiceType() throws NoSuchAttributeException {
        return (ServiceType)_data.getContainer().get(NasreqAttributeName.ServiceType, 0);
    }

    /**
     * Sets the ServiceType.
     *
     * @param avp - the attribute value
     */
    public void setServiceType(ServiceType avp) {
        _data.getContainer().add(NasreqAttributeName.ServiceType, avp.getData(), true);
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
     * Tests whether there is any AccountingRealtimeRequired.
     */
    public boolean containsAccountingRealtimeRequired() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AccountingRealtimeRequired);
    }

    /**
     * Gets the AccountingRealtimeRequired.
     */
    public diameter.base.AccountingRealtimeRequired getAccountingRealtimeRequired() throws NoSuchAttributeException {
        return (diameter.base.AccountingRealtimeRequired)_data.getContainer().get(diameter.base.BaseAttributeName.AccountingRealtimeRequired, 0);
    }

    /**
     * Sets the AccountingRealtimeRequired.
     *
     * @param avp - the attribute value
     */
    public void setAccountingRealtimeRequired(diameter.base.AccountingRealtimeRequired avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AccountingRealtimeRequired, avp.getData(), true);
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
     * Returns number of Class instances.
     */
    public int countClass() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.Class);
    }

    /**
     * Gets one Class.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.Class getClass(int index) throws NoSuchAttributeException {
        return (diameter.base.Class)_data.getContainer().get(diameter.base.BaseAttributeName.Class, index);
    }

    /**
     * Adds one Class.
     *
     * @param avp - the attribute value
     */
    public void addClass(diameter.base.Class avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.Class, avp.getData(), false);
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
        sb.append("    ResultCode:");
            try {
                sb.append(getResultCode()).append('\n');
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
        if (containsVendorSpecificApplicationId()) {
            sb.append("    VendorSpecificApplicationId:");
            try {
                sb.append(getVendorSpecificApplicationId()).append('\n');
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
        if (containsAccountingSubSessionId()) {
            sb.append("    AccountingSubSessionId:");
            try {
                sb.append(getAccountingSubSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctSessionId()) {
            sb.append("    AcctSessionId:");
            try {
                sb.append(getAcctSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctMultiSessionId()) {
            sb.append("    AcctMultiSessionId:");
            try {
                sb.append(getAcctMultiSessionId()).append('\n');
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
        if (containsErrorMessage()) {
            sb.append("    ErrorMessage:");
            try {
                sb.append(getErrorMessage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsErrorReportingHost()) {
            sb.append("    ErrorReportingHost:");
            try {
                sb.append(getErrorReportingHost()).append('\n');
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
        if (containsOriginAAAProtocol()) {
            sb.append("    OriginAAAProtocol:");
            try {
                sb.append(getOriginAAAProtocol()).append('\n');
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
        if (containsNASIdentifier()) {
            sb.append("    NASIdentifier:");
            try {
                sb.append(getNASIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNASIPAddress()) {
            sb.append("    NASIPAddress:");
            try {
                sb.append(getNASIPAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNASIPv6Address()) {
            sb.append("    NASIPv6Address:");
            try {
                sb.append(getNASIPv6Address()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNASPort()) {
            sb.append("    NASPort:");
            try {
                sb.append(getNASPort()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNASPortId()) {
            sb.append("    NASPortId:");
            try {
                sb.append(getNASPortId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNASPortType()) {
            sb.append("    NASPortType:");
            try {
                sb.append(getNASPortType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceType()) {
            sb.append("    ServiceType:");
            try {
                sb.append(getServiceType()).append('\n');
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
        if (containsAccountingRealtimeRequired()) {
            sb.append("    AccountingRealtimeRequired:");
            try {
                sb.append(getAccountingRealtimeRequired()).append('\n');
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
        for (int i = 0; i < countClass(); ++i) {
            sb.append("    Class:");
            try {
                sb.append(getClass(i)).append('\n');
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
        if (getCommandCode() != 271 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
