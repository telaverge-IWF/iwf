package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class SMSReqisterRequest extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SMS_REGISTRATION_REQUIRED(0),
        SMS_REGISTRATION_NOT_PREFERRED(1),
        NO_PREFERENCE(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SMSReqisterRequest with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMSReqisterRequest(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SMSReqisterRequest(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
