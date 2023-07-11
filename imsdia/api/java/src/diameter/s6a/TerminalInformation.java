package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Terminal-Information AVP is of type Grouped. This AVP contains the 
 * information about the user's terminal.
 */
public class TerminalInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TerminalInformation.
     */
    public TerminalInformation() {}

    TerminalInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any IMEI.
     */
    public boolean containsIMEI() {
        return _data.getContainer().contains(S6aAttributeName.IMEI);
    }

    /**
     * Gets the IMEI.
     */
    public IMEI getIMEI() throws NoSuchAttributeException {
        return (IMEI)_data.getContainer().get(S6aAttributeName.IMEI, 0);
    }

    /**
     * Sets the IMEI.
     *
     * @param avp - the attribute value
     */
    public void setIMEI(IMEI avp) {
        _data.getContainer().add(S6aAttributeName.IMEI, avp.getData(), true);
    }

    /**
     * Tests whether there is any S6a3GPP2MEID.
     */
    public boolean containsS6a3GPP2MEID() {
        return _data.getContainer().contains(S6aAttributeName.S6a3GPP2MEID);
    }

    /**
     * Gets the S6a3GPP2MEID.
     */
    public S6a3GPP2MEID getS6a3GPP2MEID() throws NoSuchAttributeException {
        return (S6a3GPP2MEID)_data.getContainer().get(S6aAttributeName.S6a3GPP2MEID, 0);
    }

    /**
     * Sets the S6a3GPP2MEID.
     *
     * @param avp - the attribute value
     */
    public void setS6a3GPP2MEID(S6a3GPP2MEID avp) {
        _data.getContainer().add(S6aAttributeName.S6a3GPP2MEID, avp.getData(), true);
    }

    /**
     * Tests whether there is any SoftwareVersion.
     */
    public boolean containsSoftwareVersion() {
        return _data.getContainer().contains(S6aAttributeName.SoftwareVersion);
    }

    /**
     * Gets the SoftwareVersion.
     */
    public SoftwareVersion getSoftwareVersion() throws NoSuchAttributeException {
        return (SoftwareVersion)_data.getContainer().get(S6aAttributeName.SoftwareVersion, 0);
    }

    /**
     * Sets the SoftwareVersion.
     *
     * @param avp - the attribute value
     */
    public void setSoftwareVersion(SoftwareVersion avp) {
        _data.getContainer().add(S6aAttributeName.SoftwareVersion, avp.getData(), true);
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
        if (containsIMEI()) {
            sb.append("    IMEI:");
            try {
                sb.append(getIMEI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsS6a3GPP2MEID()) {
            sb.append("    S6a3GPP2MEID:");
            try {
                sb.append(getS6a3GPP2MEID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSoftwareVersion()) {
            sb.append("    SoftwareVersion:");
            try {
                sb.append(getSoftwareVersion()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
