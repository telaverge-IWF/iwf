package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Account-Expiration AVP (AVP code 2309) is of type Time and 
 * indicates the subscriber account expiration date and time of day.
 */
public class AccountExpiration extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a AccountExpiration with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountExpiration(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    AccountExpiration(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
