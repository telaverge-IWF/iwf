package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Re-Auth-Answer (RAA) message [BASE] is sent in response to the RAR. The
 * Result-Code AVP MUST be present and indicates the disposition of the request.
 * A successful RAA transaction MUST be followed by an AAR message.
 */
public class RAAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new RAAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public RAAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 258, 1);
    }

    /**
     * Constructs a RAAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public RAAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a RAAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public RAAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    RAAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
        if (containsServiceType()) {
            sb.append("    ServiceType:");
            try {
                sb.append(getServiceType()).append('\n');
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
        if (containsReAuthRequestType()) {
            sb.append("    ReAuthRequestType:");
            try {
                sb.append(getReAuthRequestType()).append('\n');
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
        for (int i = 0; i < countReplyMessage(); ++i) {
            sb.append("    ReplyMessage:");
            try {
                sb.append(getReplyMessage(i)).append('\n');
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
        if (getCommandCode() != 258 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
