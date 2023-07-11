package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Callback-Number AVP (AVP Code 19) is of type UTF8String and contains a
 * dialing string to be used for callback. It MAY be used in an authentication
 * and/or authorization request as a hint to the server that a Callback service
 * is desired, but the server is not required to honor the hint in the
 * corresponding response.
 */
public class CallbackNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CallbackNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CallbackNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CallbackNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
