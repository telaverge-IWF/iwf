package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPERBSEventSpecificInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPERBSEventSpecificInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPERBSEventSpecificInformation(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CAPERBSEventSpecificInformation(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
