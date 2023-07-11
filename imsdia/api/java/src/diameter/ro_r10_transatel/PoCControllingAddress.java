package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * PoC-Controlling-Address AVP is of type UTF8String and identifies the PoC server performing
 * the controlling function for the associated PoC session.
 */
public class PoCControllingAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a PoCControllingAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCControllingAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    PoCControllingAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
