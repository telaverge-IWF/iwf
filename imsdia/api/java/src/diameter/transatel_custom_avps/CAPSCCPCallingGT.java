package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSCCPCallingGT extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSCCPCallingGT with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSCCPCallingGT(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSCCPCallingGT(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
