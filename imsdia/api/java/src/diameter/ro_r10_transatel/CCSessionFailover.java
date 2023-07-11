package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The CC-Session-Failover AVP is type of Enumerated and contains information as to whether 
 * moving the credit-control message stream to a backup server during an ongoing credit-control
 * session is supported.  In communication failures, the credit-control message streams can be
 * moved to an alternative destination if the credit-control server supports failover to an 
 * alternative server.  The secondary credit-control server name, if received from the home
 * Diameter AAA server, can be used as an address of the backup server. An implementation is not
 * required to support moving a credit-control message stream to an alternative server, as this 
 * also requires moving information related to the credit-control session to backup server.
 */
public class CCSessionFailover extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        FAILOVER_NOT_SUPPORTED(0),
        FAILOVER_SUPPORTED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CCSessionFailover with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCSessionFailover(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CCSessionFailover(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
