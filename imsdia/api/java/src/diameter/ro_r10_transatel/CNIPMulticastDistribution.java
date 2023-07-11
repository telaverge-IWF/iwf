package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * CN-IP-Multicast-Distribution AVP (AVP code 921) is of type Enumerated. 
 * It represents an indication if IP multicast distribution to UTRAN should be 
 * used for the MBMS user plane data. The following values are supported:
 */
public class CNIPMulticastDistribution extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NO_IP_MULTICAST(0),
        IP_MULTICAST(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CNIPMulticastDistribution with the given value.
     *
     * @param value - the value of the AVP
     */
    public CNIPMulticastDistribution(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CNIPMulticastDistribution(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
