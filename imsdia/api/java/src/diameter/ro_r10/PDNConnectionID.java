package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The PDN-Connection-ID AVP (AVP code 2050) is of type Unsigned32 and contains
 * the charging identifier to identify different records belonging to same PDN 
 * connection. This field includes Charging Id of first IP-CAN bearer activated  * within the PDN connection. Together with P-GW address this uniquely 
 * identifies the PDN connection.
 */
public class PDNConnectionID extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PDNConnectionID with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDNConnectionID(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PDNConnectionID(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
