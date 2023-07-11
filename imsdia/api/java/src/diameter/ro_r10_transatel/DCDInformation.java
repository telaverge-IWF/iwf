package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The DCD-Information AVP (AVP code 2115) is of type Grouped. Its purpose is 
  * to allow the transmission of service information elements used for DCD services. 
  */
public class DCDInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new DCDInformation.
     */
    public DCDInformation() {}

    DCDInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any ContentID.
     */
    public boolean containsContentID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ContentID);
    }

    /**
     * Gets the ContentID.
     */
    public ContentID getContentID() throws NoSuchAttributeException {
        return (ContentID)_data.getContainer().get(Ro_r10_transatelAttributeName.ContentID, 0);
    }

    /**
     * Sets the ContentID.
     *
     * @param avp - the attribute value
     */
    public void setContentID(ContentID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ContentID, avp.getData(), true);
    }

    /**
     * Tests whether there is any ContentproviderID.
     */
    public boolean containsContentproviderID() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ContentproviderID);
    }

    /**
     * Gets the ContentproviderID.
     */
    public ContentproviderID getContentproviderID() throws NoSuchAttributeException {
        return (ContentproviderID)_data.getContainer().get(Ro_r10_transatelAttributeName.ContentproviderID, 0);
    }

    /**
     * Sets the ContentproviderID.
     *
     * @param avp - the attribute value
     */
    public void setContentproviderID(ContentproviderID avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ContentproviderID, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsContentID()) {
            sb.append("    ContentID:");
            try {
                sb.append(getContentID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsContentproviderID()) {
            sb.append("    ContentproviderID:");
            try {
                sb.append(getContentproviderID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
