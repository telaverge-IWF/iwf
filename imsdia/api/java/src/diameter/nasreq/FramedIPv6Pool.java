package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-IPv6-Pool AVP (AVP Code 100) is of type OctetString and
 * contains the name of an assigned pool that SHOULD be used to assign
 * an IPv6 prefix for the user. If the access device does not support
 * multiple prefix pools, it MUST ignore this AVP.
 * Although specified as type OctetString for compatibility with RADIUS
 * [RADIUSIPv6], the encoding of the Data field SHOULD also conform to
 * the rules for the UTF8String Data Format.
 */
public class FramedIPv6Pool extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPv6Pool with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPv6Pool(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedIPv6Pool(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
