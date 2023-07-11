package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Charging-Rule-Base-Name AVP is of type OctetString and it indicates the name of a 
 *  pre-defined group of charging rules residing at the TPF.
 */
public class ChargingRuleBaseName extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ChargingRuleBaseName with the given value.
     *
     * @param value - the value of the AVP
     */
    public ChargingRuleBaseName(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ChargingRuleBaseName(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
