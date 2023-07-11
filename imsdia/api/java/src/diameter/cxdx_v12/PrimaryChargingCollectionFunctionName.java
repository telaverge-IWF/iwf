package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Primary-Charging-Collection-Function-Name AVP is of type DiameterURI. This AVP contains the address of the
 * Primary Charging Collection Function.
 */
public class PrimaryChargingCollectionFunctionName extends com.intellinet.diameter.DerivedAVP<URI> {
    /**
     * Constructs a PrimaryChargingCollectionFunctionName with the given value.
     *
     * @param value - the value of the AVP
     */
    public PrimaryChargingCollectionFunctionName(URI value) {
        super(new com.intellinet.diameter.URIData(value));
    }

    PrimaryChargingCollectionFunctionName(com.intellinet.diameter.URIData data) {
        super(data);
    }
}
