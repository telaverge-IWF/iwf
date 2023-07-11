package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * LCS-Client-Dialed-By-MS AVP is of type UTF8String and holds the number of the LCS client
 * dialled by the UE.
 */
public class LCSClientDialedByMS extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LCSClientDialedByMS with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSClientDialedByMS(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    LCSClientDialedByMS(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
