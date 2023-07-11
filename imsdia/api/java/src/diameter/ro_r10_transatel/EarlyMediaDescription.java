package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Early-Media-Description AVP (AVP code 1272) is of type grouped and 
 * describes the SDP session, media parameters and timestamps related to 
 * media components set to active according to SDP signalling exchanged 
 * during a  SIP session establishment before the final successful or 
 * unsuccessful SIP answer to the initial SIP INVITE message is received. 
 * Once a media component has been set to active, subsequent status changes 
 * shall also be registered.
 */
public class EarlyMediaDescription extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new EarlyMediaDescription.
     */
    public EarlyMediaDescription() {}

    EarlyMediaDescription(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SDPTimeStamps.
     */
    public boolean containsSDPTimeStamps() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SDPTimeStamps);
    }

    /**
     * Gets the SDPTimeStamps.
     */
    public SDPTimeStamps getSDPTimeStamps() throws NoSuchAttributeException {
        return (SDPTimeStamps)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPTimeStamps, 0);
    }

    /**
     * Sets the SDPTimeStamps.
     *
     * @param avp - the attribute value
     */
    public void setSDPTimeStamps(SDPTimeStamps avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPTimeStamps, avp.getData(), true);
    }

    /**
     * Returns number of SDPMediaComponent instances.
     */
    public int countSDPMediaComponent() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.SDPMediaComponent);
    }

    /**
     * Gets one SDPMediaComponent.
     *
     * @param index - the index of the attribute to return
     */
    public SDPMediaComponent getSDPMediaComponent(int index) throws NoSuchAttributeException {
        return (SDPMediaComponent)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPMediaComponent, index);
    }

    /**
     * Adds one SDPMediaComponent.
     *
     * @param avp - the attribute value
     */
    public void addSDPMediaComponent(SDPMediaComponent avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPMediaComponent, avp.getData(), false);
    }

    /**
     * Returns number of SDPSessionDescription instances.
     */
    public int countSDPSessionDescription() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.SDPSessionDescription);
    }

    /**
     * Gets one SDPSessionDescription.
     *
     * @param index - the index of the attribute to return
     */
    public SDPSessionDescription getSDPSessionDescription(int index) throws NoSuchAttributeException {
        return (SDPSessionDescription)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPSessionDescription, index);
    }

    /**
     * Adds one SDPSessionDescription.
     *
     * @param avp - the attribute value
     */
    public void addSDPSessionDescription(SDPSessionDescription avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPSessionDescription, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsSDPTimeStamps()) {
            sb.append("    SDPTimeStamps:");
            try {
                sb.append(getSDPTimeStamps()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSDPMediaComponent(); ++i) {
            sb.append("    SDPMediaComponent:");
            try {
                sb.append(getSDPMediaComponent(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSDPSessionDescription(); ++i) {
            sb.append("    SDPSessionDescription:");
            try {
                sb.append(getSDPSessionDescription(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
