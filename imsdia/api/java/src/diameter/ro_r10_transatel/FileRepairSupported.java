package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * File-Repair-Supported AVP is of type Enumerated and indicates whether the MBMS user service supports 
 * point-to-point file repair. 
 */
public class FileRepairSupported extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SUPPORTED(1),
        NOT_SUPPORTED(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a FileRepairSupported with the given value.
     *
     * @param value - the value of the AVP
     */
    public FileRepairSupported(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    FileRepairSupported(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
