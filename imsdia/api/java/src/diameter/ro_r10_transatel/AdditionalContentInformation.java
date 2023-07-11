package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Additional-Content-information AVP is of type Grouped and identifies any subsequent content types.
 * It is used to identify each content (including re-occurence) within an MM when the Type-Number AVP 
 * or Additional-Type-Information AVP from the content-Type AVP indicate a multi-part content.
 */
public class AdditionalContentInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AdditionalContentInformation.
     */
    public AdditionalContentInformation() {}

    AdditionalContentInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any TypeNumber.
     */
    public boolean containsTypeNumber() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TypeNumber);
    }

    /**
     * Gets the TypeNumber.
     */
    public TypeNumber getTypeNumber() throws NoSuchAttributeException {
        return (TypeNumber)_data.getContainer().get(Ro_r10_transatelAttributeName.TypeNumber, 0);
    }

    /**
     * Sets the TypeNumber.
     *
     * @param avp - the attribute value
     */
    public void setTypeNumber(TypeNumber avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TypeNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any AdditionalTypeInformation.
     */
    public boolean containsAdditionalTypeInformation() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AdditionalTypeInformation);
    }

    /**
     * Gets the AdditionalTypeInformation.
     */
    public AdditionalTypeInformation getAdditionalTypeInformation() throws NoSuchAttributeException {
        return (AdditionalTypeInformation)_data.getContainer().get(Ro_r10_transatelAttributeName.AdditionalTypeInformation, 0);
    }

    /**
     * Sets the AdditionalTypeInformation.
     *
     * @param avp - the attribute value
     */
    public void setAdditionalTypeInformation(AdditionalTypeInformation avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AdditionalTypeInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any ContentSize.
     */
    public boolean containsContentSize() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ContentSize);
    }

    /**
     * Gets the ContentSize.
     */
    public ContentSize getContentSize() throws NoSuchAttributeException {
        return (ContentSize)_data.getContainer().get(Ro_r10_transatelAttributeName.ContentSize, 0);
    }

    /**
     * Sets the ContentSize.
     *
     * @param avp - the attribute value
     */
    public void setContentSize(ContentSize avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ContentSize, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsTypeNumber()) {
            sb.append("    TypeNumber:");
            try {
                sb.append(getTypeNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAdditionalTypeInformation()) {
            sb.append("    AdditionalTypeInformation:");
            try {
                sb.append(getAdditionalTypeInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsContentSize()) {
            sb.append("    ContentSize:");
            try {
                sb.append(getContentSize()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
