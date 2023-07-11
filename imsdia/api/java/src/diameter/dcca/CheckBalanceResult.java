package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Check Balance Result AVP (AVP Code 422) is of type Enumerated and 
 * contains the result of the balance check. This AVP is applicable only when
 * the Requested-Action AVP indicates CHECK_BALANCE in the Credit-Control-
 * Request command.
 */
public class CheckBalanceResult extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ENOUGH_CREDIT(0),
        NO_CREDIT(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CheckBalanceResult with the given value.
     *
     * @param value - the value of the AVP
     */
    public CheckBalanceResult(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CheckBalanceResult(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
