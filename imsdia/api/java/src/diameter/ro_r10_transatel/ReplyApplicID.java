package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Reply-Replic-ID AVP is of type UTF8String and holds the identifier of a "reply path", i.e the identifier 
 *  of the application to which delivery reports, read-reply reports and reply-MMs are addressed.
 */
public class ReplyApplicID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ReplyApplicID with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReplyApplicID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ReplyApplicID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
