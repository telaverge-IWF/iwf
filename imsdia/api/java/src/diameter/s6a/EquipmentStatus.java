package diameter.s6a;

import com.intellinet.diameter.*;


public class EquipmentStatus extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        WHITELISTED(0),
        BLACKLISTED(1),
        GREYLISTED(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a EquipmentStatus with the given value.
     *
     * @param value - the value of the AVP
     */
    public EquipmentStatus(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    EquipmentStatus(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
