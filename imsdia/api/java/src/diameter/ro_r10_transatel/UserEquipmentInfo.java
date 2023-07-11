package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The User-Equipment-Info AVP is of type Grouped and allows the credit-control client to indicate
 * the identity and capability of the terminal the subscriber is using for the connection to network.
 */
public class UserEquipmentInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new UserEquipmentInfo.
     */
    public UserEquipmentInfo() {}

    UserEquipmentInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the UserEquipmentInfoType.
     */
    public UserEquipmentInfoType getUserEquipmentInfoType() throws NoSuchAttributeException {
        return (UserEquipmentInfoType)_data.getContainer().get(Ro_r10_transatelAttributeName.UserEquipmentInfoType, 0);
    }

    /**
     * Sets the UserEquipmentInfoType.
     *
     * @param avp - the attribute value
     */
    public void setUserEquipmentInfoType(UserEquipmentInfoType avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.UserEquipmentInfoType, avp.getData(), true);
    }

    /**
     * Gets the UserEquipmentInfoValue.
     */
    public UserEquipmentInfoValue getUserEquipmentInfoValue() throws NoSuchAttributeException {
        return (UserEquipmentInfoValue)_data.getContainer().get(Ro_r10_transatelAttributeName.UserEquipmentInfoValue, 0);
    }

    /**
     * Sets the UserEquipmentInfoValue.
     *
     * @param avp - the attribute value
     */
    public void setUserEquipmentInfoValue(UserEquipmentInfoValue avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.UserEquipmentInfoValue, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    UserEquipmentInfoType:");
            try {
                sb.append(getUserEquipmentInfoType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    UserEquipmentInfoValue:");
            try {
                sb.append(getUserEquipmentInfoValue()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        return sb.append('}').toString();
    }
}
