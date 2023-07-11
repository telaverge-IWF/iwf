package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Content-Disposition AVP is of type UTF8String and indicates how the message bosy or a message
 * body part is to be interpreted (e.g session,render).
 */
public class ContentDisposition extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ContentDisposition with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContentDisposition(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ContentDisposition(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
