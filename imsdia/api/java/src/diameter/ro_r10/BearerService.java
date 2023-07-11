package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Bearer-Service AVP is of type OctetString and holds the used bearer service for the PSTN leg.
 */
public class BearerService extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a BearerService with the given value.
     *
     * @param value - the value of the AVP
     */
    public BearerService(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    BearerService(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
