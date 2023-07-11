package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The leading digits of an User Name (i.e. MCC, MNC, leading digits of MSIN, 
 * see 3GPP TS 23.003 [3]). Within a HSS an User-Id identifies a set of subscribers, 
 * each of which have identical leading User Name digits.
 */
public class UserId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a UserId with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    UserId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
