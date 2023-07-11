package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * PS-Information AVP is of type Grouped. Its purpose is to allow the transmission of
 * additional PS service specific information elements.
   
 */
public class PSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new PSInformation.
     */
    public PSInformation() {}

    PSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any Ro3GPPChargingId.
     */
    public boolean containsRo3GPPChargingId() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPChargingId);
    }

    /**
     * Gets the Ro3GPPChargingId.
     */
    public Ro3GPPChargingId getRo3GPPChargingId() throws NoSuchAttributeException {
        return (Ro3GPPChargingId)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPChargingId, 0);
    }

    /**
     * Sets the Ro3GPPChargingId.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPChargingId(Ro3GPPChargingId avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPChargingId, avp.getData(), true);
    }

    /**
     * Tests whether there is any PDNConnectionID.
     */
    public boolean containsPDNConnectionID() {
        return _data.getContainer().contains(Ro_r10AttributeName.PDNConnectionID);
    }

    /**
     * Gets the PDNConnectionID.
     */
    public PDNConnectionID getPDNConnectionID() throws NoSuchAttributeException {
        return (PDNConnectionID)_data.getContainer().get(Ro_r10AttributeName.PDNConnectionID, 0);
    }

    /**
     * Sets the PDNConnectionID.
     *
     * @param avp - the attribute value
     */
    public void setPDNConnectionID(PDNConnectionID avp) {
        _data.getContainer().add(Ro_r10AttributeName.PDNConnectionID, avp.getData(), true);
    }

    /**
     * Tests whether there is any NodeId.
     */
    public boolean containsNodeId() {
        return _data.getContainer().contains(Ro_r10AttributeName.NodeId);
    }

    /**
     * Gets the NodeId.
     */
    public NodeId getNodeId() throws NoSuchAttributeException {
        return (NodeId)_data.getContainer().get(Ro_r10AttributeName.NodeId, 0);
    }

    /**
     * Sets the NodeId.
     *
     * @param avp - the attribute value
     */
    public void setNodeId(NodeId avp) {
        _data.getContainer().add(Ro_r10AttributeName.NodeId, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPPDPType.
     */
    public boolean containsRo3GPPPDPType() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPPDPType);
    }

    /**
     * Gets the Ro3GPPPDPType.
     */
    public Ro3GPPPDPType getRo3GPPPDPType() throws NoSuchAttributeException {
        return (Ro3GPPPDPType)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPPDPType, 0);
    }

    /**
     * Sets the Ro3GPPPDPType.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPPDPType(Ro3GPPPDPType avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPPDPType, avp.getData(), true);
    }

    /**
     * Returns number of PDPAddress instances.
     */
    public int countPDPAddress() {
        return _data.getContainer().count(Ro_r10AttributeName.PDPAddress);
    }

    /**
     * Gets one PDPAddress.
     *
     * @param index - the index of the attribute to return
     */
    public PDPAddress getPDPAddress(int index) throws NoSuchAttributeException {
        return (PDPAddress)_data.getContainer().get(Ro_r10AttributeName.PDPAddress, index);
    }

    /**
     * Adds one PDPAddress.
     *
     * @param avp - the attribute value
     */
    public void addPDPAddress(PDPAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.PDPAddress, avp.getData(), false);
    }

    /**
     * Tests whether there is any PDPAddressPrefixLength.
     */
    public boolean containsPDPAddressPrefixLength() {
        return _data.getContainer().contains(Ro_r10AttributeName.PDPAddressPrefixLength);
    }

    /**
     * Gets the PDPAddressPrefixLength.
     */
    public PDPAddressPrefixLength getPDPAddressPrefixLength() throws NoSuchAttributeException {
        return (PDPAddressPrefixLength)_data.getContainer().get(Ro_r10AttributeName.PDPAddressPrefixLength, 0);
    }

    /**
     * Sets the PDPAddressPrefixLength.
     *
     * @param avp - the attribute value
     */
    public void setPDPAddressPrefixLength(PDPAddressPrefixLength avp) {
        _data.getContainer().add(Ro_r10AttributeName.PDPAddressPrefixLength, avp.getData(), true);
    }

    /**
     * Tests whether there is any DynamicAddressFlag.
     */
    public boolean containsDynamicAddressFlag() {
        return _data.getContainer().contains(Ro_r10AttributeName.DynamicAddressFlag);
    }

    /**
     * Gets the DynamicAddressFlag.
     */
    public DynamicAddressFlag getDynamicAddressFlag() throws NoSuchAttributeException {
        return (DynamicAddressFlag)_data.getContainer().get(Ro_r10AttributeName.DynamicAddressFlag, 0);
    }

    /**
     * Sets the DynamicAddressFlag.
     *
     * @param avp - the attribute value
     */
    public void setDynamicAddressFlag(DynamicAddressFlag avp) {
        _data.getContainer().add(Ro_r10AttributeName.DynamicAddressFlag, avp.getData(), true);
    }

    /**
     * Tests whether there is any DynamicAddressFlagExtension.
     */
    public boolean containsDynamicAddressFlagExtension() {
        return _data.getContainer().contains(Ro_r10AttributeName.DynamicAddressFlagExtension);
    }

    /**
     * Gets the DynamicAddressFlagExtension.
     */
    public DynamicAddressFlagExtension getDynamicAddressFlagExtension() throws NoSuchAttributeException {
        return (DynamicAddressFlagExtension)_data.getContainer().get(Ro_r10AttributeName.DynamicAddressFlagExtension, 0);
    }

    /**
     * Sets the DynamicAddressFlagExtension.
     *
     * @param avp - the attribute value
     */
    public void setDynamicAddressFlagExtension(DynamicAddressFlagExtension avp) {
        _data.getContainer().add(Ro_r10AttributeName.DynamicAddressFlagExtension, avp.getData(), true);
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

    /**
     * Tests whether there is any SGSNAddress.
     */
    public boolean containsSGSNAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.SGSNAddress);
    }

    /**
     * Gets the SGSNAddress.
     */
    public SGSNAddress getSGSNAddress() throws NoSuchAttributeException {
        return (SGSNAddress)_data.getContainer().get(Ro_r10AttributeName.SGSNAddress, 0);
    }

    /**
     * Sets the SGSNAddress.
     *
     * @param avp - the attribute value
     */
    public void setSGSNAddress(SGSNAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.SGSNAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any GGSNAddress.
     */
    public boolean containsGGSNAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.GGSNAddress);
    }

    /**
     * Gets the GGSNAddress.
     */
    public GGSNAddress getGGSNAddress() throws NoSuchAttributeException {
        return (GGSNAddress)_data.getContainer().get(Ro_r10AttributeName.GGSNAddress, 0);
    }

    /**
     * Sets the GGSNAddress.
     *
     * @param avp - the attribute value
     */
    public void setGGSNAddress(GGSNAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.GGSNAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any SGWAddress.
     */
    public boolean containsSGWAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.SGWAddress);
    }

    /**
     * Gets the SGWAddress.
     */
    public SGWAddress getSGWAddress() throws NoSuchAttributeException {
        return (SGWAddress)_data.getContainer().get(Ro_r10AttributeName.SGWAddress, 0);
    }

    /**
     * Sets the SGWAddress.
     *
     * @param avp - the attribute value
     */
    public void setSGWAddress(SGWAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.SGWAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any CGAddress.
     */
    public boolean containsCGAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.CGAddress);
    }

    /**
     * Gets the CGAddress.
     */
    public CGAddress getCGAddress() throws NoSuchAttributeException {
        return (CGAddress)_data.getContainer().get(Ro_r10AttributeName.CGAddress, 0);
    }

    /**
     * Sets the CGAddress.
     *
     * @param avp - the attribute value
     */
    public void setCGAddress(CGAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.CGAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServingNodeType.
     */
    public boolean containsServingNodeType() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServingNodeType);
    }

    /**
     * Gets the ServingNodeType.
     */
    public ServingNodeType getServingNodeType() throws NoSuchAttributeException {
        return (ServingNodeType)_data.getContainer().get(Ro_r10AttributeName.ServingNodeType, 0);
    }

    /**
     * Sets the ServingNodeType.
     *
     * @param avp - the attribute value
     */
    public void setServingNodeType(ServingNodeType avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServingNodeType, avp.getData(), true);
    }

    /**
     * Tests whether there is any SGWChange.
     */
    public boolean containsSGWChange() {
        return _data.getContainer().contains(Ro_r10AttributeName.SGWChange);
    }

    /**
     * Gets the SGWChange.
     */
    public SGWChange getSGWChange() throws NoSuchAttributeException {
        return (SGWChange)_data.getContainer().get(Ro_r10AttributeName.SGWChange, 0);
    }

    /**
     * Sets the SGWChange.
     *
     * @param avp - the attribute value
     */
    public void setSGWChange(SGWChange avp) {
        _data.getContainer().add(Ro_r10AttributeName.SGWChange, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPIMSIMCCMNC.
     */
    public boolean containsRo3GPPIMSIMCCMNC() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPIMSIMCCMNC);
    }

    /**
     * Gets the Ro3GPPIMSIMCCMNC.
     */
    public Ro3GPPIMSIMCCMNC getRo3GPPIMSIMCCMNC() throws NoSuchAttributeException {
        return (Ro3GPPIMSIMCCMNC)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPIMSIMCCMNC, 0);
    }

    /**
     * Sets the Ro3GPPIMSIMCCMNC.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPIMSIMCCMNC(Ro3GPPIMSIMCCMNC avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPIMSIMCCMNC, avp.getData(), true);
    }

    /**
     * Tests whether there is any IMSIUnauthenticatedFlag.
     */
    public boolean containsIMSIUnauthenticatedFlag() {
        return _data.getContainer().contains(Ro_r10AttributeName.IMSIUnauthenticatedFlag);
    }

    /**
     * Gets the IMSIUnauthenticatedFlag.
     */
    public IMSIUnauthenticatedFlag getIMSIUnauthenticatedFlag() throws NoSuchAttributeException {
        return (IMSIUnauthenticatedFlag)_data.getContainer().get(Ro_r10AttributeName.IMSIUnauthenticatedFlag, 0);
    }

    /**
     * Sets the IMSIUnauthenticatedFlag.
     *
     * @param avp - the attribute value
     */
    public void setIMSIUnauthenticatedFlag(IMSIUnauthenticatedFlag avp) {
        _data.getContainer().add(Ro_r10AttributeName.IMSIUnauthenticatedFlag, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPGGSNMCCMNC.
     */
    public boolean containsRo3GPPGGSNMCCMNC() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPGGSNMCCMNC);
    }

    /**
     * Gets the Ro3GPPGGSNMCCMNC.
     */
    public Ro3GPPGGSNMCCMNC getRo3GPPGGSNMCCMNC() throws NoSuchAttributeException {
        return (Ro3GPPGGSNMCCMNC)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPGGSNMCCMNC, 0);
    }

    /**
     * Sets the Ro3GPPGGSNMCCMNC.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPGGSNMCCMNC(Ro3GPPGGSNMCCMNC avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPGGSNMCCMNC, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPNSAPI.
     */
    public boolean containsRo3GPPNSAPI() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPNSAPI);
    }

    /**
     * Gets the Ro3GPPNSAPI.
     */
    public Ro3GPPNSAPI getRo3GPPNSAPI() throws NoSuchAttributeException {
        return (Ro3GPPNSAPI)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPNSAPI, 0);
    }

    /**
     * Sets the Ro3GPPNSAPI.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPNSAPI(Ro3GPPNSAPI avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPNSAPI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CalledStationId.
     */
    public boolean containsCalledStationId() {
        return _data.getContainer().contains(diameter.nasreq.NasreqAttributeName.CalledStationId);
    }

    /**
     * Gets the CalledStationId.
     */
    public diameter.nasreq.CalledStationId getCalledStationId() throws NoSuchAttributeException {
        return (diameter.nasreq.CalledStationId)_data.getContainer().get(diameter.nasreq.NasreqAttributeName.CalledStationId, 0);
    }

    /**
     * Sets the CalledStationId.
     *
     * @param avp - the attribute value
     */
    public void setCalledStationId(diameter.nasreq.CalledStationId avp) {
        _data.getContainer().add(diameter.nasreq.NasreqAttributeName.CalledStationId, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPSessionStopIndicator.
     */
    public boolean containsRo3GPPSessionStopIndicator() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPSessionStopIndicator);
    }

    /**
     * Gets the Ro3GPPSessionStopIndicator.
     */
    public Ro3GPPSessionStopIndicator getRo3GPPSessionStopIndicator() throws NoSuchAttributeException {
        return (Ro3GPPSessionStopIndicator)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPSessionStopIndicator, 0);
    }

    /**
     * Sets the Ro3GPPSessionStopIndicator.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPSessionStopIndicator(Ro3GPPSessionStopIndicator avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPSessionStopIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPSelectionMode.
     */
    public boolean containsRo3GPPSelectionMode() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPSelectionMode);
    }

    /**
     * Gets the Ro3GPPSelectionMode.
     */
    public Ro3GPPSelectionMode getRo3GPPSelectionMode() throws NoSuchAttributeException {
        return (Ro3GPPSelectionMode)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPSelectionMode, 0);
    }

    /**
     * Sets the Ro3GPPSelectionMode.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPSelectionMode(Ro3GPPSelectionMode avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPSelectionMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPChargingCharacteristics.
     */
    public boolean containsRo3GPPChargingCharacteristics() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPChargingCharacteristics);
    }

    /**
     * Gets the Ro3GPPChargingCharacteristics.
     */
    public Ro3GPPChargingCharacteristics getRo3GPPChargingCharacteristics() throws NoSuchAttributeException {
        return (Ro3GPPChargingCharacteristics)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPChargingCharacteristics, 0);
    }

    /**
     * Sets the Ro3GPPChargingCharacteristics.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPChargingCharacteristics(Ro3GPPChargingCharacteristics avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPChargingCharacteristics, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPSGSNMCCMNC.
     */
    public boolean containsRo3GPPSGSNMCCMNC() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPSGSNMCCMNC);
    }

    /**
     * Gets the Ro3GPPSGSNMCCMNC.
     */
    public Ro3GPPSGSNMCCMNC getRo3GPPSGSNMCCMNC() throws NoSuchAttributeException {
        return (Ro3GPPSGSNMCCMNC)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPSGSNMCCMNC, 0);
    }

    /**
     * Sets the Ro3GPPSGSNMCCMNC.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPSGSNMCCMNC(Ro3GPPSGSNMCCMNC avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPSGSNMCCMNC, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPMSTimeZone.
     */
    public boolean containsRo3GPPMSTimeZone() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPMSTimeZone);
    }

    /**
     * Gets the Ro3GPPMSTimeZone.
     */
    public Ro3GPPMSTimeZone getRo3GPPMSTimeZone() throws NoSuchAttributeException {
        return (Ro3GPPMSTimeZone)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPMSTimeZone, 0);
    }

    /**
     * Sets the Ro3GPPMSTimeZone.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPMSTimeZone(Ro3GPPMSTimeZone avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPMSTimeZone, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChargingRuleBaseName.
     */
    public boolean containsChargingRuleBaseName() {
        return _data.getContainer().contains(Ro_r10AttributeName.ChargingRuleBaseName);
    }

    /**
     * Gets the ChargingRuleBaseName.
     */
    public ChargingRuleBaseName getChargingRuleBaseName() throws NoSuchAttributeException {
        return (ChargingRuleBaseName)_data.getContainer().get(Ro_r10AttributeName.ChargingRuleBaseName, 0);
    }

    /**
     * Sets the ChargingRuleBaseName.
     *
     * @param avp - the attribute value
     */
    public void setChargingRuleBaseName(ChargingRuleBaseName avp) {
        _data.getContainer().add(Ro_r10AttributeName.ChargingRuleBaseName, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPUserLocationInfo.
     */
    public boolean containsRo3GPPUserLocationInfo() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPUserLocationInfo);
    }

    /**
     * Gets the Ro3GPPUserLocationInfo.
     */
    public Ro3GPPUserLocationInfo getRo3GPPUserLocationInfo() throws NoSuchAttributeException {
        return (Ro3GPPUserLocationInfo)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPUserLocationInfo, 0);
    }

    /**
     * Sets the Ro3GPPUserLocationInfo.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPUserLocationInfo(Ro3GPPUserLocationInfo avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPUserLocationInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any UserCSGInformation.
     */
    public boolean containsUserCSGInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.UserCSGInformation);
    }

    /**
     * Gets the UserCSGInformation.
     */
    public UserCSGInformation getUserCSGInformation() throws NoSuchAttributeException {
        return (UserCSGInformation)_data.getContainer().get(Ro_r10AttributeName.UserCSGInformation, 0);
    }

    /**
     * Sets the UserCSGInformation.
     *
     * @param avp - the attribute value
     */
    public void setUserCSGInformation(UserCSGInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.UserCSGInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPP2BSID.
     */
    public boolean containsRo3GPP2BSID() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPP2BSID);
    }

    /**
     * Gets the Ro3GPP2BSID.
     */
    public Ro3GPP2BSID getRo3GPP2BSID() throws NoSuchAttributeException {
        return (Ro3GPP2BSID)_data.getContainer().get(Ro_r10AttributeName.Ro3GPP2BSID, 0);
    }

    /**
     * Sets the Ro3GPP2BSID.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPP2BSID(Ro3GPP2BSID avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPP2BSID, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPRATType.
     */
    public boolean containsRo3GPPRATType() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPRATType);
    }

    /**
     * Gets the Ro3GPPRATType.
     */
    public Ro3GPPRATType getRo3GPPRATType() throws NoSuchAttributeException {
        return (Ro3GPPRATType)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPRATType, 0);
    }

    /**
     * Sets the Ro3GPPRATType.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPRATType(Ro3GPPRATType avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPRATType, avp.getData(), true);
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
     * Tests whether there is any PDPContextType.
     */
    public boolean containsPDPContextType() {
        return _data.getContainer().contains(Ro_r10AttributeName.PDPContextType);
    }

    /**
     * Gets the PDPContextType.
     */
    public PDPContextType getPDPContextType() throws NoSuchAttributeException {
        return (PDPContextType)_data.getContainer().get(Ro_r10AttributeName.PDPContextType, 0);
    }

    /**
     * Sets the PDPContextType.
     *
     * @param avp - the attribute value
     */
    public void setPDPContextType(PDPContextType avp) {
        _data.getContainer().add(Ro_r10AttributeName.PDPContextType, avp.getData(), true);
    }

    /**
     * Tests whether there is any OfflineCharging.
     */
    public boolean containsOfflineCharging() {
        return _data.getContainer().contains(Ro_r10AttributeName.OfflineCharging);
    }

    /**
     * Gets the OfflineCharging.
     */
    public OfflineCharging getOfflineCharging() throws NoSuchAttributeException {
        return (OfflineCharging)_data.getContainer().get(Ro_r10AttributeName.OfflineCharging, 0);
    }

    /**
     * Sets the OfflineCharging.
     *
     * @param avp - the attribute value
     */
    public void setOfflineCharging(OfflineCharging avp) {
        _data.getContainer().add(Ro_r10AttributeName.OfflineCharging, avp.getData(), true);
    }

    /**
     * Returns number of TrafficDataVolumes instances.
     */
    public int countTrafficDataVolumes() {
        return _data.getContainer().count(Ro_r10AttributeName.TrafficDataVolumes);
    }

    /**
     * Gets one TrafficDataVolumes.
     *
     * @param index - the index of the attribute to return
     */
    public TrafficDataVolumes getTrafficDataVolumes(int index) throws NoSuchAttributeException {
        return (TrafficDataVolumes)_data.getContainer().get(Ro_r10AttributeName.TrafficDataVolumes, index);
    }

    /**
     * Adds one TrafficDataVolumes.
     *
     * @param avp - the attribute value
     */
    public void addTrafficDataVolumes(TrafficDataVolumes avp) {
        _data.getContainer().add(Ro_r10AttributeName.TrafficDataVolumes, avp.getData(), false);
    }

    /**
     * Returns number of ServiceDataContainer instances.
     */
    public int countServiceDataContainer() {
        return _data.getContainer().count(Ro_r10AttributeName.ServiceDataContainer);
    }

    /**
     * Gets one ServiceDataContainer.
     *
     * @param index - the index of the attribute to return
     */
    public ServiceDataContainer getServiceDataContainer(int index) throws NoSuchAttributeException {
        return (ServiceDataContainer)_data.getContainer().get(Ro_r10AttributeName.ServiceDataContainer, index);
    }

    /**
     * Adds one ServiceDataContainer.
     *
     * @param avp - the attribute value
     */
    public void addServiceDataContainer(ServiceDataContainer avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceDataContainer, avp.getData(), false);
    }

    /**
     * Tests whether there is any UserEquipmentInfo.
     */
    public boolean containsUserEquipmentInfo() {
        return _data.getContainer().contains(Ro_r10AttributeName.UserEquipmentInfo);
    }

    /**
     * Gets the UserEquipmentInfo.
     */
    public UserEquipmentInfo getUserEquipmentInfo() throws NoSuchAttributeException {
        return (UserEquipmentInfo)_data.getContainer().get(Ro_r10AttributeName.UserEquipmentInfo, 0);
    }

    /**
     * Sets the UserEquipmentInfo.
     *
     * @param avp - the attribute value
     */
    public void setUserEquipmentInfo(UserEquipmentInfo avp) {
        _data.getContainer().add(Ro_r10AttributeName.UserEquipmentInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any TerminalInformation.
     */
    public boolean containsTerminalInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.TerminalInformation);
    }

    /**
     * Gets the TerminalInformation.
     */
    public TerminalInformation getTerminalInformation() throws NoSuchAttributeException {
        return (TerminalInformation)_data.getContainer().get(Ro_r10AttributeName.TerminalInformation, 0);
    }

    /**
     * Sets the TerminalInformation.
     *
     * @param avp - the attribute value
     */
    public void setTerminalInformation(TerminalInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.TerminalInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any StartTime.
     */
    public boolean containsStartTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.StartTime);
    }

    /**
     * Gets the StartTime.
     */
    public StartTime getStartTime() throws NoSuchAttributeException {
        return (StartTime)_data.getContainer().get(Ro_r10AttributeName.StartTime, 0);
    }

    /**
     * Sets the StartTime.
     *
     * @param avp - the attribute value
     */
    public void setStartTime(StartTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.StartTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any StopTime.
     */
    public boolean containsStopTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.StopTime);
    }

    /**
     * Gets the StopTime.
     */
    public StopTime getStopTime() throws NoSuchAttributeException {
        return (StopTime)_data.getContainer().get(Ro_r10AttributeName.StopTime, 0);
    }

    /**
     * Sets the StopTime.
     *
     * @param avp - the attribute value
     */
    public void setStopTime(StopTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.StopTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChangeCondition.
     */
    public boolean containsChangeCondition() {
        return _data.getContainer().contains(Ro_r10AttributeName.ChangeCondition);
    }

    /**
     * Gets the ChangeCondition.
     */
    public ChangeCondition getChangeCondition() throws NoSuchAttributeException {
        return (ChangeCondition)_data.getContainer().get(Ro_r10AttributeName.ChangeCondition, 0);
    }

    /**
     * Sets the ChangeCondition.
     *
     * @param avp - the attribute value
     */
    public void setChangeCondition(ChangeCondition avp) {
        _data.getContainer().add(Ro_r10AttributeName.ChangeCondition, avp.getData(), true);
    }

    /**
     * Tests whether there is any Diagnostics.
     */
    public boolean containsDiagnostics() {
        return _data.getContainer().contains(Ro_r10AttributeName.Diagnostics);
    }

    /**
     * Gets the Diagnostics.
     */
    public Diagnostics getDiagnostics() throws NoSuchAttributeException {
        return (Diagnostics)_data.getContainer().get(Ro_r10AttributeName.Diagnostics, 0);
    }

    /**
     * Sets the Diagnostics.
     *
     * @param avp - the attribute value
     */
    public void setDiagnostics(Diagnostics avp) {
        _data.getContainer().add(Ro_r10AttributeName.Diagnostics, avp.getData(), true);
    }

    /**
     * Tests whether there is any LowPriorityIndicator.
     */
    public boolean containsLowPriorityIndicator() {
        return _data.getContainer().contains(Ro_r10AttributeName.LowPriorityIndicator);
    }

    /**
     * Gets the LowPriorityIndicator.
     */
    public LowPriorityIndicator getLowPriorityIndicator() throws NoSuchAttributeException {
        return (LowPriorityIndicator)_data.getContainer().get(Ro_r10AttributeName.LowPriorityIndicator, 0);
    }

    /**
     * Sets the LowPriorityIndicator.
     *
     * @param avp - the attribute value
     */
    public void setLowPriorityIndicator(LowPriorityIndicator avp) {
        _data.getContainer().add(Ro_r10AttributeName.LowPriorityIndicator, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsRo3GPPChargingId()) {
            sb.append("    Ro3GPPChargingId:");
            try {
                sb.append(getRo3GPPChargingId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPDNConnectionID()) {
            sb.append("    PDNConnectionID:");
            try {
                sb.append(getPDNConnectionID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNodeId()) {
            sb.append("    NodeId:");
            try {
                sb.append(getNodeId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPPDPType()) {
            sb.append("    Ro3GPPPDPType:");
            try {
                sb.append(getRo3GPPPDPType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countPDPAddress(); ++i) {
            sb.append("    PDPAddress:");
            try {
                sb.append(getPDPAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPDPAddressPrefixLength()) {
            sb.append("    PDPAddressPrefixLength:");
            try {
                sb.append(getPDPAddressPrefixLength()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDynamicAddressFlag()) {
            sb.append("    DynamicAddressFlag:");
            try {
                sb.append(getDynamicAddressFlag()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDynamicAddressFlagExtension()) {
            sb.append("    DynamicAddressFlagExtension:");
            try {
                sb.append(getDynamicAddressFlagExtension()).append('\n');
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
        if (containsSGSNAddress()) {
            sb.append("    SGSNAddress:");
            try {
                sb.append(getSGSNAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGGSNAddress()) {
            sb.append("    GGSNAddress:");
            try {
                sb.append(getGGSNAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSGWAddress()) {
            sb.append("    SGWAddress:");
            try {
                sb.append(getSGWAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCGAddress()) {
            sb.append("    CGAddress:");
            try {
                sb.append(getCGAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServingNodeType()) {
            sb.append("    ServingNodeType:");
            try {
                sb.append(getServingNodeType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSGWChange()) {
            sb.append("    SGWChange:");
            try {
                sb.append(getSGWChange()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPIMSIMCCMNC()) {
            sb.append("    Ro3GPPIMSIMCCMNC:");
            try {
                sb.append(getRo3GPPIMSIMCCMNC()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIMSIUnauthenticatedFlag()) {
            sb.append("    IMSIUnauthenticatedFlag:");
            try {
                sb.append(getIMSIUnauthenticatedFlag()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPGGSNMCCMNC()) {
            sb.append("    Ro3GPPGGSNMCCMNC:");
            try {
                sb.append(getRo3GPPGGSNMCCMNC()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPNSAPI()) {
            sb.append("    Ro3GPPNSAPI:");
            try {
                sb.append(getRo3GPPNSAPI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCalledStationId()) {
            sb.append("    CalledStationId:");
            try {
                sb.append(getCalledStationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPSessionStopIndicator()) {
            sb.append("    Ro3GPPSessionStopIndicator:");
            try {
                sb.append(getRo3GPPSessionStopIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPSelectionMode()) {
            sb.append("    Ro3GPPSelectionMode:");
            try {
                sb.append(getRo3GPPSelectionMode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPChargingCharacteristics()) {
            sb.append("    Ro3GPPChargingCharacteristics:");
            try {
                sb.append(getRo3GPPChargingCharacteristics()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPSGSNMCCMNC()) {
            sb.append("    Ro3GPPSGSNMCCMNC:");
            try {
                sb.append(getRo3GPPSGSNMCCMNC()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPMSTimeZone()) {
            sb.append("    Ro3GPPMSTimeZone:");
            try {
                sb.append(getRo3GPPMSTimeZone()).append('\n');
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
        if (containsRo3GPPUserLocationInfo()) {
            sb.append("    Ro3GPPUserLocationInfo:");
            try {
                sb.append(getRo3GPPUserLocationInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserCSGInformation()) {
            sb.append("    UserCSGInformation:");
            try {
                sb.append(getUserCSGInformation()).append('\n');
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
        if (containsRo3GPPRATType()) {
            sb.append("    Ro3GPPRATType:");
            try {
                sb.append(getRo3GPPRATType()).append('\n');
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
        if (containsPDPContextType()) {
            sb.append("    PDPContextType:");
            try {
                sb.append(getPDPContextType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOfflineCharging()) {
            sb.append("    OfflineCharging:");
            try {
                sb.append(getOfflineCharging()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countTrafficDataVolumes(); ++i) {
            sb.append("    TrafficDataVolumes:");
            try {
                sb.append(getTrafficDataVolumes(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServiceDataContainer(); ++i) {
            sb.append("    ServiceDataContainer:");
            try {
                sb.append(getServiceDataContainer(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserEquipmentInfo()) {
            sb.append("    UserEquipmentInfo:");
            try {
                sb.append(getUserEquipmentInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTerminalInformation()) {
            sb.append("    TerminalInformation:");
            try {
                sb.append(getTerminalInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsStartTime()) {
            sb.append("    StartTime:");
            try {
                sb.append(getStartTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsStopTime()) {
            sb.append("    StopTime:");
            try {
                sb.append(getStopTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsChangeCondition()) {
            sb.append("    ChangeCondition:");
            try {
                sb.append(getChangeCondition()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDiagnostics()) {
            sb.append("    Diagnostics:");
            try {
                sb.append(getDiagnostics()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLowPriorityIndicator()) {
            sb.append("    LowPriorityIndicator:");
            try {
                sb.append(getLowPriorityIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
