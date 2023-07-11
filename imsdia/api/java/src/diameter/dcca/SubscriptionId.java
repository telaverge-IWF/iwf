package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * Subscription-Id AVP is used to identity the end user's subscription and is of type Grouped.
 */
public class SubscriptionId extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SubscriptionId.
     */
    public SubscriptionId() {}

    SubscriptionId(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the SubscriptionIdType.
     */
    public SubscriptionIdType getSubscriptionIdType() throws NoSuchAttributeException {
        return (SubscriptionIdType)_data.getContainer().get(DccaAttributeName.SubscriptionIdType, 0);
    }

    /**
     * Sets the SubscriptionIdType.
     *
     * @param avp - the attribute value
     */
    public void setSubscriptionIdType(SubscriptionIdType avp) {
        _data.getContainer().add(DccaAttributeName.SubscriptionIdType, avp.getData(), true);
    }

    /**
     * Gets the SubscriptionIdData.
     */
    public SubscriptionIdData getSubscriptionIdData() throws NoSuchAttributeException {
        return (SubscriptionIdData)_data.getContainer().get(DccaAttributeName.SubscriptionIdData, 0);
    }

    /**
     * Sets the SubscriptionIdData.
     *
     * @param avp - the attribute value
     */
    public void setSubscriptionIdData(SubscriptionIdData avp) {
        _data.getContainer().add(DccaAttributeName.SubscriptionIdData, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    SubscriptionIdType:");
            try {
                sb.append(getSubscriptionIdType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    SubscriptionIdData:");
            try {
                sb.append(getSubscriptionIdData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        return sb.append('}').toString();
    }
}
