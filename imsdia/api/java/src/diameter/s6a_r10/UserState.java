package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class UserState extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        DETACHED(0),
        ATTACHED_NOT_REACHABLE_FOR_PAGING(1),
        ATTACHED_REACHABLE_FOR_PAGING(2),
        CONNECTED_NOT_REACHABLE_FOR_PAGING(3),
        CONNECTED_REACHABLE_FOR_PAGING(4),
        NETWORK_DETERMINED_NOT_REACHABLE(5);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a UserState with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserState(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    UserState(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
