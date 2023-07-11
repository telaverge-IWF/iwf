package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The AoC-Subscription-Information AVP (AVP code 2314) is of type Grouped and holds 
 * the subscription and formatting parameters received from HSS.
 */
public class AoCSubscriptionInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AoCSubscriptionInformation.
     */
    public AoCSubscriptionInformation() {}

    AoCSubscriptionInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of AoCService instances.
     */
    public int countAoCService() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.AoCService);
    }

    /**
     * Gets one AoCService.
     *
     * @param index - the index of the attribute to return
     */
    public AoCService getAoCService(int index) throws NoSuchAttributeException {
        return (AoCService)_data.getContainer().get(Ro_r10_transatelAttributeName.AoCService, index);
    }

    /**
     * Adds one AoCService.
     *
     * @param avp - the attribute value
     */
    public void addAoCService(AoCService avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AoCService, avp.getData(), false);
    }

    /**
     * Tests whether there is any AoCFormat.
     */
    public boolean containsAoCFormat() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AoCFormat);
    }

    /**
     * Gets the AoCFormat.
     */
    public AoCFormat getAoCFormat() throws NoSuchAttributeException {
        return (AoCFormat)_data.getContainer().get(Ro_r10_transatelAttributeName.AoCFormat, 0);
    }

    /**
     * Sets the AoCFormat.
     *
     * @param avp - the attribute value
     */
    public void setAoCFormat(AoCFormat avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AoCFormat, avp.getData(), true);
    }

    /**
     * Tests whether there is any PreferredAoCCurrency.
     */
    public boolean containsPreferredAoCCurrency() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.PreferredAoCCurrency);
    }

    /**
     * Gets the PreferredAoCCurrency.
     */
    public PreferredAoCCurrency getPreferredAoCCurrency() throws NoSuchAttributeException {
        return (PreferredAoCCurrency)_data.getContainer().get(Ro_r10_transatelAttributeName.PreferredAoCCurrency, 0);
    }

    /**
     * Sets the PreferredAoCCurrency.
     *
     * @param avp - the attribute value
     */
    public void setPreferredAoCCurrency(PreferredAoCCurrency avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.PreferredAoCCurrency, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        for (int i = 0; i < countAoCService(); ++i) {
            sb.append("    AoCService:");
            try {
                sb.append(getAoCService(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAoCFormat()) {
            sb.append("    AoCFormat:");
            try {
                sb.append(getAoCFormat()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPreferredAoCCurrency()) {
            sb.append("    PreferredAoCCurrency:");
            try {
                sb.append(getPreferredAoCCurrency()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
