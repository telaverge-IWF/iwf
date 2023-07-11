package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Used-Service-Unit AVP is of type Grouped (AVP Code 446) and contains the amount of used 
 * units measured from the point when the service became active or, if interim interrogations 
 * are used during the session, from the point when the previous measurement ended.
 */
public class UsedServiceUnit extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new UsedServiceUnit.
     */
    public UsedServiceUnit() {}

    UsedServiceUnit(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any ReportingReason.
     */
    public boolean containsReportingReason() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ReportingReason);
    }

    /**
     * Gets the ReportingReason.
     */
    public ReportingReason getReportingReason() throws NoSuchAttributeException {
        return (ReportingReason)_data.getContainer().get(Ro_r10_transatelAttributeName.ReportingReason, 0);
    }

    /**
     * Sets the ReportingReason.
     *
     * @param avp - the attribute value
     */
    public void setReportingReason(ReportingReason avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ReportingReason, avp.getData(), true);
    }

    /**
     * Tests whether there is any TariffChangeUsage.
     */
    public boolean containsTariffChangeUsage() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TariffChangeUsage);
    }

    /**
     * Gets the TariffChangeUsage.
     */
    public TariffChangeUsage getTariffChangeUsage() throws NoSuchAttributeException {
        return (TariffChangeUsage)_data.getContainer().get(Ro_r10_transatelAttributeName.TariffChangeUsage, 0);
    }

    /**
     * Sets the TariffChangeUsage.
     *
     * @param avp - the attribute value
     */
    public void setTariffChangeUsage(TariffChangeUsage avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TariffChangeUsage, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCTime.
     */
    public boolean containsCCTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCTime);
    }

    /**
     * Gets the CCTime.
     */
    public CCTime getCCTime() throws NoSuchAttributeException {
        return (CCTime)_data.getContainer().get(Ro_r10_transatelAttributeName.CCTime, 0);
    }

    /**
     * Sets the CCTime.
     *
     * @param avp - the attribute value
     */
    public void setCCTime(CCTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCTotalOctets.
     */
    public boolean containsCCTotalOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCTotalOctets);
    }

    /**
     * Gets the CCTotalOctets.
     */
    public CCTotalOctets getCCTotalOctets() throws NoSuchAttributeException {
        return (CCTotalOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.CCTotalOctets, 0);
    }

    /**
     * Sets the CCTotalOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCTotalOctets(CCTotalOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCTotalOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCInputOctets.
     */
    public boolean containsCCInputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCInputOctets);
    }

    /**
     * Gets the CCInputOctets.
     */
    public CCInputOctets getCCInputOctets() throws NoSuchAttributeException {
        return (CCInputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.CCInputOctets, 0);
    }

    /**
     * Sets the CCInputOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCInputOctets(CCInputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCInputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCOutputOctets.
     */
    public boolean containsCCOutputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCOutputOctets);
    }

    /**
     * Gets the CCOutputOctets.
     */
    public CCOutputOctets getCCOutputOctets() throws NoSuchAttributeException {
        return (CCOutputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.CCOutputOctets, 0);
    }

    /**
     * Sets the CCOutputOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCOutputOctets(CCOutputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCOutputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCServiceSpecificUnits.
     */
    public boolean containsCCServiceSpecificUnits() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCServiceSpecificUnits);
    }

    /**
     * Gets the CCServiceSpecificUnits.
     */
    public CCServiceSpecificUnits getCCServiceSpecificUnits() throws NoSuchAttributeException {
        return (CCServiceSpecificUnits)_data.getContainer().get(Ro_r10_transatelAttributeName.CCServiceSpecificUnits, 0);
    }

    /**
     * Sets the CCServiceSpecificUnits.
     *
     * @param avp - the attribute value
     */
    public void setCCServiceSpecificUnits(CCServiceSpecificUnits avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCServiceSpecificUnits, avp.getData(), true);
    }

    /**
     * Returns number of EventChargingTimeStamp instances.
     */
    public int countEventChargingTimeStamp() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.EventChargingTimeStamp);
    }

    /**
     * Gets one EventChargingTimeStamp.
     *
     * @param index - the index of the attribute to return
     */
    public EventChargingTimeStamp getEventChargingTimeStamp(int index) throws NoSuchAttributeException {
        return (EventChargingTimeStamp)_data.getContainer().get(Ro_r10_transatelAttributeName.EventChargingTimeStamp, index);
    }

    /**
     * Adds one EventChargingTimeStamp.
     *
     * @param avp - the attribute value
     */
    public void addEventChargingTimeStamp(EventChargingTimeStamp avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.EventChargingTimeStamp, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsReportingReason()) {
            sb.append("    ReportingReason:");
            try {
                sb.append(getReportingReason()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTariffChangeUsage()) {
            sb.append("    TariffChangeUsage:");
            try {
                sb.append(getTariffChangeUsage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCTime()) {
            sb.append("    CCTime:");
            try {
                sb.append(getCCTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCTotalOctets()) {
            sb.append("    CCTotalOctets:");
            try {
                sb.append(getCCTotalOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCInputOctets()) {
            sb.append("    CCInputOctets:");
            try {
                sb.append(getCCInputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCOutputOctets()) {
            sb.append("    CCOutputOctets:");
            try {
                sb.append(getCCOutputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCServiceSpecificUnits()) {
            sb.append("    CCServiceSpecificUnits:");
            try {
                sb.append(getCCServiceSpecificUnits()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countEventChargingTimeStamp(); ++i) {
            sb.append("    EventChargingTimeStamp:");
            try {
                sb.append(getEventChargingTimeStamp(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
