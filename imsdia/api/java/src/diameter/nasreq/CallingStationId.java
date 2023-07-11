package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Calling-Station-Id AVP (AVP Code 31) is of type UTF8String an allows the  * NAS to send the ASCII string describing the layer 2 address from which the
 * user connected in the request. For dialup access, this is the phone number
 * the call came from, using Automatic Number Identification (ANI) or a similar  * technology. For use with IEEE 802 access, the Calling-Station-Id AVP MAY
 * contain a MAC address, formated as described in [RAD802.1X]. It SHOULD only
 * be present in authentication and/or authorization requests.
 */
public class CallingStationId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CallingStationId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CallingStationId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CallingStationId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
