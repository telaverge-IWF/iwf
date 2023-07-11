package diameter.s6a;

import com.intellinet.diameter.*;


public class ClientIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ClientIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public ClientIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ClientIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
