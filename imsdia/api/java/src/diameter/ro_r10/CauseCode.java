package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Cause-Code AVP is of type Integer32 and includes the cause code value from IMS node. It is used in 
 * Accounting-request [stop] and/or Acounting-request[event] messages. It is also used in the Credit-
 * Control-request [Terminate] and/or Credit-Control-request[event] messages.
 * Within the cause codes, values <= 0 are reserved for successful causes while values >= 1 are used
 * for failure causes. In case of errors where the session has been terminated as a result of a 
 * specific known SIP error code, then code is also used as the cause code.
 */
public class CauseCode extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CauseCode with the given value.
     *
     * @param value - the value of the AVP
     */
    public CauseCode(Integer value) {
        super(new com.intellinet.diameter.Integer32Data(value));
    }

    CauseCode(com.intellinet.diameter.Integer32Data data) {
        super(data);
    }
}
