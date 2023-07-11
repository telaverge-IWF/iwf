package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SM-Service-Type AVP (AVP code 2029) is of type Enumerated and indicates 
 * the type of SM service that caused the charging interaction
 */
public class SMServiceType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        VAS4SMS_content_processing(0),
        VAS4SMS_Forwarding(1),
        VAS4SMS_Forwarding_Multiple_Subscriptions(2),
        VAS4SMS_Filtering(3),
        VAS4SMS_Receipt(4),
        VAS4SMS_Network_Storage(5),
        VAS4SMS_To_Multiple_destinations(6),
        VAS4SMS_Virtual_Private_Network(7),
        VAS4SMS_Auto_Reply(8),
        VAS4SMS_Personal_Signature(9),
        VAS4SMS_Deferred_Delivery(10);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SMServiceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMServiceType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SMServiceType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
