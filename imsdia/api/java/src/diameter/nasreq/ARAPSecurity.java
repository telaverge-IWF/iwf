package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ARAP-Security AVP (AVP Code 73) is of type Unsigned32 and MAY be
 * present in the AA-Answer message if the Framed-Protocol AVP (see
 * section 6.10.1) is set to the value of ARAP, and the Result-Code AVP
 * is set to DIAMETER_MULTI_ROUND_AUTH. See [RADIUSExt] for more
 * information on the format of this AVP.
 */
public class ARAPSecurity extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ARAPSecurity with the given value.
     *
     * @param value - the value of the AVP
     */
    public ARAPSecurity(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ARAPSecurity(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
