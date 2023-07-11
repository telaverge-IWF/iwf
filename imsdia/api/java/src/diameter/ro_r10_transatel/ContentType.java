package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Content-Type AVP is of type UTF8String and holds the media type(e.g application/sdp, text/html)
 * of the message-body.
 */
public class ContentType extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ContentType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContentType(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ContentType(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
