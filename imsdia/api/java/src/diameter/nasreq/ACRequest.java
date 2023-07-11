package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ACR message [BASE] is sent by the NAS to report its session information
 * to a target server downstream. Either of Acct-Application-Id or
 * Vendor-Specific-Application-Id AVPs MUST be present. If the
 * Vendor-Specific-Application-Id grouped AVP is present, it must have an
 * Acct-Application-Id inside.
 * The AVPs listed in the Base MUST be assumed to be present, as appropriate.
 * NAS service-specific accounting AVPs SHOULD be present as described in
 * section 8 and the rest of this specification.
 */
public class ACRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new ACRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public ACRequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 271, 1);
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
     * Tests whether there is any AcctDelayTime.
     */
    public boolean containsAcctDelayTime() {
        return _data.getContainer().contains(NasreqAttributeName.AcctDelayTime);
    }

    /**
     * Gets the AcctDelayTime.
     */
    public AcctDelayTime getAcctDelayTime() throws NoSuchAttributeException {
        return (AcctDelayTime)_data.getContainer().get(NasreqAttributeName.AcctDelayTime, 0);
    }

    /**
     * Sets the AcctDelayTime.
     *
     * @param avp - the attribute value
     */
    public void setAcctDelayTime(AcctDelayTime avp) {
        _data.getContainer().add(NasreqAttributeName.AcctDelayTime, avp.getData(), true);
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
     * Tests whether there is any AccountingInputOctets.
     */
    public boolean containsAccountingInputOctets() {
        return _data.getContainer().contains(NasreqAttributeName.AccountingInputOctets);
    }

    /**
     * Gets the AccountingInputOctets.
     */
    public AccountingInputOctets getAccountingInputOctets() throws NoSuchAttributeException {
        return (AccountingInputOctets)_data.getContainer().get(NasreqAttributeName.AccountingInputOctets, 0);
    }

    /**
     * Sets the AccountingInputOctets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingInputOctets(AccountingInputOctets avp) {
        _data.getContainer().add(NasreqAttributeName.AccountingInputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingInputPackets.
     */
    public boolean containsAccountingInputPackets() {
        return _data.getContainer().contains(NasreqAttributeName.AccountingInputPackets);
    }

    /**
     * Gets the AccountingInputPackets.
     */
    public AccountingInputPackets getAccountingInputPackets() throws NoSuchAttributeException {
        return (AccountingInputPackets)_data.getContainer().get(NasreqAttributeName.AccountingInputPackets, 0);
    }

    /**
     * Sets the AccountingInputPackets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingInputPackets(AccountingInputPackets avp) {
        _data.getContainer().add(NasreqAttributeName.AccountingInputPackets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingOutputOctets.
     */
    public boolean containsAccountingOutputOctets() {
        return _data.getContainer().contains(NasreqAttributeName.AccountingOutputOctets);
    }

    /**
     * Gets the AccountingOutputOctets.
     */
    public AccountingOutputOctets getAccountingOutputOctets() throws NoSuchAttributeException {
        return (AccountingOutputOctets)_data.getContainer().get(NasreqAttributeName.AccountingOutputOctets, 0);
    }

    /**
     * Sets the AccountingOutputOctets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingOutputOctets(AccountingOutputOctets avp) {
        _data.getContainer().add(NasreqAttributeName.AccountingOutputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingOutputPackets.
     */
    public boolean containsAccountingOutputPackets() {
        return _data.getContainer().contains(NasreqAttributeName.AccountingOutputPackets);
    }

    /**
     * Gets the AccountingOutputPackets.
     */
    public AccountingOutputPackets getAccountingOutputPackets() throws NoSuchAttributeException {
        return (AccountingOutputPackets)_data.getContainer().get(NasreqAttributeName.AccountingOutputPackets, 0);
    }

    /**
     * Sets the AccountingOutputPackets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingOutputPackets(AccountingOutputPackets avp) {
        _data.getContainer().add(NasreqAttributeName.AccountingOutputPackets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctAuthentic.
     */
    public boolean containsAcctAuthentic() {
        return _data.getContainer().contains(NasreqAttributeName.AcctAuthentic);
    }

    /**
     * Gets the AcctAuthentic.
     */
    public AcctAuthentic getAcctAuthentic() throws NoSuchAttributeException {
        return (AcctAuthentic)_data.getContainer().get(NasreqAttributeName.AcctAuthentic, 0);
    }

    /**
     * Sets the AcctAuthentic.
     *
     * @param avp - the attribute value
     */
    public void setAcctAuthentic(AcctAuthentic avp) {
        _data.getContainer().add(NasreqAttributeName.AcctAuthentic, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingAuthMethod.
     */
    public boolean containsAccountingAuthMethod() {
        return _data.getContainer().contains(NasreqAttributeName.AccountingAuthMethod);
    }

    /**
     * Gets the AccountingAuthMethod.
     */
    public AccountingAuthMethod getAccountingAuthMethod() throws NoSuchAttributeException {
        return (AccountingAuthMethod)_data.getContainer().get(NasreqAttributeName.AccountingAuthMethod, 0);
    }

    /**
     * Sets the AccountingAuthMethod.
     *
     * @param avp - the attribute value
     */
    public void setAccountingAuthMethod(AccountingAuthMethod avp) {
        _data.getContainer().add(NasreqAttributeName.AccountingAuthMethod, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctLinkCount.
     */
    public boolean containsAcctLinkCount() {
        return _data.getContainer().contains(NasreqAttributeName.AcctLinkCount);
    }

    /**
     * Gets the AcctLinkCount.
     */
    public AcctLinkCount getAcctLinkCount() throws NoSuchAttributeException {
        return (AcctLinkCount)_data.getContainer().get(NasreqAttributeName.AcctLinkCount, 0);
    }

    /**
     * Sets the AcctLinkCount.
     *
     * @param avp - the attribute value
     */
    public void setAcctLinkCount(AcctLinkCount avp) {
        _data.getContainer().add(NasreqAttributeName.AcctLinkCount, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctSessionTime.
     */
    public boolean containsAcctSessionTime() {
        return _data.getContainer().contains(NasreqAttributeName.AcctSessionTime);
    }

    /**
     * Gets the AcctSessionTime.
     */
    public AcctSessionTime getAcctSessionTime() throws NoSuchAttributeException {
        return (AcctSessionTime)_data.getContainer().get(NasreqAttributeName.AcctSessionTime, 0);
    }

    /**
     * Sets the AcctSessionTime.
     *
     * @param avp - the attribute value
     */
    public void setAcctSessionTime(AcctSessionTime avp) {
        _data.getContainer().add(NasreqAttributeName.AcctSessionTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctTunnelConnection.
     */
    public boolean containsAcctTunnelConnection() {
        return _data.getContainer().contains(NasreqAttributeName.AcctTunnelConnection);
    }

    /**
     * Gets the AcctTunnelConnection.
     */
    public AcctTunnelConnection getAcctTunnelConnection() throws NoSuchAttributeException {
        return (AcctTunnelConnection)_data.getContainer().get(NasreqAttributeName.AcctTunnelConnection, 0);
    }

    /**
     * Sets the AcctTunnelConnection.
     *
     * @param avp - the attribute value
     */
    public void setAcctTunnelConnection(AcctTunnelConnection avp) {
        _data.getContainer().add(NasreqAttributeName.AcctTunnelConnection, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctTunnelPacketsLost.
     */
    public boolean containsAcctTunnelPacketsLost() {
        return _data.getContainer().contains(NasreqAttributeName.AcctTunnelPacketsLost);
    }

    /**
     * Gets the AcctTunnelPacketsLost.
     */
    public AcctTunnelPacketsLost getAcctTunnelPacketsLost() throws NoSuchAttributeException {
        return (AcctTunnelPacketsLost)_data.getContainer().get(NasreqAttributeName.AcctTunnelPacketsLost, 0);
    }

    /**
     * Sets the AcctTunnelPacketsLost.
     *
     * @param avp - the attribute value
     */
    public void setAcctTunnelPacketsLost(AcctTunnelPacketsLost avp) {
        _data.getContainer().add(NasreqAttributeName.AcctTunnelPacketsLost, avp.getData(), true);
    }

    /**
     * Tests whether there is any CallbackId.
     */
    public boolean containsCallbackId() {
        return _data.getContainer().contains(NasreqAttributeName.CallbackId);
    }

    /**
     * Gets the CallbackId.
     */
    public CallbackId getCallbackId() throws NoSuchAttributeException {
        return (CallbackId)_data.getContainer().get(NasreqAttributeName.CallbackId, 0);
    }

    /**
     * Sets the CallbackId.
     *
     * @param avp - the attribute value
     */
    public void setCallbackId(CallbackId avp) {
        _data.getContainer().add(NasreqAttributeName.CallbackId, avp.getData(), true);
    }

    /**
     * Tests whether there is any CallbackNumber.
     */
    public boolean containsCallbackNumber() {
        return _data.getContainer().contains(NasreqAttributeName.CallbackNumber);
    }

    /**
     * Gets the CallbackNumber.
     */
    public CallbackNumber getCallbackNumber() throws NoSuchAttributeException {
        return (CallbackNumber)_data.getContainer().get(NasreqAttributeName.CallbackNumber, 0);
    }

    /**
     * Sets the CallbackNumber.
     *
     * @param avp - the attribute value
     */
    public void setCallbackNumber(CallbackNumber avp) {
        _data.getContainer().add(NasreqAttributeName.CallbackNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CalledStationId.
     */
    public boolean containsCalledStationId() {
        return _data.getContainer().contains(NasreqAttributeName.CalledStationId);
    }

    /**
     * Gets the CalledStationId.
     */
    public CalledStationId getCalledStationId() throws NoSuchAttributeException {
        return (CalledStationId)_data.getContainer().get(NasreqAttributeName.CalledStationId, 0);
    }

    /**
     * Sets the CalledStationId.
     *
     * @param avp - the attribute value
     */
    public void setCalledStationId(CalledStationId avp) {
        _data.getContainer().add(NasreqAttributeName.CalledStationId, avp.getData(), true);
    }

    /**
     * Tests whether there is any CallingStationId.
     */
    public boolean containsCallingStationId() {
        return _data.getContainer().contains(NasreqAttributeName.CallingStationId);
    }

    /**
     * Gets the CallingStationId.
     */
    public CallingStationId getCallingStationId() throws NoSuchAttributeException {
        return (CallingStationId)_data.getContainer().get(NasreqAttributeName.CallingStationId, 0);
    }

    /**
     * Sets the CallingStationId.
     *
     * @param avp - the attribute value
     */
    public void setCallingStationId(CallingStationId avp) {
        _data.getContainer().add(NasreqAttributeName.CallingStationId, avp.getData(), true);
    }

    /**
     * Returns number of ConnectInfo instances.
     */
    public int countConnectInfo() {
        return _data.getContainer().count(NasreqAttributeName.ConnectInfo);
    }

    /**
     * Gets one ConnectInfo.
     *
     * @param index - the index of the attribute to return
     */
    public ConnectInfo getConnectInfo(int index) throws NoSuchAttributeException {
        return (ConnectInfo)_data.getContainer().get(NasreqAttributeName.ConnectInfo, index);
    }

    /**
     * Adds one ConnectInfo.
     *
     * @param avp - the attribute value
     */
    public void addConnectInfo(ConnectInfo avp) {
        _data.getContainer().add(NasreqAttributeName.ConnectInfo, avp.getData(), false);
    }

    /**
     * Tests whether there is any OriginatingLineInfo.
     */
    public boolean containsOriginatingLineInfo() {
        return _data.getContainer().contains(NasreqAttributeName.OriginatingLineInfo);
    }

    /**
     * Gets the OriginatingLineInfo.
     */
    public OriginatingLineInfo getOriginatingLineInfo() throws NoSuchAttributeException {
        return (OriginatingLineInfo)_data.getContainer().get(NasreqAttributeName.OriginatingLineInfo, 0);
    }

    /**
     * Sets the OriginatingLineInfo.
     *
     * @param avp - the attribute value
     */
    public void setOriginatingLineInfo(OriginatingLineInfo avp) {
        _data.getContainer().add(NasreqAttributeName.OriginatingLineInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any AuthorizationLifetime.
     */
    public boolean containsAuthorizationLifetime() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AuthorizationLifetime);
    }

    /**
     * Gets the AuthorizationLifetime.
     */
    public diameter.base.AuthorizationLifetime getAuthorizationLifetime() throws NoSuchAttributeException {
        return (diameter.base.AuthorizationLifetime)_data.getContainer().get(diameter.base.BaseAttributeName.AuthorizationLifetime, 0);
    }

    /**
     * Sets the AuthorizationLifetime.
     *
     * @param avp - the attribute value
     */
    public void setAuthorizationLifetime(diameter.base.AuthorizationLifetime avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthorizationLifetime, avp.getData(), true);
    }

    /**
     * Tests whether there is any SessionTimeout.
     */
    public boolean containsSessionTimeout() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.SessionTimeout);
    }

    /**
     * Gets the SessionTimeout.
     */
    public diameter.base.SessionTimeout getSessionTimeout() throws NoSuchAttributeException {
        return (diameter.base.SessionTimeout)_data.getContainer().get(diameter.base.BaseAttributeName.SessionTimeout, 0);
    }

    /**
     * Sets the SessionTimeout.
     *
     * @param avp - the attribute value
     */
    public void setSessionTimeout(diameter.base.SessionTimeout avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.SessionTimeout, avp.getData(), true);
    }

    /**
     * Tests whether there is any IdleTimeout.
     */
    public boolean containsIdleTimeout() {
        return _data.getContainer().contains(NasreqAttributeName.IdleTimeout);
    }

    /**
     * Gets the IdleTimeout.
     */
    public IdleTimeout getIdleTimeout() throws NoSuchAttributeException {
        return (IdleTimeout)_data.getContainer().get(NasreqAttributeName.IdleTimeout, 0);
    }

    /**
     * Sets the IdleTimeout.
     *
     * @param avp - the attribute value
     */
    public void setIdleTimeout(IdleTimeout avp) {
        _data.getContainer().add(NasreqAttributeName.IdleTimeout, avp.getData(), true);
    }

    /**
     * Tests whether there is any PortLimit.
     */
    public boolean containsPortLimit() {
        return _data.getContainer().contains(NasreqAttributeName.PortLimit);
    }

    /**
     * Gets the PortLimit.
     */
    public PortLimit getPortLimit() throws NoSuchAttributeException {
        return (PortLimit)_data.getContainer().get(NasreqAttributeName.PortLimit, 0);
    }

    /**
     * Sets the PortLimit.
     *
     * @param avp - the attribute value
     */
    public void setPortLimit(PortLimit avp) {
        _data.getContainer().add(NasreqAttributeName.PortLimit, avp.getData(), true);
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
     * Returns number of FilterId instances.
     */
    public int countFilterId() {
        return _data.getContainer().count(NasreqAttributeName.FilterId);
    }

    /**
     * Gets one FilterId.
     *
     * @param index - the index of the attribute to return
     */
    public FilterId getFilterId(int index) throws NoSuchAttributeException {
        return (FilterId)_data.getContainer().get(NasreqAttributeName.FilterId, index);
    }

    /**
     * Adds one FilterId.
     *
     * @param avp - the attribute value
     */
    public void addFilterId(FilterId avp) {
        _data.getContainer().add(NasreqAttributeName.FilterId, avp.getData(), false);
    }

    /**
     * Returns number of NASFilterRule instances.
     */
    public int countNASFilterRule() {
        return _data.getContainer().count(NasreqAttributeName.NASFilterRule);
    }

    /**
     * Gets one NASFilterRule.
     *
     * @param index - the index of the attribute to return
     */
    public NASFilterRule getNASFilterRule(int index) throws NoSuchAttributeException {
        return (NASFilterRule)_data.getContainer().get(NasreqAttributeName.NASFilterRule, index);
    }

    /**
     * Adds one NASFilterRule.
     *
     * @param avp - the attribute value
     */
    public void addNASFilterRule(NASFilterRule avp) {
        _data.getContainer().add(NasreqAttributeName.NASFilterRule, avp.getData(), false);
    }

    /**
     * Returns number of QoSFilterRule instances.
     */
    public int countQoSFilterRule() {
        return _data.getContainer().count(NasreqAttributeName.QoSFilterRule);
    }

    /**
     * Gets one QoSFilterRule.
     *
     * @param index - the index of the attribute to return
     */
    public QoSFilterRule getQoSFilterRule(int index) throws NoSuchAttributeException {
        return (QoSFilterRule)_data.getContainer().get(NasreqAttributeName.QoSFilterRule, index);
    }

    /**
     * Adds one QoSFilterRule.
     *
     * @param avp - the attribute value
     */
    public void addQoSFilterRule(QoSFilterRule avp) {
        _data.getContainer().add(NasreqAttributeName.QoSFilterRule, avp.getData(), false);
    }

    /**
     * Tests whether there is any FramedAppletalkLink.
     */
    public boolean containsFramedAppletalkLink() {
        return _data.getContainer().contains(NasreqAttributeName.FramedAppletalkLink);
    }

    /**
     * Gets the FramedAppletalkLink.
     */
    public FramedAppletalkLink getFramedAppletalkLink() throws NoSuchAttributeException {
        return (FramedAppletalkLink)_data.getContainer().get(NasreqAttributeName.FramedAppletalkLink, 0);
    }

    /**
     * Sets the FramedAppletalkLink.
     *
     * @param avp - the attribute value
     */
    public void setFramedAppletalkLink(FramedAppletalkLink avp) {
        _data.getContainer().add(NasreqAttributeName.FramedAppletalkLink, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedAppletalkNetwork.
     */
    public boolean containsFramedAppletalkNetwork() {
        return _data.getContainer().contains(NasreqAttributeName.FramedAppletalkNetwork);
    }

    /**
     * Gets the FramedAppletalkNetwork.
     */
    public FramedAppletalkNetwork getFramedAppletalkNetwork() throws NoSuchAttributeException {
        return (FramedAppletalkNetwork)_data.getContainer().get(NasreqAttributeName.FramedAppletalkNetwork, 0);
    }

    /**
     * Sets the FramedAppletalkNetwork.
     *
     * @param avp - the attribute value
     */
    public void setFramedAppletalkNetwork(FramedAppletalkNetwork avp) {
        _data.getContainer().add(NasreqAttributeName.FramedAppletalkNetwork, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedAppletalkZone.
     */
    public boolean containsFramedAppletalkZone() {
        return _data.getContainer().contains(NasreqAttributeName.FramedAppletalkZone);
    }

    /**
     * Gets the FramedAppletalkZone.
     */
    public FramedAppletalkZone getFramedAppletalkZone() throws NoSuchAttributeException {
        return (FramedAppletalkZone)_data.getContainer().get(NasreqAttributeName.FramedAppletalkZone, 0);
    }

    /**
     * Sets the FramedAppletalkZone.
     *
     * @param avp - the attribute value
     */
    public void setFramedAppletalkZone(FramedAppletalkZone avp) {
        _data.getContainer().add(NasreqAttributeName.FramedAppletalkZone, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedCompression.
     */
    public boolean containsFramedCompression() {
        return _data.getContainer().contains(NasreqAttributeName.FramedCompression);
    }

    /**
     * Gets the FramedCompression.
     */
    public FramedCompression getFramedCompression() throws NoSuchAttributeException {
        return (FramedCompression)_data.getContainer().get(NasreqAttributeName.FramedCompression, 0);
    }

    /**
     * Sets the FramedCompression.
     *
     * @param avp - the attribute value
     */
    public void setFramedCompression(FramedCompression avp) {
        _data.getContainer().add(NasreqAttributeName.FramedCompression, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedInterfaceId.
     */
    public boolean containsFramedInterfaceId() {
        return _data.getContainer().contains(NasreqAttributeName.FramedInterfaceId);
    }

    /**
     * Gets the FramedInterfaceId.
     */
    public FramedInterfaceId getFramedInterfaceId() throws NoSuchAttributeException {
        return (FramedInterfaceId)_data.getContainer().get(NasreqAttributeName.FramedInterfaceId, 0);
    }

    /**
     * Sets the FramedInterfaceId.
     *
     * @param avp - the attribute value
     */
    public void setFramedInterfaceId(FramedInterfaceId avp) {
        _data.getContainer().add(NasreqAttributeName.FramedInterfaceId, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedIPAddress.
     */
    public boolean containsFramedIPAddress() {
        return _data.getContainer().contains(NasreqAttributeName.FramedIPAddress);
    }

    /**
     * Gets the FramedIPAddress.
     */
    public FramedIPAddress getFramedIPAddress() throws NoSuchAttributeException {
        return (FramedIPAddress)_data.getContainer().get(NasreqAttributeName.FramedIPAddress, 0);
    }

    /**
     * Sets the FramedIPAddress.
     *
     * @param avp - the attribute value
     */
    public void setFramedIPAddress(FramedIPAddress avp) {
        _data.getContainer().add(NasreqAttributeName.FramedIPAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedIPNetmask.
     */
    public boolean containsFramedIPNetmask() {
        return _data.getContainer().contains(NasreqAttributeName.FramedIPNetmask);
    }

    /**
     * Gets the FramedIPNetmask.
     */
    public FramedIPNetmask getFramedIPNetmask() throws NoSuchAttributeException {
        return (FramedIPNetmask)_data.getContainer().get(NasreqAttributeName.FramedIPNetmask, 0);
    }

    /**
     * Sets the FramedIPNetmask.
     *
     * @param avp - the attribute value
     */
    public void setFramedIPNetmask(FramedIPNetmask avp) {
        _data.getContainer().add(NasreqAttributeName.FramedIPNetmask, avp.getData(), true);
    }

    /**
     * Returns number of FramedIPv6Prefix instances.
     */
    public int countFramedIPv6Prefix() {
        return _data.getContainer().count(NasreqAttributeName.FramedIPv6Prefix);
    }

    /**
     * Gets one FramedIPv6Prefix.
     *
     * @param index - the index of the attribute to return
     */
    public FramedIPv6Prefix getFramedIPv6Prefix(int index) throws NoSuchAttributeException {
        return (FramedIPv6Prefix)_data.getContainer().get(NasreqAttributeName.FramedIPv6Prefix, index);
    }

    /**
     * Adds one FramedIPv6Prefix.
     *
     * @param avp - the attribute value
     */
    public void addFramedIPv6Prefix(FramedIPv6Prefix avp) {
        _data.getContainer().add(NasreqAttributeName.FramedIPv6Prefix, avp.getData(), false);
    }

    /**
     * Tests whether there is any FramedIPv6Pool.
     */
    public boolean containsFramedIPv6Pool() {
        return _data.getContainer().contains(NasreqAttributeName.FramedIPv6Pool);
    }

    /**
     * Gets the FramedIPv6Pool.
     */
    public FramedIPv6Pool getFramedIPv6Pool() throws NoSuchAttributeException {
        return (FramedIPv6Pool)_data.getContainer().get(NasreqAttributeName.FramedIPv6Pool, 0);
    }

    /**
     * Sets the FramedIPv6Pool.
     *
     * @param avp - the attribute value
     */
    public void setFramedIPv6Pool(FramedIPv6Pool avp) {
        _data.getContainer().add(NasreqAttributeName.FramedIPv6Pool, avp.getData(), true);
    }

    /**
     * Returns number of FramedIPv6Route instances.
     */
    public int countFramedIPv6Route() {
        return _data.getContainer().count(NasreqAttributeName.FramedIPv6Route);
    }

    /**
     * Gets one FramedIPv6Route.
     *
     * @param index - the index of the attribute to return
     */
    public FramedIPv6Route getFramedIPv6Route(int index) throws NoSuchAttributeException {
        return (FramedIPv6Route)_data.getContainer().get(NasreqAttributeName.FramedIPv6Route, index);
    }

    /**
     * Adds one FramedIPv6Route.
     *
     * @param avp - the attribute value
     */
    public void addFramedIPv6Route(FramedIPv6Route avp) {
        _data.getContainer().add(NasreqAttributeName.FramedIPv6Route, avp.getData(), false);
    }

    /**
     * Tests whether there is any FramedIPXNetwork.
     */
    public boolean containsFramedIPXNetwork() {
        return _data.getContainer().contains(NasreqAttributeName.FramedIPXNetwork);
    }

    /**
     * Gets the FramedIPXNetwork.
     */
    public FramedIPXNetwork getFramedIPXNetwork() throws NoSuchAttributeException {
        return (FramedIPXNetwork)_data.getContainer().get(NasreqAttributeName.FramedIPXNetwork, 0);
    }

    /**
     * Sets the FramedIPXNetwork.
     *
     * @param avp - the attribute value
     */
    public void setFramedIPXNetwork(FramedIPXNetwork avp) {
        _data.getContainer().add(NasreqAttributeName.FramedIPXNetwork, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedMTU.
     */
    public boolean containsFramedMTU() {
        return _data.getContainer().contains(NasreqAttributeName.FramedMTU);
    }

    /**
     * Gets the FramedMTU.
     */
    public FramedMTU getFramedMTU() throws NoSuchAttributeException {
        return (FramedMTU)_data.getContainer().get(NasreqAttributeName.FramedMTU, 0);
    }

    /**
     * Sets the FramedMTU.
     *
     * @param avp - the attribute value
     */
    public void setFramedMTU(FramedMTU avp) {
        _data.getContainer().add(NasreqAttributeName.FramedMTU, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedPool.
     */
    public boolean containsFramedPool() {
        return _data.getContainer().contains(NasreqAttributeName.FramedPool);
    }

    /**
     * Gets the FramedPool.
     */
    public FramedPool getFramedPool() throws NoSuchAttributeException {
        return (FramedPool)_data.getContainer().get(NasreqAttributeName.FramedPool, 0);
    }

    /**
     * Sets the FramedPool.
     *
     * @param avp - the attribute value
     */
    public void setFramedPool(FramedPool avp) {
        _data.getContainer().add(NasreqAttributeName.FramedPool, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedProtocol.
     */
    public boolean containsFramedProtocol() {
        return _data.getContainer().contains(NasreqAttributeName.FramedProtocol);
    }

    /**
     * Gets the FramedProtocol.
     */
    public FramedProtocol getFramedProtocol() throws NoSuchAttributeException {
        return (FramedProtocol)_data.getContainer().get(NasreqAttributeName.FramedProtocol, 0);
    }

    /**
     * Sets the FramedProtocol.
     *
     * @param avp - the attribute value
     */
    public void setFramedProtocol(FramedProtocol avp) {
        _data.getContainer().add(NasreqAttributeName.FramedProtocol, avp.getData(), true);
    }

    /**
     * Returns number of FramedRoute instances.
     */
    public int countFramedRoute() {
        return _data.getContainer().count(NasreqAttributeName.FramedRoute);
    }

    /**
     * Gets one FramedRoute.
     *
     * @param index - the index of the attribute to return
     */
    public FramedRoute getFramedRoute(int index) throws NoSuchAttributeException {
        return (FramedRoute)_data.getContainer().get(NasreqAttributeName.FramedRoute, index);
    }

    /**
     * Adds one FramedRoute.
     *
     * @param avp - the attribute value
     */
    public void addFramedRoute(FramedRoute avp) {
        _data.getContainer().add(NasreqAttributeName.FramedRoute, avp.getData(), false);
    }

    /**
     * Tests whether there is any FramedRouting.
     */
    public boolean containsFramedRouting() {
        return _data.getContainer().contains(NasreqAttributeName.FramedRouting);
    }

    /**
     * Gets the FramedRouting.
     */
    public FramedRouting getFramedRouting() throws NoSuchAttributeException {
        return (FramedRouting)_data.getContainer().get(NasreqAttributeName.FramedRouting, 0);
    }

    /**
     * Sets the FramedRouting.
     *
     * @param avp - the attribute value
     */
    public void setFramedRouting(FramedRouting avp) {
        _data.getContainer().add(NasreqAttributeName.FramedRouting, avp.getData(), true);
    }

    /**
     * Returns number of LoginIPHost instances.
     */
    public int countLoginIPHost() {
        return _data.getContainer().count(NasreqAttributeName.LoginIPHost);
    }

    /**
     * Gets one LoginIPHost.
     *
     * @param index - the index of the attribute to return
     */
    public LoginIPHost getLoginIPHost(int index) throws NoSuchAttributeException {
        return (LoginIPHost)_data.getContainer().get(NasreqAttributeName.LoginIPHost, index);
    }

    /**
     * Adds one LoginIPHost.
     *
     * @param avp - the attribute value
     */
    public void addLoginIPHost(LoginIPHost avp) {
        _data.getContainer().add(NasreqAttributeName.LoginIPHost, avp.getData(), false);
    }

    /**
     * Returns number of LoginIPv6Host instances.
     */
    public int countLoginIPv6Host() {
        return _data.getContainer().count(NasreqAttributeName.LoginIPv6Host);
    }

    /**
     * Gets one LoginIPv6Host.
     *
     * @param index - the index of the attribute to return
     */
    public LoginIPv6Host getLoginIPv6Host(int index) throws NoSuchAttributeException {
        return (LoginIPv6Host)_data.getContainer().get(NasreqAttributeName.LoginIPv6Host, index);
    }

    /**
     * Adds one LoginIPv6Host.
     *
     * @param avp - the attribute value
     */
    public void addLoginIPv6Host(LoginIPv6Host avp) {
        _data.getContainer().add(NasreqAttributeName.LoginIPv6Host, avp.getData(), false);
    }

    /**
     * Tests whether there is any LoginLATGroup.
     */
    public boolean containsLoginLATGroup() {
        return _data.getContainer().contains(NasreqAttributeName.LoginLATGroup);
    }

    /**
     * Gets the LoginLATGroup.
     */
    public LoginLATGroup getLoginLATGroup() throws NoSuchAttributeException {
        return (LoginLATGroup)_data.getContainer().get(NasreqAttributeName.LoginLATGroup, 0);
    }

    /**
     * Sets the LoginLATGroup.
     *
     * @param avp - the attribute value
     */
    public void setLoginLATGroup(LoginLATGroup avp) {
        _data.getContainer().add(NasreqAttributeName.LoginLATGroup, avp.getData(), true);
    }

    /**
     * Tests whether there is any LoginLATNode.
     */
    public boolean containsLoginLATNode() {
        return _data.getContainer().contains(NasreqAttributeName.LoginLATNode);
    }

    /**
     * Gets the LoginLATNode.
     */
    public LoginLATNode getLoginLATNode() throws NoSuchAttributeException {
        return (LoginLATNode)_data.getContainer().get(NasreqAttributeName.LoginLATNode, 0);
    }

    /**
     * Sets the LoginLATNode.
     *
     * @param avp - the attribute value
     */
    public void setLoginLATNode(LoginLATNode avp) {
        _data.getContainer().add(NasreqAttributeName.LoginLATNode, avp.getData(), true);
    }

    /**
     * Tests whether there is any LoginLATPort.
     */
    public boolean containsLoginLATPort() {
        return _data.getContainer().contains(NasreqAttributeName.LoginLATPort);
    }

    /**
     * Gets the LoginLATPort.
     */
    public LoginLATPort getLoginLATPort() throws NoSuchAttributeException {
        return (LoginLATPort)_data.getContainer().get(NasreqAttributeName.LoginLATPort, 0);
    }

    /**
     * Sets the LoginLATPort.
     *
     * @param avp - the attribute value
     */
    public void setLoginLATPort(LoginLATPort avp) {
        _data.getContainer().add(NasreqAttributeName.LoginLATPort, avp.getData(), true);
    }

    /**
     * Tests whether there is any LoginLATService.
     */
    public boolean containsLoginLATService() {
        return _data.getContainer().contains(NasreqAttributeName.LoginLATService);
    }

    /**
     * Gets the LoginLATService.
     */
    public LoginLATService getLoginLATService() throws NoSuchAttributeException {
        return (LoginLATService)_data.getContainer().get(NasreqAttributeName.LoginLATService, 0);
    }

    /**
     * Sets the LoginLATService.
     *
     * @param avp - the attribute value
     */
    public void setLoginLATService(LoginLATService avp) {
        _data.getContainer().add(NasreqAttributeName.LoginLATService, avp.getData(), true);
    }

    /**
     * Tests whether there is any LoginService.
     */
    public boolean containsLoginService() {
        return _data.getContainer().contains(NasreqAttributeName.LoginService);
    }

    /**
     * Gets the LoginService.
     */
    public LoginService getLoginService() throws NoSuchAttributeException {
        return (LoginService)_data.getContainer().get(NasreqAttributeName.LoginService, 0);
    }

    /**
     * Sets the LoginService.
     *
     * @param avp - the attribute value
     */
    public void setLoginService(LoginService avp) {
        _data.getContainer().add(NasreqAttributeName.LoginService, avp.getData(), true);
    }

    /**
     * Tests whether there is any LoginTCPPort.
     */
    public boolean containsLoginTCPPort() {
        return _data.getContainer().contains(NasreqAttributeName.LoginTCPPort);
    }

    /**
     * Gets the LoginTCPPort.
     */
    public LoginTCPPort getLoginTCPPort() throws NoSuchAttributeException {
        return (LoginTCPPort)_data.getContainer().get(NasreqAttributeName.LoginTCPPort, 0);
    }

    /**
     * Sets the LoginTCPPort.
     *
     * @param avp - the attribute value
     */
    public void setLoginTCPPort(LoginTCPPort avp) {
        _data.getContainer().add(NasreqAttributeName.LoginTCPPort, avp.getData(), true);
    }

    /**
     * Returns number of Tunneling instances.
     */
    public int countTunneling() {
        return _data.getContainer().count(NasreqAttributeName.Tunneling);
    }

    /**
     * Gets one Tunneling.
     *
     * @param index - the index of the attribute to return
     */
    public Tunneling getTunneling(int index) throws NoSuchAttributeException {
        return (Tunneling)_data.getContainer().get(NasreqAttributeName.Tunneling, index);
    }

    /**
     * Adds one Tunneling.
     *
     * @param avp - the attribute value
     */
    public void addTunneling(Tunneling avp) {
        _data.getContainer().add(NasreqAttributeName.Tunneling, avp.getData(), false);
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
        if (containsDestinationHost()) {
            sb.append("    DestinationHost:");
            try {
                sb.append(getDestinationHost()).append('\n');
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
        if (containsAcctDelayTime()) {
            sb.append("    AcctDelayTime:");
            try {
                sb.append(getAcctDelayTime()).append('\n');
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
        for (int i = 0; i < countClass(); ++i) {
            sb.append("    Class:");
            try {
                sb.append(getClass(i)).append('\n');
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
        if (containsAccountingInputOctets()) {
            sb.append("    AccountingInputOctets:");
            try {
                sb.append(getAccountingInputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingInputPackets()) {
            sb.append("    AccountingInputPackets:");
            try {
                sb.append(getAccountingInputPackets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingOutputOctets()) {
            sb.append("    AccountingOutputOctets:");
            try {
                sb.append(getAccountingOutputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingOutputPackets()) {
            sb.append("    AccountingOutputPackets:");
            try {
                sb.append(getAccountingOutputPackets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctAuthentic()) {
            sb.append("    AcctAuthentic:");
            try {
                sb.append(getAcctAuthentic()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingAuthMethod()) {
            sb.append("    AccountingAuthMethod:");
            try {
                sb.append(getAccountingAuthMethod()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctLinkCount()) {
            sb.append("    AcctLinkCount:");
            try {
                sb.append(getAcctLinkCount()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctSessionTime()) {
            sb.append("    AcctSessionTime:");
            try {
                sb.append(getAcctSessionTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctTunnelConnection()) {
            sb.append("    AcctTunnelConnection:");
            try {
                sb.append(getAcctTunnelConnection()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctTunnelPacketsLost()) {
            sb.append("    AcctTunnelPacketsLost:");
            try {
                sb.append(getAcctTunnelPacketsLost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCallbackId()) {
            sb.append("    CallbackId:");
            try {
                sb.append(getCallbackId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCallbackNumber()) {
            sb.append("    CallbackNumber:");
            try {
                sb.append(getCallbackNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCalledStationId()) {
            sb.append("    CalledStationId:");
            try {
                sb.append(getCalledStationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCallingStationId()) {
            sb.append("    CallingStationId:");
            try {
                sb.append(getCallingStationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countConnectInfo(); ++i) {
            sb.append("    ConnectInfo:");
            try {
                sb.append(getConnectInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOriginatingLineInfo()) {
            sb.append("    OriginatingLineInfo:");
            try {
                sb.append(getOriginatingLineInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAuthorizationLifetime()) {
            sb.append("    AuthorizationLifetime:");
            try {
                sb.append(getAuthorizationLifetime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSessionTimeout()) {
            sb.append("    SessionTimeout:");
            try {
                sb.append(getSessionTimeout()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIdleTimeout()) {
            sb.append("    IdleTimeout:");
            try {
                sb.append(getIdleTimeout()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPortLimit()) {
            sb.append("    PortLimit:");
            try {
                sb.append(getPortLimit()).append('\n');
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
        for (int i = 0; i < countFilterId(); ++i) {
            sb.append("    FilterId:");
            try {
                sb.append(getFilterId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countNASFilterRule(); ++i) {
            sb.append("    NASFilterRule:");
            try {
                sb.append(getNASFilterRule(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countQoSFilterRule(); ++i) {
            sb.append("    QoSFilterRule:");
            try {
                sb.append(getQoSFilterRule(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedAppletalkLink()) {
            sb.append("    FramedAppletalkLink:");
            try {
                sb.append(getFramedAppletalkLink()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedAppletalkNetwork()) {
            sb.append("    FramedAppletalkNetwork:");
            try {
                sb.append(getFramedAppletalkNetwork()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedAppletalkZone()) {
            sb.append("    FramedAppletalkZone:");
            try {
                sb.append(getFramedAppletalkZone()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedCompression()) {
            sb.append("    FramedCompression:");
            try {
                sb.append(getFramedCompression()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedInterfaceId()) {
            sb.append("    FramedInterfaceId:");
            try {
                sb.append(getFramedInterfaceId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedIPAddress()) {
            sb.append("    FramedIPAddress:");
            try {
                sb.append(getFramedIPAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedIPNetmask()) {
            sb.append("    FramedIPNetmask:");
            try {
                sb.append(getFramedIPNetmask()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFramedIPv6Prefix(); ++i) {
            sb.append("    FramedIPv6Prefix:");
            try {
                sb.append(getFramedIPv6Prefix(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedIPv6Pool()) {
            sb.append("    FramedIPv6Pool:");
            try {
                sb.append(getFramedIPv6Pool()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFramedIPv6Route(); ++i) {
            sb.append("    FramedIPv6Route:");
            try {
                sb.append(getFramedIPv6Route(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedIPXNetwork()) {
            sb.append("    FramedIPXNetwork:");
            try {
                sb.append(getFramedIPXNetwork()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedMTU()) {
            sb.append("    FramedMTU:");
            try {
                sb.append(getFramedMTU()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedPool()) {
            sb.append("    FramedPool:");
            try {
                sb.append(getFramedPool()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedProtocol()) {
            sb.append("    FramedProtocol:");
            try {
                sb.append(getFramedProtocol()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFramedRoute(); ++i) {
            sb.append("    FramedRoute:");
            try {
                sb.append(getFramedRoute(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedRouting()) {
            sb.append("    FramedRouting:");
            try {
                sb.append(getFramedRouting()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countLoginIPHost(); ++i) {
            sb.append("    LoginIPHost:");
            try {
                sb.append(getLoginIPHost(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countLoginIPv6Host(); ++i) {
            sb.append("    LoginIPv6Host:");
            try {
                sb.append(getLoginIPv6Host(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoginLATGroup()) {
            sb.append("    LoginLATGroup:");
            try {
                sb.append(getLoginLATGroup()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoginLATNode()) {
            sb.append("    LoginLATNode:");
            try {
                sb.append(getLoginLATNode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoginLATPort()) {
            sb.append("    LoginLATPort:");
            try {
                sb.append(getLoginLATPort()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoginLATService()) {
            sb.append("    LoginLATService:");
            try {
                sb.append(getLoginLATService()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoginService()) {
            sb.append("    LoginService:");
            try {
                sb.append(getLoginService()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoginTCPPort()) {
            sb.append("    LoginTCPPort:");
            try {
                sb.append(getLoginTCPPort()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countTunneling(); ++i) {
            sb.append("    Tunneling:");
            try {
                sb.append(getTunneling(i)).append('\n');
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
        if (getCommandCode() != 271 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
