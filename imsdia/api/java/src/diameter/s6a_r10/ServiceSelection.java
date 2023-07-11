package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class ServiceSelection extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ServiceSelection with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceSelection(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ServiceSelection(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
