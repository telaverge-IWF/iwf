package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * This Envelope-Reporting AVP (AVP code 1268) is of type Enumerated and
 * is used in the CCA (INITIAL) to indicate whether the client shall
 * report the start and end of each time envelope, in those cases in
 * which quota is consumed in envelopes.
 */
public class EnvelopeReporting extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        DO_NOT_REPORT_ENVELOPES(0),
        REPORT_ENVELOPES(1),
        REPORT_ENVELOPES_WITH_VOLUME(2),
        REPORT_ENVELOPES_WITH_EVENTS(3),
        REPORT_ENVELOPES_WITH_VOLUME_AND_EVENTS(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a EnvelopeReporting with the given value.
     *
     * @param value - the value of the AVP
     */
    public EnvelopeReporting(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    EnvelopeReporting(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
