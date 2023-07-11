package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CAPInformation.
     */
    public CAPInformation() {}

    CAPInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CAPCellIDAreaIDLAI.
     */
    public boolean containsCAPCellIDAreaIDLAI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCellIDAreaIDLAI);
    }

    /**
     * Gets the CAPCellIDAreaIDLAI.
     */
    public CAPCellIDAreaIDLAI getCAPCellIDAreaIDLAI() throws NoSuchAttributeException {
        return (CAPCellIDAreaIDLAI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCellIDAreaIDLAI, 0);
    }

    /**
     * Sets the CAPCellIDAreaIDLAI.
     *
     * @param avp - the attribute value
     */
    public void setCAPCellIDAreaIDLAI(CAPCellIDAreaIDLAI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCellIDAreaIDLAI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPIsFollowingOn.
     */
    public boolean containsCAPIsFollowingOn() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPIsFollowingOn);
    }

    /**
     * Gets the CAPIsFollowingOn.
     */
    public CAPIsFollowingOn getCAPIsFollowingOn() throws NoSuchAttributeException {
        return (CAPIsFollowingOn)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPIsFollowingOn, 0);
    }

    /**
     * Sets the CAPIsFollowingOn.
     *
     * @param avp - the attribute value
     */
    public void setCAPIsFollowingOn(CAPIsFollowingOn avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPIsFollowingOn, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPControlMode.
     */
    public boolean containsCAPControlMode() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPControlMode);
    }

    /**
     * Gets the CAPControlMode.
     */
    public CAPControlMode getCAPControlMode() throws NoSuchAttributeException {
        return (CAPControlMode)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPControlMode, 0);
    }

    /**
     * Sets the CAPControlMode.
     *
     * @param avp - the attribute value
     */
    public void setCAPControlMode(CAPControlMode avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPControlMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPEventTypeBCSM.
     */
    public boolean containsCAPEventTypeBCSM() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPEventTypeBCSM);
    }

    /**
     * Gets the CAPEventTypeBCSM.
     */
    public CAPEventTypeBCSM getCAPEventTypeBCSM() throws NoSuchAttributeException {
        return (CAPEventTypeBCSM)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPEventTypeBCSM, 0);
    }

    /**
     * Sets the CAPEventTypeBCSM.
     *
     * @param avp - the attribute value
     */
    public void setCAPEventTypeBCSM(CAPEventTypeBCSM avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPEventTypeBCSM, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPEventTypeSMS.
     */
    public boolean containsCAPEventTypeSMS() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPEventTypeSMS);
    }

    /**
     * Gets the CAPEventTypeSMS.
     */
    public CAPEventTypeSMS getCAPEventTypeSMS() throws NoSuchAttributeException {
        return (CAPEventTypeSMS)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPEventTypeSMS, 0);
    }

    /**
     * Sets the CAPEventTypeSMS.
     *
     * @param avp - the attribute value
     */
    public void setCAPEventTypeSMS(CAPEventTypeSMS avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPEventTypeSMS, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPServiceKey.
     */
    public boolean containsCAPServiceKey() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPServiceKey);
    }

    /**
     * Gets the CAPServiceKey.
     */
    public CAPServiceKey getCAPServiceKey() throws NoSuchAttributeException {
        return (CAPServiceKey)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPServiceKey, 0);
    }

    /**
     * Sets the CAPServiceKey.
     *
     * @param avp - the attribute value
     */
    public void setCAPServiceKey(CAPServiceKey avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPServiceKey, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPDialedDigits.
     */
    public boolean containsCAPDialedDigits() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPDialedDigits);
    }

    /**
     * Gets the CAPDialedDigits.
     */
    public CAPDialedDigits getCAPDialedDigits() throws NoSuchAttributeException {
        return (CAPDialedDigits)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPDialedDigits, 0);
    }

    /**
     * Sets the CAPDialedDigits.
     *
     * @param avp - the attribute value
     */
    public void setCAPDialedDigits(CAPDialedDigits avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPDialedDigits, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCalledTON.
     */
    public boolean containsCAPCalledTON() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCalledTON);
    }

    /**
     * Gets the CAPCalledTON.
     */
    public CAPCalledTON getCAPCalledTON() throws NoSuchAttributeException {
        return (CAPCalledTON)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCalledTON, 0);
    }

    /**
     * Sets the CAPCalledTON.
     *
     * @param avp - the attribute value
     */
    public void setCAPCalledTON(CAPCalledTON avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCalledTON, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCLI.
     */
    public boolean containsCAPCLI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCLI);
    }

    /**
     * Gets the CAPCLI.
     */
    public CAPCLI getCAPCLI() throws NoSuchAttributeException {
        return (CAPCLI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCLI, 0);
    }

    /**
     * Sets the CAPCLI.
     *
     * @param avp - the attribute value
     */
    public void setCAPCLI(CAPCLI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCLI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCallingCategory.
     */
    public boolean containsCAPCallingCategory() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCallingCategory);
    }

    /**
     * Gets the CAPCallingCategory.
     */
    public CAPCallingCategory getCAPCallingCategory() throws NoSuchAttributeException {
        return (CAPCallingCategory)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCallingCategory, 0);
    }

    /**
     * Sets the CAPCallingCategory.
     *
     * @param avp - the attribute value
     */
    public void setCAPCallingCategory(CAPCallingCategory avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCallingCategory, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPLocationNumber.
     */
    public boolean containsCAPLocationNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPLocationNumber);
    }

    /**
     * Gets the CAPLocationNumber.
     */
    public CAPLocationNumber getCAPLocationNumber() throws NoSuchAttributeException {
        return (CAPLocationNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPLocationNumber, 0);
    }

    /**
     * Sets the CAPLocationNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPLocationNumber(CAPLocationNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPLocationNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPRedirectingNumber.
     */
    public boolean containsCAPRedirectingNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPRedirectingNumber);
    }

    /**
     * Gets the CAPRedirectingNumber.
     */
    public CAPRedirectingNumber getCAPRedirectingNumber() throws NoSuchAttributeException {
        return (CAPRedirectingNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPRedirectingNumber, 0);
    }

    /**
     * Sets the CAPRedirectingNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPRedirectingNumber(CAPRedirectingNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPRedirectingNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPRedirectingIndicator.
     */
    public boolean containsCAPRedirectingIndicator() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPRedirectingIndicator);
    }

    /**
     * Gets the CAPRedirectingIndicator.
     */
    public CAPRedirectingIndicator getCAPRedirectingIndicator() throws NoSuchAttributeException {
        return (CAPRedirectingIndicator)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPRedirectingIndicator, 0);
    }

    /**
     * Sets the CAPRedirectingIndicator.
     *
     * @param avp - the attribute value
     */
    public void setCAPRedirectingIndicator(CAPRedirectingIndicator avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPRedirectingIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPOriginalRedirectingReason.
     */
    public boolean containsCAPOriginalRedirectingReason() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPOriginalRedirectingReason);
    }

    /**
     * Gets the CAPOriginalRedirectingReason.
     */
    public CAPOriginalRedirectingReason getCAPOriginalRedirectingReason() throws NoSuchAttributeException {
        return (CAPOriginalRedirectingReason)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPOriginalRedirectingReason, 0);
    }

    /**
     * Sets the CAPOriginalRedirectingReason.
     *
     * @param avp - the attribute value
     */
    public void setCAPOriginalRedirectingReason(CAPOriginalRedirectingReason avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPOriginalRedirectingReason, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPRedirectionCounter.
     */
    public boolean containsCAPRedirectionCounter() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPRedirectionCounter);
    }

    /**
     * Gets the CAPRedirectionCounter.
     */
    public CAPRedirectionCounter getCAPRedirectionCounter() throws NoSuchAttributeException {
        return (CAPRedirectionCounter)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPRedirectionCounter, 0);
    }

    /**
     * Sets the CAPRedirectionCounter.
     *
     * @param avp - the attribute value
     */
    public void setCAPRedirectionCounter(CAPRedirectionCounter avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPRedirectionCounter, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPRedirectingReason.
     */
    public boolean containsCAPRedirectingReason() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPRedirectingReason);
    }

    /**
     * Gets the CAPRedirectingReason.
     */
    public CAPRedirectingReason getCAPRedirectingReason() throws NoSuchAttributeException {
        return (CAPRedirectingReason)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPRedirectingReason, 0);
    }

    /**
     * Sets the CAPRedirectingReason.
     *
     * @param avp - the attribute value
     */
    public void setCAPRedirectingReason(CAPRedirectingReason avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPRedirectingReason, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPIMSI.
     */
    public boolean containsCAPIMSI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPIMSI);
    }

    /**
     * Gets the CAPIMSI.
     */
    public CAPIMSI getCAPIMSI() throws NoSuchAttributeException {
        return (CAPIMSI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPIMSI, 0);
    }

    /**
     * Sets the CAPIMSI.
     *
     * @param avp - the attribute value
     */
    public void setCAPIMSI(CAPIMSI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPIMSI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPVLRNumber.
     */
    public boolean containsCAPVLRNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPVLRNumber);
    }

    /**
     * Gets the CAPVLRNumber.
     */
    public CAPVLRNumber getCAPVLRNumber() throws NoSuchAttributeException {
        return (CAPVLRNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPVLRNumber, 0);
    }

    /**
     * Sets the CAPVLRNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPVLRNumber(CAPVLRNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPVLRNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCallReference.
     */
    public boolean containsCAPCallReference() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCallReference);
    }

    /**
     * Gets the CAPCallReference.
     */
    public CAPCallReference getCAPCallReference() throws NoSuchAttributeException {
        return (CAPCallReference)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCallReference, 0);
    }

    /**
     * Sets the CAPCallReference.
     *
     * @param avp - the attribute value
     */
    public void setCAPCallReference(CAPCallReference avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCallReference, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPMSCAddress.
     */
    public boolean containsCAPMSCAddress() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPMSCAddress);
    }

    /**
     * Gets the CAPMSCAddress.
     */
    public CAPMSCAddress getCAPMSCAddress() throws NoSuchAttributeException {
        return (CAPMSCAddress)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPMSCAddress, 0);
    }

    /**
     * Sets the CAPMSCAddress.
     *
     * @param avp - the attribute value
     */
    public void setCAPMSCAddress(CAPMSCAddress avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPMSCAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCalledNPI.
     */
    public boolean containsCAPCalledNPI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCalledNPI);
    }

    /**
     * Gets the CAPCalledNPI.
     */
    public CAPCalledNPI getCAPCalledNPI() throws NoSuchAttributeException {
        return (CAPCalledNPI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCalledNPI, 0);
    }

    /**
     * Sets the CAPCalledNPI.
     *
     * @param avp - the attribute value
     */
    public void setCAPCalledNPI(CAPCalledNPI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCalledNPI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCLINPI.
     */
    public boolean containsCAPCLINPI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCLINPI);
    }

    /**
     * Gets the CAPCLINPI.
     */
    public CAPCLINPI getCAPCLINPI() throws NoSuchAttributeException {
        return (CAPCLINPI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCLINPI, 0);
    }

    /**
     * Sets the CAPCLINPI.
     *
     * @param avp - the attribute value
     */
    public void setCAPCLINPI(CAPCLINPI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCLINPI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCLINOA.
     */
    public boolean containsCAPCLINOA() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCLINOA);
    }

    /**
     * Gets the CAPCLINOA.
     */
    public CAPCLINOA getCAPCLINOA() throws NoSuchAttributeException {
        return (CAPCLINOA)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCLINOA, 0);
    }

    /**
     * Sets the CAPCLINOA.
     *
     * @param avp - the attribute value
     */
    public void setCAPCLINOA(CAPCLINOA avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCLINOA, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPCLIR.
     */
    public boolean containsCAPCLIR() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPCLIR);
    }

    /**
     * Gets the CAPCLIR.
     */
    public CAPCLIR getCAPCLIR() throws NoSuchAttributeException {
        return (CAPCLIR)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPCLIR, 0);
    }

    /**
     * Sets the CAPCLIR.
     *
     * @param avp - the attribute value
     */
    public void setCAPCLIR(CAPCLIR avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPCLIR, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPVersion.
     */
    public boolean containsCAPVersion() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPVersion);
    }

    /**
     * Gets the CAPVersion.
     */
    public CAPVersion getCAPVersion() throws NoSuchAttributeException {
        return (CAPVersion)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPVersion, 0);
    }

    /**
     * Sets the CAPVersion.
     *
     * @param avp - the attribute value
     */
    public void setCAPVersion(CAPVersion avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPVersion, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPBearerCapabilityTransfer.
     */
    public boolean containsCAPBearerCapabilityTransfer() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransfer);
    }

    /**
     * Gets the CAPBearerCapabilityTransfer.
     */
    public CAPBearerCapabilityTransfer getCAPBearerCapabilityTransfer() throws NoSuchAttributeException {
        return (CAPBearerCapabilityTransfer)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransfer, 0);
    }

    /**
     * Sets the CAPBearerCapabilityTransfer.
     *
     * @param avp - the attribute value
     */
    public void setCAPBearerCapabilityTransfer(CAPBearerCapabilityTransfer avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransfer, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPBearerCapabilityTransferRate.
     */
    public boolean containsCAPBearerCapabilityTransferRate() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransferRate);
    }

    /**
     * Gets the CAPBearerCapabilityTransferRate.
     */
    public CAPBearerCapabilityTransferRate getCAPBearerCapabilityTransferRate() throws NoSuchAttributeException {
        return (CAPBearerCapabilityTransferRate)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransferRate, 0);
    }

    /**
     * Sets the CAPBearerCapabilityTransferRate.
     *
     * @param avp - the attribute value
     */
    public void setCAPBearerCapabilityTransferRate(CAPBearerCapabilityTransferRate avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransferRate, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPGMSCAddress.
     */
    public boolean containsCAPGMSCAddress() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPGMSCAddress);
    }

    /**
     * Gets the CAPGMSCAddress.
     */
    public CAPGMSCAddress getCAPGMSCAddress() throws NoSuchAttributeException {
        return (CAPGMSCAddress)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPGMSCAddress, 0);
    }

    /**
     * Sets the CAPGMSCAddress.
     *
     * @param avp - the attribute value
     */
    public void setCAPGMSCAddress(CAPGMSCAddress avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPGMSCAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPExtBasicServiceCode.
     */
    public boolean containsCAPExtBasicServiceCode() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPExtBasicServiceCode);
    }

    /**
     * Gets the CAPExtBasicServiceCode.
     */
    public CAPExtBasicServiceCode getCAPExtBasicServiceCode() throws NoSuchAttributeException {
        return (CAPExtBasicServiceCode)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPExtBasicServiceCode, 0);
    }

    /**
     * Sets the CAPExtBasicServiceCode.
     *
     * @param avp - the attribute value
     */
    public void setCAPExtBasicServiceCode(CAPExtBasicServiceCode avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPExtBasicServiceCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPBearerCapability.
     */
    public boolean containsCAPBearerCapability() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPBearerCapability);
    }

    /**
     * Gets the CAPBearerCapability.
     */
    public CAPBearerCapability getCAPBearerCapability() throws NoSuchAttributeException {
        return (CAPBearerCapability)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPBearerCapability, 0);
    }

    /**
     * Sets the CAPBearerCapability.
     *
     * @param avp - the attribute value
     */
    public void setCAPBearerCapability(CAPBearerCapability avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPBearerCapability, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMSCAddress.
     */
    public boolean containsCAPSMSCAddress() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMSCAddress);
    }

    /**
     * Gets the CAPSMSCAddress.
     */
    public CAPSMSCAddress getCAPSMSCAddress() throws NoSuchAttributeException {
        return (CAPSMSCAddress)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMSCAddress, 0);
    }

    /**
     * Sets the CAPSMSCAddress.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMSCAddress(CAPSMSCAddress avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMSCAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSGSNAddress.
     */
    public boolean containsCAPSGSNAddress() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSGSNAddress);
    }

    /**
     * Gets the CAPSGSNAddress.
     */
    public CAPSGSNAddress getCAPSGSNAddress() throws NoSuchAttributeException {
        return (CAPSGSNAddress)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSGSNAddress, 0);
    }

    /**
     * Sets the CAPSGSNAddress.
     *
     * @param avp - the attribute value
     */
    public void setCAPSGSNAddress(CAPSGSNAddress avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSGSNAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPIMEI.
     */
    public boolean containsCAPIMEI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPIMEI);
    }

    /**
     * Gets the CAPIMEI.
     */
    public CAPIMEI getCAPIMEI() throws NoSuchAttributeException {
        return (CAPIMEI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPIMEI, 0);
    }

    /**
     * Sets the CAPIMEI.
     *
     * @param avp - the attribute value
     */
    public void setCAPIMEI(CAPIMEI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPIMEI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMStatusReportRequest.
     */
    public boolean containsCAPSMStatusReportRequest() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMStatusReportRequest);
    }

    /**
     * Gets the CAPSMStatusReportRequest.
     */
    public CAPSMStatusReportRequest getCAPSMStatusReportRequest() throws NoSuchAttributeException {
        return (CAPSMStatusReportRequest)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMStatusReportRequest, 0);
    }

    /**
     * Sets the CAPSMStatusReportRequest.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMStatusReportRequest(CAPSMStatusReportRequest avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMStatusReportRequest, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMUserDataHeaderIndicator.
     */
    public boolean containsCAPSMUserDataHeaderIndicator() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMUserDataHeaderIndicator);
    }

    /**
     * Gets the CAPSMUserDataHeaderIndicator.
     */
    public CAPSMUserDataHeaderIndicator getCAPSMUserDataHeaderIndicator() throws NoSuchAttributeException {
        return (CAPSMUserDataHeaderIndicator)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMUserDataHeaderIndicator, 0);
    }

    /**
     * Sets the CAPSMUserDataHeaderIndicator.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMUserDataHeaderIndicator(CAPSMUserDataHeaderIndicator avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMUserDataHeaderIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMReplyPath.
     */
    public boolean containsCAPSMReplyPath() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMReplyPath);
    }

    /**
     * Gets the CAPSMReplyPath.
     */
    public CAPSMReplyPath getCAPSMReplyPath() throws NoSuchAttributeException {
        return (CAPSMReplyPath)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMReplyPath, 0);
    }

    /**
     * Sets the CAPSMReplyPath.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMReplyPath(CAPSMReplyPath avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMReplyPath, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMVPFormat.
     */
    public boolean containsCAPSMVPFormat() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMVPFormat);
    }

    /**
     * Gets the CAPSMVPFormat.
     */
    public CAPSMVPFormat getCAPSMVPFormat() throws NoSuchAttributeException {
        return (CAPSMVPFormat)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMVPFormat, 0);
    }

    /**
     * Sets the CAPSMVPFormat.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMVPFormat(CAPSMVPFormat avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMVPFormat, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMMessageTypeIndicator.
     */
    public boolean containsCAPSMMessageTypeIndicator() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMMessageTypeIndicator);
    }

    /**
     * Gets the CAPSMMessageTypeIndicator.
     */
    public CAPSMMessageTypeIndicator getCAPSMMessageTypeIndicator() throws NoSuchAttributeException {
        return (CAPSMMessageTypeIndicator)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMMessageTypeIndicator, 0);
    }

    /**
     * Sets the CAPSMMessageTypeIndicator.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMMessageTypeIndicator(CAPSMMessageTypeIndicator avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMMessageTypeIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMProtocolID.
     */
    public boolean containsCAPSMProtocolID() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMProtocolID);
    }

    /**
     * Gets the CAPSMProtocolID.
     */
    public CAPSMProtocolID getCAPSMProtocolID() throws NoSuchAttributeException {
        return (CAPSMProtocolID)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMProtocolID, 0);
    }

    /**
     * Sets the CAPSMProtocolID.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMProtocolID(CAPSMProtocolID avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMProtocolID, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMDCS.
     */
    public boolean containsCAPSMDCS() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMDCS);
    }

    /**
     * Gets the CAPSMDCS.
     */
    public CAPSMDCS getCAPSMDCS() throws NoSuchAttributeException {
        return (CAPSMDCS)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMDCS, 0);
    }

    /**
     * Sets the CAPSMDCS.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMDCS(CAPSMDCS avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMDCS, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMValidityPeriod.
     */
    public boolean containsCAPSMValidityPeriod() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMValidityPeriod);
    }

    /**
     * Gets the CAPSMValidityPeriod.
     */
    public CAPSMValidityPeriod getCAPSMValidityPeriod() throws NoSuchAttributeException {
        return (CAPSMValidityPeriod)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMValidityPeriod, 0);
    }

    /**
     * Sets the CAPSMValidityPeriod.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMValidityPeriod(CAPSMValidityPeriod avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMValidityPeriod, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMRejectDuplicate.
     */
    public boolean containsCAPSMRejectDuplicate() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMRejectDuplicate);
    }

    /**
     * Gets the CAPSMRejectDuplicate.
     */
    public CAPSMRejectDuplicate getCAPSMRejectDuplicate() throws NoSuchAttributeException {
        return (CAPSMRejectDuplicate)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMRejectDuplicate, 0);
    }

    /**
     * Sets the CAPSMRejectDuplicate.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMRejectDuplicate(CAPSMRejectDuplicate avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMRejectDuplicate, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSCCPCallingGT.
     */
    public boolean containsCAPSCCPCallingGT() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSCCPCallingGT);
    }

    /**
     * Gets the CAPSCCPCallingGT.
     */
    public CAPSCCPCallingGT getCAPSCCPCallingGT() throws NoSuchAttributeException {
        return (CAPSCCPCallingGT)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSCCPCallingGT, 0);
    }

    /**
     * Sets the CAPSCCPCallingGT.
     *
     * @param avp - the attribute value
     */
    public void setCAPSCCPCallingGT(CAPSCCPCallingGT avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSCCPCallingGT, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSCCPCalledGT.
     */
    public boolean containsCAPSCCPCalledGT() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSCCPCalledGT);
    }

    /**
     * Gets the CAPSCCPCalledGT.
     */
    public CAPSCCPCalledGT getCAPSCCPCalledGT() throws NoSuchAttributeException {
        return (CAPSCCPCalledGT)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSCCPCalledGT, 0);
    }

    /**
     * Sets the CAPSCCPCalledGT.
     *
     * @param avp - the attribute value
     */
    public void setCAPSCCPCalledGT(CAPSCCPCalledGT avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSCCPCalledGT, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPBearerCapabilityTransferMode.
     */
    public boolean containsCAPBearerCapabilityTransferMode() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransferMode);
    }

    /**
     * Gets the CAPBearerCapabilityTransferMode.
     */
    public CAPBearerCapabilityTransferMode getCAPBearerCapabilityTransferMode() throws NoSuchAttributeException {
        return (CAPBearerCapabilityTransferMode)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransferMode, 0);
    }

    /**
     * Sets the CAPBearerCapabilityTransferMode.
     *
     * @param avp - the attribute value
     */
    public void setCAPBearerCapabilityTransferMode(CAPBearerCapabilityTransferMode avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPBearerCapabilityTransferMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPGSMForwardingPending.
     */
    public boolean containsCAPGSMForwardingPending() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPGSMForwardingPending);
    }

    /**
     * Gets the CAPGSMForwardingPending.
     */
    public CAPGSMForwardingPending getCAPGSMForwardingPending() throws NoSuchAttributeException {
        return (CAPGSMForwardingPending)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPGSMForwardingPending, 0);
    }

    /**
     * Sets the CAPGSMForwardingPending.
     *
     * @param avp - the attribute value
     */
    public void setCAPGSMForwardingPending(CAPGSMForwardingPending avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPGSMForwardingPending, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPTCAPRemoteTransactionId.
     */
    public boolean containsCAPTCAPRemoteTransactionId() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPTCAPRemoteTransactionId);
    }

    /**
     * Gets the CAPTCAPRemoteTransactionId.
     */
    public CAPTCAPRemoteTransactionId getCAPTCAPRemoteTransactionId() throws NoSuchAttributeException {
        return (CAPTCAPRemoteTransactionId)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPTCAPRemoteTransactionId, 0);
    }

    /**
     * Sets the CAPTCAPRemoteTransactionId.
     *
     * @param avp - the attribute value
     */
    public void setCAPTCAPRemoteTransactionId(CAPTCAPRemoteTransactionId avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPTCAPRemoteTransactionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPTCAPLocalTransactionId.
     */
    public boolean containsCAPTCAPLocalTransactionId() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPTCAPLocalTransactionId);
    }

    /**
     * Gets the CAPTCAPLocalTransactionId.
     */
    public CAPTCAPLocalTransactionId getCAPTCAPLocalTransactionId() throws NoSuchAttributeException {
        return (CAPTCAPLocalTransactionId)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPTCAPLocalTransactionId, 0);
    }

    /**
     * Sets the CAPTCAPLocalTransactionId.
     *
     * @param avp - the attribute value
     */
    public void setCAPTCAPLocalTransactionId(CAPTCAPLocalTransactionId avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPTCAPLocalTransactionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPERBSInformation.
     */
    public boolean containsCAPERBSInformation() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPERBSInformation);
    }

    /**
     * Gets the CAPERBSInformation.
     */
    public CAPERBSInformation getCAPERBSInformation() throws NoSuchAttributeException {
        return (CAPERBSInformation)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPERBSInformation, 0);
    }

    /**
     * Sets the CAPERBSInformation.
     *
     * @param avp - the attribute value
     */
    public void setCAPERBSInformation(CAPERBSInformation avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPERBSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPACHInformation.
     */
    public boolean containsCAPACHInformation() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPACHInformation);
    }

    /**
     * Gets the CAPACHInformation.
     */
    public CAPACHInformation getCAPACHInformation() throws NoSuchAttributeException {
        return (CAPACHInformation)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPACHInformation, 0);
    }

    /**
     * Sets the CAPACHInformation.
     *
     * @param avp - the attribute value
     */
    public void setCAPACHInformation(CAPACHInformation avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPACHInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectInformation.
     */
    public boolean containsCAPConnectInformation() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectInformation);
    }

    /**
     * Gets the CAPConnectInformation.
     */
    public CAPConnectInformation getCAPConnectInformation() throws NoSuchAttributeException {
        return (CAPConnectInformation)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectInformation, 0);
    }

    /**
     * Sets the CAPConnectInformation.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectInformation(CAPConnectInformation avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPRRBSInformation.
     */
    public boolean containsCAPRRBSInformation() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPRRBSInformation);
    }

    /**
     * Gets the CAPRRBSInformation.
     */
    public CAPRRBSInformation getCAPRRBSInformation() throws NoSuchAttributeException {
        return (CAPRRBSInformation)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPRRBSInformation, 0);
    }

    /**
     * Sets the CAPRRBSInformation.
     *
     * @param avp - the attribute value
     */
    public void setCAPRRBSInformation(CAPRRBSInformation avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPRRBSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPReleaseCause.
     */
    public boolean containsCAPReleaseCause() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPReleaseCause);
    }

    /**
     * Gets the CAPReleaseCause.
     */
    public CAPReleaseCause getCAPReleaseCause() throws NoSuchAttributeException {
        return (CAPReleaseCause)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPReleaseCause, 0);
    }

    /**
     * Sets the CAPReleaseCause.
     *
     * @param avp - the attribute value
     */
    public void setCAPReleaseCause(CAPReleaseCause avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPReleaseCause, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPSMSpecificInfo.
     */
    public boolean containsCAPSMSpecificInfo() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPSMSpecificInfo);
    }

    /**
     * Gets the CAPSMSpecificInfo.
     */
    public CAPSMSpecificInfo getCAPSMSpecificInfo() throws NoSuchAttributeException {
        return (CAPSMSpecificInfo)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPSMSpecificInfo, 0);
    }

    /**
     * Sets the CAPSMSpecificInfo.
     *
     * @param avp - the attribute value
     */
    public void setCAPSMSpecificInfo(CAPSMSpecificInfo avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPSMSpecificInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPTCAPErrorCause.
     */
    public boolean containsCAPTCAPErrorCause() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPTCAPErrorCause);
    }

    /**
     * Gets the CAPTCAPErrorCause.
     */
    public CAPTCAPErrorCause getCAPTCAPErrorCause() throws NoSuchAttributeException {
        return (CAPTCAPErrorCause)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPTCAPErrorCause, 0);
    }

    /**
     * Sets the CAPTCAPErrorCause.
     *
     * @param avp - the attribute value
     */
    public void setCAPTCAPErrorCause(CAPTCAPErrorCause avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPTCAPErrorCause, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCAPCellIDAreaIDLAI()) {
            sb.append("    CAPCellIDAreaIDLAI:");
            try {
                sb.append(getCAPCellIDAreaIDLAI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPIsFollowingOn()) {
            sb.append("    CAPIsFollowingOn:");
            try {
                sb.append(getCAPIsFollowingOn()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPControlMode()) {
            sb.append("    CAPControlMode:");
            try {
                sb.append(getCAPControlMode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPEventTypeBCSM()) {
            sb.append("    CAPEventTypeBCSM:");
            try {
                sb.append(getCAPEventTypeBCSM()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPEventTypeSMS()) {
            sb.append("    CAPEventTypeSMS:");
            try {
                sb.append(getCAPEventTypeSMS()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPServiceKey()) {
            sb.append("    CAPServiceKey:");
            try {
                sb.append(getCAPServiceKey()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPDialedDigits()) {
            sb.append("    CAPDialedDigits:");
            try {
                sb.append(getCAPDialedDigits()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCalledTON()) {
            sb.append("    CAPCalledTON:");
            try {
                sb.append(getCAPCalledTON()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCLI()) {
            sb.append("    CAPCLI:");
            try {
                sb.append(getCAPCLI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCallingCategory()) {
            sb.append("    CAPCallingCategory:");
            try {
                sb.append(getCAPCallingCategory()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPLocationNumber()) {
            sb.append("    CAPLocationNumber:");
            try {
                sb.append(getCAPLocationNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPRedirectingNumber()) {
            sb.append("    CAPRedirectingNumber:");
            try {
                sb.append(getCAPRedirectingNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPRedirectingIndicator()) {
            sb.append("    CAPRedirectingIndicator:");
            try {
                sb.append(getCAPRedirectingIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPOriginalRedirectingReason()) {
            sb.append("    CAPOriginalRedirectingReason:");
            try {
                sb.append(getCAPOriginalRedirectingReason()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPRedirectionCounter()) {
            sb.append("    CAPRedirectionCounter:");
            try {
                sb.append(getCAPRedirectionCounter()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPRedirectingReason()) {
            sb.append("    CAPRedirectingReason:");
            try {
                sb.append(getCAPRedirectingReason()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPIMSI()) {
            sb.append("    CAPIMSI:");
            try {
                sb.append(getCAPIMSI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPVLRNumber()) {
            sb.append("    CAPVLRNumber:");
            try {
                sb.append(getCAPVLRNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCallReference()) {
            sb.append("    CAPCallReference:");
            try {
                sb.append(getCAPCallReference()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPMSCAddress()) {
            sb.append("    CAPMSCAddress:");
            try {
                sb.append(getCAPMSCAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCalledNPI()) {
            sb.append("    CAPCalledNPI:");
            try {
                sb.append(getCAPCalledNPI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCLINPI()) {
            sb.append("    CAPCLINPI:");
            try {
                sb.append(getCAPCLINPI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCLINOA()) {
            sb.append("    CAPCLINOA:");
            try {
                sb.append(getCAPCLINOA()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPCLIR()) {
            sb.append("    CAPCLIR:");
            try {
                sb.append(getCAPCLIR()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPVersion()) {
            sb.append("    CAPVersion:");
            try {
                sb.append(getCAPVersion()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPBearerCapabilityTransfer()) {
            sb.append("    CAPBearerCapabilityTransfer:");
            try {
                sb.append(getCAPBearerCapabilityTransfer()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPBearerCapabilityTransferRate()) {
            sb.append("    CAPBearerCapabilityTransferRate:");
            try {
                sb.append(getCAPBearerCapabilityTransferRate()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPGMSCAddress()) {
            sb.append("    CAPGMSCAddress:");
            try {
                sb.append(getCAPGMSCAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPExtBasicServiceCode()) {
            sb.append("    CAPExtBasicServiceCode:");
            try {
                sb.append(getCAPExtBasicServiceCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPBearerCapability()) {
            sb.append("    CAPBearerCapability:");
            try {
                sb.append(getCAPBearerCapability()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMSCAddress()) {
            sb.append("    CAPSMSCAddress:");
            try {
                sb.append(getCAPSMSCAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSGSNAddress()) {
            sb.append("    CAPSGSNAddress:");
            try {
                sb.append(getCAPSGSNAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPIMEI()) {
            sb.append("    CAPIMEI:");
            try {
                sb.append(getCAPIMEI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMStatusReportRequest()) {
            sb.append("    CAPSMStatusReportRequest:");
            try {
                sb.append(getCAPSMStatusReportRequest()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMUserDataHeaderIndicator()) {
            sb.append("    CAPSMUserDataHeaderIndicator:");
            try {
                sb.append(getCAPSMUserDataHeaderIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMReplyPath()) {
            sb.append("    CAPSMReplyPath:");
            try {
                sb.append(getCAPSMReplyPath()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMVPFormat()) {
            sb.append("    CAPSMVPFormat:");
            try {
                sb.append(getCAPSMVPFormat()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMMessageTypeIndicator()) {
            sb.append("    CAPSMMessageTypeIndicator:");
            try {
                sb.append(getCAPSMMessageTypeIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMProtocolID()) {
            sb.append("    CAPSMProtocolID:");
            try {
                sb.append(getCAPSMProtocolID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMDCS()) {
            sb.append("    CAPSMDCS:");
            try {
                sb.append(getCAPSMDCS()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMValidityPeriod()) {
            sb.append("    CAPSMValidityPeriod:");
            try {
                sb.append(getCAPSMValidityPeriod()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMRejectDuplicate()) {
            sb.append("    CAPSMRejectDuplicate:");
            try {
                sb.append(getCAPSMRejectDuplicate()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSCCPCallingGT()) {
            sb.append("    CAPSCCPCallingGT:");
            try {
                sb.append(getCAPSCCPCallingGT()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSCCPCalledGT()) {
            sb.append("    CAPSCCPCalledGT:");
            try {
                sb.append(getCAPSCCPCalledGT()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPBearerCapabilityTransferMode()) {
            sb.append("    CAPBearerCapabilityTransferMode:");
            try {
                sb.append(getCAPBearerCapabilityTransferMode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPGSMForwardingPending()) {
            sb.append("    CAPGSMForwardingPending:");
            try {
                sb.append(getCAPGSMForwardingPending()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPTCAPRemoteTransactionId()) {
            sb.append("    CAPTCAPRemoteTransactionId:");
            try {
                sb.append(getCAPTCAPRemoteTransactionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPTCAPLocalTransactionId()) {
            sb.append("    CAPTCAPLocalTransactionId:");
            try {
                sb.append(getCAPTCAPLocalTransactionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPERBSInformation()) {
            sb.append("    CAPERBSInformation:");
            try {
                sb.append(getCAPERBSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPACHInformation()) {
            sb.append("    CAPACHInformation:");
            try {
                sb.append(getCAPACHInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectInformation()) {
            sb.append("    CAPConnectInformation:");
            try {
                sb.append(getCAPConnectInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPRRBSInformation()) {
            sb.append("    CAPRRBSInformation:");
            try {
                sb.append(getCAPRRBSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPReleaseCause()) {
            sb.append("    CAPReleaseCause:");
            try {
                sb.append(getCAPReleaseCause()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPSMSpecificInfo()) {
            sb.append("    CAPSMSpecificInfo:");
            try {
                sb.append(getCAPSMSpecificInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPTCAPErrorCause()) {
            sb.append("    CAPTCAPErrorCause:");
            try {
                sb.append(getCAPTCAPErrorCause()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
