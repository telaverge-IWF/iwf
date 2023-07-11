package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class CompleteDataListIncludedIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        All_PDP_CONTEXTS_INCLUDED(0),
        MODIFIED_ADDED_PDP_CONTEXTS_INCLUDED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CompleteDataListIncludedIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public CompleteDataListIncludedIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CompleteDataListIncludedIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
