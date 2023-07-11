package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-Pool AVP (AVP Code 88) is of type OctetString and contains
 * the name of an assigned address pool that SHOULD be used to assign an
 * address for the user. If a NAS does not support multiple address
 * pools, the NAS SHOULD ignore this AVP. Address pools are usually
 * used for IP addresses but can be used for other protocols if the NAS
 * supports pools for those protocols.
 */
public class FramedPool extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedPool with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedPool(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedPool(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
