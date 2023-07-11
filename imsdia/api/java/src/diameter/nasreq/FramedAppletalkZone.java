package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Framed-AppleTalk-Zone AVP (AVP Code 39) is of type OctetString
 * and contains the AppleTalk Default Zone to be used for this user.
 * This AVP MUST only be present in an authorization response. Multiple
 * instances of this AVP in the same message are not allowed.
 */
public class FramedAppletalkZone extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedAppletalkZone with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedAppletalkZone(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedAppletalkZone(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
