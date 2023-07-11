package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The SMS-Information AVP (AVP code 2000) is of type Grouped. 
 * Its purpose is to allow the transmission of additional SMS service specific information elements. 
*/
public class SMSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SMSInformation.
     */
    public SMSInformation() {}

    SMSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SMSNode.
     */
    public boolean containsSMSNode() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMSNode);
    }

    /**
     * Gets the SMSNode.
     */
    public SMSNode getSMSNode() throws NoSuchAttributeException {
        return (SMSNode)_data.getContainer().get(Ro_r10_transatelAttributeName.SMSNode, 0);
    }

    /**
     * Sets the SMSNode.
     *
     * @param avp - the attribute value
     */
    public void setSMSNode(SMSNode avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMSNode, avp.getData(), true);
    }

    /**
     * Tests whether there is any ClientAddress.
     */
    public boolean containsClientAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ClientAddress);
    }

    /**
     * Gets the ClientAddress.
     */
    public ClientAddress getClientAddress() throws NoSuchAttributeException {
        return (ClientAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.ClientAddress, 0);
    }

    /**
     * Sets the ClientAddress.
     *
     * @param avp - the attribute value
     */
    public void setClientAddress(ClientAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ClientAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any OriginatorSCCPAddress.
     */
    public boolean containsOriginatorSCCPAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.OriginatorSCCPAddress);
    }

    /**
     * Gets the OriginatorSCCPAddress.
     */
    public OriginatorSCCPAddress getOriginatorSCCPAddress() throws NoSuchAttributeException {
        return (OriginatorSCCPAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.OriginatorSCCPAddress, 0);
    }

    /**
     * Sets the OriginatorSCCPAddress.
     *
     * @param avp - the attribute value
     */
    public void setOriginatorSCCPAddress(OriginatorSCCPAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.OriginatorSCCPAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMSCAddress.
     */
    public boolean containsSMSCAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMSCAddress);
    }

    /**
     * Gets the SMSCAddress.
     */
    public SMSCAddress getSMSCAddress() throws NoSuchAttributeException {
        return (SMSCAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.SMSCAddress, 0);
    }

    /**
     * Sets the SMSCAddress.
     *
     * @param avp - the attribute value
     */
    public void setSMSCAddress(SMSCAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMSCAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any DataCodingScheme.
     */
    public boolean containsDataCodingScheme() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.DataCodingScheme);
    }

    /**
     * Gets the DataCodingScheme.
     */
    public DataCodingScheme getDataCodingScheme() throws NoSuchAttributeException {
        return (DataCodingScheme)_data.getContainer().get(Ro_r10_transatelAttributeName.DataCodingScheme, 0);
    }

    /**
     * Sets the DataCodingScheme.
     *
     * @param avp - the attribute value
     */
    public void setDataCodingScheme(DataCodingScheme avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.DataCodingScheme, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMDischargeTime.
     */
    public boolean containsSMDischargeTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMDischargeTime);
    }

    /**
     * Gets the SMDischargeTime.
     */
    public SMDischargeTime getSMDischargeTime() throws NoSuchAttributeException {
        return (SMDischargeTime)_data.getContainer().get(Ro_r10_transatelAttributeName.SMDischargeTime, 0);
    }

    /**
     * Sets the SMDischargeTime.
     *
     * @param avp - the attribute value
     */
    public void setSMDischargeTime(SMDischargeTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMDischargeTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMMessageType.
     */
    public boolean containsSMMessageType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMMessageType);
    }

    /**
     * Gets the SMMessageType.
     */
    public SMMessageType getSMMessageType() throws NoSuchAttributeException {
        return (SMMessageType)_data.getContainer().get(Ro_r10_transatelAttributeName.SMMessageType, 0);
    }

    /**
     * Sets the SMMessageType.
     *
     * @param avp - the attribute value
     */
    public void setSMMessageType(SMMessageType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMMessageType, avp.getData(), true);
    }

    /**
     * Tests whether there is any OriginatorInterface.
     */
    public boolean containsOriginatorInterface() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.OriginatorInterface);
    }

    /**
     * Gets the OriginatorInterface.
     */
    public OriginatorInterface getOriginatorInterface() throws NoSuchAttributeException {
        return (OriginatorInterface)_data.getContainer().get(Ro_r10_transatelAttributeName.OriginatorInterface, 0);
    }

    /**
     * Sets the OriginatorInterface.
     *
     * @param avp - the attribute value
     */
    public void setOriginatorInterface(OriginatorInterface avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.OriginatorInterface, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMProtocolID.
     */
    public boolean containsSMProtocolID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMProtocolID);
    }

    /**
     * Gets the SMProtocolID.
     */
    public SMProtocolID getSMProtocolID() throws NoSuchAttributeException {
        return (SMProtocolID)_data.getContainer().get(Ro_r10_transatelAttributeName.SMProtocolID, 0);
    }

    /**
     * Sets the SMProtocolID.
     *
     * @param avp - the attribute value
     */
    public void setSMProtocolID(SMProtocolID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMProtocolID, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReplyPathRequested.
     */
    public boolean containsReplyPathRequested() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ReplyPathRequested);
    }

    /**
     * Gets the ReplyPathRequested.
     */
    public ReplyPathRequested getReplyPathRequested() throws NoSuchAttributeException {
        return (ReplyPathRequested)_data.getContainer().get(Ro_r10_transatelAttributeName.ReplyPathRequested, 0);
    }

    /**
     * Sets the ReplyPathRequested.
     *
     * @param avp - the attribute value
     */
    public void setReplyPathRequested(ReplyPathRequested avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ReplyPathRequested, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMStatus.
     */
    public boolean containsSMStatus() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMStatus);
    }

    /**
     * Gets the SMStatus.
     */
    public SMStatus getSMStatus() throws NoSuchAttributeException {
        return (SMStatus)_data.getContainer().get(Ro_r10_transatelAttributeName.SMStatus, 0);
    }

    /**
     * Sets the SMStatus.
     *
     * @param avp - the attribute value
     */
    public void setSMStatus(SMStatus avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMStatus, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMUserDataHeader.
     */
    public boolean containsSMUserDataHeader() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMUserDataHeader);
    }

    /**
     * Gets the SMUserDataHeader.
     */
    public SMUserDataHeader getSMUserDataHeader() throws NoSuchAttributeException {
        return (SMUserDataHeader)_data.getContainer().get(Ro_r10_transatelAttributeName.SMUserDataHeader, 0);
    }

    /**
     * Sets the SMUserDataHeader.
     *
     * @param avp - the attribute value
     */
    public void setSMUserDataHeader(SMUserDataHeader avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMUserDataHeader, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfMessagesSent.
     */
    public boolean containsNumberOfMessagesSent() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.NumberOfMessagesSent);
    }

    /**
     * Gets the NumberOfMessagesSent.
     */
    public NumberOfMessagesSent getNumberOfMessagesSent() throws NoSuchAttributeException {
        return (NumberOfMessagesSent)_data.getContainer().get(Ro_r10_transatelAttributeName.NumberOfMessagesSent, 0);
    }

    /**
     * Sets the NumberOfMessagesSent.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfMessagesSent(NumberOfMessagesSent avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.NumberOfMessagesSent, avp.getData(), true);
    }

    /**
     * Returns number of RecipientInfo instances.
     */
    public int countRecipientInfo() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.RecipientInfo);
    }

    /**
     * Gets one RecipientInfo.
     *
     * @param index - the index of the attribute to return
     */
    public RecipientInfo getRecipientInfo(int index) throws NoSuchAttributeException {
        return (RecipientInfo)_data.getContainer().get(Ro_r10_transatelAttributeName.RecipientInfo, index);
    }

    /**
     * Adds one RecipientInfo.
     *
     * @param avp - the attribute value
     */
    public void addRecipientInfo(RecipientInfo avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.RecipientInfo, avp.getData(), false);
    }

    /**
     * Tests whether there is any OriginatorReceivedAddress.
     */
    public boolean containsOriginatorReceivedAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.OriginatorReceivedAddress);
    }

    /**
     * Gets the OriginatorReceivedAddress.
     */
    public OriginatorReceivedAddress getOriginatorReceivedAddress() throws NoSuchAttributeException {
        return (OriginatorReceivedAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.OriginatorReceivedAddress, 0);
    }

    /**
     * Sets the OriginatorReceivedAddress.
     *
     * @param avp - the attribute value
     */
    public void setOriginatorReceivedAddress(OriginatorReceivedAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.OriginatorReceivedAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMServiceType.
     */
    public boolean containsSMServiceType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SMServiceType);
    }

    /**
     * Gets the SMServiceType.
     */
    public SMServiceType getSMServiceType() throws NoSuchAttributeException {
        return (SMServiceType)_data.getContainer().get(Ro_r10_transatelAttributeName.SMServiceType, 0);
    }

    /**
     * Sets the SMServiceType.
     *
     * @param avp - the attribute value
     */
    public void setSMServiceType(SMServiceType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SMServiceType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsSMSNode()) {
            sb.append("    SMSNode:");
            try {
                sb.append(getSMSNode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsClientAddress()) {
            sb.append("    ClientAddress:");
            try {
                sb.append(getClientAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOriginatorSCCPAddress()) {
            sb.append("    OriginatorSCCPAddress:");
            try {
                sb.append(getOriginatorSCCPAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMSCAddress()) {
            sb.append("    SMSCAddress:");
            try {
                sb.append(getSMSCAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDataCodingScheme()) {
            sb.append("    DataCodingScheme:");
            try {
                sb.append(getDataCodingScheme()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMDischargeTime()) {
            sb.append("    SMDischargeTime:");
            try {
                sb.append(getSMDischargeTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMMessageType()) {
            sb.append("    SMMessageType:");
            try {
                sb.append(getSMMessageType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOriginatorInterface()) {
            sb.append("    OriginatorInterface:");
            try {
                sb.append(getOriginatorInterface()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMProtocolID()) {
            sb.append("    SMProtocolID:");
            try {
                sb.append(getSMProtocolID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReplyPathRequested()) {
            sb.append("    ReplyPathRequested:");
            try {
                sb.append(getReplyPathRequested()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMStatus()) {
            sb.append("    SMStatus:");
            try {
                sb.append(getSMStatus()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMUserDataHeader()) {
            sb.append("    SMUserDataHeader:");
            try {
                sb.append(getSMUserDataHeader()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberOfMessagesSent()) {
            sb.append("    NumberOfMessagesSent:");
            try {
                sb.append(getNumberOfMessagesSent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRecipientInfo(); ++i) {
            sb.append("    RecipientInfo:");
            try {
                sb.append(getRecipientInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOriginatorReceivedAddress()) {
            sb.append("    OriginatorReceivedAddress:");
            try {
                sb.append(getOriginatorReceivedAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMServiceType()) {
            sb.append("    SMServiceType:");
            try {
                sb.append(getSMServiceType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
