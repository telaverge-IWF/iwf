package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Callback-Id AVP (AVP Code 20) is of type UTF8String and contains the
 * name of a place to be called, to be interpreted by the NAS. This AVP MAY be
 * present in an authentication and/or authorization response.
 */
public class CallbackId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CallbackId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CallbackId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CallbackId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
