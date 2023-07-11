package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPACHBeepTone extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        False(0),
        True(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CAPACHBeepTone with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPACHBeepTone(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CAPACHBeepTone(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
