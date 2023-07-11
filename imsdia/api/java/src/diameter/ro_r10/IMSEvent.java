package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Event AVP is of type UTF8String and holds the content of the "Event" header.
 */
public class IMSEvent extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a IMSEvent with the given value.
     *
     * @param value - the value of the AVP
     */
    public IMSEvent(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    IMSEvent(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
