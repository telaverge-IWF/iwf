package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class ActiveAPN extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ActiveAPN.
     */
    public ActiveAPN() {}

    ActiveAPN(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ContextIdentifier.
     */
    public ContextIdentifier getContextIdentifier() throws NoSuchAttributeException {
        return (ContextIdentifier)_data.getContainer().get(S6a_r11AttributeName.ContextIdentifier, 0);
    }

    /**
     * Sets the ContextIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setContextIdentifier(ContextIdentifier avp) {
        _data.getContainer().add(S6a_r11AttributeName.ContextIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceSelection.
     */
    public boolean containsServiceSelection() {
        return _data.getContainer().contains(S6a_r11AttributeName.ServiceSelection);
    }

    /**
     * Gets the ServiceSelection.
     */
    public ServiceSelection getServiceSelection() throws NoSuchAttributeException {
        return (ServiceSelection)_data.getContainer().get(S6a_r11AttributeName.ServiceSelection, 0);
    }

    /**
     * Sets the ServiceSelection.
     *
     * @param avp - the attribute value
     */
    public void setServiceSelection(ServiceSelection avp) {
        _data.getContainer().add(S6a_r11AttributeName.ServiceSelection, avp.getData(), true);
    }

    /**
     * Tests whether there is any MIP6AgentInfo.
     */
    public boolean containsMIP6AgentInfo() {
        return _data.getContainer().contains(S6a_r11AttributeName.MIP6AgentInfo);
    }

    /**
     * Gets the MIP6AgentInfo.
     */
    public MIP6AgentInfo getMIP6AgentInfo() throws NoSuchAttributeException {
        return (MIP6AgentInfo)_data.getContainer().get(S6a_r11AttributeName.MIP6AgentInfo, 0);
    }

    /**
     * Sets the MIP6AgentInfo.
     *
     * @param avp - the attribute value
     */
    public void setMIP6AgentInfo(MIP6AgentInfo avp) {
        _data.getContainer().add(S6a_r11AttributeName.MIP6AgentInfo, avp.getData(), true);
    }

    /**
     * Tests whether there is any VisitedNetworkIdentifier.
     */
    public boolean containsVisitedNetworkIdentifier() {
        return _data.getContainer().contains(S6a_r11AttributeName.VisitedNetworkIdentifier);
    }

    /**
     * Gets the VisitedNetworkIdentifier.
     */
    public VisitedNetworkIdentifier getVisitedNetworkIdentifier() throws NoSuchAttributeException {
        return (VisitedNetworkIdentifier)_data.getContainer().get(S6a_r11AttributeName.VisitedNetworkIdentifier, 0);
    }

    /**
     * Sets the VisitedNetworkIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setVisitedNetworkIdentifier(VisitedNetworkIdentifier avp) {
        _data.getContainer().add(S6a_r11AttributeName.VisitedNetworkIdentifier, avp.getData(), true);
    }

    /**
     * Returns number of SpecificAPNInfo instances.
     */
    public int countSpecificAPNInfo() {
        return _data.getContainer().count(S6a_r11AttributeName.SpecificAPNInfo);
    }

    /**
     * Gets one SpecificAPNInfo.
     *
     * @param index - the index of the attribute to return
     */
    public SpecificAPNInfo getSpecificAPNInfo(int index) throws NoSuchAttributeException {
        return (SpecificAPNInfo)_data.getContainer().get(S6a_r11AttributeName.SpecificAPNInfo, index);
    }

    /**
     * Adds one SpecificAPNInfo.
     *
     * @param avp - the attribute value
     */
    public void addSpecificAPNInfo(SpecificAPNInfo avp) {
        _data.getContainer().add(S6a_r11AttributeName.SpecificAPNInfo, avp.getData(), false);
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
        sb.append("    ContextIdentifier:");
            try {
                sb.append(getContextIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsServiceSelection()) {
            sb.append("    ServiceSelection:");
            try {
                sb.append(getServiceSelection()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMIP6AgentInfo()) {
            sb.append("    MIP6AgentInfo:");
            try {
                sb.append(getMIP6AgentInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsVisitedNetworkIdentifier()) {
            sb.append("    VisitedNetworkIdentifier:");
            try {
                sb.append(getVisitedNetworkIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSpecificAPNInfo(); ++i) {
            sb.append("    SpecificAPNInfo:");
            try {
                sb.append(getSpecificAPNInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
