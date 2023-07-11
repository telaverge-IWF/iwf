package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class ChangeCondition extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ChangeCondition with the given value.
     *
     * @param value - the value of the AVP
     */
    public ChangeCondition(Integer value) {
        super(new com.intellinet.diameter.Integer32Data(value));
    }

    ChangeCondition(com.intellinet.diameter.Integer32Data data) {
        super(data);
    }
}
