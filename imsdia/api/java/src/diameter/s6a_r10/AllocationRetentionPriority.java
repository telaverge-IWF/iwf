package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class AllocationRetentionPriority extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AllocationRetentionPriority.
     */
    public AllocationRetentionPriority() {}

    AllocationRetentionPriority(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the PriorityLevel.
     */
    public PriorityLevel getPriorityLevel() throws NoSuchAttributeException {
        return (PriorityLevel)_data.getContainer().get(S6a_r10AttributeName.PriorityLevel, 0);
    }

    /**
     * Sets the PriorityLevel.
     *
     * @param avp - the attribute value
     */
    public void setPriorityLevel(PriorityLevel avp) {
        _data.getContainer().add(S6a_r10AttributeName.PriorityLevel, avp.getData(), true);
    }

    /**
     * Tests whether there is any PreemptionCapability.
     */
    public boolean containsPreemptionCapability() {
        return _data.getContainer().contains(S6a_r10AttributeName.PreemptionCapability);
    }

    /**
     * Gets the PreemptionCapability.
     */
    public PreemptionCapability getPreemptionCapability() throws NoSuchAttributeException {
        return (PreemptionCapability)_data.getContainer().get(S6a_r10AttributeName.PreemptionCapability, 0);
    }

    /**
     * Sets the PreemptionCapability.
     *
     * @param avp - the attribute value
     */
    public void setPreemptionCapability(PreemptionCapability avp) {
        _data.getContainer().add(S6a_r10AttributeName.PreemptionCapability, avp.getData(), true);
    }

    /**
     * Tests whether there is any PreemptionVulnerability.
     */
    public boolean containsPreemptionVulnerability() {
        return _data.getContainer().contains(S6a_r10AttributeName.PreemptionVulnerability);
    }

    /**
     * Gets the PreemptionVulnerability.
     */
    public PreemptionVulnerability getPreemptionVulnerability() throws NoSuchAttributeException {
        return (PreemptionVulnerability)_data.getContainer().get(S6a_r10AttributeName.PreemptionVulnerability, 0);
    }

    /**
     * Sets the PreemptionVulnerability.
     *
     * @param avp - the attribute value
     */
    public void setPreemptionVulnerability(PreemptionVulnerability avp) {
        _data.getContainer().add(S6a_r10AttributeName.PreemptionVulnerability, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    PriorityLevel:");
            try {
                sb.append(getPriorityLevel()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsPreemptionCapability()) {
            sb.append("    PreemptionCapability:");
            try {
                sb.append(getPreemptionCapability()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsPreemptionVulnerability()) {
            sb.append("    PreemptionVulnerability:");
            try {
                sb.append(getPreemptionVulnerability()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
