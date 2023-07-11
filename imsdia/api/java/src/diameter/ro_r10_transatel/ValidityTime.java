package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Validity-Time AVP is of type Unsigned32 (AVP Code 448).  It is sent from the credit-control
 * server to the credit-control client. The AVP contains the validity time of the granted service 
 * units. The measurement of the Validity-Time is started upon receipt of the Credit-Control-Answer
 * Message containing this AVP.  If the granted service units have not been consumed within the 
 * validity time specified in this AVP, the credit-control client MUST send a Credit-Control-Request
 * message to the server, with CC-Request-Type set to UPDATE_REQUEST. The value field of the 
 * Validity-Time AVP is given in seconds.
 */
public class ValidityTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ValidityTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public ValidityTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ValidityTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
