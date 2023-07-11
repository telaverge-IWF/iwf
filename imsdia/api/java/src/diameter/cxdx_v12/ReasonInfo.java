package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Reason-Info AVP is of type UTF8String, and contains textual information to inform the user about the reason for a
 * de-registration.
 */
public class ReasonInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ReasonInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReasonInfo(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ReasonInfo(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
