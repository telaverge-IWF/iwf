package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AoC-Cost-Information AVP (AVP code 2053) is of type Grouped and holds 
 * accumulated and incremental cost infromation for the AoC service
 */
public class AoCCostInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AoCCostInformation.
     */
    public AoCCostInformation() {}

    AoCCostInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any AccumulatedCost.
     */
    public boolean containsAccumulatedCost() {
        return _data.getContainer().contains(Ro_r10AttributeName.AccumulatedCost);
    }

    /**
     * Gets the AccumulatedCost.
     */
    public AccumulatedCost getAccumulatedCost() throws NoSuchAttributeException {
        return (AccumulatedCost)_data.getContainer().get(Ro_r10AttributeName.AccumulatedCost, 0);
    }

    /**
     * Sets the AccumulatedCost.
     *
     * @param avp - the attribute value
     */
    public void setAccumulatedCost(AccumulatedCost avp) {
        _data.getContainer().add(Ro_r10AttributeName.AccumulatedCost, avp.getData(), true);
    }

    /**
     * Returns number of IncrementalCost instances.
     */
    public int countIncrementalCost() {
        return _data.getContainer().count(Ro_r10AttributeName.IncrementalCost);
    }

    /**
     * Gets one IncrementalCost.
     *
     * @param index - the index of the attribute to return
     */
    public IncrementalCost getIncrementalCost(int index) throws NoSuchAttributeException {
        return (IncrementalCost)_data.getContainer().get(Ro_r10AttributeName.IncrementalCost, index);
    }

    /**
     * Adds one IncrementalCost.
     *
     * @param avp - the attribute value
     */
    public void addIncrementalCost(IncrementalCost avp) {
        _data.getContainer().add(Ro_r10AttributeName.IncrementalCost, avp.getData(), false);
    }

    /**
     * Tests whether there is any CurrencyCode.
     */
    public boolean containsCurrencyCode() {
        return _data.getContainer().contains(Ro_r10AttributeName.CurrencyCode);
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
        if (containsAccumulatedCost()) {
            sb.append("    AccumulatedCost:");
            try {
                sb.append(getAccumulatedCost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countIncrementalCost(); ++i) {
            sb.append("    IncrementalCost:");
            try {
                sb.append(getIncrementalCost(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
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
