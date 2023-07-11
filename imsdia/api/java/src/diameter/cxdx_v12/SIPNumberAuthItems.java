package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The SIP-Number-Auth-Items AVP is of type Unsigned32 and indicates the number of authentication vectors provided
 * by the Diameter server.
 * <p>
 * When used in a request it indicates the number of SIP-Auth-Data-Item��s the S-CSCF is requesting. This can be used, for
 * instance, when the client is requesting several pre-calculated authentication vectors. In the answer message the SIPNumber-
 * Auth-Items AVP indicates the actual number of items provided by the Diameter server.
 */
public class SIPNumberAuthItems extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SIPNumberAuthItems with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPNumberAuthItems(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    SIPNumberAuthItems(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
