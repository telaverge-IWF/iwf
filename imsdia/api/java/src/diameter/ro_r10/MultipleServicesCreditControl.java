package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Multiple-Services-Credit-Control AVP is of type Grouped and contains the AVPs related 
 * to the independent credit-control of multiple services feature.  Note that each instance of
 * this AVP carries units related to one or more services or related to a single rating group.
 */
public class MultipleServicesCreditControl extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MultipleServicesCreditControl.
     */
    public MultipleServicesCreditControl() {}

    MultipleServicesCreditControl(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any GrantedServiceUnit.
     */
    public boolean containsGrantedServiceUnit() {
        return _data.getContainer().contains(Ro_r10AttributeName.GrantedServiceUnit);
    }

    /**
     * Gets the GrantedServiceUnit.
     */
    public GrantedServiceUnit getGrantedServiceUnit() throws NoSuchAttributeException {
        return (GrantedServiceUnit)_data.getContainer().get(Ro_r10AttributeName.GrantedServiceUnit, 0);
    }

    /**
     * Sets the GrantedServiceUnit.
     *
     * @param avp - the attribute value
     */
    public void setGrantedServiceUnit(GrantedServiceUnit avp) {
        _data.getContainer().add(Ro_r10AttributeName.GrantedServiceUnit, avp.getData(), true);
    }

    /**
     * Tests whether there is any RequestedServiceUnit.
     */
    public boolean containsRequestedServiceUnit() {
        return _data.getContainer().contains(Ro_r10AttributeName.RequestedServiceUnit);
    }

    /**
     * Gets the RequestedServiceUnit.
     */
    public RequestedServiceUnit getRequestedServiceUnit() throws NoSuchAttributeException {
        return (RequestedServiceUnit)_data.getContainer().get(Ro_r10AttributeName.RequestedServiceUnit, 0);
    }

    /**
     * Sets the RequestedServiceUnit.
     *
     * @param avp - the attribute value
     */
    public void setRequestedServiceUnit(RequestedServiceUnit avp) {
        _data.getContainer().add(Ro_r10AttributeName.RequestedServiceUnit, avp.getData(), true);
    }

    /**
     * Returns number of UsedServiceUnit instances.
     */
    public int countUsedServiceUnit() {
        return _data.getContainer().count(Ro_r10AttributeName.UsedServiceUnit);
    }

    /**
     * Gets one UsedServiceUnit.
     *
     * @param index - the index of the attribute to return
     */
    public UsedServiceUnit getUsedServiceUnit(int index) throws NoSuchAttributeException {
        return (UsedServiceUnit)_data.getContainer().get(Ro_r10AttributeName.UsedServiceUnit, index);
    }

    /**
     * Adds one UsedServiceUnit.
     *
     * @param avp - the attribute value
     */
    public void addUsedServiceUnit(UsedServiceUnit avp) {
        _data.getContainer().add(Ro_r10AttributeName.UsedServiceUnit, avp.getData(), false);
    }

    /**
     * Returns number of ServiceIdentifier instances.
     */
    public int countServiceIdentifier() {
        return _data.getContainer().count(Ro_r10AttributeName.ServiceIdentifier);
    }

    /**
     * Gets one ServiceIdentifier.
     *
     * @param index - the index of the attribute to return
     */
    public ServiceIdentifier getServiceIdentifier(int index) throws NoSuchAttributeException {
        return (ServiceIdentifier)_data.getContainer().get(Ro_r10AttributeName.ServiceIdentifier, index);
    }

    /**
     * Adds one ServiceIdentifier.
     *
     * @param avp - the attribute value
     */
    public void addServiceIdentifier(ServiceIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceIdentifier, avp.getData(), false);
    }

    /**
     * Tests whether there is any RatingGroup.
     */
    public boolean containsRatingGroup() {
        return _data.getContainer().contains(Ro_r10AttributeName.RatingGroup);
    }

    /**
     * Gets the RatingGroup.
     */
    public RatingGroup getRatingGroup() throws NoSuchAttributeException {
        return (RatingGroup)_data.getContainer().get(Ro_r10AttributeName.RatingGroup, 0);
    }

    /**
     * Sets the RatingGroup.
     *
     * @param avp - the attribute value
     */
    public void setRatingGroup(RatingGroup avp) {
        _data.getContainer().add(Ro_r10AttributeName.RatingGroup, avp.getData(), true);
    }

    /**
     * Returns number of GSUPoolReference instances.
     */
    public int countGSUPoolReference() {
        return _data.getContainer().count(Ro_r10AttributeName.GSUPoolReference);
    }

    /**
     * Gets one GSUPoolReference.
     *
     * @param index - the index of the attribute to return
     */
    public GSUPoolReference getGSUPoolReference(int index) throws NoSuchAttributeException {
        return (GSUPoolReference)_data.getContainer().get(Ro_r10AttributeName.GSUPoolReference, index);
    }

    /**
     * Adds one GSUPoolReference.
     *
     * @param avp - the attribute value
     */
    public void addGSUPoolReference(GSUPoolReference avp) {
        _data.getContainer().add(Ro_r10AttributeName.GSUPoolReference, avp.getData(), false);
    }

    /**
     * Tests whether there is any ValidityTime.
     */
    public boolean containsValidityTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.ValidityTime);
    }

    /**
     * Gets the ValidityTime.
     */
    public ValidityTime getValidityTime() throws NoSuchAttributeException {
        return (ValidityTime)_data.getContainer().get(Ro_r10AttributeName.ValidityTime, 0);
    }

    /**
     * Sets the ValidityTime.
     *
     * @param avp - the attribute value
     */
    public void setValidityTime(ValidityTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.ValidityTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any ResultCode.
     */
    public boolean containsResultCode() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.ResultCode);
    }

    /**
     * Gets the ResultCode.
     */
    public diameter.base.ResultCode getResultCode() throws NoSuchAttributeException {
        return (diameter.base.ResultCode)_data.getContainer().get(diameter.base.BaseAttributeName.ResultCode, 0);
    }

    /**
     * Sets the ResultCode.
     *
     * @param avp - the attribute value
     */
    public void setResultCode(diameter.base.ResultCode avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ResultCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any FinalUnitIndication.
     */
    public boolean containsFinalUnitIndication() {
        return _data.getContainer().contains(Ro_r10AttributeName.FinalUnitIndication);
    }

    /**
     * Gets the FinalUnitIndication.
     */
    public FinalUnitIndication getFinalUnitIndication() throws NoSuchAttributeException {
        return (FinalUnitIndication)_data.getContainer().get(Ro_r10AttributeName.FinalUnitIndication, 0);
    }

    /**
     * Sets the FinalUnitIndication.
     *
     * @param avp - the attribute value
     */
    public void setFinalUnitIndication(FinalUnitIndication avp) {
        _data.getContainer().add(Ro_r10AttributeName.FinalUnitIndication, avp.getData(), true);
    }

    /**
     * Tests whether there is any TimeQuotaThreshold.
     */
    public boolean containsTimeQuotaThreshold() {
        return _data.getContainer().contains(Ro_r10AttributeName.TimeQuotaThreshold);
    }

    /**
     * Gets the TimeQuotaThreshold.
     */
    public TimeQuotaThreshold getTimeQuotaThreshold() throws NoSuchAttributeException {
        return (TimeQuotaThreshold)_data.getContainer().get(Ro_r10AttributeName.TimeQuotaThreshold, 0);
    }

    /**
     * Sets the TimeQuotaThreshold.
     *
     * @param avp - the attribute value
     */
    public void setTimeQuotaThreshold(TimeQuotaThreshold avp) {
        _data.getContainer().add(Ro_r10AttributeName.TimeQuotaThreshold, avp.getData(), true);
    }

    /**
     * Tests whether there is any VolumeQuotaThreshold.
     */
    public boolean containsVolumeQuotaThreshold() {
        return _data.getContainer().contains(Ro_r10AttributeName.VolumeQuotaThreshold);
    }

    /**
     * Gets the VolumeQuotaThreshold.
     */
    public VolumeQuotaThreshold getVolumeQuotaThreshold() throws NoSuchAttributeException {
        return (VolumeQuotaThreshold)_data.getContainer().get(Ro_r10AttributeName.VolumeQuotaThreshold, 0);
    }

    /**
     * Sets the VolumeQuotaThreshold.
     *
     * @param avp - the attribute value
     */
    public void setVolumeQuotaThreshold(VolumeQuotaThreshold avp) {
        _data.getContainer().add(Ro_r10AttributeName.VolumeQuotaThreshold, avp.getData(), true);
    }

    /**
     * Tests whether there is any UnitQuotaThreshold.
     */
    public boolean containsUnitQuotaThreshold() {
        return _data.getContainer().contains(Ro_r10AttributeName.UnitQuotaThreshold);
    }

    /**
     * Gets the UnitQuotaThreshold.
     */
    public UnitQuotaThreshold getUnitQuotaThreshold() throws NoSuchAttributeException {
        return (UnitQuotaThreshold)_data.getContainer().get(Ro_r10AttributeName.UnitQuotaThreshold, 0);
    }

    /**
     * Sets the UnitQuotaThreshold.
     *
     * @param avp - the attribute value
     */
    public void setUnitQuotaThreshold(UnitQuotaThreshold avp) {
        _data.getContainer().add(Ro_r10AttributeName.UnitQuotaThreshold, avp.getData(), true);
    }

    /**
     * Tests whether there is any QuotaHoldingTime.
     */
    public boolean containsQuotaHoldingTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.QuotaHoldingTime);
    }

    /**
     * Gets the QuotaHoldingTime.
     */
    public QuotaHoldingTime getQuotaHoldingTime() throws NoSuchAttributeException {
        return (QuotaHoldingTime)_data.getContainer().get(Ro_r10AttributeName.QuotaHoldingTime, 0);
    }

    /**
     * Sets the QuotaHoldingTime.
     *
     * @param avp - the attribute value
     */
    public void setQuotaHoldingTime(QuotaHoldingTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.QuotaHoldingTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any QuotaConsumptionTime.
     */
    public boolean containsQuotaConsumptionTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.QuotaConsumptionTime);
    }

    /**
     * Gets the QuotaConsumptionTime.
     */
    public QuotaConsumptionTime getQuotaConsumptionTime() throws NoSuchAttributeException {
        return (QuotaConsumptionTime)_data.getContainer().get(Ro_r10AttributeName.QuotaConsumptionTime, 0);
    }

    /**
     * Sets the QuotaConsumptionTime.
     *
     * @param avp - the attribute value
     */
    public void setQuotaConsumptionTime(QuotaConsumptionTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.QuotaConsumptionTime, avp.getData(), true);
    }

    /**
     * Returns number of ReportingReason instances.
     */
    public int countReportingReason() {
        return _data.getContainer().count(Ro_r10AttributeName.ReportingReason);
    }

    /**
     * Gets one ReportingReason.
     *
     * @param index - the index of the attribute to return
     */
    public ReportingReason getReportingReason(int index) throws NoSuchAttributeException {
        return (ReportingReason)_data.getContainer().get(Ro_r10AttributeName.ReportingReason, index);
    }

    /**
     * Adds one ReportingReason.
     *
     * @param avp - the attribute value
     */
    public void addReportingReason(ReportingReason avp) {
        _data.getContainer().add(Ro_r10AttributeName.ReportingReason, avp.getData(), false);
    }

    /**
     * Tests whether there is any Trigger.
     */
    public boolean containsTrigger() {
        return _data.getContainer().contains(Ro_r10AttributeName.Trigger);
    }

    /**
     * Gets the Trigger.
     */
    public Trigger getTrigger() throws NoSuchAttributeException {
        return (Trigger)_data.getContainer().get(Ro_r10AttributeName.Trigger, 0);
    }

    /**
     * Sets the Trigger.
     *
     * @param avp - the attribute value
     */
    public void setTrigger(Trigger avp) {
        _data.getContainer().add(Ro_r10AttributeName.Trigger, avp.getData(), true);
    }

    /**
     * Tests whether there is any PSFurnishChargingInformation.
     */
    public boolean containsPSFurnishChargingInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.PSFurnishChargingInformation);
    }

    /**
     * Gets the PSFurnishChargingInformation.
     */
    public PSFurnishChargingInformation getPSFurnishChargingInformation() throws NoSuchAttributeException {
        return (PSFurnishChargingInformation)_data.getContainer().get(Ro_r10AttributeName.PSFurnishChargingInformation, 0);
    }

    /**
     * Sets the PSFurnishChargingInformation.
     *
     * @param avp - the attribute value
     */
    public void setPSFurnishChargingInformation(PSFurnishChargingInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.PSFurnishChargingInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any RefundInformation.
     */
    public boolean containsRefundInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.RefundInformation);
    }

    /**
     * Gets the RefundInformation.
     */
    public RefundInformation getRefundInformation() throws NoSuchAttributeException {
        return (RefundInformation)_data.getContainer().get(Ro_r10AttributeName.RefundInformation, 0);
    }

    /**
     * Sets the RefundInformation.
     *
     * @param avp - the attribute value
     */
    public void setRefundInformation(RefundInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.RefundInformation, avp.getData(), true);
    }

    /**
     * Returns number of AFCorrelationInformation instances.
     */
    public int countAFCorrelationInformation() {
        return _data.getContainer().count(Ro_r10AttributeName.AFCorrelationInformation);
    }

    /**
     * Gets one AFCorrelationInformation.
     *
     * @param index - the index of the attribute to return
     */
    public AFCorrelationInformation getAFCorrelationInformation(int index) throws NoSuchAttributeException {
        return (AFCorrelationInformation)_data.getContainer().get(Ro_r10AttributeName.AFCorrelationInformation, index);
    }

    /**
     * Adds one AFCorrelationInformation.
     *
     * @param avp - the attribute value
     */
    public void addAFCorrelationInformation(AFCorrelationInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.AFCorrelationInformation, avp.getData(), false);
    }

    /**
     * Returns number of Envelope instances.
     */
    public int countEnvelope() {
        return _data.getContainer().count(Ro_r10AttributeName.Envelope);
    }

    /**
     * Gets one Envelope.
     *
     * @param index - the index of the attribute to return
     */
    public Envelope getEnvelope(int index) throws NoSuchAttributeException {
        return (Envelope)_data.getContainer().get(Ro_r10AttributeName.Envelope, index);
    }

    /**
     * Adds one Envelope.
     *
     * @param avp - the attribute value
     */
    public void addEnvelope(Envelope avp) {
        _data.getContainer().add(Ro_r10AttributeName.Envelope, avp.getData(), false);
    }

    /**
     * Tests whether there is any EnvelopeReporting.
     */
    public boolean containsEnvelopeReporting() {
        return _data.getContainer().contains(Ro_r10AttributeName.EnvelopeReporting);
    }

    /**
     * Gets the EnvelopeReporting.
     */
    public EnvelopeReporting getEnvelopeReporting() throws NoSuchAttributeException {
        return (EnvelopeReporting)_data.getContainer().get(Ro_r10AttributeName.EnvelopeReporting, 0);
    }

    /**
     * Sets the EnvelopeReporting.
     *
     * @param avp - the attribute value
     */
    public void setEnvelopeReporting(EnvelopeReporting avp) {
        _data.getContainer().add(Ro_r10AttributeName.EnvelopeReporting, avp.getData(), true);
    }

    /**
     * Tests whether there is any TimeQuotaMechanism.
     */
    public boolean containsTimeQuotaMechanism() {
        return _data.getContainer().contains(Ro_r10AttributeName.TimeQuotaMechanism);
    }

    /**
     * Gets the TimeQuotaMechanism.
     */
    public TimeQuotaMechanism getTimeQuotaMechanism() throws NoSuchAttributeException {
        return (TimeQuotaMechanism)_data.getContainer().get(Ro_r10AttributeName.TimeQuotaMechanism, 0);
    }

    /**
     * Sets the TimeQuotaMechanism.
     *
     * @param avp - the attribute value
     */
    public void setTimeQuotaMechanism(TimeQuotaMechanism avp) {
        _data.getContainer().add(Ro_r10AttributeName.TimeQuotaMechanism, avp.getData(), true);
    }

    /**
     * Returns number of ServiceSpecificInfo instances.
     */
    public int countServiceSpecificInfo() {
        return _data.getContainer().count(Ro_r10AttributeName.ServiceSpecificInfo);
    }

    /**
     * Gets one ServiceSpecificInfo.
     *
     * @param index - the index of the attribute to return
     */
    public ServiceSpecificInfo getServiceSpecificInfo(int index) throws NoSuchAttributeException {
        return (ServiceSpecificInfo)_data.getContainer().get(Ro_r10AttributeName.ServiceSpecificInfo, index);
    }

    /**
     * Adds one ServiceSpecificInfo.
     *
     * @param avp - the attribute value
     */
    public void addServiceSpecificInfo(ServiceSpecificInfo avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceSpecificInfo, avp.getData(), false);
    }

    /**
     * Tests whether there is any QoSInformation.
     */
    public boolean containsQoSInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.QoSInformation);
    }

    /**
     * Gets the QoSInformation.
     */
    public QoSInformation getQoSInformation() throws NoSuchAttributeException {
        return (QoSInformation)_data.getContainer().get(Ro_r10AttributeName.QoSInformation, 0);
    }

    /**
     * Sets the QoSInformation.
     *
     * @param avp - the attribute value
     */
    public void setQoSInformation(QoSInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.QoSInformation, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsGrantedServiceUnit()) {
            sb.append("    GrantedServiceUnit:");
            try {
                sb.append(getGrantedServiceUnit()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRequestedServiceUnit()) {
            sb.append("    RequestedServiceUnit:");
            try {
                sb.append(getRequestedServiceUnit()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countUsedServiceUnit(); ++i) {
            sb.append("    UsedServiceUnit:");
            try {
                sb.append(getUsedServiceUnit(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServiceIdentifier(); ++i) {
            sb.append("    ServiceIdentifier:");
            try {
                sb.append(getServiceIdentifier(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRatingGroup()) {
            sb.append("    RatingGroup:");
            try {
                sb.append(getRatingGroup()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countGSUPoolReference(); ++i) {
            sb.append("    GSUPoolReference:");
            try {
                sb.append(getGSUPoolReference(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsValidityTime()) {
            sb.append("    ValidityTime:");
            try {
                sb.append(getValidityTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsResultCode()) {
            sb.append("    ResultCode:");
            try {
                sb.append(getResultCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFinalUnitIndication()) {
            sb.append("    FinalUnitIndication:");
            try {
                sb.append(getFinalUnitIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTimeQuotaThreshold()) {
            sb.append("    TimeQuotaThreshold:");
            try {
                sb.append(getTimeQuotaThreshold()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVolumeQuotaThreshold()) {
            sb.append("    VolumeQuotaThreshold:");
            try {
                sb.append(getVolumeQuotaThreshold()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUnitQuotaThreshold()) {
            sb.append("    UnitQuotaThreshold:");
            try {
                sb.append(getUnitQuotaThreshold()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsQuotaHoldingTime()) {
            sb.append("    QuotaHoldingTime:");
            try {
                sb.append(getQuotaHoldingTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsQuotaConsumptionTime()) {
            sb.append("    QuotaConsumptionTime:");
            try {
                sb.append(getQuotaConsumptionTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countReportingReason(); ++i) {
            sb.append("    ReportingReason:");
            try {
                sb.append(getReportingReason(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTrigger()) {
            sb.append("    Trigger:");
            try {
                sb.append(getTrigger()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPSFurnishChargingInformation()) {
            sb.append("    PSFurnishChargingInformation:");
            try {
                sb.append(getPSFurnishChargingInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRefundInformation()) {
            sb.append("    RefundInformation:");
            try {
                sb.append(getRefundInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countAFCorrelationInformation(); ++i) {
            sb.append("    AFCorrelationInformation:");
            try {
                sb.append(getAFCorrelationInformation(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countEnvelope(); ++i) {
            sb.append("    Envelope:");
            try {
                sb.append(getEnvelope(i)).append('\n');
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
        if (containsTimeQuotaMechanism()) {
            sb.append("    TimeQuotaMechanism:");
            try {
                sb.append(getTimeQuotaMechanism()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServiceSpecificInfo(); ++i) {
            sb.append("    ServiceSpecificInfo:");
            try {
                sb.append(getServiceSpecificInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsQoSInformation()) {
            sb.append("    QoSInformation:");
            try {
                sb.append(getQoSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
