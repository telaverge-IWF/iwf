package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The Accounting-Output-Octets AVP (AVP code 364)  together with the 
  * Accounting-Output-Packets AVP  contain the number of octets (resp packets),
  * transmitted during the data container recording interval, reflecting the 
  * volume counts for downlink traffic for a data flow.
  */
public class AccountingOutputOctets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingOutputOctets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingOutputOctets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingOutputOctets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
