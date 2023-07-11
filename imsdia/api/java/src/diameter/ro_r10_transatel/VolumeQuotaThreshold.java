package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Volume-Quota-Threshold AVP is of type Unsigned32 and contains a threshold value in octets.
 */
public class VolumeQuotaThreshold extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a VolumeQuotaThreshold with the given value.
     *
     * @param value - the value of the AVP
     */
    public VolumeQuotaThreshold(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    VolumeQuotaThreshold(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
