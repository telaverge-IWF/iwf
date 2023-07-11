package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The Real-Time-Tariff-Information AVP (AVP code 2305) is of type Grouped and holds
* the tariff information received in real time according to TS 29.658 [222] in the SIP signalling.
*/
public class RealTimeTariffInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RealTimeTariffInformation.
     */
    public RealTimeTariffInformation() {}

    RealTimeTariffInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any TariffInformation.
     */
    public boolean containsTariffInformation() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TariffInformation);
    }

    /**
     * Gets the TariffInformation.
     */
    public TariffInformation getTariffInformation() throws NoSuchAttributeException {
        return (TariffInformation)_data.getContainer().get(Ro_r10_transatelAttributeName.TariffInformation, 0);
    }

    /**
     * Sets the TariffInformation.
     *
     * @param avp - the attribute value
     */
    public void setTariffInformation(TariffInformation avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TariffInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any TariffXML.
     */
    public boolean containsTariffXML() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TariffXML);
    }

    /**
     * Gets the TariffXML.
     */
    public TariffXML getTariffXML() throws NoSuchAttributeException {
        return (TariffXML)_data.getContainer().get(Ro_r10_transatelAttributeName.TariffXML, 0);
    }

    /**
     * Sets the TariffXML.
     *
     * @param avp - the attribute value
     */
    public void setTariffXML(TariffXML avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TariffXML, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsTariffInformation()) {
            sb.append("    TariffInformation:");
            try {
                sb.append(getTariffInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTariffXML()) {
            sb.append("    TariffXML:");
            try {
                sb.append(getTariffXML()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
