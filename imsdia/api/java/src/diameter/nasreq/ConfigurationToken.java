package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Configuration-Token AVP (AVP Code 78) is of type OctetString and is sent  * by a Diameter Server to a Diameter Proxy Agent or Translation Agent in an
 * AA-Answer command to indicate a type of user profile to be used. It should
 * not be sent to a Diameter Client (NAS).
 */
public class ConfigurationToken extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ConfigurationToken with the given value.
     *
     * @param value - the value of the AVP
     */
    public ConfigurationToken(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ConfigurationToken(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
