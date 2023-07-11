package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AoC-Service AVP (AVP code 2311) is of type Grouped and holds the pair of 
 * AoC Service type and AoC Service obligatory type.
 */
public class AoCService extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AoCService.
     */
    public AoCService() {}

    AoCService(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any AoCServiceObligatoryType.
     */
    public boolean containsAoCServiceObligatoryType() {
        return _data.getContainer().contains(Ro_r10AttributeName.AoCServiceObligatoryType);
    }

    /**
     * Gets the AoCServiceObligatoryType.
     */
    public AoCServiceObligatoryType getAoCServiceObligatoryType() throws NoSuchAttributeException {
        return (AoCServiceObligatoryType)_data.getContainer().get(Ro_r10AttributeName.AoCServiceObligatoryType, 0);
    }

    /**
     * Sets the AoCServiceObligatoryType.
     *
     * @param avp - the attribute value
     */
    public void setAoCServiceObligatoryType(AoCServiceObligatoryType avp) {
        _data.getContainer().add(Ro_r10AttributeName.AoCServiceObligatoryType, avp.getData(), true);
    }

    /**
     * Tests whether there is any AoCServiceType.
     */
    public boolean containsAoCServiceType() {
        return _data.getContainer().contains(Ro_r10AttributeName.AoCServiceType);
    }

    /**
     * Gets the AoCServiceType.
     */
    public AoCServiceType getAoCServiceType() throws NoSuchAttributeException {
        return (AoCServiceType)_data.getContainer().get(Ro_r10AttributeName.AoCServiceType, 0);
    }

    /**
     * Sets the AoCServiceType.
     *
     * @param avp - the attribute value
     */
    public void setAoCServiceType(AoCServiceType avp) {
        _data.getContainer().add(Ro_r10AttributeName.AoCServiceType, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsAoCServiceObligatoryType()) {
            sb.append("    AoCServiceObligatoryType:");
            try {
                sb.append(getAoCServiceObligatoryType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAoCServiceType()) {
            sb.append("    AoCServiceType:");
            try {
                sb.append(getAoCServiceType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
