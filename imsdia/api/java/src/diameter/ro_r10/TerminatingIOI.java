package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Terminating-IOI AVP is of type UTF8String and holds the Inter operator Identifier (IOI)
 * for the terminating network as generated by the IMS network element which takes 
 * responsibility for populating this parameter in a SIP response.
 */
public class TerminatingIOI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TerminatingIOI with the given value.
     *
     * @param value - the value of the AVP
     */
    public TerminatingIOI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    TerminatingIOI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
