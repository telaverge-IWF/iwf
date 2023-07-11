package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * PoC-Information AVP is of type Grouped. Its purpose is to allow transmission of additional 
 * PoC service specific information elements.
 */
public class PoCInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new PoCInformation.
     */
    public PoCInformation() {}

    PoCInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any PoCServerRole.
     */
    public boolean containsPoCServerRole() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCServerRole);
    }

    /**
     * Gets the PoCServerRole.
     */
    public PoCServerRole getPoCServerRole() throws NoSuchAttributeException {
        return (PoCServerRole)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCServerRole, 0);
    }

    /**
     * Sets the PoCServerRole.
     *
     * @param avp - the attribute value
     */
    public void setPoCServerRole(PoCServerRole avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCServerRole, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCSessionType.
     */
    public boolean containsPoCSessionType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCSessionType);
    }

    /**
     * Gets the PoCSessionType.
     */
    public PoCSessionType getPoCSessionType() throws NoSuchAttributeException {
        return (PoCSessionType)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCSessionType, 0);
    }

    /**
     * Sets the PoCSessionType.
     *
     * @param avp - the attribute value
     */
    public void setPoCSessionType(PoCSessionType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCSessionType, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCUserRole.
     */
    public boolean containsPoCUserRole() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCUserRole);
    }

    /**
     * Gets the PoCUserRole.
     */
    public PoCUserRole getPoCUserRole() throws NoSuchAttributeException {
        return (PoCUserRole)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCUserRole, 0);
    }

    /**
     * Sets the PoCUserRole.
     *
     * @param avp - the attribute value
     */
    public void setPoCUserRole(PoCUserRole avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCUserRole, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCSessionInitiationType.
     */
    public boolean containsPoCSessionInitiationType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCSessionInitiationType);
    }

    /**
     * Gets the PoCSessionInitiationType.
     */
    public PoCSessionInitiationType getPoCSessionInitiationType() throws NoSuchAttributeException {
        return (PoCSessionInitiationType)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCSessionInitiationType, 0);
    }

    /**
     * Sets the PoCSessionInitiationType.
     *
     * @param avp - the attribute value
     */
    public void setPoCSessionInitiationType(PoCSessionInitiationType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCSessionInitiationType, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCEventType.
     */
    public boolean containsPoCEventType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCEventType);
    }

    /**
     * Gets the PoCEventType.
     */
    public PoCEventType getPoCEventType() throws NoSuchAttributeException {
        return (PoCEventType)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCEventType, 0);
    }

    /**
     * Sets the PoCEventType.
     *
     * @param avp - the attribute value
     */
    public void setPoCEventType(PoCEventType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCEventType, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfParticipants.
     */
    public boolean containsNumberOfParticipants() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.NumberOfParticipants);
    }

    /**
     * Gets the NumberOfParticipants.
     */
    public NumberOfParticipants getNumberOfParticipants() throws NoSuchAttributeException {
        return (NumberOfParticipants)_data.getContainer().get(Ro_r10_transatelAttributeName.NumberOfParticipants, 0);
    }

    /**
     * Sets the NumberOfParticipants.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfParticipants(NumberOfParticipants avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.NumberOfParticipants, avp.getData(), true);
    }

    /**
     * Returns number of ParticipantsInvolved instances.
     */
    public int countParticipantsInvolved() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.ParticipantsInvolved);
    }

    /**
     * Gets one ParticipantsInvolved.
     *
     * @param index - the index of the attribute to return
     */
    public ParticipantsInvolved getParticipantsInvolved(int index) throws NoSuchAttributeException {
        return (ParticipantsInvolved)_data.getContainer().get(Ro_r10_transatelAttributeName.ParticipantsInvolved, index);
    }

    /**
     * Adds one ParticipantsInvolved.
     *
     * @param avp - the attribute value
     */
    public void addParticipantsInvolved(ParticipantsInvolved avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ParticipantsInvolved, avp.getData(), false);
    }

    /**
     * Returns number of ParticipantGroup instances.
     */
    public int countParticipantGroup() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.ParticipantGroup);
    }

    /**
     * Gets one ParticipantGroup.
     *
     * @param index - the index of the attribute to return
     */
    public ParticipantGroup getParticipantGroup(int index) throws NoSuchAttributeException {
        return (ParticipantGroup)_data.getContainer().get(Ro_r10_transatelAttributeName.ParticipantGroup, index);
    }

    /**
     * Adds one ParticipantGroup.
     *
     * @param avp - the attribute value
     */
    public void addParticipantGroup(ParticipantGroup avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ParticipantGroup, avp.getData(), false);
    }

    /**
     * Returns number of TalkBurstExchange instances.
     */
    public int countTalkBurstExchange() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.TalkBurstExchange);
    }

    /**
     * Gets one TalkBurstExchange.
     *
     * @param index - the index of the attribute to return
     */
    public TalkBurstExchange getTalkBurstExchange(int index) throws NoSuchAttributeException {
        return (TalkBurstExchange)_data.getContainer().get(Ro_r10_transatelAttributeName.TalkBurstExchange, index);
    }

    /**
     * Adds one TalkBurstExchange.
     *
     * @param avp - the attribute value
     */
    public void addTalkBurstExchange(TalkBurstExchange avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TalkBurstExchange, avp.getData(), false);
    }

    /**
     * Tests whether there is any PoCControllingAddress.
     */
    public boolean containsPoCControllingAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCControllingAddress);
    }

    /**
     * Gets the PoCControllingAddress.
     */
    public PoCControllingAddress getPoCControllingAddress() throws NoSuchAttributeException {
        return (PoCControllingAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCControllingAddress, 0);
    }

    /**
     * Sets the PoCControllingAddress.
     *
     * @param avp - the attribute value
     */
    public void setPoCControllingAddress(PoCControllingAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCControllingAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCGroupName.
     */
    public boolean containsPoCGroupName() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCGroupName);
    }

    /**
     * Gets the PoCGroupName.
     */
    public PoCGroupName getPoCGroupName() throws NoSuchAttributeException {
        return (PoCGroupName)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCGroupName, 0);
    }

    /**
     * Sets the PoCGroupName.
     *
     * @param avp - the attribute value
     */
    public void setPoCGroupName(PoCGroupName avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCGroupName, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCSessionId.
     */
    public boolean containsPoCSessionId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCSessionId);
    }

    /**
     * Gets the PoCSessionId.
     */
    public PoCSessionId getPoCSessionId() throws NoSuchAttributeException {
        return (PoCSessionId)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCSessionId, 0);
    }

    /**
     * Sets the PoCSessionId.
     *
     * @param avp - the attribute value
     */
    public void setPoCSessionId(PoCSessionId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCSessionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChargedParty.
     */
    public boolean containsChargedParty() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ChargedParty);
    }

    /**
     * Gets the ChargedParty.
     */
    public ChargedParty getChargedParty() throws NoSuchAttributeException {
        return (ChargedParty)_data.getContainer().get(Ro_r10_transatelAttributeName.ChargedParty, 0);
    }

    /**
     * Sets the ChargedParty.
     *
     * @param avp - the attribute value
     */
    public void setChargedParty(ChargedParty avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ChargedParty, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsPoCServerRole()) {
            sb.append("    PoCServerRole:");
            try {
                sb.append(getPoCServerRole()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCSessionType()) {
            sb.append("    PoCSessionType:");
            try {
                sb.append(getPoCSessionType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCUserRole()) {
            sb.append("    PoCUserRole:");
            try {
                sb.append(getPoCUserRole()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCSessionInitiationType()) {
            sb.append("    PoCSessionInitiationType:");
            try {
                sb.append(getPoCSessionInitiationType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCEventType()) {
            sb.append("    PoCEventType:");
            try {
                sb.append(getPoCEventType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberOfParticipants()) {
            sb.append("    NumberOfParticipants:");
            try {
                sb.append(getNumberOfParticipants()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countParticipantsInvolved(); ++i) {
            sb.append("    ParticipantsInvolved:");
            try {
                sb.append(getParticipantsInvolved(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countParticipantGroup(); ++i) {
            sb.append("    ParticipantGroup:");
            try {
                sb.append(getParticipantGroup(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countTalkBurstExchange(); ++i) {
            sb.append("    TalkBurstExchange:");
            try {
                sb.append(getTalkBurstExchange(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCControllingAddress()) {
            sb.append("    PoCControllingAddress:");
            try {
                sb.append(getPoCControllingAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCGroupName()) {
            sb.append("    PoCGroupName:");
            try {
                sb.append(getPoCGroupName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCSessionId()) {
            sb.append("    PoCSessionId:");
            try {
                sb.append(getPoCSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsChargedParty()) {
            sb.append("    ChargedParty:");
            try {
                sb.append(getChargedParty()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
