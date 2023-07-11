package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class ReportInterval extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        MSEC_250(0),
        MSEC_500(1),
        MSEC_1000(2),
        MSEC_2000(3),
        MSEC_3000(4),
        MSEC_4000(5),
        MSEC_6000(6),
        MSEC_8000(7),
        MSEC_12000(8),
        MSEC_16000(9),
        MSEC_20000(10),
        MSEC_24000(11),
        MSEC_28000(12),
        MSEC_32000(13),
        MSEC_64000(14),
        MSEC_120(15),
        MSEC_240(16),
        MSEC_480(17),
        MSEC_640(18),
        MSEC_1024(19),
        MSEC_2048(20),
        MSEC_5120(21),
        MSEC_10240(22),
        MSEC_60000(23),
        MSEC_360000(24),
        MSEC_720000(25),
        MSEC_1800000(26),
        MSEC_3600000(27);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ReportInterval with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReportInterval(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ReportInterval(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
