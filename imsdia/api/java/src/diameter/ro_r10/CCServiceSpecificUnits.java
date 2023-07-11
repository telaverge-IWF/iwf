package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The CC-Service-Specific-Units AVP is of type Unsigned64 and specifies the number of
 * service-specific units (e.g., number of events, points) given in a selected service.
 * The service-specific units always refer to the service identified in the
 * Service-Identifier AVP(or Rating-Group AVP when the Multiple-Services-Credit-Control AVP is used).
 */
public class CCServiceSpecificUnits extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a CCServiceSpecificUnits with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCServiceSpecificUnits(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    CCServiceSpecificUnits(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
