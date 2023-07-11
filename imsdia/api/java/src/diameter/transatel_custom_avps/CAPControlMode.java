package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPControlMode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NO_CONTROL(0),
        LOCAL_CONTROL(1),
        REMOTE_CONTROL(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CAPControlMode with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPControlMode(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CAPControlMode(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
