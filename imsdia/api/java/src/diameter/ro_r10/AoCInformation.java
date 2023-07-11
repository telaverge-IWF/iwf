package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AoC-Information AVP (AVP code 2054) is of type Grouped that includes 
 * the information required for advice of charge.
 */
public class AoCInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AoCInformation.
     */
    public AoCInformation() {}

    AoCInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any AoCCostInformation.
     */
    public boolean containsAoCCostInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.AoCCostInformation);
    }

    /**
     * Gets the AoCCostInformation.
     */
    public AoCCostInformation getAoCCostInformation() throws NoSuchAttributeException {
        return (AoCCostInformation)_data.getContainer().get(Ro_r10AttributeName.AoCCostInformation, 0);
    }

    /**
     * Sets the AoCCostInformation.
     *
     * @param avp - the attribute value
     */
    public void setAoCCostInformation(AoCCostInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.AoCCostInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any TariffInformation.
     */
    public boolean containsTariffInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.TariffInformation);
    }

    /**
     * Gets the TariffInformation.
     */
    public TariffInformation getTariffInformation() throws NoSuchAttributeException {
        return (TariffInformation)_data.getContainer().get(Ro_r10AttributeName.TariffInformation, 0);
    }

    /**
     * Sets the TariffInformation.
     *
     * @param avp - the attribute value
     */
    public void setTariffInformation(TariffInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.TariffInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any AoCSubscriptionInformation.
     */
    public boolean containsAoCSubscriptionInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.AoCSubscriptionInformation);
    }

    /**
     * Gets the AoCSubscriptionInformation.
     */
    public AoCSubscriptionInformation getAoCSubscriptionInformation() throws NoSuchAttributeException {
        return (AoCSubscriptionInformation)_data.getContainer().get(Ro_r10AttributeName.AoCSubscriptionInformation, 0);
    }

    /**
     * Sets the AoCSubscriptionInformation.
     *
     * @param avp - the attribute value
     */
    public void setAoCSubscriptionInformation(AoCSubscriptionInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.AoCSubscriptionInformation, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsAoCCostInformation()) {
            sb.append("    AoCCostInformation:");
            try {
                sb.append(getAoCCostInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTariffInformation()) {
            sb.append("    TariffInformation:");
            try {
                sb.append(getTariffInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAoCSubscriptionInformation()) {
            sb.append("    AoCSubscriptionInformation:");
            try {
                sb.append(getAoCSubscriptionInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
