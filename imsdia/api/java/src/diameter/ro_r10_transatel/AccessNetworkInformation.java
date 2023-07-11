package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Access-Network-Information AVP (AVP code 1263) is of type OctetString 
 * and indicates the SIP P-header "P-Access-Network-Information".
 */
public class AccessNetworkInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AccessNetworkInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccessNetworkInformation(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    AccessNetworkInformation(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
