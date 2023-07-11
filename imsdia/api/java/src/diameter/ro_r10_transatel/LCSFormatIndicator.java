package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-Format-Indicator AVP is of type Enumerated and contains the format of the LCS Client name.
 */
public class LCSFormatIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        LOCATION_NAME(0),
        EMAIL_ADDRESS(1),
        MSISDN(2),
        URL(3),
        SIP_URL(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LCSFormatIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSFormatIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LCSFormatIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
