package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The QoS-Filter-Rule AVP (AVP Code 407) is of type QoSFilterRule and provides
 * QoS filter rules that need to be configured on the NAS for the user. One or
 * more such AVPs MAY be present in an authorization response.
 */
public class QoSFilterRule extends com.intellinet.diameter.DerivedAVP<IPFilterRule> {
    /**
     * Constructs a QoSFilterRule with the given value.
     *
     * @param value - the value of the AVP
     */
    public QoSFilterRule(IPFilterRule value) {
        super(new com.intellinet.diameter.IPFilterRuleData(value));
    }

    QoSFilterRule(com.intellinet.diameter.IPFilterRuleData data) {
        super(data);
    }
}
