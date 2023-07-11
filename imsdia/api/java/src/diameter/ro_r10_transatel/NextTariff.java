package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Next-Tariff AVP (AVP code 2057) is of type Grouped and holds tariff 
 * information. The Tariff is a formula for cost calculation given the 
 * Used-Service-Unit AVP. The calculated cost is given in the Currency-Code AVP.
 *  The formula sums all the rating elements and multiplies the sum by the 
 * Scale-Factor AVP. 
 */
public class NextTariff extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new NextTariff.
     */
    public NextTariff() {}

    NextTariff(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CurrencyCode.
     */
    public boolean containsCurrencyCode() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CurrencyCode);
    }

    /**
     * Gets the CurrencyCode.
     */
    public CurrencyCode getCurrencyCode() throws NoSuchAttributeException {
        return (CurrencyCode)_data.getContainer().get(Ro_r10_transatelAttributeName.CurrencyCode, 0);
    }

    /**
     * Sets the CurrencyCode.
     *
     * @param avp - the attribute value
     */
    public void setCurrencyCode(CurrencyCode avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CurrencyCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any ScaleFactor.
     */
    public boolean containsScaleFactor() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ScaleFactor);
    }

    /**
     * Gets the ScaleFactor.
     */
    public ScaleFactor getScaleFactor() throws NoSuchAttributeException {
        return (ScaleFactor)_data.getContainer().get(Ro_r10_transatelAttributeName.ScaleFactor, 0);
    }

    /**
     * Sets the ScaleFactor.
     *
     * @param avp - the attribute value
     */
    public void setScaleFactor(ScaleFactor avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ScaleFactor, avp.getData(), true);
    }

    /**
     * Returns number of RateElement instances.
     */
    public int countRateElement() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.RateElement);
    }

    /**
     * Gets one RateElement.
     *
     * @param index - the index of the attribute to return
     */
    public RateElement getRateElement(int index) throws NoSuchAttributeException {
        return (RateElement)_data.getContainer().get(Ro_r10_transatelAttributeName.RateElement, index);
    }

    /**
     * Adds one RateElement.
     *
     * @param avp - the attribute value
     */
    public void addRateElement(RateElement avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.RateElement, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCurrencyCode()) {
            sb.append("    CurrencyCode:");
            try {
                sb.append(getCurrencyCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsScaleFactor()) {
            sb.append("    ScaleFactor:");
            try {
                sb.append(getScaleFactor()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRateElement(); ++i) {
            sb.append("    RateElement:");
            try {
                sb.append(getRateElement(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
