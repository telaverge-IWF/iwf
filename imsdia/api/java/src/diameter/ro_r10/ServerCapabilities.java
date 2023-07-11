package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Server-Capabilities AVP (is of type Grouped. This AVP contains information to assist the I-CSCF in the selection
 * of an S-CSCF.
 */
public class ServerCapabilities extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServerCapabilities.
     */
    public ServerCapabilities() {}

    ServerCapabilities(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of MandatoryCapability instances.
     */
    public int countMandatoryCapability() {
        return _data.getContainer().count(Ro_r10AttributeName.MandatoryCapability);
    }

    /**
     * Gets one MandatoryCapability.
     *
     * @param index - the index of the attribute to return
     */
    public MandatoryCapability getMandatoryCapability(int index) throws NoSuchAttributeException {
        return (MandatoryCapability)_data.getContainer().get(Ro_r10AttributeName.MandatoryCapability, index);
    }

    /**
     * Adds one MandatoryCapability.
     *
     * @param avp - the attribute value
     */
    public void addMandatoryCapability(MandatoryCapability avp) {
        _data.getContainer().add(Ro_r10AttributeName.MandatoryCapability, avp.getData(), false);
    }

    /**
     * Returns number of OptionalCapability instances.
     */
    public int countOptionalCapability() {
        return _data.getContainer().count(Ro_r10AttributeName.OptionalCapability);
    }

    /**
     * Gets one OptionalCapability.
     *
     * @param index - the index of the attribute to return
     */
    public OptionalCapability getOptionalCapability(int index) throws NoSuchAttributeException {
        return (OptionalCapability)_data.getContainer().get(Ro_r10AttributeName.OptionalCapability, index);
    }

    /**
     * Adds one OptionalCapability.
     *
     * @param avp - the attribute value
     */
    public void addOptionalCapability(OptionalCapability avp) {
        _data.getContainer().add(Ro_r10AttributeName.OptionalCapability, avp.getData(), false);
    }

    /**
     * Returns number of ServerName instances.
     */
    public int countServerName() {
        return _data.getContainer().count(Ro_r10AttributeName.ServerName);
    }

    /**
     * Gets one ServerName.
     *
     * @param index - the index of the attribute to return
     */
    public ServerName getServerName(int index) throws NoSuchAttributeException {
        return (ServerName)_data.getContainer().get(Ro_r10AttributeName.ServerName, index);
    }

    /**
     * Adds one ServerName.
     *
     * @param avp - the attribute value
     */
    public void addServerName(ServerName avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServerName, avp.getData(), false);
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
        StringBuffer sb = new StringBuffer(" {\n");
        for (int i = 0; i < countMandatoryCapability(); ++i) {
            sb.append("    MandatoryCapability:");
            try {
                sb.append(getMandatoryCapability(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countOptionalCapability(); ++i) {
            sb.append("    OptionalCapability:");
            try {
                sb.append(getOptionalCapability(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServerName(); ++i) {
            sb.append("    ServerName:");
            try {
                sb.append(getServerName(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
