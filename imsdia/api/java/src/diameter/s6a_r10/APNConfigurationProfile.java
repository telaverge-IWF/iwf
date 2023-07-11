package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The APN-Configuration AVP is of type Grouped. It contains the information related to the
 * user subscribed APN configurations for EPS and the context-identifier corresponding to
 * the default APN configuration. 
 */
public class APNConfigurationProfile extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new APNConfigurationProfile.
     */
    public APNConfigurationProfile() {}

    APNConfigurationProfile(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ContextIdentifier.
     */
    public ContextIdentifier getContextIdentifier() throws NoSuchAttributeException {
        return (ContextIdentifier)_data.getContainer().get(S6a_r10AttributeName.ContextIdentifier, 0);
    }

    /**
     * Sets the ContextIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setContextIdentifier(ContextIdentifier avp) {
        _data.getContainer().add(S6a_r10AttributeName.ContextIdentifier, avp.getData(), true);
    }

    /**
     * Gets the AllAPNConfigurationsIncludedIndicator.
     */
    public AllAPNConfigurationsIncludedIndicator getAllAPNConfigurationsIncludedIndicator() throws NoSuchAttributeException {
        return (AllAPNConfigurationsIncludedIndicator)_data.getContainer().get(S6a_r10AttributeName.AllAPNConfigurationsIncludedIndicator, 0);
    }

    /**
     * Sets the AllAPNConfigurationsIncludedIndicator.
     *
     * @param avp - the attribute value
     */
    public void setAllAPNConfigurationsIncludedIndicator(AllAPNConfigurationsIncludedIndicator avp) {
        _data.getContainer().add(S6a_r10AttributeName.AllAPNConfigurationsIncludedIndicator, avp.getData(), true);
    }

    /**
     * Returns number of APNConfiguration instances.
     */
    public int countAPNConfiguration() {
        return _data.getContainer().count(S6a_r10AttributeName.APNConfiguration);
    }

    /**
     * Gets one APNConfiguration.
     *
     * @param index - the index of the attribute to return
     */
    public APNConfiguration getAPNConfiguration(int index) throws NoSuchAttributeException {
        return (APNConfiguration)_data.getContainer().get(S6a_r10AttributeName.APNConfiguration, index);
    }

    /**
     * Adds one APNConfiguration.
     *
     * @param avp - the attribute value
     */
    public void addAPNConfiguration(APNConfiguration avp) {
        _data.getContainer().add(S6a_r10AttributeName.APNConfiguration, avp.getData(), false);
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
        sb.append("    ContextIdentifier:");
            try {
                sb.append(getContextIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AllAPNConfigurationsIncludedIndicator:");
            try {
                sb.append(getAllAPNConfigurationsIncludedIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        for (int i = 0; i < countAPNConfiguration(); ++i) {
            sb.append("    APNConfiguration:");
            try {
                sb.append(getAPNConfiguration(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
