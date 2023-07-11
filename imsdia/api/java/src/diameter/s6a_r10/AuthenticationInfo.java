package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The Authentication-Info AVP is of type Grouped. This AVP contains Authentication Vectors.
 */
public class AuthenticationInfo extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AuthenticationInfo.
     */
    public AuthenticationInfo() {}

    AuthenticationInfo(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Returns number of EUTRANVector instances.
     */
    public int countEUTRANVector() {
        return _data.getContainer().count(S6a_r10AttributeName.EUTRANVector);
    }

    /**
     * Gets one EUTRANVector.
     *
     * @param index - the index of the attribute to return
     */
    public EUTRANVector getEUTRANVector(int index) throws NoSuchAttributeException {
        return (EUTRANVector)_data.getContainer().get(S6a_r10AttributeName.EUTRANVector, index);
    }

    /**
     * Adds one EUTRANVector.
     *
     * @param avp - the attribute value
     */
    public void addEUTRANVector(EUTRANVector avp) {
        _data.getContainer().add(S6a_r10AttributeName.EUTRANVector, avp.getData(), false);
    }

    /**
     * Returns number of UTRANVector instances.
     */
    public int countUTRANVector() {
        return _data.getContainer().count(S6a_r10AttributeName.UTRANVector);
    }

    /**
     * Gets one UTRANVector.
     *
     * @param index - the index of the attribute to return
     */
    public UTRANVector getUTRANVector(int index) throws NoSuchAttributeException {
        return (UTRANVector)_data.getContainer().get(S6a_r10AttributeName.UTRANVector, index);
    }

    /**
     * Adds one UTRANVector.
     *
     * @param avp - the attribute value
     */
    public void addUTRANVector(UTRANVector avp) {
        _data.getContainer().add(S6a_r10AttributeName.UTRANVector, avp.getData(), false);
    }

    /**
     * Returns number of GERANVector instances.
     */
    public int countGERANVector() {
        return _data.getContainer().count(S6a_r10AttributeName.GERANVector);
    }

    /**
     * Gets one GERANVector.
     *
     * @param index - the index of the attribute to return
     */
    public GERANVector getGERANVector(int index) throws NoSuchAttributeException {
        return (GERANVector)_data.getContainer().get(S6a_r10AttributeName.GERANVector, index);
    }

    /**
     * Adds one GERANVector.
     *
     * @param avp - the attribute value
     */
    public void addGERANVector(GERANVector avp) {
        _data.getContainer().add(S6a_r10AttributeName.GERANVector, avp.getData(), false);
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
        for (int i = 0; i < countEUTRANVector(); ++i) {
            sb.append("    EUTRANVector:");
            try {
                sb.append(getEUTRANVector(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countUTRANVector(); ++i) {
            sb.append("    UTRANVector:");
            try {
                sb.append(getUTRANVector(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countGERANVector(); ++i) {
            sb.append("    GERANVector:");
            try {
                sb.append(getGERANVector(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
