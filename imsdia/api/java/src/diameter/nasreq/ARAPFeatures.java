package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ARAP-Features AVP (AVP Code 71) is of type OctetString and MAY be
 * present in the AA-Accept message if the Framed-Protocol AVP is set to
 * the value of ARAP. See [RADIUSExt] for more information about the
 * format of this AVP.
 */
public class ARAPFeatures extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ARAPFeatures with the given value.
     *
     * @param value - the value of the AVP
     */
    public ARAPFeatures(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ARAPFeatures(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
