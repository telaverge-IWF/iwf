package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The PDN-GW-Allocation-Type AVP is of type Enumerated. It indicates whether the 
 * PDN GW address is statically allocated or dynamically selected by other nodes. 
 * If this AVP is not present, this means that the address is statically allocated. 
 * The following values are defined:
 *		STATIC (0)
 *		DYNAMIC (1)
 */
public class PDNGWAllocationType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        STATIC(0),
        DYNAMIC(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PDNGWAllocationType with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDNGWAllocationType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PDNGWAllocationType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
