package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Redirect-Server-Address AVP (AVP Code 435) is of type UTF8String and 
 * defines the address of the redirect server (eg: HTTP redirect server,
 * SIP server) wih which the end user is to be connected when the account
 * cannot cover the service cost.
 */
public class RedirectServerAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RedirectServerAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public RedirectServerAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    RedirectServerAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
