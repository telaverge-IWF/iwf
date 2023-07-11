package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The QoS-Subscribed AVP is of type OctetString. Octets are coded according 
 * to 3GPP TS 29.002 [24] (octets of QoS-Subscribed, Ext-QoS-Subscribed, 
 * Ext2-QoS-Subscribed and Ext3-QoS-Subscribed values are concatenated). 
 */
public class QoSSubscribed extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a QoSSubscribed with the given value.
     *
     * @param value - the value of the AVP
     */
    public QoSSubscribed(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    QoSSubscribed(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
