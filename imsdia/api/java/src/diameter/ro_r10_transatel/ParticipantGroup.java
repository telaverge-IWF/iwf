package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Participant-Group AVP (AVP code 1260) is of type Grouped and holds 
 * detailed information, e.g. the address (Public User ID: SIP URI, TEL URI, 
 * MSISDN), the access priority parameters, etc, of the party who is involved 
 * into the PoC session.
 */
public class ParticipantGroup extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ParticipantGroup.
     */
    public ParticipantGroup() {}

    ParticipantGroup(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CalledPartyAddress.
     */
    public boolean containsCalledPartyAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CalledPartyAddress);
    }

    /**
     * Gets the CalledPartyAddress.
     */
    public CalledPartyAddress getCalledPartyAddress() throws NoSuchAttributeException {
        return (CalledPartyAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.CalledPartyAddress, 0);
    }

    /**
     * Sets the CalledPartyAddress.
     *
     * @param avp - the attribute value
     */
    public void setCalledPartyAddress(CalledPartyAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CalledPartyAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any ParticipantAccessPriority.
     */
    public boolean containsParticipantAccessPriority() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ParticipantAccessPriority);
    }

    /**
     * Gets the ParticipantAccessPriority.
     */
    public ParticipantAccessPriority getParticipantAccessPriority() throws NoSuchAttributeException {
        return (ParticipantAccessPriority)_data.getContainer().get(Ro_r10_transatelAttributeName.ParticipantAccessPriority, 0);
    }

    /**
     * Sets the ParticipantAccessPriority.
     *
     * @param avp - the attribute value
     */
    public void setParticipantAccessPriority(ParticipantAccessPriority avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ParticipantAccessPriority, avp.getData(), true);
    }

    /**
     * Tests whether there is any UserParticipatingType.
     */
    public boolean containsUserParticipatingType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.UserParticipatingType);
    }

    /**
     * Gets the UserParticipatingType.
     */
    public UserParticipatingType getUserParticipatingType() throws NoSuchAttributeException {
        return (UserParticipatingType)_data.getContainer().get(Ro_r10_transatelAttributeName.UserParticipatingType, 0);
    }

    /**
     * Sets the UserParticipatingType.
     *
     * @param avp - the attribute value
     */
    public void setUserParticipatingType(UserParticipatingType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.UserParticipatingType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCalledPartyAddress()) {
            sb.append("    CalledPartyAddress:");
            try {
                sb.append(getCalledPartyAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsParticipantAccessPriority()) {
            sb.append("    ParticipantAccessPriority:");
            try {
                sb.append(getParticipantAccessPriority()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserParticipatingType()) {
            sb.append("    UserParticipatingType:");
            try {
                sb.append(getUserParticipatingType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
