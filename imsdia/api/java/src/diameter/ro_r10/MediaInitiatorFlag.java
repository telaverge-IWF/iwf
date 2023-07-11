package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Media-Initiator-Flag AVP is of type Enumerated and indicates which party has requested the session 
 * modification. The default value is '0' indicating the called party initiated the modification.
 */
public class MediaInitiatorFlag extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        called_party(0),
        calling_party(1),
        unknown(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MediaInitiatorFlag with the given value.
     *
     * @param value - the value of the AVP
     */
    public MediaInitiatorFlag(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MediaInitiatorFlag(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
