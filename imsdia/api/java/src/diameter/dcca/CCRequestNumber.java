package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * CC-Request-Number is of type Unsigned32 and identifies this request within one session. As
 * Session-Id AVPs are globally unique,the combination of Session-Id and CC-Request-Number is 
 * also globally unique and can be used in matching credit-control messages with confirmations.
 */
public class CCRequestNumber extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CCRequestNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCRequestNumber(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CCRequestNumber(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
