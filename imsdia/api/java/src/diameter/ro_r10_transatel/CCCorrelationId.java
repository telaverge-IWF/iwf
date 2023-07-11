package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The CC-Correlation-Id AVP (AVP Code 411) is of type OctetString and contains * information to correlate credit-control requests generated for different
 * components of the service; e.g., transport and service level. The one who
 * allocates the Service-Context-Id (i.e., unique identifier of a service
 * specific document) is also responsible for defining the content and encoding
 * of the CC-Correlation-Id AVP.
 */
public class CCCorrelationId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CCCorrelationId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCCorrelationId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CCCorrelationId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
