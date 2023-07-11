package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The APN-Aggregated-Max-Bitrate-UL AVP (AVP code 1041) is of type Unsigned32,
 * and it indicates the maximum aggregate bit rate in bits per seconds for the
 * uplink direction across all non-GBR bearers related with the same APN.
 */
public class APNAggregateMaxBitrateUL extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a APNAggregateMaxBitrateUL with the given value.
     *
     * @param value - the value of the AVP
     */
    public APNAggregateMaxBitrateUL(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    APNAggregateMaxBitrateUL(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
