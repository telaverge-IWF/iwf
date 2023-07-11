package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The NAS-Port-Id AVP (AVP Code 87) is of type UTF8String and consists
 * of ASCII text identifying the port of the NAS authenticating the
 * user. Note that "port" is meant in its sense as a service connection
 * on the NAS, not as an IP protocol identifier.
 * Either NAS-Port or NAS-Port-Id SHOULD be present in AA-Request (AAR) commands * if the NAS differentiates among its ports. NAS-Port-Id is intended for use
 * by NASes that cannot conveniently number their ports.
 */
public class NASPortId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a NASPortId with the given value.
     *
     * @param value - the value of the AVP
     */
    public NASPortId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    NASPortId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
