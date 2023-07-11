package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Message-Class AVP is of type Grouped.
 */
public class MessageClass extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MessageClass.
     */
    public MessageClass() {}

    MessageClass(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any ClassIdentifier.
     */
    public boolean containsClassIdentifier() {
        return _data.getContainer().contains(Ro_r10AttributeName.ClassIdentifier);
    }

    /**
     * Gets the ClassIdentifier.
     */
    public ClassIdentifier getClassIdentifier() throws NoSuchAttributeException {
        return (ClassIdentifier)_data.getContainer().get(Ro_r10AttributeName.ClassIdentifier, 0);
    }

    /**
     * Sets the ClassIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setClassIdentifier(ClassIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.ClassIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any TokenText.
     */
    public boolean containsTokenText() {
        return _data.getContainer().contains(Ro_r10AttributeName.TokenText);
    }

    /**
     * Gets the TokenText.
     */
    public TokenText getTokenText() throws NoSuchAttributeException {
        return (TokenText)_data.getContainer().get(Ro_r10AttributeName.TokenText, 0);
    }

    /**
     * Sets the TokenText.
     *
     * @param avp - the attribute value
     */
    public void setTokenText(TokenText avp) {
        _data.getContainer().add(Ro_r10AttributeName.TokenText, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsClassIdentifier()) {
            sb.append("    ClassIdentifier:");
            try {
                sb.append(getClassIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTokenText()) {
            sb.append("    TokenText:");
            try {
                sb.append(getTokenText()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
