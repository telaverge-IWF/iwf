package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The SDP-TimeStamps AVP (AVP code 1273) is of type Grouped and holds the 
 * time of the SDP offer and the SDP answer.
 */
public class SDPTimeStamps extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SDPTimeStamps.
     */
    public SDPTimeStamps() {}

    SDPTimeStamps(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SDPOfferTimestamp.
     */
    public boolean containsSDPOfferTimestamp() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SDPOfferTimestamp);
    }

    /**
     * Gets the SDPOfferTimestamp.
     */
    public SDPOfferTimestamp getSDPOfferTimestamp() throws NoSuchAttributeException {
        return (SDPOfferTimestamp)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPOfferTimestamp, 0);
    }

    /**
     * Sets the SDPOfferTimestamp.
     *
     * @param avp - the attribute value
     */
    public void setSDPOfferTimestamp(SDPOfferTimestamp avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPOfferTimestamp, avp.getData(), true);
    }

    /**
     * Tests whether there is any SDPAnswerTimestamp.
     */
    public boolean containsSDPAnswerTimestamp() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SDPAnswerTimestamp);
    }

    /**
     * Gets the SDPAnswerTimestamp.
     */
    public SDPAnswerTimestamp getSDPAnswerTimestamp() throws NoSuchAttributeException {
        return (SDPAnswerTimestamp)_data.getContainer().get(Ro_r10_transatelAttributeName.SDPAnswerTimestamp, 0);
    }

    /**
     * Sets the SDPAnswerTimestamp.
     *
     * @param avp - the attribute value
     */
    public void setSDPAnswerTimestamp(SDPAnswerTimestamp avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SDPAnswerTimestamp, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsSDPOfferTimestamp()) {
            sb.append("    SDPOfferTimestamp:");
            try {
                sb.append(getSDPOfferTimestamp()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSDPAnswerTimestamp()) {
            sb.append("    SDPAnswerTimestamp:");
            try {
                sb.append(getSDPAnswerTimestamp()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
