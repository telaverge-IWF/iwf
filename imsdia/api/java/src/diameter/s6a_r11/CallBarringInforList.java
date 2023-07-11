package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class CallBarringInforList extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CallBarringInforList.
     */
    public CallBarringInforList() {}

    CallBarringInforList(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of SSCode instances.
     */
    public int countSSCode() {
        return _data.getContainer().count(S6a_r11AttributeName.SSCode);
    }

    /**
     * Gets one SSCode.
     *
     * @param index - the index of the attribute to return
     */
    public SSCode getSSCode(int index) throws NoSuchAttributeException {
        return (SSCode)_data.getContainer().get(S6a_r11AttributeName.SSCode, index);
    }

    /**
     * Adds one SSCode.
     *
     * @param avp - the attribute value
     */
    public void addSSCode(SSCode avp) {
        _data.getContainer().add(S6a_r11AttributeName.SSCode, avp.getData(), false);
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
        for (int i = 0; i < countSSCode(); ++i) {
            sb.append("    SSCode:");
            try {
                sb.append(getSSCode(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
