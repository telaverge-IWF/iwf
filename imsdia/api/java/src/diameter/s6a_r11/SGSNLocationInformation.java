package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class SGSNLocationInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SGSNLocationInformation.
     */
    public SGSNLocationInformation() {}

    SGSNLocationInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CellGlobalIdentity.
     */
    public boolean containsCellGlobalIdentity() {
        return _data.getContainer().contains(S6a_r11AttributeName.CellGlobalIdentity);
    }

    /**
     * Gets the CellGlobalIdentity.
     */
    public CellGlobalIdentity getCellGlobalIdentity() throws NoSuchAttributeException {
        return (CellGlobalIdentity)_data.getContainer().get(S6a_r11AttributeName.CellGlobalIdentity, 0);
    }

    /**
     * Sets the CellGlobalIdentity.
     *
     * @param avp - the attribute value
     */
    public void setCellGlobalIdentity(CellGlobalIdentity avp) {
        _data.getContainer().add(S6a_r11AttributeName.CellGlobalIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any LocationAreaIdentity.
     */
    public boolean containsLocationAreaIdentity() {
        return _data.getContainer().contains(S6a_r11AttributeName.LocationAreaIdentity);
    }

    /**
     * Gets the LocationAreaIdentity.
     */
    public LocationAreaIdentity getLocationAreaIdentity() throws NoSuchAttributeException {
        return (LocationAreaIdentity)_data.getContainer().get(S6a_r11AttributeName.LocationAreaIdentity, 0);
    }

    /**
     * Sets the LocationAreaIdentity.
     *
     * @param avp - the attribute value
     */
    public void setLocationAreaIdentity(LocationAreaIdentity avp) {
        _data.getContainer().add(S6a_r11AttributeName.LocationAreaIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceAreaIdentity.
     */
    public boolean containsServiceAreaIdentity() {
        return _data.getContainer().contains(S6a_r11AttributeName.ServiceAreaIdentity);
    }

    /**
     * Gets the ServiceAreaIdentity.
     */
    public ServiceAreaIdentity getServiceAreaIdentity() throws NoSuchAttributeException {
        return (ServiceAreaIdentity)_data.getContainer().get(S6a_r11AttributeName.ServiceAreaIdentity, 0);
    }

    /**
     * Sets the ServiceAreaIdentity.
     *
     * @param avp - the attribute value
     */
    public void setServiceAreaIdentity(ServiceAreaIdentity avp) {
        _data.getContainer().add(S6a_r11AttributeName.ServiceAreaIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any RoutingAreaIdentity.
     */
    public boolean containsRoutingAreaIdentity() {
        return _data.getContainer().contains(S6a_r11AttributeName.RoutingAreaIdentity);
    }

    /**
     * Gets the RoutingAreaIdentity.
     */
    public RoutingAreaIdentity getRoutingAreaIdentity() throws NoSuchAttributeException {
        return (RoutingAreaIdentity)_data.getContainer().get(S6a_r11AttributeName.RoutingAreaIdentity, 0);
    }

    /**
     * Sets the RoutingAreaIdentity.
     *
     * @param avp - the attribute value
     */
    public void setRoutingAreaIdentity(RoutingAreaIdentity avp) {
        _data.getContainer().add(S6a_r11AttributeName.RoutingAreaIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any GeographicalInformation.
     */
    public boolean containsGeographicalInformation() {
        return _data.getContainer().contains(S6a_r11AttributeName.GeographicalInformation);
    }

    /**
     * Gets the GeographicalInformation.
     */
    public GeographicalInformation getGeographicalInformation() throws NoSuchAttributeException {
        return (GeographicalInformation)_data.getContainer().get(S6a_r11AttributeName.GeographicalInformation, 0);
    }

    /**
     * Sets the GeographicalInformation.
     *
     * @param avp - the attribute value
     */
    public void setGeographicalInformation(GeographicalInformation avp) {
        _data.getContainer().add(S6a_r11AttributeName.GeographicalInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any GeodeticInformation.
     */
    public boolean containsGeodeticInformation() {
        return _data.getContainer().contains(S6a_r11AttributeName.GeodeticInformation);
    }

    /**
     * Gets the GeodeticInformation.
     */
    public GeodeticInformation getGeodeticInformation() throws NoSuchAttributeException {
        return (GeodeticInformation)_data.getContainer().get(S6a_r11AttributeName.GeodeticInformation, 0);
    }

    /**
     * Sets the GeodeticInformation.
     *
     * @param avp - the attribute value
     */
    public void setGeodeticInformation(GeodeticInformation avp) {
        _data.getContainer().add(S6a_r11AttributeName.GeodeticInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CurrentLocationRetrieved.
     */
    public boolean containsCurrentLocationRetrieved() {
        return _data.getContainer().contains(S6a_r11AttributeName.CurrentLocationRetrieved);
    }

    /**
     * Gets the CurrentLocationRetrieved.
     */
    public CurrentLocationRetrieved getCurrentLocationRetrieved() throws NoSuchAttributeException {
        return (CurrentLocationRetrieved)_data.getContainer().get(S6a_r11AttributeName.CurrentLocationRetrieved, 0);
    }

    /**
     * Sets the CurrentLocationRetrieved.
     *
     * @param avp - the attribute value
     */
    public void setCurrentLocationRetrieved(CurrentLocationRetrieved avp) {
        _data.getContainer().add(S6a_r11AttributeName.CurrentLocationRetrieved, avp.getData(), true);
    }

    /**
     * Tests whether there is any AgeOfLocationInformation.
     */
    public boolean containsAgeOfLocationInformation() {
        return _data.getContainer().contains(S6a_r11AttributeName.AgeOfLocationInformation);
    }

    /**
     * Gets the AgeOfLocationInformation.
     */
    public AgeOfLocationInformation getAgeOfLocationInformation() throws NoSuchAttributeException {
        return (AgeOfLocationInformation)_data.getContainer().get(S6a_r11AttributeName.AgeOfLocationInformation, 0);
    }

    /**
     * Sets the AgeOfLocationInformation.
     *
     * @param avp - the attribute value
     */
    public void setAgeOfLocationInformation(AgeOfLocationInformation avp) {
        _data.getContainer().add(S6a_r11AttributeName.AgeOfLocationInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any UserCSGInformation.
     */
    public boolean containsUserCSGInformation() {
        return _data.getContainer().contains(S6a_r11AttributeName.UserCSGInformation);
    }

    /**
     * Gets the UserCSGInformation.
     */
    public UserCSGInformation getUserCSGInformation() throws NoSuchAttributeException {
        return (UserCSGInformation)_data.getContainer().get(S6a_r11AttributeName.UserCSGInformation, 0);
    }

    /**
     * Sets the UserCSGInformation.
     *
     * @param avp - the attribute value
     */
    public void setUserCSGInformation(UserCSGInformation avp) {
        _data.getContainer().add(S6a_r11AttributeName.UserCSGInformation, avp.getData(), true);
    }

    /**
     * Returns number of extra AVP instances.
     */
    public int countExtra() {
        return _data.getContainer().count(AttributeName.AVP);
    }

    /**
     * Returns number of extra AVP instances that match the given attribute name.
     *
     * @param name - the attribute to count
     */
    public int countExtra(AttributeName name) {
        return _data.getContainer().countExtra(name);
    }

    /**
     * Gets an extra AVP that matches the given attribute name.
     *
     * @param name - the attribute to return
     * @param index - the index of the attribute to return
     */
    public AVP getExtra(AttributeName name, int index) throws NoSuchAttributeException {
        return _data.getContainer().getExtra(name, index);
    }

    /**
     * Adds one extra AVP.
     *
     * @param avp - the attribute value
     */
    public void addExtra(AVP avp) {
        _data.getContainer().add(AttributeName.AVP, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCellGlobalIdentity()) {
            sb.append("    CellGlobalIdentity:");
            try {
                sb.append(getCellGlobalIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLocationAreaIdentity()) {
            sb.append("    LocationAreaIdentity:");
            try {
                sb.append(getLocationAreaIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceAreaIdentity()) {
            sb.append("    ServiceAreaIdentity:");
            try {
                sb.append(getServiceAreaIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRoutingAreaIdentity()) {
            sb.append("    RoutingAreaIdentity:");
            try {
                sb.append(getRoutingAreaIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGeographicalInformation()) {
            sb.append("    GeographicalInformation:");
            try {
                sb.append(getGeographicalInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGeodeticInformation()) {
            sb.append("    GeodeticInformation:");
            try {
                sb.append(getGeodeticInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCurrentLocationRetrieved()) {
            sb.append("    CurrentLocationRetrieved:");
            try {
                sb.append(getCurrentLocationRetrieved()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAgeOfLocationInformation()) {
            sb.append("    AgeOfLocationInformation:");
            try {
                sb.append(getAgeOfLocationInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserCSGInformation()) {
            sb.append("    UserCSGInformation:");
            try {
                sb.append(getUserCSGInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
