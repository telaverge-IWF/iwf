package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The CUG-Information AVP (AVP code 2304) is of type OctetString and holds the CUG Interlock Code. 
 * which identifies CUG membership within the Network for .Closed User Group. MMTel supplementary service.
 */
public class CUGInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CUGInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public CUGInformation(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CUGInformation(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
