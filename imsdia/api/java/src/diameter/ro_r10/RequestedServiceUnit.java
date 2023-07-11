package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Requested-Service-Unit AVP (AVP Code 437) is of type Grouped and contains the amount of 
 * requested units specified by the Diameter credit-control client. A server is not required to
 * implement all the unit types, and it must treat unknown or unsupported unit types as invalid AVPs.
 */
public class RequestedServiceUnit extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RequestedServiceUnit.
     */
    public RequestedServiceUnit() {}

    RequestedServiceUnit(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CCTime.
     */
    public boolean containsCCTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.CCTime);
    }

    /**
     * Gets the CCTime.
     */
    public CCTime getCCTime() throws NoSuchAttributeException {
        return (CCTime)_data.getContainer().get(Ro_r10AttributeName.CCTime, 0);
    }

    /**
     * Sets the CCTime.
     *
     * @param avp - the attribute value
     */
    public void setCCTime(CCTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.CCTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCMoney.
     */
    public boolean containsCCMoney() {
        return _data.getContainer().contains(Ro_r10AttributeName.CCMoney);
    }

    /**
     * Gets the CCMoney.
     */
    public CCMoney getCCMoney() throws NoSuchAttributeException {
        return (CCMoney)_data.getContainer().get(Ro_r10AttributeName.CCMoney, 0);
    }

    /**
     * Sets the CCMoney.
     *
     * @param avp - the attribute value
     */
    public void setCCMoney(CCMoney avp) {
        _data.getContainer().add(Ro_r10AttributeName.CCMoney, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCTotalOctets.
     */
    public boolean containsCCTotalOctets() {
        return _data.getContainer().contains(Ro_r10AttributeName.CCTotalOctets);
    }

    /**
     * Gets the CCTotalOctets.
     */
    public CCTotalOctets getCCTotalOctets() throws NoSuchAttributeException {
        return (CCTotalOctets)_data.getContainer().get(Ro_r10AttributeName.CCTotalOctets, 0);
    }

    /**
     * Sets the CCTotalOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCTotalOctets(CCTotalOctets avp) {
        _data.getContainer().add(Ro_r10AttributeName.CCTotalOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCInputOctets.
     */
    public boolean containsCCInputOctets() {
        return _data.getContainer().contains(Ro_r10AttributeName.CCInputOctets);
    }

    /**
     * Gets the CCInputOctets.
     */
    public CCInputOctets getCCInputOctets() throws NoSuchAttributeException {
        return (CCInputOctets)_data.getContainer().get(Ro_r10AttributeName.CCInputOctets, 0);
    }

    /**
     * Sets the CCInputOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCInputOctets(CCInputOctets avp) {
        _data.getContainer().add(Ro_r10AttributeName.CCInputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCOutputOctets.
     */
    public boolean containsCCOutputOctets() {
        return _data.getContainer().contains(Ro_r10AttributeName.CCOutputOctets);
    }

    /**
     * Gets the CCOutputOctets.
     */
    public CCOutputOctets getCCOutputOctets() throws NoSuchAttributeException {
        return (CCOutputOctets)_data.getContainer().get(Ro_r10AttributeName.CCOutputOctets, 0);
    }

    /**
     * Sets the CCOutputOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCOutputOctets(CCOutputOctets avp) {
        _data.getContainer().add(Ro_r10AttributeName.CCOutputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCServiceSpecificUnits.
     */
    public boolean containsCCServiceSpecificUnits() {
        return _data.getContainer().contains(Ro_r10AttributeName.CCServiceSpecificUnits);
    }

    /**
     * Gets the CCServiceSpecificUnits.
     */
    public CCServiceSpecificUnits getCCServiceSpecificUnits() throws NoSuchAttributeException {
        return (CCServiceSpecificUnits)_data.getContainer().get(Ro_r10AttributeName.CCServiceSpecificUnits, 0);
    }

    /**
     * Sets the CCServiceSpecificUnits.
     *
     * @param avp - the attribute value
     */
    public void setCCServiceSpecificUnits(CCServiceSpecificUnits avp) {
        _data.getContainer().add(Ro_r10AttributeName.CCServiceSpecificUnits, avp.getData(), true);
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
        if (containsCCTime()) {
            sb.append("    CCTime:");
            try {
                sb.append(getCCTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCMoney()) {
            sb.append("    CCMoney:");
            try {
                sb.append(getCCMoney()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCTotalOctets()) {
            sb.append("    CCTotalOctets:");
            try {
                sb.append(getCCTotalOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCInputOctets()) {
            sb.append("    CCInputOctets:");
            try {
                sb.append(getCCInputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCOutputOctets()) {
            sb.append("    CCOutputOctets:");
            try {
                sb.append(getCCOutputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCServiceSpecificUnits()) {
            sb.append("    CCServiceSpecificUnits:");
            try {
                sb.append(getCCServiceSpecificUnits()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
