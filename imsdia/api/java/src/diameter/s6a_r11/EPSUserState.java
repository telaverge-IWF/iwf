package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class EPSUserState extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new EPSUserState.
     */
    public EPSUserState() {}

    EPSUserState(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any MMEUserState.
     */
    public boolean containsMMEUserState() {
        return _data.getContainer().contains(S6a_r11AttributeName.MMEUserState);
    }

    /**
     * Gets the MMEUserState.
     */
    public MMEUserState getMMEUserState() throws NoSuchAttributeException {
        return (MMEUserState)_data.getContainer().get(S6a_r11AttributeName.MMEUserState, 0);
    }

    /**
     * Sets the MMEUserState.
     *
     * @param avp - the attribute value
     */
    public void setMMEUserState(MMEUserState avp) {
        _data.getContainer().add(S6a_r11AttributeName.MMEUserState, avp.getData(), true);
    }

    /**
     * Tests whether there is any SGSNUserState.
     */
    public boolean containsSGSNUserState() {
        return _data.getContainer().contains(S6a_r11AttributeName.SGSNUserState);
    }

    /**
     * Gets the SGSNUserState.
     */
    public SGSNUserState getSGSNUserState() throws NoSuchAttributeException {
        return (SGSNUserState)_data.getContainer().get(S6a_r11AttributeName.SGSNUserState, 0);
    }

    /**
     * Sets the SGSNUserState.
     *
     * @param avp - the attribute value
     */
    public void setSGSNUserState(SGSNUserState avp) {
        _data.getContainer().add(S6a_r11AttributeName.SGSNUserState, avp.getData(), true);
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
        if (containsMMEUserState()) {
            sb.append("    MMEUserState:");
            try {
                sb.append(getMMEUserState()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSGSNUserState()) {
            sb.append("    SGSNUserState:");
            try {
                sb.append(getSGSNUserState()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
