package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Final-Unit-Action AVP (AVP Code 449) is of type Enumerated and indicates to the credit-control
 * client the action to be taken when the user's account cannot cover the service cost.
 */
public class FinalUnitAction extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        TERMINATE(0),
        REDIRECT(1),
        RESTRICT_ACCESS(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a FinalUnitAction with the given value.
     *
     * @param value - the value of the AVP
     */
    public FinalUnitAction(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    FinalUnitAction(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
