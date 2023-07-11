package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Incoming-Trunk-Group-ID AVP is of type UTF8String and identifies the incoming PSTN leg.
 */
public class IncomingTrunkGroupID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a IncomingTrunkGroupID with the given value.
     *
     * @param value - the value of the AVP
     */
    public IncomingTrunkGroupID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    IncomingTrunkGroupID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
