package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class SpecificAPNInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SpecificAPNInfo.
     */
    public SpecificAPNInfo() {}

    SpecificAPNInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ServiceSelection.
     */
    public ServiceSelection getServiceSelection() throws NoSuchAttributeException {
        return (ServiceSelection)_data.getContainer().get(S6a_r10AttributeName.ServiceSelection, 0);
    }

    /**
     * Sets the ServiceSelection.
     *
     * @param avp - the attribute value
     */
    public void setServiceSelection(ServiceSelection avp) {
        _data.getContainer().add(S6a_r10AttributeName.ServiceSelection, avp.getData(), true);
    }

    /**
     * Gets the MIP6AgentInfo.
     */
    public MIP6AgentInfo getMIP6AgentInfo() throws NoSuchAttributeException {
        return (MIP6AgentInfo)_data.getContainer().get(S6a_r10AttributeName.MIP6AgentInfo, 0);
    }

    /**
     * Sets the MIP6AgentInfo.
     *
     * @param avp - the attribute value
     */
    public void setMIP6AgentInfo(MIP6AgentInfo avp) {
        _data.getContainer().add(S6a_r10AttributeName.MIP6AgentInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any VisitedNetworkIdentifier.
     */
    public boolean containsVisitedNetworkIdentifier() {
        return _data.getContainer().contains(S6a_r10AttributeName.VisitedNetworkIdentifier);
    }

    /**
     * Gets the VisitedNetworkIdentifier.
     */
    public VisitedNetworkIdentifier getVisitedNetworkIdentifier() throws NoSuchAttributeException {
        return (VisitedNetworkIdentifier)_data.getContainer().get(S6a_r10AttributeName.VisitedNetworkIdentifier, 0);
    }

    /**
     * Sets the VisitedNetworkIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setVisitedNetworkIdentifier(VisitedNetworkIdentifier avp) {
        _data.getContainer().add(S6a_r10AttributeName.VisitedNetworkIdentifier, avp.getData(), true);
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
        sb.append("    ServiceSelection:");
            try {
                sb.append(getServiceSelection()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    MIP6AgentInfo:");
            try {
                sb.append(getMIP6AgentInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsVisitedNetworkIdentifier()) {
            sb.append("    VisitedNetworkIdentifier:");
            try {
                sb.append(getVisitedNetworkIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
