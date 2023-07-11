package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
  * The Supplementary-Service AVP (AVP code 2048) is of type Grouped and holds 
  * the specific supplementary service details for one MMTel supplementary service.
  */
public class SupplementaryService extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SupplementaryService.
     */
    public SupplementaryService() {}

    SupplementaryService(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any ServiceType.
     */
    public boolean containsServiceType() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServiceType);
    }

    /**
     * Gets the ServiceType.
     */
    public ServiceType getServiceType() throws NoSuchAttributeException {
        return (ServiceType)_data.getContainer().get(Ro_r10AttributeName.ServiceType, 0);
    }

    /**
     * Sets the ServiceType.
     *
     * @param avp - the attribute value
     */
    public void setServiceType(ServiceType avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceType, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceMode.
     */
    public boolean containsServiceMode() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServiceMode);
    }

    /**
     * Gets the ServiceMode.
     */
    public ServiceMode getServiceMode() throws NoSuchAttributeException {
        return (ServiceMode)_data.getContainer().get(Ro_r10AttributeName.ServiceMode, 0);
    }

    /**
     * Sets the ServiceMode.
     *
     * @param avp - the attribute value
     */
    public void setServiceMode(ServiceMode avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceMode, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfDiversions.
     */
    public boolean containsNumberOfDiversions() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberOfDiversions);
    }

    /**
     * Gets the NumberOfDiversions.
     */
    public NumberOfDiversions getNumberOfDiversions() throws NoSuchAttributeException {
        return (NumberOfDiversions)_data.getContainer().get(Ro_r10AttributeName.NumberOfDiversions, 0);
    }

    /**
     * Sets the NumberOfDiversions.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfDiversions(NumberOfDiversions avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberOfDiversions, avp.getData(), true);
    }

    /**
     * Tests whether there is any AssociatedPartyAddress.
     */
    public boolean containsAssociatedPartyAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.AssociatedPartyAddress);
    }

    /**
     * Gets the AssociatedPartyAddress.
     */
    public AssociatedPartyAddress getAssociatedPartyAddress() throws NoSuchAttributeException {
        return (AssociatedPartyAddress)_data.getContainer().get(Ro_r10AttributeName.AssociatedPartyAddress, 0);
    }

    /**
     * Sets the AssociatedPartyAddress.
     *
     * @param avp - the attribute value
     */
    public void setAssociatedPartyAddress(AssociatedPartyAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.AssociatedPartyAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceId.
     */
    public boolean containsServiceId() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServiceId);
    }

    /**
     * Gets the ServiceId.
     */
    public ServiceId getServiceId() throws NoSuchAttributeException {
        return (ServiceId)_data.getContainer().get(Ro_r10AttributeName.ServiceId, 0);
    }

    /**
     * Sets the ServiceId.
     *
     * @param avp - the attribute value
     */
    public void setServiceId(ServiceId avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceId, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChangeTime.
     */
    public boolean containsChangeTime() {
        return _data.getContainer().contains(Ro_r10AttributeName.ChangeTime);
    }

    /**
     * Gets the ChangeTime.
     */
    public ChangeTime getChangeTime() throws NoSuchAttributeException {
        return (ChangeTime)_data.getContainer().get(Ro_r10AttributeName.ChangeTime, 0);
    }

    /**
     * Sets the ChangeTime.
     *
     * @param avp - the attribute value
     */
    public void setChangeTime(ChangeTime avp) {
        _data.getContainer().add(Ro_r10AttributeName.ChangeTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any NumberOfParticipants.
     */
    public boolean containsNumberOfParticipants() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberOfParticipants);
    }

    /**
     * Gets the NumberOfParticipants.
     */
    public NumberOfParticipants getNumberOfParticipants() throws NoSuchAttributeException {
        return (NumberOfParticipants)_data.getContainer().get(Ro_r10AttributeName.NumberOfParticipants, 0);
    }

    /**
     * Sets the NumberOfParticipants.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfParticipants(NumberOfParticipants avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberOfParticipants, avp.getData(), true);
    }

    /**
     * Tests whether there is any ParticipantActionType.
     */
    public boolean containsParticipantActionType() {
        return _data.getContainer().contains(Ro_r10AttributeName.ParticipantActionType);
    }

    /**
     * Gets the ParticipantActionType.
     */
    public ParticipantActionType getParticipantActionType() throws NoSuchAttributeException {
        return (ParticipantActionType)_data.getContainer().get(Ro_r10AttributeName.ParticipantActionType, 0);
    }

    /**
     * Sets the ParticipantActionType.
     *
     * @param avp - the attribute value
     */
    public void setParticipantActionType(ParticipantActionType avp) {
        _data.getContainer().add(Ro_r10AttributeName.ParticipantActionType, avp.getData(), true);
    }

    /**
     * Tests whether there is any CUGInformation.
     */
    public boolean containsCUGInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.CUGInformation);
    }

    /**
     * Gets the CUGInformation.
     */
    public CUGInformation getCUGInformation() throws NoSuchAttributeException {
        return (CUGInformation)_data.getContainer().get(Ro_r10AttributeName.CUGInformation, 0);
    }

    /**
     * Sets the CUGInformation.
     *
     * @param avp - the attribute value
     */
    public void setCUGInformation(CUGInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.CUGInformation, avp.getData(), true);
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


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsServiceType()) {
            sb.append("    ServiceType:");
            try {
                sb.append(getServiceType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceMode()) {
            sb.append("    ServiceMode:");
            try {
                sb.append(getServiceMode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberOfDiversions()) {
            sb.append("    NumberOfDiversions:");
            try {
                sb.append(getNumberOfDiversions()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAssociatedPartyAddress()) {
            sb.append("    AssociatedPartyAddress:");
            try {
                sb.append(getAssociatedPartyAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceId()) {
            sb.append("    ServiceId:");
            try {
                sb.append(getServiceId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsChangeTime()) {
            sb.append("    ChangeTime:");
            try {
                sb.append(getChangeTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberOfParticipants()) {
            sb.append("    NumberOfParticipants:");
            try {
                sb.append(getNumberOfParticipants()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsParticipantActionType()) {
            sb.append("    ParticipantActionType:");
            try {
                sb.append(getParticipantActionType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCUGInformation()) {
            sb.append("    CUGInformation:");
            try {
                sb.append(getCUGInformation()).append('\n');
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
        return sb.append('}').toString();
    }
}
