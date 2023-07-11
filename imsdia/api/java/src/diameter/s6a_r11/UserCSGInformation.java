package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class UserCSGInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new UserCSGInformation.
     */
    public UserCSGInformation() {}

    UserCSGInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the CSGId.
     */
    public CSGId getCSGId() throws NoSuchAttributeException {
        return (CSGId)_data.getContainer().get(S6a_r11AttributeName.CSGId, 0);
    }

    /**
     * Sets the CSGId.
     *
     * @param avp - the attribute value
     */
    public void setCSGId(CSGId avp) {
        _data.getContainer().add(S6a_r11AttributeName.CSGId, avp.getData(), true);
    }

    /**
     * Gets the CSGAccessMode.
     */
    public CSGAccessMode getCSGAccessMode() throws NoSuchAttributeException {
        return (CSGAccessMode)_data.getContainer().get(S6a_r11AttributeName.CSGAccessMode, 0);
    }

    /**
     * Sets the CSGAccessMode.
     *
     * @param avp - the attribute value
     */
    public void setCSGAccessMode(CSGAccessMode avp) {
        _data.getContainer().add(S6a_r11AttributeName.CSGAccessMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any CSGMembershipIndication.
     */
    public boolean containsCSGMembershipIndication() {
        return _data.getContainer().contains(S6a_r11AttributeName.CSGMembershipIndication);
    }

    /**
     * Gets the CSGMembershipIndication.
     */
    public CSGMembershipIndication getCSGMembershipIndication() throws NoSuchAttributeException {
        return (CSGMembershipIndication)_data.getContainer().get(S6a_r11AttributeName.CSGMembershipIndication, 0);
    }

    /**
     * Sets the CSGMembershipIndication.
     *
     * @param avp - the attribute value
     */
    public void setCSGMembershipIndication(CSGMembershipIndication avp) {
        _data.getContainer().add(S6a_r11AttributeName.CSGMembershipIndication, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    CSGId:");
            try {
                sb.append(getCSGId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CSGAccessMode:");
            try {
                sb.append(getCSGAccessMode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsCSGMembershipIndication()) {
            sb.append("    CSGMembershipIndication:");
            try {
                sb.append(getCSGMembershipIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
