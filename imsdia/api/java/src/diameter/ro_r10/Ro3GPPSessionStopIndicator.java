package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * 3GPP-Session-Stop-Indicator AVP is of type Octetstring. It indicates to the AAA server
 * that the last PDP context of a session is released and that the PDP session has been terminated.
 */
public class Ro3GPPSessionStopIndicator extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPSessionStopIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPSessionStopIndicator(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Ro3GPPSessionStopIndicator(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
