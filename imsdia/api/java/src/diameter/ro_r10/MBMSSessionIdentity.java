package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * MBMS-Session-Identity AVP is of type OctetString. Its length is one octet. It is allocated by the BM-SC.
 * together with TMGI it identifies a transmission of a specific MBMS session. The initial transmission and 
 * the subsequent transmissions of the MBMS session will use the same values of these parameters. This AVP 
 * is optional within the Gmb interface.
 */
public class MBMSSessionIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a MBMSSessionIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public MBMSSessionIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    MBMSSessionIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
