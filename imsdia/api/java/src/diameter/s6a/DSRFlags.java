package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The DSR-Flags AVP is of type Unsigned32 and it contains a bit mask. 
 * The meaning of the bits is defined below :
 * 0 -Regional Subscription Withdrawal,	This bit, when set, indicates that Regional 
 * Subscription shall be deleted from the subscriber data.
 *  1 -Complete APN Configuration Profile Withdrawal, This bit, when set, indicates 
 *     that all EPS Subscription Data for the subscriber shall be deleted from the 
 *     subscriber data.
 *  2 -Subscribed Charging Characteristics Withdrawal,	This bit, when set, indicates 
 *     that the Subscribed Charging Characteristics shall be replaced with a local 
 *     default  value or deleted in the MME.	
 *  3 -PDN subscription contexts Withdrawal, This bit, when set, indicates that the PDN 
 *      subscription contexts whose identifier is included in the Context-Identifier 
 *	AVP shall be deleted. 
 *  Note 1: If the Complete APN Configuration Profile Withdrawal bit is set, 
 *				this bit should not be set.
 */
public class DSRFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a DSRFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public DSRFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    DSRFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
