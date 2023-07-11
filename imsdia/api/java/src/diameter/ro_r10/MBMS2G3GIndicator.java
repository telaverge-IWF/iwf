package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * MBMS-2G-3G-Indicator AVP is of type Enumerated. It indicates whether the MBMS bearer service will be
 * delivered in 2g-only, 3G-only or both coverage areas. 
 */
public class MBMS2G3GIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ONLY_2G(0),
        ONLY_3G(1),
        BOTH_2G_AND_3G(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MBMS2G3GIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public MBMS2G3GIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MBMS2G3GIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
