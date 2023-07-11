package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The PDP-Address-Prefix-Length AVP (AVP code 2606) is of type Unsigned32 and contains the prefix length 
* of an IPv6 typed PDP-Address AVP. The omission of this AVP for an IPv6 typed IP address implicitly means
* prefix length of 64 bits, as in this case the 64 bit prefix length default shall be assumed.
*/
public class PDPAddressPrefixLength extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PDPAddressPrefixLength with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDPAddressPrefixLength(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PDPAddressPrefixLength(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
