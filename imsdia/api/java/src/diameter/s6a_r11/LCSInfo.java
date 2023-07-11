package diameter.s6a_r11;

import com.intellinet.diameter.*;


/** 
 * The LCS-Info AVP is of type Grouped. This AVP shall contain the following 
 * LCS related information for a subscriber: list of GMLCs in the HPLMN that are 
 * permitted to issue a call/session unrelated or call/session related MT-LR 
 *  location request for this UE;
 *  privacy exception list;
 *  MO-LR list.
 */
public class LCSInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new LCSInfo.
     */
    public LCSInfo() {}

    LCSInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of GMLCNumber instances.
     */
    public int countGMLCNumber() {
        return _data.getContainer().count(S6a_r11AttributeName.GMLCNumber);
    }

    /**
     * Gets one GMLCNumber.
     *
     * @param index - the index of the attribute to return
     */
    public GMLCNumber getGMLCNumber(int index) throws NoSuchAttributeException {
        return (GMLCNumber)_data.getContainer().get(S6a_r11AttributeName.GMLCNumber, index);
    }

    /**
     * Adds one GMLCNumber.
     *
     * @param avp - the attribute value
     */
    public void addGMLCNumber(GMLCNumber avp) {
        _data.getContainer().add(S6a_r11AttributeName.GMLCNumber, avp.getData(), false);
    }

    /**
     * Returns number of LCSPrivacyException instances.
     */
    public int countLCSPrivacyException() {
        return _data.getContainer().count(S6a_r11AttributeName.LCSPrivacyException);
    }

    /**
     * Gets one LCSPrivacyException.
     *
     * @param index - the index of the attribute to return
     */
    public LCSPrivacyException getLCSPrivacyException(int index) throws NoSuchAttributeException {
        return (LCSPrivacyException)_data.getContainer().get(S6a_r11AttributeName.LCSPrivacyException, index);
    }

    /**
     * Adds one LCSPrivacyException.
     *
     * @param avp - the attribute value
     */
    public void addLCSPrivacyException(LCSPrivacyException avp) {
        _data.getContainer().add(S6a_r11AttributeName.LCSPrivacyException, avp.getData(), false);
    }

    /**
     * Returns number of MOLR instances.
     */
    public int countMOLR() {
        return _data.getContainer().count(S6a_r11AttributeName.MOLR);
    }

    /**
     * Gets one MOLR.
     *
     * @param index - the index of the attribute to return
     */
    public MOLR getMOLR(int index) throws NoSuchAttributeException {
        return (MOLR)_data.getContainer().get(S6a_r11AttributeName.MOLR, index);
    }

    /**
     * Adds one MOLR.
     *
     * @param avp - the attribute value
     */
    public void addMOLR(MOLR avp) {
        _data.getContainer().add(S6a_r11AttributeName.MOLR, avp.getData(), false);
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
        for (int i = 0; i < countGMLCNumber(); ++i) {
            sb.append("    GMLCNumber:");
            try {
                sb.append(getGMLCNumber(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countLCSPrivacyException(); ++i) {
            sb.append("    LCSPrivacyException:");
            try {
                sb.append(getLCSPrivacyException(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countMOLR(); ++i) {
            sb.append("    MOLR:");
            try {
                sb.append(getMOLR(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
