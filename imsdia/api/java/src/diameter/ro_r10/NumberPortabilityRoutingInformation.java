package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 *The Number-Portability-Routing-Information AVP (AVP code 2024) is of type 
 * UTF8String. This AVP holds information on the routing number received by 
 * S-CSCF during number portability look-up (ENUM/DNS). This information is 
 * sent over SIP in the Requested URI header.
 */
public class NumberPortabilityRoutingInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a NumberPortabilityRoutingInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberPortabilityRoutingInformation(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    NumberPortabilityRoutingInformation(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
