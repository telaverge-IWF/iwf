package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Traffic-Data-Volumes AVP (AVP code 2046) is of type Grouped.
 *  Its purpose is to allow the transmission of the IP-CAN bearer 
 * container, on encountering change on charging condition for 
 * this IP-CAN bearer.This container  reports the volume count 
 * (separated for uplink and downlink).
 */
public class TrafficDataVolumes extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TrafficDataVolumes.
     */
    public TrafficDataVolumes() {}

    TrafficDataVolumes(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any QoSInformation.
     */
    public boolean containsQoSInformation() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.QoSInformation);
    }

    /**
     * Gets the QoSInformation.
     */
    public QoSInformation getQoSInformation() throws NoSuchAttributeException {
        return (QoSInformation)_data.getContainer().get(Ro_r10_transatelAttributeName.QoSInformation, 0);
    }

    /**
     * Sets the QoSInformation.
     *
     * @param avp - the attribute value
     */
    public void setQoSInformation(QoSInformation avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.QoSInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingInputOctets.
     */
    public boolean containsAccountingInputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingInputOctets);
    }

    /**
     * Gets the AccountingInputOctets.
     */
    public AccountingInputOctets getAccountingInputOctets() throws NoSuchAttributeException {
        return (AccountingInputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingInputOctets, 0);
    }

    /**
     * Sets the AccountingInputOctets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingInputOctets(AccountingInputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingInputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingInputPackets.
     */
    public boolean containsAccountingInputPackets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingInputPackets);
    }

    /**
     * Gets the AccountingInputPackets.
     */
    public AccountingInputPackets getAccountingInputPackets() throws NoSuchAttributeException {
        return (AccountingInputPackets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingInputPackets, 0);
    }

    /**
     * Sets the AccountingInputPackets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingInputPackets(AccountingInputPackets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingInputPackets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingOutputOctets.
     */
    public boolean containsAccountingOutputOctets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingOutputOctets);
    }

    /**
     * Gets the AccountingOutputOctets.
     */
    public AccountingOutputOctets getAccountingOutputOctets() throws NoSuchAttributeException {
        return (AccountingOutputOctets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingOutputOctets, 0);
    }

    /**
     * Sets the AccountingOutputOctets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingOutputOctets(AccountingOutputOctets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingOutputOctets, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountingOutputPackets.
     */
    public boolean containsAccountingOutputPackets() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AccountingOutputPackets);
    }

    /**
     * Gets the AccountingOutputPackets.
     */
    public AccountingOutputPackets getAccountingOutputPackets() throws NoSuchAttributeException {
        return (AccountingOutputPackets)_data.getContainer().get(Ro_r10_transatelAttributeName.AccountingOutputPackets, 0);
    }

    /**
     * Sets the AccountingOutputPackets.
     *
     * @param avp - the attribute value
     */
    public void setAccountingOutputPackets(AccountingOutputPackets avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AccountingOutputPackets, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChangeCondition.
     */
    public boolean containsChangeCondition() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ChangeCondition);
    }

    /**
     * Gets the ChangeCondition.
     */
    public ChangeCondition getChangeCondition() throws NoSuchAttributeException {
        return (ChangeCondition)_data.getContainer().get(Ro_r10_transatelAttributeName.ChangeCondition, 0);
    }

    /**
     * Sets the ChangeCondition.
     *
     * @param avp - the attribute value
     */
    public void setChangeCondition(ChangeCondition avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ChangeCondition, avp.getData(), true);
    }

    /**
     * Tests whether there is any ChangeTime.
     */
    public boolean containsChangeTime() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ChangeTime);
    }

    /**
     * Gets the ChangeTime.
     */
    public ChangeTime getChangeTime() throws NoSuchAttributeException {
        return (ChangeTime)_data.getContainer().get(Ro_r10_transatelAttributeName.ChangeTime, 0);
    }

    /**
     * Sets the ChangeTime.
     *
     * @param avp - the attribute value
     */
    public void setChangeTime(ChangeTime avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ChangeTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPUserLocationInfo.
     */
    public boolean containsRo3GPPUserLocationInfo() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Ro3GPPUserLocationInfo);
    }

    /**
     * Gets the Ro3GPPUserLocationInfo.
     */
    public Ro3GPPUserLocationInfo getRo3GPPUserLocationInfo() throws NoSuchAttributeException {
        return (Ro3GPPUserLocationInfo)_data.getContainer().get(Ro_r10_transatelAttributeName.Ro3GPPUserLocationInfo, 0);
    }

    /**
     * Sets the Ro3GPPUserLocationInfo.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPUserLocationInfo(Ro3GPPUserLocationInfo avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Ro3GPPUserLocationInfo, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsQoSInformation()) {
            sb.append("    QoSInformation:");
            try {
                sb.append(getQoSInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingInputOctets()) {
            sb.append("    AccountingInputOctets:");
            try {
                sb.append(getAccountingInputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingInputPackets()) {
            sb.append("    AccountingInputPackets:");
            try {
                sb.append(getAccountingInputPackets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingOutputOctets()) {
            sb.append("    AccountingOutputOctets:");
            try {
                sb.append(getAccountingOutputOctets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountingOutputPackets()) {
            sb.append("    AccountingOutputPackets:");
            try {
                sb.append(getAccountingOutputPackets()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsChangeCondition()) {
            sb.append("    ChangeCondition:");
            try {
                sb.append(getChangeCondition()).append('\n');
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
        if (containsRo3GPPUserLocationInfo()) {
            sb.append("    Ro3GPPUserLocationInfo:");
            try {
                sb.append(getRo3GPPUserLocationInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
