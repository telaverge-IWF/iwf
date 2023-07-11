package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Credit-Control-Failure-Handling AVP is of type Enumerated. The credit-control client 
 * uses information in this AVP to decide what to do if sending credit-control messages to the
 * credit-control server has been, for instance, temporarily prevented due to a network problem.
 * Depending on the service logic, the credit-control server can order the client to terminate 
 * the service immediately when there is a reason to believe that the service cannot be charged, 
 * or to try failover to an alternative server, if possible. Then the server could either 
 * terminate or grant the service, should the alternative connection also fail.
 */
public class CreditControlFailureHandling extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        TERMINATE(0),
        CONTINUE(1),
        RETRY_AND_TERMINATE(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CreditControlFailureHandling with the given value.
     *
     * @param value - the value of the AVP
     */
    public CreditControlFailureHandling(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CreditControlFailureHandling(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
