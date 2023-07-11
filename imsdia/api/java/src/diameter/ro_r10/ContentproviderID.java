package diameter.ro_r10;

import com.intellinet.diameter.*;


public class ContentproviderID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ContentproviderID with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContentproviderID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ContentproviderID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
