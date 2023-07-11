package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Media-Initiator-Party  AVP (AVP code 1288) is of type UTF8String. 
 * Enumerated in IMS charging, it holds the address (SIP URI or TEL URI) of 
 * the party (Public User ID or Public Service ID) who initiates the media 
 * action, like adding/removing, connecting/disconnecting the media. 
 * The Media Initiator Party shall be populated with the SIP URI or TEL URI 
 * contained in the Request-URI of the outgoing request. 
 * It is use for PoC charging.
 */
public class MediaInitiatorParty extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a MediaInitiatorParty with the given value.
     *
     * @param value - the value of the AVP
     */
    public MediaInitiatorParty(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    MediaInitiatorParty(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
