package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class ApplicationServiceType extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ApplicationServiceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ApplicationServiceType(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ApplicationServiceType(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
