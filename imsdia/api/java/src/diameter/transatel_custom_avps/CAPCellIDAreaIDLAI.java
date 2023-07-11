package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCellIDAreaIDLAI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPCellIDAreaIDLAI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCellIDAreaIDLAI(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CAPCellIDAreaIDLAI(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
