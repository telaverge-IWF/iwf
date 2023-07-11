package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Carrier-Select-Routing-Information AVP (AVP code 2023) is of type 
 * UTF8String. This AVP holds information on carrier selection performed by 
 * S-CSCF/AS. This information is sent over SIP in the Requested URI header.
 */
public class CarrierSelectRoutingInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CarrierSelectRoutingInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public CarrierSelectRoutingInformation(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CarrierSelectRoutingInformation(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
