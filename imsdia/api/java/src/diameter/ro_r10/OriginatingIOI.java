package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Originating-IOI AVP is of type UTF8String and holds the Inter Operator Identifier (IOI)
 * for the originating network as generated by the IMS network element which takes
 * responsibility for populating this parameter in a SIP request.
 */
public class OriginatingIOI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a OriginatingIOI with the given value.
     *
     * @param value - the value of the AVP
     */
    public OriginatingIOI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    OriginatingIOI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
