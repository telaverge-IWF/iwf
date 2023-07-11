package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Application-Provided-Called-Party-Address AVP is of type UTF8String and holds the 
 * called party number (SIP URI, E.164),if it is determined by an application server.
 */
public class ApplicationProvidedCalledPartyAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ApplicationProvidedCalledPartyAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public ApplicationProvidedCalledPartyAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ApplicationProvidedCalledPartyAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
