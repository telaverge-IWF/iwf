package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Requested-Party-Address AVP (AVP code 1251) is of type UTF8 String. 
 * In IMS it holds the address (SIP URI or TEL URI) of the party (Public User 
 * ID or Public Service ID) to whom the SIP transaction was originally posted.
 * The Requested Party Address shall be populated with the SIP URI or TEL URI 
 * contained in the Request-URI of the incoming request. This field is only 
 * present if different from the Called Party Address parameter.
 */
public class RequestedPartyAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RequestedPartyAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public RequestedPartyAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    RequestedPartyAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
