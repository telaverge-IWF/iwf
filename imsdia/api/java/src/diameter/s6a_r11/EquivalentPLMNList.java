package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class EquivalentPLMNList extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new EquivalentPLMNList.
     */
    public EquivalentPLMNList() {}

    EquivalentPLMNList(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of VisitedPLMNId instances.
     */
    public int countVisitedPLMNId() {
        return _data.getContainer().count(S6a_r11AttributeName.VisitedPLMNId);
    }

    /**
     * Gets one VisitedPLMNId.
     *
     * @param index - the index of the attribute to return
     */
    public VisitedPLMNId getVisitedPLMNId(int index) throws NoSuchAttributeException {
        return (VisitedPLMNId)_data.getContainer().get(S6a_r11AttributeName.VisitedPLMNId, index);
    }

    /**
     * Adds one VisitedPLMNId.
     *
     * @param avp - the attribute value
     */
    public void addVisitedPLMNId(VisitedPLMNId avp) {
        _data.getContainer().add(S6a_r11AttributeName.VisitedPLMNId, avp.getData(), false);
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
        for (int i = 0; i < countVisitedPLMNId(); ++i) {
            sb.append("    VisitedPLMNId:");
            try {
                sb.append(getVisitedPLMNId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
