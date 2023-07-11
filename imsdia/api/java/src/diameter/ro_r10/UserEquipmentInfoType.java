package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The User-Equipment-Info-Type AVP is of type Enumerated and defines the type of user equipment
 * information contained in the User-Equipment-Info-Value AVP.
 */
public class UserEquipmentInfoType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        IMEISV(0),
        MAC(1),
        EUI64(2),
        MODIFIED_EUI64(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a UserEquipmentInfoType with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserEquipmentInfoType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    UserEquipmentInfoType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
