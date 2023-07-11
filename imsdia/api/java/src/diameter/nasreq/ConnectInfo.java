package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Connect-Info AVP (AVP Code 77) is of type UTF8String and is sent in the
 * AA-Request message or ACR STOP message. When sent in the Access-Request, it
 * indicates the nature of the user's connection.
 * The connection speed SHOULD be included at the beginning of the first 
 * Connect-Info AVP in the message.
 */
public class ConnectInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ConnectInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public ConnectInfo(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ConnectInfo(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
