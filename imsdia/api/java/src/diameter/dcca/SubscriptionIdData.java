package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * Subscription-Id-Data AVP is used to identity the end user and is of type UTF8String.
 */
public class SubscriptionIdData extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SubscriptionIdData with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubscriptionIdData(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    SubscriptionIdData(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
