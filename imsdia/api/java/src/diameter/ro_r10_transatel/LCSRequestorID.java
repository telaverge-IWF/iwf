package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-Requestor-ID AVP is of type Grouped and contains information re;ated to the identification 
 * of the requestor.
 */
public class LCSRequestorID extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LCSRequestorID.
     */
    public LCSRequestorID() {}

    LCSRequestorID(com.intellinet.diameter.GroupedData data) {
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
     * Tests whether there is any LCSRequestorIDString.
     */
    public boolean containsLCSRequestorIDString() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.LCSRequestorIDString);
    }

    /**
     * Gets the LCSRequestorIDString.
     */
    public LCSRequestorIDString getLCSRequestorIDString() throws NoSuchAttributeException {
        return (LCSRequestorIDString)_data.getContainer().get(Ro_r10_transatelAttributeName.LCSRequestorIDString, 0);
    }

    /**
     * Sets the LCSRequestorIDString.
     *
     * @param avp - the attribute value
     */
    public void setLCSRequestorIDString(LCSRequestorIDString avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.LCSRequestorIDString, avp.getData(), true);
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
        if (containsLCSRequestorIDString()) {
            sb.append("    LCSRequestorIDString:");
            try {
                sb.append(getLCSRequestorIDString()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
