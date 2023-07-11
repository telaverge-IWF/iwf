package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Required-MBMS-Bearer-Capabilities AVP is of type UTF8String and contains the minimum bearer capabilities
 * the UE needs to support. The information conatined in this AVP is UTF-8 encoded QoS profile as defined
 * in 3GPP TS 24.008.
 */
public class RequiredMBMSBearerCapabilities extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RequiredMBMSBearerCapabilities with the given value.
     *
     * @param value - the value of the AVP
     */
    public RequiredMBMSBearerCapabilities(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    RequiredMBMSBearerCapabilities(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
