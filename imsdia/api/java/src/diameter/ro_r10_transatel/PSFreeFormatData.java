package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * PS-Free-Format-Data AVP is of type OctetString and holds online charging session specific data.
 */
public class PSFreeFormatData extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a PSFreeFormatData with the given value.
     *
     * @param value - the value of the AVP
     */
    public PSFreeFormatData(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    PSFreeFormatData(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
