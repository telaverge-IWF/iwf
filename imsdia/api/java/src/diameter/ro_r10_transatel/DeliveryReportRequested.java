package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Delivery-Report-Requested AVP is of type Enumerated and indicates whether a delivery report has been 
 * requested by teh originator MMS User Agent or not.
 */
public class DeliveryReportRequested extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        No(0),
        Yes(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a DeliveryReportRequested with the given value.
     *
     * @param value - the value of the AVP
     */
    public DeliveryReportRequested(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    DeliveryReportRequested(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
