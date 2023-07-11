package diameter.s6a;

import com.intellinet.diameter.*;


/** 
 * The Network-Access-Mode AVP is of type Enumerated.  The following values are defined:
 *	 PACKET_AND_CIRCUIT (0)
 *	 ONLY_CIRCUIT (1)
 *	 ONLY_PACKET  (2)
 */
public class NetworkAccessMode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PACKET_AND_CIRCUIT(0),
        ONLY_CIRCUIT(1),
        ONLY_PACKET(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a NetworkAccessMode with the given value.
     *
     * @param value - the value of the AVP
     */
    public NetworkAccessMode(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    NetworkAccessMode(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
