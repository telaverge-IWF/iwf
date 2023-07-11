package diameter.s13_r10;

import com.intellinet.diameter.*;


/**
 * The Equipment-Status AVP is of type Enumerated, and contains the status 
 * of the mobile equipment. The following values are defined:
 * 
 *  WHITELISTED (0) 
 *  Mobile Equipment is authenticated to the network. 
 *  BLACKLISTED (1) 
 *  There is compliant registered against this Mobile Equipment.
 *  GREYLISTED (2) 
 * There is no compliant registered against this Mobile Equipment, but it 
 * is not authenticated to our network
 */
public class EquipmentStatus extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        WHITELISTED(0),
        BLACKLISTED(1),
        GREYLISTED(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a EquipmentStatus with the given value.
     *
     * @param value - the value of the AVP
     */
    public EquipmentStatus(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    EquipmentStatus(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
