package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Service-Data-Container AVP (AVP code 2040) is of type Grouped. Its 
 * purpose is to allow the transmission of the container to be reported for 
 * Flow based Charging. On encountering change on charging condition, this 
 * container  identifies the volume count (separated for uplink and downlink), 
 * elapsed time or number of events, per service data flow identified per 
 * rating group or combination of the rating group and service id within an  
 * IP-CAN bearer.
 */
public class ServiceDataContainer extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServiceDataContainer.
     */
    public ServiceDataContainer() {}

    ServiceDataContainer(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any AFCorrelationInformation.
     */
    public boolean containsAFCorrelationInformation() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AFCorrelationInformation);
    }

    /**
     * Gets the AFCorrelationInformation.
     */
    public AFCorrelationInformation getAFCorrelationInformation() throws NoSuchAttributeException {
        return (AFCorrelationInformation)_data.getContainer().get(Ro_r10_transatelAttributeName.AFCorrelationInformation, 0);
    }

    /**
     * Sets the AFCorrelationInformation.
     *
     * @param avp - the attribute value
     */
    public void setAFCorrelationInformation(AFCorrelationInformation avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AFCorrelationInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChargingRuleBaseName.
     */
    public boolean containsChargingRuleBaseName() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ChargingRuleBaseName);
    }

    /**
     * Gets the ChargingRuleBaseName.
     */
    public ChargingRuleBaseName getChargingRuleBaseName() throws NoSuchAttributeException {
        return (ChargingRuleBaseName)_data.getContainer().get(Ro_r10_transatelAttributeName.ChargingRuleBaseName, 0);
    }

    /**
     * Sets the ChargingRuleBaseName.
     *
     * @param avp - the attribute value
     */
    public void setChargingRuleBaseName(ChargingRuleBaseName avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ChargingRuleBaseName, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingInputOctets.
     */
    public boolean containsAccountingInputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingInputOctets);
    }

    /**
     * Gets the AccountingInputOctets.
     */
    public AccountingInputOctets getAccountingInputOctets() throws NoSuchAttributeException {
        return (AccountingInputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingInputOctets, 0);
    }

    /**
     * Sets the AccountingInputOctets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingInputOctets(AccountingInputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingInputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingOutputOctets.
     */
    public boolean containsAccountingOutputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingOutputOctets);
    }

    /**
     * Gets the AccountingOutputOctets.
     */
    public AccountingOutputOctets getAccountingOutputOctets() throws NoSuchAttributeException {
        return (AccountingOutputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingOutputOctets, 0);
    }

    /**
     * Sets the AccountingOutputOctets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingOutputOctets(AccountingOutputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingOutputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingInputPackets.
     */
    public boolean containsAccountingInputPackets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingInputPackets);
    }

    /**
     * Gets the AccountingInputPackets.
     */
    public AccountingInputPackets getAccountingInputPackets() throws NoSuchAttributeException {
        return (AccountingInputPackets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingInputPackets, 0);
    }

    /**
     * Sets the AccountingInputPackets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingInputPackets(AccountingInputPackets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingInputPackets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingOutputPackets.
     */
    public boolean containsAccountingOutputPackets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingOutputPackets);
    }

    /**
     * Gets the AccountingOutputPackets.
     */
    public AccountingOutputPackets getAccountingOutputPackets() throws NoSuchAttributeException {
        return (AccountingOutputPackets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingOutputPackets, 0);
    }

    /**
     * Sets the AccountingOutputPackets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingOutputPackets(AccountingOutputPackets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingOutputPackets, avp.getData(), true);
    }

    /**
     * Tests whether there is any LocalSequenceNumber.
     */
    public boolean containsLocalSequenceNumber() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.LocalSequenceNumber);
    }

    /**
     * Gets the LocalSequenceNumber.
     */
    public LocalSequenceNumber getLocalSequenceNumber() throws NoSuchAttributeException {
        return (LocalSequenceNumber)_data.getContainer().get(Ro_r10_transatelAttributeName.LocalSequenceNumber, 0);
    }

    /**
     * Sets the LocalSequenceNumber.
     *
     * @param avp - the attribute value
     */
    public void setLocalSequenceNumber(LocalSequenceNumber avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.LocalSequenceNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any QoSInformation.
     */
    public boolean containsQoSInformation() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.QoSInformation);
    }

    /**
     * Gets the QoSInformation.
     */
    public QoSInformation getQoSInformation() throws NoSuchAttributeException {
        return (QoSInformation)_data.getContainer().get(Ro_r10_transatelAttributeName.QoSInformation, 0);
    }

    /**
     * Sets the QoSInformation.
     *
     * @param avp - the attribute value
     */
    public void setQoSInformation(QoSInformation avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.QoSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any RatingGroup.
     */
    public boolean containsRatingGroup() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.RatingGroup);
    }

    /**
     * Gets the RatingGroup.
     */
    public RatingGroup getRatingGroup() throws NoSuchAttributeException {
        return (RatingGroup)_data.getContainer().get(Ro_r10_transatelAttributeName.RatingGroup, 0);
    }

    /**
     * Sets the RatingGroup.
     *
     * @param avp - the attribute value
     */
    public void setRatingGroup(RatingGroup avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.RatingGroup, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChangeTime.
     */
    public boolean containsChangeTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ChangeTime);
    }

    /**
     * Gets the ChangeTime.
     */
    public ChangeTime getChangeTime() throws NoSuchAttributeException {
        return (ChangeTime)_data.getContainer().get(Ro_r10_transatelAttributeName.ChangeTime, 0);
    }

    /**
     * Sets the ChangeTime.
     *
     * @param avp - the attribute value
     */
    public void setChangeTime(ChangeTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ChangeTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceIdentifier.
     */
    public boolean containsServiceIdentifier() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ServiceIdentifier);
    }

    /**
     * Gets the ServiceIdentifier.
     */
    public ServiceIdentifier getServiceIdentifier() throws NoSuchAttributeException {
        return (ServiceIdentifier)_data.getContainer().get(Ro_r10_transatelAttributeName.ServiceIdentifier, 0);
    }

    /**
     * Sets the ServiceIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setServiceIdentifier(ServiceIdentifier avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ServiceIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceSpecificInfo.
     */
    public boolean containsServiceSpecificInfo() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ServiceSpecificInfo);
    }

    /**
     * Gets the ServiceSpecificInfo.
     */
    public ServiceSpecificInfo getServiceSpecificInfo() throws NoSuchAttributeException {
        return (ServiceSpecificInfo)_data.getContainer().get(Ro_r10_transatelAttributeName.ServiceSpecificInfo, 0);
    }

    /**
     * Sets the ServiceSpecificInfo.
     *
     * @param avp - the attribute value
     */
    public void setServiceSpecificInfo(ServiceSpecificInfo avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ServiceSpecificInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any SGSNAddress.
     */
    public boolean containsSGSNAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SGSNAddress);
    }

    /**
     * Gets the SGSNAddress.
     */
    public SGSNAddress getSGSNAddress() throws NoSuchAttributeException {
        return (SGSNAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.SGSNAddress, 0);
    }

    /**
     * Sets the SGSNAddress.
     *
     * @param avp - the attribute value
     */
    public void setSGSNAddress(SGSNAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SGSNAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any TimeFirstUsage.
     */
    public boolean containsTimeFirstUsage() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TimeFirstUsage);
    }

    /**
     * Gets the TimeFirstUsage.
     */
    public TimeFirstUsage getTimeFirstUsage() throws NoSuchAttributeException {
        return (TimeFirstUsage)_data.getContainer().get(Ro_r10_transatelAttributeName.TimeFirstUsage, 0);
    }

    /**
     * Sets the TimeFirstUsage.
     *
     * @param avp - the attribute value
     */
    public void setTimeFirstUsage(TimeFirstUsage avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TimeFirstUsage, avp.getData(), true);
    }

    /**
     * Tests whether there is any TimeLastUsage.
     */
    public boolean containsTimeLastUsage() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TimeLastUsage);
    }

    /**
     * Gets the TimeLastUsage.
     */
    public TimeLastUsage getTimeLastUsage() throws NoSuchAttributeException {
        return (TimeLastUsage)_data.getContainer().get(Ro_r10_transatelAttributeName.TimeLastUsage, 0);
    }

    /**
     * Sets the TimeLastUsage.
     *
     * @param avp - the attribute value
     */
    public void setTimeLastUsage(TimeLastUsage avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TimeLastUsage, avp.getData(), true);
    }

    /**
     * Tests whether there is any TimeUsage.
     */
    public boolean containsTimeUsage() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TimeUsage);
    }

    /**
     * Gets the TimeUsage.
     */
    public TimeUsage getTimeUsage() throws NoSuchAttributeException {
        return (TimeUsage)_data.getContainer().get(Ro_r10_transatelAttributeName.TimeUsage, 0);
    }

    /**
     * Sets the TimeUsage.
     *
     * @param avp - the attribute value
     */
    public void setTimeUsage(TimeUsage avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TimeUsage, avp.getData(), true);
    }

    /**
     * Returns number of ChangeCondition instances.
     */
    public int countChangeCondition() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.ChangeCondition);
    }

    /**
     * Gets one ChangeCondition.
     *
     * @param index - the index of the attribute to return
     */
    public ChangeCondition getChangeCondition(int index) throws NoSuchAttributeException {
        return (ChangeCondition)_data.getContainer().get(Ro_r10_transatelAttributeName.ChangeCondition, index);
    }

    /**
     * Adds one ChangeCondition.
     *
     * @param avp - the attribute value
     */
    public void addChangeCondition(ChangeCondition avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ChangeCondition, avp.getData(), false);
    }

    /**
     * Tests whether there is any Ro3GPPUserLocationInfo.
     */
    public boolean containsRo3GPPUserLocationInfo() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Ro3GPPUserLocationInfo);
    }

    /**
     * Gets the Ro3GPPUserLocationInfo.
     */
    public Ro3GPPUserLocationInfo getRo3GPPUserLocationInfo() throws NoSuchAttributeException {
        return (Ro3GPPUserLocationInfo)_data.getContainer().get(Ro_r10_transatelAttributeName.Ro3GPPUserLocationInfo, 0);
    }

    /**
     * Sets the Ro3GPPUserLocationInfo.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPUserLocationInfo(Ro3GPPUserLocationInfo avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Ro3GPPUserLocationInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPP2BSID.
     */
    public boolean containsRo3GPP2BSID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Ro3GPP2BSID);
    }

    /**
     * Gets the Ro3GPP2BSID.
     */
    public Ro3GPP2BSID getRo3GPP2BSID() throws NoSuchAttributeException {
        return (Ro3GPP2BSID)_data.getContainer().get(Ro_r10_transatelAttributeName.Ro3GPP2BSID, 0);
    }

    /**
     * Sets the Ro3GPP2BSID.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPP2BSID(Ro3GPP2BSID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Ro3GPP2BSID, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsAFCorrelationInformation()) {
            sb.append("    AFCorrelationInformation:");
            try {
                sb.append(getAFCorrelationInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsChargingRuleBaseName()) {
            sb.append("    ChargingRuleBaseName:");
            try {
                sb.append(getChargingRuleBaseName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingInputOctets()) {
            sb.append("    AccountingInputOctets:");
            try {
                sb.append(getAccountingInputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingOutputOctets()) {
            sb.append("    AccountingOutputOctets:");
            try {
                sb.append(getAccountingOutputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingInputPackets()) {
            sb.append("    AccountingInputPackets:");
            try {
                sb.append(getAccountingInputPackets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingOutputPackets()) {
            sb.append("    AccountingOutputPackets:");
            try {
                sb.append(getAccountingOutputPackets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLocalSequenceNumber()) {
            sb.append("    LocalSequenceNumber:");
            try {
                sb.append(getLocalSequenceNumber()).append('\n');
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
        if (containsRatingGroup()) {
            sb.append("    RatingGroup:");
            try {
                sb.append(getRatingGroup()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsChangeTime()) {
            sb.append("    ChangeTime:");
            try {
                sb.append(getChangeTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceIdentifier()) {
            sb.append("    ServiceIdentifier:");
            try {
                sb.append(getServiceIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceSpecificInfo()) {
            sb.append("    ServiceSpecificInfo:");
            try {
                sb.append(getServiceSpecificInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSGSNAddress()) {
            sb.append("    SGSNAddress:");
            try {
                sb.append(getSGSNAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTimeFirstUsage()) {
            sb.append("    TimeFirstUsage:");
            try {
                sb.append(getTimeFirstUsage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTimeLastUsage()) {
            sb.append("    TimeLastUsage:");
            try {
                sb.append(getTimeLastUsage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTimeUsage()) {
            sb.append("    TimeUsage:");
            try {
                sb.append(getTimeUsage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countChangeCondition(); ++i) {
            sb.append("    ChangeCondition:");
            try {
                sb.append(getChangeCondition(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPUserLocationInfo()) {
            sb.append("    Ro3GPPUserLocationInfo:");
            try {
                sb.append(getRo3GPPUserLocationInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPP2BSID()) {
            sb.append("    Ro3GPP2BSID:");
            try {
                sb.append(getRo3GPP2BSID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
