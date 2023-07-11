package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class EPSLocationInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new EPSLocationInformation.
     */
    public EPSLocationInformation() {}

    EPSLocationInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any MMELocationInformation.
     */
    public boolean containsMMELocationInformation() {
        return _data.getContainer().contains(S6a_r10AttributeName.MMELocationInformation);
    }

    /**
     * Gets the MMELocationInformation.
     */
    public MMELocationInformation getMMELocationInformation() throws NoSuchAttributeException {
        return (MMELocationInformation)_data.getContainer().get(S6a_r10AttributeName.MMELocationInformation, 0);
    }

    /**
     * Sets the MMELocationInformation.
     *
     * @param avp - the attribute value
     */
    public void setMMELocationInformation(MMELocationInformation avp) {
        _data.getContainer().add(S6a_r10AttributeName.MMELocationInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any SGSNLocationInformation.
     */
    public boolean containsSGSNLocationInformation() {
        return _data.getContainer().contains(S6a_r10AttributeName.SGSNLocationInformation);
    }

    /**
     * Gets the SGSNLocationInformation.
     */
    public SGSNLocationInformation getSGSNLocationInformation() throws NoSuchAttributeException {
        return (SGSNLocationInformation)_data.getContainer().get(S6a_r10AttributeName.SGSNLocationInformation, 0);
    }

    /**
     * Sets the SGSNLocationInformation.
     *
     * @param avp - the attribute value
     */
    public void setSGSNLocationInformation(SGSNLocationInformation avp) {
        _data.getContainer().add(S6a_r10AttributeName.SGSNLocationInformation, avp.getData(), true);
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
        if (containsMMELocationInformation()) {
            sb.append("    MMELocationInformation:");
            try {
                sb.append(getMMELocationInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSGSNLocationInformation()) {
            sb.append("    SGSNLocationInformation:");
            try {
                sb.append(getSGSNLocationInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
