package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Called-Station-Id AVP (AVP Code 30) is of type UTF8String and allows
 * the NAS to send the ASCII string describing the layer 2 address the user
 * contacted in the request. For dialup access,this can be a phone number,
 * obtained using Dialed Number identification (DNIS) or a similar 
 * technology. Note that this may be different from the phone number the call
 * comes on. For the use with IEEE 802 access,the Called-Station-Id MAY contain
 * a MAC address formatted as described in RAD802.1X.
 */
public class CalledStationId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CalledStationId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CalledStationId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CalledStationId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
