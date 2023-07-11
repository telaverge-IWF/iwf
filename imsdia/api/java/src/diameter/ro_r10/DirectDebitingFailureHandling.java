package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Direct-Debiting-Failure-Handling AVP (AVP Code 428) is of type
 * Enumerated. The credit-control client uses information in this AVP to decide
 * what to do if sending credit-control messages (Requested-Action AVP set to
 * DIRECT_DEBITING) to the credit-control server has been, for instance,
 * temporarily prevented due to a network problem.
 */
public class DirectDebitingFailureHandling extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        TERMINATE_OR_BUFFER(0),
        CONTINUE(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a DirectDebitingFailureHandling with the given value.
     *
     * @param value - the value of the AVP
     */
    public DirectDebitingFailureHandling(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    DirectDebitingFailureHandling(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
