package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The User-Equipment-Info-Value AVP is of type OctetString. The User-Equipment-Info-Type AVP 
 * defines which type of identifier is used.
 */
public class UserEquipmentInfoValue extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a UserEquipmentInfoValue with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserEquipmentInfoValue(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    UserEquipmentInfoValue(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
