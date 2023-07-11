package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-AppleTalk-Link AVP (AVP Code 37) is of type Unsigned32 and
 * contains the AppleTalk network number that should be used for the
 * serial link to the user, which is another AppleTalk router. This AVP
 * MUST only be present in an authorization response and is never used
 * when the user is not another router.
 * Despite the size of the field, values range from 0 to 65,535. 
 */
public class FramedAppletalkLink extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a FramedAppletalkLink with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedAppletalkLink(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    FramedAppletalkLink(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
