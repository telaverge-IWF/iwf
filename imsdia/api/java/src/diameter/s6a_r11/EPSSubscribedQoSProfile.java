package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The EPS-Subscribed-QoS-Profile AVP is of type Grouped. It contains the information related 
 * to the user profile relevant for EPS.
 */
public class EPSSubscribedQoSProfile extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new EPSSubscribedQoSProfile.
     */
    public EPSSubscribedQoSProfile() {}

    EPSSubscribedQoSProfile(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the QoSClassIdentifier.
     */
    public QoSClassIdentifier getQoSClassIdentifier() throws NoSuchAttributeException {
        return (QoSClassIdentifier)_data.getContainer().get(S6a_r11AttributeName.QoSClassIdentifier, 0);
    }

    /**
     * Sets the QoSClassIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setQoSClassIdentifier(QoSClassIdentifier avp) {
        _data.getContainer().add(S6a_r11AttributeName.QoSClassIdentifier, avp.getData(), true);
    }

    /**
     * Gets the AllocationRetentionPriority.
     */
    public AllocationRetentionPriority getAllocationRetentionPriority() throws NoSuchAttributeException {
        return (AllocationRetentionPriority)_data.getContainer().get(S6a_r11AttributeName.AllocationRetentionPriority, 0);
    }

    /**
     * Sets the AllocationRetentionPriority.
     *
     * @param avp - the attribute value
     */
    public void setAllocationRetentionPriority(AllocationRetentionPriority avp) {
        _data.getContainer().add(S6a_r11AttributeName.AllocationRetentionPriority, avp.getData(), true);
    }

    /**
     * Returns number of extra AVP instances.
     */
    public int countExtra() {
        return _data.getContainer().count(AttributeName.AVP);
    }

    /**
     * Returns number of extra AVP instances that match the given attribute name.
     *
     * @param name - the attribute to count
     */
    public int countExtra(AttributeName name) {
        return _data.getContainer().countExtra(name);
    }

    /**
     * Gets an extra AVP that matches the given attribute name.
     *
     * @param name - the attribute to return
     * @param index - the index of the attribute to return
     */
    public AVP getExtra(AttributeName name, int index) throws NoSuchAttributeException {
        return _data.getContainer().getExtra(name, index);
    }

    /**
     * Adds one extra AVP.
     *
     * @param avp - the attribute value
     */
    public void addExtra(AVP avp) {
        _data.getContainer().add(AttributeName.AVP, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    QoSClassIdentifier:");
            try {
                sb.append(getQoSClassIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AllocationRetentionPriority:");
            try {
                sb.append(getAllocationRetentionPriority()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
