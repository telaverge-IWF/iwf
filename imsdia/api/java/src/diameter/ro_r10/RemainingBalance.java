package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Remaining-Balance AVP (AVPcode 2021) is of type Grouped and provides 
 * information about the remaining account balance of the subscriber.
 */
public class RemainingBalance extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RemainingBalance.
     */
    public RemainingBalance() {}

    RemainingBalance(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the UnitValue.
     */
    public UnitValue getUnitValue() throws NoSuchAttributeException {
        return (UnitValue)_data.getContainer().get(Ro_r10AttributeName.UnitValue, 0);
    }

    /**
     * Sets the UnitValue.
     *
     * @param avp - the attribute value
     */
    public void setUnitValue(UnitValue avp) {
        _data.getContainer().add(Ro_r10AttributeName.UnitValue, avp.getData(), true);
    }

    /**
     * Gets the CurrencyCode.
     */
    public CurrencyCode getCurrencyCode() throws NoSuchAttributeException {
        return (CurrencyCode)_data.getContainer().get(Ro_r10AttributeName.CurrencyCode, 0);
    }

    /**
     * Sets the CurrencyCode.
     *
     * @param avp - the attribute value
     */
    public void setCurrencyCode(CurrencyCode avp) {
        _data.getContainer().add(Ro_r10AttributeName.CurrencyCode, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    UnitValue:");
            try {
                sb.append(getUnitValue()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CurrencyCode:");
            try {
                sb.append(getCurrencyCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        return sb.append('}').toString();
    }
}
