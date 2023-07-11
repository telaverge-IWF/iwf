package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * RAIdentity AVP is of type UTF8String and contains the Routing Area Identity of the SGSN where the UE
 * is registered. RAI use and structure is specified in 3GPP TS 23.003.
 */
public class RAI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RAI with the given value.
     *
     * @param value - the value of the AVP
     */
    public RAI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    RAI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
