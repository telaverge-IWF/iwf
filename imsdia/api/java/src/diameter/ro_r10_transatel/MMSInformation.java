package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * MMS-Information AVP is of type Grouped. Its purpose is to allow the transmission of additional 
 * MMS service specific information elements.
 */
public class MMSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MMSInformation.
     */
    public MMSInformation() {}

    MMSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any OriginatorAddress.
     */
    public boolean containsOriginatorAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.OriginatorAddress);
    }

    /**
     * Gets the OriginatorAddress.
     */
    public OriginatorAddress getOriginatorAddress() throws NoSuchAttributeException {
        return (OriginatorAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.OriginatorAddress, 0);
    }

    /**
     * Sets the OriginatorAddress.
     *
     * @param avp - the attribute value
     */
    public void setOriginatorAddress(OriginatorAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.OriginatorAddress, avp.getData(), true);
    }

    /**
     * Returns number of RecipientAddress instances.
     */
    public int countRecipientAddress() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.RecipientAddress);
    }

    /**
     * Gets one RecipientAddress.
     *
     * @param index - the index of the attribute to return
     */
    public RecipientAddress getRecipientAddress(int index) throws NoSuchAttributeException {
        return (RecipientAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.RecipientAddress, index);
    }

    /**
     * Adds one RecipientAddress.
     *
     * @param avp - the attribute value
     */
    public void addRecipientAddress(RecipientAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.RecipientAddress, avp.getData(), false);
    }

    /**
     * Tests whether there is any SubmissionTime.
     */
    public boolean containsSubmissionTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SubmissionTime);
    }

    /**
     * Gets the SubmissionTime.
     */
    public SubmissionTime getSubmissionTime() throws NoSuchAttributeException {
        return (SubmissionTime)_data.getContainer().get(Ro_r10_transatelAttributeName.SubmissionTime, 0);
    }

    /**
     * Sets the SubmissionTime.
     *
     * @param avp - the attribute value
     */
    public void setSubmissionTime(SubmissionTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SubmissionTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any MMContentType.
     */
    public boolean containsMMContentType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MMContentType);
    }

    /**
     * Gets the MMContentType.
     */
    public MMContentType getMMContentType() throws NoSuchAttributeException {
        return (MMContentType)_data.getContainer().get(Ro_r10_transatelAttributeName.MMContentType, 0);
    }

    /**
     * Sets the MMContentType.
     *
     * @param avp - the attribute value
     */
    public void setMMContentType(MMContentType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MMContentType, avp.getData(), true);
    }

    /**
     * Tests whether there is any Priority.
     */
    public boolean containsPriority() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Priority);
    }

    /**
     * Gets the Priority.
     */
    public Priority getPriority() throws NoSuchAttributeException {
        return (Priority)_data.getContainer().get(Ro_r10_transatelAttributeName.Priority, 0);
    }

    /**
     * Sets the Priority.
     *
     * @param avp - the attribute value
     */
    public void setPriority(Priority avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Priority, avp.getData(), true);
    }

    /**
     * Tests whether there is any MessageID.
     */
    public boolean containsMessageID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MessageID);
    }

    /**
     * Gets the MessageID.
     */
    public MessageID getMessageID() throws NoSuchAttributeException {
        return (MessageID)_data.getContainer().get(Ro_r10_transatelAttributeName.MessageID, 0);
    }

    /**
     * Sets the MessageID.
     *
     * @param avp - the attribute value
     */
    public void setMessageID(MessageID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MessageID, avp.getData(), true);
    }

    /**
     * Tests whether there is any MessageType.
     */
    public boolean containsMessageType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MessageType);
    }

    /**
     * Gets the MessageType.
     */
    public MessageType getMessageType() throws NoSuchAttributeException {
        return (MessageType)_data.getContainer().get(Ro_r10_transatelAttributeName.MessageType, 0);
    }

    /**
     * Sets the MessageType.
     *
     * @param avp - the attribute value
     */
    public void setMessageType(MessageType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MessageType, avp.getData(), true);
    }

    /**
     * Tests whether there is any MessageSize.
     */
    public boolean containsMessageSize() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MessageSize);
    }

    /**
     * Gets the MessageSize.
     */
    public MessageSize getMessageSize() throws NoSuchAttributeException {
        return (MessageSize)_data.getContainer().get(Ro_r10_transatelAttributeName.MessageSize, 0);
    }

    /**
     * Sets the MessageSize.
     *
     * @param avp - the attribute value
     */
    public void setMessageSize(MessageSize avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MessageSize, avp.getData(), true);
    }

    /**
     * Tests whether there is any MessageClass.
     */
    public boolean containsMessageClass() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MessageClass);
    }

    /**
     * Gets the MessageClass.
     */
    public MessageClass getMessageClass() throws NoSuchAttributeException {
        return (MessageClass)_data.getContainer().get(Ro_r10_transatelAttributeName.MessageClass, 0);
    }

    /**
     * Sets the MessageClass.
     *
     * @param avp - the attribute value
     */
    public void setMessageClass(MessageClass avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MessageClass, avp.getData(), true);
    }

    /**
     * Tests whether there is any DeliveryReportRequested.
     */
    public boolean containsDeliveryReportRequested() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.DeliveryReportRequested);
    }

    /**
     * Gets the DeliveryReportRequested.
     */
    public DeliveryReportRequested getDeliveryReportRequested() throws NoSuchAttributeException {
        return (DeliveryReportRequested)_data.getContainer().get(Ro_r10_transatelAttributeName.DeliveryReportRequested, 0);
    }

    /**
     * Sets the DeliveryReportRequested.
     *
     * @param avp - the attribute value
     */
    public void setDeliveryReportRequested(DeliveryReportRequested avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.DeliveryReportRequested, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReadReplyReportRequested.
     */
    public boolean containsReadReplyReportRequested() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ReadReplyReportRequested);
    }

    /**
     * Gets the ReadReplyReportRequested.
     */
    public ReadReplyReportRequested getReadReplyReportRequested() throws NoSuchAttributeException {
        return (ReadReplyReportRequested)_data.getContainer().get(Ro_r10_transatelAttributeName.ReadReplyReportRequested, 0);
    }

    /**
     * Sets the ReadReplyReportRequested.
     *
     * @param avp - the attribute value
     */
    public void setReadReplyReportRequested(ReadReplyReportRequested avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ReadReplyReportRequested, avp.getData(), true);
    }

    /**
     * Tests whether there is any MMBoxStorageRequested.
     */
    public boolean containsMMBoxStorageRequested() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MMBoxStorageRequested);
    }

    /**
     * Gets the MMBoxStorageRequested.
     */
    public MMBoxStorageRequested getMMBoxStorageRequested() throws NoSuchAttributeException {
        return (MMBoxStorageRequested)_data.getContainer().get(Ro_r10_transatelAttributeName.MMBoxStorageRequested, 0);
    }

    /**
     * Sets the MMBoxStorageRequested.
     *
     * @param avp - the attribute value
     */
    public void setMMBoxStorageRequested(MMBoxStorageRequested avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MMBoxStorageRequested, avp.getData(), true);
    }

    /**
     * Tests whether there is any ApplicID.
     */
    public boolean containsApplicID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ApplicID);
    }

    /**
     * Gets the ApplicID.
     */
    public ApplicID getApplicID() throws NoSuchAttributeException {
        return (ApplicID)_data.getContainer().get(Ro_r10_transatelAttributeName.ApplicID, 0);
    }

    /**
     * Sets the ApplicID.
     *
     * @param avp - the attribute value
     */
    public void setApplicID(ApplicID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ApplicID, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReplyApplicID.
     */
    public boolean containsReplyApplicID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ReplyApplicID);
    }

    /**
     * Gets the ReplyApplicID.
     */
    public ReplyApplicID getReplyApplicID() throws NoSuchAttributeException {
        return (ReplyApplicID)_data.getContainer().get(Ro_r10_transatelAttributeName.ReplyApplicID, 0);
    }

    /**
     * Sets the ReplyApplicID.
     *
     * @param avp - the attribute value
     */
    public void setReplyApplicID(ReplyApplicID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ReplyApplicID, avp.getData(), true);
    }

    /**
     * Tests whether there is any AuxApplicInfo.
     */
    public boolean containsAuxApplicInfo() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AuxApplicInfo);
    }

    /**
     * Gets the AuxApplicInfo.
     */
    public AuxApplicInfo getAuxApplicInfo() throws NoSuchAttributeException {
        return (AuxApplicInfo)_data.getContainer().get(Ro_r10_transatelAttributeName.AuxApplicInfo, 0);
    }

    /**
     * Sets the AuxApplicInfo.
     *
     * @param avp - the attribute value
     */
    public void setAuxApplicInfo(AuxApplicInfo avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AuxApplicInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any ContentClass.
     */
    public boolean containsContentClass() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ContentClass);
    }

    /**
     * Gets the ContentClass.
     */
    public ContentClass getContentClass() throws NoSuchAttributeException {
        return (ContentClass)_data.getContainer().get(Ro_r10_transatelAttributeName.ContentClass, 0);
    }

    /**
     * Sets the ContentClass.
     *
     * @param avp - the attribute value
     */
    public void setContentClass(ContentClass avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ContentClass, avp.getData(), true);
    }

    /**
     * Tests whether there is any DRMContent.
     */
    public boolean containsDRMContent() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.DRMContent);
    }

    /**
     * Gets the DRMContent.
     */
    public DRMContent getDRMContent() throws NoSuchAttributeException {
        return (DRMContent)_data.getContainer().get(Ro_r10_transatelAttributeName.DRMContent, 0);
    }

    /**
     * Sets the DRMContent.
     *
     * @param avp - the attribute value
     */
    public void setDRMContent(DRMContent avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.DRMContent, avp.getData(), true);
    }

    /**
     * Tests whether there is any Adaptations.
     */
    public boolean containsAdaptations() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Adaptations);
    }

    /**
     * Gets the Adaptations.
     */
    public Adaptations getAdaptations() throws NoSuchAttributeException {
        return (Adaptations)_data.getContainer().get(Ro_r10_transatelAttributeName.Adaptations, 0);
    }

    /**
     * Sets the Adaptations.
     *
     * @param avp - the attribute value
     */
    public void setAdaptations(Adaptations avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Adaptations, avp.getData(), true);
    }

    /**
     * Tests whether there is any VASPId.
     */
    public boolean containsVASPId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.VASPId);
    }

    /**
     * Gets the VASPId.
     */
    public VASPId getVASPId() throws NoSuchAttributeException {
        return (VASPId)_data.getContainer().get(Ro_r10_transatelAttributeName.VASPId, 0);
    }

    /**
     * Sets the VASPId.
     *
     * @param avp - the attribute value
     */
    public void setVASPId(VASPId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.VASPId, avp.getData(), true);
    }

    /**
     * Tests whether there is any VASId.
     */
    public boolean containsVASId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.VASId);
    }

    /**
     * Gets the VASId.
     */
    public VASId getVASId() throws NoSuchAttributeException {
        return (VASId)_data.getContainer().get(Ro_r10_transatelAttributeName.VASId, 0);
    }

    /**
     * Sets the VASId.
     *
     * @param avp - the attribute value
     */
    public void setVASId(VASId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.VASId, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsOriginatorAddress()) {
            sb.append("    OriginatorAddress:");
            try {
                sb.append(getOriginatorAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRecipientAddress(); ++i) {
            sb.append("    RecipientAddress:");
            try {
                sb.append(getRecipientAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSubmissionTime()) {
            sb.append("    SubmissionTime:");
            try {
                sb.append(getSubmissionTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMMContentType()) {
            sb.append("    MMContentType:");
            try {
                sb.append(getMMContentType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPriority()) {
            sb.append("    Priority:");
            try {
                sb.append(getPriority()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMessageID()) {
            sb.append("    MessageID:");
            try {
                sb.append(getMessageID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMessageType()) {
            sb.append("    MessageType:");
            try {
                sb.append(getMessageType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMessageSize()) {
            sb.append("    MessageSize:");
            try {
                sb.append(getMessageSize()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMessageClass()) {
            sb.append("    MessageClass:");
            try {
                sb.append(getMessageClass()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDeliveryReportRequested()) {
            sb.append("    DeliveryReportRequested:");
            try {
                sb.append(getDeliveryReportRequested()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReadReplyReportRequested()) {
            sb.append("    ReadReplyReportRequested:");
            try {
                sb.append(getReadReplyReportRequested()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMMBoxStorageRequested()) {
            sb.append("    MMBoxStorageRequested:");
            try {
                sb.append(getMMBoxStorageRequested()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsApplicID()) {
            sb.append("    ApplicID:");
            try {
                sb.append(getApplicID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReplyApplicID()) {
            sb.append("    ReplyApplicID:");
            try {
                sb.append(getReplyApplicID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAuxApplicInfo()) {
            sb.append("    AuxApplicInfo:");
            try {
                sb.append(getAuxApplicInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsContentClass()) {
            sb.append("    ContentClass:");
            try {
                sb.append(getContentClass()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDRMContent()) {
            sb.append("    DRMContent:");
            try {
                sb.append(getDRMContent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAdaptations()) {
            sb.append("    Adaptations:");
            try {
                sb.append(getAdaptations()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVASPId()) {
            sb.append("    VASPId:");
            try {
                sb.append(getVASPId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVASId()) {
            sb.append("    VASId:");
            try {
                sb.append(getVASId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
