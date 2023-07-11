package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SMS-Node AVP (AVP code 2016) is of type Enumerated and identifies the 
 * role which the SMS node performs in relation to the charging event. 
 */
public class SMSNode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SMS_Router(0),
        IP_SM_GW(1),
        SMS_Router_and_IP_SM_GW(2),
        SMS_SC(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SMSNode with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMSNode(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SMSNode(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
