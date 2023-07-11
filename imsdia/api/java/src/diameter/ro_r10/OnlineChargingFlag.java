package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Online-Charging-Flag AVP (AVP code 2303) is of type Enumerated and indicates the Online Charging
 * Request was sent based on the provided ECF address from the SIP P-header .P-Charging-Function-Addresses.
 */
public class OnlineChargingFlag extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ECF_address_not_provided(0),
        ECF_address_provided(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a OnlineChargingFlag with the given value.
     *
     * @param value - the value of the AVP
     */
    public OnlineChargingFlag(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    OnlineChargingFlag(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
