package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * 3GPP-NSAPI AVP is of type UTF8String and it identifies a particular PDP.
 */
public class Ro3GPPNSAPI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPNSAPI with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPNSAPI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPNSAPI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
