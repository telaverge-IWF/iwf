package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class IMSVoiceOverPSSessionsSupported extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOT_SUPPORTED(0),
        SUPPORTED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a IMSVoiceOverPSSessionsSupported with the given value.
     *
     * @param value - the value of the AVP
     */
    public IMSVoiceOverPSSessionsSupported(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    IMSVoiceOverPSSessionsSupported(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
