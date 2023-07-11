package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Flows AVP (AVP code 510) is of type Grouped, and it indicates IP flows
 * via their flow identifiers.
 * If no Flow-Number AVP(s) are supplied, the Flows AVP refers to all Flows
 * matching the media component number.
 */
public class Flows extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new Flows.
     */
    public Flows() {}

    Flows(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the MediaComponentNumber.
     */
    public MediaComponentNumber getMediaComponentNumber() throws NoSuchAttributeException {
        return (MediaComponentNumber)_data.getContainer().get(Ro_r10_transatelAttributeName.MediaComponentNumber, 0);
    }

    /**
     * Sets the MediaComponentNumber.
     *
     * @param avp - the attribute value
     */
    public void setMediaComponentNumber(MediaComponentNumber avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MediaComponentNumber, avp.getData(), true);
    }

    /**
     * Returns number of FlowNumber instances.
     */
    public int countFlowNumber() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.FlowNumber);
    }

    /**
     * Gets one FlowNumber.
     *
     * @param index - the index of the attribute to return
     */
    public FlowNumber getFlowNumber(int index) throws NoSuchAttributeException {
        return (FlowNumber)_data.getContainer().get(Ro_r10_transatelAttributeName.FlowNumber, index);
    }

    /**
     * Adds one FlowNumber.
     *
     * @param avp - the attribute value
     */
    public void addFlowNumber(FlowNumber avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.FlowNumber, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    MediaComponentNumber:");
            try {
                sb.append(getMediaComponentNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        for (int i = 0; i < countFlowNumber(); ++i) {
            sb.append("    FlowNumber:");
            try {
                sb.append(getFlowNumber(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
