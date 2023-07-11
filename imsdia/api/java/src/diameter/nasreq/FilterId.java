package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Filter-Id AVP (AVP Code 11) is of type UTF8String and contains the name
 * of the filter list for this user. Zero or more Filter-Id AVPs MAY be sent in
 * an authorization answer.
 * Identifying a filter list by name allows the filter to be used on different  
 * NASes without regard to filter-list implementation details. However, this
 * AVP is not roaming friendly, as filter naming differs from one service 
 * provider to another. In non-RADIUS environments, it is RECOMMENDED that the
 * NAS-Filter-Rule AVP be used instead.
 */
public class FilterId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FilterId with the given value.
     *
     * @param value - the value of the AVP
     */
    public FilterId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    FilterId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
