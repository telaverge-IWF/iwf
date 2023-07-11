package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Envelope AVP (AVP code 1266) is a grouped AVP which reports the 
 * start and end time of one time envelope using the Envelope-Start-Time 
 * and Envelope-End-Time AVPs. Further details of its usage are described 
 * in clause 6.5.6 and 6.5.7.
 */
public class Envelope extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new Envelope.
     */
    public Envelope() {}

    Envelope(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the EnvelopeStartTime.
     */
    public EnvelopeStartTime getEnvelopeStartTime() throws NoSuchAttributeException {
        return (EnvelopeStartTime)_data.getContainer().get(Ro_r10_transatelAttributeName.EnvelopeStartTime, 0);
    }

    /**
     * Sets the EnvelopeStartTime.
     *
     * @param avp - the attribute value
     */
    public void setEnvelopeStartTime(EnvelopeStartTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.EnvelopeStartTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any EnvelopeEndTime.
     */
    public boolean containsEnvelopeEndTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.EnvelopeEndTime);
    }

    /**
     * Gets the EnvelopeEndTime.
     */
    public EnvelopeEndTime getEnvelopeEndTime() throws NoSuchAttributeException {
        return (EnvelopeEndTime)_data.getContainer().get(Ro_r10_transatelAttributeName.EnvelopeEndTime, 0);
    }

    /**
     * Sets the EnvelopeEndTime.
     *
     * @param avp - the attribute value
     */
    public void setEnvelopeEndTime(EnvelopeEndTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.EnvelopeEndTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCTotalOctets.
     */
    public boolean containsCCTotalOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCTotalOctets);
    }

    /**
     * Gets the CCTotalOctets.
     */
    public CCTotalOctets getCCTotalOctets() throws NoSuchAttributeException {
        return (CCTotalOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.CCTotalOctets, 0);
    }

    /**
     * Sets the CCTotalOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCTotalOctets(CCTotalOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCTotalOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCInputOctets.
     */
    public boolean containsCCInputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCInputOctets);
    }

    /**
     * Gets the CCInputOctets.
     */
    public CCInputOctets getCCInputOctets() throws NoSuchAttributeException {
        return (CCInputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.CCInputOctets, 0);
    }

    /**
     * Sets the CCInputOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCInputOctets(CCInputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCInputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCOutputOctets.
     */
    public boolean containsCCOutputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCOutputOctets);
    }

    /**
     * Gets the CCOutputOctets.
     */
    public CCOutputOctets getCCOutputOctets() throws NoSuchAttributeException {
        return (CCOutputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.CCOutputOctets, 0);
    }

    /**
     * Sets the CCOutputOctets.
     *
     * @param avp - the attribute value
     */
    public void setCCOutputOctets(CCOutputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCOutputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCServiceSpecificUnits.
     */
    public boolean containsCCServiceSpecificUnits() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.CCServiceSpecificUnits);
    }

    /**
     * Gets the CCServiceSpecificUnits.
     */
    public CCServiceSpecificUnits getCCServiceSpecificUnits() throws NoSuchAttributeException {
        return (CCServiceSpecificUnits)_data.getContainer().get(Ro_r10_transatelAttributeName.CCServiceSpecificUnits, 0);
    }

    /**
     * Sets the CCServiceSpecificUnits.
     *
     * @param avp - the attribute value
     */
    public void setCCServiceSpecificUnits(CCServiceSpecificUnits avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.CCServiceSpecificUnits, avp.getData(), true);
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
        sb.append("    EnvelopeStartTime:");
            try {
                sb.append(getEnvelopeStartTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsEnvelopeEndTime()) {
            sb.append("    EnvelopeEndTime:");
            try {
                sb.append(getEnvelopeEndTime()).append('\n');
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
