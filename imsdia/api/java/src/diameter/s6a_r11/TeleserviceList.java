package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class TeleserviceList extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TeleserviceList.
     */
    public TeleserviceList() {}

    TeleserviceList(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of TSCode instances.
     */
    public int countTSCode() {
        return _data.getContainer().count(S6a_r11AttributeName.TSCode);
    }

    /**
     * Gets one TSCode.
     *
     * @param index - the index of the attribute to return
     */
    public TSCode getTSCode(int index) throws NoSuchAttributeException {
        return (TSCode)_data.getContainer().get(S6a_r11AttributeName.TSCode, index);
    }

    /**
     * Adds one TSCode.
     *
     * @param avp - the attribute value
     */
    public void addTSCode(TSCode avp) {
        _data.getContainer().add(S6a_r11AttributeName.TSCode, avp.getData(), false);
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
        for (int i = 0; i < countTSCode(); ++i) {
            sb.append("    TSCode:");
            try {
                sb.append(getTSCode(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
