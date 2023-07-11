package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSCCPCalledGT extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSCCPCalledGT with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSCCPCalledGT(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSCCPCalledGT(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
