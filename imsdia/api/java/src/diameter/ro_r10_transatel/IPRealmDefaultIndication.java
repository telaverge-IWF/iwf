package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The IP-Realm-Default-Indication  AVP (AVP code 2603) is of type Enumerated and indicates 
 * whether the IP realm used for the SDP media component is the Default IP realm or not.
 */
public class IPRealmDefaultIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Default_IP_Realm_Not_used(0),
        Default_IP_realm_used(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a IPRealmDefaultIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public IPRealmDefaultIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    IPRealmDefaultIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
