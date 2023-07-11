package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CSInformation.
     */
    public CSInformation() {}

    CSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CallType.
     */
    public boolean containsCallType() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CallType);
    }

    /**
     * Gets the CallType.
     */
    public CallType getCallType() throws NoSuchAttributeException {
        return (CallType)_data.getContainer().get(Transatel_custom_avpsAttributeName.CallType, 0);
    }

    /**
     * Sets the CallType.
     *
     * @param avp - the attribute value
     */
    public void setCallType(CallType avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CallType, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPInformation.
     */
    public boolean containsCAPInformation() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPInformation);
    }

    /**
     * Gets the CAPInformation.
     */
    public CAPInformation getCAPInformation() throws NoSuchAttributeException {
        return (CAPInformation)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPInformation, 0);
    }

    /**
     * Sets the CAPInformation.
     *
     * @param avp - the attribute value
     */
    public void setCAPInformation(CAPInformation avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPInformation, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCallType()) {
            sb.append("    CallType:");
            try {
                sb.append(getCallType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPInformation()) {
            sb.append("    CAPInformation:");
            try {
                sb.append(getCAPInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
