package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Public-Identity AVP is of type UTF8String. This AVP contains the public identity of a user in the IMS. The syntax
 * of this AVP corresponds either to a SIP URL (with the format defined in IETF RFC 3261 and IETF RFC 2396)
 * or a TEL URL (with the format defined in IETF RFC 2806).
 */
public class PublicIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a PublicIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public PublicIdentity(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    PublicIdentity(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
