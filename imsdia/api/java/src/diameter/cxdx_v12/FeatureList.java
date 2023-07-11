package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Feature-List AVP is of type Unsigned32 and it contains a bit mask indicating the supported
 * features of an application. For the Cx application, the meaning of the bits has been defined in 7.1.1. 
 */
public class FeatureList extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a FeatureList with the given value.
     *
     * @param value - the value of the AVP
     */
    public FeatureList(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    FeatureList(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
