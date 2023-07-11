package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Interface-Port AVP (AVP code 2004) is of type UTF8String and holds the port-identification or contains information about the transport layer port used by the application associated with the charging event.
 */
public class InterfacePort extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a InterfacePort with the given value.
     *
     * @param value - the value of the AVP
     */
    public InterfacePort(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    InterfacePort(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
