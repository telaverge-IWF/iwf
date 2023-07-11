package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectSuppressionOfAnnouncement extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectSuppressionOfAnnouncement with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectSuppressionOfAnnouncement(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectSuppressionOfAnnouncement(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
