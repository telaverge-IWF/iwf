package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
  * The IMS-Application-Reference-Identifier AVP (AVP code 2601) is of type UTF8String and holds the 
  * IMS Application Reference Identifier (IARI) as contained in a SIP request to identify an IMS Application 
  * as defined in TS 24.229 [202]
  */
public class IMSApplicationReferenceIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a IMSApplicationReferenceIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public IMSApplicationReferenceIdentifier(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    IMSApplicationReferenceIdentifier(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
