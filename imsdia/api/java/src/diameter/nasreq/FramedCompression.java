package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-Compression AVP (AVP Code 13) is of type Enumerated and
 * contains the compression protocol to be used for the link. It MAY be
 * used in an authorization request as a hint to the server that a
 * specific compression type is desired, but the server is not required
 * to honor the hint in the corresponding response.
 */
public class FramedCompression extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NONE(0),
        VJ_TCP_IP(1),
        IPX(2),
        STAC_LZS(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a FramedCompression with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedCompression(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    FramedCompression(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
