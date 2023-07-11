package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Participants-Involved AVP is of type UTF8String and holds the list of address (Public User ID,
 * SIP URI,TEL URI,MSISDN) of the parties who are involved into PoC session.
 */
public class ParticipantsInvolved extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ParticipantsInvolved with the given value.
     *
     * @param value - the value of the AVP
     */
    public ParticipantsInvolved(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    ParticipantsInvolved(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
