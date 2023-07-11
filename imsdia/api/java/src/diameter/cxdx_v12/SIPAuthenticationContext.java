package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The SIP-Authentication-Context AVP is of type OctectString, and contains authentication-related information relevant
 * for performing the authentication but that is not part of the SIP authentication headers.
 * <p>
 * Some mechanisms (e.g. PGP, digest with quality of protection set to auth-int defined in IETF RFC 2617, digest with
 * predictive nonces or sip access digest) request that part or the whole SIP request is passed to the entity performing the
 * authentication. In such cases the SIP-Authentication-Context AVP would be carrying such information.
 */
public class SIPAuthenticationContext extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SIPAuthenticationContext with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPAuthenticationContext(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SIPAuthenticationContext(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
