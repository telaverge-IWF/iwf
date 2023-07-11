package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Feature-List-ID AVP is of type Unsigned32 and it contains the identity
 * of a feature list.
 */
public class FeatureListID extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a FeatureListID with the given value.
     *
     * @param value - the value of the AVP
     */
    public FeatureListID(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    FeatureListID(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
