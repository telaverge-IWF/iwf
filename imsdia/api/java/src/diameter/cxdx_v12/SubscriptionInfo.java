package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class SubscriptionInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new SubscriptionInfo.
     */
    public SubscriptionInfo() {}

    SubscriptionInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the CallIDSIPHeader.
     */
    public CallIDSIPHeader getCallIDSIPHeader() throws NoSuchAttributeException {
        return (CallIDSIPHeader)_data.getContainer().get(Cxdx_v12AttributeName.CallIDSIPHeader, 0);
    }

    /**
     * Sets the CallIDSIPHeader.
     *
     * @param avp - the attribute value
     */
    public void setCallIDSIPHeader(CallIDSIPHeader avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.CallIDSIPHeader, avp.getData(), true);
    }

    /**
     * Gets the FromSIPHeader.
     */
    public FromSIPHeader getFromSIPHeader() throws NoSuchAttributeException {
        return (FromSIPHeader)_data.getContainer().get(Cxdx_v12AttributeName.FromSIPHeader, 0);
    }

    /**
     * Sets the FromSIPHeader.
     *
     * @param avp - the attribute value
     */
    public void setFromSIPHeader(FromSIPHeader avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.FromSIPHeader, avp.getData(), true);
    }

    /**
     * Gets the ToSIPHeader.
     */
    public ToSIPHeader getToSIPHeader() throws NoSuchAttributeException {
        return (ToSIPHeader)_data.getContainer().get(Cxdx_v12AttributeName.ToSIPHeader, 0);
    }

    /**
     * Sets the ToSIPHeader.
     *
     * @param avp - the attribute value
     */
    public void setToSIPHeader(ToSIPHeader avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.ToSIPHeader, avp.getData(), true);
    }

    /**
     * Gets the RecordRoute.
     */
    public RecordRoute getRecordRoute() throws NoSuchAttributeException {
        return (RecordRoute)_data.getContainer().get(Cxdx_v12AttributeName.RecordRoute, 0);
    }

    /**
     * Sets the RecordRoute.
     *
     * @param avp - the attribute value
     */
    public void setRecordRoute(RecordRoute avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.RecordRoute, avp.getData(), true);
    }

    /**
     * Gets the Contact.
     */
    public Contact getContact() throws NoSuchAttributeException {
        return (Contact)_data.getContainer().get(Cxdx_v12AttributeName.Contact, 0);
    }

    /**
     * Sets the Contact.
     *
     * @param avp - the attribute value
     */
    public void setContact(Contact avp) {
        _data.getContainer().add(Cxdx_v12AttributeName.Contact, avp.getData(), true);
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
        sb.append("    CallIDSIPHeader:");
            try {
                sb.append(getCallIDSIPHeader()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    FromSIPHeader:");
            try {
                sb.append(getFromSIPHeader()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ToSIPHeader:");
            try {
                sb.append(getToSIPHeader()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    RecordRoute:");
            try {
                sb.append(getRecordRoute()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    Contact:");
            try {
                sb.append(getContact()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
