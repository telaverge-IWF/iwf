package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Service-Context-Id AVP is of type UTF8String and is defined in RFC4006. It contains a unique
 * identifier of the Diameter Credit Control service specific document that applies to the 
 * request. This is an identifier allocated by the service provider/operator, by the service 
 * elsement manufacturer or by a stadardization body and must uniquely identify a given Diameter
 * Credit Control service specific document. The format of Service-Context-Id is:
 * "extensions".MNC.MCC."Release"."service-context" "@" "domain". 
 * Eg:- For PS charging  32251@3gpp.org, For WLAN cherging 32252@3gpp.org
 */
public class ServiceContextId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ServiceContextId with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceContextId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ServiceContextId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
