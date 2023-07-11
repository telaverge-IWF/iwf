package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Domain-Name AVP is of type UTF8String and represents a fully qualified domain name.
 */
public class DomainName extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a DomainName with the given value.
     *
     * @param value - the value of the AVP
     */
    public DomainName(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    DomainName(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
