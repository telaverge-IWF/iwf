package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The APN-Aggregated-Max-Bitrate-DL AVP (AVP code 1040) is of type Unsigned32,
 * and it indicates the maximum aggregate bit rate in bits per seconds for the
 * downlink direction across all non-GBR bearers related with the same APN.
 */
public class APNAggregateMaxBitrateDL extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a APNAggregateMaxBitrateDL with the given value.
     *
     * @param value - the value of the AVP
     */
    public APNAggregateMaxBitrateDL(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    APNAggregateMaxBitrateDL(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
