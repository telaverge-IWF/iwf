package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Location-Type AVP is of type Grouped and indicates the type of location estimate required
 *  by the LCS Client.
 */
public class LocationType extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LocationType.
     */
    public LocationType() {}

    LocationType(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any LocationEstimateType.
     */
    public boolean containsLocationEstimateType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.LocationEstimateType);
    }

    /**
     * Gets the LocationEstimateType.
     */
    public LocationEstimateType getLocationEstimateType() throws NoSuchAttributeException {
        return (LocationEstimateType)_data.getContainer().get(Ro_r10_transatelAttributeName.LocationEstimateType, 0);
    }

    /**
     * Sets the LocationEstimateType.
     *
     * @param avp - the attribute value
     */
    public void setLocationEstimateType(LocationEstimateType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.LocationEstimateType, avp.getData(), true);
    }

    /**
     * Tests whether there is any DeferredLocationEventType.
     */
    public boolean containsDeferredLocationEventType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.DeferredLocationEventType);
    }

    /**
     * Gets the DeferredLocationEventType.
     */
    public DeferredLocationEventType getDeferredLocationEventType() throws NoSuchAttributeException {
        return (DeferredLocationEventType)_data.getContainer().get(Ro_r10_transatelAttributeName.DeferredLocationEventType, 0);
    }

    /**
     * Sets the DeferredLocationEventType.
     *
     * @param avp - the attribute value
     */
    public void setDeferredLocationEventType(DeferredLocationEventType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.DeferredLocationEventType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsLocationEstimateType()) {
            sb.append("    LocationEstimateType:");
            try {
                sb.append(getLocationEstimateType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDeferredLocationEventType()) {
            sb.append("    DeferredLocationEventType:");
            try {
                sb.append(getDeferredLocationEventType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
