package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * WLAN-Radio-Container AVP is of type Grouped. 
 */
public class WLANRadioContainer extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new WLANRadioContainer.
     */
    public WLANRadioContainer() {}

    WLANRadioContainer(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any OperatorName.
     */
    public boolean containsOperatorName() {
        return _data.getContainer().contains(Ro_r10AttributeName.OperatorName);
    }

    /**
     * Gets the OperatorName.
     */
    public OperatorName getOperatorName() throws NoSuchAttributeException {
        return (OperatorName)_data.getContainer().get(Ro_r10AttributeName.OperatorName, 0);
    }

    /**
     * Sets the OperatorName.
     *
     * @param avp - the attribute value
     */
    public void setOperatorName(OperatorName avp) {
        _data.getContainer().add(Ro_r10AttributeName.OperatorName, avp.getData(), true);
    }

    /**
     * Tests whether there is any LocationInformation.
     */
    public boolean containsLocationInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.LocationInformation);
    }

    /**
     * Gets the LocationInformation.
     */
    public LocationInformation getLocationInformation() throws NoSuchAttributeException {
        return (LocationInformation)_data.getContainer().get(Ro_r10AttributeName.LocationInformation, 0);
    }

    /**
     * Sets the LocationInformation.
     *
     * @param avp - the attribute value
     */
    public void setLocationInformation(LocationInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.LocationInformation, avp.getData(), true);
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
     * Tests whether there is any WLANTechnology.
     */
    public boolean containsWLANTechnology() {
        return _data.getContainer().contains(Ro_r10AttributeName.WLANTechnology);
    }

    /**
     * Gets the WLANTechnology.
     */
    public WLANTechnology getWLANTechnology() throws NoSuchAttributeException {
        return (WLANTechnology)_data.getContainer().get(Ro_r10AttributeName.WLANTechnology, 0);
    }

    /**
     * Sets the WLANTechnology.
     *
     * @param avp - the attribute value
     */
    public void setWLANTechnology(WLANTechnology avp) {
        _data.getContainer().add(Ro_r10AttributeName.WLANTechnology, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsOperatorName()) {
            sb.append("    OperatorName:");
            try {
                sb.append(getOperatorName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLocationInformation()) {
            sb.append("    LocationInformation:");
            try {
                sb.append(getLocationInformation()).append('\n');
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
        if (containsWLANTechnology()) {
            sb.append("    WLANTechnology:");
            try {
                sb.append(getWLANTechnology()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
