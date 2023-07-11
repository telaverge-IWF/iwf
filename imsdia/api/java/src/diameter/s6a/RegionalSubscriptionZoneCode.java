package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Regional-Subscription-Zone-Code AVP is of type OctetString. Up to 10 zone codes 
 * are used to define the tracking areas into which the subscriber is allowed or 
 * not allowed to roam. See 3GPP TS 23.003 [3].
 */
public class RegionalSubscriptionZoneCode extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RegionalSubscriptionZoneCode with the given value.
     *
     * @param value - the value of the AVP
     */
    public RegionalSubscriptionZoneCode(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    RegionalSubscriptionZoneCode(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
