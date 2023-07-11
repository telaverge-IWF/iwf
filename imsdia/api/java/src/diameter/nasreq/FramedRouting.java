package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-Routing AVP (AVP Code 10) is of type Enumerated and
 * contains the routing method for the user when the user is a router to
 * a network. This AVP SHOULD only be present in authorization
 * responses. The supported values are listed in [RADIUSTypes]. The
 * following list is informational:
 * 0 None
 * 1 Send routing packets
 * 2 Listen for routing packets
 * 3 Send and Listen
 */
public class FramedRouting extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NONE(0),
        SEND(1),
        LISTEN(2),
        SEND_LISTEN(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a FramedRouting with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedRouting(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    FramedRouting(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
