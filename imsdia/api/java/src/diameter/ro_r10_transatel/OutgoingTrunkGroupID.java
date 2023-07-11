package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Outgoing-Trunk-Group-ID AVP is of type UTF8String and identifies the outgoing PSTN leg.
 */
public class OutgoingTrunkGroupID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a OutgoingTrunkGroupID with the given value.
     *
     * @param value - the value of the AVP
     */
    public OutgoingTrunkGroupID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    OutgoingTrunkGroupID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
