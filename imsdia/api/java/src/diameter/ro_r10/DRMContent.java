package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * DRM-Content AVP is of type Enumerated and indicates if the MM contains DRM-protected content.
 */
public class DRMContent extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        No(0),
        Yes(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a DRMContent with the given value.
     *
     * @param value - the value of the AVP
     */
    public DRMContent(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    DRMContent(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
