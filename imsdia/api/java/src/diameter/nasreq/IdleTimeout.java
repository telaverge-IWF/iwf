package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Idle-Timeout AVP (AVP Code 28) is of type Unsigned32 and sets the
 * maximum number of consecutive seconds of idle connection allowable to
 * the user before termination of the session or before a prompt is
 * issued. The default is none, or system specific.
 */
public class IdleTimeout extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a IdleTimeout with the given value.
     *
     * @param value - the value of the AVP
     */
    public IdleTimeout(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    IdleTimeout(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
