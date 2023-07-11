package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class WildcardedPublicIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a WildcardedPublicIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public WildcardedPublicIdentity(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    WildcardedPublicIdentity(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
