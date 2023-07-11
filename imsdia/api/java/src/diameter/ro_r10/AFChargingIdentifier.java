package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AF-Charging-Identifier AVP (AVP code 505)is of type OctetString,contains
 * the AF Charging Identifier that is sent by the AF. This information may be
 * used for charging correlation with bearer layer.
 */
public class AFChargingIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AFChargingIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public AFChargingIdentifier(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    AFChargingIdentifier(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
