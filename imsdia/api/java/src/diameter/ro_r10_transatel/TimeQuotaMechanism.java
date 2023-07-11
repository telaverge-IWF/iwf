package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Time-Quota-Mechanism AVP (AVP code 1270) is of type Grouped.
 */
public class TimeQuotaMechanism extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TimeQuotaMechanism.
     */
    public TimeQuotaMechanism() {}

    TimeQuotaMechanism(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the TimeQuotaType.
     */
    public TimeQuotaType getTimeQuotaType() throws NoSuchAttributeException {
        return (TimeQuotaType)_data.getContainer().get(Ro_r10_transatelAttributeName.TimeQuotaType, 0);
    }

    /**
     * Sets the TimeQuotaType.
     *
     * @param avp - the attribute value
     */
    public void setTimeQuotaType(TimeQuotaType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TimeQuotaType, avp.getData(), true);
    }

    /**
     * Gets the BaseTimeInterval.
     */
    public BaseTimeInterval getBaseTimeInterval() throws NoSuchAttributeException {
        return (BaseTimeInterval)_data.getContainer().get(Ro_r10_transatelAttributeName.BaseTimeInterval, 0);
    }

    /**
     * Sets the BaseTimeInterval.
     *
     * @param avp - the attribute value
     */
    public void setBaseTimeInterval(BaseTimeInterval avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.BaseTimeInterval, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    TimeQuotaType:");
            try {
                sb.append(getTimeQuotaType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    BaseTimeInterval:");
            try {
                sb.append(getBaseTimeInterval()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        return sb.append('}').toString();
    }
}
