package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class Contact extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Contact with the given value.
     *
     * @param value - the value of the AVP
     */
    public Contact(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Contact(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
