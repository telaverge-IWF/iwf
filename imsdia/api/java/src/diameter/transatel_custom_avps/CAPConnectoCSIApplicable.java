package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectoCSIApplicable extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectoCSIApplicable with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectoCSIApplicable(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectoCSIApplicable(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
