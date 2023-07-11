package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
  * The Accounting-Input-Octets AVP (AVP code 363)  together with the i
  * Accounting-Input-Packets AVP contain the number of octets (resp packets) ,
  * transmitted during the data container recording interval, reflecting the 
  * volume counts for uplink traffic for a data flow.
 */
public class AccountingInputOctets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingInputOctets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingInputOctets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingInputOctets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
