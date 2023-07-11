package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The CHAP-Algorithm AVP (AVP Code 403) is of type Enumerated and
 * contains the algorithm identifier used in the computation of the CHAP
 * response [PPPCHAP].
 */
public class CHAPAlgorithm extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        CHAPMD5(5);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CHAPAlgorithm with the given value.
     *
     * @param value - the value of the AVP
     */
    public CHAPAlgorithm(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CHAPAlgorithm(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
