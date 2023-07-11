package diameter.ro_r10;

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
        return (PoCChangeTime)_data.getContainer().get(Ro_r10AttributeName.PoCChangeTime, 0);
    }

    /**
     * Sets the PoCChangeTime.
     *
     * @param avp - the attribute value
     */
    public void setPoCChangeTime(PoCChangeTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.PoCChangeTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfTalkBursts.
     */
    public boolean containsNumberOfTalkBursts() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberOfTalkBursts);
    }

    /**
     * Gets the NumberOfTalkBursts.
     */
    public NumberOfTalkBursts getNumberOfTalkBursts() throws NoSuchAttributeException {
        return (NumberOfTalkBursts)_data.getContainer().get(Ro_r10AttributeName.NumberOfTalkBursts, 0);
    }

    /**
     * Sets the NumberOfTalkBursts.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfTalkBursts(NumberOfTalkBursts avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberOfTalkBursts, avp.getData(), true);
    }

    /**
     * Tests whether there is any TalkBurstVolume.
     */
    public boolean containsTalkBurstVolume() {
        return _data.getContainer().contains(Ro_r10AttributeName.TalkBurstVolume);
    }

    /**
     * Gets the TalkBurstVolume.
     */
    public TalkBurstVolume getTalkBurstVolume() throws NoSuchAttributeException {
        return (TalkBurstVolume)_data.getContainer().get(Ro_r10AttributeName.TalkBurstVolume, 0);
    }

    /**
     * Sets the TalkBurstVolume.
     *
     * @param avp - the attribute value
     */
    public void setTalkBurstVolume(TalkBurstVolume avp) {
        _data.getContainer().add(Ro_r10AttributeName.TalkBurstVolume, avp.getData(), true);
    }

    /**
     * Tests whether there is any TalkBurstTime.
     */
    public boolean containsTalkBurstTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.TalkBurstTime);
    }

    /**
     * Gets the TalkBurstTime.
     */
    public TalkBurstTime getTalkBurstTime() throws NoSuchAttributeException {
        return (TalkBurstTime)_data.getContainer().get(Ro_r10AttributeName.TalkBurstTime, 0);
    }

    /**
     * Sets the TalkBurstTime.
     *
     * @param avp - the attribute value
     */
    public void setTalkBurstTime(TalkBurstTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.TalkBurstTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfReceivedTalkBursts.
     */
    public boolean containsNumberOfReceivedTalkBursts() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberOfReceivedTalkBursts);
    }

    /**
     * Gets the NumberOfReceivedTalkBursts.
     */
    public NumberOfReceivedTalkBursts getNumberOfReceivedTalkBursts() throws NoSuchAttributeException {
        return (NumberOfReceivedTalkBursts)_data.getContainer().get(Ro_r10AttributeName.NumberOfReceivedTalkBursts, 0);
    }

    /**
     * Sets the NumberOfReceivedTalkBursts.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfReceivedTalkBursts(NumberOfReceivedTalkBursts avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberOfReceivedTalkBursts, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReceivedTalkBurstVolume.
     */
    public boolean containsReceivedTalkBurstVolume() {
        return _data.getContainer().contains(Ro_r10AttributeName.ReceivedTalkBurstVolume);
    }

    /**
     * Gets the ReceivedTalkBurstVolume.
     */
    public ReceivedTalkBurstVolume getReceivedTalkBurstVolume() throws NoSuchAttributeException {
        return (ReceivedTalkBurstVolume)_data.getContainer().get(Ro_r10AttributeName.ReceivedTalkBurstVolume, 0);
    }

    /**
     * Sets the ReceivedTalkBurstVolume.
     *
     * @param avp - the attribute value
     */
    public void setReceivedTalkBurstVolume(ReceivedTalkBurstVolume avp) {
        _data.getContainer().add(Ro_r10AttributeName.ReceivedTalkBurstVolume, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReceivedTalkBurstTime.
     */
    public boolean containsReceivedTalkBurstTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.ReceivedTalkBurstTime);
    }

    /**
     * Gets the ReceivedTalkBurstTime.
     */
    public ReceivedTalkBurstTime getReceivedTalkBurstTime() throws NoSuchAttributeException {
        return (ReceivedTalkBurstTime)_data.getContainer().get(Ro_r10AttributeName.ReceivedTalkBurstTime, 0);
    }

    /**
     * Sets the ReceivedTalkBurstTime.
     *
     * @param avp - the attribute value
     */
    public void setReceivedTalkBurstTime(ReceivedTalkBurstTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.ReceivedTalkBurstTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfParticipants.
     */
    public boolean containsNumberOfParticipants() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberOfParticipants);
    }

    /**
     * Gets the NumberOfParticipants.
     */
    public NumberOfParticipants getNumberOfParticipants() throws NoSuchAttributeException {
        return (NumberOfParticipants)_data.getContainer().get(Ro_r10AttributeName.NumberOfParticipants, 0);
    }

    /**
     * Sets the NumberOfParticipants.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfParticipants(NumberOfParticipants avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberOfParticipants, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCChangeCondition.
     */
    public boolean containsPoCChangeCondition() {
        return _data.getContainer().contains(Ro_r10AttributeName.PoCChangeCondition);
    }

    /**
     * Gets the PoCChangeCondition.
     */
    public PoCChangeCondition getPoCChangeCondition() throws NoSuchAttributeException {
        return (PoCChangeCondition)_data.getContainer().get(Ro_r10AttributeName.PoCChangeCondition, 0);
    }

    /**
     * Sets the PoCChangeCondition.
     *
     * @param avp - the attribute value
     */
    public void setPoCChangeCondition(PoCChangeCondition avp) {
        _data.getContainer().add(Ro_r10AttributeName.PoCChangeCondition, avp.getData(), true);
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
