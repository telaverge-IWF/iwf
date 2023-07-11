package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The PoC-Event-Type AVP (AVP code 2025) is of type Enumerated and indicates 
  * PoC session unrelated charging event.
  */
public class PoCEventType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Normal(0),
        Instant_Ppersonal_Aalert_event(1),
        PoC_Group_Advertisement_event(2),
        Early_Ssession_Setting_up_event(3),
        PoC_Talk_Burst(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PoCEventType with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCEventType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PoCEventType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
