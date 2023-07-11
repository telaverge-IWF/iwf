package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Priority-Level AVP (AVP code 1046) is of type Unsigned 32. The AVP is used for
 * deciding whether a bearer establishment or modification request can be accepted or needs
 * to be rejected in case of resource limitations (typically used for admission control
 * of GBR traffic). The AVP can also be used to decide which existing bearers to pre-empt
 * during resource limitations. The priority level defines the relative importance of a resource request.
 */
public class PriorityLevel extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PriorityLevel with the given value.
     *
     * @param value - the value of the AVP
     */
    public PriorityLevel(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PriorityLevel(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
