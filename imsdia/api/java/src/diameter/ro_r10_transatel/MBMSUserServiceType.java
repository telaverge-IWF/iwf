package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * MBMS-User-Service-Type AVP is of type Enumerated and indicates type of service the MBMS user service that
 * is being delivered.
 */
public class MBMSUserServiceType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        DOWNLOAD(1),
        STREAMING(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MBMSUserServiceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public MBMSUserServiceType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MBMSUserServiceType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
