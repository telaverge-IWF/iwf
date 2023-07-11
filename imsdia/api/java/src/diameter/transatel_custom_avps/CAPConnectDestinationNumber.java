package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectDestinationNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPConnectDestinationNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectDestinationNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPConnectDestinationNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
