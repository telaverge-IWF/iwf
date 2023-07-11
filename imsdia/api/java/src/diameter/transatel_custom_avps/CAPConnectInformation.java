package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CAPConnectInformation.
     */
    public CAPConnectInformation() {}

    CAPConnectInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CAPAnnouncementAccessNumber.
     */
    public boolean containsCAPAnnouncementAccessNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPAnnouncementAccessNumber);
    }

    /**
     * Gets the CAPAnnouncementAccessNumber.
     */
    public CAPAnnouncementAccessNumber getCAPAnnouncementAccessNumber() throws NoSuchAttributeException {
        return (CAPAnnouncementAccessNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPAnnouncementAccessNumber, 0);
    }

    /**
     * Sets the CAPAnnouncementAccessNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPAnnouncementAccessNumber(CAPAnnouncementAccessNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPAnnouncementAccessNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPAnnouncementAccessNumberNOA.
     */
    public boolean containsCAPAnnouncementAccessNumberNOA() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPAnnouncementAccessNumberNOA);
    }

    /**
     * Gets the CAPAnnouncementAccessNumberNOA.
     */
    public CAPAnnouncementAccessNumberNOA getCAPAnnouncementAccessNumberNOA() throws NoSuchAttributeException {
        return (CAPAnnouncementAccessNumberNOA)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPAnnouncementAccessNumberNOA, 0);
    }

    /**
     * Sets the CAPAnnouncementAccessNumberNOA.
     *
     * @param avp - the attribute value
     */
    public void setCAPAnnouncementAccessNumberNOA(CAPAnnouncementAccessNumberNOA avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPAnnouncementAccessNumberNOA, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectDestinationNumber.
     */
    public boolean containsCAPConnectDestinationNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumber);
    }

    /**
     * Gets the CAPConnectDestinationNumber.
     */
    public CAPConnectDestinationNumber getCAPConnectDestinationNumber() throws NoSuchAttributeException {
        return (CAPConnectDestinationNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumber, 0);
    }

    /**
     * Sets the CAPConnectDestinationNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectDestinationNumber(CAPConnectDestinationNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectDestinationNumberNature.
     */
    public boolean containsCAPConnectDestinationNumberNature() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberNature);
    }

    /**
     * Gets the CAPConnectDestinationNumberNature.
     */
    public CAPConnectDestinationNumberNature getCAPConnectDestinationNumberNature() throws NoSuchAttributeException {
        return (CAPConnectDestinationNumberNature)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberNature, 0);
    }

    /**
     * Sets the CAPConnectDestinationNumberNature.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectDestinationNumberNature(CAPConnectDestinationNumberNature avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberNature, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectDestinationNumberNPI.
     */
    public boolean containsCAPConnectDestinationNumberNPI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberNPI);
    }

    /**
     * Gets the CAPConnectDestinationNumberNPI.
     */
    public CAPConnectDestinationNumberNPI getCAPConnectDestinationNumberNPI() throws NoSuchAttributeException {
        return (CAPConnectDestinationNumberNPI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberNPI, 0);
    }

    /**
     * Sets the CAPConnectDestinationNumberNPI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectDestinationNumberNPI(CAPConnectDestinationNumberNPI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberNPI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectGenericNumber.
     */
    public boolean containsCAPConnectGenericNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectGenericNumber);
    }

    /**
     * Gets the CAPConnectGenericNumber.
     */
    public CAPConnectGenericNumber getCAPConnectGenericNumber() throws NoSuchAttributeException {
        return (CAPConnectGenericNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectGenericNumber, 0);
    }

    /**
     * Sets the CAPConnectGenericNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectGenericNumber(CAPConnectGenericNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectGenericNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectCallingCategory.
     */
    public boolean containsCAPConnectCallingCategory() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectCallingCategory);
    }

    /**
     * Gets the CAPConnectCallingCategory.
     */
    public CAPConnectCallingCategory getCAPConnectCallingCategory() throws NoSuchAttributeException {
        return (CAPConnectCallingCategory)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectCallingCategory, 0);
    }

    /**
     * Sets the CAPConnectCallingCategory.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectCallingCategory(CAPConnectCallingCategory avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectCallingCategory, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectRedirectingNumber.
     */
    public boolean containsCAPConnectRedirectingNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumber);
    }

    /**
     * Gets the CAPConnectRedirectingNumber.
     */
    public CAPConnectRedirectingNumber getCAPConnectRedirectingNumber() throws NoSuchAttributeException {
        return (CAPConnectRedirectingNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumber, 0);
    }

    /**
     * Sets the CAPConnectRedirectingNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectRedirectingNumber(CAPConnectRedirectingNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectRedirectingIndicator.
     */
    public boolean containsCAPConnectRedirectingIndicator() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectRedirectingIndicator);
    }

    /**
     * Gets the CAPConnectRedirectingIndicator.
     */
    public CAPConnectRedirectingIndicator getCAPConnectRedirectingIndicator() throws NoSuchAttributeException {
        return (CAPConnectRedirectingIndicator)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectRedirectingIndicator, 0);
    }

    /**
     * Sets the CAPConnectRedirectingIndicator.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectRedirectingIndicator(CAPConnectRedirectingIndicator avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectRedirectingIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectOriginalRedirectingReason.
     */
    public boolean containsCAPConnectOriginalRedirectingReason() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectOriginalRedirectingReason);
    }

    /**
     * Gets the CAPConnectOriginalRedirectingReason.
     */
    public CAPConnectOriginalRedirectingReason getCAPConnectOriginalRedirectingReason() throws NoSuchAttributeException {
        return (CAPConnectOriginalRedirectingReason)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectOriginalRedirectingReason, 0);
    }

    /**
     * Sets the CAPConnectOriginalRedirectingReason.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectOriginalRedirectingReason(CAPConnectOriginalRedirectingReason avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectOriginalRedirectingReason, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectRedirectingCounter.
     */
    public boolean containsCAPConnectRedirectingCounter() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectRedirectingCounter);
    }

    /**
     * Gets the CAPConnectRedirectingCounter.
     */
    public CAPConnectRedirectingCounter getCAPConnectRedirectingCounter() throws NoSuchAttributeException {
        return (CAPConnectRedirectingCounter)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectRedirectingCounter, 0);
    }

    /**
     * Sets the CAPConnectRedirectingCounter.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectRedirectingCounter(CAPConnectRedirectingCounter avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectRedirectingCounter, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectRedirectingReason.
     */
    public boolean containsCAPConnectRedirectingReason() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectRedirectingReason);
    }

    /**
     * Gets the CAPConnectRedirectingReason.
     */
    public CAPConnectRedirectingReason getCAPConnectRedirectingReason() throws NoSuchAttributeException {
        return (CAPConnectRedirectingReason)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectRedirectingReason, 0);
    }

    /**
     * Sets the CAPConnectRedirectingReason.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectRedirectingReason(CAPConnectRedirectingReason avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectRedirectingReason, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectoCSIApplicable.
     */
    public boolean containsCAPConnectoCSIApplicable() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectoCSIApplicable);
    }

    /**
     * Gets the CAPConnectoCSIApplicable.
     */
    public CAPConnectoCSIApplicable getCAPConnectoCSIApplicable() throws NoSuchAttributeException {
        return (CAPConnectoCSIApplicable)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectoCSIApplicable, 0);
    }

    /**
     * Sets the CAPConnectoCSIApplicable.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectoCSIApplicable(CAPConnectoCSIApplicable avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectoCSIApplicable, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectSuppressionOfAnnouncement.
     */
    public boolean containsCAPConnectSuppressionOfAnnouncement() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectSuppressionOfAnnouncement);
    }

    /**
     * Gets the CAPConnectSuppressionOfAnnouncement.
     */
    public CAPConnectSuppressionOfAnnouncement getCAPConnectSuppressionOfAnnouncement() throws NoSuchAttributeException {
        return (CAPConnectSuppressionOfAnnouncement)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectSuppressionOfAnnouncement, 0);
    }

    /**
     * Sets the CAPConnectSuppressionOfAnnouncement.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectSuppressionOfAnnouncement(CAPConnectSuppressionOfAnnouncement avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectSuppressionOfAnnouncement, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectGenericNumberNOA.
     */
    public boolean containsCAPConnectGenericNumberNOA() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNOA);
    }

    /**
     * Gets the CAPConnectGenericNumberNOA.
     */
    public CAPConnectGenericNumberNOA getCAPConnectGenericNumberNOA() throws NoSuchAttributeException {
        return (CAPConnectGenericNumberNOA)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNOA, 0);
    }

    /**
     * Sets the CAPConnectGenericNumberNOA.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectGenericNumberNOA(CAPConnectGenericNumberNOA avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNOA, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectGenericNumberNPI.
     */
    public boolean containsCAPConnectGenericNumberNPI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNPI);
    }

    /**
     * Gets the CAPConnectGenericNumberNPI.
     */
    public CAPConnectGenericNumberNPI getCAPConnectGenericNumberNPI() throws NoSuchAttributeException {
        return (CAPConnectGenericNumberNPI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNPI, 0);
    }

    /**
     * Sets the CAPConnectGenericNumberNPI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectGenericNumberNPI(CAPConnectGenericNumberNPI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNPI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectOriginalCalledNumber.
     */
    public boolean containsCAPConnectOriginalCalledNumber() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumber);
    }

    /**
     * Gets the CAPConnectOriginalCalledNumber.
     */
    public CAPConnectOriginalCalledNumber getCAPConnectOriginalCalledNumber() throws NoSuchAttributeException {
        return (CAPConnectOriginalCalledNumber)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumber, 0);
    }

    /**
     * Sets the CAPConnectOriginalCalledNumber.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectOriginalCalledNumber(CAPConnectOriginalCalledNumber avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectDestinationNumberINN.
     */
    public boolean containsCAPConnectDestinationNumberINN() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberINN);
    }

    /**
     * Gets the CAPConnectDestinationNumberINN.
     */
    public CAPConnectDestinationNumberINN getCAPConnectDestinationNumberINN() throws NoSuchAttributeException {
        return (CAPConnectDestinationNumberINN)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberINN, 0);
    }

    /**
     * Sets the CAPConnectDestinationNumberINN.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectDestinationNumberINN(CAPConnectDestinationNumberINN avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectDestinationNumberINN, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectGenericNumberNQI.
     */
    public boolean containsCAPConnectGenericNumberNQI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNQI);
    }

    /**
     * Gets the CAPConnectGenericNumberNQI.
     */
    public CAPConnectGenericNumberNQI getCAPConnectGenericNumberNQI() throws NoSuchAttributeException {
        return (CAPConnectGenericNumberNQI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNQI, 0);
    }

    /**
     * Sets the CAPConnectGenericNumberNQI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectGenericNumberNQI(CAPConnectGenericNumberNQI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNQI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectGenericNumberNII.
     */
    public boolean containsCAPConnectGenericNumberNII() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNII);
    }

    /**
     * Gets the CAPConnectGenericNumberNII.
     */
    public CAPConnectGenericNumberNII getCAPConnectGenericNumberNII() throws NoSuchAttributeException {
        return (CAPConnectGenericNumberNII)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNII, 0);
    }

    /**
     * Sets the CAPConnectGenericNumberNII.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectGenericNumberNII(CAPConnectGenericNumberNII avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberNII, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectGenericNumberARI.
     */
    public boolean containsCAPConnectGenericNumberARI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberARI);
    }

    /**
     * Gets the CAPConnectGenericNumberARI.
     */
    public CAPConnectGenericNumberARI getCAPConnectGenericNumberARI() throws NoSuchAttributeException {
        return (CAPConnectGenericNumberARI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberARI, 0);
    }

    /**
     * Sets the CAPConnectGenericNumberARI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectGenericNumberARI(CAPConnectGenericNumberARI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberARI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectGenericNumberSCI.
     */
    public boolean containsCAPConnectGenericNumberSCI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberSCI);
    }

    /**
     * Gets the CAPConnectGenericNumberSCI.
     */
    public CAPConnectGenericNumberSCI getCAPConnectGenericNumberSCI() throws NoSuchAttributeException {
        return (CAPConnectGenericNumberSCI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberSCI, 0);
    }

    /**
     * Sets the CAPConnectGenericNumberSCI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectGenericNumberSCI(CAPConnectGenericNumberSCI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectGenericNumberSCI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectRedirectingNumberNOA.
     */
    public boolean containsCAPConnectRedirectingNumberNOA() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberNOA);
    }

    /**
     * Gets the CAPConnectRedirectingNumberNOA.
     */
    public CAPConnectRedirectingNumberNOA getCAPConnectRedirectingNumberNOA() throws NoSuchAttributeException {
        return (CAPConnectRedirectingNumberNOA)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberNOA, 0);
    }

    /**
     * Sets the CAPConnectRedirectingNumberNOA.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectRedirectingNumberNOA(CAPConnectRedirectingNumberNOA avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberNOA, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectRedirectingNumberNPI.
     */
    public boolean containsCAPConnectRedirectingNumberNPI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberNPI);
    }

    /**
     * Gets the CAPConnectRedirectingNumberNPI.
     */
    public CAPConnectRedirectingNumberNPI getCAPConnectRedirectingNumberNPI() throws NoSuchAttributeException {
        return (CAPConnectRedirectingNumberNPI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberNPI, 0);
    }

    /**
     * Sets the CAPConnectRedirectingNumberNPI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectRedirectingNumberNPI(CAPConnectRedirectingNumberNPI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberNPI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectRedirectingNumberARI.
     */
    public boolean containsCAPConnectRedirectingNumberARI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberARI);
    }

    /**
     * Gets the CAPConnectRedirectingNumberARI.
     */
    public CAPConnectRedirectingNumberARI getCAPConnectRedirectingNumberARI() throws NoSuchAttributeException {
        return (CAPConnectRedirectingNumberARI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberARI, 0);
    }

    /**
     * Sets the CAPConnectRedirectingNumberARI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectRedirectingNumberARI(CAPConnectRedirectingNumberARI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectRedirectingNumberARI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectOriginalCalledNumberNOA.
     */
    public boolean containsCAPConnectOriginalCalledNumberNOA() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberNOA);
    }

    /**
     * Gets the CAPConnectOriginalCalledNumberNOA.
     */
    public CAPConnectOriginalCalledNumberNOA getCAPConnectOriginalCalledNumberNOA() throws NoSuchAttributeException {
        return (CAPConnectOriginalCalledNumberNOA)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberNOA, 0);
    }

    /**
     * Sets the CAPConnectOriginalCalledNumberNOA.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectOriginalCalledNumberNOA(CAPConnectOriginalCalledNumberNOA avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberNOA, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectOriginalCalledNumberNPI.
     */
    public boolean containsCAPConnectOriginalCalledNumberNPI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberNPI);
    }

    /**
     * Gets the CAPConnectOriginalCalledNumberNPI.
     */
    public CAPConnectOriginalCalledNumberNPI getCAPConnectOriginalCalledNumberNPI() throws NoSuchAttributeException {
        return (CAPConnectOriginalCalledNumberNPI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberNPI, 0);
    }

    /**
     * Sets the CAPConnectOriginalCalledNumberNPI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectOriginalCalledNumberNPI(CAPConnectOriginalCalledNumberNPI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberNPI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectOriginalCalledNumberARI.
     */
    public boolean containsCAPConnectOriginalCalledNumberARI() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberARI);
    }

    /**
     * Gets the CAPConnectOriginalCalledNumberARI.
     */
    public CAPConnectOriginalCalledNumberARI getCAPConnectOriginalCalledNumberARI() throws NoSuchAttributeException {
        return (CAPConnectOriginalCalledNumberARI)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberARI, 0);
    }

    /**
     * Sets the CAPConnectOriginalCalledNumberARI.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectOriginalCalledNumberARI(CAPConnectOriginalCalledNumberARI avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectOriginalCalledNumberARI, avp.getData(), true);
    }

    /**
     * Tests whether there is any CAPConnectMaxDuration.
     */
    public boolean containsCAPConnectMaxDuration() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPConnectMaxDuration);
    }

    /**
     * Gets the CAPConnectMaxDuration.
     */
    public CAPConnectMaxDuration getCAPConnectMaxDuration() throws NoSuchAttributeException {
        return (CAPConnectMaxDuration)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPConnectMaxDuration, 0);
    }

    /**
     * Sets the CAPConnectMaxDuration.
     *
     * @param avp - the attribute value
     */
    public void setCAPConnectMaxDuration(CAPConnectMaxDuration avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPConnectMaxDuration, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCAPAnnouncementAccessNumber()) {
            sb.append("    CAPAnnouncementAccessNumber:");
            try {
                sb.append(getCAPAnnouncementAccessNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPAnnouncementAccessNumberNOA()) {
            sb.append("    CAPAnnouncementAccessNumberNOA:");
            try {
                sb.append(getCAPAnnouncementAccessNumberNOA()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectDestinationNumber()) {
            sb.append("    CAPConnectDestinationNumber:");
            try {
                sb.append(getCAPConnectDestinationNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectDestinationNumberNature()) {
            sb.append("    CAPConnectDestinationNumberNature:");
            try {
                sb.append(getCAPConnectDestinationNumberNature()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectDestinationNumberNPI()) {
            sb.append("    CAPConnectDestinationNumberNPI:");
            try {
                sb.append(getCAPConnectDestinationNumberNPI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectGenericNumber()) {
            sb.append("    CAPConnectGenericNumber:");
            try {
                sb.append(getCAPConnectGenericNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectCallingCategory()) {
            sb.append("    CAPConnectCallingCategory:");
            try {
                sb.append(getCAPConnectCallingCategory()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectRedirectingNumber()) {
            sb.append("    CAPConnectRedirectingNumber:");
            try {
                sb.append(getCAPConnectRedirectingNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectRedirectingIndicator()) {
            sb.append("    CAPConnectRedirectingIndicator:");
            try {
                sb.append(getCAPConnectRedirectingIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectOriginalRedirectingReason()) {
            sb.append("    CAPConnectOriginalRedirectingReason:");
            try {
                sb.append(getCAPConnectOriginalRedirectingReason()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectRedirectingCounter()) {
            sb.append("    CAPConnectRedirectingCounter:");
            try {
                sb.append(getCAPConnectRedirectingCounter()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectRedirectingReason()) {
            sb.append("    CAPConnectRedirectingReason:");
            try {
                sb.append(getCAPConnectRedirectingReason()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectoCSIApplicable()) {
            sb.append("    CAPConnectoCSIApplicable:");
            try {
                sb.append(getCAPConnectoCSIApplicable()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectSuppressionOfAnnouncement()) {
            sb.append("    CAPConnectSuppressionOfAnnouncement:");
            try {
                sb.append(getCAPConnectSuppressionOfAnnouncement()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectGenericNumberNOA()) {
            sb.append("    CAPConnectGenericNumberNOA:");
            try {
                sb.append(getCAPConnectGenericNumberNOA()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectGenericNumberNPI()) {
            sb.append("    CAPConnectGenericNumberNPI:");
            try {
                sb.append(getCAPConnectGenericNumberNPI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectOriginalCalledNumber()) {
            sb.append("    CAPConnectOriginalCalledNumber:");
            try {
                sb.append(getCAPConnectOriginalCalledNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectDestinationNumberINN()) {
            sb.append("    CAPConnectDestinationNumberINN:");
            try {
                sb.append(getCAPConnectDestinationNumberINN()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectGenericNumberNQI()) {
            sb.append("    CAPConnectGenericNumberNQI:");
            try {
                sb.append(getCAPConnectGenericNumberNQI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectGenericNumberNII()) {
            sb.append("    CAPConnectGenericNumberNII:");
            try {
                sb.append(getCAPConnectGenericNumberNII()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectGenericNumberARI()) {
            sb.append("    CAPConnectGenericNumberARI:");
            try {
                sb.append(getCAPConnectGenericNumberARI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectGenericNumberSCI()) {
            sb.append("    CAPConnectGenericNumberSCI:");
            try {
                sb.append(getCAPConnectGenericNumberSCI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectRedirectingNumberNOA()) {
            sb.append("    CAPConnectRedirectingNumberNOA:");
            try {
                sb.append(getCAPConnectRedirectingNumberNOA()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectRedirectingNumberNPI()) {
            sb.append("    CAPConnectRedirectingNumberNPI:");
            try {
                sb.append(getCAPConnectRedirectingNumberNPI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectRedirectingNumberARI()) {
            sb.append("    CAPConnectRedirectingNumberARI:");
            try {
                sb.append(getCAPConnectRedirectingNumberARI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectOriginalCalledNumberNOA()) {
            sb.append("    CAPConnectOriginalCalledNumberNOA:");
            try {
                sb.append(getCAPConnectOriginalCalledNumberNOA()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectOriginalCalledNumberNPI()) {
            sb.append("    CAPConnectOriginalCalledNumberNPI:");
            try {
                sb.append(getCAPConnectOriginalCalledNumberNPI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectOriginalCalledNumberARI()) {
            sb.append("    CAPConnectOriginalCalledNumberARI:");
            try {
                sb.append(getCAPConnectOriginalCalledNumberARI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCAPConnectMaxDuration()) {
            sb.append("    CAPConnectMaxDuration:");
            try {
                sb.append(getCAPConnectMaxDuration()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
