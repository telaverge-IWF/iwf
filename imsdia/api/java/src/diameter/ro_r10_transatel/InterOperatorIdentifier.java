package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Inter-Operator-Identifier AVP is of type Grouped and holds the identification of the
 * network neighbours (originating and terminating) as exchanged via SIP signalling.
 */
public class InterOperatorIdentifier extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new InterOperatorIdentifier.
     */
    public InterOperatorIdentifier() {}

    InterOperatorIdentifier(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any OriginatingIOI.
     */
    public boolean containsOriginatingIOI() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.OriginatingIOI);
    }

    /**
     * Gets the OriginatingIOI.
     */
    public OriginatingIOI getOriginatingIOI() throws NoSuchAttributeException {
        return (OriginatingIOI)_data.getContainer().get(Ro_r10_transatelAttributeName.OriginatingIOI, 0);
    }

    /**
     * Sets the OriginatingIOI.
     *
     * @param avp - the attribute value
     */
    public void setOriginatingIOI(OriginatingIOI avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.OriginatingIOI, avp.getData(), true);
    }

    /**
     * Tests whether there is any TerminatingIOI.
     */
    public boolean containsTerminatingIOI() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.TerminatingIOI);
    }

    /**
     * Gets the TerminatingIOI.
     */
    public TerminatingIOI getTerminatingIOI() throws NoSuchAttributeException {
        return (TerminatingIOI)_data.getContainer().get(Ro_r10_transatelAttributeName.TerminatingIOI, 0);
    }

    /**
     * Sets the TerminatingIOI.
     *
     * @param avp - the attribute value
     */
    public void setTerminatingIOI(TerminatingIOI avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.TerminatingIOI, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsOriginatingIOI()) {
            sb.append("    OriginatingIOI:");
            try {
                sb.append(getOriginatingIOI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTerminatingIOI()) {
            sb.append("    TerminatingIOI:");
            try {
                sb.append(getTerminatingIOI()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
