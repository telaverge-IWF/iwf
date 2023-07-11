package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ARAP-Features AVP (AVP Code 71) is of type OctetString and MAY be
 * present in the AA-Accept message if the Framed-Protocol AVP is set to
 * the value of ARAP.  See [RADIUSExt] for more information about the
 * format of this AVP.
 */
public class ARAPZoneAccess extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        DEFAULT(0),
        INCLUSIVELY(2),
        EXCLUSIVELY(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ARAPZoneAccess with the given value.
     *
     * @param value - the value of the AVP
     */
    public ARAPZoneAccess(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ARAPZoneAccess(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
