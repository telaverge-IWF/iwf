package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPRRBSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CAPRRBSInformation.
     */
    public CAPRRBSInformation() {}

    CAPRRBSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CAPRRBSNoAnswerTimeout.
     */
    public boolean containsCAPRRBSNoAnswerTimeout() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPRRBSNoAnswerTimeout);
    }

    /**
     * Gets the CAPRRBSNoAnswerTimeout.
     */
    public CAPRRBSNoAnswerTimeout getCAPRRBSNoAnswerTimeout() throws NoSuchAttributeException {
        return (CAPRRBSNoAnswerTimeout)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPRRBSNoAnswerTimeout, 0);
    }

    /**
     * Sets the CAPRRBSNoAnswerTimeout.
     *
     * @param avp - the attribute value
     */
    public void setCAPRRBSNoAnswerTimeout(CAPRRBSNoAnswerTimeout avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPRRBSNoAnswerTimeout, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCAPRRBSNoAnswerTimeout()) {
            sb.append("    CAPRRBSNoAnswerTimeout:");
            try {
                sb.append(getCAPRRBSNoAnswerTimeout()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
