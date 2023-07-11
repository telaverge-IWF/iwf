package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * PS-Append-Free-Format-Data AVP is of type enumerated and indicates if the information sent in the
 * PS-Free-Format-Data AVP must be appended to the PS-Free-Format-Data stored for the online-session.
 */
public class PSAppendFreeFormatData extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Append(0),
        Overwrite(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PSAppendFreeFormatData with the given value.
     *
     * @param value - the value of the AVP
     */
    public PSAppendFreeFormatData(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PSAppendFreeFormatData(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
