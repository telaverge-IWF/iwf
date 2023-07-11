package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The Software-Version AVP is of type UTF8String. This AVP contains the 
 * Software Version of the International Mobile Equipment Identity.
 * See 3GPP TS 23.003 [3].
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
