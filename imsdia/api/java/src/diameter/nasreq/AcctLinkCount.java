package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Acct-Link-Count AVP (AVP Code 51) is of type Unsigned32 and
 * indicates the total number of links that have been active (current or
 * closed) in a given multilink session at the time the accounting
 * record is generated. This AVP MAY be included in Accounting-Requests
 * for any session that may be part of a multilink service.
 */
public class AcctLinkCount extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a AcctLinkCount with the given value.
     *
     * @param value - the value of the AVP
     */
    public AcctLinkCount(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    AcctLinkCount(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
