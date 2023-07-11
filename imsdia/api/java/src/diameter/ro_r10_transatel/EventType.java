package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Event-Type AVP is of type grouped and containes information about the type of chargeable
 * telecommunication service/event for which the accounting-request message is generated.
 */
public class EventType extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new EventType.
     */
    public EventType() {}

    EventType(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any SIPMethod.
     */
    public boolean containsSIPMethod() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.SIPMethod);
    }

    /**
     * Gets the SIPMethod.
     */
    public SIPMethod getSIPMethod() throws NoSuchAttributeException {
        return (SIPMethod)_data.getContainer().get(Ro_r10_transatelAttributeName.SIPMethod, 0);
    }

    /**
     * Sets the SIPMethod.
     *
     * @param avp - the attribute value
     */
    public void setSIPMethod(SIPMethod avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.SIPMethod, avp.getData(), true);
    }

    /**
     * Tests whether there is any IMSEvent.
     */
    public boolean containsIMSEvent() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.IMSEvent);
    }

    /**
     * Gets the IMSEvent.
     */
    public IMSEvent getIMSEvent() throws NoSuchAttributeException {
        return (IMSEvent)_data.getContainer().get(Ro_r10_transatelAttributeName.IMSEvent, 0);
    }

    /**
     * Sets the IMSEvent.
     *
     * @param avp - the attribute value
     */
    public void setIMSEvent(IMSEvent avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.IMSEvent, avp.getData(), true);
    }

    /**
     * Tests whether there is any Expires.
     */
    public boolean containsExpires() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Expires);
    }

    /**
     * Gets the Expires.
     */
    public Expires getExpires() throws NoSuchAttributeException {
        return (Expires)_data.getContainer().get(Ro_r10_transatelAttributeName.Expires, 0);
    }

    /**
     * Sets the Expires.
     *
     * @param avp - the attribute value
     */
    public void setExpires(Expires avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Expires, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsSIPMethod()) {
            sb.append("    SIPMethod:");
            try {
                sb.append(getSIPMethod()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIMSEvent()) {
            sb.append("    IMSEvent:");
            try {
                sb.append(getIMSEvent()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsExpires()) {
            sb.append("    Expires:");
            try {
                sb.append(getExpires()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
