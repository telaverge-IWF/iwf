package diameter.ro_r10;

import com.intellinet.diameter.*;


/** 
 * The Interface-Text AVP (AVP code 2005) is of type UTF8String and is the consolidation information about the application associated with the charging event.
 */
public class InterfaceText extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a InterfaceText with the given value.
     *
     * @param value - the value of the AVP
     */
    public InterfaceText(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    InterfaceText(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
