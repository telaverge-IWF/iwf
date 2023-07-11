package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class SIPDigestAuthenticate extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SIPDigestAuthenticate.
     */
    public SIPDigestAuthenticate() {}

    SIPDigestAuthenticate(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the DigestRealm.
     */
    public DigestRealm getDigestRealm() throws NoSuchAttributeException {
        return (DigestRealm)_data.getContainer().get(Cxdx_v12AttributeName.DigestRealm, 0);
    }

    /**
     * Sets the DigestRealm.
     *
     * @param avp - the attribute value
     */
    public void setDigestRealm(DigestRealm avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.DigestRealm, avp.getData(), true);
    }

    /**
     * Gets the DigestQoP.
     */
    public DigestQoP getDigestQoP() throws NoSuchAttributeException {
        return (DigestQoP)_data.getContainer().get(Cxdx_v12AttributeName.DigestQoP, 0);
    }

    /**
     * Sets the DigestQoP.
     *
     * @param avp - the attribute value
     */
    public void setDigestQoP(DigestQoP avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.DigestQoP, avp.getData(), true);
    }

    /**
     * Gets the DigestHA1.
     */
    public DigestHA1 getDigestHA1() throws NoSuchAttributeException {
        return (DigestHA1)_data.getContainer().get(Cxdx_v12AttributeName.DigestHA1, 0);
    }

    /**
     * Sets the DigestHA1.
     *
     * @param avp - the attribute value
     */
    public void setDigestHA1(DigestHA1 avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.DigestHA1, avp.getData(), true);
    }

    /**
     * Tests whether there is any DigestAlgorithm.
     */
    public boolean containsDigestAlgorithm() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.DigestAlgorithm);
    }

    /**
     * Gets the DigestAlgorithm.
     */
    public DigestAlgorithm getDigestAlgorithm() throws NoSuchAttributeException {
        return (DigestAlgorithm)_data.getContainer().get(Cxdx_v12AttributeName.DigestAlgorithm, 0);
    }

    /**
     * Sets the DigestAlgorithm.
     *
     * @param avp - the attribute value
     */
    public void setDigestAlgorithm(DigestAlgorithm avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.DigestAlgorithm, avp.getData(), true);
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
        sb.append("    DigestRealm:");
            try {
                sb.append(getDigestRealm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    DigestQoP:");
            try {
                sb.append(getDigestQoP()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    DigestHA1:");
            try {
                sb.append(getDigestHA1()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsDigestAlgorithm()) {
            sb.append("    DigestAlgorithm:");
            try {
                sb.append(getDigestAlgorithm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
