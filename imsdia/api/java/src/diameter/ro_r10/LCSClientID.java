package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * LCS-Client-ID AVP is of type Grouped and holds information related to the identity of an LCS client.
 */
public class LCSClientID extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LCSClientID.
     */
    public LCSClientID() {}

    LCSClientID(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any LCSClientType.
     */
    public boolean containsLCSClientType() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSClientType);
    }

    /**
     * Gets the LCSClientType.
     */
    public LCSClientType getLCSClientType() throws NoSuchAttributeException {
        return (LCSClientType)_data.getContainer().get(Ro_r10AttributeName.LCSClientType, 0);
    }

    /**
     * Sets the LCSClientType.
     *
     * @param avp - the attribute value
     */
    public void setLCSClientType(LCSClientType avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSClientType, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSClientExternalID.
     */
    public boolean containsLCSClientExternalID() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSClientExternalID);
    }

    /**
     * Gets the LCSClientExternalID.
     */
    public LCSClientExternalID getLCSClientExternalID() throws NoSuchAttributeException {
        return (LCSClientExternalID)_data.getContainer().get(Ro_r10AttributeName.LCSClientExternalID, 0);
    }

    /**
     * Sets the LCSClientExternalID.
     *
     * @param avp - the attribute value
     */
    public void setLCSClientExternalID(LCSClientExternalID avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSClientExternalID, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSClientDialedByMS.
     */
    public boolean containsLCSClientDialedByMS() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSClientDialedByMS);
    }

    /**
     * Gets the LCSClientDialedByMS.
     */
    public LCSClientDialedByMS getLCSClientDialedByMS() throws NoSuchAttributeException {
        return (LCSClientDialedByMS)_data.getContainer().get(Ro_r10AttributeName.LCSClientDialedByMS, 0);
    }

    /**
     * Sets the LCSClientDialedByMS.
     *
     * @param avp - the attribute value
     */
    public void setLCSClientDialedByMS(LCSClientDialedByMS avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSClientDialedByMS, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSClientName.
     */
    public boolean containsLCSClientName() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSClientName);
    }

    /**
     * Gets the LCSClientName.
     */
    public LCSClientName getLCSClientName() throws NoSuchAttributeException {
        return (LCSClientName)_data.getContainer().get(Ro_r10AttributeName.LCSClientName, 0);
    }

    /**
     * Sets the LCSClientName.
     *
     * @param avp - the attribute value
     */
    public void setLCSClientName(LCSClientName avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSClientName, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSAPN.
     */
    public boolean containsLCSAPN() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSAPN);
    }

    /**
     * Gets the LCSAPN.
     */
    public LCSAPN getLCSAPN() throws NoSuchAttributeException {
        return (LCSAPN)_data.getContainer().get(Ro_r10AttributeName.LCSAPN, 0);
    }

    /**
     * Sets the LCSAPN.
     *
     * @param avp - the attribute value
     */
    public void setLCSAPN(LCSAPN avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSAPN, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSRequestorID.
     */
    public boolean containsLCSRequestorID() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSRequestorID);
    }

    /**
     * Gets the LCSRequestorID.
     */
    public LCSRequestorID getLCSRequestorID() throws NoSuchAttributeException {
        return (LCSRequestorID)_data.getContainer().get(Ro_r10AttributeName.LCSRequestorID, 0);
    }

    /**
     * Sets the LCSRequestorID.
     *
     * @param avp - the attribute value
     */
    public void setLCSRequestorID(LCSRequestorID avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSRequestorID, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsLCSClientType()) {
            sb.append("    LCSClientType:");
            try {
                sb.append(getLCSClientType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSClientExternalID()) {
            sb.append("    LCSClientExternalID:");
            try {
                sb.append(getLCSClientExternalID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSClientDialedByMS()) {
            sb.append("    LCSClientDialedByMS:");
            try {
                sb.append(getLCSClientDialedByMS()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSClientName()) {
            sb.append("    LCSClientName:");
            try {
                sb.append(getLCSClientName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSAPN()) {
            sb.append("    LCSAPN:");
            try {
                sb.append(getLCSAPN()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSRequestorID()) {
            sb.append("    LCSRequestorID:");
            try {
                sb.append(getLCSRequestorID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
