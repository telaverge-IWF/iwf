package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Positioning-Data AVP is of type UTF8String and indicates the usage of each positioning method
 * that was attempted to determine the location estimate either successfully or unsuccessfully.
 */
public class PositioningData extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a PositioningData with the given value.
     *
     * @param value - the value of the AVP
     */
    public PositioningData(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    PositioningData(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
