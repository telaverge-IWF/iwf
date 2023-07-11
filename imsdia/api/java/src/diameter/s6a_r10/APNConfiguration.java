package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The APN-Configuration AVP is of type Grouped. It contains the information related
 * to the user's subscribed APN configurations.
 */
public class APNConfiguration extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new APNConfiguration.
     */
    public APNConfiguration() {}

    APNConfiguration(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ContextIdentifier.
     */
    public ContextIdentifier getContextIdentifier() throws NoSuchAttributeException {
        return (ContextIdentifier)_data.getContainer().get(S6a_r10AttributeName.ContextIdentifier, 0);
    }

    /**
     * Sets the ContextIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setContextIdentifier(ContextIdentifier avp) {
        _data.getContainer().add(S6a_r10AttributeName.ContextIdentifier, avp.getData(), true);
    }

    /**
     * Gets the PDNType.
     */
    public PDNType getPDNType() throws NoSuchAttributeException {
        return (PDNType)_data.getContainer().get(S6a_r10AttributeName.PDNType, 0);
    }

    /**
     * Sets the PDNType.
     *
     * @param avp - the attribute value
     */
    public void setPDNType(PDNType avp) {
        _data.getContainer().add(S6a_r10AttributeName.PDNType, avp.getData(), true);
    }

    /**
     * Gets the ServiceSelection.
     */
    public ServiceSelection getServiceSelection() throws NoSuchAttributeException {
        return (ServiceSelection)_data.getContainer().get(S6a_r10AttributeName.ServiceSelection, 0);
    }

    /**
     * Sets the ServiceSelection.
     *
     * @param avp - the attribute value
     */
    public void setServiceSelection(ServiceSelection avp) {
        _data.getContainer().add(S6a_r10AttributeName.ServiceSelection, avp.getData(), true);
    }

    /**
     * Returns number of ServedPartyIPAddress instances.
     */
    public int countServedPartyIPAddress() {
        return _data.getContainer().count(S6a_r10AttributeName.ServedPartyIPAddress);
    }

    /**
     * Gets one ServedPartyIPAddress.
     *
     * @param index - the index of the attribute to return
     */
    public ServedPartyIPAddress getServedPartyIPAddress(int index) throws NoSuchAttributeException {
        return (ServedPartyIPAddress)_data.getContainer().get(S6a_r10AttributeName.ServedPartyIPAddress, index);
    }

    /**
     * Adds one ServedPartyIPAddress.
     *
     * @param avp - the attribute value
     */
    public void addServedPartyIPAddress(ServedPartyIPAddress avp) {
        _data.getContainer().add(S6a_r10AttributeName.ServedPartyIPAddress, avp.getData(), false);
    }

    /**
     * Tests whether there is any EPSSubscribedQoSProfile.
     */
    public boolean containsEPSSubscribedQoSProfile() {
        return _data.getContainer().contains(S6a_r10AttributeName.EPSSubscribedQoSProfile);
    }

    /**
     * Gets the EPSSubscribedQoSProfile.
     */
    public EPSSubscribedQoSProfile getEPSSubscribedQoSProfile() throws NoSuchAttributeException {
        return (EPSSubscribedQoSProfile)_data.getContainer().get(S6a_r10AttributeName.EPSSubscribedQoSProfile, 0);
    }

    /**
     * Sets the EPSSubscribedQoSProfile.
     *
     * @param avp - the attribute value
     */
    public void setEPSSubscribedQoSProfile(EPSSubscribedQoSProfile avp) {
        _data.getContainer().add(S6a_r10AttributeName.EPSSubscribedQoSProfile, avp.getData(), true);
    }

    /**
     * Tests whether there is any VPLMNDynamicAddressAllowed.
     */
    public boolean containsVPLMNDynamicAddressAllowed() {
        return _data.getContainer().contains(S6a_r10AttributeName.VPLMNDynamicAddressAllowed);
    }

    /**
     * Gets the VPLMNDynamicAddressAllowed.
     */
    public VPLMNDynamicAddressAllowed getVPLMNDynamicAddressAllowed() throws NoSuchAttributeException {
        return (VPLMNDynamicAddressAllowed)_data.getContainer().get(S6a_r10AttributeName.VPLMNDynamicAddressAllowed, 0);
    }

    /**
     * Sets the VPLMNDynamicAddressAllowed.
     *
     * @param avp - the attribute value
     */
    public void setVPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed avp) {
        _data.getContainer().add(S6a_r10AttributeName.VPLMNDynamicAddressAllowed, avp.getData(), true);
    }

    /**
     * Tests whether there is any MIP6AgentInfo.
     */
    public boolean containsMIP6AgentInfo() {
        return _data.getContainer().contains(S6a_r10AttributeName.MIP6AgentInfo);
    }

    /**
     * Gets the MIP6AgentInfo.
     */
    public MIP6AgentInfo getMIP6AgentInfo() throws NoSuchAttributeException {
        return (MIP6AgentInfo)_data.getContainer().get(S6a_r10AttributeName.MIP6AgentInfo, 0);
    }

    /**
     * Sets the MIP6AgentInfo.
     *
     * @param avp - the attribute value
     */
    public void setMIP6AgentInfo(MIP6AgentInfo avp) {
        _data.getContainer().add(S6a_r10AttributeName.MIP6AgentInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any VisitedNetworkIdentifier.
     */
    public boolean containsVisitedNetworkIdentifier() {
        return _data.getContainer().contains(S6a_r10AttributeName.VisitedNetworkIdentifier);
    }

    /**
     * Gets the VisitedNetworkIdentifier.
     */
    public VisitedNetworkIdentifier getVisitedNetworkIdentifier() throws NoSuchAttributeException {
        return (VisitedNetworkIdentifier)_data.getContainer().get(S6a_r10AttributeName.VisitedNetworkIdentifier, 0);
    }

    /**
     * Sets the VisitedNetworkIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setVisitedNetworkIdentifier(VisitedNetworkIdentifier avp) {
        _data.getContainer().add(S6a_r10AttributeName.VisitedNetworkIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any PDNGWAllocationType.
     */
    public boolean containsPDNGWAllocationType() {
        return _data.getContainer().contains(S6a_r10AttributeName.PDNGWAllocationType);
    }

    /**
     * Gets the PDNGWAllocationType.
     */
    public PDNGWAllocationType getPDNGWAllocationType() throws NoSuchAttributeException {
        return (PDNGWAllocationType)_data.getContainer().get(S6a_r10AttributeName.PDNGWAllocationType, 0);
    }

    /**
     * Sets the PDNGWAllocationType.
     *
     * @param avp - the attribute value
     */
    public void setPDNGWAllocationType(PDNGWAllocationType avp) {
        _data.getContainer().add(S6a_r10AttributeName.PDNGWAllocationType, avp.getData(), true);
    }

    /**
     * Tests whether there is any S6a3GPPChargingCharacteristics.
     */
    public boolean containsS6a3GPPChargingCharacteristics() {
        return _data.getContainer().contains(S6a_r10AttributeName.S6a3GPPChargingCharacteristics);
    }

    /**
     * Gets the S6a3GPPChargingCharacteristics.
     */
    public S6a3GPPChargingCharacteristics getS6a3GPPChargingCharacteristics() throws NoSuchAttributeException {
        return (S6a3GPPChargingCharacteristics)_data.getContainer().get(S6a_r10AttributeName.S6a3GPPChargingCharacteristics, 0);
    }

    /**
     * Sets the S6a3GPPChargingCharacteristics.
     *
     * @param avp - the attribute value
     */
    public void setS6a3GPPChargingCharacteristics(S6a3GPPChargingCharacteristics avp) {
        _data.getContainer().add(S6a_r10AttributeName.S6a3GPPChargingCharacteristics, avp.getData(), true);
    }

    /**
     * Tests whether there is any AMBR.
     */
    public boolean containsAMBR() {
        return _data.getContainer().contains(S6a_r10AttributeName.AMBR);
    }

    /**
     * Gets the AMBR.
     */
    public AMBR getAMBR() throws NoSuchAttributeException {
        return (AMBR)_data.getContainer().get(S6a_r10AttributeName.AMBR, 0);
    }

    /**
     * Sets the AMBR.
     *
     * @param avp - the attribute value
     */
    public void setAMBR(AMBR avp) {
        _data.getContainer().add(S6a_r10AttributeName.AMBR, avp.getData(), true);
    }

    /**
     * Returns number of SpecificAPNInfo instances.
     */
    public int countSpecificAPNInfo() {
        return _data.getContainer().count(S6a_r10AttributeName.SpecificAPNInfo);
    }

    /**
     * Gets one SpecificAPNInfo.
     *
     * @param index - the index of the attribute to return
     */
    public SpecificAPNInfo getSpecificAPNInfo(int index) throws NoSuchAttributeException {
        return (SpecificAPNInfo)_data.getContainer().get(S6a_r10AttributeName.SpecificAPNInfo, index);
    }

    /**
     * Adds one SpecificAPNInfo.
     *
     * @param avp - the attribute value
     */
    public void addSpecificAPNInfo(SpecificAPNInfo avp) {
        _data.getContainer().add(S6a_r10AttributeName.SpecificAPNInfo, avp.getData(), false);
    }

    /**
     * Tests whether there is any APNOIReplacement.
     */
    public boolean containsAPNOIReplacement() {
        return _data.getContainer().contains(S6a_r10AttributeName.APNOIReplacement);
    }

    /**
     * Gets the APNOIReplacement.
     */
    public APNOIReplacement getAPNOIReplacement() throws NoSuchAttributeException {
        return (APNOIReplacement)_data.getContainer().get(S6a_r10AttributeName.APNOIReplacement, 0);
    }

    /**
     * Sets the APNOIReplacement.
     *
     * @param avp - the attribute value
     */
    public void setAPNOIReplacement(APNOIReplacement avp) {
        _data.getContainer().add(S6a_r10AttributeName.APNOIReplacement, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPTOPermission.
     */
    public boolean containsSIPTOPermission() {
        return _data.getContainer().contains(S6a_r10AttributeName.SIPTOPermission);
    }

    /**
     * Gets the SIPTOPermission.
     */
    public SIPTOPermission getSIPTOPermission() throws NoSuchAttributeException {
        return (SIPTOPermission)_data.getContainer().get(S6a_r10AttributeName.SIPTOPermission, 0);
    }

    /**
     * Sets the SIPTOPermission.
     *
     * @param avp - the attribute value
     */
    public void setSIPTOPermission(SIPTOPermission avp) {
        _data.getContainer().add(S6a_r10AttributeName.SIPTOPermission, avp.getData(), true);
    }

    /**
     * Tests whether there is any LIPAPermission.
     */
    public boolean containsLIPAPermission() {
        return _data.getContainer().contains(S6a_r10AttributeName.LIPAPermission);
    }

    /**
     * Gets the LIPAPermission.
     */
    public LIPAPermission getLIPAPermission() throws NoSuchAttributeException {
        return (LIPAPermission)_data.getContainer().get(S6a_r10AttributeName.LIPAPermission, 0);
    }

    /**
     * Sets the LIPAPermission.
     *
     * @param avp - the attribute value
     */
    public void setLIPAPermission(LIPAPermission avp) {
        _data.getContainer().add(S6a_r10AttributeName.LIPAPermission, avp.getData(), true);
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
        sb.append("    ContextIdentifier:");
            try {
                sb.append(getContextIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    PDNType:");
            try {
                sb.append(getPDNType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ServiceSelection:");
            try {
                sb.append(getServiceSelection()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        for (int i = 0; i < countServedPartyIPAddress(); ++i) {
            sb.append("    ServedPartyIPAddress:");
            try {
                sb.append(getServedPartyIPAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEPSSubscribedQoSProfile()) {
            sb.append("    EPSSubscribedQoSProfile:");
            try {
                sb.append(getEPSSubscribedQoSProfile()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVPLMNDynamicAddressAllowed()) {
            sb.append("    VPLMNDynamicAddressAllowed:");
            try {
                sb.append(getVPLMNDynamicAddressAllowed()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMIP6AgentInfo()) {
            sb.append("    MIP6AgentInfo:");
            try {
                sb.append(getMIP6AgentInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVisitedNetworkIdentifier()) {
            sb.append("    VisitedNetworkIdentifier:");
            try {
                sb.append(getVisitedNetworkIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPDNGWAllocationType()) {
            sb.append("    PDNGWAllocationType:");
            try {
                sb.append(getPDNGWAllocationType()).append('\n');
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
        for (int i = 0; i < countSpecificAPNInfo(); ++i) {
            sb.append("    SpecificAPNInfo:");
            try {
                sb.append(getSpecificAPNInfo(i)).append('\n');
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
        if (containsSIPTOPermission()) {
            sb.append("    SIPTOPermission:");
            try {
                sb.append(getSIPTOPermission()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLIPAPermission()) {
            sb.append("    LIPAPermission:");
            try {
                sb.append(getLIPAPermission()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
