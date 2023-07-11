package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPACHInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new CAPACHInformation.
     */
    public CAPACHInformation() {}

    CAPACHInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any CAPACHBeepTone.
     */
    public boolean containsCAPACHBeepTone() {
        return _data.getContainer().contains(Transatel_custom_avpsAttributeName.CAPACHBeepTone);
    }

    /**
     * Gets the CAPACHBeepTone.
     */
    public CAPACHBeepTone getCAPACHBeepTone() throws NoSuchAttributeException {
        return (CAPACHBeepTone)_data.getContainer().get(Transatel_custom_avpsAttributeName.CAPACHBeepTone, 0);
    }

    /**
     * Sets the CAPACHBeepTone.
     *
     * @param avp - the attribute value
     */
    public void setCAPACHBeepTone(CAPACHBeepTone avp) {
        _data.getContainer().add(Transatel_custom_avpsAttributeName.CAPACHBeepTone, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsCAPACHBeepTone()) {
            sb.append("    CAPACHBeepTone:");
            try {
                sb.append(getCAPACHBeepTone()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
