package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMStatusReportRequest extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMStatusReportRequest with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMStatusReportRequest(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMStatusReportRequest(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
