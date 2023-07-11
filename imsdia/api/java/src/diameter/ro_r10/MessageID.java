package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Message-ID AVP is of type UTF8String and holds the MM identification provided by the originating
 * MMs\s Relay/Server.
 */
public class MessageID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a MessageID with the given value.
     *
     * @param value - the value of the AVP
     */
    public MessageID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    MessageID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
