package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * QoS-Class-Identifier AVP (AVP code 1028) is of type Enumerated, and it identifies a set of
 * IP-CAN specific QoS parameters that define the authorized QoS, excluding the applicable
 * bitrates and ARP for the IP-CAN bearer or service flow
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
