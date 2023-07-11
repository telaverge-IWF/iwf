package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AF-Correlation-Information AVP (AVPcode 1276) is of type Grouped 
 * and includes the "AF Charging Identifier" (ICID for IMS)  and associate
 * flow identifiers generated by the AF and received by GGSN over Rx/Gx 
 * as defined in TS 29.214 [214] and TS 29.212 [215]. The AF-Correlation-
 * Information is defined per Rating Group or per Rating Group and 
 * Service Identifier when Service Identifier level reporting applies.
 */
public class AFCorrelationInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AFCorrelationInformation.
     */
    public AFCorrelationInformation() {}

    AFCorrelationInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the AFChargingIdentifier.
     */
    public AFChargingIdentifier getAFChargingIdentifier() throws NoSuchAttributeException {
        return (AFChargingIdentifier)_data.getContainer().get(Ro_r10AttributeName.AFChargingIdentifier, 0);
    }

    /**
     * Sets the AFChargingIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setAFChargingIdentifier(AFChargingIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.AFChargingIdentifier, avp.getData(), true);
    }

    /**
     * Returns number of Flows instances.
     */
    public int countFlows() {
        return _data.getContainer().count(Ro_r10AttributeName.Flows);
    }

    /**
     * Gets one Flows.
     *
     * @param index - the index of the attribute to return
     */
    public Flows getFlows(int index) throws NoSuchAttributeException {
        return (Flows)_data.getContainer().get(Ro_r10AttributeName.Flows, index);
    }

    /**
     * Adds one Flows.
     *
     * @param avp - the attribute value
     */
    public void addFlows(Flows avp) {
        _data.getContainer().add(Ro_r10AttributeName.Flows, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    AFChargingIdentifier:");
            try {
                sb.append(getAFChargingIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        for (int i = 0; i < countFlows(); ++i) {
            sb.append("    Flows:");
            try {
                sb.append(getFlows(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
