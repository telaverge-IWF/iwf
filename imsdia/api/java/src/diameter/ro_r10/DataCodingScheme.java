package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Data-Coding-Scheme AVP (AVP code 2001) is of type Integer 32 and contains the data coding scheme of the message. For SM applications the specific coding is as described in TS 23.040 [216].
 */
public class DataCodingScheme extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a DataCodingScheme with the given value.
     *
     * @param value - the value of the AVP
     */
    public DataCodingScheme(Integer value) {
        super(new com.intellinet.diameter.Integer32Data(value));
    }

    DataCodingScheme(com.intellinet.diameter.Integer32Data data) {
        super(data);
    }
}
