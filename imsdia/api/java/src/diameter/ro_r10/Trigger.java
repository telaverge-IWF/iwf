package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Trigger AVP (AVP code 1264) is of type Grouped and holds the trigger
 * types. The presence of the Trigger AVP without any Trigger-Type AVP in a
 * CCA allows OCS to disable all the triggers. The presence of the Trigger
 * AVP in the CCR identifies the event(s) triggering the CCR.
 */
public class Trigger extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new Trigger.
     */
    public Trigger() {}

    Trigger(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of TriggerType instances.
     */
    public int countTriggerType() {
        return _data.getContainer().count(Ro_r10AttributeName.TriggerType);
    }

    /**
     * Gets one TriggerType.
     *
     * @param index - the index of the attribute to return
     */
    public TriggerType getTriggerType(int index) throws NoSuchAttributeException {
        return (TriggerType)_data.getContainer().get(Ro_r10AttributeName.TriggerType, index);
    }

    /**
     * Adds one TriggerType.
     *
     * @param avp - the attribute value
     */
    public void addTriggerType(TriggerType avp) {
        _data.getContainer().add(Ro_r10AttributeName.TriggerType, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        for (int i = 0; i < countTriggerType(); ++i) {
            sb.append("    TriggerType:");
            try {
                sb.append(getTriggerType(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
