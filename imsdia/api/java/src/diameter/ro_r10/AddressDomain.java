package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Address-Domain AVP is of type Grouped and indicates the domain/network to which the associated
 * address resides. If this AVP is present, at least one of the AVPs in the grouping must be included.
 */
public class AddressDomain extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new AddressDomain.
     */
    public AddressDomain() {}

    AddressDomain(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any DomainName.
     */
    public boolean containsDomainName() {
        return _data.getContainer().contains(Ro_r10AttributeName.DomainName);
    }

    /**
     * Gets the DomainName.
     */
    public DomainName getDomainName() throws NoSuchAttributeException {
        return (DomainName)_data.getContainer().get(Ro_r10AttributeName.DomainName, 0);
    }

    /**
     * Sets the DomainName.
     *
     * @param avp - the attribute value
     */
    public void setDomainName(DomainName avp) {
        _data.getContainer().add(Ro_r10AttributeName.DomainName, avp.getData(), true);
    }

    /**
     * Tests whether there is any Ro3GPPIMSIMCCMNC.
     */
    public boolean containsRo3GPPIMSIMCCMNC() {
        return _data.getContainer().contains(Ro_r10AttributeName.Ro3GPPIMSIMCCMNC);
    }

    /**
     * Gets the Ro3GPPIMSIMCCMNC.
     */
    public Ro3GPPIMSIMCCMNC getRo3GPPIMSIMCCMNC() throws NoSuchAttributeException {
        return (Ro3GPPIMSIMCCMNC)_data.getContainer().get(Ro_r10AttributeName.Ro3GPPIMSIMCCMNC, 0);
    }

    /**
     * Sets the Ro3GPPIMSIMCCMNC.
     *
     * @param avp - the attribute value
     */
    public void setRo3GPPIMSIMCCMNC(Ro3GPPIMSIMCCMNC avp) {
        _data.getContainer().add(Ro_r10AttributeName.Ro3GPPIMSIMCCMNC, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsDomainName()) {
            sb.append("    DomainName:");
            try {
                sb.append(getDomainName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRo3GPPIMSIMCCMNC()) {
            sb.append("    Ro3GPPIMSIMCCMNC:");
            try {
                sb.append(getRo3GPPIMSIMCCMNC()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
