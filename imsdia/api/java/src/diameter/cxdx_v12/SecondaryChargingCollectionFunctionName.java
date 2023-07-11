package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Secondary-Charging-Collection-Function-Name AVP is of type DiameterURI. This AVP contains the address of
 * the Secondary Charging Collection Function.
 */
public class SecondaryChargingCollectionFunctionName extends com.intellinet.diameter.DerivedAVP<URI> {
    /**
     * Constructs a SecondaryChargingCollectionFunctionName with the given value.
     *
     * @param value - the value of the AVP
     */
    public SecondaryChargingCollectionFunctionName(URI value) {
        super(new com.intellinet.diameter.URIData(value));
    }

    SecondaryChargingCollectionFunctionName(com.intellinet.diameter.URIData data) {
        super(data);
    }
}
