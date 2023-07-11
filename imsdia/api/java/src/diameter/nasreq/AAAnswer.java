package diameter.nasreq;

import com.intellinet.diameter.*;


/**     
 * The AA-Answer (AAA) message is indicated by setting the Command-Code field to * 265 and clearing the 'R' bit in the Command Flags field. It is sent in
 * response to the AA-Request (AAR) message. If authorization was requested, a
 * successful response will include the authorization AVPs appropriate for the
 * service being provided, as defined in section 6.
 * For authentication exchanges requiring more than a single round trip,
 * the server MUST set the Result-Code AVP to DIAMETER_MULTI_ROUND_AUTH.
 * An AAA message with this result code MAY include one Reply-Message or
 * more and MAY include zero or one State AVPs.
 */
public class AAAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new AAAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public AAAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 265, 1);
    }

    /**
     * Constructs a AAAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public AAAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a AAAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public AAAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    AAAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Returns number of ConfigurationToken instances.
     */
    public int countConfigurationToken() {
        return _data.getContainer().count(NasreqAttributeName.ConfigurationToken);
    }

    /**
     * Gets one ConfigurationToken.
     *
     * @param index - the index of the attribute to return
     */
    public ConfigurationToken getConfigurationToken(int index) throws NoSuchAttributeException {
        return (ConfigurationToken)_data.getContainer().get(NasreqAttributeName.ConfigurationToken, index);
    }

    /**
     * Adds one ConfigurationToken.
     *
     * @param avp - the attribute value
     */
    public void addConfigurationToken(ConfigurationToken avp) {
        _data.getContainer().add(NasreqAttributeName.ConfigurationToken, avp.getData(), false);
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
     * Tests whether there is any ReAuthRequestType.
     */
    public boolean containsReAuthRequestType() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.ReAuthRequestType);
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
     * Tests whether there is any MultiRoundTimeOut.
     */
    public boolean containsMultiRoundTimeOut() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.MultiRoundTimeOut);
    }

    /**
     * Gets the MultiRoundTimeOut.
     */
    public diameter.base.MultiRoundTimeOut getMultiRoundTimeOut() throws NoSuchAttributeException {
        return (diameter.base.MultiRoundTimeOut)_data.getContainer().get(diameter.base.BaseAttributeName.MultiRoundTimeOut, 0);
    }

    /**
     * Sets the MultiRoundTimeOut.
     *
     * @param avp - the attribute value
     */
    public void setMultiRoundTimeOut(diameter.base.MultiRoundTimeOut avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.MultiRoundTimeOut, avp.getData(), true);
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
     * Returns number of ReplyMessage instances.
     */
    public int countReplyMessage() {
        return _data.getContainer().count(NasreqAttributeName.ReplyMessage);
    }

    /**
     * Gets one ReplyMessage.
     *
     * @param index - the index of the attribute to return
     */
    public ReplyMessage getReplyMessage(int index) throws NoSuchAttributeException {
        return (ReplyMessage)_data.getContainer().get(NasreqAttributeName.ReplyMessage, index);
    }

    /**
     * Adds one ReplyMessage.
     *
     * @param avp - the attribute value
     */
    public void addReplyMessage(ReplyMessage avp) {
        _data.getContainer().add(NasreqAttributeName.ReplyMessage, avp.getData(), false);
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
     * Tests whether there is any PasswordRetry.
     */
    public boolean containsPasswordRetry() {
        return _data.getContainer().contains(NasreqAttributeName.PasswordRetry);
    }

    /**
     * Gets the PasswordRetry.
     */
    public PasswordRetry getPasswordRetry() throws NoSuchAttributeException {
        return (PasswordRetry)_data.getContainer().get(NasreqAttributeName.PasswordRetry, 0);
    }

    /**
     * Sets the PasswordRetry.
     *
     * @param avp - the attribute value
     */
    public void setPasswordRetry(PasswordRetry avp) {
        _data.getContainer().add(NasreqAttributeName.PasswordRetry, avp.getData(), true);
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
     * Tests whether there is any Prompt.
     */
    public boolean containsPrompt() {
        return _data.getContainer().contains(NasreqAttributeName.Prompt);
    }

    /**
     * Gets the Prompt.
     */
    public Prompt getPrompt() throws NoSuchAttributeException {
        return (Prompt)_data.getContainer().get(NasreqAttributeName.Prompt, 0);
    }

    /**
     * Sets the Prompt.
     *
     * @param avp - the attribute value
     */
    public void setPrompt(Prompt avp) {
        _data.getContainer().add(NasreqAttributeName.Prompt, avp.getData(), true);
    }

    /**
     * Tests whether there is any ARAPChallengeResponse.
     */
    public boolean containsARAPChallengeResponse() {
        return _data.getContainer().contains(NasreqAttributeName.ARAPChallengeResponse);
    }

    /**
     * Gets the ARAPChallengeResponse.
     */
    public ARAPChallengeResponse getARAPChallengeResponse() throws NoSuchAttributeException {
        return (ARAPChallengeResponse)_data.getContainer().get(NasreqAttributeName.ARAPChallengeResponse, 0);
    }

    /**
     * Sets the ARAPChallengeResponse.
     *
     * @param avp - the attribute value
     */
    public void setARAPChallengeResponse(ARAPChallengeResponse avp) {
        _data.getContainer().add(NasreqAttributeName.ARAPChallengeResponse, avp.getData(), true);
    }

    /**
     * Tests whether there is any ARAPFeatures.
     */
    public boolean containsARAPFeatures() {
        return _data.getContainer().contains(NasreqAttributeName.ARAPFeatures);
    }

    /**
     * Gets the ARAPFeatures.
     */
    public ARAPFeatures getARAPFeatures() throws NoSuchAttributeException {
        return (ARAPFeatures)_data.getContainer().get(NasreqAttributeName.ARAPFeatures, 0);
    }

    /**
     * Sets the ARAPFeatures.
     *
     * @param avp - the attribute value
     */
    public void setARAPFeatures(ARAPFeatures avp) {
        _data.getContainer().add(NasreqAttributeName.ARAPFeatures, avp.getData(), true);
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
     * Tests whether there is any ARAPZoneAccess.
     */
    public boolean containsARAPZoneAccess() {
        return _data.getContainer().contains(NasreqAttributeName.ARAPZoneAccess);
    }

    /**
     * Gets the ARAPZoneAccess.
     */
    public ARAPZoneAccess getARAPZoneAccess() throws NoSuchAttributeException {
        return (ARAPZoneAccess)_data.getContainer().get(NasreqAttributeName.ARAPZoneAccess, 0);
    }

    /**
     * Sets the ARAPZoneAccess.
     *
     * @param avp - the attribute value
     */
    public void setARAPZoneAccess(ARAPZoneAccess avp) {
        _data.getContainer().add(NasreqAttributeName.ARAPZoneAccess, avp.getData(), true);
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
     * Returns number of FramedAppletalkNetwork instances.
     */
    public int countFramedAppletalkNetwork() {
        return _data.getContainer().count(NasreqAttributeName.FramedAppletalkNetwork);
    }

    /**
     * Gets one FramedAppletalkNetwork.
     *
     * @param index - the index of the attribute to return
     */
    public FramedAppletalkNetwork getFramedAppletalkNetwork(int index) throws NoSuchAttributeException {
        return (FramedAppletalkNetwork)_data.getContainer().get(NasreqAttributeName.FramedAppletalkNetwork, index);
    }

    /**
     * Adds one FramedAppletalkNetwork.
     *
     * @param avp - the attribute value
     */
    public void addFramedAppletalkNetwork(FramedAppletalkNetwork avp) {
        _data.getContainer().add(NasreqAttributeName.FramedAppletalkNetwork, avp.getData(), false);
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
     * Returns number of RedirectHost instances.
     */
    public int countRedirectHost() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.RedirectHost);
    }

    /**
     * Gets one RedirectHost.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.RedirectHost getRedirectHost(int index) throws NoSuchAttributeException {
        return (diameter.base.RedirectHost)_data.getContainer().get(diameter.base.BaseAttributeName.RedirectHost, index);
    }

    /**
     * Adds one RedirectHost.
     *
     * @param avp - the attribute value
     */
    public void addRedirectHost(diameter.base.RedirectHost avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RedirectHost, avp.getData(), false);
    }

    /**
     * Tests whether there is any RedirectHostUsage.
     */
    public boolean containsRedirectHostUsage() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.RedirectHostUsage);
    }

    /**
     * Gets the RedirectHostUsage.
     */
    public diameter.base.RedirectHostUsage getRedirectHostUsage() throws NoSuchAttributeException {
        return (diameter.base.RedirectHostUsage)_data.getContainer().get(diameter.base.BaseAttributeName.RedirectHostUsage, 0);
    }

    /**
     * Sets the RedirectHostUsage.
     *
     * @param avp - the attribute value
     */
    public void setRedirectHostUsage(diameter.base.RedirectHostUsage avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RedirectHostUsage, avp.getData(), true);
    }

    /**
     * Tests whether there is any RedirectMaxCacheTime.
     */
    public boolean containsRedirectMaxCacheTime() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.RedirectMaxCacheTime);
    }

    /**
     * Gets the RedirectMaxCacheTime.
     */
    public diameter.base.RedirectMaxCacheTime getRedirectMaxCacheTime() throws NoSuchAttributeException {
        return (diameter.base.RedirectMaxCacheTime)_data.getContainer().get(diameter.base.BaseAttributeName.RedirectMaxCacheTime, 0);
    }

    /**
     * Sets the RedirectMaxCacheTime.
     *
     * @param avp - the attribute value
     */
    public void setRedirectMaxCacheTime(diameter.base.RedirectMaxCacheTime avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RedirectMaxCacheTime, avp.getData(), true);
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
        sb.append("    AuthRequestType:");
            try {
                sb.append(getAuthRequestType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
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
        if (containsUserName()) {
            sb.append("    UserName:");
            try {
                sb.append(getUserName()).append('\n');
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
        for (int i = 0; i < countClass(); ++i) {
            sb.append("    Class:");
            try {
                sb.append(getClass(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countConfigurationToken(); ++i) {
            sb.append("    ConfigurationToken:");
            try {
                sb.append(getConfigurationToken(i)).append('\n');
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
        if (containsIdleTimeout()) {
            sb.append("    IdleTimeout:");
            try {
                sb.append(getIdleTimeout()).append('\n');
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
        if (containsReAuthRequestType()) {
            sb.append("    ReAuthRequestType:");
            try {
                sb.append(getReAuthRequestType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMultiRoundTimeOut()) {
            sb.append("    MultiRoundTimeOut:");
            try {
                sb.append(getMultiRoundTimeOut()).append('\n');
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
        if (containsState()) {
            sb.append("    State:");
            try {
                sb.append(getState()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countReplyMessage(); ++i) {
            sb.append("    ReplyMessage:");
            try {
                sb.append(getReplyMessage(i)).append('\n');
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
        for (int i = 0; i < countFilterId(); ++i) {
            sb.append("    FilterId:");
            try {
                sb.append(getFilterId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPasswordRetry()) {
            sb.append("    PasswordRetry:");
            try {
                sb.append(getPasswordRetry()).append('\n');
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
        if (containsPrompt()) {
            sb.append("    Prompt:");
            try {
                sb.append(getPrompt()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsARAPChallengeResponse()) {
            sb.append("    ARAPChallengeResponse:");
            try {
                sb.append(getARAPChallengeResponse()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsARAPFeatures()) {
            sb.append("    ARAPFeatures:");
            try {
                sb.append(getARAPFeatures()).append('\n');
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
        if (containsARAPZoneAccess()) {
            sb.append("    ARAPZoneAccess:");
            try {
                sb.append(getARAPZoneAccess()).append('\n');
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
        if (containsFramedAppletalkLink()) {
            sb.append("    FramedAppletalkLink:");
            try {
                sb.append(getFramedAppletalkLink()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFramedAppletalkNetwork(); ++i) {
            sb.append("    FramedAppletalkNetwork:");
            try {
                sb.append(getFramedAppletalkNetwork(i)).append('\n');
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
        if (containsFramedIPNetmask()) {
            sb.append("    FramedIPNetmask:");
            try {
                sb.append(getFramedIPNetmask()).append('\n');
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
        if (containsFramedPool()) {
            sb.append("    FramedPool:");
            try {
                sb.append(getFramedPool()).append('\n');
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
        if (containsFramedProtocol()) {
            sb.append("    FramedProtocol:");
            try {
                sb.append(getFramedProtocol()).append('\n');
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
        for (int i = 0; i < countTunneling(); ++i) {
            sb.append("    Tunneling:");
            try {
                sb.append(getTunneling(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRedirectHost(); ++i) {
            sb.append("    RedirectHost:");
            try {
                sb.append(getRedirectHost(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRedirectHostUsage()) {
            sb.append("    RedirectHostUsage:");
            try {
                sb.append(getRedirectHostUsage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRedirectMaxCacheTime()) {
            sb.append("    RedirectMaxCacheTime:");
            try {
                sb.append(getRedirectMaxCacheTime()).append('\n');
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
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }

    private void validate() throws WrongCommandTypeException {
        if (getCommandCode() != 265 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
