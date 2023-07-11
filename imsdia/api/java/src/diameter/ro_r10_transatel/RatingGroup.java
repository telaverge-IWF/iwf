package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Rating-Group AVP is of type Unsigned32 (AVP Code 432) and contains the
 * identifier of a rating group. All the services subject to the same rating 
 * type are part of the same rating group. The specific rating group the 
 * request relates to is uniquely identified by the combination of 
 * Service-Context-Id and Rating-Group AVPs.
 */
public class RatingGroup extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a RatingGroup with the given value.
     *
     * @param value - the value of the AVP
     */
    public RatingGroup(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    RatingGroup(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
