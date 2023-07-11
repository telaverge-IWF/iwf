package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Supported-Applications AVP is of type Grouped and it contains the supported application identifiers of a Diameter node.
 */
public class SupportedApplications extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SupportedApplications.
     */
    public SupportedApplications() {}

    SupportedApplications(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of AuthApplicationId instances.
     */
    public int countAuthApplicationId() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.AuthApplicationId);
    }

    /**
     * Gets one AuthApplicationId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.AuthApplicationId getAuthApplicationId(int index) throws NoSuchAttributeException {
        return (diameter.base.AuthApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.AuthApplicationId, index);
    }

    /**
     * Adds one AuthApplicationId.
     *
     * @param avp - the attribute value
     */
    public void addAuthApplicationId(diameter.base.AuthApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthApplicationId, avp.getData(), false);
    }

    /**
     * Returns number of AcctApplicationId instances.
     */
    public int countAcctApplicationId() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.AcctApplicationId);
    }

    /**
     * Gets one AcctApplicationId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.AcctApplicationId getAcctApplicationId(int index) throws NoSuchAttributeException {
        return (diameter.base.AcctApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.AcctApplicationId, index);
    }

    /**
     * Adds one AcctApplicationId.
     *
     * @param avp - the attribute value
     */
    public void addAcctApplicationId(diameter.base.AcctApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AcctApplicationId, avp.getData(), false);
    }

    /**
     * Returns number of VendorSpecificApplicationId instances.
     */
    public int countVendorSpecificApplicationId() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.VendorSpecificApplicationId);
    }

    /**
     * Gets one VendorSpecificApplicationId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.VendorSpecificApplicationId getVendorSpecificApplicationId(int index) throws NoSuchAttributeException {
        return (diameter.base.VendorSpecificApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.VendorSpecificApplicationId, index);
    }

    /**
     * Adds one VendorSpecificApplicationId.
     *
     * @param avp - the attribute value
     */
    public void addVendorSpecificApplicationId(diameter.base.VendorSpecificApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.VendorSpecificApplicationId, avp.getData(), false);
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
        for (int i = 0; i < countAuthApplicationId(); ++i) {
            sb.append("    AuthApplicationId:");
            try {
                sb.append(getAuthApplicationId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countAcctApplicationId(); ++i) {
            sb.append("    AcctApplicationId:");
            try {
                sb.append(getAcctApplicationId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countVendorSpecificApplicationId(); ++i) {
            sb.append("    VendorSpecificApplicationId:");
            try {
                sb.append(getVendorSpecificApplicationId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
