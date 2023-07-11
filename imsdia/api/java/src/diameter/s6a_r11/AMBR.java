package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The AMBR AVP is of type Grouped.
 */
public class AMBR extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AMBR.
     */
    public AMBR() {}

    AMBR(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the MaxRequestedBandwidthUL.
     */
    public MaxRequestedBandwidthUL getMaxRequestedBandwidthUL() throws NoSuchAttributeException {
        return (MaxRequestedBandwidthUL)_data.getContainer().get(S6a_r11AttributeName.MaxRequestedBandwidthUL, 0);
    }

    /**
     * Sets the MaxRequestedBandwidthUL.
     *
     * @param avp - the attribute value
     */
    public void setMaxRequestedBandwidthUL(MaxRequestedBandwidthUL avp) {
        _data.getContainer().add(S6a_r11AttributeName.MaxRequestedBandwidthUL, avp.getData(), true);
    }

    /**
     * Gets the MaxRequestedBandwidthDL.
     */
    public MaxRequestedBandwidthDL getMaxRequestedBandwidthDL() throws NoSuchAttributeException {
        return (MaxRequestedBandwidthDL)_data.getContainer().get(S6a_r11AttributeName.MaxRequestedBandwidthDL, 0);
    }

    /**
     * Sets the MaxRequestedBandwidthDL.
     *
     * @param avp - the attribute value
     */
    public void setMaxRequestedBandwidthDL(MaxRequestedBandwidthDL avp) {
        _data.getContainer().add(S6a_r11AttributeName.MaxRequestedBandwidthDL, avp.getData(), true);
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
        sb.append("    MaxRequestedBandwidthUL:");
            try {
                sb.append(getMaxRequestedBandwidthUL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    MaxRequestedBandwidthDL:");
            try {
                sb.append(getMaxRequestedBandwidthDL()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
