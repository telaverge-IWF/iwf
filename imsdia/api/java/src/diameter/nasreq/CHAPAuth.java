package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The CHAP-Auth AVP (AVP Code 402) is of type Grouped and contains the
 * information necessary to authenticate a user using the PPP
 * Challenge-Handshake Authentication Protocol (CHAP) [PPPCHAP]. If the
 * CHAP-Auth AVP is found in a message, the CHAP-Challenge AVP MUST be
 * present as well. The optional AVPs containing the CHAP response
 * depend upon the value of the CHAP-Algorithm AVP.
 */
public class CHAPAuth extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CHAPAuth.
     */
    public CHAPAuth() {}

    CHAPAuth(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the CHAPAlgorithm.
     */
    public CHAPAlgorithm getCHAPAlgorithm() throws NoSuchAttributeException {
        return (CHAPAlgorithm)_data.getContainer().get(NasreqAttributeName.CHAPAlgorithm, 0);
    }

    /**
     * Sets the CHAPAlgorithm.
     *
     * @param avp - the attribute value
     */
    public void setCHAPAlgorithm(CHAPAlgorithm avp) {
        _data.getContainer().add(NasreqAttributeName.CHAPAlgorithm, avp.getData(), true);
    }

    /**
     * Gets the CHAPIdent.
     */
    public CHAPIdent getCHAPIdent() throws NoSuchAttributeException {
        return (CHAPIdent)_data.getContainer().get(NasreqAttributeName.CHAPIdent, 0);
    }

    /**
     * Sets the CHAPIdent.
     *
     * @param avp - the attribute value
     */
    public void setCHAPIdent(CHAPIdent avp) {
        _data.getContainer().add(NasreqAttributeName.CHAPIdent, avp.getData(), true);
    }

    /**
     * Tests whether there is any CHAPResponse.
     */
    public boolean containsCHAPResponse() {
        return _data.getContainer().contains(NasreqAttributeName.CHAPResponse);
    }

    /**
     * Gets the CHAPResponse.
     */
    public CHAPResponse getCHAPResponse() throws NoSuchAttributeException {
        return (CHAPResponse)_data.getContainer().get(NasreqAttributeName.CHAPResponse, 0);
    }

    /**
     * Sets the CHAPResponse.
     *
     * @param avp - the attribute value
     */
    public void setCHAPResponse(CHAPResponse avp) {
        _data.getContainer().add(NasreqAttributeName.CHAPResponse, avp.getData(), true);
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
        sb.append("    CHAPAlgorithm:");
            try {
                sb.append(getCHAPAlgorithm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CHAPIdent:");
            try {
                sb.append(getCHAPIdent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsCHAPResponse()) {
            sb.append("    CHAPResponse:");
            try {
                sb.append(getCHAPResponse()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
