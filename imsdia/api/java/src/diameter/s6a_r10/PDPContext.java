package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class PDPContext extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new PDPContext.
     */
    public PDPContext() {}

    PDPContext(com.intellinet.diameter.GroupedData data) {
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
     * Gets the PDPType.
     */
    public PDPType getPDPType() throws NoSuchAttributeException {
        return (PDPType)_data.getContainer().get(S6a_r10AttributeName.PDPType, 0);
    }

    /**
     * Sets the PDPType.
     *
     * @param avp - the attribute value
     */
    public void setPDPType(PDPType avp) {
        _data.getContainer().add(S6a_r10AttributeName.PDPType, avp.getData(), true);
    }

    /**
     * Gets the QoSSubscribed.
     */
    public QoSSubscribed getQoSSubscribed() throws NoSuchAttributeException {
        return (QoSSubscribed)_data.getContainer().get(S6a_r10AttributeName.QoSSubscribed, 0);
    }

    /**
     * Sets the QoSSubscribed.
     *
     * @param avp - the attribute value
     */
    public void setQoSSubscribed(QoSSubscribed avp) {
        _data.getContainer().add(S6a_r10AttributeName.QoSSubscribed, avp.getData(), true);
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
     * Tests whether there is any PDPAddress.
     */
    public boolean containsPDPAddress() {
        return _data.getContainer().contains(S6a_r10AttributeName.PDPAddress);
    }

    /**
     * Gets the PDPAddress.
     */
    public PDPAddress getPDPAddress() throws NoSuchAttributeException {
        return (PDPAddress)_data.getContainer().get(S6a_r10AttributeName.PDPAddress, 0);
    }

    /**
     * Sets the PDPAddress.
     *
     * @param avp - the attribute value
     */
    public void setPDPAddress(PDPAddress avp) {
        _data.getContainer().add(S6a_r10AttributeName.PDPAddress, avp.getData(), true);
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
     * Tests whether there is any ExtPDPType.
     */
    public boolean containsExtPDPType() {
        return _data.getContainer().contains(S6a_r10AttributeName.ExtPDPType);
    }

    /**
     * Gets the ExtPDPType.
     */
    public ExtPDPType getExtPDPType() throws NoSuchAttributeException {
        return (ExtPDPType)_data.getContainer().get(S6a_r10AttributeName.ExtPDPType, 0);
    }

    /**
     * Sets the ExtPDPType.
     *
     * @param avp - the attribute value
     */
    public void setExtPDPType(ExtPDPType avp) {
        _data.getContainer().add(S6a_r10AttributeName.ExtPDPType, avp.getData(), true);
    }

    /**
     * Tests whether there is any ExtPDPAddress.
     */
    public boolean containsExtPDPAddress() {
        return _data.getContainer().contains(S6a_r10AttributeName.ExtPDPAddress);
    }

    /**
     * Gets the ExtPDPAddress.
     */
    public ExtPDPAddress getExtPDPAddress() throws NoSuchAttributeException {
        return (ExtPDPAddress)_data.getContainer().get(S6a_r10AttributeName.ExtPDPAddress, 0);
    }

    /**
     * Sets the ExtPDPAddress.
     *
     * @param avp - the attribute value
     */
    public void setExtPDPAddress(ExtPDPAddress avp) {
        _data.getContainer().add(S6a_r10AttributeName.ExtPDPAddress, avp.getData(), true);
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
        sb.append("    PDPType:");
            try {
                sb.append(getPDPType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    QoSSubscribed:");
            try {
                sb.append(getQoSSubscribed()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ServiceSelection:");
            try {
                sb.append(getServiceSelection()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsPDPAddress()) {
            sb.append("    PDPAddress:");
            try {
                sb.append(getPDPAddress()).append('\n');
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
        if (containsS6a3GPPChargingCharacteristics()) {
            sb.append("    S6a3GPPChargingCharacteristics:");
            try {
                sb.append(getS6a3GPPChargingCharacteristics()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsExtPDPType()) {
            sb.append("    ExtPDPType:");
            try {
                sb.append(getExtPDPType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsExtPDPAddress()) {
            sb.append("    ExtPDPAddress:");
            try {
                sb.append(getExtPDPAddress()).append('\n');
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
