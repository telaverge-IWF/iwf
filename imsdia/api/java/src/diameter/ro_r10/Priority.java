package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Priority AVP is of type Enumerated and the priority of the message is specified by the originator 
 * MMs User Agent.
 */
public class Priority extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Low(0),
        Normal(1),
        High(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a Priority with the given value.
     *
     * @param value - the value of the AVP
     */
    public Priority(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    Priority(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
