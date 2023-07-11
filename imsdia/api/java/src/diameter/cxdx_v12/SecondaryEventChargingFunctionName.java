package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Secondary-Event-Charging-Function-Name AVP is of type DiameterURI. This AVP contains the address of the
 * Secondary Event Charging Function.
 */
public class SecondaryEventChargingFunctionName extends com.intellinet.diameter.DerivedAVP<URI> {
    /**
     * Constructs a SecondaryEventChargingFunctionName with the given value.
     *
     * @param value - the value of the AVP
     */
    public SecondaryEventChargingFunctionName(URI value) {
        super(new com.intellinet.diameter.URIData(value));
    }

    SecondaryEventChargingFunctionName(com.intellinet.diameter.URIData data) {
        super(data);
    }
}
