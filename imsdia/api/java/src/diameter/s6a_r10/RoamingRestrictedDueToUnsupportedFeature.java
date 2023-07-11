package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class RoamingRestrictedDueToUnsupportedFeature extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Roaming_Restricted_Due_To_Unsupported_Feature(0);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a RoamingRestrictedDueToUnsupportedFeature with the given value.
     *
     * @param value - the value of the AVP
     */
    public RoamingRestrictedDueToUnsupportedFeature(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    RoamingRestrictedDueToUnsupportedFeature(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
