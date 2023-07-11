package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Origin-AAA-Protocol AVP (AVP Code 408) is of the type Enumerated
 * and should be inserted in a Diameter message translated by a gateway
 * system from another AAA protocol, such as RADIUS. It identifies the
 * source protocol of the message to the Diameter system receiving the
 * message.
 */
public class OriginAAAProtocol extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        RADIUS(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a OriginAAAProtocol with the given value.
     *
     * @param value - the value of the AVP
     */
    public OriginAAAProtocol(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    OriginAAAProtocol(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
