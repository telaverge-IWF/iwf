package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The Supported-Features is of type Grouped,If this AVP is present it may 
 * inform the destination host about the features that origin host supports.
 * The Vendor-ID AVP and the Feature-List AVP shall together identify which 
 * feature list is carried in the Supported-Features AVP.
 * Where a Supported-Feature AVP is used to identify  features that have been
 * defined by 3GPP, the Vendor-ID AVP shall contain the vendor ID of 3GPP.
 * Where the Supported-Feature AVP is used to identify features that have been 
 * defined by a vendor other than 3GPP, it shall contain the vendor ID of the
 * specific vendor in question.
 * If there are multiple feature lists defined by the same vendor, the  
 * Feature-List-ID AVP shall differentiate those lists from one another.
 */
public class SupportedFeatures extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SupportedFeatures.
     */
    public SupportedFeatures() {}

    SupportedFeatures(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the VendorId.
     */
    public diameter.base.VendorId getVendorId() throws NoSuchAttributeException {
        return (diameter.base.VendorId)_data.getContainer().get(diameter.base.BaseAttributeName.VendorId, 0);
    }

    /**
     * Sets the VendorId.
     *
     * @param avp - the attribute value
     */
    public void setVendorId(diameter.base.VendorId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.VendorId, avp.getData(), true);
    }

    /**
     * Gets the FeatureListID.
     */
    public FeatureListID getFeatureListID() throws NoSuchAttributeException {
        return (FeatureListID)_data.getContainer().get(S6a_r11AttributeName.FeatureListID, 0);
    }

    /**
     * Sets the FeatureListID.
     *
     * @param avp - the attribute value
     */
    public void setFeatureListID(FeatureListID avp) {
        _data.getContainer().add(S6a_r11AttributeName.FeatureListID, avp.getData(), true);
    }

    /**
     * Gets the FeatureList.
     */
    public FeatureList getFeatureList() throws NoSuchAttributeException {
        return (FeatureList)_data.getContainer().get(S6a_r11AttributeName.FeatureList, 0);
    }

    /**
     * Sets the FeatureList.
     *
     * @param avp - the attribute value
     */
    public void setFeatureList(FeatureList avp) {
        _data.getContainer().add(S6a_r11AttributeName.FeatureList, avp.getData(), true);
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
        sb.append("    VendorId:");
            try {
                sb.append(getVendorId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    FeatureListID:");
            try {
                sb.append(getFeatureListID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    FeatureList:");
            try {
                sb.append(getFeatureList()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
