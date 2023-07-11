package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class UESRVCCCapability extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        UE_SRVCC_NOT_SUPPORTED(0),
        UE_SRVCC_SUPPORTED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a UESRVCCCapability with the given value.
     *
     * @param value - the value of the AVP
     */
    public UESRVCCCapability(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    UESRVCCCapability(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
