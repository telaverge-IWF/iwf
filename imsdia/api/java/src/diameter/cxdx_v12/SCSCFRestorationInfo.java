package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class SCSCFRestorationInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SCSCFRestorationInfo.
     */
    public SCSCFRestorationInfo() {}

    SCSCFRestorationInfo(com.intellinet.diameter.GroupedData data) {
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
     * Returns number of RestorationInfo instances.
     */
    public int countRestorationInfo() {
        return _data.getContainer().count(Cxdx_v12AttributeName.RestorationInfo);
    }

    /**
     * Gets one RestorationInfo.
     *
     * @param index - the index of the attribute to return
     */
    public RestorationInfo getRestorationInfo(int index) throws NoSuchAttributeException {
        return (RestorationInfo)_data.getContainer().get(Cxdx_v12AttributeName.RestorationInfo, index);
    }

    /**
     * Adds one RestorationInfo.
     *
     * @param avp - the attribute value
     */
    public void addRestorationInfo(RestorationInfo avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.RestorationInfo, avp.getData(), false);
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
        for (int i = 0; i < countRestorationInfo(); ++i) {
            sb.append("    RestorationInfo:");
            try {
                sb.append(getRestorationInfo(i)).append('\n');
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
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
