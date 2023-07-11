package diameter.cua;

import com.intellinet.diameter.*;


/**
 * The Capabilities-Update-Answer, indicated by the Command Code set to
 * 328 and the Command Flags' 'R' bit cleared, is sent in response to a
 * CUR message.
 */
public class CapabilitiesUpdateAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new CapabilitiesUpdateAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public CapabilitiesUpdateAnswer(boolean error, boolean retrans) {
        super(false, false, error, retrans, 328, 0);
    }

    /**
     * Constructs a CapabilitiesUpdateAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public CapabilitiesUpdateAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a CapabilitiesUpdateAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public CapabilitiesUpdateAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    CapabilitiesUpdateAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
        super(data);
        validate();
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
        sb.append("    ResultCode:");
            try {
                sb.append(getResultCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsErrorMessage()) {
            sb.append("    ErrorMessage:");
            try {
                sb.append(getErrorMessage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }

    private void validate() throws WrongCommandTypeException {
        if (getCommandCode() != 328 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
