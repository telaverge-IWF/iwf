package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Incremental-Cost AVP (AVP code 2062) is of type Grouped and holds the 
 * incremental cost since last AoC interaction for the ongoing session.
 */
public class IncrementalCost extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new IncrementalCost.
     */
    public IncrementalCost() {}

    IncrementalCost(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ValueDigits.
     */
    public ValueDigits getValueDigits() throws NoSuchAttributeException {
        return (ValueDigits)_data.getContainer().get(Ro_r10AttributeName.ValueDigits, 0);
    }

    /**
     * Sets the ValueDigits.
     *
     * @param avp - the attribute value
     */
    public void setValueDigits(ValueDigits avp) {
        _data.getContainer().add(Ro_r10AttributeName.ValueDigits, avp.getData(), true);
    }

    /**
     * Tests whether there is any Exponent.
     */
    public boolean containsExponent() {
        return _data.getContainer().contains(Ro_r10AttributeName.Exponent);
    }

    /**
     * Gets the Exponent.
     */
    public Exponent getExponent() throws NoSuchAttributeException {
        return (Exponent)_data.getContainer().get(Ro_r10AttributeName.Exponent, 0);
    }

    /**
     * Sets the Exponent.
     *
     * @param avp - the attribute value
     */
    public void setExponent(Exponent avp) {
        _data.getContainer().add(Ro_r10AttributeName.Exponent, avp.getData(), true);
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
