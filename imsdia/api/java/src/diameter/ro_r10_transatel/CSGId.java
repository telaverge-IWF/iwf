package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The CSG-Id  AVP is of type Unsigned32. Values are coded according to 3GPP TS 23.003 [3].
* Unused bits (least significant) shall be padded with zeros.
*/
public class CSGId extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CSGId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CSGId(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CSGId(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
