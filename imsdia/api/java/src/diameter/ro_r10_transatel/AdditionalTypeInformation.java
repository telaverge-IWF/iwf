package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Additional-Type-Information AVP is of type UTF8String and identifies any additional information
 * beyond well-known media type or non-well-known media types.
 */
public class AdditionalTypeInformation extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AdditionalTypeInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public AdditionalTypeInformation(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    AdditionalTypeInformation(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
