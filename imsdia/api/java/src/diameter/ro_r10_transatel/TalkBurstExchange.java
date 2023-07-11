package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Talk-Burst-Exchange AVP is of type Grouped and holds the talk burst related charging data.
 */
public class TalkBurstExchange extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TalkBurstExchange.
     */
    public TalkBurstExchange() {}

    TalkBurstExchange(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the PoCChangeTime.
     */
    public PoCChangeTime getPoCChangeTime() throws NoSuchAttributeException {
        return (PoCChangeTime)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCChangeTime, 0);
    }

    /**
     * Sets the PoCChangeTime.
     *
     * @param avp - the attribute value
     */
    public void setPoCChangeTime(PoCChangeTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCChangeTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfTalkBursts.
     */
    public boolean containsNumberOfTalkBursts() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.NumberOfTalkBursts);
    }

    /**
     * Gets the NumberOfTalkBursts.
     */
    public NumberOfTalkBursts getNumberOfTalkBursts() throws NoSuchAttributeException {
        return (NumberOfTalkBursts)_data.getContainer().get(Ro_r10_transatelAttributeName.NumberOfTalkBursts, 0);
    }

    /**
     * Sets the NumberOfTalkBursts.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfTalkBursts(NumberOfTalkBursts avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.NumberOfTalkBursts, avp.getData(), true);
    }

    /**
     * Tests whether there is any TalkBurstVolume.
     */
    public boolean containsTalkBurstVolume() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TalkBurstVolume);
    }

    /**
     * Gets the TalkBurstVolume.
     */
    public TalkBurstVolume getTalkBurstVolume() throws NoSuchAttributeException {
        return (TalkBurstVolume)_data.getContainer().get(Ro_r10_transatelAttributeName.TalkBurstVolume, 0);
    }

    /**
     * Sets the TalkBurstVolume.
     *
     * @param avp - the attribute value
     */
    public void setTalkBurstVolume(TalkBurstVolume avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TalkBurstVolume, avp.getData(), true);
    }

    /**
     * Tests whether there is any TalkBurstTime.
     */
    public boolean containsTalkBurstTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TalkBurstTime);
    }

    /**
     * Gets the TalkBurstTime.
     */
    public TalkBurstTime getTalkBurstTime() throws NoSuchAttributeException {
        return (TalkBurstTime)_data.getContainer().get(Ro_r10_transatelAttributeName.TalkBurstTime, 0);
    }

    /**
     * Sets the TalkBurstTime.
     *
     * @param avp - the attribute value
     */
    public void setTalkBurstTime(TalkBurstTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TalkBurstTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfReceivedTalkBursts.
     */
    public boolean containsNumberOfReceivedTalkBursts() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.NumberOfReceivedTalkBursts);
    }

    /**
     * Gets the NumberOfReceivedTalkBursts.
     */
    public NumberOfReceivedTalkBursts getNumberOfReceivedTalkBursts() throws NoSuchAttributeException {
        return (NumberOfReceivedTalkBursts)_data.getContainer().get(Ro_r10_transatelAttributeName.NumberOfReceivedTalkBursts, 0);
    }

    /**
     * Sets the NumberOfReceivedTalkBursts.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfReceivedTalkBursts(NumberOfReceivedTalkBursts avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.NumberOfReceivedTalkBursts, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReceivedTalkBurstVolume.
     */
    public boolean containsReceivedTalkBurstVolume() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ReceivedTalkBurstVolume);
    }

    /**
     * Gets the ReceivedTalkBurstVolume.
     */
    public ReceivedTalkBurstVolume getReceivedTalkBurstVolume() throws NoSuchAttributeException {
        return (ReceivedTalkBurstVolume)_data.getContainer().get(Ro_r10_transatelAttributeName.ReceivedTalkBurstVolume, 0);
    }

    /**
     * Sets the ReceivedTalkBurstVolume.
     *
     * @param avp - the attribute value
     */
    public void setReceivedTalkBurstVolume(ReceivedTalkBurstVolume avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ReceivedTalkBurstVolume, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReceivedTalkBurstTime.
     */
    public boolean containsReceivedTalkBurstTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ReceivedTalkBurstTime);
    }

    /**
     * Gets the ReceivedTalkBurstTime.
     */
    public ReceivedTalkBurstTime getReceivedTalkBurstTime() throws NoSuchAttributeException {
        return (ReceivedTalkBurstTime)_data.getContainer().get(Ro_r10_transatelAttributeName.ReceivedTalkBurstTime, 0);
    }

    /**
     * Sets the ReceivedTalkBurstTime.
     *
     * @param avp - the attribute value
     */
    public void setReceivedTalkBurstTime(ReceivedTalkBurstTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ReceivedTalkBurstTime, avp.getData(), true);
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
     * Tests whether there is any PoCChangeCondition.
     */
    public boolean containsPoCChangeCondition() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PoCChangeCondition);
    }

    /**
     * Gets the PoCChangeCondition.
     */
    public PoCChangeCondition getPoCChangeCondition() throws NoSuchAttributeException {
        return (PoCChangeCondition)_data.getContainer().get(Ro_r10_transatelAttributeName.PoCChangeCondition, 0);
    }

    /**
     * Sets the PoCChangeCondition.
     *
     * @param avp - the attribute value
     */
    public void setPoCChangeCondition(PoCChangeCondition avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PoCChangeCondition, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    PoCChangeTime:");
            try {
                sb.append(getPoCChangeTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsNumberOfTalkBursts()) {
            sb.append("    NumberOfTalkBursts:");
            try {
                sb.append(getNumberOfTalkBursts()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTalkBurstVolume()) {
            sb.append("    TalkBurstVolume:");
            try {
                sb.append(getTalkBurstVolume()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTalkBurstTime()) {
            sb.append("    TalkBurstTime:");
            try {
                sb.append(getTalkBurstTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberOfReceivedTalkBursts()) {
            sb.append("    NumberOfReceivedTalkBursts:");
            try {
                sb.append(getNumberOfReceivedTalkBursts()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReceivedTalkBurstVolume()) {
            sb.append("    ReceivedTalkBurstVolume:");
            try {
                sb.append(getReceivedTalkBurstVolume()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReceivedTalkBurstTime()) {
            sb.append("    ReceivedTalkBurstTime:");
            try {
                sb.append(getReceivedTalkBurstTime()).append('\n');
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
        if (containsPoCChangeCondition()) {
            sb.append("    PoCChangeCondition:");
            try {
                sb.append(getPoCChangeCondition()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
