package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class MMEUserState extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MMEUserState.
     */
    public MMEUserState() {}

    MMEUserState(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any UserState.
     */
    public boolean containsUserState() {
        return _data.getContainer().contains(S6a_r10AttributeName.UserState);
    }

    /**
     * Gets the UserState.
     */
    public UserState getUserState() throws NoSuchAttributeException {
        return (UserState)_data.getContainer().get(S6a_r10AttributeName.UserState, 0);
    }

    /**
     * Sets the UserState.
     *
     * @param avp - the attribute value
     */
    public void setUserState(UserState avp) {
        _data.getContainer().add(S6a_r10AttributeName.UserState, avp.getData(), true);
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
        if (containsUserState()) {
            sb.append("    UserState:");
            try {
                sb.append(getUserState()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
