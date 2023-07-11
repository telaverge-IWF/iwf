package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The QoS-Information AVP (AVP code 1016) is of type Grouped, and it defines the QoS
 * information for resources requested by the UE, an IP-CAN bearer, PCC rule, QCI or APN.
 * When this AVP is sent from the PCEF to the PCRF, it indicates the requested QoS information
 * associated with resources requested by the UE, an IP CAN bearer or the subscribed QoS
 * information at APN level.
 */
public class QoSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new QoSInformation.
     */
    public QoSInformation() {}

    QoSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any QoSClassIdentifier.
     */
    public boolean containsQoSClassIdentifier() {
        return _data.getContainer().contains(Ro_r10AttributeName.QoSClassIdentifier);
    }

    /**
     * Gets the QoSClassIdentifier.
     */
    public QoSClassIdentifier getQoSClassIdentifier() throws NoSuchAttributeException {
        return (QoSClassIdentifier)_data.getContainer().get(Ro_r10AttributeName.QoSClassIdentifier, 0);
    }

    /**
     * Sets the QoSClassIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setQoSClassIdentifier(QoSClassIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.QoSClassIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any MaxRequestedBandwidthUL.
     */
    public boolean containsMaxRequestedBandwidthUL() {
        return _data.getContainer().contains(Ro_r10AttributeName.MaxRequestedBandwidthUL);
    }

    /**
     * Gets the MaxRequestedBandwidthUL.
     */
    public MaxRequestedBandwidthUL getMaxRequestedBandwidthUL() throws NoSuchAttributeException {
        return (MaxRequestedBandwidthUL)_data.getContainer().get(Ro_r10AttributeName.MaxRequestedBandwidthUL, 0);
    }

    /**
     * Sets the MaxRequestedBandwidthUL.
     *
     * @param avp - the attribute value
     */
    public void setMaxRequestedBandwidthUL(MaxRequestedBandwidthUL avp) {
        _data.getContainer().add(Ro_r10AttributeName.MaxRequestedBandwidthUL, avp.getData(), true);
    }

    /**
     * Tests whether there is any MaxRequestedBandwidthDL.
     */
    public boolean containsMaxRequestedBandwidthDL() {
        return _data.getContainer().contains(Ro_r10AttributeName.MaxRequestedBandwidthDL);
    }

    /**
     * Gets the MaxRequestedBandwidthDL.
     */
    public MaxRequestedBandwidthDL getMaxRequestedBandwidthDL() throws NoSuchAttributeException {
        return (MaxRequestedBandwidthDL)_data.getContainer().get(Ro_r10AttributeName.MaxRequestedBandwidthDL, 0);
    }

    /**
     * Sets the MaxRequestedBandwidthDL.
     *
     * @param avp - the attribute value
     */
    public void setMaxRequestedBandwidthDL(MaxRequestedBandwidthDL avp) {
        _data.getContainer().add(Ro_r10AttributeName.MaxRequestedBandwidthDL, avp.getData(), true);
    }

    /**
     * Tests whether there is any GuaranteedBitrateUL.
     */
    public boolean containsGuaranteedBitrateUL() {
        return _data.getContainer().contains(Ro_r10AttributeName.GuaranteedBitrateUL);
    }

    /**
     * Gets the GuaranteedBitrateUL.
     */
    public GuaranteedBitrateUL getGuaranteedBitrateUL() throws NoSuchAttributeException {
        return (GuaranteedBitrateUL)_data.getContainer().get(Ro_r10AttributeName.GuaranteedBitrateUL, 0);
    }

    /**
     * Sets the GuaranteedBitrateUL.
     *
     * @param avp - the attribute value
     */
    public void setGuaranteedBitrateUL(GuaranteedBitrateUL avp) {
        _data.getContainer().add(Ro_r10AttributeName.GuaranteedBitrateUL, avp.getData(), true);
    }

    /**
     * Tests whether there is any GuaranteedBitrateDL.
     */
    public boolean containsGuaranteedBitrateDL() {
        return _data.getContainer().contains(Ro_r10AttributeName.GuaranteedBitrateDL);
    }

    /**
     * Gets the GuaranteedBitrateDL.
     */
    public GuaranteedBitrateDL getGuaranteedBitrateDL() throws NoSuchAttributeException {
        return (GuaranteedBitrateDL)_data.getContainer().get(Ro_r10AttributeName.GuaranteedBitrateDL, 0);
    }

    /**
     * Sets the GuaranteedBitrateDL.
     *
     * @param avp - the attribute value
     */
    public void setGuaranteedBitrateDL(GuaranteedBitrateDL avp) {
        _data.getContainer().add(Ro_r10AttributeName.GuaranteedBitrateDL, avp.getData(), true);
    }

    /**
     * Tests whether there is any BearerIdentifier.
     */
    public boolean containsBearerIdentifier() {
        return _data.getContainer().contains(Ro_r10AttributeName.BearerIdentifier);
    }

    /**
     * Gets the BearerIdentifier.
     */
    public BearerIdentifier getBearerIdentifier() throws NoSuchAttributeException {
        return (BearerIdentifier)_data.getContainer().get(Ro_r10AttributeName.BearerIdentifier, 0);
    }

    /**
     * Sets the BearerIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setBearerIdentifier(BearerIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.BearerIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any AllocationRetentionPriority.
     */
    public boolean containsAllocationRetentionPriority() {
        return _data.getContainer().contains(Ro_r10AttributeName.AllocationRetentionPriority);
    }

    /**
     * Gets the AllocationRetentionPriority.
     */
    public AllocationRetentionPriority getAllocationRetentionPriority() throws NoSuchAttributeException {
        return (AllocationRetentionPriority)_data.getContainer().get(Ro_r10AttributeName.AllocationRetentionPriority, 0);
    }

    /**
     * Sets the AllocationRetentionPriority.
     *
     * @param avp - the attribute value
     */
    public void setAllocationRetentionPriority(AllocationRetentionPriority avp) {
        _data.getContainer().add(Ro_r10AttributeName.AllocationRetentionPriority, avp.getData(), true);
    }

    /**
     * Tests whether there is any APNAggregateMaxBitrateUL.
     */
    public boolean containsAPNAggregateMaxBitrateUL() {
        return _data.getContainer().contains(Ro_r10AttributeName.APNAggregateMaxBitrateUL);
    }

    /**
     * Gets the APNAggregateMaxBitrateUL.
     */
    public APNAggregateMaxBitrateUL getAPNAggregateMaxBitrateUL() throws NoSuchAttributeException {
        return (APNAggregateMaxBitrateUL)_data.getContainer().get(Ro_r10AttributeName.APNAggregateMaxBitrateUL, 0);
    }

    /**
     * Sets the APNAggregateMaxBitrateUL.
     *
     * @param avp - the attribute value
     */
    public void setAPNAggregateMaxBitrateUL(APNAggregateMaxBitrateUL avp) {
        _data.getContainer().add(Ro_r10AttributeName.APNAggregateMaxBitrateUL, avp.getData(), true);
    }

    /**
     * Tests whether there is any APNAggregateMaxBitrateDL.
     */
    public boolean containsAPNAggregateMaxBitrateDL() {
        return _data.getContainer().contains(Ro_r10AttributeName.APNAggregateMaxBitrateDL);
    }

    /**
     * Gets the APNAggregateMaxBitrateDL.
     */
    public APNAggregateMaxBitrateDL getAPNAggregateMaxBitrateDL() throws NoSuchAttributeException {
        return (APNAggregateMaxBitrateDL)_data.getContainer().get(Ro_r10AttributeName.APNAggregateMaxBitrateDL, 0);
    }

    /**
     * Sets the APNAggregateMaxBitrateDL.
     *
     * @param avp - the attribute value
     */
    public void setAPNAggregateMaxBitrateDL(APNAggregateMaxBitrateDL avp) {
        _data.getContainer().add(Ro_r10AttributeName.APNAggregateMaxBitrateDL, avp.getData(), true);
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
        if (containsQoSClassIdentifier()) {
            sb.append("    QoSClassIdentifier:");
            try {
                sb.append(getQoSClassIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMaxRequestedBandwidthUL()) {
            sb.append("    MaxRequestedBandwidthUL:");
            try {
                sb.append(getMaxRequestedBandwidthUL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMaxRequestedBandwidthDL()) {
            sb.append("    MaxRequestedBandwidthDL:");
            try {
                sb.append(getMaxRequestedBandwidthDL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGuaranteedBitrateUL()) {
            sb.append("    GuaranteedBitrateUL:");
            try {
                sb.append(getGuaranteedBitrateUL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGuaranteedBitrateDL()) {
            sb.append("    GuaranteedBitrateDL:");
            try {
                sb.append(getGuaranteedBitrateDL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsBearerIdentifier()) {
            sb.append("    BearerIdentifier:");
            try {
                sb.append(getBearerIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAllocationRetentionPriority()) {
            sb.append("    AllocationRetentionPriority:");
            try {
                sb.append(getAllocationRetentionPriority()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAPNAggregateMaxBitrateUL()) {
            sb.append("    APNAggregateMaxBitrateUL:");
            try {
                sb.append(getAPNAggregateMaxBitrateUL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAPNAggregateMaxBitrateDL()) {
            sb.append("    APNAggregateMaxBitrateDL:");
            try {
                sb.append(getAPNAggregateMaxBitrateDL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
