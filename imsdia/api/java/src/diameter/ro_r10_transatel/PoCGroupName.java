package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * PoC-Group-Name AVP is of type UTF8String and identifies a pre-arranged group. Included if the
 * session is a pre-arranged group session.
 */
public class PoCGroupName extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a PoCGroupName with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCGroupName(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    PoCGroupName(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
