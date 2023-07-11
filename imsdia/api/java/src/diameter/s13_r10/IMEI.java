package diameter.s13_r10;

import com.intellinet.diameter.*;


/**
 * The IMEI AVP is of type UTF8String. This AVP contains the International Mobile 
 * Equipment Identity. See 3GPP TS 23.003 
 */
public class IMEI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a IMEI with the given value.
     *
     * @param value - the value of the AVP
     */
    public IMEI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    IMEI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
