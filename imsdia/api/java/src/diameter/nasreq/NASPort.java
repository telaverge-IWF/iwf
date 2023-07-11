package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The NAS-Port AVP (AVP Code 5) is of type Unsigned32 and contains the
 * physical or virtual port number of the NAS which is authenticating
 * the user. Note that "port" is meant in its sense as a service
 * connection on the NAS, not as an IP protocol identifier.
 * Either NAS-Port or NAS-Port-Id (AVP Code 87) SHOULD be present in
 * AA-Request (AAR) commands if the NAS differentiates among its ports.
 */
public class NASPort extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NASPort with the given value.
     *
     * @param value - the value of the AVP
     */
    public NASPort(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NASPort(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
