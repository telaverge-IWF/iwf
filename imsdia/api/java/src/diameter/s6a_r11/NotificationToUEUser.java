package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class NotificationToUEUser extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOTIFY_LOCATION_ALLOWED(0),
        NOTIFYANDVERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE(1),
        NOTIFYANDVERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE(2),
        LOCATION_NOT_ALLOWED(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a NotificationToUEUser with the given value.
     *
     * @param value - the value of the AVP
     */
    public NotificationToUEUser(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    NotificationToUEUser(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
