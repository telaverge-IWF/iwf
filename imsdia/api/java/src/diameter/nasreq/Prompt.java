package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Prompt AVP (AVP Code 76) is of type Enumerated and MAY be present in the
 * AA-Answer message. When present, it is used by the NAS to determine whether
 * the user's response, when entered, should be echoed.
 */
public class Prompt extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOECHO(0),
        ECHO(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a Prompt with the given value.
     *
     * @param value - the value of the AVP
     */
    public Prompt(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    Prompt(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
