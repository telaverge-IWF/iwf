package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-Client-Name AVP is of type Grouped and contains the information related to the name of the LCS client.
 */
public class LCSClientName extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LCSClientName.
     */
    public LCSClientName() {}

    LCSClientName(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any LCSDataCodingScheme.
     */
    public boolean containsLCSDataCodingScheme() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.LCSDataCodingScheme);
    }

    /**
     * Gets the LCSDataCodingScheme.
     */
    public LCSDataCodingScheme getLCSDataCodingScheme() throws NoSuchAttributeException {
        return (LCSDataCodingScheme)_data.getContainer().get(Ro_r10_transatelAttributeName.LCSDataCodingScheme, 0);
    }

    /**
     * Sets the LCSDataCodingScheme.
     *
     * @param avp - the attribute value
     */
    public void setLCSDataCodingScheme(LCSDataCodingScheme avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.LCSDataCodingScheme, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSNameString.
     */
    public boolean containsLCSNameString() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.LCSNameString);
    }

    /**
     * Gets the LCSNameString.
     */
    public LCSNameString getLCSNameString() throws NoSuchAttributeException {
        return (LCSNameString)_data.getContainer().get(Ro_r10_transatelAttributeName.LCSNameString, 0);
    }

    /**
     * Sets the LCSNameString.
     *
     * @param avp - the attribute value
     */
    public void setLCSNameString(LCSNameString avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.LCSNameString, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSFormatIndicator.
     */
    public boolean containsLCSFormatIndicator() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.LCSFormatIndicator);
    }

    /**
     * Gets the LCSFormatIndicator.
     */
    public LCSFormatIndicator getLCSFormatIndicator() throws NoSuchAttributeException {
        return (LCSFormatIndicator)_data.getContainer().get(Ro_r10_transatelAttributeName.LCSFormatIndicator, 0);
    }

    /**
     * Sets the LCSFormatIndicator.
     *
     * @param avp - the attribute value
     */
    public void setLCSFormatIndicator(LCSFormatIndicator avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.LCSFormatIndicator, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsLCSDataCodingScheme()) {
            sb.append("    LCSDataCodingScheme:");
            try {
                sb.append(getLCSDataCodingScheme()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSNameString()) {
            sb.append("    LCSNameString:");
            try {
                sb.append(getLCSNameString()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSFormatIndicator()) {
            sb.append("    LCSFormatIndicator:");
            try {
                sb.append(getLCSFormatIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
