package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The Access-Restriction-Data AVP is of type Unsigned32 and it contains a bit mask where each bit 
 * when set to 1 indicates a restriction.. The meaning of the bits is the following:
 * 0	UTRAN Not Allowed
 * 1	GERAN Not Allowed
 * 2	GAN Not Allowed
 * 3	I-HSPA-Evolution Not Allowed
 * 4	E-UTRAN Not Allowed
 * 5	HO-To-Non-3GPP-Access Not Allowed
 * 6	Roaming Restricted In MME Due To Unsupported Feature
 */
public class AccessRestrictionData extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a AccessRestrictionData with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccessRestrictionData(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    AccessRestrictionData(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
