package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Acct-Authentic AVP (AVP Code 45) is of type Enumerated and
 * specifies how the user was authenticated. The supported values are
 * listed in [RADIUSTypes]. The following list is informational:
 * 1 RADIUS
 * 2 Local
 * 3 Remote
 * 4 Diameter
 */
public class AcctAuthentic extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        RADIUS(1),
        LOCAL(2),
        REMOTE(3),
        DIAMETER(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AcctAuthentic with the given value.
     *
     * @param value - the value of the AVP
     */
    public AcctAuthentic(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AcctAuthentic(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
