package diameter.ro_r10;

import com.intellinet.diameter.*;


public class ContentID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ContentID with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContentID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ContentID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
