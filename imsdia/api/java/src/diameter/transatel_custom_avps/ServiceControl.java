package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class ServiceControl extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServiceControl.
     */
    public ServiceControl() {}

    ServiceControl(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SCPAction.
     */
    public boolean containsSCPAction() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.SCPAction);
    }

    /**
     * Gets the SCPAction.
     */
    public SCPAction getSCPAction() throws NoSuchAttributeException {
        return (SCPAction)_data.getContainer().get(Transatel_custom_avpsAttributeName.SCPAction, 0);
    }

    /**
     * Sets the SCPAction.
     *
     * @param avp - the attribute value
     */
    public void setSCPAction(SCPAction avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.SCPAction, avp.getData(), true);
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
        if (containsSCPAction()) {
            sb.append("    SCPAction:");
            try {
                sb.append(getSCPAction()).append('\n');
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
