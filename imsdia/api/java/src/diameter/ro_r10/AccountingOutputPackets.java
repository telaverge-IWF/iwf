package diameter.ro_r10;

import com.intellinet.diameter.*;


/** 
  * The Accounting-Output-Packets AVP (AVP code 366)  together with the 
  * Accounting-Output-Octets AVP contain the number of packets (resp octets) ,
  * transmitted during the data container recording interval, reflecting the 
  * volume counts for downlink traffic for a data flow.
 */
public class AccountingOutputPackets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingOutputPackets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingOutputPackets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingOutputPackets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
