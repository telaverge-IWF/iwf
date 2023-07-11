package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Access-Network-Charging-Identifier-Value AVP (AVP code 503) is of type 
 * OctetString, and contains a charging identifier (e.g. GCID).
 */
public class AccessNetworkChargingIdentifierValue extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AccessNetworkChargingIdentifierValue with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccessNetworkChargingIdentifierValue(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    AccessNetworkChargingIdentifierValue(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
