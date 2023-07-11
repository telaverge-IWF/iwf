package diameter.s6a_r11;

import com.intellinet.diameter.*;


/** 
  * The MIP6-Agent-Info AVP (AVP code 486) is of type Grouped and
  * contains necessary information to assign an HA to the MN
  */
public class MIP6AgentInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MIP6AgentInfo.
     */
    public MIP6AgentInfo() {}

    MIP6AgentInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of MIPHomeAgentAddress instances.
     */
    public int countMIPHomeAgentAddress() {
        return _data.getContainer().count(S6a_r11AttributeName.MIPHomeAgentAddress);
    }

    /**
     * Gets one MIPHomeAgentAddress.
     *
     * @param index - the index of the attribute to return
     */
    public MIPHomeAgentAddress getMIPHomeAgentAddress(int index) throws NoSuchAttributeException {
        return (MIPHomeAgentAddress)_data.getContainer().get(S6a_r11AttributeName.MIPHomeAgentAddress, index);
    }

    /**
     * Adds one MIPHomeAgentAddress.
     *
     * @param avp - the attribute value
     */
    public void addMIPHomeAgentAddress(MIPHomeAgentAddress avp) {
        _data.getContainer().add(S6a_r11AttributeName.MIPHomeAgentAddress, avp.getData(), false);
    }

    /**
     * Tests whether there is any MIPHomeAgentHost.
     */
    public boolean containsMIPHomeAgentHost() {
        return _data.getContainer().contains(S6a_r11AttributeName.MIPHomeAgentHost);
    }

    /**
     * Gets the MIPHomeAgentHost.
     */
    public MIPHomeAgentHost getMIPHomeAgentHost() throws NoSuchAttributeException {
        return (MIPHomeAgentHost)_data.getContainer().get(S6a_r11AttributeName.MIPHomeAgentHost, 0);
    }

    /**
     * Sets the MIPHomeAgentHost.
     *
     * @param avp - the attribute value
     */
    public void setMIPHomeAgentHost(MIPHomeAgentHost avp) {
        _data.getContainer().add(S6a_r11AttributeName.MIPHomeAgentHost, avp.getData(), true);
    }

    /**
     * Tests whether there is any MIP6HomeLinkPrefix.
     */
    public boolean containsMIP6HomeLinkPrefix() {
        return _data.getContainer().contains(S6a_r11AttributeName.MIP6HomeLinkPrefix);
    }

    /**
     * Gets the MIP6HomeLinkPrefix.
     */
    public MIP6HomeLinkPrefix getMIP6HomeLinkPrefix() throws NoSuchAttributeException {
        return (MIP6HomeLinkPrefix)_data.getContainer().get(S6a_r11AttributeName.MIP6HomeLinkPrefix, 0);
    }

    /**
     * Sets the MIP6HomeLinkPrefix.
     *
     * @param avp - the attribute value
     */
    public void setMIP6HomeLinkPrefix(MIP6HomeLinkPrefix avp) {
        _data.getContainer().add(S6a_r11AttributeName.MIP6HomeLinkPrefix, avp.getData(), true);
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
        for (int i = 0; i < countMIPHomeAgentAddress(); ++i) {
            sb.append("    MIPHomeAgentAddress:");
            try {
                sb.append(getMIPHomeAgentAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMIPHomeAgentHost()) {
            sb.append("    MIPHomeAgentHost:");
            try {
                sb.append(getMIPHomeAgentHost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMIP6HomeLinkPrefix()) {
            sb.append("    MIP6HomeLinkPrefix:");
            try {
                sb.append(getMIP6HomeLinkPrefix()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
