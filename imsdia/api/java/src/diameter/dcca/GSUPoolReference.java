package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The G-S-U-Pool-Reference AVP (AVP Code 457) is of type Grouped. It is used
 * in the Credit-Control-Answer message,and associates the Granted-Service-Unit
 * AVP within which it appears with a credit pool within the session.
 */
public class GSUPoolReference extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new GSUPoolReference.
     */
    public GSUPoolReference() {}

    GSUPoolReference(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the GSUPoolIdentifier.
     */
    public GSUPoolIdentifier getGSUPoolIdentifier() throws NoSuchAttributeException {
        return (GSUPoolIdentifier)_data.getContainer().get(DccaAttributeName.GSUPoolIdentifier, 0);
    }

    /**
     * Sets the GSUPoolIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setGSUPoolIdentifier(GSUPoolIdentifier avp) {
        _data.getContainer().add(DccaAttributeName.GSUPoolIdentifier, avp.getData(), true);
    }

    /**
     * Gets the CCUnitType.
     */
    public CCUnitType getCCUnitType() throws NoSuchAttributeException {
        return (CCUnitType)_data.getContainer().get(DccaAttributeName.CCUnitType, 0);
    }

    /**
     * Sets the CCUnitType.
     *
     * @param avp - the attribute value
     */
    public void setCCUnitType(CCUnitType avp) {
        _data.getContainer().add(DccaAttributeName.CCUnitType, avp.getData(), true);
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


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    GSUPoolIdentifier:");
            try {
                sb.append(getGSUPoolIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CCUnitType:");
            try {
                sb.append(getCCUnitType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    UnitValue:");
            try {
                sb.append(getUnitValue()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        return sb.append('}').toString();
    }
}
