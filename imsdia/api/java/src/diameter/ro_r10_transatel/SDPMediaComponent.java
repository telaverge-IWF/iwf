package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * SDP-Media-Component AVP is of type Grouped and contains information about media used for a
 * IMS session.
 */
public class SDPMediaComponent extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SDPMediaComponent.
     */
    public SDPMediaComponent() {}

    SDPMediaComponent(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SDPMediaName.
     */
    public boolean containsSDPMediaName() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SDPMediaName);
    }

    /**
     * Gets the SDPMediaName.
     */
    public SDPMediaName getSDPMediaName() throws NoSuchAttributeException {
        return (SDPMediaName)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPMediaName, 0);
    }

    /**
     * Sets the SDPMediaName.
     *
     * @param avp - the attribute value
     */
    public void setSDPMediaName(SDPMediaName avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPMediaName, avp.getData(), true);
    }

    /**
     * Returns number of SDPMediaDescription instances.
     */
    public int countSDPMediaDescription() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.SDPMediaDescription);
    }

    /**
     * Gets one SDPMediaDescription.
     *
     * @param index - the index of the attribute to return
     */
    public SDPMediaDescription getSDPMediaDescription(int index) throws NoSuchAttributeException {
        return (SDPMediaDescription)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPMediaDescription, index);
    }

    /**
     * Adds one SDPMediaDescription.
     *
     * @param avp - the attribute value
     */
    public void addSDPMediaDescription(SDPMediaDescription avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPMediaDescription, avp.getData(), false);
    }

    /**
     * Tests whether there is any LocalGWInsertedIndication.
     */
    public boolean containsLocalGWInsertedIndication() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.LocalGWInsertedIndication);
    }

    /**
     * Gets the LocalGWInsertedIndication.
     */
    public LocalGWInsertedIndication getLocalGWInsertedIndication() throws NoSuchAttributeException {
        return (LocalGWInsertedIndication)_data.getContainer().get(Ro_r10_transatelAttributeName.LocalGWInsertedIndication, 0);
    }

    /**
     * Sets the LocalGWInsertedIndication.
     *
     * @param avp - the attribute value
     */
    public void setLocalGWInsertedIndication(LocalGWInsertedIndication avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.LocalGWInsertedIndication, avp.getData(), true);
    }

    /**
     * Tests whether there is any TranscoderInsertedIndication.
     */
    public boolean containsTranscoderInsertedIndication() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TranscoderInsertedIndication);
    }

    /**
     * Gets the TranscoderInsertedIndication.
     */
    public TranscoderInsertedIndication getTranscoderInsertedIndication() throws NoSuchAttributeException {
        return (TranscoderInsertedIndication)_data.getContainer().get(Ro_r10_transatelAttributeName.TranscoderInsertedIndication, 0);
    }

    /**
     * Sets the TranscoderInsertedIndication.
     *
     * @param avp - the attribute value
     */
    public void setTranscoderInsertedIndication(TranscoderInsertedIndication avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TranscoderInsertedIndication, avp.getData(), true);
    }

    /**
     * Tests whether there is any IPRealmDefaultIndication.
     */
    public boolean containsIPRealmDefaultIndication() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.IPRealmDefaultIndication);
    }

    /**
     * Gets the IPRealmDefaultIndication.
     */
    public IPRealmDefaultIndication getIPRealmDefaultIndication() throws NoSuchAttributeException {
        return (IPRealmDefaultIndication)_data.getContainer().get(Ro_r10_transatelAttributeName.IPRealmDefaultIndication, 0);
    }

    /**
     * Sets the IPRealmDefaultIndication.
     *
     * @param avp - the attribute value
     */
    public void setIPRealmDefaultIndication(IPRealmDefaultIndication avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.IPRealmDefaultIndication, avp.getData(), true);
    }

    /**
     * Tests whether there is any MediaInitiatorFlag.
     */
    public boolean containsMediaInitiatorFlag() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MediaInitiatorFlag);
    }

    /**
     * Gets the MediaInitiatorFlag.
     */
    public MediaInitiatorFlag getMediaInitiatorFlag() throws NoSuchAttributeException {
        return (MediaInitiatorFlag)_data.getContainer().get(Ro_r10_transatelAttributeName.MediaInitiatorFlag, 0);
    }

    /**
     * Sets the MediaInitiatorFlag.
     *
     * @param avp - the attribute value
     */
    public void setMediaInitiatorFlag(MediaInitiatorFlag avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MediaInitiatorFlag, avp.getData(), true);
    }

    /**
     * Tests whether there is any MediaInitiatorParty.
     */
    public boolean containsMediaInitiatorParty() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.MediaInitiatorParty);
    }

    /**
     * Gets the MediaInitiatorParty.
     */
    public MediaInitiatorParty getMediaInitiatorParty() throws NoSuchAttributeException {
        return (MediaInitiatorParty)_data.getContainer().get(Ro_r10_transatelAttributeName.MediaInitiatorParty, 0);
    }

    /**
     * Sets the MediaInitiatorParty.
     *
     * @param avp - the attribute value
     */
    public void setMediaInitiatorParty(MediaInitiatorParty avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.MediaInitiatorParty, avp.getData(), true);
    }

    /**
     * Tests whether there is any AuthorizedQoS.
     */
    public boolean containsAuthorizedQoS() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AuthorizedQoS);
    }

    /**
     * Gets the AuthorizedQoS.
     */
    public AuthorizedQoS getAuthorizedQoS() throws NoSuchAttributeException {
        return (AuthorizedQoS)_data.getContainer().get(Ro_r10_transatelAttributeName.AuthorizedQoS, 0);
    }

    /**
     * Sets the AuthorizedQoS.
     *
     * @param avp - the attribute value
     */
    public void setAuthorizedQoS(AuthorizedQoS avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AuthorizedQoS, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPChargingId.
     */
    public boolean containsRo3GPPChargingId() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Ro3GPPChargingId);
    }

    /**
     * Gets the Ro3GPPChargingId.
     */
    public Ro3GPPChargingId getRo3GPPChargingId() throws NoSuchAttributeException {
        return (Ro3GPPChargingId)_data.getContainer().get(Ro_r10_transatelAttributeName.Ro3GPPChargingId, 0);
    }

    /**
     * Sets the Ro3GPPChargingId.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPChargingId(Ro3GPPChargingId avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Ro3GPPChargingId, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccessNetworkChargingIdentifierValue.
     */
    public boolean containsAccessNetworkChargingIdentifierValue() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccessNetworkChargingIdentifierValue);
    }

    /**
     * Gets the AccessNetworkChargingIdentifierValue.
     */
    public AccessNetworkChargingIdentifierValue getAccessNetworkChargingIdentifierValue() throws NoSuchAttributeException {
        return (AccessNetworkChargingIdentifierValue)_data.getContainer().get(Ro_r10_transatelAttributeName.AccessNetworkChargingIdentifierValue, 0);
    }

    /**
     * Sets the AccessNetworkChargingIdentifierValue.
     *
     * @param avp - the attribute value
     */
    public void setAccessNetworkChargingIdentifierValue(AccessNetworkChargingIdentifierValue avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccessNetworkChargingIdentifierValue, avp.getData(), true);
    }

    /**
     * Tests whether there is any SDPType.
     */
    public boolean containsSDPType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SDPType);
    }

    /**
     * Gets the SDPType.
     */
    public SDPType getSDPType() throws NoSuchAttributeException {
        return (SDPType)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPType, 0);
    }

    /**
     * Sets the SDPType.
     *
     * @param avp - the attribute value
     */
    public void setSDPType(SDPType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsSDPMediaName()) {
            sb.append("    SDPMediaName:");
            try {
                sb.append(getSDPMediaName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSDPMediaDescription(); ++i) {
            sb.append("    SDPMediaDescription:");
            try {
                sb.append(getSDPMediaDescription(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLocalGWInsertedIndication()) {
            sb.append("    LocalGWInsertedIndication:");
            try {
                sb.append(getLocalGWInsertedIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTranscoderInsertedIndication()) {
            sb.append("    TranscoderInsertedIndication:");
            try {
                sb.append(getTranscoderInsertedIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIPRealmDefaultIndication()) {
            sb.append("    IPRealmDefaultIndication:");
            try {
                sb.append(getIPRealmDefaultIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMediaInitiatorFlag()) {
            sb.append("    MediaInitiatorFlag:");
            try {
                sb.append(getMediaInitiatorFlag()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMediaInitiatorParty()) {
            sb.append("    MediaInitiatorParty:");
            try {
                sb.append(getMediaInitiatorParty()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAuthorizedQoS()) {
            sb.append("    AuthorizedQoS:");
            try {
                sb.append(getAuthorizedQoS()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPChargingId()) {
            sb.append("    Ro3GPPChargingId:");
            try {
                sb.append(getRo3GPPChargingId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccessNetworkChargingIdentifierValue()) {
            sb.append("    AccessNetworkChargingIdentifierValue:");
            try {
                sb.append(getAccessNetworkChargingIdentifierValue()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSDPType()) {
            sb.append("    SDPType:");
            try {
                sb.append(getSDPType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
