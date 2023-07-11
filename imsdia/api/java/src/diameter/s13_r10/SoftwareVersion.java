package diameter.s13_r10;

import com.intellinet.diameter.*;


/**
 * The Software-Version AVP is of type UTF8String. This AVP contains the International 
 * Mobile Equipment Identity. See 3GPP TS 23.003 
 */
public class SoftwareVersion extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SoftwareVersion with the given value.
     *
     * @param value - the value of the AVP
     */
    public SoftwareVersion(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    SoftwareVersion(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
