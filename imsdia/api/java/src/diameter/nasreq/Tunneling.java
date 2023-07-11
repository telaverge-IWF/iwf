package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunneling AVP (AVP Code 401) is of type Grouped and contains the
 * following AVPs, used to describe a compulsory tunnel service:
 * [RADTunnels], [RADTunlAcct].
 */
public class Tunneling extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new Tunneling.
     */
    public Tunneling() {}

    Tunneling(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the TunnelType.
     */
    public TunnelType getTunnelType() throws NoSuchAttributeException {
        return (TunnelType)_data.getContainer().get(NasreqAttributeName.TunnelType, 0);
    }

    /**
     * Sets the TunnelType.
     *
     * @param avp - the attribute value
     */
    public void setTunnelType(TunnelType avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelType, avp.getData(), true);
    }

    /**
     * Gets the TunnelMediumType.
     */
    public TunnelMediumType getTunnelMediumType() throws NoSuchAttributeException {
        return (TunnelMediumType)_data.getContainer().get(NasreqAttributeName.TunnelMediumType, 0);
    }

    /**
     * Sets the TunnelMediumType.
     *
     * @param avp - the attribute value
     */
    public void setTunnelMediumType(TunnelMediumType avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelMediumType, avp.getData(), true);
    }

    /**
     * Gets the TunnelClientEndpoint.
     */
    public TunnelClientEndpoint getTunnelClientEndpoint() throws NoSuchAttributeException {
        return (TunnelClientEndpoint)_data.getContainer().get(NasreqAttributeName.TunnelClientEndpoint, 0);
    }

    /**
     * Sets the TunnelClientEndpoint.
     *
     * @param avp - the attribute value
     */
    public void setTunnelClientEndpoint(TunnelClientEndpoint avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelClientEndpoint, avp.getData(), true);
    }

    /**
     * Gets the TunnelServerEndpoint.
     */
    public TunnelServerEndpoint getTunnelServerEndpoint() throws NoSuchAttributeException {
        return (TunnelServerEndpoint)_data.getContainer().get(NasreqAttributeName.TunnelServerEndpoint, 0);
    }

    /**
     * Sets the TunnelServerEndpoint.
     *
     * @param avp - the attribute value
     */
    public void setTunnelServerEndpoint(TunnelServerEndpoint avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelServerEndpoint, avp.getData(), true);
    }

    /**
     * Tests whether there is any TunnelPreference.
     */
    public boolean containsTunnelPreference() {
        return _data.getContainer().contains(NasreqAttributeName.TunnelPreference);
    }

    /**
     * Gets the TunnelPreference.
     */
    public TunnelPreference getTunnelPreference() throws NoSuchAttributeException {
        return (TunnelPreference)_data.getContainer().get(NasreqAttributeName.TunnelPreference, 0);
    }

    /**
     * Sets the TunnelPreference.
     *
     * @param avp - the attribute value
     */
    public void setTunnelPreference(TunnelPreference avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelPreference, avp.getData(), true);
    }

    /**
     * Tests whether there is any TunnelClientAuthId.
     */
    public boolean containsTunnelClientAuthId() {
        return _data.getContainer().contains(NasreqAttributeName.TunnelClientAuthId);
    }

    /**
     * Gets the TunnelClientAuthId.
     */
    public TunnelClientAuthId getTunnelClientAuthId() throws NoSuchAttributeException {
        return (TunnelClientAuthId)_data.getContainer().get(NasreqAttributeName.TunnelClientAuthId, 0);
    }

    /**
     * Sets the TunnelClientAuthId.
     *
     * @param avp - the attribute value
     */
    public void setTunnelClientAuthId(TunnelClientAuthId avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelClientAuthId, avp.getData(), true);
    }

    /**
     * Tests whether there is any TunnelServerAuthId.
     */
    public boolean containsTunnelServerAuthId() {
        return _data.getContainer().contains(NasreqAttributeName.TunnelServerAuthId);
    }

    /**
     * Gets the TunnelServerAuthId.
     */
    public TunnelServerAuthId getTunnelServerAuthId() throws NoSuchAttributeException {
        return (TunnelServerAuthId)_data.getContainer().get(NasreqAttributeName.TunnelServerAuthId, 0);
    }

    /**
     * Sets the TunnelServerAuthId.
     *
     * @param avp - the attribute value
     */
    public void setTunnelServerAuthId(TunnelServerAuthId avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelServerAuthId, avp.getData(), true);
    }

    /**
     * Tests whether there is any TunnelAssignmentId.
     */
    public boolean containsTunnelAssignmentId() {
        return _data.getContainer().contains(NasreqAttributeName.TunnelAssignmentId);
    }

    /**
     * Gets the TunnelAssignmentId.
     */
    public TunnelAssignmentId getTunnelAssignmentId() throws NoSuchAttributeException {
        return (TunnelAssignmentId)_data.getContainer().get(NasreqAttributeName.TunnelAssignmentId, 0);
    }

    /**
     * Sets the TunnelAssignmentId.
     *
     * @param avp - the attribute value
     */
    public void setTunnelAssignmentId(TunnelAssignmentId avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelAssignmentId, avp.getData(), true);
    }

    /**
     * Tests whether there is any TunnelPassword.
     */
    public boolean containsTunnelPassword() {
        return _data.getContainer().contains(NasreqAttributeName.TunnelPassword);
    }

    /**
     * Gets the TunnelPassword.
     */
    public TunnelPassword getTunnelPassword() throws NoSuchAttributeException {
        return (TunnelPassword)_data.getContainer().get(NasreqAttributeName.TunnelPassword, 0);
    }

    /**
     * Sets the TunnelPassword.
     *
     * @param avp - the attribute value
     */
    public void setTunnelPassword(TunnelPassword avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelPassword, avp.getData(), true);
    }

    /**
     * Tests whether there is any TunnelPrivateGroupId.
     */
    public boolean containsTunnelPrivateGroupId() {
        return _data.getContainer().contains(NasreqAttributeName.TunnelPrivateGroupId);
    }

    /**
     * Gets the TunnelPrivateGroupId.
     */
    public TunnelPrivateGroupId getTunnelPrivateGroupId() throws NoSuchAttributeException {
        return (TunnelPrivateGroupId)_data.getContainer().get(NasreqAttributeName.TunnelPrivateGroupId, 0);
    }

    /**
     * Sets the TunnelPrivateGroupId.
     *
     * @param avp - the attribute value
     */
    public void setTunnelPrivateGroupId(TunnelPrivateGroupId avp) {
        _data.getContainer().add(NasreqAttributeName.TunnelPrivateGroupId, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    TunnelType:");
            try {
                sb.append(getTunnelType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    TunnelMediumType:");
            try {
                sb.append(getTunnelMediumType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    TunnelClientEndpoint:");
            try {
                sb.append(getTunnelClientEndpoint()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    TunnelServerEndpoint:");
            try {
                sb.append(getTunnelServerEndpoint()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsTunnelPreference()) {
            sb.append("    TunnelPreference:");
            try {
                sb.append(getTunnelPreference()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTunnelClientAuthId()) {
            sb.append("    TunnelClientAuthId:");
            try {
                sb.append(getTunnelClientAuthId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTunnelServerAuthId()) {
            sb.append("    TunnelServerAuthId:");
            try {
                sb.append(getTunnelServerAuthId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTunnelAssignmentId()) {
            sb.append("    TunnelAssignmentId:");
            try {
                sb.append(getTunnelAssignmentId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTunnelPassword()) {
            sb.append("    TunnelPassword:");
            try {
                sb.append(getTunnelPassword()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTunnelPrivateGroupId()) {
            sb.append("    TunnelPrivateGroupId:");
            try {
                sb.append(getTunnelPrivateGroupId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
