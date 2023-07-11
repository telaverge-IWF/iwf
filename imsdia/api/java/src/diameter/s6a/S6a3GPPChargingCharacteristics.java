package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * 3GPP-Charging-Characteristics AVP is of type UTF8String. It contains the charging
 * characteristics for this PDP context received in the Create PDP Context Request
 * Message (only available in R99 and later releases).see 3GPP TS 32.299 [8].
 */
public class S6a3GPPChargingCharacteristics extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a S6a3GPPChargingCharacteristics with the given value.
     *
     * @param value - the value of the AVP
     */
    public S6a3GPPChargingCharacteristics(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    S6a3GPPChargingCharacteristics(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
