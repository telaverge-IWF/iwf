package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The RAT-Type AVP (AVP code 1032) is of type Enumerated and is used to identify the 
 * radio access technology that is serving the UE.  NOTE1: Values 0-999 are used for generic 
 * radio access technologies that can apply to different IP-CAN types and are not IP-CAN specific.
 * NOTE2: Values 1000-1999 are used for 3GPP specific radio access technology types.
 * NOTE3: Values 2000-2999 are used for 3GPP2 specific radio access technology types. 
 * The following values are defined:
 * WLAN (0) -This value shall be used to indicate that the RAT is WLAN.
 * UTRAN (1000) This value shall be used to indicate that the RAT is UTRAN. 
 * For further details refer to 3GPP TS 29.060 [18].
 * GERAN (1001) This value shall be used to indicate that the RAT is GERAN. 
 * For further details refer to 3GPP TS 29.060 [18].
 * GAN (1002) This value shall be used to indicate that the RAT is GAN. 
 * For further details refer to 3GPP TS 29.060 [18].
 * HSPA_EVOLUTION (1003) This value shall be used to indicate that the RAT is HSPA Evolution. 
 * For further details refer to 3GPP TS 29.060 [18].
 * CDMA2000_1X (2000) This value shall be used to indicate that the RAT is CDMA2000 1X. 
 * For further details refer to 3GPP2 X.S0011-D [20].
 * HRPD (2001) This value shall be used to indicate that the RAT is HRPD.
 * For further details refer to 3GPP2 X.S0011-D [20].
 * UMB (2002) This value shall be used to indicate that the RAT is UMB. 
 * For further details refer to 3GPP2 X.S0011-D [20].
*/
public class RATType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        WLAN(0),
        UTRAN(1000),
        GERAN(1001),
        GAN(1002),
        HSPA_EVOLUTION(1003),
        EUTRAN(1004),
        CDMA2000_1X(2000),
        HRPD(2001),
        UMB(2002);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a RATType with the given value.
     *
     * @param value - the value of the AVP
     */
    public RATType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    RATType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
