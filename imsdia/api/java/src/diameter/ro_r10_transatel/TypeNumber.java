package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Type-Number AVP is of type Enumerated and identifies the well-known media types. The values
 * taken from OMNA WSP Content type codes database.
 */
public class TypeNumber extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TypeNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public TypeNumber(Integer value) {
        super(new com.intellinet.diameter.Integer32Data(value));
    }

    TypeNumber(com.intellinet.diameter.Integer32Data data) {
        super(data);
    }
}
