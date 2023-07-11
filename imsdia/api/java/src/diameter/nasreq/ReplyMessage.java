package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Reply-Message AVP (AVP Code 18) is of type UTF8String and contains text
 * that MAY be displayed to the user. When used in a AA-Answer message with a
 * successful Result-Code AVP, it indicates success. When found in an AAA
 * message with a Result-Code other than DIAMETER_SUCCESS, the AVP contains a
 * failure message.
 * The Reply-Message AVP MAY indicate dialog text to prompt the user before
 * another AA-Request attempt. When used in an AA-Answer with a Result-Code of
 * DIAMETER_MULTI_ROUND_AUTH or in an Re-Auth-Request message, it MAY contain
 * a dialog text to prompt the user for a response.
 */
public class ReplyMessage extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ReplyMessage with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReplyMessage(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ReplyMessage(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
