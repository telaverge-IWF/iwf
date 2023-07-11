package diameter.ro_r10;

import com.intellinet.diameter.*;


public class DeliveryStatus extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a DeliveryStatus with the given value.
     *
     * @param value - the value of the AVP
     */
    public DeliveryStatus(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    DeliveryStatus(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
