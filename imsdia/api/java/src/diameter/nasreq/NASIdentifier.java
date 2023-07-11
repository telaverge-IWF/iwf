package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The NAS-Identifier AVP (AVP Code 32) [RADIUS] is of type UTF8String
 * and contains the identity of the NAS providing service to the user.
 * This AVP SHOULD only be added by a RADIUS/Diameter Translation Agent.
 * When this AVP is present, the Origin-Host AVP identifies the NAS
 * providing service to the user.
 * Diameter agents and servers SHOULD check whether a NAS-Identifier AVP
 * corresponds to an entry in the Route-Record AVP. If no match is
 * found, then an error is logged, but no other action is taken. 
 */
public class NASIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a NASIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public NASIdentifier(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    NASIdentifier(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
