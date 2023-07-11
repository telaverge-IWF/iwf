package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Originator-Interface AVP (AVP code 2009) is the group AVP which contains information related to the Interface on which the message originated.
 */
public class OriginatorInterface extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new OriginatorInterface.
     */
    public OriginatorInterface() {}

    OriginatorInterface(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any InterfaceId.
     */
    public boolean containsInterfaceId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.InterfaceId);
    }

    /**
     * Gets the InterfaceId.
     */
    public InterfaceId getInterfaceId() throws NoSuchAttributeException {
        return (InterfaceId)_data.getContainer().get(Ro_r10_transatelAttributeName.InterfaceId, 0);
    }

    /**
     * Sets the InterfaceId.
     *
     * @param avp - the attribute value
     */
    public void setInterfaceId(InterfaceId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.InterfaceId, avp.getData(), true);
    }

    /**
     * Tests whether there is any InterfaceText.
     */
    public boolean containsInterfaceText() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.InterfaceText);
    }

    /**
     * Gets the InterfaceText.
     */
    public InterfaceText getInterfaceText() throws NoSuchAttributeException {
        return (InterfaceText)_data.getContainer().get(Ro_r10_transatelAttributeName.InterfaceText, 0);
    }

    /**
     * Sets the InterfaceText.
     *
     * @param avp - the attribute value
     */
    public void setInterfaceText(InterfaceText avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.InterfaceText, avp.getData(), true);
    }

    /**
     * Tests whether there is any InterfacePort.
     */
    public boolean containsInterfacePort() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.InterfacePort);
    }

    /**
     * Gets the InterfacePort.
     */
    public InterfacePort getInterfacePort() throws NoSuchAttributeException {
        return (InterfacePort)_data.getContainer().get(Ro_r10_transatelAttributeName.InterfacePort, 0);
    }

    /**
     * Sets the InterfacePort.
     *
     * @param avp - the attribute value
     */
    public void setInterfacePort(InterfacePort avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.InterfacePort, avp.getData(), true);
    }

    /**
     * Tests whether there is any InterfaceType.
     */
    public boolean containsInterfaceType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.InterfaceType);
    }

    /**
     * Gets the InterfaceType.
     */
    public InterfaceType getInterfaceType() throws NoSuchAttributeException {
        return (InterfaceType)_data.getContainer().get(Ro_r10_transatelAttributeName.InterfaceType, 0);
    }

    /**
     * Sets the InterfaceType.
     *
     * @param avp - the attribute value
     */
    public void setInterfaceType(InterfaceType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.InterfaceType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsInterfaceId()) {
            sb.append("    InterfaceId:");
            try {
                sb.append(getInterfaceId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsInterfaceText()) {
            sb.append("    InterfaceText:");
            try {
                sb.append(getInterfaceText()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsInterfacePort()) {
            sb.append("    InterfacePort:");
            try {
                sb.append(getInterfacePort()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsInterfaceType()) {
            sb.append("    InterfaceType:");
            try {
                sb.append(getInterfaceType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
