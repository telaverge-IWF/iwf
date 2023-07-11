package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPERBSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CAPERBSInformation.
     */
    public CAPERBSInformation() {}

    CAPERBSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CAPEventTypeBCSM.
     */
    public boolean containsCAPEventTypeBCSM() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPEventTypeBCSM);
    }

    /**
     * Gets the CAPEventTypeBCSM.
     */
    public CAPEventTypeBCSM getCAPEventTypeBCSM() throws NoSuchAttributeException {
        return (CAPEventTypeBCSM)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPEventTypeBCSM, 0);
    }

    /**
     * Sets the CAPEventTypeBCSM.
     *
     * @param avp - the attribute value
     */
    public void setCAPEventTypeBCSM(CAPEventTypeBCSM avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPEventTypeBCSM, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPEventTypeSMS.
     */
    public boolean containsCAPEventTypeSMS() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPEventTypeSMS);
    }

    /**
     * Gets the CAPEventTypeSMS.
     */
    public CAPEventTypeSMS getCAPEventTypeSMS() throws NoSuchAttributeException {
        return (CAPEventTypeSMS)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPEventTypeSMS, 0);
    }

    /**
     * Sets the CAPEventTypeSMS.
     *
     * @param avp - the attribute value
     */
    public void setCAPEventTypeSMS(CAPEventTypeSMS avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPEventTypeSMS, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPERBSEventSpecificInformation.
     */
    public boolean containsCAPERBSEventSpecificInformation() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPERBSEventSpecificInformation);
    }

    /**
     * Gets the CAPERBSEventSpecificInformation.
     */
    public CAPERBSEventSpecificInformation getCAPERBSEventSpecificInformation() throws NoSuchAttributeException {
        return (CAPERBSEventSpecificInformation)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPERBSEventSpecificInformation, 0);
    }

    /**
     * Sets the CAPERBSEventSpecificInformation.
     *
     * @param avp - the attribute value
     */
    public void setCAPERBSEventSpecificInformation(CAPERBSEventSpecificInformation avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPERBSEventSpecificInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPERBSLegId.
     */
    public boolean containsCAPERBSLegId() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPERBSLegId);
    }

    /**
     * Gets the CAPERBSLegId.
     */
    public CAPERBSLegId getCAPERBSLegId() throws NoSuchAttributeException {
        return (CAPERBSLegId)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPERBSLegId, 0);
    }

    /**
     * Sets the CAPERBSLegId.
     *
     * @param avp - the attribute value
     */
    public void setCAPERBSLegId(CAPERBSLegId avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPERBSLegId, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPERBSMessageType.
     */
    public boolean containsCAPERBSMessageType() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPERBSMessageType);
    }

    /**
     * Gets the CAPERBSMessageType.
     */
    public CAPERBSMessageType getCAPERBSMessageType() throws NoSuchAttributeException {
        return (CAPERBSMessageType)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPERBSMessageType, 0);
    }

    /**
     * Sets the CAPERBSMessageType.
     *
     * @param avp - the attribute value
     */
    public void setCAPERBSMessageType(CAPERBSMessageType avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPERBSMessageType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCAPEventTypeBCSM()) {
            sb.append("    CAPEventTypeBCSM:");
            try {
                sb.append(getCAPEventTypeBCSM()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPEventTypeSMS()) {
            sb.append("    CAPEventTypeSMS:");
            try {
                sb.append(getCAPEventTypeSMS()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPERBSEventSpecificInformation()) {
            sb.append("    CAPERBSEventSpecificInformation:");
            try {
                sb.append(getCAPERBSEventSpecificInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPERBSLegId()) {
            sb.append("    CAPERBSLegId:");
            try {
                sb.append(getCAPERBSLegId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPERBSMessageType()) {
            sb.append("    CAPERBSMessageType:");
            try {
                sb.append(getCAPERBSMessageType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
