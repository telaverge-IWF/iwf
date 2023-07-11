package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The IMS-Communication-Service-Identifier AVP (AVP code 1281) is of type 
 * UTF8String and holds the IMS Communication Service Identifier (ICSI) as 
 * contained in the P-Asserted-Service header of a SIP request to identify an 
 * IMS Communication Service as defined in TS 24.229 [202].
 */
public class IMSCommunicationServiceIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a IMSCommunicationServiceIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public IMSCommunicationServiceIdentifier(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    IMSCommunicationServiceIdentifier(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
