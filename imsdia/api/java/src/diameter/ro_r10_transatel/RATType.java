package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The RAT-Type AVP (AVP code 1032) is of type Enumerated and is used to identify the radio
* access technology that is serving the UE.
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
        UMB(2002),
        EHRPD(2003);

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
