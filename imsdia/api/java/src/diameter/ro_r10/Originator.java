package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Originator AVP is of type Enumerated and indicates the originating party of the message body.
 */
public class Originator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Calling_Party(0),
        Called_Party(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a Originator with the given value.
     *
     * @param value - the value of the AVP
     */
    public Originator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    Originator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
