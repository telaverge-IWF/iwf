package diameter.cua;

import com.intellinet.diameter.*;


/**
 * The Capabilities-Update-Request (CUR), indicated by the Command Code
 * set to 328 and the Command Flags' 'R' bit set, is sent to update
 * local capabilities.  Upon detection of a transport failure, this
 * message MUST NOT be sent to an alternate peer.

 * When Diameter is run over the Stream Control Transmission Protocol
 * (SCTP) [RFC4960], which allows connections to span multiple
 * interfaces and multiple IP addresses, the Capabilities-Update-Request
 * message MUST contain one Host-IP-Address AVP for each potential IP
 * address that may be locally used when transmitting Diameter messages.*
 */
public class CapabilitiesUpdateRequest extends com.intellinet.diameter.Command {
    /**
     * Constructs a new CapabilitiesUpdateRequest command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public CapabilitiesUpdateRequest(boolean error, boolean retrans) {
        super(true, false, error, retrans, 328, 0);
    }

    /**
     * Constructs a CapabilitiesUpdateRequest command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public CapabilitiesUpdateRequest(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a CapabilitiesUpdateRequest command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public CapabilitiesUpdateRequest(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    CapabilitiesUpdateRequest(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
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
     * Returns number of HostIPAddress instances.
     */
    public int countHostIPAddress() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.HostIPAddress);
    }

    /**
     * Gets one HostIPAddress.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.HostIPAddress getHostIPAddress(int index) throws NoSuchAttributeException {
        return (diameter.base.HostIPAddress)_data.getContainer().get(diameter.base.BaseAttributeName.HostIPAddress, index);
    }

    /**
     * Adds one HostIPAddress.
     *
     * @param avp - the attribute value
     */
    public void addHostIPAddress(diameter.base.HostIPAddress avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.HostIPAddress, avp.getData(), false);
    }

    /**
     * Gets the VendorId.
     */
    public diameter.base.VendorId getVendorId() throws NoSuchAttributeException {
        return (diameter.base.VendorId)_data.getContainer().get(diameter.base.BaseAttributeName.VendorId, 0);
    }

    /**
     * Sets the VendorId.
     *
     * @param avp - the attribute value
     */
    public void setVendorId(diameter.base.VendorId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.VendorId, avp.getData(), true);
    }

    /**
     * Gets the ProductName.
     */
    public diameter.base.ProductName getProductName() throws NoSuchAttributeException {
        return (diameter.base.ProductName)_data.getContainer().get(diameter.base.BaseAttributeName.ProductName, 0);
    }

    /**
     * Sets the ProductName.
     *
     * @param avp - the attribute value
     */
    public void setProductName(diameter.base.ProductName avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ProductName, avp.getData(), true);
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
     * Returns number of SupportedVendorId instances.
     */
    public int countSupportedVendorId() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.SupportedVendorId);
    }

    /**
     * Gets one SupportedVendorId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.SupportedVendorId getSupportedVendorId(int index) throws NoSuchAttributeException {
        return (diameter.base.SupportedVendorId)_data.getContainer().get(diameter.base.BaseAttributeName.SupportedVendorId, index);
    }

    /**
     * Adds one SupportedVendorId.
     *
     * @param avp - the attribute value
     */
    public void addSupportedVendorId(diameter.base.SupportedVendorId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.SupportedVendorId, avp.getData(), false);
    }

    /**
     * Returns number of AuthApplicationId instances.
     */
    public int countAuthApplicationId() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.AuthApplicationId);
    }

    /**
     * Gets one AuthApplicationId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.AuthApplicationId getAuthApplicationId(int index) throws NoSuchAttributeException {
        return (diameter.base.AuthApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.AuthApplicationId, index);
    }

    /**
     * Adds one AuthApplicationId.
     *
     * @param avp - the attribute value
     */
    public void addAuthApplicationId(diameter.base.AuthApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthApplicationId, avp.getData(), false);
    }

    /**
     * Returns number of AcctApplicationId instances.
     */
    public int countAcctApplicationId() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.AcctApplicationId);
    }

    /**
     * Gets one AcctApplicationId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.AcctApplicationId getAcctApplicationId(int index) throws NoSuchAttributeException {
        return (diameter.base.AcctApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.AcctApplicationId, index);
    }

    /**
     * Adds one AcctApplicationId.
     *
     * @param avp - the attribute value
     */
    public void addAcctApplicationId(diameter.base.AcctApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AcctApplicationId, avp.getData(), false);
    }

    /**
     * Returns number of VendorSpecificApplicationId instances.
     */
    public int countVendorSpecificApplicationId() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.VendorSpecificApplicationId);
    }

    /**
     * Gets one VendorSpecificApplicationId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.VendorSpecificApplicationId getVendorSpecificApplicationId(int index) throws NoSuchAttributeException {
        return (diameter.base.VendorSpecificApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.VendorSpecificApplicationId, index);
    }

    /**
     * Adds one VendorSpecificApplicationId.
     *
     * @param avp - the attribute value
     */
    public void addVendorSpecificApplicationId(diameter.base.VendorSpecificApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.VendorSpecificApplicationId, avp.getData(), false);
    }

    /**
     * Tests whether there is any FirmwareRevision.
     */
    public boolean containsFirmwareRevision() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.FirmwareRevision);
    }

    /**
     * Gets the FirmwareRevision.
     */
    public diameter.base.FirmwareRevision getFirmwareRevision() throws NoSuchAttributeException {
        return (diameter.base.FirmwareRevision)_data.getContainer().get(diameter.base.BaseAttributeName.FirmwareRevision, 0);
    }

    /**
     * Sets the FirmwareRevision.
     *
     * @param avp - the attribute value
     */
    public void setFirmwareRevision(diameter.base.FirmwareRevision avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.FirmwareRevision, avp.getData(), true);
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
        for (int i = 0; i < countHostIPAddress(); ++i) {
            sb.append("    HostIPAddress:");
            try {
                sb.append(getHostIPAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    VendorId:");
            try {
                sb.append(getVendorId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ProductName:");
            try {
                sb.append(getProductName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsOriginStateId()) {
            sb.append("    OriginStateId:");
            try {
                sb.append(getOriginStateId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSupportedVendorId(); ++i) {
            sb.append("    SupportedVendorId:");
            try {
                sb.append(getSupportedVendorId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countAuthApplicationId(); ++i) {
            sb.append("    AuthApplicationId:");
            try {
                sb.append(getAuthApplicationId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countAcctApplicationId(); ++i) {
            sb.append("    AcctApplicationId:");
            try {
                sb.append(getAcctApplicationId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countVendorSpecificApplicationId(); ++i) {
            sb.append("    VendorSpecificApplicationId:");
            try {
                sb.append(getVendorSpecificApplicationId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFirmwareRevision()) {
            sb.append("    FirmwareRevision:");
            try {
                sb.append(getFirmwareRevision()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }

    private void validate() throws WrongCommandTypeException {
        if (getCommandCode() != 328 || !isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
