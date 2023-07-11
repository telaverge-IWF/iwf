package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The All-APN-Configurations-Included-Indicator AVP is of type Enumerated.  
 * The following values are defined:
 *    	 All_APN_CONFIGURATIONS_INCLUDED (0)
 * 	 MODIFIED/ADDED_APN_CONFIGURATIONS_INCLUDED (1)
 */
public class AllAPNConfigurationsIncludedIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        All_APN_CONFIGURATIONS_INCLUDED(0),
        MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AllAPNConfigurationsIncludedIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public AllAPNConfigurationsIncludedIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AllAPNConfigurationsIncludedIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
