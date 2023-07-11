package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The User-CSG-Information AVP (AVP code 2319) is of type Grouped and holds the user .
* Closed Subscriber Group. Information associated to CSG cell access: it comprises CSG ID 
* within the PLMN, Access mode and indication on CSG membership for the user when hybrid access 
* applies, as defined in TS 29.060 [225] for GPRS case, and in TS 29.274 [226] for EPC case
*/
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
        return (CSGId)_data.getContainer().get(Ro_r10_transatelAttributeName.CSGId, 0);
    }

    /**
     * Sets the CSGId.
     *
     * @param avp - the attribute value
     */
    public void setCSGId(CSGId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CSGId, avp.getData(), true);
    }

    /**
     * Gets the CSGAccessMode.
     */
    public CSGAccessMode getCSGAccessMode() throws NoSuchAttributeException {
        return (CSGAccessMode)_data.getContainer().get(Ro_r10_transatelAttributeName.CSGAccessMode, 0);
    }

    /**
     * Sets the CSGAccessMode.
     *
     * @param avp - the attribute value
     */
    public void setCSGAccessMode(CSGAccessMode avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CSGAccessMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any CSGMembershipIndication.
     */
    public boolean containsCSGMembershipIndication() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CSGMembershipIndication);
    }

    /**
     * Gets the CSGMembershipIndication.
     */
    public CSGMembershipIndication getCSGMembershipIndication() throws NoSuchAttributeException {
        return (CSGMembershipIndication)_data.getContainer().get(Ro_r10_transatelAttributeName.CSGMembershipIndication, 0);
    }

    /**
     * Sets the CSGMembershipIndication.
     *
     * @param avp - the attribute value
     */
    public void setCSGMembershipIndication(CSGMembershipIndication avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CSGMembershipIndication, avp.getData(), true);
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
