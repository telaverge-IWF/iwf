package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Accounting-Auth-Method AVP (AVP Code 406) is of type Enumerated.
 * A NAS MAY include this AVP in an Accounting-Request message to
 * indicate the method used to authenticate the user. (Note that this
 * is equivalent to the RADIUS MS-Acct-Auth-Type VSA attribute).
 */
public class AccountingAuthMethod extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PAP(1),
        CHAP(2),
        MS_CHAP_1(3),
        MS_CHAP_2(4),
        EAP(5),
        NONE(7);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AccountingAuthMethod with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingAuthMethod(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AccountingAuthMethod(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
