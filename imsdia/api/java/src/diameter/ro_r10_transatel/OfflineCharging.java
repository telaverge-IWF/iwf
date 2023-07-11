package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Offline-Charging AVP (AVP code 1278) is a grouped AVP, which is used to set 
 * the parameters required to control offline charging. 
 */
public class OfflineCharging extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new OfflineCharging.
     */
    public OfflineCharging() {}

    OfflineCharging(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any QuotaConsumptionTime.
     */
    public boolean containsQuotaConsumptionTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.QuotaConsumptionTime);
    }

    /**
     * Gets the QuotaConsumptionTime.
     */
    public QuotaConsumptionTime getQuotaConsumptionTime() throws NoSuchAttributeException {
        return (QuotaConsumptionTime)_data.getContainer().get(Ro_r10_transatelAttributeName.QuotaConsumptionTime, 0);
    }

    /**
     * Sets the QuotaConsumptionTime.
     *
     * @param avp - the attribute value
     */
    public void setQuotaConsumptionTime(QuotaConsumptionTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.QuotaConsumptionTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any TimeQuotaMechanism.
     */
    public boolean containsTimeQuotaMechanism() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TimeQuotaMechanism);
    }

    /**
     * Gets the TimeQuotaMechanism.
     */
    public TimeQuotaMechanism getTimeQuotaMechanism() throws NoSuchAttributeException {
        return (TimeQuotaMechanism)_data.getContainer().get(Ro_r10_transatelAttributeName.TimeQuotaMechanism, 0);
    }

    /**
     * Sets the TimeQuotaMechanism.
     *
     * @param avp - the attribute value
     */
    public void setTimeQuotaMechanism(TimeQuotaMechanism avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TimeQuotaMechanism, avp.getData(), true);
    }

    /**
     * Tests whether there is any EnvelopeReporting.
     */
    public boolean containsEnvelopeReporting() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.EnvelopeReporting);
    }

    /**
     * Gets the EnvelopeReporting.
     */
    public EnvelopeReporting getEnvelopeReporting() throws NoSuchAttributeException {
        return (EnvelopeReporting)_data.getContainer().get(Ro_r10_transatelAttributeName.EnvelopeReporting, 0);
    }

    /**
     * Sets the EnvelopeReporting.
     *
     * @param avp - the attribute value
     */
    public void setEnvelopeReporting(EnvelopeReporting avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.EnvelopeReporting, avp.getData(), true);
    }

    /**
     * Returns number of MultipleServicesCreditControl instances.
     */
    public int countMultipleServicesCreditControl() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.MultipleServicesCreditControl);
    }

    /**
     * Gets one MultipleServicesCreditControl.
     *
     * @param index - the index of the attribute to return
     */
    public MultipleServicesCreditControl getMultipleServicesCreditControl(int index) throws NoSuchAttributeException {
        return (MultipleServicesCreditControl)_data.getContainer().get(Ro_r10_transatelAttributeName.MultipleServicesCreditControl, index);
    }

    /**
     * Adds one MultipleServicesCreditControl.
     *
     * @param avp - the attribute value
     */
    public void addMultipleServicesCreditControl(MultipleServicesCreditControl avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MultipleServicesCreditControl, avp.getData(), false);
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
        if (containsQuotaConsumptionTime()) {
            sb.append("    QuotaConsumptionTime:");
            try {
                sb.append(getQuotaConsumptionTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTimeQuotaMechanism()) {
            sb.append("    TimeQuotaMechanism:");
            try {
                sb.append(getTimeQuotaMechanism()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEnvelopeReporting()) {
            sb.append("    EnvelopeReporting:");
            try {
                sb.append(getEnvelopeReporting()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countMultipleServicesCreditControl(); ++i) {
            sb.append("    MultipleServicesCreditControl:");
            try {
                sb.append(getMultipleServicesCreditControl(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
