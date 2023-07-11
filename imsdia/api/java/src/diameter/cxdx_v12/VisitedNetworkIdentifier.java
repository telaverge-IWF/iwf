package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Visited-Network-Identifier AVP is of type OctetString. This AVP contains an identifier that helps the home
 * network to identify the visited network (e.g. the visited network domain name).
 */
public class VisitedNetworkIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a VisitedNetworkIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public VisitedNetworkIdentifier(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    VisitedNetworkIdentifier(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
