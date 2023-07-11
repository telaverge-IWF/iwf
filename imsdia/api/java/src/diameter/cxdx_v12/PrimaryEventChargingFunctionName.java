package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Primary-Event-Charging-Function-Name AVP is of type DiameterURI. This AVP contains the address of the
 * Primary Event Charging Function.
 */
public class PrimaryEventChargingFunctionName extends com.intellinet.diameter.DerivedAVP<URI> {
    /**
     * Constructs a PrimaryEventChargingFunctionName with the given value.
     *
     * @param value - the value of the AVP
     */
    public PrimaryEventChargingFunctionName(URI value) {
        super(new com.intellinet.diameter.URIData(value));
    }

    PrimaryEventChargingFunctionName(com.intellinet.diameter.URIData data) {
        super(data);
    }
}
