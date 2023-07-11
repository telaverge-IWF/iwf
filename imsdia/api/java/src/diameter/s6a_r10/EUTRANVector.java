package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 *The E-UTRAN-Vector AVP is of type Grouped. This AVP contains an E-UTRAN Vector.
 */
public class EUTRANVector extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new EUTRANVector.
     */
    public EUTRANVector() {}

    EUTRANVector(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the RAND.
     */
    public RAND getRAND() throws NoSuchAttributeException {
        return (RAND)_data.getContainer().get(S6a_r10AttributeName.RAND, 0);
    }

    /**
     * Sets the RAND.
     *
     * @param avp - the attribute value
     */
    public void setRAND(RAND avp) {
        _data.getContainer().add(S6a_r10AttributeName.RAND, avp.getData(), true);
    }

    /**
     * Gets the XRES.
     */
    public XRES getXRES() throws NoSuchAttributeException {
        return (XRES)_data.getContainer().get(S6a_r10AttributeName.XRES, 0);
    }

    /**
     * Sets the XRES.
     *
     * @param avp - the attribute value
     */
    public void setXRES(XRES avp) {
        _data.getContainer().add(S6a_r10AttributeName.XRES, avp.getData(), true);
    }

    /**
     * Gets the AUTN.
     */
    public AUTN getAUTN() throws NoSuchAttributeException {
        return (AUTN)_data.getContainer().get(S6a_r10AttributeName.AUTN, 0);
    }

    /**
     * Sets the AUTN.
     *
     * @param avp - the attribute value
     */
    public void setAUTN(AUTN avp) {
        _data.getContainer().add(S6a_r10AttributeName.AUTN, avp.getData(), true);
    }

    /**
     * Gets the KASME.
     */
    public KASME getKASME() throws NoSuchAttributeException {
        return (KASME)_data.getContainer().get(S6a_r10AttributeName.KASME, 0);
    }

    /**
     * Sets the KASME.
     *
     * @param avp - the attribute value
     */
    public void setKASME(KASME avp) {
        _data.getContainer().add(S6a_r10AttributeName.KASME, avp.getData(), true);
    }

    /**
     * Tests whether there is any ItemNumber.
     */
    public boolean containsItemNumber() {
        return _data.getContainer().contains(S6a_r10AttributeName.ItemNumber);
    }

    /**
     * Gets the ItemNumber.
     */
    public ItemNumber getItemNumber() throws NoSuchAttributeException {
        return (ItemNumber)_data.getContainer().get(S6a_r10AttributeName.ItemNumber, 0);
    }

    /**
     * Sets the ItemNumber.
     *
     * @param avp - the attribute value
     */
    public void setItemNumber(ItemNumber avp) {
        _data.getContainer().add(S6a_r10AttributeName.ItemNumber, avp.getData(), true);
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
        sb.append("    RAND:");
            try {
                sb.append(getRAND()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    XRES:");
            try {
                sb.append(getXRES()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AUTN:");
            try {
                sb.append(getAUTN()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    KASME:");
            try {
                sb.append(getKASME()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsItemNumber()) {
            sb.append("    ItemNumber:");
            try {
                sb.append(getItemNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
