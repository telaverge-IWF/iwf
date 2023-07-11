package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * MBMS-Information AVP is of type Grouped . Its purpose is to allow the transmission of additional 
 * MBMS service specific information elements.
 */
public class MBMSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MBMSInformation.
     */
    public MBMSInformation() {}

    MBMSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any TMGI.
     */
    public boolean containsTMGI() {
        return _data.getContainer().contains(Ro_r10AttributeName.TMGI);
    }

    /**
     * Gets the TMGI.
     */
    public TMGI getTMGI() throws NoSuchAttributeException {
        return (TMGI)_data.getContainer().get(Ro_r10AttributeName.TMGI, 0);
    }

    /**
     * Sets the TMGI.
     *
     * @param avp - the attribute value
     */
    public void setTMGI(TMGI avp) {
        _data.getContainer().add(Ro_r10AttributeName.TMGI, avp.getData(), true);
    }

    /**
     * Tests whether there is any MBMSServiceType.
     */
    public boolean containsMBMSServiceType() {
        return _data.getContainer().contains(Ro_r10AttributeName.MBMSServiceType);
    }

    /**
     * Gets the MBMSServiceType.
     */
    public MBMSServiceType getMBMSServiceType() throws NoSuchAttributeException {
        return (MBMSServiceType)_data.getContainer().get(Ro_r10AttributeName.MBMSServiceType, 0);
    }

    /**
     * Sets the MBMSServiceType.
     *
     * @param avp - the attribute value
     */
    public void setMBMSServiceType(MBMSServiceType avp) {
        _data.getContainer().add(Ro_r10AttributeName.MBMSServiceType, avp.getData(), true);
    }

    /**
     * Tests whether there is any MBMSUserServiceType.
     */
    public boolean containsMBMSUserServiceType() {
        return _data.getContainer().contains(Ro_r10AttributeName.MBMSUserServiceType);
    }

    /**
     * Gets the MBMSUserServiceType.
     */
    public MBMSUserServiceType getMBMSUserServiceType() throws NoSuchAttributeException {
        return (MBMSUserServiceType)_data.getContainer().get(Ro_r10AttributeName.MBMSUserServiceType, 0);
    }

    /**
     * Sets the MBMSUserServiceType.
     *
     * @param avp - the attribute value
     */
    public void setMBMSUserServiceType(MBMSUserServiceType avp) {
        _data.getContainer().add(Ro_r10AttributeName.MBMSUserServiceType, avp.getData(), true);
    }

    /**
     * Tests whether there is any FileRepairSupported.
     */
    public boolean containsFileRepairSupported() {
        return _data.getContainer().contains(Ro_r10AttributeName.FileRepairSupported);
    }

    /**
     * Gets the FileRepairSupported.
     */
    public FileRepairSupported getFileRepairSupported() throws NoSuchAttributeException {
        return (FileRepairSupported)_data.getContainer().get(Ro_r10AttributeName.FileRepairSupported, 0);
    }

    /**
     * Sets the FileRepairSupported.
     *
     * @param avp - the attribute value
     */
    public void setFileRepairSupported(FileRepairSupported avp) {
        _data.getContainer().add(Ro_r10AttributeName.FileRepairSupported, avp.getData(), true);
    }

    /**
     * Tests whether there is any RequiredMBMSBearerCapabilities.
     */
    public boolean containsRequiredMBMSBearerCapabilities() {
        return _data.getContainer().contains(Ro_r10AttributeName.RequiredMBMSBearerCapabilities);
    }

    /**
     * Gets the RequiredMBMSBearerCapabilities.
     */
    public RequiredMBMSBearerCapabilities getRequiredMBMSBearerCapabilities() throws NoSuchAttributeException {
        return (RequiredMBMSBearerCapabilities)_data.getContainer().get(Ro_r10AttributeName.RequiredMBMSBearerCapabilities, 0);
    }

    /**
     * Sets the RequiredMBMSBearerCapabilities.
     *
     * @param avp - the attribute value
     */
    public void setRequiredMBMSBearerCapabilities(RequiredMBMSBearerCapabilities avp) {
        _data.getContainer().add(Ro_r10AttributeName.RequiredMBMSBearerCapabilities, avp.getData(), true);
    }

    /**
     * Tests whether there is any MBMS2G3GIndicator.
     */
    public boolean containsMBMS2G3GIndicator() {
        return _data.getContainer().contains(Ro_r10AttributeName.MBMS2G3GIndicator);
    }

    /**
     * Gets the MBMS2G3GIndicator.
     */
    public MBMS2G3GIndicator getMBMS2G3GIndicator() throws NoSuchAttributeException {
        return (MBMS2G3GIndicator)_data.getContainer().get(Ro_r10AttributeName.MBMS2G3GIndicator, 0);
    }

    /**
     * Sets the MBMS2G3GIndicator.
     *
     * @param avp - the attribute value
     */
    public void setMBMS2G3GIndicator(MBMS2G3GIndicator avp) {
        _data.getContainer().add(Ro_r10AttributeName.MBMS2G3GIndicator, avp.getData(), true);
    }

    /**
     * Tests whether there is any RAI.
     */
    public boolean containsRAI() {
        return _data.getContainer().contains(Ro_r10AttributeName.RAI);
    }

    /**
     * Gets the RAI.
     */
    public RAI getRAI() throws NoSuchAttributeException {
        return (RAI)_data.getContainer().get(Ro_r10AttributeName.RAI, 0);
    }

    /**
     * Sets the RAI.
     *
     * @param avp - the attribute value
     */
    public void setRAI(RAI avp) {
        _data.getContainer().add(Ro_r10AttributeName.RAI, avp.getData(), true);
    }

    /**
     * Returns number of MBMSServiceArea instances.
     */
    public int countMBMSServiceArea() {
        return _data.getContainer().count(Ro_r10AttributeName.MBMSServiceArea);
    }

    /**
     * Gets one MBMSServiceArea.
     *
     * @param index - the index of the attribute to return
     */
    public MBMSServiceArea getMBMSServiceArea(int index) throws NoSuchAttributeException {
        return (MBMSServiceArea)_data.getContainer().get(Ro_r10AttributeName.MBMSServiceArea, index);
    }

    /**
     * Adds one MBMSServiceArea.
     *
     * @param avp - the attribute value
     */
    public void addMBMSServiceArea(MBMSServiceArea avp) {
        _data.getContainer().add(Ro_r10AttributeName.MBMSServiceArea, avp.getData(), false);
    }

    /**
     * Tests whether there is any MBMSSessionIdentity.
     */
    public boolean containsMBMSSessionIdentity() {
        return _data.getContainer().contains(Ro_r10AttributeName.MBMSSessionIdentity);
    }

    /**
     * Gets the MBMSSessionIdentity.
     */
    public MBMSSessionIdentity getMBMSSessionIdentity() throws NoSuchAttributeException {
        return (MBMSSessionIdentity)_data.getContainer().get(Ro_r10AttributeName.MBMSSessionIdentity, 0);
    }

    /**
     * Sets the MBMSSessionIdentity.
     *
     * @param avp - the attribute value
     */
    public void setMBMSSessionIdentity(MBMSSessionIdentity avp) {
        _data.getContainer().add(Ro_r10AttributeName.MBMSSessionIdentity, avp.getData(), true);
    }

    /**
     * Tests whether there is any CNIPMulticastDistribution.
     */
    public boolean containsCNIPMulticastDistribution() {
        return _data.getContainer().contains(Ro_r10AttributeName.CNIPMulticastDistribution);
    }

    /**
     * Gets the CNIPMulticastDistribution.
     */
    public CNIPMulticastDistribution getCNIPMulticastDistribution() throws NoSuchAttributeException {
        return (CNIPMulticastDistribution)_data.getContainer().get(Ro_r10AttributeName.CNIPMulticastDistribution, 0);
    }

    /**
     * Sets the CNIPMulticastDistribution.
     *
     * @param avp - the attribute value
     */
    public void setCNIPMulticastDistribution(CNIPMulticastDistribution avp) {
        _data.getContainer().add(Ro_r10AttributeName.CNIPMulticastDistribution, avp.getData(), true);
    }

    /**
     * Tests whether there is any MBMSGWAddress.
     */
    public boolean containsMBMSGWAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.MBMSGWAddress);
    }

    /**
     * Gets the MBMSGWAddress.
     */
    public MBMSGWAddress getMBMSGWAddress() throws NoSuchAttributeException {
        return (MBMSGWAddress)_data.getContainer().get(Ro_r10AttributeName.MBMSGWAddress, 0);
    }

    /**
     * Sets the MBMSGWAddress.
     *
     * @param avp - the attribute value
     */
    public void setMBMSGWAddress(MBMSGWAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.MBMSGWAddress, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsTMGI()) {
            sb.append("    TMGI:");
            try {
                sb.append(getTMGI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMBMSServiceType()) {
            sb.append("    MBMSServiceType:");
            try {
                sb.append(getMBMSServiceType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMBMSUserServiceType()) {
            sb.append("    MBMSUserServiceType:");
            try {
                sb.append(getMBMSUserServiceType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFileRepairSupported()) {
            sb.append("    FileRepairSupported:");
            try {
                sb.append(getFileRepairSupported()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRequiredMBMSBearerCapabilities()) {
            sb.append("    RequiredMBMSBearerCapabilities:");
            try {
                sb.append(getRequiredMBMSBearerCapabilities()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMBMS2G3GIndicator()) {
            sb.append("    MBMS2G3GIndicator:");
            try {
                sb.append(getMBMS2G3GIndicator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRAI()) {
            sb.append("    RAI:");
            try {
                sb.append(getRAI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countMBMSServiceArea(); ++i) {
            sb.append("    MBMSServiceArea:");
            try {
                sb.append(getMBMSServiceArea(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMBMSSessionIdentity()) {
            sb.append("    MBMSSessionIdentity:");
            try {
                sb.append(getMBMSSessionIdentity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCNIPMulticastDistribution()) {
            sb.append("    CNIPMulticastDistribution:");
            try {
                sb.append(getCNIPMulticastDistribution()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMBMSGWAddress()) {
            sb.append("    MBMSGWAddress:");
            try {
                sb.append(getMBMSGWAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
