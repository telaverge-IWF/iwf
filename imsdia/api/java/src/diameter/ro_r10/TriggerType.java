package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Trigger-Type AVP is of type Enumerated and indicates a single re-authorisation event type.
 * When included in the Credit Control Answer command, this AVP indicates the events that
 * shall cause the credit control client to re-authorise the associated quota. The client 
 * shall not re-authorise the quota when events which are not included in the Trigger-Type AVP occur.
 * When included in the Credit Control Request command indicates the specific event which caused the 
 * re-authorisation request of the Reporting-Reason with value RATING_CONDITION_CHANGE associated.
 */
public class TriggerType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        CHANGE_IN_SGSN_IP_ADDRESS(1),
        CHANGE_IN_QOS(2),
        CHANGE_IN_LOCATION(3),
        CHANGE_IN_RAT(4),
        CHANGEINQOS_TRAFFIC_CLASS(10),
        CHANGEINQOS_RELIABILITY_CLASS(11),
        CHANGEINQOS_DELAY_CLASS(12),
        CHANGEINQOS_PEAK_THROUGHPUT(13),
        CHANGEINQOS_PRECEDENCE_CLASS(14),
        CHANGEINQOS_MEAN_THROUGHPUT(15),
        CHANGEINQOS_MAXIMUM_BIT_RATE_FOR_UPLINK(16),
        CHANGEINQOS_MAXIMUM_BIT_RATE_FOR_DOWNLINK(17),
        CHANGEINQOS_RESIDUAL_BER(18),
        CHANGEINQOS_SDU_ERROR_RATIO(19),
        CHANGEINQOS_TRANSFER_DELAY(20),
        CHANGEINQOS_TRAFFIC_HANDLING_PRIORITY(21),
        CHANGEINQOS_GUARANTEED_BIT_RATE_FOR_UPLINK(22),
        CHANGEINQOS_GUARANTEED_BIT_RATE_FOR_DOWNLINK(23),
        CHANGEINLOCATION_MCC(30),
        CHANGEINLOCATION_MNC(31),
        CHANGEINLOCATION_RAC(32),
        CHANGEINLOCATION_LAC(33),
        CHANGEINLOCATION_CellId(34),
        CHANGE_IN_MEDIA_COMPOSITION(40),
        CHANGEINPARTICIPANTS_Number(50),
        CHANGE_IN_THRSHLD_OF_PARTICIPANTS_NMB(51),
        CHANGE_IN_USER_PARTICIPATING_TYPE(52),
        CHANGE_IN_SERVICE_CONDITION(60),
        CHANGE_IN_SERVING_NODE(61);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a TriggerType with the given value.
     *
     * @param value - the value of the AVP
     */
    public TriggerType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    TriggerType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
