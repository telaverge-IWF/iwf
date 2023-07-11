package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The Cancellation-Type AVP is of type Enumerated and indicates the type of cancellation. 
 * The following values are defined:
 * UPDATE_PROCEDURE (0) -     This value is used when the Cancel Location is sent to the 
 *                 previous MME due to a received Update Location message from a new MME.
 * SUBSCRIPTION_WITHDRAWAL (1) - This value is used when the Cancel Location is sent to the 
 *             current MME due to withdrawal of the user's subscription by the HSS operator.
 */
public class CancellationType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        MME_UPDATE_PROCEDURE(0),
        SGSN_UPDATE_PROCEDURE(1),
        SUBSCRIPTION_WITHDRAWAL(2),
        UPDATE_PROCEDURE_IWF(3),
        INITIAL_ATTACH_PROCEDURE(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CancellationType with the given value.
     *
     * @param value - the value of the AVP
     */
    public CancellationType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CancellationType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
