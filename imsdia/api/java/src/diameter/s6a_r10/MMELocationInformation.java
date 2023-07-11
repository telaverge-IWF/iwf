package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class MMELocationInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MMELocationInformation.
     */
    public MMELocationInformation() {}

    MMELocationInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any EUTRANCellGlobalIdentity.
     */
    public boolean containsEUTRANCellGlobalIdentity() {
        return _data.getContainer().contains(S6a_r10AttributeName.EUTRANCellGlobalIdentity);
    }

    /**
     * Gets the EUTRANCellGlobalIdentity.
     */
    public EUTRANCellGlobalIdentity getEUTRANCellGlobalIdentity() throws NoSuchAttributeException {
        return (EUTRANCellGlobalIdentity)_data.getContainer().get(S6a_r10AttributeName.EUTRANCellGlobalIdentity, 0);
    }

    /**
     * Sets the EUTRANCellGlobalIdentity.
     *
     * @param avp - the attribute value
     */
    public void setEUTRANCellGlobalIdentity(EUTRANCellGlobalIdentity avp) {
        _data.getContainer().add(S6a_r10AttributeName.EUTRANCellGlobalIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any TrackingAreaIdentity.
     */
    public boolean containsTrackingAreaIdentity() {
        return _data.getContainer().contains(S6a_r10AttributeName.TrackingAreaIdentity);
    }

    /**
     * Gets the TrackingAreaIdentity.
     */
    public TrackingAreaIdentity getTrackingAreaIdentity() throws NoSuchAttributeException {
        return (TrackingAreaIdentity)_data.getContainer().get(S6a_r10AttributeName.TrackingAreaIdentity, 0);
    }

    /**
     * Sets the TrackingAreaIdentity.
     *
     * @param avp - the attribute value
     */
    public void setTrackingAreaIdentity(TrackingAreaIdentity avp) {
        _data.getContainer().add(S6a_r10AttributeName.TrackingAreaIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any GeographicalInformation.
     */
    public boolean containsGeographicalInformation() {
        return _data.getContainer().contains(S6a_r10AttributeName.GeographicalInformation);
    }

    /**
     * Gets the GeographicalInformation.
     */
    public GeographicalInformation getGeographicalInformation() throws NoSuchAttributeException {
        return (GeographicalInformation)_data.getContainer().get(S6a_r10AttributeName.GeographicalInformation, 0);
    }

    /**
     * Sets the GeographicalInformation.
     *
     * @param avp - the attribute value
     */
    public void setGeographicalInformation(GeographicalInformation avp) {
        _data.getContainer().add(S6a_r10AttributeName.GeographicalInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any GeodeticInformation.
     */
    public boolean containsGeodeticInformation() {
        return _data.getContainer().contains(S6a_r10AttributeName.GeodeticInformation);
    }

    /**
     * Gets the GeodeticInformation.
     */
    public GeodeticInformation getGeodeticInformation() throws NoSuchAttributeException {
        return (GeodeticInformation)_data.getContainer().get(S6a_r10AttributeName.GeodeticInformation, 0);
    }

    /**
     * Sets the GeodeticInformation.
     *
     * @param avp - the attribute value
     */
    public void setGeodeticInformation(GeodeticInformation avp) {
        _data.getContainer().add(S6a_r10AttributeName.GeodeticInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CurrentLocationRetrieved.
     */
    public boolean containsCurrentLocationRetrieved() {
        return _data.getContainer().contains(S6a_r10AttributeName.CurrentLocationRetrieved);
    }

    /**
     * Gets the CurrentLocationRetrieved.
     */
    public CurrentLocationRetrieved getCurrentLocationRetrieved() throws NoSuchAttributeException {
        return (CurrentLocationRetrieved)_data.getContainer().get(S6a_r10AttributeName.CurrentLocationRetrieved, 0);
    }

    /**
     * Sets the CurrentLocationRetrieved.
     *
     * @param avp - the attribute value
     */
    public void setCurrentLocationRetrieved(CurrentLocationRetrieved avp) {
        _data.getContainer().add(S6a_r10AttributeName.CurrentLocationRetrieved, avp.getData(), true);
    }

    /**
     * Tests whether there is any AgeOfLocationInformation.
     */
    public boolean containsAgeOfLocationInformation() {
        return _data.getContainer().contains(S6a_r10AttributeName.AgeOfLocationInformation);
    }

    /**
     * Gets the AgeOfLocationInformation.
     */
    public AgeOfLocationInformation getAgeOfLocationInformation() throws NoSuchAttributeException {
        return (AgeOfLocationInformation)_data.getContainer().get(S6a_r10AttributeName.AgeOfLocationInformation, 0);
    }

    /**
     * Sets the AgeOfLocationInformation.
     *
     * @param avp - the attribute value
     */
    public void setAgeOfLocationInformation(AgeOfLocationInformation avp) {
        _data.getContainer().add(S6a_r10AttributeName.AgeOfLocationInformation, avp.getData(), true);
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
        if (containsEUTRANCellGlobalIdentity()) {
            sb.append("    EUTRANCellGlobalIdentity:");
            try {
                sb.append(getEUTRANCellGlobalIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTrackingAreaIdentity()) {
            sb.append("    TrackingAreaIdentity:");
            try {
                sb.append(getTrackingAreaIdentity()).append('\n');
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
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
