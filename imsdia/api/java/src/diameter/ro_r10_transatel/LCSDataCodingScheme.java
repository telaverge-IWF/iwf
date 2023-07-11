package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * LCS-Data-Coding-Scheme AVP is of type UTF8String and contains information of the alphabet and the 
 * language used.
 */
public class LCSDataCodingScheme extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LCSDataCodingScheme with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSDataCodingScheme(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    LCSDataCodingScheme(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
