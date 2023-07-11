package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The AA-Request (AAR), which is indicated by setting the Command-Code field to * 265 and the 'R' bit in the Command Flags field, is used to request
 * authentication and/or authorization for a given NAS user.
 * The type of request is identified through the Auth-Request-Type AVP [BASE].
 * The recommended value for most RADIUS interoperabily situations is
 * AUTHORIZE_AUTHENTICATE.
 * If Authentication is requested, the User-Name attribute SHOULD be present, as * well as any additional authentication AVPs that would carry the password
 * information. A request for authorization SHOULD only include the information  * from which the authorization will be performed, such as the User-Name,
 * Called-Station-Id, or Calling-Station-Id AVPs. All requests SHOULD contain
 * AVPs uniquely identifying the source of the call, such as Origin-Host and
 * NAS-Port. Certain networks MAY use different AVPs for authorization purposes.
 * A request for authorization will include some AVPs defined in section 6.
 */
public class AARequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new AARequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public AARequest(boolean error, boolean retrans) {
        super(true, true, error, retrans, 265, 1);
    }

    /**
     * Constructs a AARequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public AARequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a AARequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public AARequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    AARequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Gets the AuthRequestType.
     */
    public diameter.base.AuthRequestType getAuthRequestType() throws NoSuchAttributeException {
        return (diameter.base.AuthRequestType)_data.getContainer().get(diameter.base.BaseAttributeName.AuthRequestType, 0);
    }

    /**
     * Sets the AuthRequestType.
     *
     * @param avp - the attribute value
     */
    public void setAuthRequestType(diameter.base.AuthRequestType avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthRequestType, avp.getData(), true);
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
     * Tests whether there is any UserPassword.
     */
    public boolean containsUserPassword() {
        return _data.getContainer().contains(NasreqAttributeName.UserPassword);
    }

    /**
     * Gets the UserPassword.
     */
    public UserPassword getUserPassword() throws NoSuchAttributeException {
        return (UserPassword)_data.getContainer().get(NasreqAttributeName.UserPassword, 0);
    }

    /**
     * Sets the UserPassword.
     *
     * @param avp - the attribute value
     */
    public void setUserPassword(UserPassword avp) {
        _data.getContainer().add(NasreqAttributeName.UserPassword, avp.getData(), true);
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
     * Tests whether there is any AuthGracePeriod.
     */
    public boolean containsAuthGracePeriod() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AuthGracePeriod);
    }

    /**
     * Gets the AuthGracePeriod.
     */
    public diameter.base.AuthGracePeriod getAuthGracePeriod() throws NoSuchAttributeException {
        return (diameter.base.AuthGracePeriod)_data.getContainer().get(diameter.base.BaseAttributeName.AuthGracePeriod, 0);
    }

    /**
     * Sets the AuthGracePeriod.
     *
     * @param avp - the attribute value
     */
    public void setAuthGracePeriod(diameter.base.AuthGracePeriod avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthGracePeriod, avp.getData(), true);
    }

    /**
     * Tests whether there is any AuthSessionState.
     */
    public boolean containsAuthSessionState() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AuthSessionState);
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
     * Tests whether there is any ConnectInfo.
     */
    public boolean containsConnectInfo() {
        return _data.getContainer().contains(NasreqAttributeName.ConnectInfo);
    }

    /**
     * Gets the ConnectInfo.
     */
    public ConnectInfo getConnectInfo() throws NoSuchAttributeException {
        return (ConnectInfo)_data.getContainer().get(NasreqAttributeName.ConnectInfo, 0);
    }

    /**
     * Sets the ConnectInfo.
     *
     * @param avp - the attribute value
     */
    public void setConnectInfo(ConnectInfo avp) {
        _data.getContainer().add(NasreqAttributeName.ConnectInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any CHAPAuth.
     */
    public boolean containsCHAPAuth() {
        return _data.getContainer().contains(NasreqAttributeName.CHAPAuth);
    }

    /**
     * Gets the CHAPAuth.
     */
    public CHAPAuth getCHAPAuth() throws NoSuchAttributeException {
        return (CHAPAuth)_data.getContainer().get(NasreqAttributeName.CHAPAuth, 0);
    }

    /**
     * Sets the CHAPAuth.
     *
     * @param avp - the attribute value
     */
    public void setCHAPAuth(CHAPAuth avp) {
        _data.getContainer().add(NasreqAttributeName.CHAPAuth, avp.getData(), true);
    }

    /**
     * Tests whether there is any CHAPChallenge.
     */
    public boolean containsCHAPChallenge() {
        return _data.getContainer().contains(NasreqAttributeName.CHAPChallenge);
    }

    /**
     * Gets the CHAPChallenge.
     */
    public CHAPChallenge getCHAPChallenge() throws NoSuchAttributeException {
        return (CHAPChallenge)_data.getContainer().get(NasreqAttributeName.CHAPChallenge, 0);
    }

    /**
     * Sets the CHAPChallenge.
     *
     * @param avp - the attribute value
     */
    public void setCHAPChallenge(CHAPChallenge avp) {
        _data.getContainer().add(NasreqAttributeName.CHAPChallenge, avp.getData(), true);
    }

    /**
     * Returns number of FramedCompression instances.
     */
    public int countFramedCompression() {
        return _data.getContainer().count(NasreqAttributeName.FramedCompression);
    }

    /**
     * Gets one FramedCompression.
     *
     * @param index - the index of the attribute to return
     */
    public FramedCompression getFramedCompression(int index) throws NoSuchAttributeException {
        return (FramedCompression)_data.getContainer().get(NasreqAttributeName.FramedCompression, index);
    }

    /**
     * Adds one FramedCompression.
     *
     * @param avp - the attribute value
     */
    public void addFramedCompression(FramedCompression avp) {
        _data.getContainer().add(NasreqAttributeName.FramedCompression, avp.getData(), false);
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
     * Tests whether there is any ARAPPassword.
     */
    public boolean containsARAPPassword() {
        return _data.getContainer().contains(NasreqAttributeName.ARAPPassword);
    }

    /**
     * Gets the ARAPPassword.
     */
    public ARAPPassword getARAPPassword() throws NoSuchAttributeException {
        return (ARAPPassword)_data.getContainer().get(NasreqAttributeName.ARAPPassword, 0);
    }

    /**
     * Sets the ARAPPassword.
     *
     * @param avp - the attribute value
     */
    public void setARAPPassword(ARAPPassword avp) {
        _data.getContainer().add(NasreqAttributeName.ARAPPassword, avp.getData(), true);
    }

    /**
     * Tests whether there is any ARAPSecurity.
     */
    public boolean containsARAPSecurity() {
        return _data.getContainer().contains(NasreqAttributeName.ARAPSecurity);
    }

    /**
     * Gets the ARAPSecurity.
     */
    public ARAPSecurity getARAPSecurity() throws NoSuchAttributeException {
        return (ARAPSecurity)_data.getContainer().get(NasreqAttributeName.ARAPSecurity, 0);
    }

    /**
     * Sets the ARAPSecurity.
     *
     * @param avp - the attribute value
     */
    public void setARAPSecurity(ARAPSecurity avp) {
        _data.getContainer().add(NasreqAttributeName.ARAPSecurity, avp.getData(), true);
    }

    /**
     * Returns number of ARAPSecurityData instances.
     */
    public int countARAPSecurityData() {
        return _data.getContainer().count(NasreqAttributeName.ARAPSecurityData);
    }

    /**
     * Gets one ARAPSecurityData.
     *
     * @param index - the index of the attribute to return
     */
    public ARAPSecurityData getARAPSecurityData(int index) throws NoSuchAttributeException {
        return (ARAPSecurityData)_data.getContainer().get(NasreqAttributeName.ARAPSecurityData, index);
    }

    /**
     * Adds one ARAPSecurityData.
     *
     * @param avp - the attribute value
     */
    public void addARAPSecurityData(ARAPSecurityData avp) {
        _data.getContainer().add(NasreqAttributeName.ARAPSecurityData, avp.getData(), false);
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
        sb.append("    AuthApplicationId:");
            try {
                sb.append(getAuthApplicationId()).append('\n');
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
        sb.append("    AuthRequestType:");
            try {
                sb.append(getAuthRequestType()).append('\n');
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
        if (containsPortLimit()) {
            sb.append("    PortLimit:");
            try {
                sb.append(getPortLimit()).append('\n');
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
        if (containsUserPassword()) {
            sb.append("    UserPassword:");
            try {
                sb.append(getUserPassword()).append('\n');
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
        if (containsState()) {
            sb.append("    State:");
            try {
                sb.append(getState()).append('\n');
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
        if (containsAuthGracePeriod()) {
            sb.append("    AuthGracePeriod:");
            try {
                sb.append(getAuthGracePeriod()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAuthSessionState()) {
            sb.append("    AuthSessionState:");
            try {
                sb.append(getAuthSessionState()).append('\n');
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
        if (containsOriginatingLineInfo()) {
            sb.append("    OriginatingLineInfo:");
            try {
                sb.append(getOriginatingLineInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsConnectInfo()) {
            sb.append("    ConnectInfo:");
            try {
                sb.append(getConnectInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCHAPAuth()) {
            sb.append("    CHAPAuth:");
            try {
                sb.append(getCHAPAuth()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCHAPChallenge()) {
            sb.append("    CHAPChallenge:");
            try {
                sb.append(getCHAPChallenge()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFramedCompression(); ++i) {
            sb.append("    FramedCompression:");
            try {
                sb.append(getFramedCompression(i)).append('\n');
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
        for (int i = 0; i < countFramedIPv6Prefix(); ++i) {
            sb.append("    FramedIPv6Prefix:");
            try {
                sb.append(getFramedIPv6Prefix(i)).append('\n');
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
        if (containsFramedMTU()) {
            sb.append("    FramedMTU:");
            try {
                sb.append(getFramedMTU()).append('\n');
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
        if (containsARAPPassword()) {
            sb.append("    ARAPPassword:");
            try {
                sb.append(getARAPPassword()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsARAPSecurity()) {
            sb.append("    ARAPSecurity:");
            try {
                sb.append(getARAPSecurity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countARAPSecurityData(); ++i) {
            sb.append("    ARAPSecurityData:");
            try {
                sb.append(getARAPSecurityData(i)).append('\n');
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
        if (getCommandCode() != 265 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
