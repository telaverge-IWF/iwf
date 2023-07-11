package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The NAS-Filter-Rule AVP (AVP Code 400) is of type IPFilterRule and provides
 * filter rules that need to be configured on the NAS for the user. One or more
 * of these AVPs MAY be present in an authorization response.
 */
public class NASFilterRule extends com.intellinet.diameter.DerivedAVP<IPFilterRule> {
    /**
     * Constructs a NASFilterRule with the given value.
     *
     * @param value - the value of the AVP
     */
    public NASFilterRule(IPFilterRule value) {
        super(new com.intellinet.diameter.IPFilterRuleData(value));
    }

    NASFilterRule(com.intellinet.diameter.IPFilterRuleData data) {
        super(data);
    }
}
