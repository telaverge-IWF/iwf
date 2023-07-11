package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The Redirect-Server AVP (AVP Code 434) is of type Grouped and contains the address 
 * information of the redirect server (e.g., HTTP redirect server, SIP Server) with which 
 * the end user is to be connected when the account cannot cover the service cost.It MUST be
 * present when the Final-Unit-Action AVP is set to REDIRECT.
 */
public class RedirectServer extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new RedirectServer.
     */
    public RedirectServer() {}

    RedirectServer(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the RedirectAddressType.
     */
    public RedirectAddressType getRedirectAddressType() throws NoSuchAttributeException {
        return (RedirectAddressType)_data.getContainer().get(DccaAttributeName.RedirectAddressType, 0);
    }

    /**
     * Sets the RedirectAddressType.
     *
     * @param avp - the attribute value
     */
    public void setRedirectAddressType(RedirectAddressType avp) {
        _data.getContainer().add(DccaAttributeName.RedirectAddressType, avp.getData(), true);
    }

    /**
     * Gets the RedirectServerAddress.
     */
    public RedirectServerAddress getRedirectServerAddress() throws NoSuchAttributeException {
        return (RedirectServerAddress)_data.getContainer().get(DccaAttributeName.RedirectServerAddress, 0);
    }

    /**
     * Sets the RedirectServerAddress.
     *
     * @param avp - the attribute value
     */
    public void setRedirectServerAddress(RedirectServerAddress avp) {
        _data.getContainer().add(DccaAttributeName.RedirectServerAddress, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    RedirectAddressType:");
            try {
                sb.append(getRedirectAddressType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    RedirectServerAddress:");
            try {
                sb.append(getRedirectServerAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        return sb.append('}').toString();
    }
}
