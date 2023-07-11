package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Tariff-Information AVP (AVP code 2060) is of type Grouped and holds a 
 * tariff definition either from the local provider or from 3rd party provider
 */
public class TariffInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TariffInformation.
     */
    public TariffInformation() {}

    TariffInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the CurrentTariff.
     */
    public CurrentTariff getCurrentTariff() throws NoSuchAttributeException {
        return (CurrentTariff)_data.getContainer().get(Ro_r10AttributeName.CurrentTariff, 0);
    }

    /**
     * Sets the CurrentTariff.
     *
     * @param avp - the attribute value
     */
    public void setCurrentTariff(CurrentTariff avp) {
        _data.getContainer().add(Ro_r10AttributeName.CurrentTariff, avp.getData(), true);
    }

    /**
     * Tests whether there is any TariffTimeChange.
     */
    public boolean containsTariffTimeChange() {
        return _data.getContainer().contains(Ro_r10AttributeName.TariffTimeChange);
    }

    /**
     * Gets the TariffTimeChange.
     */
    public TariffTimeChange getTariffTimeChange() throws NoSuchAttributeException {
        return (TariffTimeChange)_data.getContainer().get(Ro_r10AttributeName.TariffTimeChange, 0);
    }

    /**
     * Sets the TariffTimeChange.
     *
     * @param avp - the attribute value
     */
    public void setTariffTimeChange(TariffTimeChange avp) {
        _data.getContainer().add(Ro_r10AttributeName.TariffTimeChange, avp.getData(), true);
    }

    /**
     * Tests whether there is any NextTariff.
     */
    public boolean containsNextTariff() {
        return _data.getContainer().contains(Ro_r10AttributeName.NextTariff);
    }

    /**
     * Gets the NextTariff.
     */
    public NextTariff getNextTariff() throws NoSuchAttributeException {
        return (NextTariff)_data.getContainer().get(Ro_r10AttributeName.NextTariff, 0);
    }

    /**
     * Sets the NextTariff.
     *
     * @param avp - the attribute value
     */
    public void setNextTariff(NextTariff avp) {
        _data.getContainer().add(Ro_r10AttributeName.NextTariff, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    CurrentTariff:");
            try {
                sb.append(getCurrentTariff()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsTariffTimeChange()) {
            sb.append("    TariffTimeChange:");
            try {
                sb.append(getTariffTimeChange()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNextTariff()) {
            sb.append("    NextTariff:");
            try {
                sb.append(getNextTariff()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
