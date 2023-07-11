package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class ListOfMeasurements extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ListOfMeasurements with the given value.
     *
     * @param value - the value of the AVP
     */
    public ListOfMeasurements(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ListOfMeasurements(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
