package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Filter-Id AVP is of type UTF8String and contains the name of the filter
 * list for this user. Zero or more Filter-Id AVPs MAY be sent in an 
 * authorisation answer.
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
