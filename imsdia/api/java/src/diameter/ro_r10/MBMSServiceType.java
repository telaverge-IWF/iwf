package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * MBMS-Service-Type AVP is of type Enumerated and contains explicit information about the type of
 * service that the BM-SC start Procedure is about to start.
 */
public class MBMSServiceType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        MULTICAST(0),
        BROADCAST(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MBMSServiceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public MBMSServiceType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MBMSServiceType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
