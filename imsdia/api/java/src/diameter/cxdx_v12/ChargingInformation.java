package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Charging-Information is of type Grouped, and contains the addresses of the charging functions.
 */
public class ChargingInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ChargingInformation.
     */
    public ChargingInformation() {}

    ChargingInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any PrimaryEventChargingFunctionName.
     */
    public boolean containsPrimaryEventChargingFunctionName() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.PrimaryEventChargingFunctionName);
    }

    /**
     * Gets the PrimaryEventChargingFunctionName.
     */
    public PrimaryEventChargingFunctionName getPrimaryEventChargingFunctionName() throws NoSuchAttributeException {
        return (PrimaryEventChargingFunctionName)_data.getContainer().get(Cxdx_v12AttributeName.PrimaryEventChargingFunctionName, 0);
    }

    /**
     * Sets the PrimaryEventChargingFunctionName.
     *
     * @param avp - the attribute value
     */
    public void setPrimaryEventChargingFunctionName(PrimaryEventChargingFunctionName avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.PrimaryEventChargingFunctionName, avp.getData(), true);
    }

    /**
     * Tests whether there is any SecondaryEventChargingFunctionName.
     */
    public boolean containsSecondaryEventChargingFunctionName() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SecondaryEventChargingFunctionName);
    }

    /**
     * Gets the SecondaryEventChargingFunctionName.
     */
    public SecondaryEventChargingFunctionName getSecondaryEventChargingFunctionName() throws NoSuchAttributeException {
        return (SecondaryEventChargingFunctionName)_data.getContainer().get(Cxdx_v12AttributeName.SecondaryEventChargingFunctionName, 0);
    }

    /**
     * Sets the SecondaryEventChargingFunctionName.
     *
     * @param avp - the attribute value
     */
    public void setSecondaryEventChargingFunctionName(SecondaryEventChargingFunctionName avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SecondaryEventChargingFunctionName, avp.getData(), true);
    }

    /**
     * Tests whether there is any PrimaryChargingCollectionFunctionName.
     */
    public boolean containsPrimaryChargingCollectionFunctionName() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.PrimaryChargingCollectionFunctionName);
    }

    /**
     * Gets the PrimaryChargingCollectionFunctionName.
     */
    public PrimaryChargingCollectionFunctionName getPrimaryChargingCollectionFunctionName() throws NoSuchAttributeException {
        return (PrimaryChargingCollectionFunctionName)_data.getContainer().get(Cxdx_v12AttributeName.PrimaryChargingCollectionFunctionName, 0);
    }

    /**
     * Sets the PrimaryChargingCollectionFunctionName.
     *
     * @param avp - the attribute value
     */
    public void setPrimaryChargingCollectionFunctionName(PrimaryChargingCollectionFunctionName avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.PrimaryChargingCollectionFunctionName, avp.getData(), true);
    }

    /**
     * Tests whether there is any SecondaryChargingCollectionFunctionName.
     */
    public boolean containsSecondaryChargingCollectionFunctionName() {
        return _data.getContainer().contains(Cxdx_v12AttributeName.SecondaryChargingCollectionFunctionName);
    }

    /**
     * Gets the SecondaryChargingCollectionFunctionName.
     */
    public SecondaryChargingCollectionFunctionName getSecondaryChargingCollectionFunctionName() throws NoSuchAttributeException {
        return (SecondaryChargingCollectionFunctionName)_data.getContainer().get(Cxdx_v12AttributeName.SecondaryChargingCollectionFunctionName, 0);
    }

    /**
     * Sets the SecondaryChargingCollectionFunctionName.
     *
     * @param avp - the attribute value
     */
    public void setSecondaryChargingCollectionFunctionName(SecondaryChargingCollectionFunctionName avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.SecondaryChargingCollectionFunctionName, avp.getData(), true);
    }

    /**
     * Returns number of extra AVP instances.
     */
    public int countExtra() {
        return _data.getContainer().count(AttributeName.AVP);
    }

    /**
     * Returns number of extra AVP instances that match the given attribute name.
     *
     * @param name - the attribute to count
     */
    public int countExtra(AttributeName name) {
        return _data.getContainer().countExtra(name);
    }

    /**
     * Gets an extra AVP that matches the given attribute name.
     *
     * @param name - the attribute to return
     * @param index - the index of the attribute to return
     */
    public AVP getExtra(AttributeName name, int index) throws NoSuchAttributeException {
        return _data.getContainer().getExtra(name, index);
    }

    /**
     * Adds one extra AVP.
     *
     * @param avp - the attribute value
     */
    public void addExtra(AVP avp) {
        _data.getContainer().add(AttributeName.AVP, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsPrimaryEventChargingFunctionName()) {
            sb.append("    PrimaryEventChargingFunctionName:");
            try {
                sb.append(getPrimaryEventChargingFunctionName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSecondaryEventChargingFunctionName()) {
            sb.append("    SecondaryEventChargingFunctionName:");
            try {
                sb.append(getSecondaryEventChargingFunctionName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPrimaryChargingCollectionFunctionName()) {
            sb.append("    PrimaryChargingCollectionFunctionName:");
            try {
                sb.append(getPrimaryChargingCollectionFunctionName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSecondaryChargingCollectionFunctionName()) {
            sb.append("    SecondaryChargingCollectionFunctionName:");
            try {
                sb.append(getSecondaryChargingCollectionFunctionName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
