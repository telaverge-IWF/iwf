package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * A Diameter server may initiate a re-authentication and/or reauthorization
 * service for a particular session by issuing a Re-Auth-Request (RAR) message
 * [BASE].For example, for pre-paid services, the Diameter server that 
 * originally authorized a session may need some confirmation that the user is
 * still using the services. If a NAS receives an RAR message with Session-Id
 * equal to a currently active session and a Re-Auth-Type that includes
 * authentication, it MUST initiate a re-authentication toward the user, if
 * the service supports this particular feature.  
 */
public class RARequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new RARequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public RARequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 258, 1);
    }

    /**
     * Constructs a RARequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public RARequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a RARequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public RARequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    RARequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Gets the ReAuthRequestType.
     */
    public diameter.base.ReAuthRequestType getReAuthRequestType() throws NoSuchAttributeException {
        return (diameter.base.ReAuthRequestType)_data.getContainer().get(diameter.base.BaseAttributeName.ReAuthRequestType, 0);
    }

    /**
     * Sets the ReAuthRequestType.
     *
     * @param avp - the attribute value
     */
    public void setReAuthRequestType(diameter.base.ReAuthRequestType avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ReAuthRequestType, avp.getData(), true);
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
     * Tests whether there is any FramedIPv6Prefix.
     */
    public boolean containsFramedIPv6Prefix() {
        return _data.getContainer().contains(NasreqAttributeName.FramedIPv6Prefix);
    }

    /**
     * Gets the FramedIPv6Prefix.
     */
    public FramedIPv6Prefix getFramedIPv6Prefix() throws NoSuchAttributeException {
        return (FramedIPv6Prefix)_data.getContainer().get(NasreqAttributeName.FramedIPv6Prefix, 0);
    }

    /**
     * Sets the FramedIPv6Prefix.
     *
     * @param avp - the attribute value
     */
    public void setFramedIPv6Prefix(FramedIPv6Prefix avp) {
        _data.getContainer().add(NasreqAttributeName.FramedIPv6Prefix, avp.getData(), true);
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
     * Tests whether there is any State.
     */
    public boolean containsState() {
        return _data.getContainer().contains(NasreqAttributeName.State);
    }

    /**
     * Gets the State.
     */
    public State getState() throws NoSuchAttributeException {
        return (State)_data.getContainer().get(NasreqAttributeName.State, 0);
    }

    /**
     * Sets the State.
     *
     * @param avp - the attribute value
     */
    public void setState(State avp) {
        _data.getContainer().add(NasreqAttributeName.State, avp.getData(), true);
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
     * Tests whether there is any ReplyMessage.
     */
    public boolean containsReplyMessage() {
        return _data.getContainer().contains(NasreqAttributeName.ReplyMessage);
    }

    /**
     * Gets the ReplyMessage.
     */
    public ReplyMessage getReplyMessage() throws NoSuchAttributeException {
        return (ReplyMessage)_data.getContainer().get(NasreqAttributeName.ReplyMessage, 0);
    }

    /**
     * Sets the ReplyMessage.
     *
     * @param avp - the attribute value
     */
    public void setReplyMessage(ReplyMessage avp) {
        _data.getContainer().add(NasreqAttributeName.ReplyMessage, avp.getData(), true);
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
        sb.append("    DestinationHost:");
            try {
                sb.append(getDestinationHost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AuthApplicationId:");
            try {
                sb.append(getAuthApplicationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ReAuthRequestType:");
            try {
                sb.append(getReAuthRequestType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsUserName()) {
            sb.append("    UserName:");
            try {
                sb.append(getUserName()).append('\n');
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
        if (containsFramedIPAddress()) {
            sb.append("    FramedIPAddress:");
            try {
                sb.append(getFramedIPAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedIPv6Prefix()) {
            sb.append("    FramedIPv6Prefix:");
            try {
                sb.append(getFramedIPv6Prefix()).append('\n');
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
        if (containsOriginatingLineInfo()) {
            sb.append("    OriginatingLineInfo:");
            try {
                sb.append(getOriginatingLineInfo()).append('\n');
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
        if (containsState()) {
            sb.append("    State:");
            try {
                sb.append(getState()).append('\n');
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
        if (containsReplyMessage()) {
            sb.append("    ReplyMessage:");
            try {
                sb.append(getReplyMessage()).append('\n');
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
        if (getCommandCode() != 258 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
