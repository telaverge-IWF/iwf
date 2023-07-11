package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The MMBox-Storage-Requested AVP (AVP code 1248) is of type Enumerated and 
 * indicates whether an MMBoxstorage has been requested by the originator MMS 
 * User Agent or not.The values for whether an MMBox Storage was requested are:
 */
public class MMBoxStorageRequested extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        No(0),
        Yes(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MMBoxStorageRequested with the given value.
     *
     * @param value - the value of the AVP
     */
    public MMBoxStorageRequested(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MMBoxStorageRequested(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
