package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Service-Id AVP is of type UTF8String and identifies the service the MRFC is hosting. For conferences
 * the conference ID is used as the value of this parameter.
 */
public class ServiceId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ServiceId with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ServiceId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
