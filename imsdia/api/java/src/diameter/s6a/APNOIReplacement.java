package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The APN-OI-Replacement AVP is of type UTF8String. This AVP Indicates the domain name 
 * to replace the APN OI when constructing the PDN GW FQDN upon which to perform a DNS 
 * resolution. See TS 23.003 [3].
 */
public class APNOIReplacement extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a APNOIReplacement with the given value.
     *
     * @param value - the value of the AVP
     */
    public APNOIReplacement(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    APNOIReplacement(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
