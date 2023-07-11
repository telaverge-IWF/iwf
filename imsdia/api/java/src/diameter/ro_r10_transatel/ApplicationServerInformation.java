package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Application-Server-Information is of type Grouped and contains information about
 * application servers visited through ISC interface.
 */
public class ApplicationServerInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new ApplicationServerInformation.
     */
    public ApplicationServerInformation() {}

    ApplicationServerInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any ApplicationServer.
     */
    public boolean containsApplicationServer() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.ApplicationServer);
    }

    /**
     * Gets the ApplicationServer.
     */
    public ApplicationServer getApplicationServer() throws NoSuchAttributeException {
        return (ApplicationServer)_data.getContainer().get(Ro_r10_transatelAttributeName.ApplicationServer, 0);
    }

    /**
     * Sets the ApplicationServer.
     *
     * @param avp - the attribute value
     */
    public void setApplicationServer(ApplicationServer avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ApplicationServer, avp.getData(), true);
    }

    /**
     * Returns number of ApplicationProvidedCalledPartyAddress instances.
     */
    public int countApplicationProvidedCalledPartyAddress() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.ApplicationProvidedCalledPartyAddress);
    }

    /**
     * Gets one ApplicationProvidedCalledPartyAddress.
     *
     * @param index - the index of the attribute to return
     */
    public ApplicationProvidedCalledPartyAddress getApplicationProvidedCalledPartyAddress(int index) throws NoSuchAttributeException {
        return (ApplicationProvidedCalledPartyAddress)_data.getContainer().get(Ro_r10_transatelAttributeName.ApplicationProvidedCalledPartyAddress, index);
    }

    /**
     * Adds one ApplicationProvidedCalledPartyAddress.
     *
     * @param avp - the attribute value
     */
    public void addApplicationProvidedCalledPartyAddress(ApplicationProvidedCalledPartyAddress avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.ApplicationProvidedCalledPartyAddress, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsApplicationServer()) {
            sb.append("    ApplicationServer:");
            try {
                sb.append(getApplicationServer()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countApplicationProvidedCalledPartyAddress(); ++i) {
            sb.append("    ApplicationProvidedCalledPartyAddress:");
            try {
                sb.append(getApplicationProvidedCalledPartyAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
