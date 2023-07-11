package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * 3GPP_Selection-Mode AVP is of type UTF8String. It contains the selection mode for this
 * PDP context received in the create PDP context request message.
 */
public class Ro3GPPSelectionMode extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPSelectionMode with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPSelectionMode(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPSelectionMode(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
