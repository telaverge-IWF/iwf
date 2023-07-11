package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Service-Information AVP is of type Grouped. Its purpose is to allow the transmission of
 * additional 3GPP service specific information elements which are not described in the 32.299V7.1
 */
public class ServiceInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ServiceInformation.
     */
    public ServiceInformation() {}

    ServiceInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of SubscriptionId instances.
     */
    public int countSubscriptionId() {
        return _data.getContainer().count(Ro_r10AttributeName.SubscriptionId);
    }

    /**
     * Gets one SubscriptionId.
     *
     * @param index - the index of the attribute to return
     */
    public SubscriptionId getSubscriptionId(int index) throws NoSuchAttributeException {
        return (SubscriptionId)_data.getContainer().get(Ro_r10AttributeName.SubscriptionId, index);
    }

    /**
     * Adds one SubscriptionId.
     *
     * @param avp - the attribute value
     */
    public void addSubscriptionId(SubscriptionId avp) {
        _data.getContainer().add(Ro_r10AttributeName.SubscriptionId, avp.getData(), false);
    }

    /**
     * Tests whether there is any AoCInformation.
     */
    public boolean containsAoCInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.AoCInformation);
    }

    /**
     * Gets the AoCInformation.
     */
    public AoCInformation getAoCInformation() throws NoSuchAttributeException {
        return (AoCInformation)_data.getContainer().get(Ro_r10AttributeName.AoCInformation, 0);
    }

    /**
     * Sets the AoCInformation.
     *
     * @param avp - the attribute value
     */
    public void setAoCInformation(AoCInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.AoCInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any PSInformation.
     */
    public boolean containsPSInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.PSInformation);
    }

    /**
     * Gets the PSInformation.
     */
    public PSInformation getPSInformation() throws NoSuchAttributeException {
        return (PSInformation)_data.getContainer().get(Ro_r10AttributeName.PSInformation, 0);
    }

    /**
     * Sets the PSInformation.
     *
     * @param avp - the attribute value
     */
    public void setPSInformation(PSInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.PSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any WLANInformation.
     */
    public boolean containsWLANInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.WLANInformation);
    }

    /**
     * Gets the WLANInformation.
     */
    public WLANInformation getWLANInformation() throws NoSuchAttributeException {
        return (WLANInformation)_data.getContainer().get(Ro_r10AttributeName.WLANInformation, 0);
    }

    /**
     * Sets the WLANInformation.
     *
     * @param avp - the attribute value
     */
    public void setWLANInformation(WLANInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.WLANInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any IMSInformation.
     */
    public boolean containsIMSInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.IMSInformation);
    }

    /**
     * Gets the IMSInformation.
     */
    public IMSInformation getIMSInformation() throws NoSuchAttributeException {
        return (IMSInformation)_data.getContainer().get(Ro_r10AttributeName.IMSInformation, 0);
    }

    /**
     * Sets the IMSInformation.
     *
     * @param avp - the attribute value
     */
    public void setIMSInformation(IMSInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.IMSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any MMSInformation.
     */
    public boolean containsMMSInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.MMSInformation);
    }

    /**
     * Gets the MMSInformation.
     */
    public MMSInformation getMMSInformation() throws NoSuchAttributeException {
        return (MMSInformation)_data.getContainer().get(Ro_r10AttributeName.MMSInformation, 0);
    }

    /**
     * Sets the MMSInformation.
     *
     * @param avp - the attribute value
     */
    public void setMMSInformation(MMSInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.MMSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any LCSInformation.
     */
    public boolean containsLCSInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.LCSInformation);
    }

    /**
     * Gets the LCSInformation.
     */
    public LCSInformation getLCSInformation() throws NoSuchAttributeException {
        return (LCSInformation)_data.getContainer().get(Ro_r10AttributeName.LCSInformation, 0);
    }

    /**
     * Sets the LCSInformation.
     *
     * @param avp - the attribute value
     */
    public void setLCSInformation(LCSInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.LCSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any PoCInformation.
     */
    public boolean containsPoCInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.PoCInformation);
    }

    /**
     * Gets the PoCInformation.
     */
    public PoCInformation getPoCInformation() throws NoSuchAttributeException {
        return (PoCInformation)_data.getContainer().get(Ro_r10AttributeName.PoCInformation, 0);
    }

    /**
     * Sets the PoCInformation.
     *
     * @param avp - the attribute value
     */
    public void setPoCInformation(PoCInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.PoCInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any MBMSInformation.
     */
    public boolean containsMBMSInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.MBMSInformation);
    }

    /**
     * Gets the MBMSInformation.
     */
    public MBMSInformation getMBMSInformation() throws NoSuchAttributeException {
        return (MBMSInformation)_data.getContainer().get(Ro_r10AttributeName.MBMSInformation, 0);
    }

    /**
     * Sets the MBMSInformation.
     *
     * @param avp - the attribute value
     */
    public void setMBMSInformation(MBMSInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.MBMSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any SMSInformation.
     */
    public boolean containsSMSInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.SMSInformation);
    }

    /**
     * Gets the SMSInformation.
     */
    public SMSInformation getSMSInformation() throws NoSuchAttributeException {
        return (SMSInformation)_data.getContainer().get(Ro_r10AttributeName.SMSInformation, 0);
    }

    /**
     * Sets the SMSInformation.
     *
     * @param avp - the attribute value
     */
    public void setSMSInformation(SMSInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.SMSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any MMTelInformation.
     */
    public boolean containsMMTelInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.MMTelInformation);
    }

    /**
     * Gets the MMTelInformation.
     */
    public MMTelInformation getMMTelInformation() throws NoSuchAttributeException {
        return (MMTelInformation)_data.getContainer().get(Ro_r10AttributeName.MMTelInformation, 0);
    }

    /**
     * Sets the MMTelInformation.
     *
     * @param avp - the attribute value
     */
    public void setMMTelInformation(MMTelInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.MMTelInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceGenericInformation.
     */
    public boolean containsServiceGenericInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServiceGenericInformation);
    }

    /**
     * Gets the ServiceGenericInformation.
     */
    public ServiceGenericInformation getServiceGenericInformation() throws NoSuchAttributeException {
        return (ServiceGenericInformation)_data.getContainer().get(Ro_r10AttributeName.ServiceGenericInformation, 0);
    }

    /**
     * Sets the ServiceGenericInformation.
     *
     * @param avp - the attribute value
     */
    public void setServiceGenericInformation(ServiceGenericInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceGenericInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any IMInformation.
     */
    public boolean containsIMInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.IMInformation);
    }

    /**
     * Gets the IMInformation.
     */
    public IMInformation getIMInformation() throws NoSuchAttributeException {
        return (IMInformation)_data.getContainer().get(Ro_r10AttributeName.IMInformation, 0);
    }

    /**
     * Sets the IMInformation.
     *
     * @param avp - the attribute value
     */
    public void setIMInformation(IMInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.IMInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any DCDInformation.
     */
    public boolean containsDCDInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.DCDInformation);
    }

    /**
     * Gets the DCDInformation.
     */
    public DCDInformation getDCDInformation() throws NoSuchAttributeException {
        return (DCDInformation)_data.getContainer().get(Ro_r10AttributeName.DCDInformation, 0);
    }

    /**
     * Sets the DCDInformation.
     *
     * @param avp - the attribute value
     */
    public void setDCDInformation(DCDInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.DCDInformation, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        for (int i = 0; i < countSubscriptionId(); ++i) {
            sb.append("    SubscriptionId:");
            try {
                sb.append(getSubscriptionId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAoCInformation()) {
            sb.append("    AoCInformation:");
            try {
                sb.append(getAoCInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPSInformation()) {
            sb.append("    PSInformation:");
            try {
                sb.append(getPSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsWLANInformation()) {
            sb.append("    WLANInformation:");
            try {
                sb.append(getWLANInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIMSInformation()) {
            sb.append("    IMSInformation:");
            try {
                sb.append(getIMSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMMSInformation()) {
            sb.append("    MMSInformation:");
            try {
                sb.append(getMMSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsLCSInformation()) {
            sb.append("    LCSInformation:");
            try {
                sb.append(getLCSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPoCInformation()) {
            sb.append("    PoCInformation:");
            try {
                sb.append(getPoCInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMBMSInformation()) {
            sb.append("    MBMSInformation:");
            try {
                sb.append(getMBMSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSMSInformation()) {
            sb.append("    SMSInformation:");
            try {
                sb.append(getSMSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMMTelInformation()) {
            sb.append("    MMTelInformation:");
            try {
                sb.append(getMMTelInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceGenericInformation()) {
            sb.append("    ServiceGenericInformation:");
            try {
                sb.append(getServiceGenericInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIMInformation()) {
            sb.append("    IMInformation:");
            try {
                sb.append(getIMInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDCDInformation()) {
            sb.append("    DCDInformation:");
            try {
                sb.append(getDCDInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
