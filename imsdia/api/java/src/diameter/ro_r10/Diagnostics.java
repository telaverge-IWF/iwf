package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
  * The Diagnostics AVP (AVP code 2039) is of type Integer32 and provides a 
  * more detailed cause value for sending  Accounting-request from PCN node. 
  * It complements the Change-Condition AVP.
  */
public class Diagnostics extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a Diagnostics with the given value.
     *
     * @param value - the value of the AVP
     */
    public Diagnostics(Integer value) {
        super(new com.intellinet.diameter.Integer32Data(value));
    }

    Diagnostics(com.intellinet.diameter.Integer32Data data) {
        super(data);
    }
}
