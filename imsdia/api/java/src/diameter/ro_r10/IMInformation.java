package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The IM-Information AVP (AVP code 2110) is of type Grouped. Its purpose is 
 * to allow the transmission of service information elements used for IM services.
 */
public class IMInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new IMInformation.
     */
    public IMInformation() {}

    IMInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any TotalNumberOfMessagesSent.
     */
    public boolean containsTotalNumberOfMessagesSent() {
        return _data.getContainer().contains(Ro_r10AttributeName.TotalNumberOfMessagesSent);
    }

    /**
     * Gets the TotalNumberOfMessagesSent.
     */
    public TotalNumberOfMessagesSent getTotalNumberOfMessagesSent() throws NoSuchAttributeException {
        return (TotalNumberOfMessagesSent)_data.getContainer().get(Ro_r10AttributeName.TotalNumberOfMessagesSent, 0);
    }

    /**
     * Sets the TotalNumberOfMessagesSent.
     *
     * @param avp - the attribute value
     */
    public void setTotalNumberOfMessagesSent(TotalNumberOfMessagesSent avp) {
        _data.getContainer().add(Ro_r10AttributeName.TotalNumberOfMessagesSent, avp.getData(), true);
    }

    /**
     * Tests whether there is any TotalNumberOfMessagesExploded.
     */
    public boolean containsTotalNumberOfMessagesExploded() {
        return _data.getContainer().contains(Ro_r10AttributeName.TotalNumberOfMessagesExploded);
    }

    /**
     * Gets the TotalNumberOfMessagesExploded.
     */
    public TotalNumberOfMessagesExploded getTotalNumberOfMessagesExploded() throws NoSuchAttributeException {
        return (TotalNumberOfMessagesExploded)_data.getContainer().get(Ro_r10AttributeName.TotalNumberOfMessagesExploded, 0);
    }

    /**
     * Sets the TotalNumberOfMessagesExploded.
     *
     * @param avp - the attribute value
     */
    public void setTotalNumberOfMessagesExploded(TotalNumberOfMessagesExploded avp) {
        _data.getContainer().add(Ro_r10AttributeName.TotalNumberOfMessagesExploded, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfMessagesSuccessfullySent.
     */
    public boolean containsNumberOfMessagesSuccessfullySent() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberOfMessagesSuccessfullySent);
    }

    /**
     * Gets the NumberOfMessagesSuccessfullySent.
     */
    public NumberOfMessagesSuccessfullySent getNumberOfMessagesSuccessfullySent() throws NoSuchAttributeException {
        return (NumberOfMessagesSuccessfullySent)_data.getContainer().get(Ro_r10AttributeName.NumberOfMessagesSuccessfullySent, 0);
    }

    /**
     * Sets the NumberOfMessagesSuccessfullySent.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfMessagesSuccessfullySent(NumberOfMessagesSuccessfullySent avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberOfMessagesSuccessfullySent, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfMessagesSuccessfullyExploded.
     */
    public boolean containsNumberOfMessagesSuccessfullyExploded() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberOfMessagesSuccessfullyExploded);
    }

    /**
     * Gets the NumberOfMessagesSuccessfullyExploded.
     */
    public NumberOfMessagesSuccessfullyExploded getNumberOfMessagesSuccessfullyExploded() throws NoSuchAttributeException {
        return (NumberOfMessagesSuccessfullyExploded)_data.getContainer().get(Ro_r10AttributeName.NumberOfMessagesSuccessfullyExploded, 0);
    }

    /**
     * Sets the NumberOfMessagesSuccessfullyExploded.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfMessagesSuccessfullyExploded(NumberOfMessagesSuccessfullyExploded avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberOfMessagesSuccessfullyExploded, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsTotalNumberOfMessagesSent()) {
            sb.append("    TotalNumberOfMessagesSent:");
            try {
                sb.append(getTotalNumberOfMessagesSent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTotalNumberOfMessagesExploded()) {
            sb.append("    TotalNumberOfMessagesExploded:");
            try {
                sb.append(getTotalNumberOfMessagesExploded()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberOfMessagesSuccessfullySent()) {
            sb.append("    NumberOfMessagesSuccessfullySent:");
            try {
                sb.append(getNumberOfMessagesSuccessfullySent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberOfMessagesSuccessfullyExploded()) {
            sb.append("    NumberOfMessagesSuccessfullyExploded:");
            try {
                sb.append(getNumberOfMessagesSuccessfullyExploded()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
