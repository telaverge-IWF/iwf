package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The Requested-EUTRAN-Authentication-Info is of type Grouped. It contains the 
 * information related to the to authentication requests for E-UTRAN
 */
public class RequestedEUTRANAuthenticationInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RequestedEUTRANAuthenticationInfo.
     */
    public RequestedEUTRANAuthenticationInfo() {}

    RequestedEUTRANAuthenticationInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any NumberOfRequestedVectors.
     */
    public boolean containsNumberOfRequestedVectors() {
        return _data.getContainer().contains(S6a_r10AttributeName.NumberOfRequestedVectors);
    }

    /**
     * Gets the NumberOfRequestedVectors.
     */
    public NumberOfRequestedVectors getNumberOfRequestedVectors() throws NoSuchAttributeException {
        return (NumberOfRequestedVectors)_data.getContainer().get(S6a_r10AttributeName.NumberOfRequestedVectors, 0);
    }

    /**
     * Sets the NumberOfRequestedVectors.
     *
     * @param avp - the attribute value
     */
    public void setNumberOfRequestedVectors(NumberOfRequestedVectors avp) {
        _data.getContainer().add(S6a_r10AttributeName.NumberOfRequestedVectors, avp.getData(), true);
    }

    /**
     * Tests whether there is any ImmediateResponsePreferred.
     */
    public boolean containsImmediateResponsePreferred() {
        return _data.getContainer().contains(S6a_r10AttributeName.ImmediateResponsePreferred);
    }

    /**
     * Gets the ImmediateResponsePreferred.
     */
    public ImmediateResponsePreferred getImmediateResponsePreferred() throws NoSuchAttributeException {
        return (ImmediateResponsePreferred)_data.getContainer().get(S6a_r10AttributeName.ImmediateResponsePreferred, 0);
    }

    /**
     * Sets the ImmediateResponsePreferred.
     *
     * @param avp - the attribute value
     */
    public void setImmediateResponsePreferred(ImmediateResponsePreferred avp) {
        _data.getContainer().add(S6a_r10AttributeName.ImmediateResponsePreferred, avp.getData(), true);
    }

    /**
     * Tests whether there is any ReSynchronizationInfo.
     */
    public boolean containsReSynchronizationInfo() {
        return _data.getContainer().contains(S6a_r10AttributeName.ReSynchronizationInfo);
    }

    /**
     * Gets the ReSynchronizationInfo.
     */
    public ReSynchronizationInfo getReSynchronizationInfo() throws NoSuchAttributeException {
        return (ReSynchronizationInfo)_data.getContainer().get(S6a_r10AttributeName.ReSynchronizationInfo, 0);
    }

    /**
     * Sets the ReSynchronizationInfo.
     *
     * @param avp - the attribute value
     */
    public void setReSynchronizationInfo(ReSynchronizationInfo avp) {
        _data.getContainer().add(S6a_r10AttributeName.ReSynchronizationInfo, avp.getData(), true);
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
        if (containsNumberOfRequestedVectors()) {
            sb.append("    NumberOfRequestedVectors:");
            try {
                sb.append(getNumberOfRequestedVectors()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsImmediateResponsePreferred()) {
            sb.append("    ImmediateResponsePreferred:");
            try {
                sb.append(getImmediateResponsePreferred()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsReSynchronizationInfo()) {
            sb.append("    ReSynchronizationInfo:");
            try {
                sb.append(getReSynchronizationInfo()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
