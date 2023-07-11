package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class MDTConfiguration extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MDTConfiguration.
     */
    public MDTConfiguration() {}

    MDTConfiguration(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the JobType.
     */
    public JobType getJobType() throws NoSuchAttributeException {
        return (JobType)_data.getContainer().get(S6a_r10AttributeName.JobType, 0);
    }

    /**
     * Sets the JobType.
     *
     * @param avp - the attribute value
     */
    public void setJobType(JobType avp) {
        _data.getContainer().add(S6a_r10AttributeName.JobType, avp.getData(), true);
    }

    /**
     * Tests whether there is any AreaScope.
     */
    public boolean containsAreaScope() {
        return _data.getContainer().contains(S6a_r10AttributeName.AreaScope);
    }

    /**
     * Gets the AreaScope.
     */
    public AreaScope getAreaScope() throws NoSuchAttributeException {
        return (AreaScope)_data.getContainer().get(S6a_r10AttributeName.AreaScope, 0);
    }

    /**
     * Sets the AreaScope.
     *
     * @param avp - the attribute value
     */
    public void setAreaScope(AreaScope avp) {
        _data.getContainer().add(S6a_r10AttributeName.AreaScope, avp.getData(), true);
    }

    /**
     * Tests whether there is any ListOfMeasurements.
     */
    public boolean containsListOfMeasurements() {
        return _data.getContainer().contains(S6a_r10AttributeName.ListOfMeasurements);
    }

    /**
     * Gets the ListOfMeasurements.
     */
    public ListOfMeasurements getListOfMeasurements() throws NoSuchAttributeException {
        return (ListOfMeasurements)_data.getContainer().get(S6a_r10AttributeName.ListOfMeasurements, 0);
    }

    /**
     * Sets the ListOfMeasurements.
     *
     * @param avp - the attribute value
     */
    public void setListOfMeasurements(ListOfMeasurements avp) {
        _data.getContainer().add(S6a_r10AttributeName.ListOfMeasurements, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReportingTrigger.
     */
    public boolean containsReportingTrigger() {
        return _data.getContainer().contains(S6a_r10AttributeName.ReportingTrigger);
    }

    /**
     * Gets the ReportingTrigger.
     */
    public ReportingTrigger getReportingTrigger() throws NoSuchAttributeException {
        return (ReportingTrigger)_data.getContainer().get(S6a_r10AttributeName.ReportingTrigger, 0);
    }

    /**
     * Sets the ReportingTrigger.
     *
     * @param avp - the attribute value
     */
    public void setReportingTrigger(ReportingTrigger avp) {
        _data.getContainer().add(S6a_r10AttributeName.ReportingTrigger, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReportInterval.
     */
    public boolean containsReportInterval() {
        return _data.getContainer().contains(S6a_r10AttributeName.ReportInterval);
    }

    /**
     * Gets the ReportInterval.
     */
    public ReportInterval getReportInterval() throws NoSuchAttributeException {
        return (ReportInterval)_data.getContainer().get(S6a_r10AttributeName.ReportInterval, 0);
    }

    /**
     * Sets the ReportInterval.
     *
     * @param avp - the attribute value
     */
    public void setReportInterval(ReportInterval avp) {
        _data.getContainer().add(S6a_r10AttributeName.ReportInterval, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReportAmount.
     */
    public boolean containsReportAmount() {
        return _data.getContainer().contains(S6a_r10AttributeName.ReportAmount);
    }

    /**
     * Gets the ReportAmount.
     */
    public ReportAmount getReportAmount() throws NoSuchAttributeException {
        return (ReportAmount)_data.getContainer().get(S6a_r10AttributeName.ReportAmount, 0);
    }

    /**
     * Sets the ReportAmount.
     *
     * @param avp - the attribute value
     */
    public void setReportAmount(ReportAmount avp) {
        _data.getContainer().add(S6a_r10AttributeName.ReportAmount, avp.getData(), true);
    }

    /**
     * Tests whether there is any EventThresholdRSRP.
     */
    public boolean containsEventThresholdRSRP() {
        return _data.getContainer().contains(S6a_r10AttributeName.EventThresholdRSRP);
    }

    /**
     * Gets the EventThresholdRSRP.
     */
    public EventThresholdRSRP getEventThresholdRSRP() throws NoSuchAttributeException {
        return (EventThresholdRSRP)_data.getContainer().get(S6a_r10AttributeName.EventThresholdRSRP, 0);
    }

    /**
     * Sets the EventThresholdRSRP.
     *
     * @param avp - the attribute value
     */
    public void setEventThresholdRSRP(EventThresholdRSRP avp) {
        _data.getContainer().add(S6a_r10AttributeName.EventThresholdRSRP, avp.getData(), true);
    }

    /**
     * Tests whether there is any EventThresholdRSRQ.
     */
    public boolean containsEventThresholdRSRQ() {
        return _data.getContainer().contains(S6a_r10AttributeName.EventThresholdRSRQ);
    }

    /**
     * Gets the EventThresholdRSRQ.
     */
    public EventThresholdRSRQ getEventThresholdRSRQ() throws NoSuchAttributeException {
        return (EventThresholdRSRQ)_data.getContainer().get(S6a_r10AttributeName.EventThresholdRSRQ, 0);
    }

    /**
     * Sets the EventThresholdRSRQ.
     *
     * @param avp - the attribute value
     */
    public void setEventThresholdRSRQ(EventThresholdRSRQ avp) {
        _data.getContainer().add(S6a_r10AttributeName.EventThresholdRSRQ, avp.getData(), true);
    }

    /**
     * Tests whether there is any LoggingInterval.
     */
    public boolean containsLoggingInterval() {
        return _data.getContainer().contains(S6a_r10AttributeName.LoggingInterval);
    }

    /**
     * Gets the LoggingInterval.
     */
    public LoggingInterval getLoggingInterval() throws NoSuchAttributeException {
        return (LoggingInterval)_data.getContainer().get(S6a_r10AttributeName.LoggingInterval, 0);
    }

    /**
     * Sets the LoggingInterval.
     *
     * @param avp - the attribute value
     */
    public void setLoggingInterval(LoggingInterval avp) {
        _data.getContainer().add(S6a_r10AttributeName.LoggingInterval, avp.getData(), true);
    }

    /**
     * Tests whether there is any LoggingDuration.
     */
    public boolean containsLoggingDuration() {
        return _data.getContainer().contains(S6a_r10AttributeName.LoggingDuration);
    }

    /**
     * Gets the LoggingDuration.
     */
    public LoggingDuration getLoggingDuration() throws NoSuchAttributeException {
        return (LoggingDuration)_data.getContainer().get(S6a_r10AttributeName.LoggingDuration, 0);
    }

    /**
     * Sets the LoggingDuration.
     *
     * @param avp - the attribute value
     */
    public void setLoggingDuration(LoggingDuration avp) {
        _data.getContainer().add(S6a_r10AttributeName.LoggingDuration, avp.getData(), true);
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
        sb.append("    JobType:");
            try {
                sb.append(getJobType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsAreaScope()) {
            sb.append("    AreaScope:");
            try {
                sb.append(getAreaScope()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsListOfMeasurements()) {
            sb.append("    ListOfMeasurements:");
            try {
                sb.append(getListOfMeasurements()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReportingTrigger()) {
            sb.append("    ReportingTrigger:");
            try {
                sb.append(getReportingTrigger()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReportInterval()) {
            sb.append("    ReportInterval:");
            try {
                sb.append(getReportInterval()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReportAmount()) {
            sb.append("    ReportAmount:");
            try {
                sb.append(getReportAmount()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEventThresholdRSRP()) {
            sb.append("    EventThresholdRSRP:");
            try {
                sb.append(getEventThresholdRSRP()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEventThresholdRSRQ()) {
            sb.append("    EventThresholdRSRQ:");
            try {
                sb.append(getEventThresholdRSRQ()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoggingInterval()) {
            sb.append("    LoggingInterval:");
            try {
                sb.append(getLoggingInterval()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLoggingDuration()) {
            sb.append("    LoggingDuration:");
            try {
                sb.append(getLoggingDuration()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
