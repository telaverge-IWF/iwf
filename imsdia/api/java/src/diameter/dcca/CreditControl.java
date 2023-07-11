package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Credit-Control AVP (AVP Code 426) is of type Enumerated and must be
 * included in AA requests when the service element has credit-control
 * capabilities.
 */
public class CreditControl extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        CREDIT_AUTHORIZATION(0),
        RE_AUTHORIZATION(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CreditControl with the given value.
     *
     * @param value - the value of the AVP
     */
    public CreditControl(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CreditControl(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
