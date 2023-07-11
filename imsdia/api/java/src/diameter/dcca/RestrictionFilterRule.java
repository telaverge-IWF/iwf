package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Restriction-Filter-Rule AVP (AVP Code 438) is of type IPFilterRule and provides filter 
 * rules corresponding to services that are to remain accessible even if there are no more service 
 * units granted. The access device has to configure the specified filter rules for the subscriber 
 * and MUST drop all the packets not matching these filters.
 */
public class RestrictionFilterRule extends com.intellinet.diameter.DerivedAVP<IPFilterRule> {
    /**
     * Constructs a RestrictionFilterRule with the given value.
     *
     * @param value - the value of the AVP
     */
    public RestrictionFilterRule(IPFilterRule value) {
        super(new com.intellinet.diameter.IPFilterRuleData(value));
    }

    RestrictionFilterRule(com.intellinet.diameter.IPFilterRuleData data) {
        super(data);
    }
}
