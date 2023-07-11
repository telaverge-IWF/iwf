package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The Accounting-Input-Packets AVP (AVP code 365)  together with the 
  * Accounting-Input-Octets AVP contain the number of packets (resp octets) ,
  * transmitted during the data container recording interval, reflecting the 
  * volume counts for uplink traffic for a data flow.
  */
public class AccountingInputPackets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingInputPackets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingInputPackets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingInputPackets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
