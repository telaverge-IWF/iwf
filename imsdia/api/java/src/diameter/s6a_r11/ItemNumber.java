package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The Item-Number AVP is of type Unsigned32. If more than one EPS Vector is included 
 * within one Authentication-Info AVP, the Item-Number AVP shall be present within each 
 * EPS Vector. Vectors with lower Item Number should be used before Vectors with higher 
 * Item Number are used in the MME. The Item Number is used to order Vectors received 
 * within one request. For Vectors received within different requests those received by 
 * the earlier request should be used before those received by the later request.
 */
public class ItemNumber extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ItemNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public ItemNumber(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ItemNumber(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
