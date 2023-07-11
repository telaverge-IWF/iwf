package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Message-Body AVP is of type Grouped and holds information about the message bodies including 
 * user-to-user data.
 */
public class MessageBody extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MessageBody.
     */
    public MessageBody() {}

    MessageBody(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the ContentType.
     */
    public ContentType getContentType() throws NoSuchAttributeException {
        return (ContentType)_data.getContainer().get(Ro_r10_transatelAttributeName.ContentType, 0);
    }

    /**
     * Sets the ContentType.
     *
     * @param avp - the attribute value
     */
    public void setContentType(ContentType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ContentType, avp.getData(), true);
    }

    /**
     * Gets the ContentLength.
     */
    public ContentLength getContentLength() throws NoSuchAttributeException {
        return (ContentLength)_data.getContainer().get(Ro_r10_transatelAttributeName.ContentLength, 0);
    }

    /**
     * Sets the ContentLength.
     *
     * @param avp - the attribute value
     */
    public void setContentLength(ContentLength avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ContentLength, avp.getData(), true);
    }

    /**
     * Tests whether there is any ContentDisposition.
     */
    public boolean containsContentDisposition() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ContentDisposition);
    }

    /**
     * Gets the ContentDisposition.
     */
    public ContentDisposition getContentDisposition() throws NoSuchAttributeException {
        return (ContentDisposition)_data.getContainer().get(Ro_r10_transatelAttributeName.ContentDisposition, 0);
    }

    /**
     * Sets the ContentDisposition.
     *
     * @param avp - the attribute value
     */
    public void setContentDisposition(ContentDisposition avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ContentDisposition, avp.getData(), true);
    }

    /**
     * Tests whether there is any Originator.
     */
    public boolean containsOriginator() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.Originator);
    }

    /**
     * Gets the Originator.
     */
    public Originator getOriginator() throws NoSuchAttributeException {
        return (Originator)_data.getContainer().get(Ro_r10_transatelAttributeName.Originator, 0);
    }

    /**
     * Sets the Originator.
     *
     * @param avp - the attribute value
     */
    public void setOriginator(Originator avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.Originator, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    ContentType:");
            try {
                sb.append(getContentType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ContentLength:");
            try {
                sb.append(getContentLength()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsContentDisposition()) {
            sb.append("    ContentDisposition:");
            try {
                sb.append(getContentDisposition()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOriginator()) {
            sb.append("    Originator:");
            try {
                sb.append(getOriginator()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
