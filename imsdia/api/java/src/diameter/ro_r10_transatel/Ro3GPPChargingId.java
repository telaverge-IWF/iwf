package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * 3GPP-Charging-Id AVP is of type Unsigned32 and contains the Charging ID for 
 * this PDP context (this together with GGSN-Address constitutes a unique identifier
 * for the PDP context).
 */
public class Ro3GPPChargingId extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a Ro3GPPChargingId with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPChargingId(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    Ro3GPPChargingId(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
