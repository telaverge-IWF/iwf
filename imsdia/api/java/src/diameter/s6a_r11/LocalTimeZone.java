package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class LocalTimeZone extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LocalTimeZone.
     */
    public LocalTimeZone() {}

    LocalTimeZone(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the S6A3GPPMSTimeZone.
     */
    public S6A3GPPMSTimeZone getS6A3GPPMSTimeZone() throws NoSuchAttributeException {
        return (S6A3GPPMSTimeZone)_data.getContainer().get(S6a_r11AttributeName.S6A3GPPMSTimeZone, 0);
    }

    /**
     * Sets the S6A3GPPMSTimeZone.
     *
     * @param avp - the attribute value
     */
    public void setS6A3GPPMSTimeZone(S6A3GPPMSTimeZone avp) {
        _data.getContainer().add(S6a_r11AttributeName.S6A3GPPMSTimeZone, avp.getData(), true);
    }

    /**
     * Gets the DaylightSavingTime.
     */
    public DaylightSavingTime getDaylightSavingTime() throws NoSuchAttributeException {
        return (DaylightSavingTime)_data.getContainer().get(S6a_r11AttributeName.DaylightSavingTime, 0);
    }

    /**
     * Sets the DaylightSavingTime.
     *
     * @param avp - the attribute value
     */
    public void setDaylightSavingTime(DaylightSavingTime avp) {
        _data.getContainer().add(S6a_r11AttributeName.DaylightSavingTime, avp.getData(), true);
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
        sb.append("    S6A3GPPMSTimeZone:");
            try {
                sb.append(getS6A3GPPMSTimeZone()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    DaylightSavingTime:");
            try {
                sb.append(getDaylightSavingTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
