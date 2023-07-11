package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
  * The Serving-Node-Type AVP (AVP Code 2047) is of type Enumerated and 
  * identifies the type of Serving Node. It may take the following values: 
  */
public class ServingNodeType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SGSN(0),
        PMIPSGW(1),
        GTPSGW(2),
        ePDG(3),
        hSGW(4),
        MME(5);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ServingNodeType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServingNodeType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ServingNodeType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
