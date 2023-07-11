package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Service-Type AVP (AVP Code 6) is of type Enumerated and contains
 * the type of service the user has requested or the type of service to
 * be provided. One such AVP MAY be present in an authentication and/or
 * authorization request or response. A NAS is not required to
 * implement all of these service types. It MUST treat unknown or
 * unsupported Service-Types received in a response as a failure and end
 * the session with a DIAMETER_INVALID_AVP_VALUE Result-Code.
 * Service-Type 6 6.1 Enumerated | M | P | | V | Y |
 */
public class State extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a State with the given value.
     *
     * @param value - the value of the AVP
     */
    public State(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    State(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
