package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Cost-Unit AVP is of type UTF8String, and it is used to display a human readable string to
 * the end user.  It specifies the applicable unit to the Cost-Information when the service cost
 * is a cost per unit (e.g., cost of the service is $1 per minute). The Cost-Unit can be minutes,
 * hours, days, kilobytes,megabytes, etc.
 */
public class CostUnit extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CostUnit with the given value.
     *
     * @param value - the value of the AVP
     */
    public CostUnit(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CostUnit(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
