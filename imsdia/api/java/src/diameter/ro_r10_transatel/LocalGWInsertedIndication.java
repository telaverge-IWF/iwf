package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Local-GW-Inserted-Indication  AVP (AVP code 2604) is of type Enumerated and indicates if 
 * the local GW (TrGW, IMS-AGW) is inserted or not for the SDP media component.
 */
public class LocalGWInsertedIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Local_GW_Not_Inserted(0),
        Local_GW_Inserted(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LocalGWInsertedIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public LocalGWInsertedIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LocalGWInsertedIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
