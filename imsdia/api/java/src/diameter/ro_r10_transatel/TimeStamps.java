package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Time-Stamps AVP is of type Grouped and holds the time of the initial SIP request and the time
 * of response to the initial SIP request.
 */
public class TimeStamps extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TimeStamps.
     */
    public TimeStamps() {}

    TimeStamps(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SIPRequestTimestamp.
     */
    public boolean containsSIPRequestTimestamp() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SIPRequestTimestamp);
    }

    /**
     * Gets the SIPRequestTimestamp.
     */
    public SIPRequestTimestamp getSIPRequestTimestamp() throws NoSuchAttributeException {
        return (SIPRequestTimestamp)_data.getContainer().get(Ro_r10_transatelAttributeName.SIPRequestTimestamp, 0);
    }

    /**
     * Sets the SIPRequestTimestamp.
     *
     * @param avp - the attribute value
     */
    public void setSIPRequestTimestamp(SIPRequestTimestamp avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SIPRequestTimestamp, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPResponseTimestamp.
     */
    public boolean containsSIPResponseTimestamp() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SIPResponseTimestamp);
    }

    /**
     * Gets the SIPResponseTimestamp.
     */
    public SIPResponseTimestamp getSIPResponseTimestamp() throws NoSuchAttributeException {
        return (SIPResponseTimestamp)_data.getContainer().get(Ro_r10_transatelAttributeName.SIPResponseTimestamp, 0);
    }

    /**
     * Sets the SIPResponseTimestamp.
     *
     * @param avp - the attribute value
     */
    public void setSIPResponseTimestamp(SIPResponseTimestamp avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SIPResponseTimestamp, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPRequestTimestampFraction.
     */
    public boolean containsSIPRequestTimestampFraction() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SIPRequestTimestampFraction);
    }

    /**
     * Gets the SIPRequestTimestampFraction.
     */
    public SIPRequestTimestampFraction getSIPRequestTimestampFraction() throws NoSuchAttributeException {
        return (SIPRequestTimestampFraction)_data.getContainer().get(Ro_r10_transatelAttributeName.SIPRequestTimestampFraction, 0);
    }

    /**
     * Sets the SIPRequestTimestampFraction.
     *
     * @param avp - the attribute value
     */
    public void setSIPRequestTimestampFraction(SIPRequestTimestampFraction avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SIPRequestTimestampFraction, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPResponseTimestampFraction.
     */
    public boolean containsSIPResponseTimestampFraction() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SIPResponseTimestampFraction);
    }

    /**
     * Gets the SIPResponseTimestampFraction.
     */
    public SIPResponseTimestampFraction getSIPResponseTimestampFraction() throws NoSuchAttributeException {
        return (SIPResponseTimestampFraction)_data.getContainer().get(Ro_r10_transatelAttributeName.SIPResponseTimestampFraction, 0);
    }

    /**
     * Sets the SIPResponseTimestampFraction.
     *
     * @param avp - the attribute value
     */
    public void setSIPResponseTimestampFraction(SIPResponseTimestampFraction avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SIPResponseTimestampFraction, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsSIPRequestTimestamp()) {
            sb.append("    SIPRequestTimestamp:");
            try {
                sb.append(getSIPRequestTimestamp()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPResponseTimestamp()) {
            sb.append("    SIPResponseTimestamp:");
            try {
                sb.append(getSIPResponseTimestamp()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPRequestTimestampFraction()) {
            sb.append("    SIPRequestTimestampFraction:");
            try {
                sb.append(getSIPRequestTimestampFraction()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPResponseTimestampFraction()) {
            sb.append("    SIPResponseTimestampFraction:");
            try {
                sb.append(getSIPResponseTimestampFraction()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
