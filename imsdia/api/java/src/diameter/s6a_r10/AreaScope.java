package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class AreaScope extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AreaScope.
     */
    public AreaScope() {}

    AreaScope(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of CellGlobalIdentity instances.
     */
    public int countCellGlobalIdentity() {
        return _data.getContainer().count(S6a_r10AttributeName.CellGlobalIdentity);
    }

    /**
     * Gets one CellGlobalIdentity.
     *
     * @param index - the index of the attribute to return
     */
    public CellGlobalIdentity getCellGlobalIdentity(int index) throws NoSuchAttributeException {
        return (CellGlobalIdentity)_data.getContainer().get(S6a_r10AttributeName.CellGlobalIdentity, index);
    }

    /**
     * Adds one CellGlobalIdentity.
     *
     * @param avp - the attribute value
     */
    public void addCellGlobalIdentity(CellGlobalIdentity avp) {
        _data.getContainer().add(S6a_r10AttributeName.CellGlobalIdentity, avp.getData(), false);
    }

    /**
     * Returns number of EUTRANCellGlobalIdentity instances.
     */
    public int countEUTRANCellGlobalIdentity() {
        return _data.getContainer().count(S6a_r10AttributeName.EUTRANCellGlobalIdentity);
    }

    /**
     * Gets one EUTRANCellGlobalIdentity.
     *
     * @param index - the index of the attribute to return
     */
    public EUTRANCellGlobalIdentity getEUTRANCellGlobalIdentity(int index) throws NoSuchAttributeException {
        return (EUTRANCellGlobalIdentity)_data.getContainer().get(S6a_r10AttributeName.EUTRANCellGlobalIdentity, index);
    }

    /**
     * Adds one EUTRANCellGlobalIdentity.
     *
     * @param avp - the attribute value
     */
    public void addEUTRANCellGlobalIdentity(EUTRANCellGlobalIdentity avp) {
        _data.getContainer().add(S6a_r10AttributeName.EUTRANCellGlobalIdentity, avp.getData(), false);
    }

    /**
     * Returns number of RoutingAreaIdentity instances.
     */
    public int countRoutingAreaIdentity() {
        return _data.getContainer().count(S6a_r10AttributeName.RoutingAreaIdentity);
    }

    /**
     * Gets one RoutingAreaIdentity.
     *
     * @param index - the index of the attribute to return
     */
    public RoutingAreaIdentity getRoutingAreaIdentity(int index) throws NoSuchAttributeException {
        return (RoutingAreaIdentity)_data.getContainer().get(S6a_r10AttributeName.RoutingAreaIdentity, index);
    }

    /**
     * Adds one RoutingAreaIdentity.
     *
     * @param avp - the attribute value
     */
    public void addRoutingAreaIdentity(RoutingAreaIdentity avp) {
        _data.getContainer().add(S6a_r10AttributeName.RoutingAreaIdentity, avp.getData(), false);
    }

    /**
     * Returns number of LocationAreaIdentity instances.
     */
    public int countLocationAreaIdentity() {
        return _data.getContainer().count(S6a_r10AttributeName.LocationAreaIdentity);
    }

    /**
     * Gets one LocationAreaIdentity.
     *
     * @param index - the index of the attribute to return
     */
    public LocationAreaIdentity getLocationAreaIdentity(int index) throws NoSuchAttributeException {
        return (LocationAreaIdentity)_data.getContainer().get(S6a_r10AttributeName.LocationAreaIdentity, index);
    }

    /**
     * Adds one LocationAreaIdentity.
     *
     * @param avp - the attribute value
     */
    public void addLocationAreaIdentity(LocationAreaIdentity avp) {
        _data.getContainer().add(S6a_r10AttributeName.LocationAreaIdentity, avp.getData(), false);
    }

    /**
     * Returns number of TrackingAreaIdentity instances.
     */
    public int countTrackingAreaIdentity() {
        return _data.getContainer().count(S6a_r10AttributeName.TrackingAreaIdentity);
    }

    /**
     * Gets one TrackingAreaIdentity.
     *
     * @param index - the index of the attribute to return
     */
    public TrackingAreaIdentity getTrackingAreaIdentity(int index) throws NoSuchAttributeException {
        return (TrackingAreaIdentity)_data.getContainer().get(S6a_r10AttributeName.TrackingAreaIdentity, index);
    }

    /**
     * Adds one TrackingAreaIdentity.
     *
     * @param avp - the attribute value
     */
    public void addTrackingAreaIdentity(TrackingAreaIdentity avp) {
        _data.getContainer().add(S6a_r10AttributeName.TrackingAreaIdentity, avp.getData(), false);
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
        for (int i = 0; i < countCellGlobalIdentity(); ++i) {
            sb.append("    CellGlobalIdentity:");
            try {
                sb.append(getCellGlobalIdentity(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countEUTRANCellGlobalIdentity(); ++i) {
            sb.append("    EUTRANCellGlobalIdentity:");
            try {
                sb.append(getEUTRANCellGlobalIdentity(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRoutingAreaIdentity(); ++i) {
            sb.append("    RoutingAreaIdentity:");
            try {
                sb.append(getRoutingAreaIdentity(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countLocationAreaIdentity(); ++i) {
            sb.append("    LocationAreaIdentity:");
            try {
                sb.append(getLocationAreaIdentity(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countTrackingAreaIdentity(); ++i) {
            sb.append("    TrackingAreaIdentity:");
            try {
                sb.append(getTrackingAreaIdentity(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
