package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Outgoing-Session-Id AVP (AVP code 2320) is of type UTF8String and holds the outgoing session 
 * identifier for an AS acting as B2BUA. For a SIP session the Outgoing-Session-Id AVP contains the 
 * SIP Call ID of the outgoing leg, as defined in RFC 3261 [405].
 */
public class OutgoingSessionId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a OutgoingSessionId with the given value.
     *
     * @param value - the value of the AVP
     */
    public OutgoingSessionId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    OutgoingSessionId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
