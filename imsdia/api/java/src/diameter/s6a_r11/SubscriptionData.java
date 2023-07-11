package diameter.s6a_r11;

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
        return _data.getContainer().contains(S6a_r11AttributeName.SubscriberStatus);
    }

    /**
     * Gets the SubscriberStatus.
     */
    public SubscriberStatus getSubscriberStatus() throws NoSuchAttributeException {
        return (SubscriberStatus)_data.getContainer().get(S6a_r11AttributeName.SubscriberStatus, 0);
    }

    /**
     * Sets the SubscriberStatus.
     *
     * @param avp - the attribute value
     */
    public void setSubscriberStatus(SubscriberStatus avp) {
        _data.getContainer().add(S6a_r11AttributeName.SubscriberStatus, avp.getData(), true);
    }

    /**
     * Tests whether there is any MSISDN.
     */
    public boolean containsMSISDN() {
        return _data.getContainer().contains(S6a_r11AttributeName.MSISDN);
    }

    /**
     * Gets the MSISDN.
     */
    public MSISDN getMSISDN() throws NoSuchAttributeException {
        return (MSISDN)_data.getContainer().get(S6a_r11AttributeName.MSISDN, 0);
    }

    /**
     * Sets the MSISDN.
     *
     * @param avp - the attribute value
     */
    public void setMSISDN(MSISDN avp) {
        _data.getContainer().add(S6a_r11AttributeName.MSISDN, avp.getData(), true);
    }

    /**
     * Tests whether there is any AMSISDN.
     */
    public boolean containsAMSISDN() {
        return _data.getContainer().contains(S6a_r11AttributeName.AMSISDN);
    }

    /**
     * Gets the AMSISDN.
     */
    public AMSISDN getAMSISDN() throws NoSuchAttributeException {
        return (AMSISDN)_data.getContainer().get(S6a_r11AttributeName.AMSISDN, 0);
    }

    /**
     * Sets the AMSISDN.
     *
     * @param avp - the attribute value
     */
    public void setAMSISDN(AMSISDN avp) {
        _data.getContainer().add(S6a_r11AttributeName.AMSISDN, avp.getData(), true);
    }

    /**
     * Tests whether there is any STNSR.
     */
    public boolean containsSTNSR() {
        return _data.getContainer().contains(S6a_r11AttributeName.STNSR);
    }

    /**
     * Gets the STNSR.
     */
    public STNSR getSTNSR() throws NoSuchAttributeException {
        return (STNSR)_data.getContainer().get(S6a_r11AttributeName.STNSR, 0);
    }

    /**
     * Sets the STNSR.
     *
     * @param avp - the attribute value
     */
    public void setSTNSR(STNSR avp) {
        _data.getContainer().add(S6a_r11AttributeName.STNSR, avp.getData(), true);
    }

    /**
     * Tests whether there is any ICSIndicator.
     */
    public boolean containsICSIndicator() {
        return _data.getContainer().contains(S6a_r11AttributeName.ICSIndicator);
    }

    /**
     * Gets the ICSIndicator.
     */
    public ICSIndicator getICSIndicator() throws NoSuchAttributeException {
        return (ICSIndicator)_data.getContainer().get(S6a_r11AttributeName.ICSIndicator, 0);
    }

    /**
     * Sets the ICSIndicator.
     *
     * @param avp - the attribute value
     */
    public void setICSIndicator(ICSIndicator avp) {
        _data.getContainer().add(S6a_r11AttributeName.ICSIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any NetworkAccessMode.
     */
    public boolean containsNetworkAccessMode() {
        return _data.getContainer().contains(S6a_r11AttributeName.NetworkAccessMode);
    }

    /**
     * Gets the NetworkAccessMode.
     */
    public NetworkAccessMode getNetworkAccessMode() throws NoSuchAttributeException {
        return (NetworkAccessMode)_data.getContainer().get(S6a_r11AttributeName.NetworkAccessMode, 0);
    }

    /**
     * Sets the NetworkAccessMode.
     *
     * @param avp - the attribute value
     */
    public void setNetworkAccessMode(NetworkAccessMode avp) {
        _data.getContainer().add(S6a_r11AttributeName.NetworkAccessMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any OperatorDeterminedBarring.
     */
    public boolean containsOperatorDeterminedBarring() {
        return _data.getContainer().contains(S6a_r11AttributeName.OperatorDeterminedBarring);
    }

    /**
     * Gets the OperatorDeterminedBarring.
     */
    public OperatorDeterminedBarring getOperatorDeterminedBarring() throws NoSuchAttributeException {
        return (OperatorDeterminedBarring)_data.getContainer().get(S6a_r11AttributeName.OperatorDeterminedBarring, 0);
    }

    /**
     * Sets the OperatorDeterminedBarring.
     *
     * @param avp - the attribute value
     */
    public void setOperatorDeterminedBarring(OperatorDeterminedBarring avp) {
        _data.getContainer().add(S6a_r11AttributeName.OperatorDeterminedBarring, avp.getData(), true);
    }

    /**
     * Tests whether there is any HPLMNODB.
     */
    public boolean containsHPLMNODB() {
        return _data.getContainer().contains(S6a_r11AttributeName.HPLMNODB);
    }

    /**
     * Gets the HPLMNODB.
     */
    public HPLMNODB getHPLMNODB() throws NoSuchAttributeException {
        return (HPLMNODB)_data.getContainer().get(S6a_r11AttributeName.HPLMNODB, 0);
    }

    /**
     * Sets the HPLMNODB.
     *
     * @param avp - the attribute value
     */
    public void setHPLMNODB(HPLMNODB avp) {
        _data.getContainer().add(S6a_r11AttributeName.HPLMNODB, avp.getData(), true);
    }

    /**
     * Returns number of RegionalSubscriptionZoneCode instances.
     */
    public int countRegionalSubscriptionZoneCode() {
        return _data.getContainer().count(S6a_r11AttributeName.RegionalSubscriptionZoneCode);
    }

    /**
     * Gets one RegionalSubscriptionZoneCode.
     *
     * @param index - the index of the attribute to return
     */
    public RegionalSubscriptionZoneCode getRegionalSubscriptionZoneCode(int index) throws NoSuchAttributeException {
        return (RegionalSubscriptionZoneCode)_data.getContainer().get(S6a_r11AttributeName.RegionalSubscriptionZoneCode, index);
    }

    /**
     * Adds one RegionalSubscriptionZoneCode.
     *
     * @param avp - the attribute value
     */
    public void addRegionalSubscriptionZoneCode(RegionalSubscriptionZoneCode avp) {
        _data.getContainer().add(S6a_r11AttributeName.RegionalSubscriptionZoneCode, avp.getData(), false);
    }

    /**
     * Tests whether there is any AccessRestrictionData.
     */
    public boolean containsAccessRestrictionData() {
        return _data.getContainer().contains(S6a_r11AttributeName.AccessRestrictionData);
    }

    /**
     * Gets the AccessRestrictionData.
     */
    public AccessRestrictionData getAccessRestrictionData() throws NoSuchAttributeException {
        return (AccessRestrictionData)_data.getContainer().get(S6a_r11AttributeName.AccessRestrictionData, 0);
    }

    /**
     * Sets the AccessRestrictionData.
     *
     * @param avp - the attribute value
     */
    public void setAccessRestrictionData(AccessRestrictionData avp) {
        _data.getContainer().add(S6a_r11AttributeName.AccessRestrictionData, avp.getData(), true);
    }

    /**
     * Tests whether there is any APNOIReplacement.
     */
    public boolean containsAPNOIReplacement() {
        return _data.getContainer().contains(S6a_r11AttributeName.APNOIReplacement);
    }

    /**
     * Gets the APNOIReplacement.
     */
    public APNOIReplacement getAPNOIReplacement() throws NoSuchAttributeException {
        return (APNOIReplacement)_data.getContainer().get(S6a_r11AttributeName.APNOIReplacement, 0);
    }

    /**
     * Sets the APNOIReplacement.
     *
     * @param avp - the attribute value
     */
    public void setAPNOIReplacement(APNOIReplacement avp) {
        _data.getContainer().add(S6a_r11AttributeName.APNOIReplacement, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSInfo.
     */
    public boolean containsLCSInfo() {
        return _data.getContainer().contains(S6a_r11AttributeName.LCSInfo);
    }

    /**
     * Gets the LCSInfo.
     */
    public LCSInfo getLCSInfo() throws NoSuchAttributeException {
        return (LCSInfo)_data.getContainer().get(S6a_r11AttributeName.LCSInfo, 0);
    }

    /**
     * Sets the LCSInfo.
     *
     * @param avp - the attribute value
     */
    public void setLCSInfo(LCSInfo avp) {
        _data.getContainer().add(S6a_r11AttributeName.LCSInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any TeleserviceList.
     */
    public boolean containsTeleserviceList() {
        return _data.getContainer().contains(S6a_r11AttributeName.TeleserviceList);
    }

    /**
     * Gets the TeleserviceList.
     */
    public TeleserviceList getTeleserviceList() throws NoSuchAttributeException {
        return (TeleserviceList)_data.getContainer().get(S6a_r11AttributeName.TeleserviceList, 0);
    }

    /**
     * Sets the TeleserviceList.
     *
     * @param avp - the attribute value
     */
    public void setTeleserviceList(TeleserviceList avp) {
        _data.getContainer().add(S6a_r11AttributeName.TeleserviceList, avp.getData(), true);
    }

    /**
     * Tests whether there is any CallBarringInforList.
     */
    public boolean containsCallBarringInforList() {
        return _data.getContainer().contains(S6a_r11AttributeName.CallBarringInforList);
    }

    /**
     * Gets the CallBarringInforList.
     */
    public CallBarringInforList getCallBarringInforList() throws NoSuchAttributeException {
        return (CallBarringInforList)_data.getContainer().get(S6a_r11AttributeName.CallBarringInforList, 0);
    }

    /**
     * Sets the CallBarringInforList.
     *
     * @param avp - the attribute value
     */
    public void setCallBarringInforList(CallBarringInforList avp) {
        _data.getContainer().add(S6a_r11AttributeName.CallBarringInforList, avp.getData(), true);
    }

    /**
     * Tests whether there is any S6a3GPPChargingCharacteristics.
     */
    public boolean containsS6a3GPPChargingCharacteristics() {
        return _data.getContainer().contains(S6a_r11AttributeName.S6a3GPPChargingCharacteristics);
    }

    /**
     * Gets the S6a3GPPChargingCharacteristics.
     */
    public S6a3GPPChargingCharacteristics getS6a3GPPChargingCharacteristics() throws NoSuchAttributeException {
        return (S6a3GPPChargingCharacteristics)_data.getContainer().get(S6a_r11AttributeName.S6a3GPPChargingCharacteristics, 0);
    }

    /**
     * Sets the S6a3GPPChargingCharacteristics.
     *
     * @param avp - the attribute value
     */
    public void setS6a3GPPChargingCharacteristics(S6a3GPPChargingCharacteristics avp) {
        _data.getContainer().add(S6a_r11AttributeName.S6a3GPPChargingCharacteristics, avp.getData(), true);
    }

    /**
     * Tests whether there is any AMBR.
     */
    public boolean containsAMBR() {
        return _data.getContainer().contains(S6a_r11AttributeName.AMBR);
    }

    /**
     * Gets the AMBR.
     */
    public AMBR getAMBR() throws NoSuchAttributeException {
        return (AMBR)_data.getContainer().get(S6a_r11AttributeName.AMBR, 0);
    }

    /**
     * Sets the AMBR.
     *
     * @param avp - the attribute value
     */
    public void setAMBR(AMBR avp) {
        _data.getContainer().add(S6a_r11AttributeName.AMBR, avp.getData(), true);
    }

    /**
     * Tests whether there is any APNConfigurationProfile.
     */
    public boolean containsAPNConfigurationProfile() {
        return _data.getContainer().contains(S6a_r11AttributeName.APNConfigurationProfile);
    }

    /**
     * Gets the APNConfigurationProfile.
     */
    public APNConfigurationProfile getAPNConfigurationProfile() throws NoSuchAttributeException {
        return (APNConfigurationProfile)_data.getContainer().get(S6a_r11AttributeName.APNConfigurationProfile, 0);
    }

    /**
     * Sets the APNConfigurationProfile.
     *
     * @param avp - the attribute value
     */
    public void setAPNConfigurationProfile(APNConfigurationProfile avp) {
        _data.getContainer().add(S6a_r11AttributeName.APNConfigurationProfile, avp.getData(), true);
    }

    /**
     * Tests whether there is any RATFrequencySelectionPriorityID.
     */
    public boolean containsRATFrequencySelectionPriorityID() {
        return _data.getContainer().contains(S6a_r11AttributeName.RATFrequencySelectionPriorityID);
    }

    /**
     * Gets the RATFrequencySelectionPriorityID.
     */
    public RATFrequencySelectionPriorityID getRATFrequencySelectionPriorityID() throws NoSuchAttributeException {
        return (RATFrequencySelectionPriorityID)_data.getContainer().get(S6a_r11AttributeName.RATFrequencySelectionPriorityID, 0);
    }

    /**
     * Sets the RATFrequencySelectionPriorityID.
     *
     * @param avp - the attribute value
     */
    public void setRATFrequencySelectionPriorityID(RATFrequencySelectionPriorityID avp) {
        _data.getContainer().add(S6a_r11AttributeName.RATFrequencySelectionPriorityID, avp.getData(), true);
    }

    /**
     * Tests whether there is any TraceData.
     */
    public boolean containsTraceData() {
        return _data.getContainer().contains(S6a_r11AttributeName.TraceData);
    }

    /**
     * Gets the TraceData.
     */
    public TraceData getTraceData() throws NoSuchAttributeException {
        return (TraceData)_data.getContainer().get(S6a_r11AttributeName.TraceData, 0);
    }

    /**
     * Sets the TraceData.
     *
     * @param avp - the attribute value
     */
    public void setTraceData(TraceData avp) {
        _data.getContainer().add(S6a_r11AttributeName.TraceData, avp.getData(), true);
    }

    /**
     * Tests whether there is any GPRSSubscriptionData.
     */
    public boolean containsGPRSSubscriptionData() {
        return _data.getContainer().contains(S6a_r11AttributeName.GPRSSubscriptionData);
    }

    /**
     * Gets the GPRSSubscriptionData.
     */
    public GPRSSubscriptionData getGPRSSubscriptionData() throws NoSuchAttributeException {
        return (GPRSSubscriptionData)_data.getContainer().get(S6a_r11AttributeName.GPRSSubscriptionData, 0);
    }

    /**
     * Sets the GPRSSubscriptionData.
     *
     * @param avp - the attribute value
     */
    public void setGPRSSubscriptionData(GPRSSubscriptionData avp) {
        _data.getContainer().add(S6a_r11AttributeName.GPRSSubscriptionData, avp.getData(), true);
    }

    /**
     * Returns number of CSGSubscriptionData instances.
     */
    public int countCSGSubscriptionData() {
        return _data.getContainer().count(S6a_r11AttributeName.CSGSubscriptionData);
    }

    /**
     * Gets one CSGSubscriptionData.
     *
     * @param index - the index of the attribute to return
     */
    public CSGSubscriptionData getCSGSubscriptionData(int index) throws NoSuchAttributeException {
        return (CSGSubscriptionData)_data.getContainer().get(S6a_r11AttributeName.CSGSubscriptionData, index);
    }

    /**
     * Adds one CSGSubscriptionData.
     *
     * @param avp - the attribute value
     */
    public void addCSGSubscriptionData(CSGSubscriptionData avp) {
        _data.getContainer().add(S6a_r11AttributeName.CSGSubscriptionData, avp.getData(), false);
    }

    /**
     * Tests whether there is any RoamingRestrictedDueToUnsupportedFeature.
     */
    public boolean containsRoamingRestrictedDueToUnsupportedFeature() {
        return _data.getContainer().contains(S6a_r11AttributeName.RoamingRestrictedDueToUnsupportedFeature);
    }

    /**
     * Gets the RoamingRestrictedDueToUnsupportedFeature.
     */
    public RoamingRestrictedDueToUnsupportedFeature getRoamingRestrictedDueToUnsupportedFeature() throws NoSuchAttributeException {
        return (RoamingRestrictedDueToUnsupportedFeature)_data.getContainer().get(S6a_r11AttributeName.RoamingRestrictedDueToUnsupportedFeature, 0);
    }

    /**
     * Sets the RoamingRestrictedDueToUnsupportedFeature.
     *
     * @param avp - the attribute value
     */
    public void setRoamingRestrictedDueToUnsupportedFeature(RoamingRestrictedDueToUnsupportedFeature avp) {
        _data.getContainer().add(S6a_r11AttributeName.RoamingRestrictedDueToUnsupportedFeature, avp.getData(), true);
    }

    /**
     * Tests whether there is any SubscribedPeriodicRAUTAUTimer.
     */
    public boolean containsSubscribedPeriodicRAUTAUTimer() {
        return _data.getContainer().contains(S6a_r11AttributeName.SubscribedPeriodicRAUTAUTimer);
    }

    /**
     * Gets the SubscribedPeriodicRAUTAUTimer.
     */
    public SubscribedPeriodicRAUTAUTimer getSubscribedPeriodicRAUTAUTimer() throws NoSuchAttributeException {
        return (SubscribedPeriodicRAUTAUTimer)_data.getContainer().get(S6a_r11AttributeName.SubscribedPeriodicRAUTAUTimer, 0);
    }

    /**
     * Sets the SubscribedPeriodicRAUTAUTimer.
     *
     * @param avp - the attribute value
     */
    public void setSubscribedPeriodicRAUTAUTimer(SubscribedPeriodicRAUTAUTimer avp) {
        _data.getContainer().add(S6a_r11AttributeName.SubscribedPeriodicRAUTAUTimer, avp.getData(), true);
    }

    /**
     * Tests whether there is any MPSPriority.
     */
    public boolean containsMPSPriority() {
        return _data.getContainer().contains(S6a_r11AttributeName.MPSPriority);
    }

    /**
     * Gets the MPSPriority.
     */
    public MPSPriority getMPSPriority() throws NoSuchAttributeException {
        return (MPSPriority)_data.getContainer().get(S6a_r11AttributeName.MPSPriority, 0);
    }

    /**
     * Sets the MPSPriority.
     *
     * @param avp - the attribute value
     */
    public void setMPSPriority(MPSPriority avp) {
        _data.getContainer().add(S6a_r11AttributeName.MPSPriority, avp.getData(), true);
    }

    /**
     * Tests whether there is any VPLMNLIPAAllowed.
     */
    public boolean containsVPLMNLIPAAllowed() {
        return _data.getContainer().contains(S6a_r11AttributeName.VPLMNLIPAAllowed);
    }

    /**
     * Gets the VPLMNLIPAAllowed.
     */
    public VPLMNLIPAAllowed getVPLMNLIPAAllowed() throws NoSuchAttributeException {
        return (VPLMNLIPAAllowed)_data.getContainer().get(S6a_r11AttributeName.VPLMNLIPAAllowed, 0);
    }

    /**
     * Sets the VPLMNLIPAAllowed.
     *
     * @param avp - the attribute value
     */
    public void setVPLMNLIPAAllowed(VPLMNLIPAAllowed avp) {
        _data.getContainer().add(S6a_r11AttributeName.VPLMNLIPAAllowed, avp.getData(), true);
    }

    /**
     * Tests whether there is any RelayNodeIndicator.
     */
    public boolean containsRelayNodeIndicator() {
        return _data.getContainer().contains(S6a_r11AttributeName.RelayNodeIndicator);
    }

    /**
     * Gets the RelayNodeIndicator.
     */
    public RelayNodeIndicator getRelayNodeIndicator() throws NoSuchAttributeException {
        return (RelayNodeIndicator)_data.getContainer().get(S6a_r11AttributeName.RelayNodeIndicator, 0);
    }

    /**
     * Sets the RelayNodeIndicator.
     *
     * @param avp - the attribute value
     */
    public void setRelayNodeIndicator(RelayNodeIndicator avp) {
        _data.getContainer().add(S6a_r11AttributeName.RelayNodeIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any MDTUserConsent.
     */
    public boolean containsMDTUserConsent() {
        return _data.getContainer().contains(S6a_r11AttributeName.MDTUserConsent);
    }

    /**
     * Gets the MDTUserConsent.
     */
    public MDTUserConsent getMDTUserConsent() throws NoSuchAttributeException {
        return (MDTUserConsent)_data.getContainer().get(S6a_r11AttributeName.MDTUserConsent, 0);
    }

    /**
     * Sets the MDTUserConsent.
     *
     * @param avp - the attribute value
     */
    public void setMDTUserConsent(MDTUserConsent avp) {
        _data.getContainer().add(S6a_r11AttributeName.MDTUserConsent, avp.getData(), true);
    }

    /**
     * Tests whether there is any SubscribedVSRVCC.
     */
    public boolean containsSubscribedVSRVCC() {
        return _data.getContainer().contains(S6a_r11AttributeName.SubscribedVSRVCC);
    }

    /**
     * Gets the SubscribedVSRVCC.
     */
    public SubscribedVSRVCC getSubscribedVSRVCC() throws NoSuchAttributeException {
        return (SubscribedVSRVCC)_data.getContainer().get(S6a_r11AttributeName.SubscribedVSRVCC, 0);
    }

    /**
     * Sets the SubscribedVSRVCC.
     *
     * @param avp - the attribute value
     */
    public void setSubscribedVSRVCC(SubscribedVSRVCC avp) {
        _data.getContainer().add(S6a_r11AttributeName.SubscribedVSRVCC, avp.getData(), true);
    }

    /**
     * Tests whether there is any SubscriptionDataFlags.
     */
    public boolean containsSubscriptionDataFlags() {
        return _data.getContainer().contains(S6a_r11AttributeName.SubscriptionDataFlags);
    }

    /**
     * Gets the SubscriptionDataFlags.
     */
    public SubscriptionDataFlags getSubscriptionDataFlags() throws NoSuchAttributeException {
        return (SubscriptionDataFlags)_data.getContainer().get(S6a_r11AttributeName.SubscriptionDataFlags, 0);
    }

    /**
     * Sets the SubscriptionDataFlags.
     *
     * @param avp - the attribute value
     */
    public void setSubscriptionDataFlags(SubscriptionDataFlags avp) {
        _data.getContainer().add(S6a_r11AttributeName.SubscriptionDataFlags, avp.getData(), true);
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
        if (containsAMSISDN()) {
            sb.append("    AMSISDN:");
            try {
                sb.append(getAMSISDN()).append('\n');
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
        if (containsICSIndicator()) {
            sb.append("    ICSIndicator:");
            try {
                sb.append(getICSIndicator()).append('\n');
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
        if (containsSubscribedPeriodicRAUTAUTimer()) {
            sb.append("    SubscribedPeriodicRAUTAUTimer:");
            try {
                sb.append(getSubscribedPeriodicRAUTAUTimer()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMPSPriority()) {
            sb.append("    MPSPriority:");
            try {
                sb.append(getMPSPriority()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVPLMNLIPAAllowed()) {
            sb.append("    VPLMNLIPAAllowed:");
            try {
                sb.append(getVPLMNLIPAAllowed()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRelayNodeIndicator()) {
            sb.append("    RelayNodeIndicator:");
            try {
                sb.append(getRelayNodeIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMDTUserConsent()) {
            sb.append("    MDTUserConsent:");
            try {
                sb.append(getMDTUserConsent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSubscribedVSRVCC()) {
            sb.append("    SubscribedVSRVCC:");
            try {
                sb.append(getSubscribedVSRVCC()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSubscriptionDataFlags()) {
            sb.append("    SubscriptionDataFlags:");
            try {
                sb.append(getSubscriptionDataFlags()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
