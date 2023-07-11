package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class GPRSSubscriptionData extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new GPRSSubscriptionData.
     */
    public GPRSSubscriptionData() {}

    GPRSSubscriptionData(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the CompleteDataListIncludedIndicator.
     */
    public CompleteDataListIncludedIndicator getCompleteDataListIncludedIndicator() throws NoSuchAttributeException {
        return (CompleteDataListIncludedIndicator)_data.getContainer().get(S6a_r11AttributeName.CompleteDataListIncludedIndicator, 0);
    }

    /**
     * Sets the CompleteDataListIncludedIndicator.
     *
     * @param avp - the attribute value
     */
    public void setCompleteDataListIncludedIndicator(CompleteDataListIncludedIndicator avp) {
        _data.getContainer().add(S6a_r11AttributeName.CompleteDataListIncludedIndicator, avp.getData(), true);
    }

    /**
     * Returns number of PDPContext instances.
     */
    public int countPDPContext() {
        return _data.getContainer().count(S6a_r11AttributeName.PDPContext);
    }

    /**
     * Gets one PDPContext.
     *
     * @param index - the index of the attribute to return
     */
    public PDPContext getPDPContext(int index) throws NoSuchAttributeException {
        return (PDPContext)_data.getContainer().get(S6a_r11AttributeName.PDPContext, index);
    }

    /**
     * Adds one PDPContext.
     *
     * @param avp - the attribute value
     */
    public void addPDPContext(PDPContext avp) {
        _data.getContainer().add(S6a_r11AttributeName.PDPContext, avp.getData(), false);
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
        sb.append("    CompleteDataListIncludedIndicator:");
            try {
                sb.append(getCompleteDataListIncludedIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        for (int i = 0; i < countPDPContext(); ++i) {
            sb.append("    PDPContext:");
            try {
                sb.append(getPDPContext(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
