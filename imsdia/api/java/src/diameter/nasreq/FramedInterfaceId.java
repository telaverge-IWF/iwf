package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-Interface-Id AVP (AVP Code 96) is of type Unsigned64 and
 * contains the IPv6 interface identifier to be configured for the user.
 * It MAY be used in authorization requests as a hint to the server that
 * a specific interface id is desired, but the server is not required to
 * honor the hint in the corresponding response.
 */
public class FramedInterfaceId extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a FramedInterfaceId with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedInterfaceId(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    FramedInterfaceId(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
