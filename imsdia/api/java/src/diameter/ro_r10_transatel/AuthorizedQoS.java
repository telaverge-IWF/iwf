package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Authorized-QoS AVP is of type UTF8String and holds the Authorised QoS as defined in TS 23.207/
 * TS 29.207 and applied via the Go reference points.
 */
public class AuthorizedQoS extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AuthorizedQoS with the given value.
     *
     * @param value - the value of the AVP
     */
    public AuthorizedQoS(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    AuthorizedQoS(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
