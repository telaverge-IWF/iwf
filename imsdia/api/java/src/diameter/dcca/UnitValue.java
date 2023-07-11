package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * Unit-Value AVP is of type Grouped (AVP Code 445) and specifies the units as decimal value.
 * The Unit-Value is a value with an exponent;i.e., Unit-Value = Value-Digits AVP * 10^Exponent.
 * This representation avoids unwanted rounding off.
 */
public class UnitValue extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new UnitValue.
     */
    public UnitValue() {}

    UnitValue(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ValueDigits.
     */
    public ValueDigits getValueDigits() throws NoSuchAttributeException {
        return (ValueDigits)_data.getContainer().get(DccaAttributeName.ValueDigits, 0);
    }

    /**
     * Sets the ValueDigits.
     *
     * @param avp - the attribute value
     */
    public void setValueDigits(ValueDigits avp) {
        _data.getContainer().add(DccaAttributeName.ValueDigits, avp.getData(), true);
    }

    /**
     * Tests whether there is any Exponent.
     */
    public boolean containsExponent() {
        return _data.getContainer().contains(DccaAttributeName.Exponent);
    }

    /**
     * Gets the Exponent.
     */
    public Exponent getExponent() throws NoSuchAttributeException {
        return (Exponent)_data.getContainer().get(DccaAttributeName.Exponent, 0);
    }

    /**
     * Sets the Exponent.
     *
     * @param avp - the attribute value
     */
    public void setExponent(Exponent avp) {
        _data.getContainer().add(DccaAttributeName.Exponent, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    ValueDigits:");
            try {
                sb.append(getValueDigits()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsExponent()) {
            sb.append("    Exponent:");
            try {
                sb.append(getExponent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
