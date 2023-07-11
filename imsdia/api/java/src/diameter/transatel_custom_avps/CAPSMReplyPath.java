package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMReplyPath extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMReplyPath with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMReplyPath(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMReplyPath(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
