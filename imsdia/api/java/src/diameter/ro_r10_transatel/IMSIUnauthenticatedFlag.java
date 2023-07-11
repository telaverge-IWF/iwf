package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The IMSI-Unauthenticated-Flag AVP (AVP code 2308) is of type Enumerated, and indicates the served
 * IMSI is not authenticated. This may occur when emergency bearer service is provided 
 * (refer to TS 23.060 [74]  and TS 29.274 [91]). If this flag is not present, this means the 
 * served IMSI is authenticated.
 */
public class IMSIUnauthenticatedFlag extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Authenticated(0),
        Unauthenticated(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a IMSIUnauthenticatedFlag with the given value.
     *
     * @param value - the value of the AVP
     */
    public IMSIUnauthenticatedFlag(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    IMSIUnauthenticatedFlag(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
