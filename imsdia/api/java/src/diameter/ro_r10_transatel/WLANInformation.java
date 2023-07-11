package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * WLAN-Information AVP is of type Grouped. Its purpose is to allow the transmission of additional
 * WLAN service specific information elements. The format and the contents of the fields inside the
 * WLAN-Information AVP is specified in TS 32.252.
 */
public class WLANInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new WLANInformation.
     */
    public WLANInformation() {}

    WLANInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any WLANSessionId.
     */
    public boolean containsWLANSessionId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.WLANSessionId);
    }

    /**
     * Gets the WLANSessionId.
     */
    public WLANSessionId getWLANSessionId() throws NoSuchAttributeException {
        return (WLANSessionId)_data.getContainer().get(Ro_r10_transatelAttributeName.WLANSessionId, 0);
    }

    /**
     * Sets the WLANSessionId.
     *
     * @param avp - the attribute value
     */
    public void setWLANSessionId(WLANSessionId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.WLANSessionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any PDGAddress.
     */
    public boolean containsPDGAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PDGAddress);
    }

    /**
     * Gets the PDGAddress.
     */
    public PDGAddress getPDGAddress() throws NoSuchAttributeException {
        return (PDGAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.PDGAddress, 0);
    }

    /**
     * Sets the PDGAddress.
     *
     * @param avp - the attribute value
     */
    public void setPDGAddress(PDGAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PDGAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any PDGChargingId.
     */
    public boolean containsPDGChargingId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PDGChargingId);
    }

    /**
     * Gets the PDGChargingId.
     */
    public PDGChargingId getPDGChargingId() throws NoSuchAttributeException {
        return (PDGChargingId)_data.getContainer().get(Ro_r10_transatelAttributeName.PDGChargingId, 0);
    }

    /**
     * Sets the PDGChargingId.
     *
     * @param avp - the attribute value
     */
    public void setPDGChargingId(PDGChargingId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PDGChargingId, avp.getData(), true);
    }

    /**
     * Tests whether there is any WAGAddress.
     */
    public boolean containsWAGAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.WAGAddress);
    }

    /**
     * Gets the WAGAddress.
     */
    public WAGAddress getWAGAddress() throws NoSuchAttributeException {
        return (WAGAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.WAGAddress, 0);
    }

    /**
     * Sets the WAGAddress.
     *
     * @param avp - the attribute value
     */
    public void setWAGAddress(WAGAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.WAGAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any WAGPLMNId.
     */
    public boolean containsWAGPLMNId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.WAGPLMNId);
    }

    /**
     * Gets the WAGPLMNId.
     */
    public WAGPLMNId getWAGPLMNId() throws NoSuchAttributeException {
        return (WAGPLMNId)_data.getContainer().get(Ro_r10_transatelAttributeName.WAGPLMNId, 0);
    }

    /**
     * Sets the WAGPLMNId.
     *
     * @param avp - the attribute value
     */
    public void setWAGPLMNId(WAGPLMNId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.WAGPLMNId, avp.getData(), true);
    }

    /**
     * Tests whether there is any WLANRadioContainer.
     */
    public boolean containsWLANRadioContainer() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.WLANRadioContainer);
    }

    /**
     * Gets the WLANRadioContainer.
     */
    public WLANRadioContainer getWLANRadioContainer() throws NoSuchAttributeException {
        return (WLANRadioContainer)_data.getContainer().get(Ro_r10_transatelAttributeName.WLANRadioContainer, 0);
    }

    /**
     * Sets the WLANRadioContainer.
     *
     * @param avp - the attribute value
     */
    public void setWLANRadioContainer(WLANRadioContainer avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.WLANRadioContainer, avp.getData(), true);
    }

    /**
     * Tests whether there is any WLANUELocalIPAddress.
     */
    public boolean containsWLANUELocalIPAddress() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.WLANUELocalIPAddress);
    }

    /**
     * Gets the WLANUELocalIPAddress.
     */
    public WLANUELocalIPAddress getWLANUELocalIPAddress() throws NoSuchAttributeException {
        return (WLANUELocalIPAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.WLANUELocalIPAddress, 0);
    }

    /**
     * Sets the WLANUELocalIPAddress.
     *
     * @param avp - the attribute value
     */
    public void setWLANUELocalIPAddress(WLANUELocalIPAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.WLANUELocalIPAddress, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsWLANSessionId()) {
            sb.append("    WLANSessionId:");
            try {
                sb.append(getWLANSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPDGAddress()) {
            sb.append("    PDGAddress:");
            try {
                sb.append(getPDGAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPDGChargingId()) {
            sb.append("    PDGChargingId:");
            try {
                sb.append(getPDGChargingId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsWAGAddress()) {
            sb.append("    WAGAddress:");
            try {
                sb.append(getWAGAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsWAGPLMNId()) {
            sb.append("    WAGPLMNId:");
            try {
                sb.append(getWAGPLMNId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsWLANRadioContainer()) {
            sb.append("    WLANRadioContainer:");
            try {
                sb.append(getWLANRadioContainer()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsWLANUELocalIPAddress()) {
            sb.append("    WLANUELocalIPAddress:");
            try {
                sb.append(getWLANUELocalIPAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
