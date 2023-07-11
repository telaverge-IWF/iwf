package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Associated-Identities AVP is of type Grouped and it contains the private user identities 
 * associated to an IMS subscription. 
 */
public class AssociatedIdentities extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AssociatedIdentities.
     */
    public AssociatedIdentities() {}

    AssociatedIdentities(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of UserName instances.
     */
    public int countUserName() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.UserName);
    }

    /**
     * Gets one UserName.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.UserName getUserName(int index) throws NoSuchAttributeException {
        return (diameter.base.UserName)_data.getContainer().get(diameter.base.BaseAttributeName.UserName, index);
    }

    /**
     * Adds one UserName.
     *
     * @param avp - the attribute value
     */
    public void addUserName(diameter.base.UserName avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.UserName, avp.getData(), false);
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
        for (int i = 0; i < countUserName(); ++i) {
            sb.append("    UserName:");
            try {
                sb.append(getUserName(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
