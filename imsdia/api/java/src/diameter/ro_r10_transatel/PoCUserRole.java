package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The PoC-User-Role AVP (AVP code 1252) is of type Grouped. It specifies the 
 * role(s) related information of the PoC User that participating in the PoC 
 * Session.
 */
public class PoCUserRole extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new PoCUserRole.
     */
    public PoCUserRole() {}

    PoCUserRole(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any PoCUserRoleIds.
     */
    public boolean containsPoCUserRoleIds() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCUserRoleIds);
    }

    /**
     * Gets the PoCUserRoleIds.
     */
    public PoCUserRoleIds getPoCUserRoleIds() throws NoSuchAttributeException {
        return (PoCUserRoleIds)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCUserRoleIds, 0);
    }

    /**
     * Sets the PoCUserRoleIds.
     *
     * @param avp - the attribute value
     */
    public void setPoCUserRoleIds(PoCUserRoleIds avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCUserRoleIds, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCUserRoleinfoUnits.
     */
    public boolean containsPoCUserRoleinfoUnits() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCUserRoleinfoUnits);
    }

    /**
     * Gets the PoCUserRoleinfoUnits.
     */
    public PoCUserRoleinfoUnits getPoCUserRoleinfoUnits() throws NoSuchAttributeException {
        return (PoCUserRoleinfoUnits)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCUserRoleinfoUnits, 0);
    }

    /**
     * Sets the PoCUserRoleinfoUnits.
     *
     * @param avp - the attribute value
     */
    public void setPoCUserRoleinfoUnits(PoCUserRoleinfoUnits avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCUserRoleinfoUnits, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsPoCUserRoleIds()) {
            sb.append("    PoCUserRoleIds:");
            try {
                sb.append(getPoCUserRoleIds()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCUserRoleinfoUnits()) {
            sb.append("    PoCUserRoleinfoUnits:");
            try {
                sb.append(getPoCUserRoleinfoUnits()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
