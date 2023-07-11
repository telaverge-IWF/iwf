package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPAnnouncementAccessNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPAnnouncementAccessNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPAnnouncementAccessNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPAnnouncementAccessNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
