package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * LCS-Information AVP is of type Grouped.Its purpose is to allow the transmission of additional 
 * LCS service specific information elements.
 */
public class LCSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LCSInformation.
     */
    public LCSInformation() {}

    LCSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any LCSClientID.
     */
    public boolean containsLCSClientID() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSClientID);
    }

    /**
     * Gets the LCSClientID.
     */
    public LCSClientID getLCSClientID() throws NoSuchAttributeException {
        return (LCSClientID)_data.getContainer().get(Ro_r10AttributeName.LCSClientID, 0);
    }

    /**
     * Sets the LCSClientID.
     *
     * @param avp - the attribute value
     */
    public void setLCSClientID(LCSClientID avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSClientID, avp.getData(), true);
    }

    /**
     * Tests whether there is any LocationType.
     */
    public boolean containsLocationType() {
        return _data.getContainer().contains(Ro_r10AttributeName.LocationType);
    }

    /**
     * Gets the LocationType.
     */
    public LocationType getLocationType() throws NoSuchAttributeException {
        return (LocationType)_data.getContainer().get(Ro_r10AttributeName.LocationType, 0);
    }

    /**
     * Sets the LocationType.
     *
     * @param avp - the attribute value
     */
    public void setLocationType(LocationType avp) {
        _data.getContainer().add(Ro_r10AttributeName.LocationType, avp.getData(), true);
    }

    /**
     * Tests whether there is any LocationEstimate.
     */
    public boolean containsLocationEstimate() {
        return _data.getContainer().contains(Ro_r10AttributeName.LocationEstimate);
    }

    /**
     * Gets the LocationEstimate.
     */
    public LocationEstimate getLocationEstimate() throws NoSuchAttributeException {
        return (LocationEstimate)_data.getContainer().get(Ro_r10AttributeName.LocationEstimate, 0);
    }

    /**
     * Sets the LocationEstimate.
     *
     * @param avp - the attribute value
     */
    public void setLocationEstimate(LocationEstimate avp) {
        _data.getContainer().add(Ro_r10AttributeName.LocationEstimate, avp.getData(), true);
    }

    /**
     * Tests whether there is any PositioningData.
     */
    public boolean containsPositioningData() {
        return _data.getContainer().contains(Ro_r10AttributeName.PositioningData);
    }

    /**
     * Gets the PositioningData.
     */
    public PositioningData getPositioningData() throws NoSuchAttributeException {
        return (PositioningData)_data.getContainer().get(Ro_r10AttributeName.PositioningData, 0);
    }

    /**
     * Sets the PositioningData.
     *
     * @param avp - the attribute value
     */
    public void setPositioningData(PositioningData avp) {
        _data.getContainer().add(Ro_r10AttributeName.PositioningData, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPIMSI.
     */
    public boolean containsRo3GPPIMSI() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPIMSI);
    }

    /**
     * Gets the Ro3GPPIMSI.
     */
    public Ro3GPPIMSI getRo3GPPIMSI() throws NoSuchAttributeException {
        return (Ro3GPPIMSI)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPIMSI, 0);
    }

    /**
     * Sets the Ro3GPPIMSI.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPIMSI(Ro3GPPIMSI avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPIMSI, avp.getData(), true);
    }

    /**
     * Tests whether there is any MSISDN.
     */
    public boolean containsMSISDN() {
        return _data.getContainer().contains(Ro_r10AttributeName.MSISDN);
    }

    /**
     * Gets the MSISDN.
     */
    public MSISDN getMSISDN() throws NoSuchAttributeException {
        return (MSISDN)_data.getContainer().get(Ro_r10AttributeName.MSISDN, 0);
    }

    /**
     * Sets the MSISDN.
     *
     * @param avp - the attribute value
     */
    public void setMSISDN(MSISDN avp) {
        _data.getContainer().add(Ro_r10AttributeName.MSISDN, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsLCSClientID()) {
            sb.append("    LCSClientID:");
            try {
                sb.append(getLCSClientID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLocationType()) {
            sb.append("    LocationType:");
            try {
                sb.append(getLocationType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLocationEstimate()) {
            sb.append("    LocationEstimate:");
            try {
                sb.append(getLocationEstimate()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPositioningData()) {
            sb.append("    PositioningData:");
            try {
                sb.append(getPositioningData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPIMSI()) {
            sb.append("    Ro3GPPIMSI:");
            try {
                sb.append(getRo3GPPIMSI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMSISDN()) {
            sb.append("    MSISDN:");
            try {
                sb.append(getMSISDN()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
