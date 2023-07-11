package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Originator-Received-Address AVP (AVP code 2027) is of type Grouped. Its 
 * purpose is to identify the originator of a message with the original, 
 * unmodified address information as received before any address manipulations 
 * has taken place in the entity generating the charging information
 */
public class OriginatorReceivedAddress extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new OriginatorReceivedAddress.
     */
    public OriginatorReceivedAddress() {}

    OriginatorReceivedAddress(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any IMSAddressType.
     */
    public boolean containsIMSAddressType() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.IMSAddressType);
    }

    /**
     * Gets the IMSAddressType.
     */
    public IMSAddressType getIMSAddressType() throws NoSuchAttributeException {
        return (IMSAddressType)_data.getContainer().get(Ro_r10_transatelAttributeName.IMSAddressType, 0);
    }

    /**
     * Sets the IMSAddressType.
     *
     * @param avp - the attribute value
     */
    public void setIMSAddressType(IMSAddressType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.IMSAddressType, avp.getData(), true);
    }

    /**
     * Tests whether there is any AddressData.
     */
    public boolean containsAddressData() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AddressData);
    }

    /**
     * Gets the AddressData.
     */
    public AddressData getAddressData() throws NoSuchAttributeException {
        return (AddressData)_data.getContainer().get(Ro_r10_transatelAttributeName.AddressData, 0);
    }

    /**
     * Sets the AddressData.
     *
     * @param avp - the attribute value
     */
    public void setAddressData(AddressData avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AddressData, avp.getData(), true);
    }

    /**
     * Tests whether there is any AddressDomain.
     */
    public boolean containsAddressDomain() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.AddressDomain);
    }

    /**
     * Gets the AddressDomain.
     */
    public AddressDomain getAddressDomain() throws NoSuchAttributeException {
        return (AddressDomain)_data.getContainer().get(Ro_r10_transatelAttributeName.AddressDomain, 0);
    }

    /**
     * Sets the AddressDomain.
     *
     * @param avp - the attribute value
     */
    public void setAddressDomain(AddressDomain avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.AddressDomain, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsIMSAddressType()) {
            sb.append("    IMSAddressType:");
            try {
                sb.append(getIMSAddressType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAddressData()) {
            sb.append("    AddressData:");
            try {
                sb.append(getAddressData()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAddressDomain()) {
            sb.append("    AddressDomain:");
            try {
                sb.append(getAddressDomain()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
