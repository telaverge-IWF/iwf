package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Multiple-Services-Indicator is of type Enumerated and indicates whether the Diameter 
 * credit-control client is capable of handling multiple services independently within a
 * (sub-) session.  The absence of this AVP means that independent credit-control of multiple
 * services is not supported. 
 */
public class MultipleServicesIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        MULTIPLE_SERVICES_NOT_SUPPORTED(0),
        MULTIPLE_SERVICES_SUPPORTED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MultipleServicesIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public MultipleServicesIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MultipleServicesIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
