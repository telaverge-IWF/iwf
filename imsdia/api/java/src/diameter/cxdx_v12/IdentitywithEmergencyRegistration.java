package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class IdentitywithEmergencyRegistration extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new IdentitywithEmergencyRegistration.
     */
    public IdentitywithEmergencyRegistration() {}

    IdentitywithEmergencyRegistration(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the UserName.
     */
    public diameter.base.UserName getUserName() throws NoSuchAttributeException {
        return (diameter.base.UserName)_data.getContainer().get(diameter.base.BaseAttributeName.UserName, 0);
    }

    /**
     * Sets the UserName.
     *
     * @param avp - the attribute value
     */
    public void setUserName(diameter.base.UserName avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.UserName, avp.getData(), true);
    }

    /**
     * Gets the PublicIdentity.
     */
    public PublicIdentity getPublicIdentity() throws NoSuchAttributeException {
        return (PublicIdentity)_data.getContainer().get(Cxdx_v12AttributeName.PublicIdentity, 0);
    }

    /**
     * Sets the PublicIdentity.
     *
     * @param avp - the attribute value
     */
    public void setPublicIdentity(PublicIdentity avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.PublicIdentity, avp.getData(), true);
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
        sb.append("    UserName:");
            try {
                sb.append(getUserName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    PublicIdentity:");
            try {
                sb.append(getPublicIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
