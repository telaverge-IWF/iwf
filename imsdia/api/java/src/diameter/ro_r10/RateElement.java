package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
  * The Rate-Element AVP (AVP code 2058) is of type Grouped and holds simple 
  * rate element of one dimension.
  */
public class RateElement extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RateElement.
     */
    public RateElement() {}

    RateElement(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the CCUnitType.
     */
    public CCUnitType getCCUnitType() throws NoSuchAttributeException {
        return (CCUnitType)_data.getContainer().get(Ro_r10AttributeName.CCUnitType, 0);
    }

    /**
     * Sets the CCUnitType.
     *
     * @param avp - the attribute value
     */
    public void setCCUnitType(CCUnitType avp) {
        _data.getContainer().add(Ro_r10AttributeName.CCUnitType, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReasonCode.
     */
    public boolean containsReasonCode() {
        return _data.getContainer().contains(Ro_r10AttributeName.ReasonCode);
    }

    /**
     * Gets the ReasonCode.
     */
    public ReasonCode getReasonCode() throws NoSuchAttributeException {
        return (ReasonCode)_data.getContainer().get(Ro_r10AttributeName.ReasonCode, 0);
    }

    /**
     * Sets the ReasonCode.
     *
     * @param avp - the attribute value
     */
    public void setReasonCode(ReasonCode avp) {
        _data.getContainer().add(Ro_r10AttributeName.ReasonCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any UnitValue.
     */
    public boolean containsUnitValue() {
        return _data.getContainer().contains(Ro_r10AttributeName.UnitValue);
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
     * Tests whether there is any UnitCost.
     */
    public boolean containsUnitCost() {
        return _data.getContainer().contains(Ro_r10AttributeName.UnitCost);
    }

    /**
     * Gets the UnitCost.
     */
    public UnitCost getUnitCost() throws NoSuchAttributeException {
        return (UnitCost)_data.getContainer().get(Ro_r10AttributeName.UnitCost, 0);
    }

    /**
     * Sets the UnitCost.
     *
     * @param avp - the attribute value
     */
    public void setUnitCost(UnitCost avp) {
        _data.getContainer().add(Ro_r10AttributeName.UnitCost, avp.getData(), true);
    }

    /**
     * Tests whether there is any UnitQuotaThreshold.
     */
    public boolean containsUnitQuotaThreshold() {
        return _data.getContainer().contains(Ro_r10AttributeName.UnitQuotaThreshold);
    }

    /**
     * Gets the UnitQuotaThreshold.
     */
    public UnitQuotaThreshold getUnitQuotaThreshold() throws NoSuchAttributeException {
        return (UnitQuotaThreshold)_data.getContainer().get(Ro_r10AttributeName.UnitQuotaThreshold, 0);
    }

    /**
     * Sets the UnitQuotaThreshold.
     *
     * @param avp - the attribute value
     */
    public void setUnitQuotaThreshold(UnitQuotaThreshold avp) {
        _data.getContainer().add(Ro_r10AttributeName.UnitQuotaThreshold, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    CCUnitType:");
            try {
                sb.append(getCCUnitType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsReasonCode()) {
            sb.append("    ReasonCode:");
            try {
                sb.append(getReasonCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUnitValue()) {
            sb.append("    UnitValue:");
            try {
                sb.append(getUnitValue()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUnitCost()) {
            sb.append("    UnitCost:");
            try {
                sb.append(getUnitCost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUnitQuotaThreshold()) {
            sb.append("    UnitQuotaThreshold:");
            try {
                sb.append(getUnitQuotaThreshold()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
