package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The Tariff-XML AVP (AVP code 2306) is of type UTF8String and holds the XML body describing 
* the tariff/add-on charge information exchanged during the SIP transaction, as described in the TS 29.658 [222].
*/
public class TariffXML extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TariffXML with the given value.
     *
     * @param value - the value of the AVP
     */
    public TariffXML(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    TariffXML(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
