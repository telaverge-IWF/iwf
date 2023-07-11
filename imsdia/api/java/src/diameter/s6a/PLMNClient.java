package diameter.s6a;

import com.intellinet.diameter.*;


public class PLMNClient extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        BROADCAST_SERVICE(0),
        O_AND_M_HPLMN(1),
        O_AND_M_VPLMN(2),
        ANONYMOUS_LOCATION(3),
        TARGET_UE_SUBSCRIBED_SERVICE(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PLMNClient with the given value.
     *
     * @param value - the value of the AVP
     */
    public PLMNClient(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PLMNClient(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
