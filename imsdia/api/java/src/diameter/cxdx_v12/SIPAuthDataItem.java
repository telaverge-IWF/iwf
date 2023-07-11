package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The SIP-Auth-Data-Item is of type Grouped, and contains the authentication and/or authorization information for the
 * Diameter client.
 */
public class SIPAuthDataItem extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SIPAuthDataItem.
     */
    public SIPAuthDataItem() {}

    SIPAuthDataItem(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SIPItemNumber.
     */
    public boolean containsSIPItemNumber() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SIPItemNumber);
    }

    /**
     * Gets the SIPItemNumber.
     */
    public SIPItemNumber getSIPItemNumber() throws NoSuchAttributeException {
        return (SIPItemNumber)_data.getContainer().get(Cxdx_v12AttributeName.SIPItemNumber, 0);
    }

    /**
     * Sets the SIPItemNumber.
     *
     * @param avp - the attribute value
     */
    public void setSIPItemNumber(SIPItemNumber avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SIPItemNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPAuthenticationScheme.
     */
    public boolean containsSIPAuthenticationScheme() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SIPAuthenticationScheme);
    }

    /**
     * Gets the SIPAuthenticationScheme.
     */
    public SIPAuthenticationScheme getSIPAuthenticationScheme() throws NoSuchAttributeException {
        return (SIPAuthenticationScheme)_data.getContainer().get(Cxdx_v12AttributeName.SIPAuthenticationScheme, 0);
    }

    /**
     * Sets the SIPAuthenticationScheme.
     *
     * @param avp - the attribute value
     */
    public void setSIPAuthenticationScheme(SIPAuthenticationScheme avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SIPAuthenticationScheme, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPAuthenticate.
     */
    public boolean containsSIPAuthenticate() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SIPAuthenticate);
    }

    /**
     * Gets the SIPAuthenticate.
     */
    public SIPAuthenticate getSIPAuthenticate() throws NoSuchAttributeException {
        return (SIPAuthenticate)_data.getContainer().get(Cxdx_v12AttributeName.SIPAuthenticate, 0);
    }

    /**
     * Sets the SIPAuthenticate.
     *
     * @param avp - the attribute value
     */
    public void setSIPAuthenticate(SIPAuthenticate avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SIPAuthenticate, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPAuthorization.
     */
    public boolean containsSIPAuthorization() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SIPAuthorization);
    }

    /**
     * Gets the SIPAuthorization.
     */
    public SIPAuthorization getSIPAuthorization() throws NoSuchAttributeException {
        return (SIPAuthorization)_data.getContainer().get(Cxdx_v12AttributeName.SIPAuthorization, 0);
    }

    /**
     * Sets the SIPAuthorization.
     *
     * @param avp - the attribute value
     */
    public void setSIPAuthorization(SIPAuthorization avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SIPAuthorization, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPAuthenticationContext.
     */
    public boolean containsSIPAuthenticationContext() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SIPAuthenticationContext);
    }

    /**
     * Gets the SIPAuthenticationContext.
     */
    public SIPAuthenticationContext getSIPAuthenticationContext() throws NoSuchAttributeException {
        return (SIPAuthenticationContext)_data.getContainer().get(Cxdx_v12AttributeName.SIPAuthenticationContext, 0);
    }

    /**
     * Sets the SIPAuthenticationContext.
     *
     * @param avp - the attribute value
     */
    public void setSIPAuthenticationContext(SIPAuthenticationContext avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SIPAuthenticationContext, avp.getData(), true);
    }

    /**
     * Tests whether there is any ConfidentialityKey.
     */
    public boolean containsConfidentialityKey() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.ConfidentialityKey);
    }

    /**
     * Gets the ConfidentialityKey.
     */
    public ConfidentialityKey getConfidentialityKey() throws NoSuchAttributeException {
        return (ConfidentialityKey)_data.getContainer().get(Cxdx_v12AttributeName.ConfidentialityKey, 0);
    }

    /**
     * Sets the ConfidentialityKey.
     *
     * @param avp - the attribute value
     */
    public void setConfidentialityKey(ConfidentialityKey avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.ConfidentialityKey, avp.getData(), true);
    }

    /**
     * Tests whether there is any IntegrityKey.
     */
    public boolean containsIntegrityKey() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.IntegrityKey);
    }

    /**
     * Gets the IntegrityKey.
     */
    public IntegrityKey getIntegrityKey() throws NoSuchAttributeException {
        return (IntegrityKey)_data.getContainer().get(Cxdx_v12AttributeName.IntegrityKey, 0);
    }

    /**
     * Sets the IntegrityKey.
     *
     * @param avp - the attribute value
     */
    public void setIntegrityKey(IntegrityKey avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.IntegrityKey, avp.getData(), true);
    }

    /**
     * Tests whether there is any SIPDigestAuthenticate.
     */
    public boolean containsSIPDigestAuthenticate() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SIPDigestAuthenticate);
    }

    /**
     * Gets the SIPDigestAuthenticate.
     */
    public SIPDigestAuthenticate getSIPDigestAuthenticate() throws NoSuchAttributeException {
        return (SIPDigestAuthenticate)_data.getContainer().get(Cxdx_v12AttributeName.SIPDigestAuthenticate, 0);
    }

    /**
     * Sets the SIPDigestAuthenticate.
     *
     * @param avp - the attribute value
     */
    public void setSIPDigestAuthenticate(SIPDigestAuthenticate avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SIPDigestAuthenticate, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedIPAddress.
     */
    public boolean containsFramedIPAddress() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.FramedIPAddress);
    }

    /**
     * Gets the FramedIPAddress.
     */
    public FramedIPAddress getFramedIPAddress() throws NoSuchAttributeException {
        return (FramedIPAddress)_data.getContainer().get(Cxdx_v12AttributeName.FramedIPAddress, 0);
    }

    /**
     * Sets the FramedIPAddress.
     *
     * @param avp - the attribute value
     */
    public void setFramedIPAddress(FramedIPAddress avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.FramedIPAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedIPv6Prefix.
     */
    public boolean containsFramedIPv6Prefix() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.FramedIPv6Prefix);
    }

    /**
     * Gets the FramedIPv6Prefix.
     */
    public FramedIPv6Prefix getFramedIPv6Prefix() throws NoSuchAttributeException {
        return (FramedIPv6Prefix)_data.getContainer().get(Cxdx_v12AttributeName.FramedIPv6Prefix, 0);
    }

    /**
     * Sets the FramedIPv6Prefix.
     *
     * @param avp - the attribute value
     */
    public void setFramedIPv6Prefix(FramedIPv6Prefix avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.FramedIPv6Prefix, avp.getData(), true);
    }

    /**
     * Tests whether there is any FramedInterfaceId.
     */
    public boolean containsFramedInterfaceId() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.FramedInterfaceId);
    }

    /**
     * Gets the FramedInterfaceId.
     */
    public FramedInterfaceId getFramedInterfaceId() throws NoSuchAttributeException {
        return (FramedInterfaceId)_data.getContainer().get(Cxdx_v12AttributeName.FramedInterfaceId, 0);
    }

    /**
     * Sets the FramedInterfaceId.
     *
     * @param avp - the attribute value
     */
    public void setFramedInterfaceId(FramedInterfaceId avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.FramedInterfaceId, avp.getData(), true);
    }

    /**
     * Returns number of LineIdentifier instances.
     */
    public int countLineIdentifier() {
        return _data.getContainer().count(Cxdx_v12AttributeName.LineIdentifier);
    }

    /**
     * Gets one LineIdentifier.
     *
     * @param index - the index of the attribute to return
     */
    public LineIdentifier getLineIdentifier(int index) throws NoSuchAttributeException {
        return (LineIdentifier)_data.getContainer().get(Cxdx_v12AttributeName.LineIdentifier, index);
    }

    /**
     * Adds one LineIdentifier.
     *
     * @param avp - the attribute value
     */
    public void addLineIdentifier(LineIdentifier avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.LineIdentifier, avp.getData(), false);
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
        if (containsSIPItemNumber()) {
            sb.append("    SIPItemNumber:");
            try {
                sb.append(getSIPItemNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPAuthenticationScheme()) {
            sb.append("    SIPAuthenticationScheme:");
            try {
                sb.append(getSIPAuthenticationScheme()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPAuthenticate()) {
            sb.append("    SIPAuthenticate:");
            try {
                sb.append(getSIPAuthenticate()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPAuthorization()) {
            sb.append("    SIPAuthorization:");
            try {
                sb.append(getSIPAuthorization()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPAuthenticationContext()) {
            sb.append("    SIPAuthenticationContext:");
            try {
                sb.append(getSIPAuthenticationContext()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsConfidentialityKey()) {
            sb.append("    ConfidentialityKey:");
            try {
                sb.append(getConfidentialityKey()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIntegrityKey()) {
            sb.append("    IntegrityKey:");
            try {
                sb.append(getIntegrityKey()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSIPDigestAuthenticate()) {
            sb.append("    SIPDigestAuthenticate:");
            try {
                sb.append(getSIPDigestAuthenticate()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedIPAddress()) {
            sb.append("    FramedIPAddress:");
            try {
                sb.append(getFramedIPAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedIPv6Prefix()) {
            sb.append("    FramedIPv6Prefix:");
            try {
                sb.append(getFramedIPv6Prefix()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFramedInterfaceId()) {
            sb.append("    FramedInterfaceId:");
            try {
                sb.append(getFramedInterfaceId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countLineIdentifier(); ++i) {
            sb.append("    LineIdentifier:");
            try {
                sb.append(getLineIdentifier(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
