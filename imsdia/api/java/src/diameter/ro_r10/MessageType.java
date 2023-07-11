package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Message-Type AVP is of type Enumerated and holds the type of message according to the MMs transaction
 * e.g sunmission,delivery.
 */
public class MessageType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        m_send_req(1),
        m_send_conf(2),
        m_notification_ind(3),
        m_notifyresp_ind(4),
        m_retrive_conf(5),
        m_acknowledge_ind(6),
        m_delivery_ind(7),
        m_read_rec_ind(8),
        m_read_orig_ind(9),
        m_forward_req(10),
        m_forward_conf(11),
        m_mbox_store_conf(12),
        m_mbox_view_conf(13),
        m_mbox_upload_conf(14),
        m_mbox_delete_conf(15);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MessageType with the given value.
     *
     * @param value - the value of the AVP
     */
    public MessageType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MessageType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
