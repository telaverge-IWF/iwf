package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Application-Server AVP is of type UTF8String and holds the SIP URL of the AS
 * addressed during the session.
 */
public class ApplicationServer extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ApplicationServer with the given value.
     *
     * @param value - the value of the AVP
     */
    public ApplicationServer(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ApplicationServer(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
