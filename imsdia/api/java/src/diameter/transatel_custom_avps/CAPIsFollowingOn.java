package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPIsFollowingOn extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        False(0),
        True(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CAPIsFollowingOn with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPIsFollowingOn(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CAPIsFollowingOn(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
