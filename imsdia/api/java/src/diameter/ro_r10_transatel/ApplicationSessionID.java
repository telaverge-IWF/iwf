package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class ApplicationSessionID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ApplicationSessionID with the given value.
     *
     * @param value - the value of the AVP
     */
    public ApplicationSessionID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ApplicationSessionID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
