package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Reply-Path-Requested AVP (AVP code 2011) is of type Enumerated. The possible values are:
 */
public class ReplyPathRequested extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        No_Reply_Path_Set(0),
        Reply_path_Set(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ReplyPathRequested with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReplyPathRequested(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ReplyPathRequested(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
