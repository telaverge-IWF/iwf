package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Re-Auth-Answer (RAA), indicated by the Command-Code set to 258
 * and the message flags' 'R' bit clear, is sent in response to the RAR.
 * The Result-Code AVP MUST be present, and indicates the disposition of
 * the request.
 * <p>
 * A successful RAA message MUST be followed by an application-specific
 * authentication and/or authorization message.
 */
public class ReAuthAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new ReAuthAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public ReAuthAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 258, 4);
    }

    /**
     * Constructs a ReAuthAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public ReAuthAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a ReAuthAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public ReAuthAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    ReAuthAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
