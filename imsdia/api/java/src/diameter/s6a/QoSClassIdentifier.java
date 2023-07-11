package diameter.s6a;

import com.intellinet.diameter.*;


/**
* QoS-Class-Identifier AVP (AVP code 1028) is of type Enumerated, and it defines 
* the maximum authorized traffic class for the transport bearer or service flow. 
* The following values are defined:
* 	TRAFFIC_CLASS_A (0) -This value defines that the QoS class is A.
* 	TRAFFIC_CLASS_B (1)- This value defines that the QoS class is B.
* 	TRAFFIC_CLASS_C (2)-This value defines that the QoS class is C.
*	TRAFFIC_CLASS_D (3)- This value defines that the QoS class is D.
* 	TRAFFIC_CLASS_E (4)-This value defines that the QoS class is E.
* 	TRAFFIC_CLASS_F (5)-This value defines that the QoS class is F.
* The mapping of QCI to QoS classes of specific transport technology can be found 
* in pertinent SDO's specification.
*/
public class QoSClassIdentifier extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        TRAFFIC_CLASS_A(1),
        TRAFFIC_CLASS_B(2),
        TRAFFIC_CLASS_C(3),
        TRAFFIC_CLASS_D(4),
        TRAFFIC_CLASS_E(5),
        TRAFFIC_CLASS_F(6),
        TRAFFIC_CLASS_G(7),
        TRAFFIC_CLASS_H(8),
        TRAFFIC_CLASS_I(9);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a QoSClassIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public QoSClassIdentifier(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    QoSClassIdentifier(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
