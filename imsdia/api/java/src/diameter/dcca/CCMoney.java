package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The CC-Money AVP is of type Grouped and specifies the monetary amount in the given
 * currency.  The Currency-Code AVP SHOULD be included.
 */
public class CCMoney extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CCMoney.
     */
    public CCMoney() {}

    CCMoney(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the UnitValue.
     */
    public UnitValue getUnitValue() throws NoSuchAttributeException {
        return (UnitValue)_data.getContainer().get(DccaAttributeName.UnitValue, 0);
    }

    /**
     * Sets the UnitValue.
     *
     * @param avp - the attribute value
     */
    public void setUnitValue(UnitValue avp) {
        _data.getContainer().add(DccaAttributeName.UnitValue, avp.getData(), true);
    }

    /**
     * Tests whether there is any CurrencyCode.
     */
    public boolean containsCurrencyCode() {
        return _data.getContainer().contains(DccaAttributeName.CurrencyCode);
    }

    /**
     * Gets the CurrencyCode.
     */
    public CurrencyCode getCurrencyCode() throws NoSuchAttributeException {
        return (CurrencyCode)_data.getContainer().get(DccaAttributeName.CurrencyCode, 0);
    }

    /**
     * Sets the CurrencyCode.
     *
     * @param avp - the attribute value
     */
    public void setCurrencyCode(CurrencyCode avp) {
        _data.getContainer().add(DccaAttributeName.CurrencyCode, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    UnitValue:");
            try {
                sb.append(getUnitValue()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsCurrencyCode()) {
            sb.append("    CurrencyCode:");
            try {
                sb.append(getCurrencyCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
