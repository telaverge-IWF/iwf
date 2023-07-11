package diameter.ro_r10;

import com.intellinet.diameter.*;


public class ApplicationServerID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ApplicationServerID with the given value.
     *
     * @param value - the value of the AVP
     */
    public ApplicationServerID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ApplicationServerID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
