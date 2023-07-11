package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Interface-Id AVP (AVP code 2003) is of type UTF8String and holds the interface identification provided by the messaging node (originator/destination).
 */
public class InterfaceId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a InterfaceId with the given value.
     *
     * @param value - the value of the AVP
     */
    public InterfaceId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    InterfaceId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
