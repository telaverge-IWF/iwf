package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPAnnouncementAccessNumberNOA extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPAnnouncementAccessNumberNOA with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPAnnouncementAccessNumberNOA(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPAnnouncementAccessNumberNOA(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
