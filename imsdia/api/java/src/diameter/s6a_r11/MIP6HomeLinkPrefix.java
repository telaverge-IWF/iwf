package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class MIP6HomeLinkPrefix extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a MIP6HomeLinkPrefix with the given value.
     *
     * @param value - the value of the AVP
     */
    public MIP6HomeLinkPrefix(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    MIP6HomeLinkPrefix(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
