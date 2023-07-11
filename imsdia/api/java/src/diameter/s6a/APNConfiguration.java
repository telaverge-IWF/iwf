package diameter.s6a;

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
        return (ContextIdentifier)_data.getContainer().get(S6aAttributeName.ContextIdentifier, 0);
    }

    /**
     * Sets the ContextIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setContextIdentifier(ContextIdentifier avp) {
        _data.getContainer().add(S6aAttributeName.ContextIdentifier, avp.getData(), true);
    }

    /**
     * Gets the PDNType.
     */
    public PDNType getPDNType() throws NoSuchAttributeException {
        return (PDNType)_data.getContainer().get(S6aAttributeName.PDNType, 0);
    }

    /**
     * Sets the PDNType.
     *
     * @param avp - the attribute value
     */
    public void setPDNType(PDNType avp) {
        _data.getContainer().add(S6aAttributeName.PDNType, avp.getData(), true);
    }

    /**
     * Gets the ServiceSelection.
     */
    public ServiceSelection getServiceSelection() throws NoSuchAttributeException {
        return (ServiceSelection)_data.getContainer().get(S6aAttributeName.ServiceSelection, 0);
    }

    /**
     * Sets the ServiceSelection.
     *
     * @param avp - the attribute value
     */
    public void setServiceSelection(ServiceSelection avp) {
        _data.getContainer().add(S6aAttributeName.ServiceSelection, avp.getData(), true);
    }

    /**
     * Returns number of ServedPartyIPAddress instances.
     */
    public int countServedPartyIPAddress() {
        return _data.getContainer().count(S6aAttributeName.ServedPartyIPAddress);
    }

    /**
     * Gets one ServedPartyIPAddress.
     *
     * @param index - the index of the attribute to return
     */
    public ServedPartyIPAddress getServedPartyIPAddress(int index) throws NoSuchAttributeException {
        return (ServedPartyIPAddress)_data.getContainer().get(S6aAttributeName.ServedPartyIPAddress, index);
    }

    /**
     * Adds one ServedPartyIPAddress.
     *
     * @param avp - the attribute value
     */
    public void addServedPartyIPAddress(ServedPartyIPAddress avp) {
        _data.getContainer().add(S6aAttributeName.ServedPartyIPAddress, avp.getData(), false);
    }

    /**
     * Tests whether there is any EPSSubscribedQoSProfile.
     */
    public boolean containsEPSSubscribedQoSProfile() {
        return _data.getContainer().contains(S6aAttributeName.EPSSubscribedQoSProfile);
    }

    /**
     * Gets the EPSSubscribedQoSProfile.
     */
    public EPSSubscribedQoSProfile getEPSSubscribedQoSProfile() throws NoSuchAttributeException {
        return (EPSSubscribedQoSProfile)_data.getContainer().get(S6aAttributeName.EPSSubscribedQoSProfile, 0);
    }

    /**
     * Sets the EPSSubscribedQoSProfile.
     *
     * @param avp - the attribute value
     */
    public void setEPSSubscribedQoSProfile(EPSSubscribedQoSProfile avp) {
        _data.getContainer().add(S6aAttributeName.EPSSubscribedQoSProfile, avp.getData(), true);
    }

    /**
     * Tests whether there is any VPLMNDynamicAddressAllowed.
     */
    public boolean containsVPLMNDynamicAddressAllowed() {
        return _data.getContainer().contains(S6aAttributeName.VPLMNDynamicAddressAllowed);
    }

    /**
     * Gets the VPLMNDynamicAddressAllowed.
     */
    public VPLMNDynamicAddressAllowed getVPLMNDynamicAddressAllowed() throws NoSuchAttributeException {
        return (VPLMNDynamicAddressAllowed)_data.getContainer().get(S6aAttributeName.VPLMNDynamicAddressAllowed, 0);
    }

    /**
     * Sets the VPLMNDynamicAddressAllowed.
     *
     * @param avp - the attribute value
     */
    public void setVPLMNDynamicAddressAllowed(VPLMNDynamicAddressAllowed avp) {
        _data.getContainer().add(S6aAttributeName.VPLMNDynamicAddressAllowed, avp.getData(), true);
    }

    /**
     * Tests whether there is any MIP6AgentInfo.
     */
    public boolean containsMIP6AgentInfo() {
        return _data.getContainer().contains(S6aAttributeName.MIP6AgentInfo);
    }

    /**
     * Gets the MIP6AgentInfo.
     */
    public MIP6AgentInfo getMIP6AgentInfo() throws NoSuchAttributeException {
        return (MIP6AgentInfo)_data.getContainer().get(S6aAttributeName.MIP6AgentInfo, 0);
    }

    /**
     * Sets the MIP6AgentInfo.
     *
     * @param avp - the attribute value
     */
    public void setMIP6AgentInfo(MIP6AgentInfo avp) {
        _data.getContainer().add(S6aAttributeName.MIP6AgentInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any PDNGWAllocationType.
     */
    public boolean containsPDNGWAllocationType() {
        return _data.getContainer().contains(S6aAttributeName.PDNGWAllocationType);
    }

    /**
     * Gets the PDNGWAllocationType.
     */
    public PDNGWAllocationType getPDNGWAllocationType() throws NoSuchAttributeException {
        return (PDNGWAllocationType)_data.getContainer().get(S6aAttributeName.PDNGWAllocationType, 0);
    }

    /**
     * Sets the PDNGWAllocationType.
     *
     * @param avp - the attribute value
     */
    public void setPDNGWAllocationType(PDNGWAllocationType avp) {
        _data.getContainer().add(S6aAttributeName.PDNGWAllocationType, avp.getData(), true);
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
     * Returns number of SpecificAPNInfo instances.
     */
    public int countSpecificAPNInfo() {
        return _data.getContainer().count(S6aAttributeName.SpecificAPNInfo);
    }

    /**
     * Gets one SpecificAPNInfo.
     *
     * @param index - the index of the attribute to return
     */
    public SpecificAPNInfo getSpecificAPNInfo(int index) throws NoSuchAttributeException {
        return (SpecificAPNInfo)_data.getContainer().get(S6aAttributeName.SpecificAPNInfo, index);
    }

    /**
     * Adds one SpecificAPNInfo.
     *
     * @param avp - the attribute value
     */
    public void addSpecificAPNInfo(SpecificAPNInfo avp) {
        _data.getContainer().add(S6aAttributeName.SpecificAPNInfo, avp.getData(), false);
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
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
