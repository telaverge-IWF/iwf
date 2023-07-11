package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The SGW-Change AVP (AVP Code 2065) is of type Enumerated, and indicates 
  * this is the first Accounting Request (ACR)[Start] due to S-GW change. 
  * If this AVP is not present, this means this ACR [Start] is not due to 
  * SGW change.
  */
public class SGWChange extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ACR_Start_NOT_due_to_SGW_Change(0),
        ACR_Start_due_to_SGW_Change(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SGWChange with the given value.
     *
     * @param value - the value of the AVP
     */
    public SGWChange(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SGWChange(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
