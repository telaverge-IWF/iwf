package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Read-Reply-Report-Requested AVP is of type Enumerated and indicates whether a read reply report has
 * been requested by the originator MMS User Agent or not.
 */
public class ReadReplyReportRequested extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        No(0),
        Yes(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ReadReplyReportRequested with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReadReplyReportRequested(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ReadReplyReportRequested(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
