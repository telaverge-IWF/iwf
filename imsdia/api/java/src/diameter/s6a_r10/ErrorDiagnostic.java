package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class ErrorDiagnostic extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        GPRS_DATA_SUBSCRIBED(0),
        NO_GPRS_DATA_SUBSCRIBED(1),
        ODB_ALL_APN(2),
        ODB_HPLMN_APN(3),
        ODB_VPLMN_APN(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ErrorDiagnostic with the given value.
     *
     * @param value - the value of the AVP
     */
    public ErrorDiagnostic(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ErrorDiagnostic(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
