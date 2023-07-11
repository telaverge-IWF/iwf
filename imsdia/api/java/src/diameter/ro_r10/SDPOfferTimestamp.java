package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SDP-Offer-Timestamp AVP (AVP code 1274) is of type Time and holds the 
 * time in UTC format of the SDP offer
 */
public class SDPOfferTimestamp extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SDPOfferTimestamp with the given value.
     *
     * @param value - the value of the AVP
     */
    public SDPOfferTimestamp(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    SDPOfferTimestamp(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
