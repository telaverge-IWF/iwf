package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * PS-Furnish-Charging-Information AVP is of type Grouped. Its purpose is to add online charging session
 * specific information, received via the Ro Reference point onto the Rf reference point in order to 
 * facilitate its inclusion in CDRs.This information element may be received in CCA message via the Ro
 * reference point. In situations where online and offline charging are active in parallel, the information
 * element is transparently copied into ACR to be sent on the Rf reference point.
 */
public class PSFurnishChargingInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new PSFurnishChargingInformation.
     */
    public PSFurnishChargingInformation() {}

    PSFurnishChargingInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the Ro3GPPChargingId.
     */
    public Ro3GPPChargingId getRo3GPPChargingId() throws NoSuchAttributeException {
        return (Ro3GPPChargingId)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPChargingId, 0);
    }

    /**
     * Sets the Ro3GPPChargingId.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPChargingId(Ro3GPPChargingId avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPChargingId, avp.getData(), true);
    }

    /**
     * Gets the PSFreeFormatData.
     */
    public PSFreeFormatData getPSFreeFormatData() throws NoSuchAttributeException {
        return (PSFreeFormatData)_data.getContainer().get(Ro_r10AttributeName.PSFreeFormatData, 0);
    }

    /**
     * Sets the PSFreeFormatData.
     *
     * @param avp - the attribute value
     */
    public void setPSFreeFormatData(PSFreeFormatData avp) {
        _data.getContainer().add(Ro_r10AttributeName.PSFreeFormatData, avp.getData(), true);
    }

    /**
     * Tests whether there is any PSAppendFreeFormatData.
     */
    public boolean containsPSAppendFreeFormatData() {
        return _data.getContainer().contains(Ro_r10AttributeName.PSAppendFreeFormatData);
    }

    /**
     * Gets the PSAppendFreeFormatData.
     */
    public PSAppendFreeFormatData getPSAppendFreeFormatData() throws NoSuchAttributeException {
        return (PSAppendFreeFormatData)_data.getContainer().get(Ro_r10AttributeName.PSAppendFreeFormatData, 0);
    }

    /**
     * Sets the PSAppendFreeFormatData.
     *
     * @param avp - the attribute value
     */
    public void setPSAppendFreeFormatData(PSAppendFreeFormatData avp) {
        _data.getContainer().add(Ro_r10AttributeName.PSAppendFreeFormatData, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    Ro3GPPChargingId:");
            try {
                sb.append(getRo3GPPChargingId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    PSFreeFormatData:");
            try {
                sb.append(getPSFreeFormatData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsPSAppendFreeFormatData()) {
            sb.append("    PSAppendFreeFormatData:");
            try {
                sb.append(getPSAppendFreeFormatData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
