package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The Feature-List AVP is of type Unsigned32 and it contains a bit mask
 * indicating the supported * features of an application.
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
