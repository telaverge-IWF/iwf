package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class HomogeneousSupportofIMSVoiceOverPSSessions extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOT_SUPPORTED(0),
        SUPPORTED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a HomogeneousSupportofIMSVoiceOverPSSessions with the given value.
     *
     * @param value - the value of the AVP
     */
    public HomogeneousSupportofIMSVoiceOverPSSessions(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    HomogeneousSupportofIMSVoiceOverPSSessions(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
