package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The NAS-Port-Type AVP (AVP Code 61) is of type Enumerated and contains the
 * type of the port on which the NAS is authenticating the user. This AVP 
 * SHOULD be present if the NAS uses the same NAS-Port number ranges for 
 * different service types concurrently. The supported values are defined in
 * [RADIUSTypes]. 
 */
public class NASPortType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Async(0),
        Sync(1),
        ISDN_Sync(2),
        ISDN_Async_V_120(3),
        ISDN_Async_V_110(4),
        Virtual(5),
        PIAFS(6),
        HDLC_Clear_Channel(7),
        X_25(8),
        X_75(9),
        G_3_Fax(10),
        SDSL(11),
        ADSL_CAP(12),
        ADSL_DMT(13),
        IDSL(14),
        Ethernet(15),
        xDSL(16),
        Cable(17),
        Wireless(18),
        IEEE_802_11(19),
        Token_Ring(20),
        FDDI(21),
        CDMA2000(22),
        UMTS(23),
        CDMA1X_EV(24),
        IAPP_IEEE_802_11f(25);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a NASPortType with the given value.
     *
     * @param value - the value of the AVP
     */
    public NASPortType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    NASPortType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
