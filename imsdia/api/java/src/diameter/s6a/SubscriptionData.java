package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Subscription-Data AVP is of type Grouped. It contains the information
 * related to the user profile relevant for EPS.	
 */
public class SubscriptionData extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SubscriptionData.
     */
    public SubscriptionData() {}

    SubscriptionData(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SubscriberStatus.
     */
    public boolean containsSubscriberStatus() {
        return _data.getContainer().contains(S6aAttributeName.SubscriberStatus);
    }

    /**
     * Gets the SubscriberStatus.
     */
    public SubscriberStatus getSubscriberStatus() throws NoSuchAttributeException {
        return (SubscriberStatus)_data.getContainer().get(S6aAttributeName.SubscriberStatus, 0);
    }

    /**
     * Sets the SubscriberStatus.
     *
     * @param avp - the attribute value
     */
    public void setSubscriberStatus(SubscriberStatus avp) {
        _data.getContainer().add(S6aAttributeName.SubscriberStatus, avp.getData(), true);
    }

    /**
     * Tests whether there is any MSISDN.
     */
    public boolean containsMSISDN() {
        return _data.getContainer().contains(S6aAttributeName.MSISDN);
    }

    /**
     * Gets the MSISDN.
     */
    public MSISDN getMSISDN() throws NoSuchAttributeException {
        return (MSISDN)_data.getContainer().get(S6aAttributeName.MSISDN, 0);
    }

    /**
     * Sets the MSISDN.
     *
     * @param avp - the attribute value
     */
    public void setMSISDN(MSISDN avp) {
        _data.getContainer().add(S6aAttributeName.MSISDN, avp.getData(), true);
    }

    /**
     * Tests whether there is any STNSR.
     */
    public boolean containsSTNSR() {
        return _data.getContainer().contains(S6aAttributeName.STNSR);
    }

    /**
     * Gets the STNSR.
     */
    public STNSR getSTNSR() throws NoSuchAttributeException {
        return (STNSR)_data.getContainer().get(S6aAttributeName.STNSR, 0);
    }

    /**
     * Sets the STNSR.
     *
     * @param avp - the attribute value
     */
    public void setSTNSR(STNSR avp) {
        _data.getContainer().add(S6aAttributeName.STNSR, avp.getData(), true);
    }

    /**
     * Tests whether there is any NetworkAccessMode.
     */
    public boolean containsNetworkAccessMode() {
        return _data.getContainer().contains(S6aAttributeName.NetworkAccessMode);
    }

    /**
     * Gets the NetworkAccessMode.
     */
    public NetworkAccessMode getNetworkAccessMode() throws NoSuchAttributeException {
        return (NetworkAccessMode)_data.getContainer().get(S6aAttributeName.NetworkAccessMode, 0);
    }

    /**
     * Sets the NetworkAccessMode.
     *
     * @param avp - the attribute value
     */
    public void setNetworkAccessMode(NetworkAccessMode avp) {
        _data.getContainer().add(S6aAttributeName.NetworkAccessMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any OperatorDeterminedBarring.
     */
    public boolean containsOperatorDeterminedBarring() {
        return _data.getContainer().contains(S6aAttributeName.OperatorDeterminedBarring);
    }

    /**
     * Gets the OperatorDeterminedBarring.
     */
    public OperatorDeterminedBarring getOperatorDeterminedBarring() throws NoSuchAttributeException {
        return (OperatorDeterminedBarring)_data.getContainer().get(S6aAttributeName.OperatorDeterminedBarring, 0);
    }

    /**
     * Sets the OperatorDeterminedBarring.
     *
     * @param avp - the attribute value
     */
    public void setOperatorDeterminedBarring(OperatorDeterminedBarring avp) {
        _data.getContainer().add(S6aAttributeName.OperatorDeterminedBarring, avp.getData(), true);
    }

    /**
     * Tests whether there is any HPLMNODB.
     */
    public boolean containsHPLMNODB() {
        return _data.getContainer().contains(S6aAttributeName.HPLMNODB);
    }

    /**
     * Gets the HPLMNODB.
     */
    public HPLMNODB getHPLMNODB() throws NoSuchAttributeException {
        return (HPLMNODB)_data.getContainer().get(S6aAttributeName.HPLMNODB, 0);
    }

    /**
     * Sets the HPLMNODB.
     *
     * @param avp - the attribute value
     */
    public void setHPLMNODB(HPLMNODB avp) {
        _data.getContainer().add(S6aAttributeName.HPLMNODB, avp.getData(), true);
    }

    /**
     * Returns number of RegionalSubscriptionZoneCode instances.
     */
    public int countRegionalSubscriptionZoneCode() {
        return _data.getContainer().count(S6aAttributeName.RegionalSubscriptionZoneCode);
    }

    /**
     * Gets one RegionalSubscriptionZoneCode.
     *
     * @param index - the index of the attribute to return
     */
    public RegionalSubscriptionZoneCode getRegionalSubscriptionZoneCode(int index) throws NoSuchAttributeException {
        return (RegionalSubscriptionZoneCode)_data.getContainer().get(S6aAttributeName.RegionalSubscriptionZoneCode, index);
    }

    /**
     * Adds one RegionalSubscriptionZoneCode.
     *
     * @param avp - the attribute value
     */
    public void addRegionalSubscriptionZoneCode(RegionalSubscriptionZoneCode avp) {
        _data.getContainer().add(S6aAttributeName.RegionalSubscriptionZoneCode, avp.getData(), false);
    }

    /**
     * Tests whether there is any AccessRestrictionData.
     */
    public boolean containsAccessRestrictionData() {
        return _data.getContainer().contains(S6aAttributeName.AccessRestrictionData);
    }

    /**
     * Gets the AccessRestrictionData.
     */
    public AccessRestrictionData getAccessRestrictionData() throws NoSuchAttributeException {
        return (AccessRestrictionData)_data.getContainer().get(S6aAttributeName.AccessRestrictionData, 0);
    }

    /**
     * Sets the AccessRestrictionData.
     *
     * @param avp - the attribute value
     */
    public void setAccessRestrictionData(AccessRestrictionData avp) {
        _data.getContainer().add(S6aAttributeName.AccessRestrictionData, avp.getData(), true);
    }

    /**
     * Tests whether there is any APNOIReplacement.
     */
    public boolean containsAPNOIReplacement() {
        return _data.getContainer().contains(S6aAttributeName.APNOIReplacement);
    }

    /**
     * Gets the APNOIReplacement.
     */
    public APNOIReplacement getAPNOIReplacement() throws NoSuchAttributeException {
        return (APNOIReplacement)_data.getContainer().get(S6aAttributeName.APNOIReplacement, 0);
    }

    /**
     * Sets the APNOIReplacement.
     *
     * @param avp - the attribute value
     */
    public void setAPNOIReplacement(APNOIReplacement avp) {
        _data.getContainer().add(S6aAttributeName.APNOIReplacement, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSInfo.
     */
    public boolean containsLCSInfo() {
        return _data.getContainer().contains(S6aAttributeName.LCSInfo);
    }

    /**
     * Gets the LCSInfo.
     */
    public LCSInfo getLCSInfo() throws NoSuchAttributeException {
        return (LCSInfo)_data.getContainer().get(S6aAttributeName.LCSInfo, 0);
    }

    /**
     * Sets the LCSInfo.
     *
     * @param avp - the attribute value
     */
    public void setLCSInfo(LCSInfo avp) {
        _data.getContainer().add(S6aAttributeName.LCSInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any TeleserviceList.
     */
    public boolean containsTeleserviceList() {
        return _data.getContainer().contains(S6aAttributeName.TeleserviceList);
    }

    /**
     * Gets the TeleserviceList.
     */
    public TeleserviceList getTeleserviceList() throws NoSuchAttributeException {
        return (TeleserviceList)_data.getContainer().get(S6aAttributeName.TeleserviceList, 0);
    }

    /**
     * Sets the TeleserviceList.
     *
     * @param avp - the attribute value
     */
    public void setTeleserviceList(TeleserviceList avp) {
        _data.getContainer().add(S6aAttributeName.TeleserviceList, avp.getData(), true);
    }

    /**
     * Tests whether there is any CallBarringInforList.
     */
    public boolean containsCallBarringInforList() {
        return _data.getContainer().contains(S6aAttributeName.CallBarringInforList);
    }

    /**
     * Gets the CallBarringInforList.
     */
    public CallBarringInforList getCallBarringInforList() throws NoSuchAttributeException {
        return (CallBarringInforList)_data.getContainer().get(S6aAttributeName.CallBarringInforList, 0);
    }

    /**
     * Sets the CallBarringInforList.
     *
     * @param avp - the attribute value
     */
    public void setCallBarringInforList(CallBarringInforList avp) {
        _data.getContainer().add(S6aAttributeName.CallBarringInforList, avp.getData(), true);
    }

    /**
     * Tests whether there is any S6a3GPPChargingCharacteristics.
     */
    public boolean containsS6a3GPPChargingCharacteristics() {
        return _data.getContainer().contains(S6aAttributeName.S6a3GPPChargingCharacteristics);
    }

    /**
     * Gets the S6a3GPPChargingCharacteristics.
     */
    public S6a3GPPChargingCharacteristics getS6a3GPPChargingCharacteristics() throws NoSuchAttributeException {
        return (S6a3GPPChargingCharacteristics)_data.getContainer().get(S6aAttributeName.S6a3GPPChargingCharacteristics, 0);
    }

    /**
     * Sets the S6a3GPPChargingCharacteristics.
     *
     * @param avp - the attribute value
     */
    public void setS6a3GPPChargingCharacteristics(S6a3GPPChargingCharacteristics avp) {
        _data.getContainer().add(S6aAttributeName.S6a3GPPChargingCharacteristics, avp.getData(), true);
    }

    /**
     * Tests whether there is any AMBR.
     */
    public boolean containsAMBR() {
        return _data.getContainer().contains(S6aAttributeName.AMBR);
    }

    /**
     * Gets the AMBR.
     */
    public AMBR getAMBR() throws NoSuchAttributeException {
        return (AMBR)_data.getContainer().get(S6aAttributeName.AMBR, 0);
    }

    /**
     * Sets the AMBR.
     *
     * @param avp - the attribute value
     */
    public void setAMBR(AMBR avp) {
        _data.getContainer().add(S6aAttributeName.AMBR, avp.getData(), true);
    }

    /**
     * Tests whether there is any APNConfigurationProfile.
     */
    public boolean containsAPNConfigurationProfile() {
        return _data.getContainer().contains(S6aAttributeName.APNConfigurationProfile);
    }

    /**
     * Gets the APNConfigurationProfile.
     */
    public APNConfigurationProfile getAPNConfigurationProfile() throws NoSuchAttributeException {
        return (APNConfigurationProfile)_data.getContainer().get(S6aAttributeName.APNConfigurationProfile, 0);
    }

    /**
     * Sets the APNConfigurationProfile.
     *
     * @param avp - the attribute value
     */
    public void setAPNConfigurationProfile(APNConfigurationProfile avp) {
        _data.getContainer().add(S6aAttributeName.APNConfigurationProfile, avp.getData(), true);
    }

    /**
     * Tests whether there is any RATFrequencySelectionPriorityID.
     */
    public boolean containsRATFrequencySelectionPriorityID() {
        return _data.getContainer().contains(S6aAttributeName.RATFrequencySelectionPriorityID);
    }

    /**
     * Gets the RATFrequencySelectionPriorityID.
     */
    public RATFrequencySelectionPriorityID getRATFrequencySelectionPriorityID() throws NoSuchAttributeException {
        return (RATFrequencySelectionPriorityID)_data.getContainer().get(S6aAttributeName.RATFrequencySelectionPriorityID, 0);
    }

    /**
     * Sets the RATFrequencySelectionPriorityID.
     *
     * @param avp - the attribute value
     */
    public void setRATFrequencySelectionPriorityID(RATFrequencySelectionPriorityID avp) {
        _data.getContainer().add(S6aAttributeName.RATFrequencySelectionPriorityID, avp.getData(), true);
    }

    /**
     * Tests whether there is any TraceData.
     */
    public boolean containsTraceData() {
        return _data.getContainer().contains(S6aAttributeName.TraceData);
    }

    /**
     * Gets the TraceData.
     */
    public TraceData getTraceData() throws NoSuchAttributeException {
        return (TraceData)_data.getContainer().get(S6aAttributeName.TraceData, 0);
    }

    /**
     * Sets the TraceData.
     *
     * @param avp - the attribute value
     */
    public void setTraceData(TraceData avp) {
        _data.getContainer().add(S6aAttributeName.TraceData, avp.getData(), true);
    }

    /**
     * Tests whether there is any GPRSSubscriptionData.
     */
    public boolean containsGPRSSubscriptionData() {
        return _data.getContainer().contains(S6aAttributeName.GPRSSubscriptionData);
    }

    /**
     * Gets the GPRSSubscriptionData.
     */
    public GPRSSubscriptionData getGPRSSubscriptionData() throws NoSuchAttributeException {
        return (GPRSSubscriptionData)_data.getContainer().get(S6aAttributeName.GPRSSubscriptionData, 0);
    }

    /**
     * Sets the GPRSSubscriptionData.
     *
     * @param avp - the attribute value
     */
    public void setGPRSSubscriptionData(GPRSSubscriptionData avp) {
        _data.getContainer().add(S6aAttributeName.GPRSSubscriptionData, avp.getData(), true);
    }

    /**
     * Returns number of CSGSubscriptionData instances.
     */
    public int countCSGSubscriptionData() {
        return _data.getContainer().count(S6aAttributeName.CSGSubscriptionData);
    }

    /**
     * Gets one CSGSubscriptionData.
     *
     * @param index - the index of the attribute to return
     */
    public CSGSubscriptionData getCSGSubscriptionData(int index) throws NoSuchAttributeException {
        return (CSGSubscriptionData)_data.getContainer().get(S6aAttributeName.CSGSubscriptionData, index);
    }

    /**
     * Adds one CSGSubscriptionData.
     *
     * @param avp - the attribute value
     */
    public void addCSGSubscriptionData(CSGSubscriptionData avp) {
        _data.getContainer().add(S6aAttributeName.CSGSubscriptionData, avp.getData(), false);
    }

    /**
     * Tests whether there is any RoamingRestrictedDueToUnsupportedFeature.
     */
    public boolean containsRoamingRestrictedDueToUnsupportedFeature() {
        return _data.getContainer().contains(S6aAttributeName.RoamingRestrictedDueToUnsupportedFeature);
    }

    /**
     * Gets the RoamingRestrictedDueToUnsupportedFeature.
     */
    public RoamingRestrictedDueToUnsupportedFeature getRoamingRestrictedDueToUnsupportedFeature() throws NoSuchAttributeException {
        return (RoamingRestrictedDueToUnsupportedFeature)_data.getContainer().get(S6aAttributeName.RoamingRestrictedDueToUnsupportedFeature, 0);
    }

    /**
     * Sets the RoamingRestrictedDueToUnsupportedFeature.
     *
     * @param avp - the attribute value
     */
    public void setRoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature avp) {
        _data.getContainer().add(S6aAttributeName.RoamingRestrictedDueToUnsupportedFeature, avp.getData(), true);
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
        if (containsSubscriberStatus()) {
            sb.append("    SubscriberStatus:");
            try {
                sb.append(getSubscriberStatus()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMSISDN()) {
            sb.append("    MSISDN:");
            try {
                sb.append(getMSISDN()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSTNSR()) {
            sb.append("    STNSR:");
            try {
                sb.append(getSTNSR()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNetworkAccessMode()) {
            sb.append("    NetworkAccessMode:");
            try {
                sb.append(getNetworkAccessMode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOperatorDeterminedBarring()) {
            sb.append("    OperatorDeterminedBarring:");
            try {
                sb.append(getOperatorDeterminedBarring()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsHPLMNODB()) {
            sb.append("    HPLMNODB:");
            try {
                sb.append(getHPLMNODB()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRegionalSubscriptionZoneCode(); ++i) {
            sb.append("    RegionalSubscriptionZoneCode:");
            try {
                sb.append(getRegionalSubscriptionZoneCode(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccessRestrictionData()) {
            sb.append("    AccessRestrictionData:");
            try {
                sb.append(getAccessRestrictionData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAPNOIReplacement()) {
            sb.append("    APNOIReplacement:");
            try {
                sb.append(getAPNOIReplacement()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSInfo()) {
            sb.append("    LCSInfo:");
            try {
                sb.append(getLCSInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTeleserviceList()) {
            sb.append("    TeleserviceList:");
            try {
                sb.append(getTeleserviceList()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCallBarringInforList()) {
            sb.append("    CallBarringInforList:");
            try {
                sb.append(getCallBarringInforList()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsS6a3GPPChargingCharacteristics()) {
            sb.append("    S6a3GPPChargingCharacteristics:");
            try {
                sb.append(getS6a3GPPChargingCharacteristics()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAMBR()) {
            sb.append("    AMBR:");
            try {
                sb.append(getAMBR()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAPNConfigurationProfile()) {
            sb.append("    APNConfigurationProfile:");
            try {
                sb.append(getAPNConfigurationProfile()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRATFrequencySelectionPriorityID()) {
            sb.append("    RATFrequencySelectionPriorityID:");
            try {
                sb.append(getRATFrequencySelectionPriorityID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTraceData()) {
            sb.append("    TraceData:");
            try {
                sb.append(getTraceData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGPRSSubscriptionData()) {
            sb.append("    GPRSSubscriptionData:");
            try {
                sb.append(getGPRSSubscriptionData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countCSGSubscriptionData(); ++i) {
            sb.append("    CSGSubscriptionData:");
            try {
                sb.append(getCSGSubscriptionData(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRoamingRestrictedDueToUnsupportedFeature()) {
            sb.append("    RoamingRestrictedDueToUnsupportedFeature:");
            try {
                sb.append(getRoamingRestrictedDueToUnsupportedFeature()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
