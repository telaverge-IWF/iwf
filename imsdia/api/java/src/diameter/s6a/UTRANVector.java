package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The UTRAN-Vector AVP is of type Grouped. This AVP contains an UMTS Vector. 
 */
public class UTRANVector extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new UTRANVector.
     */
    public UTRANVector() {}

    UTRANVector(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the RAND.
     */
    public RAND getRAND() throws NoSuchAttributeException {
        return (RAND)_data.getContainer().get(S6aAttributeName.RAND, 0);
    }

    /**
     * Sets the RAND.
     *
     * @param avp - the attribute value
     */
    public void setRAND(RAND avp) {
        _data.getContainer().add(S6aAttributeName.RAND, avp.getData(), true);
    }

    /**
     * Gets the XRES.
     */
    public XRES getXRES() throws NoSuchAttributeException {
        return (XRES)_data.getContainer().get(S6aAttributeName.XRES, 0);
    }

    /**
     * Sets the XRES.
     *
     * @param avp - the attribute value
     */
    public void setXRES(XRES avp) {
        _data.getContainer().add(S6aAttributeName.XRES, avp.getData(), true);
    }

    /**
     * Gets the AUTN.
     */
    public AUTN getAUTN() throws NoSuchAttributeException {
        return (AUTN)_data.getContainer().get(S6aAttributeName.AUTN, 0);
    }

    /**
     * Sets the AUTN.
     *
     * @param avp - the attribute value
     */
    public void setAUTN(AUTN avp) {
        _data.getContainer().add(S6aAttributeName.AUTN, avp.getData(), true);
    }

    /**
     * Gets the CK.
     */
    public CK getCK() throws NoSuchAttributeException {
        return (CK)_data.getContainer().get(S6aAttributeName.CK, 0);
    }

    /**
     * Sets the CK.
     *
     * @param avp - the attribute value
     */
    public void setCK(CK avp) {
        _data.getContainer().add(S6aAttributeName.CK, avp.getData(), true);
    }

    /**
     * Gets the IK.
     */
    public IK getIK() throws NoSuchAttributeException {
        return (IK)_data.getContainer().get(S6aAttributeName.IK, 0);
    }

    /**
     * Sets the IK.
     *
     * @param avp - the attribute value
     */
    public void setIK(IK avp) {
        _data.getContainer().add(S6aAttributeName.IK, avp.getData(), true);
    }

    /**
     * Tests whether there is any ItemNumber.
     */
    public boolean containsItemNumber() {
        return _data.getContainer().contains(S6aAttributeName.ItemNumber);
    }

    /**
     * Gets the ItemNumber.
     */
    public ItemNumber getItemNumber() throws NoSuchAttributeException {
        return (ItemNumber)_data.getContainer().get(S6aAttributeName.ItemNumber, 0);
    }

    /**
     * Sets the ItemNumber.
     *
     * @param avp - the attribute value
     */
    public void setItemNumber(ItemNumber avp) {
        _data.getContainer().add(S6aAttributeName.ItemNumber, avp.getData(), true);
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
        sb.append("    CK:");
            try {
                sb.append(getCK()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    IK:");
            try {
                sb.append(getIK()).append('\n');
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
