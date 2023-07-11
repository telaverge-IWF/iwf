package diameter.s6a_r11;

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
        QCI_1(1),
        QCI_2(2),
        QCI_3(3),
        QCI_4(4),
        QCI_5(5),
        QCI_6(6),
        QCI_7(7),
        QCI_8(8),
        QCI_9(9);

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
