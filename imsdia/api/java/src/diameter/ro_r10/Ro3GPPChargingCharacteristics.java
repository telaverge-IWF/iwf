package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * 3GPP-Charging-Characteristics AVP is of type UTF8String. It contains the charging
 * characteristics for this PDP context received in the Create PDP Context Request 
 * Message (only available in R99 and later releases).
 */
public class Ro3GPPChargingCharacteristics extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPChargingCharacteristics with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPChargingCharacteristics(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPChargingCharacteristics(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
