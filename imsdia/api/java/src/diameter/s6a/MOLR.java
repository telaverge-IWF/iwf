package diameter.s6a;

import com.intellinet.diameter.*;


public class MOLR extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MOLR.
     */
    public MOLR() {}

    MOLR(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the SSCode.
     */
    public SSCode getSSCode() throws NoSuchAttributeException {
        return (SSCode)_data.getContainer().get(S6aAttributeName.SSCode, 0);
    }

    /**
     * Sets the SSCode.
     *
     * @param avp - the attribute value
     */
    public void setSSCode(SSCode avp) {
        _data.getContainer().add(S6aAttributeName.SSCode, avp.getData(), true);
    }

    /**
     * Gets the SSStatus.
     */
    public SSStatus getSSStatus() throws NoSuchAttributeException {
        return (SSStatus)_data.getContainer().get(S6aAttributeName.SSStatus, 0);
    }

    /**
     * Sets the SSStatus.
     *
     * @param avp - the attribute value
     */
    public void setSSStatus(SSStatus avp) {
        _data.getContainer().add(S6aAttributeName.SSStatus, avp.getData(), true);
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
        sb.append("    SSCode:");
            try {
                sb.append(getSSCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    SSStatus:");
            try {
                sb.append(getSSStatus()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
