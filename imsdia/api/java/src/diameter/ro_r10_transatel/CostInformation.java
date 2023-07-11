package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Cost-Information AVP is of type Grouped, and it is used to return the cost information
 * of a service, which the credit-control client can transfer transparently to the end user. 
 *  When the Requested-Action AVP with value PRICE_ENQUIRY is included in the
 * Credit-Control-Request command, the Cost-Information AVP sent in the succeeding 
 * Credit-Control-Answer command contains the cost estimation of the requested service, without
 * any reservation being made.
 *  The Cost-Information AVP included in the Credit-Control-Answer command with the CC-Request-Type
 * set to UPDATE_REQUEST contains the accumulated cost estimation for the session, without taking any
 * credit reservation into account.
 *  The Cost-Information AVP included in the Credit-Control-Answer command with the CC-Request-Type
 * set to EVENT_REQUEST or TERMINATION_REQUEST contains the estimated total cost for the requested service.
 */
public class CostInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CostInformation.
     */
    public CostInformation() {}

    CostInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the UnitValue.
     */
    public UnitValue getUnitValue() throws NoSuchAttributeException {
        return (UnitValue)_data.getContainer().get(Ro_r10_transatelAttributeName.UnitValue, 0);
    }

    /**
     * Sets the UnitValue.
     *
     * @param avp - the attribute value
     */
    public void setUnitValue(UnitValue avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.UnitValue, avp.getData(), true);
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
     * Tests whether there is any CostUnit.
     */
    public boolean containsCostUnit() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CostUnit);
    }

    /**
     * Gets the CostUnit.
     */
    public CostUnit getCostUnit() throws NoSuchAttributeException {
        return (CostUnit)_data.getContainer().get(Ro_r10_transatelAttributeName.CostUnit, 0);
    }

    /**
     * Sets the CostUnit.
     *
     * @param avp - the attribute value
     */
    public void setCostUnit(CostUnit avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CostUnit, avp.getData(), true);
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
        if (containsCostUnit()) {
            sb.append("    CostUnit:");
            try {
                sb.append(getCostUnit()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
