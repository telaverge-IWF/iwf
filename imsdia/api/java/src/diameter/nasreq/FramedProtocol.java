package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-Protocol AVP (AVP Code 7) is of type Enumerated and
 * contains the framing to be used for framed access. This AVP MAY be
 * present in both requests and responses. The supported values are
 * listed in [RADIUSTypes]. The following list is informational:
 *  1 PPP
 *  2 SLIP
 *  3 AppleTalk Remote Access Protocol (ARAP)
 *  4 Gandalf proprietary SingleLink/MultiLink protocol
 *  5 Xylogics proprietary IPX/SLIP
 *  6 X.75 Synchronous
 */
public class FramedProtocol extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PPP(1),
        SLIP(2),
        ARAP(3),
        GANDALF(4),
        XYLOGICS(5),
        X_75(6);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a FramedProtocol with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedProtocol(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    FramedProtocol(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
