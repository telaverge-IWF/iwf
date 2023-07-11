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
 */
public class ServiceType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        LOGIN(1),
        FRAMED(2),
        CALLBACK_LOGIN(3),
        CALLBACK_FRAMED(4),
        OUTBOUND(5),
        ADMINISTRATIVE(6),
        NAS_PROMPT(7),
        AUTHENTICATE_ONLY(8),
        CALLBACK_NAS_PROMPT(9),
        CALL_CHECK(10),
        CALLBACK_ADMINISTRATIVE(11),
        VOICE(12),
        FAX(13),
        MODEM_RELAY(14),
        IAPP_REGISTER(15),
        IAPP_AP_CHECK(16),
        AUTHORIZE_ONLY(17);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ServiceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ServiceType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
