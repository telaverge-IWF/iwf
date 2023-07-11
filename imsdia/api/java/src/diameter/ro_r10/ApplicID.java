package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Applic-ID AVP is of type UTF8String and holds the identification of the destination application that
 * the underlying MMS abstract message was addressed to.
 */
public class ApplicID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ApplicID with the given value.
     *
     * @param value - the value of the AVP
     */
    public ApplicID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ApplicID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
