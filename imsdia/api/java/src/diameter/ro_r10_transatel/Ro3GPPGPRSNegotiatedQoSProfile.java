package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * 3GPP-GPRS-Negotiated-QoS-Profile AVP is of type UTF8String. It is the
 * QoS Profile applied by GGSN.
 */
public class Ro3GPPGPRSNegotiatedQoSProfile extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPGPRSNegotiatedQoSProfile with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPGPRSNegotiatedQoSProfile(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPGPRSNegotiatedQoSProfile(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
