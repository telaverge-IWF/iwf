package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Trunk-Group-ID is of type Grouped and identifies the incoming and out going PSTN legs.
 */
public class TrunkGroupID extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TrunkGroupID.
     */
    public TrunkGroupID() {}

    TrunkGroupID(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any IncomingTrunkGroupID.
     */
    public boolean containsIncomingTrunkGroupID() {
        return _data.getContainer().contains(Ro_r10AttributeName.IncomingTrunkGroupID);
    }

    /**
     * Gets the IncomingTrunkGroupID.
     */
    public IncomingTrunkGroupID getIncomingTrunkGroupID() throws NoSuchAttributeException {
        return (IncomingTrunkGroupID)_data.getContainer().get(Ro_r10AttributeName.IncomingTrunkGroupID, 0);
    }

    /**
     * Sets the IncomingTrunkGroupID.
     *
     * @param avp - the attribute value
     */
    public void setIncomingTrunkGroupID(IncomingTrunkGroupID avp) {
        _data.getContainer().add(Ro_r10AttributeName.IncomingTrunkGroupID, avp.getData(), true);
    }

    /**
     * Tests whether there is any OutgoingTrunkGroupID.
     */
    public boolean containsOutgoingTrunkGroupID() {
        return _data.getContainer().contains(Ro_r10AttributeName.OutgoingTrunkGroupID);
    }

    /**
     * Gets the OutgoingTrunkGroupID.
     */
    public OutgoingTrunkGroupID getOutgoingTrunkGroupID() throws NoSuchAttributeException {
        return (OutgoingTrunkGroupID)_data.getContainer().get(Ro_r10AttributeName.OutgoingTrunkGroupID, 0);
    }

    /**
     * Sets the OutgoingTrunkGroupID.
     *
     * @param avp - the attribute value
     */
    public void setOutgoingTrunkGroupID(OutgoingTrunkGroupID avp) {
        _data.getContainer().add(Ro_r10AttributeName.OutgoingTrunkGroupID, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsIncomingTrunkGroupID()) {
            sb.append("    IncomingTrunkGroupID:");
            try {
                sb.append(getIncomingTrunkGroupID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOutgoingTrunkGroupID()) {
            sb.append("    OutgoingTrunkGroupID:");
            try {
                sb.append(getOutgoingTrunkGroupID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
