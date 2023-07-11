package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectMaxDuration extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectMaxDuration with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectMaxDuration(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectMaxDuration(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
