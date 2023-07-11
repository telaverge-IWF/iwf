package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Recipient-Info AVP (AVP code 2026) is of type Grouped. Its purpose is 
 * to group information associated with a recipient. and contains the list of 
 * Recipient addresses of the message.
 */
public class RecipientInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RecipientInfo.
     */
    public RecipientInfo() {}

    RecipientInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any DestinationInterface.
     */
    public boolean containsDestinationInterface() {
        return _data.getContainer().contains(Ro_r10AttributeName.DestinationInterface);
    }

    /**
     * Gets the DestinationInterface.
     */
    public DestinationInterface getDestinationInterface() throws NoSuchAttributeException {
        return (DestinationInterface)_data.getContainer().get(Ro_r10AttributeName.DestinationInterface, 0);
    }

    /**
     * Sets the DestinationInterface.
     *
     * @param avp - the attribute value
     */
    public void setDestinationInterface(DestinationInterface avp) {
        _data.getContainer().add(Ro_r10AttributeName.DestinationInterface, avp.getData(), true);
    }

    /**
     * Returns number of RecipientAddress instances.
     */
    public int countRecipientAddress() {
        return _data.getContainer().count(Ro_r10AttributeName.RecipientAddress);
    }

    /**
     * Gets one RecipientAddress.
     *
     * @param index - the index of the attribute to return
     */
    public RecipientAddress getRecipientAddress(int index) throws NoSuchAttributeException {
        return (RecipientAddress)_data.getContainer().get(Ro_r10AttributeName.RecipientAddress, index);
    }

    /**
     * Adds one RecipientAddress.
     *
     * @param avp - the attribute value
     */
    public void addRecipientAddress(RecipientAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.RecipientAddress, avp.getData(), false);
    }

    /**
     * Returns number of RecipientReceivedAddress instances.
     */
    public int countRecipientReceivedAddress() {
        return _data.getContainer().count(Ro_r10AttributeName.RecipientReceivedAddress);
    }

    /**
     * Gets one RecipientReceivedAddress.
     *
     * @param index - the index of the attribute to return
     */
    public RecipientReceivedAddress getRecipientReceivedAddress(int index) throws NoSuchAttributeException {
        return (RecipientReceivedAddress)_data.getContainer().get(Ro_r10AttributeName.RecipientReceivedAddress, index);
    }

    /**
     * Adds one RecipientReceivedAddress.
     *
     * @param avp - the attribute value
     */
    public void addRecipientReceivedAddress(RecipientReceivedAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.RecipientReceivedAddress, avp.getData(), false);
    }

    /**
     * Tests whether there is any RecipientSCCPAddress.
     */
    public boolean containsRecipientSCCPAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.RecipientSCCPAddress);
    }

    /**
     * Gets the RecipientSCCPAddress.
     */
    public RecipientSCCPAddress getRecipientSCCPAddress() throws NoSuchAttributeException {
        return (RecipientSCCPAddress)_data.getContainer().get(Ro_r10AttributeName.RecipientSCCPAddress, 0);
    }

    /**
     * Sets the RecipientSCCPAddress.
     *
     * @param avp - the attribute value
     */
    public void setRecipientSCCPAddress(RecipientSCCPAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.RecipientSCCPAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMProtocolID.
     */
    public boolean containsSMProtocolID() {
        return _data.getContainer().contains(Ro_r10AttributeName.SMProtocolID);
    }

    /**
     * Gets the SMProtocolID.
     */
    public SMProtocolID getSMProtocolID() throws NoSuchAttributeException {
        return (SMProtocolID)_data.getContainer().get(Ro_r10AttributeName.SMProtocolID, 0);
    }

    /**
     * Sets the SMProtocolID.
     *
     * @param avp - the attribute value
     */
    public void setSMProtocolID(SMProtocolID avp) {
        _data.getContainer().add(Ro_r10AttributeName.SMProtocolID, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsDestinationInterface()) {
            sb.append("    DestinationInterface:");
            try {
                sb.append(getDestinationInterface()).append('\n');
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
        for (int i = 0; i < countRecipientReceivedAddress(); ++i) {
            sb.append("    RecipientReceivedAddress:");
            try {
                sb.append(getRecipientReceivedAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRecipientSCCPAddress()) {
            sb.append("    RecipientSCCPAddress:");
            try {
                sb.append(getRecipientSCCPAddress()).append('\n');
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
        return sb.append('}').toString();
    }
}
