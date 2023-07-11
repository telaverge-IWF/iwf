package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Deregistration-Reason AVP is of type Grouped, and indicates the reason for a de-registration operation.
 */
public class DeregistrationReason extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new DeregistrationReason.
     */
    public DeregistrationReason() {}

    DeregistrationReason(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ReasonCode.
     */
    public ReasonCode getReasonCode() throws NoSuchAttributeException {
        return (ReasonCode)_data.getContainer().get(Cxdx_v12AttributeName.ReasonCode, 0);
    }

    /**
     * Sets the ReasonCode.
     *
     * @param avp - the attribute value
     */
    public void setReasonCode(ReasonCode avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.ReasonCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReasonInfo.
     */
    public boolean containsReasonInfo() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.ReasonInfo);
    }

    /**
     * Gets the ReasonInfo.
     */
    public ReasonInfo getReasonInfo() throws NoSuchAttributeException {
        return (ReasonInfo)_data.getContainer().get(Cxdx_v12AttributeName.ReasonInfo, 0);
    }

    /**
     * Sets the ReasonInfo.
     *
     * @param avp - the attribute value
     */
    public void setReasonInfo(ReasonInfo avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.ReasonInfo, avp.getData(), true);
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
        sb.append("    ReasonCode:");
            try {
                sb.append(getReasonCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsReasonInfo()) {
            sb.append("    ReasonInfo:");
            try {
                sb.append(getReasonInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
